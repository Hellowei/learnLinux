/*******************************************************************************
* FILE		: wave.c
* Description	: 为了实现高效回放,本刷波模块将使用大量内存,建议在内存充足的情况
*				 下使用,每注册一道波形大约需要1~8M(以波形映射高度,回放长度而定)
*			  
* Copyright (c) 2013 by zondan. All Rights Reserved.
* 
* History:
* Version		Name	   		Date			Description
   0.1			wave.c		2013/11/16		Initial Version
   
*******************************************************************************/

#if _ENB_WAVE_DRIVE
#define WAVE_GLOBALS
#include "includes.h"
#include "wave.h"

typedef struct wave_database{
	struct wave_database *next;
	int name;	//	波形唯一标识
	PWAVEBASE pBase;	//	继承属性
	GAL_PIXEL color;	//	波形颜色
	PRINT_WAVE_TYPE type;	//	波形种类
	int left;	//	client left
	int top;	//	client top
	int right;	//	client right
	int bottom;	//	client bottom
	int width;	//	wave width	= right - left
	int height;	//	wave height	= bottom - top
	//	draw wave
	int drawflag;
	int	page;
	int pagelen;
	int currPage;	//	当前可用的最大页数
	int drawPage;	//	当前显示最小页数
	int drawCnt;	//	已画点数/画点计数
	int *data;
	int *tail;
	int *curr;
	//	wave real data
	int maxVal;
	int minVal;
	int inVal;
	int diffVal;
	int cacheSize;	//	由采样率决定大小,size=60*SampleRate
	int *cacheHead;
	int *cacheTail;
	int *pCacheW;	//	缓存写指针
	int *pCacheR;	//	缓存读指针
	struct wave_database *previous;
}WAVEDB, *PWAVEDB;

static PWAVEDB sDataBase = NULL;

const static STRINGID Str_Analy[12] = {
	STR_DLG_FHR_DIAG_ACC_NORMAL,
	STR_DLG_FHR_DIAG_ACC_LITTLE,
	STR_DLG_FHR_DIAG_ACC_FASTIGIA,
	STR_DLG_FHR_DIAG_REDUCE_SLOW,
	STR_DLG_FHR_DIAG_REDUCE_LITTLE,
	STR_DLG_FHR_DIAG_REDUCE_SLOW_TAIL,
	STR_DLG_FHR_DIAG_REDUCE_VARY_SLOW,
	STR_DLG_FHR_DIAG_REDUCE_HEAVY_VARY,
	STR_DLG_FHR_DIAG_REDUCE_LIGHT_VARY,
	STR_DLG_FHR_DIAG_REDUCE_EARLY,
	STR_DLG_FHR_DIAG_REDUCE_EXTEND,
	STR_DLG_FHR_DIAG_REDUCE_EARLY_VARY
};

const static STRINGID Str_Event[15] = {
	STR_DLG_DRM_A,
	STR_DLG_DRM_B,
	STR_DLG_DRM_C,
	STR_DLG_DRM_D,
	STR_DLG_DRM_E,
	STR_DLG_DRM_F,
	STR_DLG_DRM_G,
	STR_DLG_DRM_H,
	STR_DLG_DRM_I,
	STR_DLG_DRM_J,
	STR_DLG_DRM_K,
	STR_DLG_DRM_L,
	STR_DLG_DRM_M,
	STR_DLG_DRM_N,
	STR_DLG_DRM_O
};


static  UINT8 uparrow_sign[] =
{
	________,
	___XX___,
	__XXXX__,
	_XXXXXX_,
	XXXXXXXX,
	__XXXX__,
	__XXXX__,
	__XXXX__,
	__XXXX__,
	________
};

static  UINT8 zero_sign[] =
{
	________,
	_X____X_,
	_XX__XX_,
	_XXXXXX_,
	_XX__XX_,
	_X____X_,
	________
};

const static BITMAP Bmp_Fm = { 0, 1, 8, 10, 1, (VOID*)uparrow_sign };

const static BITMAP Bmp_Zero = { 0, 1, 8,  7, 1, (VOID*)zero_sign };

const static int InvalData = INVALID_PARAM_INT;

const static int VgaPixel = 
	(SCREEN_WIDTH * (WAVE_SPEED_30 + 1) * 100 / DIMENSIONS_W);

void DestroyWaveBuffer(void)
{
	PWAVEDB p = sDataBase;
	PWAVEDB previous;
	sDataBase = NULL;
	if (p) while (p->next) p = p->next;
	while (p) {
		previous = p->previous;
		free (p->cacheHead);
		free (p->data);
		free (p);
		p = previous;
	}
}

static BOOL gen_NewWave(int name)
{
	PWAVEDB p = sDataBase;

	if (NULL == p)
	{
		if (NULL == (p = (PWAVEDB)malloc(sizeof(WAVEDB))))
			return FALSE;

		ZeroMemory(p, sizeof(WAVEDB));

		p->name = name;

		sDataBase = p;

		return TRUE;
	}

	while (p) {
		if (p->name == name)	// not a new wave
			return FALSE;

		if (NULL == p->next)
			break;
	}

	if (NULL == (p->next = (PWAVEDB)malloc(sizeof(WAVEDB))))
		return FALSE;

	ZeroMemory(p->next, sizeof(WAVEDB));

	p->next->previous = p;

	p = p->next;

	p->name = name;

	return TRUE;
}

static PWAVEDB GetWaveByName(int name)
{
	PWAVEDB p = sDataBase;
	
	if (0 == name)
		return NULL;

	while (p) {
		if (p->name == name)
			break;
		
		p = p->next;
	}
	
	return p;
}

static void DrawBrushBar(HDC hdc, PWAVEBASE pBase, int right)
{
	int remainder;
	int x, i;
	PDC pdc;
	GAL_PIXEL old;
	if (FALSE == pBase->isBrush)
		return;

	remainder = pBase->brushWidth;
	old = SetPenColor(hdc, *(pBase->brColor));
	pdc = dc_HDC2PDC(hdc);
	x = pBase->xPos + 1;
	if (x > pdc->DevRC.right)
		x -= pdc->DevRC.right;
	i = 0;
	if (FALSE == pBase->is3dBrush) {
		while (remainder > i) {
			SetPenColor(hdc, *(pBase->brColor + i));
			Line(hdc, x, 0, x, pBase->background->cy);
			if (++x > right)
				x = 0;
			i++;
		}
	} else {
		while (remainder > i) {
			Line(hdc, x, 0, x, pBase->background->cy);
			if (++x > right)
				x = 0;

			i++;
		}
	}
	SetPenColor(hdc, old);
}

static BOOL IsWaveCanDraw(PWAVEDB pWave)
{
	BOOL flag = FALSE;
	do {
		if (FALSE == pWave->drawflag)
			break;

		if (NULL == pWave->pBase)
			break;

		if (HWND_DESKTOP == pWave->pBase->hWnd)
			break;

		if (HWND_INVALID == pWave->pBase->hWnd)
			break;

		if (0 == pWave->page)
			break;

		if (0 == pWave->pagelen)
			break;

		if (NULL == pWave->data)
			break;

		if (pWave->curr < pWave->data || pWave->curr >pWave->tail)
			break;

		return TRUE;
	} while (0);
	return FALSE;
}

void MapWaveHeight(PWAVEDB pWave)
{
	//VgaPixel
	double foffset, fdata;
	int *target;
	int index;
	int av;
	int pos;
	if (pWave->pCacheR == pWave->pCacheW)
		return;

	foffset = (double)((pWave->curr + 1 - pWave->data) % pWave->pagelen);
	fdata = foffset * pWave->cacheSize / VgaPixel;
	index = (int)fdata;
	fdata -= index;
	if (fdata > 0)
		index++;

	target = pWave->cacheHead + index;

	if (pWave->pCacheR < pWave->pCacheW) {
		if (target <= pWave->pCacheR || target > pWave->pCacheW)
			return;
	}

	if (pWave->pCacheR > pWave->pCacheW) {
		if (target <= pWave->pCacheR && target > pWave->pCacheW) 
			return;
	}

	if (target == pWave->cacheHead)
		av = *(pWave->cacheTail) * fdata + (*target) * (1 - fdata);
	else
		av = *(target - 1) * fdata + (*target) * (1 - fdata);

	if (pWave->inVal == av) {
		pos = InvalData;
	}
	else if (pWave->maxVal <= av) {
		pos = pWave->top + 1;
	}
	else if (pWave->minVal >= av) {
		pos = pWave->bottom - 1;
	}
	else {
		pos = (av - pWave->minVal) * pWave->height / pWave->diffVal;
		pos = pWave->bottom - pos;
	}
	*(pWave->curr) = pos;
	if (pWave->curr == pWave->tail)
		pWave->curr = pWave->data;
	else
		pWave->curr++;
}

static STATUS MoveWaveBrush(PWAVEDB pWave)
{
	//STATUS moved = STATUS;
	int nrPage = -1;
	int xPos;
	if (pWave->pBase && pWave->pBase->speed)
		nrPage = WAVE_CX_CM / (*(pWave->pBase->speed) + 1);
	else
		return ERR_INVALID_HANDLE;

	if (nrPage < pWave->currPage - pWave->drawPage) {
		// 不需要画刷子，需要重绘全部背景
		pWave->pBase->xPos = -1;
		return TRUE;
	}
	else {
		// 将xPos移动到要画点的后一个位置
		xPos = (pWave->curr - pWave->data) % pWave->pagelen;
		xPos = xPos * WAVE_SPEED_MAX / (*(pWave->pBase->speed) + 1);
		if ( pWave->pBase->xPos < xPos) {
			pWave->pBase->xPos = xPos;
			return ERR_OK;
		}
	}
	return ERR_ALREADY_EXIST;
}

static void sDrawWave(PWAVEDB pWave)
{
	int page;
	int speed = *(pWave->pBase->speed);
	int numPoint;
	int *pageStart = pWave->data + (pWave->pagelen * pWave->drawPage);
	int *drawStart;
	int step = 0;
	int oldPos, newPos;
	numPoint = pWave->curr - pageStart;
	if (numPoint < 0)
		numPoint += pWave->page * pWave->pagelen;
	if (numPoint < 0) {
		printf("On Line:%d,In Functions:sDrawWave 'numPoint'error\n",__LINE__);
		return;
	}
	drawStart = pageStart + (pWave->drawCnt - 1) * (speed + 1);
	if (drawStart > pWave->tail)
	{
		drawStart -= pWave->page * pWave->pagelen;
	}
	switch (speed) {
		case WAVE_SPEED_10:
			numPoint /= 3;
			break;

		case WAVE_SPEED_20:
			numPoint = numPoint * 2 / 3;
			break;

		case WAVE_SPEED_30:
			break;

		default:
			printf("On Line:%d,In Functions:sDrawWave 'speed'error\n",__LINE__);
			return;
	}
	switch (pWave->type)
	{
		case PRINT_WAVE_SAMPLE:
		{
			newPos = *drawStart;
			HDC hdc = GetDC(pWave->pBase->hWnd);
			while (pWave->drawCnt < numPoint) {
				drawStart += (speed + 1);
				oldPos = newPos;
				newPos = *drawStart;
				if (newPos > 0)
				{
					if (pWave->drawCnt - 1 > 0)
					{
						DrawLine(hdc, pWave->drawCnt - 1, oldPos,
							pWave->drawCnt, newPos);
					}
					else
					{
						DrawLine(hdc, pWave->drawCnt, newPos-1,
							pWave->drawCnt, newPos);
					}
				}
				pWave->drawCnt++;
			}
			ReleaseDC(hdc);
		}
			break;

		case PRINT_WAVE_FHR:
		{
			newPos = *drawStart;
			HDC hdc = GetDC(pWave->pBase->hWnd);
			while (pWave->drawCnt < numPoint)
			{
				drawStart += (speed + 1);
				oldPos = newPos;
				newPos = *drawStart;
				if (newPos > 0)
				{
					if ((pWave->drawCnt - 1 > 0)
						&& (ABS(newPos - oldPos) < FHR_MAX_OFFSET))
					{
						DrawLine(hdc, pWave->drawCnt - 1, oldPos,
							pWave->drawCnt, newPos);
					}
					else
					{
						DrawLine(hdc, pWave->drawCnt, newPos-1,
							pWave->drawCnt, newPos);
					}
				}
				pWave->drawCnt++;
			}
			ReleaseDC(hdc);
		}
			break;

		case PRINT_WAVE_MARK:
		{
			/* 对于标记来说,波形数据相当于ICONID */
//			HDC hdc = GetDC(pWave->pBase->hWnd);
//			int id;
//			while(drawStart != pWave)
//			{
//				id = *drawStart++;
//				if (id > STR_NULL)
//				{
//					DrawIcon(hdc, x, pWave->top, id);
//				}
//			}
//			ReleaseDC(hdc);
		}
			break;

		case PRINT_WAVE_STR:
		{
			/* 对于字符标记来说,波形数据相当于STRINGID */
			/* 中文可以使用垂直文本 *//* 其它语言横置文本 */
			HDC hdc = GetDC(pWave->pBase->hWnd);
			PLOGFONT pFont = GetSystemFont(SYSLOGFONT_WCHAR_DEF);
			int id;
			int i;
			while(drawStart != pWave->curr)
			{
				id = STR_NULL;
				for (i = 0; i < WAVE_SPEED_MAX - speed; i++)
				{
					if (*drawStart > STR_NULL)
					{
						id = *drawStart;
					}
					drawStart++;
					if (drawStart > pWave->tail)
					{
						drawStart = pWave->data;
					}
				}
				if (id  > STR_NULL && id < STR_MAXNUM)
				{
					VerticalTextOutLen(hdc, pWave->drawCnt, pWave->top,
						LoadString(id), -1);
					pWave->drawCnt += pFont->size;
					drawStart += pFont->size * (WAVE_SPEED_MAX - speed);
					if (drawStart > pWave->tail)
					{
						drawStart -= (pWave->tail - pWave->data);
					}
				}
				else
				{
					pWave->drawCnt ++;
				}
			}
			ReleaseDC(hdc);
		}
			break;

		default:
			return;
	}
}

/******************** 基本属性,控件句柄,背景,速度,刷新条等 ********************/
void SetWaveOptions(int name, PWAVEBASE p, PRECT prc)
{
	PWAVEDB pWave;
	RECT rc;
	if (pWave = GetWaveByName(name))
	{
		if (p)
			pWave->pBase = p;
	}
	else {
		gen_NewWave(name);
		if (pWave = GetWaveByName(name))
		{
			if (p)
				pWave->pBase = p;
		}
	}
	if (pWave) {
		if (prc) {
			pWave->left = prc->left;
			pWave->top = prc->top;
			pWave->right = prc->right;
			pWave->bottom = prc->bottom;
			pWave->height = RECTHP(prc);
			pWave->width = RECTWP(prc);
		}
		else {
			pWave->left = 0;
			pWave->top = 0;
			pWave->right = 0;
			pWave->bottom = 0;
			pWave->height = 0;
			pWave->width = 0;
		}
		if (pWave->pBase) {
			if (HWND_DESKTOP == pWave->pBase->hWnd)
				return;
			
			if (HWND_INVALID == pWave->pBase->hWnd)
				return;

			GetClientRect(pWave->pBase->hWnd, &rc);
			pWave->left = (pWave->left > rc.left) ? pWave->left : rc.left;
			pWave->top = (pWave->top > rc.top) ? pWave->top : rc.top;
			pWave->right = (pWave->right < rc.right) ? pWave->right : rc.right;
			pWave->bottom =
				(pWave->bottom < rc.bottom) ? pWave->bottom : rc.bottom;
			pWave->height =
				(pWave->height < RECTH(rc)) ? pWave->height : RECTH(rc);
			pWave->width =
				(pWave->width < RECTW(rc)) ? pWave->width : RECTW(rc);
		}
	}
}

/***************************** 波形属性,颜色,类型 *****************************/
void SetWaveColor(int name, GAL_PIXEL color)
{
	PWAVEDB pWave;
	if (pWave = GetWaveByName(name))
	{
		pWave->color = color;
	}
	else {
		gen_NewWave(name);
		if (pWave = GetWaveByName(name))
			pWave->color = color;
	}
}

void SetWaveType(int name, PRINT_WAVE_TYPE type)
{
	PWAVEDB pWave;
	if (pWave = GetWaveByName(name))
	{
		pWave->type = type;
	}
	else {
		gen_NewWave(name);
		if (pWave = GetWaveByName(name))
			pWave->type = type;
	}
}

/********************* 数据操作,设置、写入、清空波形数据 *********************/
void SetBufferLength(int name, int page, int size)
{
	PWAVEDB pWave;
	if (pWave = GetWaveByName(name)) {
		pWave->page = page;
		pWave->pagelen = size;

		if (pWave->data) {
			free (pWave->data);

			pWave->data = NULL;
			pWave->tail = NULL;
			pWave->curr = NULL;
		}

		if (pWave->data = (int *)malloc(page * size * sizeof(int))) {
			pWave->tail = pWave->data + (page * size);
			pWave->curr = pWave->data;
		}
		
	}
}

void SetWaveSampleRate(int name, float sample)
{
	PWAVEDB pWave;
	if (pWave = GetWaveByName(name)) {
		int ilen;
		float flen;
		do {
			if (ABS(sample) > 0) {
				flen = sample * 60;
				ilen = (int)flen;

				if (flen > ilen)
					break;
			}
			else
				break;

			if (pWave->cacheHead) {
				free (pWave->cacheHead);
				pWave->cacheHead = NULL;
				pWave->cacheTail = NULL;
				pWave->pCacheW = NULL;
				pWave->pCacheR = NULL;
				pWave->cacheSize = 0;
			}

			if (pWave->cacheHead = (int *)malloc(ilen * sizeof(int))) {
				pWave->cacheTail = pWave->cacheHead + ilen;
				pWave->pCacheW = pWave->cacheHead;
				pWave->pCacheR = pWave->cacheHead;
				pWave->cacheSize = ilen;
			}
		} while (0);
	}
}

void SetWaveDataRange(int name, int maxVal, int minVal, int invalid)
{
	PWAVEDB pWave;
	if (pWave = GetWaveByName(name)) {
		if (maxVal > minVal && (maxVal < invalid || minVal > invalid)) {
			pWave->maxVal = maxVal;
			pWave->minVal = minVal;
			pWave->inVal = invalid;
			pWave->diffVal = pWave->maxVal - pWave->minVal;
		}
	}
}

void PutWaveData(int name, int data)
{
	PWAVEDB pWave;
	if (pWave = GetWaveByName(name)) {
		if (pWave->cacheHead) {

			*(pWave->pCacheW) = data;
			
			if (pWave->pCacheW == pWave->cacheTail)
				pWave->pCacheW = pWave->cacheHead;
			else
				pWave->pCacheW++;
		}
		MapWaveHeight(pWave);
	}
}

void CleanWaveDataBuffer(int name)
{
	PWAVEDB pWave;
	if (pWave = GetWaveByName(name)) {

		int *p = pWave->data;

		if (NULL == p)
			return;

		while (p <= pWave->tail)
			*p++ = InvalData;

		pWave->curr = pWave->data;
		pWave->currPage = 0;
	}
}

/*********************** UI操作,包括翻页,隐藏,显示,刷新 ***********************/
void RefreshWaveBackground(BOOLEAN all)
{
	//	历遍所有波形数据,找出需要画的波形刷新背景
	int nrWave = 0;
	int nrBase = 0;
	int i;
	PWAVEDB pWave = sDataBase;
	PWAVEBASE *p;
	PWAVEBASE pBase;
	HDC hdc;
	PDC pdc;
	RECT rc;
	while(pWave) {
		if (pWave->drawflag && pWave->pBase && pWave->pBase->background)
			nrWave++;

		pWave = pWave->next;
	}

	if (nrWave == 0)
		return;

	if (NULL == (p = (PWAVEBASE*)malloc(nrWave * sizeof(PWAVEBASE))))
		return;

	pWave = sDataBase;
	ZeroMemory(p, nrWave * sizeof(PWAVEBASE));
	while(nrWave > 0) {
		if (pWave->drawflag && pWave->pBase && pWave->pBase->background) {
			nrWave--;
			if (pWave->pBase->hWnd != HWND_INVALID) {
				nrBase++;
				*(p + nrBase - 1) = pWave->pBase;
			}
			for (i = 0; i < nrBase - 1; i++) {
				if (*(p + nrBase - 1) == *(p + i))
					nrBase--;
			}
		}
		pWave = pWave->next;
	}
	for (i = 0; i < nrBase - 1; i++) {
		pBase = *(p + i);
		hdc = GetDC(pBase->hWnd);
		pdc = dc_HDC2PDC(hdc);
		if (all) {
			SetRect(&rc, 0, 0, RECTW(pdc->DevRC), RECTH(pdc->DevRC));
			FillRectEx(hdc, &rc, RECTW(rc), pBase->background->data);
		}
		else {
			// 画刷新条背景
			SetRect(&rc, pBase->xPos, 0, pBase->xPos + pBase->brushWidth,
					RECTH(pdc->DevRC));
			FillRectEx(hdc, &rc, RECTW(rc), pBase->background->data);
			DrawBrushBar(hdc, pBase, rc.right);
		}
		ReleaseDC(hdc);
		
	}
}

void PrintWave(int name, int page)
{
	PWAVEDB pWave;
	STATUS status;
	if (pWave = GetWaveByName(name)) {
		if (IsWaveCanDraw(pWave)) {
			if (!(page < 0 || pWave->currPage < page)) {
				pWave->drawPage = page;
				pWave->drawCnt = 0;
			}
			status = MoveWaveBrush(pWave);
			if (status == ERR_INVALID_HANDLE)
				return;

			if (status != ERR_ALREADY_EXIST)
				RefreshWaveBackground((BOOLEAN)status);
			
			sDrawWave(pWave);
		}
	}
}

void SetWaveDrawFlag(int name, char draw)
{
	PWAVEDB pWave;
	if (pWave = GetWaveByName(name))
		pWave->drawflag = (draw == TRUE);
}
#endif

