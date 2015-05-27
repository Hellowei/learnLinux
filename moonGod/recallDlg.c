/*****************************************************************************************
* FILE		: recallDlg.c
* Description	: 
*			  
* Copyright (c) 2013 by XXX. All Rights Reserved.
* 
* History:
* Version		Name	   		Date			Description
   0.1			XXX			2013/10/10		Initial Version
   
*****************************************************************************************/
#include "includes.h"

#define RECALL_PAGE_DATA_NUMBER (6 * 60)
#define RECALL_PAGE_STEP		(5 * 60)
#define RECALL_PAGE_MAX_NUMBER  (DATA_SAVE_LEN / RECALL_PAGE_STEP)
#define RECALL_PAGE_PIXEL_LEN   648

static BITMAPMEM RecallFhrBmpMem   = {0, 0, 0L, 0L, NULL};
static BITMAPMEM RecallTOCOBmpMem  = {0, 0, 0L, 0L, NULL};
static BITMAPMEM RecallInfoGphMem  = {0, 0, 0L, 0L, NULL};
static BITMAPMEM RecallAnalyGphMem = {0, 0, 0L, 0L, NULL};

static PTRPARIENT RecallPatientPtr = NULL;
static UINT8 RecallInfoFlag;
static UINT8 RecallAnalyFlag;
static INT s_lastChoseGrade;//缓存用户上次默认评分法
static UCHAR InfoText[14][40];
static INT8 RecallPage;
static INT8 MaxRecallPage;
static INT32 PageIndex[RECALL_PAGE_MAX_NUMBER];
static HWND hStaticWnd1,hStaticBut1,hStaticBut2;
static VOID InitFetalRecallBmpMem(ICONID icon, PBITMAPMEM pBmpMem)
{
	PFBMEM  this = &FbMem;
	BITMAP  bmp  = GetSystemIcon(icon);
	this->SetMenory(this, pBmpMem);
	this->New(this, bmp.width, bmp.height, 16);
}

static VOID InitFetalRecallGraph(VOID)
{
	BITMAP  bmp;
	RECT	rc;
	INT32   x, y, w, h;
	PFBMEM  this = &FbMem;
	bmp = GetSystemIcon(IDI_FHR_GPH);
	SetRect(&rc, 0, 0, bmp.width, bmp.height);
	this->SetMenory(this, &RecallFhrBmpMem);
	this->SetBrushColor(this, GetWindowElementColor(WEC_EXCOLOR_BLACK1));
	this->FillRect(this, &rc);
	x = 0;
	y = bmp.height * (240 - 160) / (240 - 30);
	w = bmp.width;
	h = bmp.height * 40 / (240 - 30);
	SetRect(&rc, x, y, x+w, y+h);
	this->SetBrushColor(this, GetWindowElementColor(WEC_EXCOLOR_DARKSEAGREEN));
	this->FillRect(this, &rc);
	this->SetForeColor(this, GetWindowElementColor(WEC_EXCOLOR_BLACK2));
	this->SetBackColor(this, PIXEL_transparent);
	this->PutIcon(this, bmp.bits, 0, 0, bmp.width, bmp.height);

	bmp = GetSystemIcon(IDI_TOCO_GPH);
	this->SetMenory(this, &RecallTOCOBmpMem);
	SetRect(&rc, 0, 0, bmp.width, bmp.height);
	this->SetBrushColor(this, GetWindowElementColor(WEC_EXCOLOR_BLACK1));
	this->FillRect(this, &rc);
	this->SetForeColor(this, GetWindowElementColor(WEC_EXCOLOR_BLACK2));
	this->SetBackColor(this, PIXEL_transparent);
	this->PutIcon(this, bmp.bits, 0, 0, bmp.width, bmp.height);

}

static INT32 
	RecallScaleWave(INT32 max, INT32 min, INT32 top, INT32 bottom, INT32 data)
{
	if (data >= max)
		return 0;
	if (data == min)
		return bottom;
	if (data < min)
		return 0;
	INT32 height = bottom-top;
	return (height - ((height * (data - min)) / (max - min)));
}

static PutRecallEvent(HDC hdc, INT32 xPos, UINT8 event)
{
	extern STRINGID EventStrID[16];
//	prinfo("xPos, event...%d, %d\r\n", xPos, event);
	PDC pdc = dc_HDC2PDC(hdc);
	INT32 yPos = 2;
	GAL_PIXEL forecolor = PIXEL_white;
	GAL_PIXEL backcolor = PIXEL_transparent;
	
	if (event > TABLESIZE(EventStrID))
		return;
	
	UCHAR *txt = LoadString(EventStrID[event]);
	
	forecolor = SetTextColor(hdc, forecolor);
	backcolor = SetBkColor(hdc, backcolor);
	
	TextOutVLen(hdc, xPos, yPos, txt, strlen(txt));

	SetTextColor(hdc, forecolor);
	SetBkColor(hdc, backcolor);

}

static PutRecallAnalysis(HDC hdc, INT32 xPos, UINT8 analysis)
{
	extern STRINGID AnalyStrID[12];
	
	PDC pdc = dc_HDC2PDC(hdc);
	INT32 yPos = RECTH(pdc->DevRC) - 100;
	GAL_PIXEL forecolor = PIXEL_white;
	
	if (analysis > TABLESIZE(AnalyStrID))
		return;
	
	UCHAR *txt = LoadString(AnalyStrID[analysis]);
	
	forecolor = SetTextColor(hdc, forecolor);
	
	TextOutVLen(hdc, xPos, yPos, txt, strlen(txt));

	SetTextColor(hdc, forecolor);
}

static PutRecallFetalMark(HDC hdc, INT32 xPos, UINT8 mark)
{
	INT32 y1, y2, y3;
	PDC pdc = dc_HDC2PDC(hdc);
	GAL_PIXEL forecolor = PIXEL_white;
	GAL_PIXEL backcolor = PIXEL_black;
	
	forecolor = SetBrushColor(hdc, forecolor);
	backcolor = SetBkColor(hdc, PIXEL_transparent);
	
	y1 = 2;
	y2 = RECTH(pdc->DevRC) - 16;
	y3 = 50;
	
	if (mark & 0x01)
		DrawIcon(hdc, xPos, y1, IDI_UPARROW);
	if (mark & 0x02)
		DrawIcon(hdc, xPos, y2, IDI_NM);
	if (mark & 0x04)
		DrawIcon(hdc, xPos, y3, IDI_UPARROW);

	SetBrushColor(hdc, forecolor);
	SetBkColor(hdc, backcolor);
}

static VOID
	DrawFetalRecallFhrWave(HWND hWnd, PFETALDATA data, INT32 index, INT32 len)
{
	int i, loops;
	int ndx, n, m;
	int newPox1, oldPox1 = 0;
	int newPox2, oldPox2 = 0;
	UINT8 event, analysis;
	GAL_PIXEL color1 = PIXEL_magenta;
	GAL_PIXEL color2 = PIXEL_yellow;
	HDC hdc = GetDC(hWnd);
	loops = len;
	// 显示波形
	
	SetPenColor(hdc, PIXEL_red);
	for (i = 0; i < loops; i++)
	{
		ndx = (i * RECALL_PAGE_DATA_NUMBER * FETAL_SAMPLE_RATE + 648 / 2) / 648;
		n = (ndx / FETAL_SAMPLE_RATE) + index;
		m = (ndx & 0x03);
		newPox1 = RecallScaleWave(240, 30, 0, 252, data[n].wave[m].fhr1);
		newPox2 = RecallScaleWave(240, 30, 0, 252, data[n].wave[m].fhr2);
		if (oldPox1 > 0 && oldPox1 < 252)
		{
			if (ABS(newPox1 - oldPox1) < 20)
			{
				SetPenColor(hdc, color1);
				DrawLine(hdc, i-1, oldPox1, i, newPox1);
			}
		}
		oldPox1 = newPox1;
		if (oldPox2 > 0 && oldPox2 < 252)
		{
			SetPenColor(hdc, color2);
			if (ABS(newPox2 - oldPox2) < 30)
				DrawLine(hdc, i-1, oldPox2, i, newPox2);
		}
		oldPox2 = newPox2;
	}
	// 显示事件
	m = 0;
	for (i = 1; i < loops; i++)
	{
		ndx = (i * RECALL_PAGE_DATA_NUMBER * FETAL_SAMPLE_RATE + 648 / 2) / 648;
		n = (ndx / FETAL_SAMPLE_RATE) + index;
		event = 0;
		analysis = 0;
		while (m < n)
		{
			if (data[m].event)
				event = data[m].event;
			if (data[m].event)
				analysis = data[m].analysis;
			m++;
		}
		if (event)
			PutRecallEvent(hdc, i, event);
//		PutRecallAnalysis(hdc, i, analysis);
	}
	ReleaseDC(hdc);
}

static VOID
	DrawFetalRecallTocoWave(HWND hWnd, PFETALDATA data, INT32 index, INT32 len)
{
	int i, j, loops;
	int ndx, n, m;
	int newPox1, oldPox1 = 0;
	int newPox2, oldPox2 = 0;
	UINT8 mark;
	GAL_PIXEL color1 = PIXEL_green;
	GAL_PIXEL color2 = PIXEL_magenta;
	HDC hdc = GetDC(hWnd);
	loops = len;
	// 显示波形
	for (i = 0; i < loops; i++)
	{
		ndx = (i * RECALL_PAGE_DATA_NUMBER * FETAL_SAMPLE_RATE + 648 / 2) / 648;
		n = (ndx / FETAL_SAMPLE_RATE) + index;
		m = (ndx & 0x03);
		newPox1 = RecallScaleWave(100, 0, 0, 122, data[n].wave[m].toco) - 1;
		newPox2 = RecallScaleWave( 40, 0, 5,  45, data[n].wave[m].afm) + 3;
		SetPenColor(hdc, color1);
		if (oldPox1 > 0)
		{
//			if (ABS(newPox1 - oldPox1) < 10)
			{
				DrawLine(hdc, i-1, oldPox1, i, newPox1);
			}
		}
		oldPox1 = newPox1;
		SetPenColor(hdc, color2);
		if (oldPox2 > 0)
		{
//			if (ABS(newPox1 - oldPox1) < 10)
			{
				DrawLine(hdc, i-1, oldPox2, i, newPox2);
			}
		}
		oldPox2 = newPox2;
	}
	// 显示标记
	m = 0;
	for (i = 1; i < loops; i++)
	{
		ndx = (i * RECALL_PAGE_DATA_NUMBER * FETAL_SAMPLE_RATE + 648 / 2) / 648;
		n = (ndx / FETAL_SAMPLE_RATE) + index;
		mark = 0;
		while (m < n)
		{
			if (data[m].wave[0].fmbits || data[m].wave[1].fmbits
				|| data[m].wave[2].fmbits || data[m].wave[3].fmbits )
				mark |= 0x01;
			if (data[m].wave[0].afmbits || data[m].wave[1].afmbits
				|| data[m].wave[2].afmbits || data[m].wave[3].afmbits )
				mark |= 0x04;
			if (data[m].wave[0].zerobits || data[m].wave[1].zerobits
				|| data[m].wave[2].zerobits || data[m].wave[3].zerobits )
				mark |= 0x02;
			m++;
		}
		if (mark)
			PutRecallFetalMark(hdc, i, mark);
	}
	ReleaseDC(hdc);
}

void time2datetime(int t, DATETIME *dt)
{
	struct tm *plocal_time;
	plocal_time = localtime((const time_t *)&t);
	dt->year = plocal_time->tm_year + 1900;
	dt->month = plocal_time->tm_mon + 1;
	dt->day = plocal_time->tm_mday;
	dt->hour = plocal_time->tm_hour;
	dt->minute = plocal_time->tm_min;
	dt->second = plocal_time->tm_sec;
}


static VOID RefreshRecallGraph(HWND hWnd)
{
	HWND hCtrl;
	INT32 index = (INT32)RecallPatientPtr->data.info[0].index;
	INT32 curr  = PageIndex[RecallPage];
	INT32 drLen;
	drLen = (DATA_SAVE_LEN + index - curr) % DATA_SAVE_LEN;
	drLen = drLen * RECALL_PAGE_PIXEL_LEN / RECALL_PAGE_DATA_NUMBER;
	if (drLen > RECALL_PAGE_PIXEL_LEN)
		drLen = RECALL_PAGE_PIXEL_LEN;
	char log[128];
	sprintf(log,"drLen, index, curr...%d, %d, %d\r\n", drLen, index, curr);
	PutSystemLog(log);
	sprintf(log,"PageIndex[%d]:%d\r\n", RecallPage, PageIndex[RecallPage]);
	PutSystemLog(log);
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_FHRGPH_L))
	{
		DrawFetalRecallFhrWave
			(hCtrl, RecallPatientPtr->data.data, PageIndex[RecallPage], drLen);
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_TOCOGPH_L))
	{
		DrawFetalRecallTocoWave
			(hCtrl, RecallPatientPtr->data.data, PageIndex[RecallPage], drLen);
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_TIME_L))
	{
		DATETIME dt;
		time2datetime(RecallPatientPtr->data.data[PageIndex[RecallPage]].time, &dt);
		UCHAR *txt = LoadString(STR_DLG_RECALL_TIME);
		GetTimeStr(&dt, txt);
		SetWindowText(hCtrl, STR_DLG_RECALL_TIME);
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_SCROLL_L))
	{
		DrawScrollH(hCtrl, RecallPage, MaxRecallPage, 1);
	}
}

static VOID ShowPationInfo(HWND hWnd)
{
	const int x = DLG_OFFSET * 2 + 648;
	const int offset = STATIC_HEIGHT;
	int len = (SCREEN_WIDTH - 4 - x - DLG_OFFSET) >> 3;
	HDC hdc = GetDC(hWnd);
	PDC pdc = dc_HDC2PDC(hdc);
	PLOGFONT pFont = pdc->pLogFont;
	GAL_PIXEL textColor = SetTextColor(hdc, PIXEL_black);
	GAL_PIXEL backColor = SetBkColor(hdc, PIXEL_transparent);
	int i, y;
	CHAR txt[len];
	//pdc->pLogFont = GetSystemFont(SYSLOGFONT_WCHAR_DEF);
	pdc->pLogFont = GetSystemFont(SYSLOGFONT_SMAFONT);//phh

	y = DLG_MENU_HIGHT + DLG_OFFSET + 2;
	for (i = 0; i < 5; i++)
	{
		memset(txt, '\0', len);
		if (RUSSIAN == MonitorConfig.language)
		{
            len = (SCREEN_WIDTH - 4 - x - DLG_OFFSET) >> 3;
		    len += RuStringNum(InfoText[i]);
		}
		if (strlen(InfoText[i]) > len - 1)
		{
			strncpy(txt, InfoText[i], len - 4);
			strcat(txt, "...");
		}
		else
		{
			strncpy(txt, InfoText[i], len - 1);
		}
		TextOut(hdc, x, y, txt);
		y += offset;
	}
	SetTextColor(hdc, textColor);
	SetBkColor(hdc, backColor);
	pdc->pLogFont = pFont;
	ReleaseDC(hdc);
}

static VOID FetalRecallShow(HWND hWnd)
{
	printf("点击历史open  dead here UUUUUUUU000\n");
	HWND hCtrl;
	HDC hdc;
	RECT rc;
	int x, y, offset;
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_FHRGPH_L))
	{	printf("UUUUUUUU111\n");
		SetRect(&rc, 0, 0, RecallFhrBmpMem.cx, RecallFhrBmpMem.cy + 1);
		hdc = GetDC(hCtrl);
		FillRectEx(hdc, &rc, RecallFhrBmpMem.cx, RecallFhrBmpMem.data);
		ReleaseDC(hdc);
		printf("UUUUUUUU222\n");
	}
	
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_TOCOGPH_L))
	{	printf("UUUUUUUU333\n");
		SetRect(&rc, 0, 0, RecallTOCOBmpMem.cx, RecallTOCOBmpMem.cy + 1);
		hdc = GetDC(hCtrl);
		FillRectEx(hdc, &rc, RecallTOCOBmpMem.cx, RecallTOCOBmpMem.data);
		ReleaseDC(hdc);
		printf("UUUUUUUU444\n");
	}
	printf("UUUUUUUU5555\n");
	RefreshRecallGraph(hWnd);
		printf("UUUUUUssssssssssUU\n");
}

static VOID DispAnalysis(HDC hdc, PRECT prc, ARET_SAVE *pRet)
{
	INT32 x = DLG_OFFSET;
	INT32 y = DLG_OFFSET;
	INT32 y1;
	UCHAR txt[64];
	RECT rc;
	
	SetTextColor(hdc, GetWindowElementColor (FGC_CONTROL_DEF));
	SetPenColor(hdc, GetWindowElementColor (FGC_CONTROL_DEF));

	y = prc->top + DLG_OFFSET;
	x = prc->left + DLG_OFFSET;

	//适应俄语界面调整
	Rect(hdc, x, y, x + 80 * 5, y + KEY_HEIGHT * 6+KEY_HEIGHT*1.8);
	printf("rrrr(%d,%d)\n",x,y);
	Line(hdc, x, y + KEY_HEIGHT * 1+KEY_HEIGHT*0.3*1, x + 80 * 5, y + KEY_HEIGHT * 1+KEY_HEIGHT*0.3*1);
	Line(hdc, x, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2, x + 80 * 5, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2);
	Line(hdc, x, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3, x + 80 * 5, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3);
	Line(hdc, x, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*4, x + 80 * 5, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*4);
	Line(hdc, x, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*5, x + 80 * 5, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*5);

	Line(hdc, x +  120+70*0, y, x +  120+70*0, y + KEY_HEIGHT * 6+KEY_HEIGHT*1.8);
	Line(hdc, x +  120+70*1, y, x +  120+70*1, y + KEY_HEIGHT * 6+KEY_HEIGHT*1.8);
	Line(hdc, x +  120+70*2, y, x +  120+70*2, y + KEY_HEIGHT * 6+KEY_HEIGHT*1.8);
	Line(hdc, x +  120+70*3, y, x +  120+70*3, y + KEY_HEIGHT * 6+KEY_HEIGHT*1.8);

	SetRect(&rc, x, y , x + 120, y + KEY_HEIGHT);

	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ITEMS));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1+KEY_HEIGHT*0.3*1, x + 120, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*1);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FHR_BASE));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2, x + 120, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*2);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_AMPLITUDE));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3, x + 120, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*3);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FAST_TIME));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*4, x + 120, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*4);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FAST_AMPL));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*5, x + 120, y + KEY_HEIGHT * 6+KEY_HEIGHT*0.3*5);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FM_TIMES));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	
	x += 120;
	SetRect(&rc, x, y , x + 70, y + KEY_HEIGHT);
	sprintf(txt, "0");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1+KEY_HEIGHT*0.3*1, x + 70, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*1);
	sprintf(txt, "<100");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2, x + 70, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*2);
	sprintf(txt, "<5");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3, x + 70, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*3);
	sprintf(txt, "<10");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*4, x + 70, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*4);
	sprintf(txt, "<10");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*5, x + 70, y + KEY_HEIGHT * 6+KEY_HEIGHT*0.3*5);
	sprintf(txt, "0");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));

	
	x += 70;
	SetRect(&rc, x, y , x + 70, y + KEY_HEIGHT);
	sprintf(txt, "1");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x + 4, y + KEY_HEIGHT * 1 + 2+KEY_HEIGHT*0.3*1, x + 70 - 4, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.25*1);
	sprintf(txt, "100-119,>160");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2, x + 70, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*2);
	sprintf(txt, "5-9,>30");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3, x + 70, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*3);
	sprintf(txt, "10-14");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*4, x + 70, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*4);
	sprintf(txt, "10-14");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*5, x + 70, y + KEY_HEIGHT * 6+KEY_HEIGHT*0.3*5);
	sprintf(txt, "1-2");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	
	x += 70;
	SetRect(&rc, x, y , x + 70, y + KEY_HEIGHT);
	sprintf(txt, "2");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1+KEY_HEIGHT*0.3*1, x + 70, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*1);
	sprintf(txt, "120-160");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2, x + 70, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*2);
	sprintf(txt, "10-30");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3, x + 70, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*3);
	sprintf(txt, ">=15");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*4, x + 70, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*4);
	sprintf(txt, ">=15");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*5, x + 70, y + KEY_HEIGHT * 6+KEY_HEIGHT*0.3*5);
	sprintf(txt, ">3");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	x += 70;
	SetRect(&rc, x, y , x + 70, y + KEY_HEIGHT);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_RESULT));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1+KEY_HEIGHT*0.3*1, x + 70, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*1);
	if (pRet->fhr_JX)
		sprintf(txt, "%d", pRet->fhr_JX);
	else
		strcpy(txt, "--");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2, x + 70, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*2);
	if (pRet->fhr_ZV)
		sprintf(txt, "%d", pRet->fhr_ZV);
	else
		strcpy(txt, "--");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3, x + 70, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*3);
	if (pRet->fasttime)
		sprintf(txt, "%d", pRet->fasttime);
	else
		strcpy(txt, "--");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*4, x + 70, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*4);
	if (pRet->fasthigh)
		sprintf(txt, "%d", pRet->fasthigh);
	else
		strcpy(txt, "--");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*5, x + 70, y + KEY_HEIGHT * 6+KEY_HEIGHT*0.3*5);
	if (pRet->fm_nr)
		sprintf(txt, "%d", pRet->fm_nr);
	else
		strcpy(txt, "--");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	
	x += 88;
	y1 = y + 8;
	y += KEY_HEIGHT * 6 + DLG_OFFSET;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_NAME));
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	sprintf(txt, "%s %d:%02d", LoadString(STR_DLG_ANLS_TIME),
		pRet->second / 60, pRet->second % 60);
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	sprintf(txt, "%s   %d%%", LoadString(STR_DLG_ANLS_VALID), pRet->vld_pct);
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	
	struct tm *plocal_time;
	UINT32 time = pRet->endtime - pRet->second;
	plocal_time = localtime((const time_t *)&time);
	sprintf(txt, "%s: %02d:%02d:%02d", LoadString(STR_PRINT_TIME_START), 
		plocal_time->tm_hour, plocal_time->tm_min, plocal_time->tm_sec);
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	
	plocal_time = localtime((const time_t *)&(pRet->endtime));
	sprintf(txt, "%s: %02d:%02d:%02d", LoadString(STR_PRINT_TIME_END), 
		plocal_time->tm_hour, plocal_time->tm_min, plocal_time->tm_sec);
	TextOut(hdc, x, y1, txt);
	
}
//fischer评分方法 @vinyin 2015-05-04
static VOID DispAnalysisFischer(HDC hdc, PRECT prc, ARET_SAVE *pRet)
{
	INT32 x = prc->left + DLG_OFFSET;
	INT32 y = prc->top + DLG_OFFSET;
	INT32 y1;
	UCHAR txt[64];
	RECT rc;
	
	SetTextColor(hdc, GetWindowElementColor (FGC_CONTROL_DEF));
	SetPenColor(hdc, GetWindowElementColor (FGC_CONTROL_DEF));
	//
	const UCHAR width = 90;
	const UCHAR deltaWidth = 83;
	Rect(hdc, x, y, x + width * 5 + 2, y + KEY_HEIGHT * 6+KEY_HEIGHT*1.8);
	
	Line(hdc, x, y + KEY_HEIGHT * 1+KEY_HEIGHT*0.3*1, x + width * 5, y + KEY_HEIGHT * 1+KEY_HEIGHT*0.3*1);
	Line(hdc, x, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2, x + width * 5, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2);
	Line(hdc, x, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3, x + width * 5, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3);
	Line(hdc, x, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*4, x + width * 5, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*4);
	Line(hdc, x, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*5, x + width * 5, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*5);

	Line(hdc, x +  120+deltaWidth*0, y, x +  120+deltaWidth*0, y + KEY_HEIGHT * 6+KEY_HEIGHT*1.8);
	Line(hdc, x +  120+deltaWidth*1, y, x +  120+deltaWidth*1, y + KEY_HEIGHT * 6+KEY_HEIGHT*1.8);
	Line(hdc, x +  120+deltaWidth*2, y, x +  120+deltaWidth*2, y + KEY_HEIGHT * 6+KEY_HEIGHT*1.8);
	Line(hdc, x +  120+deltaWidth*3, y, x +  120+deltaWidth*3, y + KEY_HEIGHT * 6+KEY_HEIGHT*1.8);
	//从上到下是 项目 胎心率基线 振幅变异 周期变异  加速 减速
	SetRect(&rc, x, y , x + 120, y + KEY_HEIGHT);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ITEMS));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1+KEY_HEIGHT*0.3*1, x + 120, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*1);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_BASE_LINE));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	int count = 0;
	printf("count=%d ,str = %s \n",count++,txt);
	SetRect(&rc, x, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2, x + 120, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*2);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_AMPLITUDE_VAR));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	printf("count=%d ,str = %s \n",count++,txt);
	SetRect(&rc, x, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3, x + 120, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*3);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_PERIOD_VAR));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	printf("count=%d ,str = %s \n",count++,txt);
	SetRect(&rc, x, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*4, x + 120, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*4);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ACCELRATION));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	printf("count=%d ,str = %s \n",count++,txt);
	SetRect(&rc, x, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*5, x + 120, y + KEY_HEIGHT * 6+KEY_HEIGHT*0.3*5);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_SLOWDOWN));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//从上到下是 0分  <100,>180   <5   <2   无   LD,>=8
	x += 120;
	SetRect(&rc, x, y , x + deltaWidth, y + KEY_HEIGHT);
	sprintf(txt, "0");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1+KEY_HEIGHT*0.3*1, x + deltaWidth, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*1);
	sprintf(txt, "<100,>180");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2, x + deltaWidth, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*2);
	sprintf(txt, "<5");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3, x + deltaWidth, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*3);
	sprintf(txt, "<2");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*4, x + deltaWidth, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*4);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ACCELRATION_TYPE0));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*5, x + deltaWidth, y + KEY_HEIGHT * 6+KEY_HEIGHT*0.3*5);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_SLOWDOWN_TYPE0));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//从上到下是 1分  100~119\n161~180   5~9,>30   2~6  1~4 4~7,VD 
	x += deltaWidth;
	SetRect(&rc, x, y , x + deltaWidth, y + KEY_HEIGHT);
	sprintf(txt, "1");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x + 4, y + KEY_HEIGHT * 1 + 2+KEY_HEIGHT*0.3*1, x + deltaWidth - 4, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.25*1);
	sprintf(txt, "100~119 161~180");
	printf("count=%d kkkkkkkkkkkkkkkkkkkkkkkkkkk,str = %s \n",count++,txt);
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2, x + deltaWidth, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*2);
	sprintf(txt, " 5~9,>30");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3, x + deltaWidth, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*3);
	sprintf(txt, "2~6");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*4, x + deltaWidth, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*4);
	sprintf(txt, "1~4");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*5, x + deltaWidth, y + KEY_HEIGHT * 6+KEY_HEIGHT*0.3*5);
	sprintf(txt, "4~7,VD");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//从上到下是 2分  120~160   10~30   >6  >4 无,其他
	x += deltaWidth;
	SetRect(&rc, x, y , x + deltaWidth, y + KEY_HEIGHT);
	sprintf(txt, "2");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1+KEY_HEIGHT*0.3*1, x + deltaWidth, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*1);
	sprintf(txt, "120-160");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2, x + deltaWidth, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*2);
	sprintf(txt, "10-30");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3, x + deltaWidth, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*3);
	sprintf(txt, ">6");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*4, x + deltaWidth, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*4);
	sprintf(txt, ">4");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*5, x + deltaWidth, y + KEY_HEIGHT * 6+KEY_HEIGHT*0.3*5);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_SLOWDOWN_TYPE2));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//从上到下是 本例结果  实际的分数1 分数2 分数3 分数4 分数5
	x += deltaWidth;
	SetRect(&rc, x, y , x + deltaWidth, y + KEY_HEIGHT);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_RESULT));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//心率基线
	SetRect(&rc, x, y + KEY_HEIGHT * 1+KEY_HEIGHT*0.3*1, x + deltaWidth, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*1);
	if (pRet->fhr_JX)
		sprintf(txt, "%d", pRet->fhr_JX);
	else
		strcpy(txt, "--");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//振幅变异
	SetRect(&rc, x, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2, x + deltaWidth, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*2);
	if (pRet->fhr_ZV)
		sprintf(txt, "%d", pRet->fhr_ZV);
	else
		strcpy(txt, "--");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//周期变异
	SetRect(&rc, x, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3, x + deltaWidth, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*3);
	if (pRet->fhr_QV)
		sprintf(txt, "%d", pRet->fhr_QV);
	else
		strcpy(txt, "--");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//加速
	SetRect(&rc, x, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*4, x + deltaWidth, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*4);
	sprintf(txt, "%d", pRet->tdfast);
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//减速
	SetRect(&rc, x, y + KEY_HEIGHT * 5+KEY_HEIGHT*0.3*5, x + deltaWidth, y + KEY_HEIGHT * 6+KEY_HEIGHT*0.3*5);
	sprintf(txt, "%d", pRet->tdslow);
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//从上到下是 FISCHER评分方法 监测时间 有效数据 开始时间 结束时间
	x += 88;
	y1 = y + 8;
	y += KEY_HEIGHT * 6 + DLG_OFFSET;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FISCHER));
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	sprintf(txt, "%s %d:%02d", LoadString(STR_DLG_ANLS_TIME),
		pRet->second / 60, pRet->second % 60);
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	sprintf(txt, "%s   %d%%", LoadString(STR_DLG_ANLS_VALID), pRet->vld_pct);
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	
	struct tm *plocal_time;
	UINT32 time = pRet->endtime - pRet->second;
	plocal_time = localtime((const time_t *)&time);
	sprintf(txt, "%s: %02d:%02d:%02d", LoadString(STR_PRINT_TIME_START), 
		plocal_time->tm_hour, plocal_time->tm_min, plocal_time->tm_sec);
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	
	plocal_time = localtime((const time_t *)&(pRet->endtime));
	sprintf(txt, "%s: %02d:%02d:%02d", LoadString(STR_PRINT_TIME_END), 
		plocal_time->tm_hour, plocal_time->tm_min, plocal_time->tm_sec);
	TextOut(hdc, x, y1, txt);
	
}


//Krebs评分方法 @vinyin 2015-05-05
static VOID DispAnalysisKrebs(HDC hdc, PRECT prc, ARET_SAVE *pRet)
{
	INT32 x = prc->left + DLG_OFFSET;
	INT32 y = prc->top + DLG_OFFSET/2;
	INT32 y1;
	UCHAR txt[64];
	RECT rc;
	SetTextColor(hdc, GetWindowElementColor (FGC_CONTROL_DEF));
	SetPenColor(hdc, GetWindowElementColor (FGC_CONTROL_DEF));
	//
	const UCHAR width = 90;
	const UCHAR deltaWidth = 83;
	Rect(hdc, x, y, x + width * 5 + 2, y + KEY_HEIGHT * 8.4);
	
	Line(hdc, x, y + KEY_HEIGHT * 1.2*1, x + width * 5, y + KEY_HEIGHT * 1.2*1);
	Line(hdc, x, y + KEY_HEIGHT * 1.2*2, x + width * 5, y + KEY_HEIGHT * 1.2*2);
	Line(hdc, x, y + KEY_HEIGHT * 1.2*3, x + width * 5, y + KEY_HEIGHT * 1.2*3);
	Line(hdc, x, y + KEY_HEIGHT * 1.2*4, x + width * 5, y + KEY_HEIGHT * 1.2*4);
	Line(hdc, x, y + KEY_HEIGHT * 1.2*5, x + width * 5, y + KEY_HEIGHT * 1.2*5);
	Line(hdc, x, y + KEY_HEIGHT * 1.2*6, x + width * 5, y + KEY_HEIGHT * 1.2*6);

	Line(hdc, x +  120+deltaWidth*0, y, x +  120+deltaWidth*0, y + KEY_HEIGHT * 8.4);
	Line(hdc, x +  120+deltaWidth*1, y, x +  120+deltaWidth*1, y + KEY_HEIGHT * 8.4);
	Line(hdc, x +  120+deltaWidth*2, y, x +  120+deltaWidth*2, y + KEY_HEIGHT * 8.4);
	Line(hdc, x +  120+deltaWidth*3, y, x +  120+deltaWidth*3, y + KEY_HEIGHT *8.4);
	//从上到下是 项目 心率基线 振幅变异 周期变异 加速 减速 胎动 
	SetRect(&rc, x, y+10 , x + 120, y + KEY_HEIGHT);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ITEMS));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.2 + 5, x + 120, y + KEY_HEIGHT * 2.2);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FHR_BASE));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2.4+5, x + 120, y + KEY_HEIGHT *3.4);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_AMPLITUDE_VAR));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	
	SetRect(&rc, x, y + KEY_HEIGHT * 3.6+5, x + 120, y + KEY_HEIGHT * 4.6);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_PERIOD_VAR));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	
	SetRect(&rc, x, y + KEY_HEIGHT * 4.8+5, x + 120, y + KEY_HEIGHT * 5.8);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ACCELRATION));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	
	SetRect(&rc, x, y + KEY_HEIGHT *6.0+5, x + 120, y + KEY_HEIGHT * 7);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_SLOWDOWN));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));

	SetRect(&rc, x, y + KEY_HEIGHT * 7.2+5, x + 120, y + KEY_HEIGHT * 8.2);
	sprintf(txt, "%s",LoadString(STR_DLG_ANLS_FETALMOVIE));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//从上到下是 0分  <100,>180   <5   <3  无 >=2  0   
	x += 120;
	SetRect(&rc, x, y , x + deltaWidth, y + KEY_HEIGHT);
	sprintf(txt, "0");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1+KEY_HEIGHT*0.3*1, x + deltaWidth, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*1);
	sprintf(txt, "<100,>180");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2, x + deltaWidth, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*2);
	sprintf(txt, "<5");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3, x + deltaWidth, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*3);
	sprintf(txt, "<3");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 4.8+5, x + deltaWidth, y + KEY_HEIGHT * 5.8);
	sprintf(txt, "%s",LoadString(STR_DLG_ANLS_NOTHING));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT *6.0+5, x + deltaWidth, y + KEY_HEIGHT *7);
	sprintf(txt, "%s", ">=2");//LoadString());
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));

	SetRect(&rc, x, y + KEY_HEIGHT * 7.2+5, x + deltaWidth, y + KEY_HEIGHT * 8.2);
	sprintf(txt, "%s", "0");//LoadString());
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//从上到下是 1分  100~119,161~180 5~9,>25 3~6 1~4 1 1~4
	x += deltaWidth;
	SetRect(&rc, x, y , x + deltaWidth, y + KEY_HEIGHT);
	sprintf(txt, "1");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x + 4, y + KEY_HEIGHT * 1 + 2+KEY_HEIGHT*0.3*1, x + deltaWidth - 4, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.25*1);
	sprintf(txt, "100~119,161~180");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2, x + deltaWidth, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*2);
	sprintf(txt, "5~9,>25");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3, x + deltaWidth, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*3);
	sprintf(txt, "3~6");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 4.8+5, x + deltaWidth, y + KEY_HEIGHT * 5.8);
	sprintf(txt, "1~4");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x,y + KEY_HEIGHT *6.0+5, x + deltaWidth, y + KEY_HEIGHT *7);
	sprintf(txt, "%s", "1");//LoadString());
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 7.2+5, x + deltaWidth, y + KEY_HEIGHT * 8.2);
	sprintf(txt, "%s", "1~4");//LoadString());
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//从上到下是 2分  <20   >11   >24  >3  无减速或1个减速 
	x += deltaWidth;
	SetRect(&rc, x, y , x + deltaWidth, y + KEY_HEIGHT);
	sprintf(txt, "2");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1+KEY_HEIGHT*0.3*1, x + deltaWidth, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*1);
	sprintf(txt, "120~160");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2, x + deltaWidth, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*2);
	sprintf(txt, "10~25");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3, x + deltaWidth, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*3);
	sprintf(txt, ">6");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 4.8+5, x + deltaWidth, y + KEY_HEIGHT * 5.8);
	sprintf(txt, "%s", ">4");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT *6.0+5, x + deltaWidth, y + KEY_HEIGHT *7);
	sprintf(txt, "%s",LoadString(STR_DLG_ANLS_NOTHINGORED));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 7.2+5, x + deltaWidth,y + KEY_HEIGHT * 8.2);
	sprintf(txt, "%s", ">4");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//从上到下是 本例结果  结果1 结果2 结果3 结果4 结果5
	x += deltaWidth;
	SetRect(&rc, x, y , x + deltaWidth, y + KEY_HEIGHT);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_RESULT));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//基线
	SetRect(&rc, x, y + KEY_HEIGHT * 1+KEY_HEIGHT*0.3*1, x + deltaWidth, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*1);
	if (pRet->fhr_JX)
		sprintf(txt, "%d", pRet->fhr_JX);
	else
		strcpy(txt, "--");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//振幅
	SetRect(&rc, x, y + KEY_HEIGHT * 2+KEY_HEIGHT*0.3*2, x + deltaWidth, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*2);
	if (pRet->fhr_ZV)
		sprintf(txt, "%d", pRet->fhr_ZV);
	else
		strcpy(txt, "--");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//周期
	SetRect(&rc, x, y + KEY_HEIGHT * 3+KEY_HEIGHT*0.3*3, x + deltaWidth, y + KEY_HEIGHT * 4+KEY_HEIGHT*0.3*3);
	if (pRet->fhr_QV)
		sprintf(txt, "%d", pRet->fhr_QV);
	else
		strcpy(txt, "--");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//加速
	SetRect(&rc, x, y + KEY_HEIGHT * 4.8+5, x + deltaWidth, y + KEY_HEIGHT * 5.8);
	sprintf(txt, "%d", pRet->tdfast);
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//减速
	SetRect(&rc, x, y + KEY_HEIGHT * 6.0+5, x + deltaWidth, y + KEY_HEIGHT * 7);
	sprintf(txt, "%d", pRet->tdslow);
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//胎动
	SetRect(&rc, x, y + KEY_HEIGHT * 7.2+5, x + deltaWidth, y + KEY_HEIGHT * 8.2);
	sprintf(txt, "%d", pRet->fm_nr);
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//从上到下是 Krebs评分方法 监测时间 有效数据 开始时间 结束时间
	x += 88;
	y1 = y + 8;
	y += KEY_HEIGHT * 6 + DLG_OFFSET;
	sprintf(txt, "%s",LoadString(STR_DLG_ANLS_KREBS));
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	sprintf(txt, "%s %d:%02d", LoadString(STR_DLG_ANLS_TIME),
		pRet->second / 60, pRet->second % 60);
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	sprintf(txt, "%s   %d%%", LoadString(STR_DLG_ANLS_VALID), pRet->vld_pct);
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	
	struct tm *plocal_time;
	UINT32 time = pRet->endtime - pRet->second;
	plocal_time = localtime((const time_t *)&time);
	sprintf(txt, "%s: %02d:%02d:%02d", LoadString(STR_PRINT_TIME_START), 
		plocal_time->tm_hour, plocal_time->tm_min, plocal_time->tm_sec);
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	
	plocal_time = localtime((const time_t *)&(pRet->endtime));
	sprintf(txt, "%s: %02d:%02d:%02d", LoadString(STR_PRINT_TIME_END), 
		plocal_time->tm_hour, plocal_time->tm_min, plocal_time->tm_sec);
	TextOut(hdc, x, y1, txt);
}
//cst评分方法 @vinyin 2015-05-05
static VOID DispAnalysisCST(HDC hdc, PRECT prc, ARET_SAVE *pRet)
{
	INT32 x = prc->left + DLG_OFFSET;
	INT32 y = prc->top + DLG_OFFSET;
	INT32 y1;
	UCHAR txt[64];
	RECT rc;
	SetTextColor(hdc, GetWindowElementColor (FGC_CONTROL_DEF));
	SetPenColor(hdc, GetWindowElementColor (FGC_CONTROL_DEF));
	//
	const UCHAR width = 90;
	const UCHAR deltaWidth = 83;
	Rect(hdc, x, y, x + width * 5 + 2, y + KEY_HEIGHT * 8);

	Line(hdc, x, y + KEY_HEIGHT * 1.33, x + width * 5, y + KEY_HEIGHT * 1.33);
	Line(hdc, x, y + KEY_HEIGHT * 1.33 * 2, x + width * 5, y + KEY_HEIGHT * 1.33 * 2);
	Line(hdc, x, y + KEY_HEIGHT * 1.33 * 3, x + width * 5, y + KEY_HEIGHT * 1.33 * 3);
	Line(hdc, x, y + KEY_HEIGHT * 1.33 * 4, x + width * 5, y + KEY_HEIGHT * 1.33 * 4);
	Line(hdc, x, y + KEY_HEIGHT * 1.33 * 5, x + width * 5, y + KEY_HEIGHT * 1.33 * 5);

	Line(hdc, x +  120+deltaWidth*0, y, x +  120+deltaWidth*0, y + KEY_HEIGHT * 8);
	Line(hdc, x +  120+deltaWidth*1, y, x +  120+deltaWidth*1, y + KEY_HEIGHT * 8);
	Line(hdc, x +  120+deltaWidth*2, y, x +  120+deltaWidth*2, y + KEY_HEIGHT * 8);
	Line(hdc, x +  120+deltaWidth*3, y, x +  120+deltaWidth*3, y + KEY_HEIGHT * 8);
	//从上到下是 项目 胎心基线 振幅摆动 频率摆动 加速 减速 
	SetRect(&rc, x, y , x + 120, y + KEY_HEIGHT* 1.33);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ITEMS));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33+10, x + 120, KEY_HEIGHT * 1.33*2);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FHR_BASE));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*2, x + 120, y + KEY_HEIGHT * 1.33*3);
	sprintf(txt, "%s",LoadString(STR_DLG_ANLS_AMPLITUDE_VAR));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*3, x + 120, y + KEY_HEIGHT * 1.33*4);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_PERIOD_VAR));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*4, x + 120, y + KEY_HEIGHT * 1.33*5);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ACCELRATION));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*5, x + 120, y + KEY_HEIGHT * 1.33*6);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_SLOWDOWN));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//从上到下是 0分 >100,<180 <5 <2 无 晚期+其它
	x += 120;
	SetRect(&rc, x, y , x + deltaWidth, y + KEY_HEIGHT* 1.33);
	sprintf(txt, "%s", "0");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33+10, x + deltaWidth, KEY_HEIGHT * 1.33*2);
	sprintf(txt, "%s", "<100,>180");//LoadString("胎心节律稳定性"));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*2, x + deltaWidth, y + KEY_HEIGHT * 1.33*3);
	sprintf(txt, "%s","<5");// LoadString("小时加速次数"));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*3, x + deltaWidth, y + KEY_HEIGHT * 1.33*4);
	sprintf(txt, "%s", "<2");//LoadString(STR_DLG_ANLS_PERIOD_VAR));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*4, x + deltaWidth, y + KEY_HEIGHT * 1.33*5);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_NOTHING));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*5, x + deltaWidth, y + KEY_HEIGHT * 1.33*6);
	sprintf(txt, "%s",LoadString(STR_DLG_ANLS_LDOROTHER));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//从上到下是 1分 100~119,161~180
	x += deltaWidth;
	SetRect(&rc, x, y , x + deltaWidth, y + KEY_HEIGHT* 1.33);
	sprintf(txt, "%s", "1");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33+10, x + deltaWidth, KEY_HEIGHT * 1.33*2);
	sprintf(txt, "%s", "100~119,161~180");//LoadString("胎心节律稳定性"));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*2, x + deltaWidth, y + KEY_HEIGHT * 1.33*3);
	sprintf(txt, "%s","5~9,>25");// LoadString("小时加速次数"));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*3, x + deltaWidth, y + KEY_HEIGHT * 1.33*4);
	sprintf(txt, "%s", "2~6");//LoadString(STR_DLG_ANLS_PERIOD_VAR));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*4, x + deltaWidth, y + KEY_HEIGHT * 1.33*5);
	sprintf(txt, "%s",LoadString(STR_DLG_ANLS_ACCELRATION_TYPE1));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*5, x + deltaWidth, y + KEY_HEIGHT * 1.33*6);
	sprintf(txt, "%s",LoadString(STR_DLG_ANLS_CHANGE));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//从上到下是 2分 120~160 
	x += deltaWidth;
	SetRect(&rc, x, y , x + deltaWidth, y + KEY_HEIGHT* 1.33);
	sprintf(txt, "%s", "2");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33+10, x + deltaWidth, KEY_HEIGHT * 1.33*2);
	sprintf(txt, "%s", "120~160");//LoadString("胎心节律稳定性"));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*2, x + deltaWidth, y + KEY_HEIGHT * 1.33*3);
	sprintf(txt, "%s","10~25");// LoadString("小时加速次数"));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*3, x + deltaWidth, y + KEY_HEIGHT * 1.33*4);
	sprintf(txt, "%s", ">6");//LoadString(STR_DLG_ANLS_PERIOD_VAR));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*4, x + deltaWidth, y + KEY_HEIGHT * 1.33*5);
	sprintf(txt, "%s",LoadString(STR_DLG_ANLS_ACCELRATION_TYPE2));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*5, x + deltaWidth, y + KEY_HEIGHT * 1.33*6);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_NOTHING));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//从上到下是 本例结果 结果1 结果2 结果3
	x += deltaWidth;
	SetRect(&rc, x, y , x + deltaWidth, y + KEY_HEIGHT* 1.33);
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_RESULT));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33+10, x + deltaWidth, KEY_HEIGHT * 1.33*2);
	if (pRet->fhr_JX)
		sprintf(txt, "%d", pRet->fhr_JX);
	else
		strcpy(txt, "--");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//振幅
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*2, x + deltaWidth, y + KEY_HEIGHT * 1.33*3);
	if (pRet->fhr_ZV)
		sprintf(txt, "%d", pRet->fhr_ZV);
	else
		strcpy(txt, "--");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//周期
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*3, x + deltaWidth, y + KEY_HEIGHT * 1.33*4);
	if (pRet->fhr_QV)
		sprintf(txt, "%d", pRet->fhr_QV);
	else
		strcpy(txt, "--");
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//加速
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*4, x + deltaWidth, y + KEY_HEIGHT * 1.33*5);
	if (pRet->tdfast)//
		if(pRet->fastType == 1)//周期性
			sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ACCELRATION_TYPE1));
		else if(pRet->fastType == 2)//散在性
			sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ACCELRATION_TYPE2));
		else
			strcpy(txt, "--");
	else
		sprintf(txt, "%s", LoadString(STR_DLG_ANLS_NOTHING));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	//减速
	SetRect(&rc, x, y + KEY_HEIGHT * 1.33*5, x + deltaWidth, y + KEY_HEIGHT * 1.33*6);
	if (pRet->tdslow)
		if(pRet->slowType == 1)//晚期减速
			sprintf(txt, "%s", LoadString(STR_DLG_ANLS_LASTSLOW));
		else if(pRet->slowType == 2)//早期减速
			sprintf(txt, "%s", LoadString(STR_DLG_ANLS_EDSLOW));
		else if(pRet->slowType == 3)//变异
			sprintf(txt, "%s", LoadString(STR_DLG_ANLS_CHANGE));
		else
			strcpy(txt, "--");
	else
		sprintf(txt, "%s", LoadString(STR_DLG_ANLS_NOTHING));
	TextOutCenterLen(hdc, &rc, txt, strlen(txt));
	
	//从上到下是 CST评分方法 监测时间 有效数据 开始时间 结束时间
	x += 88;
	y1 = y + 8;
	y += KEY_HEIGHT * 6 + DLG_OFFSET;
	sprintf(txt, "%s","CST评分方法");// LoadString(STR_DLG_ANLS_FISCHER));
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	sprintf(txt, "%s %d:%02d", LoadString(STR_DLG_ANLS_TIME),
		pRet->second / 60, pRet->second % 60);
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	sprintf(txt, "%s   %d%%", LoadString(STR_DLG_ANLS_VALID), pRet->vld_pct);
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	
	struct tm *plocal_time;
	UINT32 time = pRet->endtime - pRet->second;
	plocal_time = localtime((const time_t *)&time);
	sprintf(txt, "%s: %02d:%02d:%02d", LoadString(STR_PRINT_TIME_START), 
		plocal_time->tm_hour, plocal_time->tm_min, plocal_time->tm_sec);
	TextOut(hdc, x, y1, txt);
	y1 += STATIC_HEIGHT;
	
	plocal_time = localtime((const time_t *)&(pRet->endtime));
	sprintf(txt, "%s: %02d:%02d:%02d", LoadString(STR_PRINT_TIME_END), 
		plocal_time->tm_hour, plocal_time->tm_min, plocal_time->tm_sec);
	TextOut(hdc, x, y1, txt);
	
}

static VOID DispPationAnalysis(HDC hdc, PRECT prc, ARET_SAVE *pRet)
{
	GAL_PIXEL brushColor = 
		SetBrushColor(hdc, GetWindowElementColor(WEC_EXCOLOR_BEIGE));
	GAL_PIXEL textColor = SetTextColor(hdc, PIXEL_black);
	GAL_PIXEL penColor = SetPenColor(hdc, PIXEL_black);
	GAL_PIXEL backColor =
		SetBkColor(hdc, GetWindowElementColor(WEC_EXCOLOR_BEIGE));
	
	RECT rcOut =
		{ prc->left + 8, prc->top + 8, prc->right - 8, prc->bottom - 8 };
	PDC pdc = dc_HDC2PDC(hdc);
	PLOGFONT pFont = pdc->pLogFont;
	INT32 y = rcOut.top;
	INT32 offset;
	INT32 i;

	FillRect(hdc, prc->left, prc->top, RECTWP(prc) - 1, RECTHP(prc) - 1);
	Rect(hdc,prc->left + 3,prc->top + 3, prc->right - 4, prc->bottom - 4);
	Rect(hdc,prc->left + 1,prc->top + 1, prc->right - 2, prc->bottom - 2);

	//pdc->pLogFont = GetSystemFont(SYSLOGFONT_WCHAR_DEF);//phh
	pdc->pLogFont = GetSystemFont(SYSLOGFONT_SMAFONT);//phh
	
	enum {
		NST_SHOW_ANALYSIS = 1,//默认用nst评分--
		FISCHER_SHOW_ANALYSIS,//fischer评分方法
		KREBS_SHOW_ANALYSIS,//Krebs评分
		CST_SHOW_ANALYSIS,//cst评分
		
	};
	switch (FhrConfig.defaultAnalyType)
	{
		case NST_SHOW_ANALYSIS:
			DispAnalysis(hdc, prc, pRet);
		break;
		case FISCHER_SHOW_ANALYSIS:
			DispAnalysisFischer(hdc, prc, pRet);
		break;
		case KREBS_SHOW_ANALYSIS:
			DispAnalysisKrebs(hdc, prc, pRet);
		break;
		case CST_SHOW_ANALYSIS:
			DispAnalysisCST(hdc, prc, pRet);
		break;
		default:
		break;
	}
	// 恢复现场
	pdc->pLogFont = pFont;
	SetBrushColor(hdc, brushColor);
	SetTextColor(hdc, textColor);
	SetPenColor(hdc, penColor);
	SetBkColor(hdc, backColor);
}

static VOID DispPationInfo(HDC hdc, PRECT prc, PPTNINFO pinfo)
{
	GAL_PIXEL brushColor = 
		SetBrushColor(hdc, GetWindowElementColor(WEC_EXCOLOR_BEIGE));
	GAL_PIXEL textColor = SetTextColor(hdc, PIXEL_black);
	GAL_PIXEL penColor = SetPenColor(hdc, PIXEL_black);
	GAL_PIXEL backColor =
		SetBkColor(hdc, GetWindowElementColor(WEC_EXCOLOR_BEIGE));
	
	RECT rcOut =
		{ prc->left + 8, prc->top + 8, prc->right - 8, prc->bottom - 8 };
	PDC pdc = dc_HDC2PDC(hdc);
	PLOGFONT pFont = pdc->pLogFont;
	INT32 y = rcOut.top;
	INT32 offset;
	INT32 i;

	FillRect(hdc, prc->left, prc->top, RECTWP(prc) - 1, RECTHP(prc) - 1);
	Rect(hdc,prc->left + 3,prc->top + 3, prc->right - 4, prc->bottom - 4);
	Rect(hdc,prc->left + 1,prc->top + 1, prc->right - 2, prc->bottom - 2);

	//pdc->pLogFont = GetSystemFont(SYSLOGFONT_WCHAR_DEF);
	pdc->pLogFont = GetSystemFont(SYSLOGFONT_SMAFONT);//phh

	offset = pdc->pLogFont->size + (pdc->pLogFont->size >> 2);
	for (i = 0; i < 8/*TABLESIZE(InfoText)*/; i++)
	{
		TextOut(hdc, rcOut.left, y, InfoText[i]);
		y += offset;
	}
	SetRect(&rcOut, rcOut.left, y, rcOut.right, rcOut.bottom);
	TextOutWrap(hdc, &rcOut, pinfo->note, -1);
	
	// 恢复现场
	pdc->pLogFont = pFont;
	SetBrushColor(hdc, brushColor);
	SetTextColor(hdc, textColor);
	SetPenColor(hdc, penColor);
	SetBkColor(hdc, backColor);
}

static VOID ShowPatientAnalysis(HWND hWnd, int show)
{
	RECT rc = { 20, 0, WAVE_WIDTH + DLG_OFFSET, 210+55 };//by panhonghui
	RECT rcWin;
	HDC hdc = GetDC(hWnd);
	HWND hCtrl;
	PCONTROL pCtrl;
	INT32 i;
//	prinfo("RecallPatientPtr->ansis.len:%d\n", RecallPatientPtr->ansis.len);
	if (NULL == RecallAnalyGphMem.data)
	{
		PFBMEM  this = &FbMem;
		this->SetMenory(this, &RecallAnalyGphMem);
		this->New(this, RECTW(rc) + 1, RECTH(rc) + 1, 16);
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_ANALY_B))
	{
		INT32 y = 0;
		i = 0;
		ClientToScreen(hCtrl, &i, &y);
		i = (y * 2 - RECTH(rc)) >> 1;
		rc.top += i;
		rc.bottom += i;
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_INFO_B))
	{
		EnableWindow(hCtrl, !show);
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_PAGEUP_B))
	{
		EnableWindow(hCtrl, !show);
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_PAGEDN_B))
	{
		EnableWindow(hCtrl, !show);
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_PRINTPAGE_B))
	{
		//EnableWindow(hCtrl, !show && (RecallPatientPtr->ansis.len > 0));
	//	EnableWindow(hCtrl, FALSE); //去掉评分打印
		EnableWindow(hCtrl, !show);
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_PRINTALL_B))
	{
		EnableWindow(hCtrl, !show);
	}
	if (show == FALSE)
	{
		if (RecallAnalyGphMem.data)
		{
			int iLine;
			UCHAR *pp;
			pp = RecallAnalyGphMem.data;
			iLine = RecallAnalyGphMem.cx * RecallAnalyGphMem.bits >> 3;
			for (i = 0; i < RecallAnalyGphMem.cy; i++)
			{
				pp = RecallAnalyGphMem.data + i * iLine;
				fb_putlinemem(((PWIN)hWnd)->fblayer, rc.left, rc.top +i,
								RecallAnalyGphMem.cx, pp);
			}
		}
//			FillRectEx(hdc, &rc, RecallInfoGphMem.cx, RecallInfoGphMem.data);
	}
	else
	{
		fb_getmem(rc.left, rc.top,RecallAnalyGphMem.cx, RecallAnalyGphMem.cy, RecallAnalyGphMem.data);
		DispPationAnalysis(hdc, (PRECT)&rc,
			(ARET_SAVE*)(RecallPatientPtr->ansis.buffer));
	}
	ReleaseDC(hdc);
}

static VOID ShowPatientInformation(HWND hWnd, int show)
{
	RECT rc = 
	{
		350,
		0,
		WAVE_WIDTH + DLG_OFFSET,
		252
	};
	HDC hdc = GetDC(hWnd);
	HWND hCtrl;
	INT32 i;
	
	if (NULL == RecallInfoGphMem.data)
	{
		PFBMEM  this = &FbMem;
		this->SetMenory(this, &RecallInfoGphMem);
		this->New(this, RECTW(rc) + 1, RECTH(rc) + 1, 16);
	}

	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_ANALY_B))
	{
		EnableWindow(hCtrl, !show && (RecallPatientPtr->ansis.len > 0));
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_INFO_B))
	{
		INT32 y = 0;
		i = 0;
		ClientToScreen(hCtrl, &i, &y);
		i = (y * 2 - RECTH(rc)) >> 1;
		rc.top += i;
		rc.bottom += i;
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_PAGEUP_B))
	{
		EnableWindow(hCtrl, !show);
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_PAGEDN_B))
	{
		EnableWindow(hCtrl, !show);
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_PRINTPAGE_B))
	{
		EnableWindow(hCtrl, !show && (RecallPatientPtr->ansis.len > 0));
		//EnableWindow(hCtrl, FALSE); //去掉评分打印
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_PRINTALL_B))
	{
		EnableWindow(hCtrl, !show);
	}
	if (show == TRUE)
	{
		fb_getmem(rc.left, rc.top,
			RecallInfoGphMem.cx, RecallInfoGphMem.cy, RecallInfoGphMem.data);
		DispPationInfo(hdc, (PRECT)&rc, &(RecallPatientPtr->info));
	}
	if (show == FALSE)
	{
		if (RecallInfoGphMem.data)
		{
			int iLine;
			UCHAR *pp;
			pp = RecallInfoGphMem.data;
			iLine = RecallInfoGphMem.cx * RecallInfoGphMem.bits >> 3;
			for (i = 0; i < RecallInfoGphMem.cy; i++)
			{
				pp = RecallInfoGphMem.data + i * iLine;
				fb_putlinemem(((PWIN)hWnd)->fblayer, rc.left, rc.top +i,
								RecallInfoGphMem.cx, pp);
			}
		}
//			FillRectEx(hdc, &rc, RecallInfoGphMem.cx, RecallInfoGphMem.data);
	}
	ReleaseDC(hdc);
}

static VOID InitInfoText(PPTNINFO pInfo)
{
	int i;
	char *p;
	if (!pInfo)return;
	DATETIME time;
	i = RecallPatientPtr->data.data[RecallPatientPtr->data.info[0].index].time;
	time2datetime(i, &time);
	INT32 len = RecallPatientPtr->data.info[0].count;
	memset(InfoText, '\0', sizeof(InfoText));
	sprintf(InfoText[0], "%s%s",
		LoadString(STR_DLG_PATIENT_NAME), pInfo->patientName);
	sprintf(InfoText[1], "%s%s",
		LoadString(STR_DLG_PATIENT_ID), pInfo->patientID);
	sprintf(InfoText[2], "%s %d",
		LoadString(STR_DLG_PATIENT_AGE), pInfo->patientAge);
	sprintf(InfoText[3], "%s%2dW%dD",
		LoadString(STR_DLG_PATIENT_GESTATIONAL), 
		pInfo->gestationalWeeks, pInfo->gestationalDay);
	sprintf(InfoText[4], "%s %d",
		LoadString(STR_DLG_PATIENT_GTIMES), pInfo->gestationalTimes);
	sprintf(InfoText[5], "%s: %02d:%02d:%02d", 
		LoadString(STR_DLG_RECALL_ENDTIME),
		time.hour, time.minute, time.second);
	sprintf(InfoText[6], "%s: %02d:%02d:%02d",
		LoadString(STR_DLG_RECALL_LENGTH),
		len / 3600, (len % 3600) / 60, len % 60);
	sprintf(InfoText[7], "%s", LoadString(STR_DLG_PATIENT_NOTE));
}


static VOID FetalRecallInit(HWND hWnd)
{
	HWND hCtrl;
	INT32 i;
	INT32 ndx;
	if (RecallFhrBmpMem.data == RecallTOCOBmpMem.data)
	{
		InitFetalRecallBmpMem(IDI_FHR_GPH, &RecallFhrBmpMem);
		InitFetalRecallBmpMem(IDI_TOCO_GPH, &RecallTOCOBmpMem);
		InitFetalRecallGraph();
	}
	if (FmsPtr->GetSaveNum(FmsPtr) == 0)
	{
		EndDialog(hWnd, IDOK);
		return;
	}
	RecallInfoFlag = FALSE;
	RecallAnalyFlag = FALSE;
	//得到用户上次设置的评分法
	FhrConfig.defaultAnalyType = FhrConfig.defaultAnalyType?FhrConfig.defaultAnalyType:1;
	RecallPage = 0;
	i = RecallPatientPtr->data.info[0].count;		   // 数据长度/时间长度(s)
	i = (i + 59) / 60;								  // 时间长度(m)
	MaxRecallPage = (i + 4) / 5;

	if (RecallPatientPtr->data.info[0].count < DATA_SAVE_LEN)
	{
		ndx = 0;
		for (i = 0; i < RECALL_PAGE_MAX_NUMBER; i++)
		{
			PageIndex[i] = 1 + i * RECALL_PAGE_STEP;
		}
	}
	else
	{
		ndx = (RecallPatientPtr->data.info[0].index + 1) % DATA_SAVE_LEN;
		for (i = 0; i < RECALL_PAGE_MAX_NUMBER; i++)
		{
			PageIndex[i] = (ndx + i * RECALL_PAGE_STEP) % DATA_SAVE_LEN;
		}
	}
	InitInfoText(&(RecallPatientPtr->info));
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_SCROLL_L))
	{
		SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
	}
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_ANALY_B))
	{
		SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
		EnableWindow(hCtrl, (RecallPatientPtr->ansis.len > 0));
	}
		printf("init recallanalyflag=false444444444\n");
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_INFO_B))
	{
		SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
	}
		printf("init recallanalyflag=false5555555555\n");
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_PAGEUP_B))
	{
		SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
	}
		printf("init recallanalyflag=false66666666\n");
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_PAGEDN_B))
	{
		SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
	}
		printf("init recallanalyflag=false999999999999999\n");
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_PRINTPAGE_B))
	{
		SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
		EnableWindow(hCtrl, (RecallPatientPtr->ansis.len > 0));
		//EnableWindow(hCtrl, FALSE); //去掉评分打印
	}
		printf("init recallanalyflag=false8888888888\n");
	if (hCtrl = GetDlgItem(hWnd, IDC_FETAL_RECALL_PRINTALL_B))
	{
		SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
	}
		printf("init recallanalyflag=false00000000\n");
}
//设置默认的评分方法
static BOOL ChoseAnalysDlg_OnCommand(HWND hWnd, DWORD choiceID)
{
	
	//所有单选框设为非选中状态
	INT i;
	for ( i = IDC_ANALY_SETUP_SONWINDOW_BUT1;i <= IDC_ANALY_SETUP_SONWINDOW_BUT4; i++)
	{
		CheckDlgButton(hWnd,i,FALSE);
	}
	switch (choiceID)
	{	case IDC_ANALY_SETUP_SONWINDOW_BUT1:
		case IDC_ANALY_SETUP_SONWINDOW_BUT2:
		case IDC_ANALY_SETUP_SONWINDOW_BUT3:
		case IDC_ANALY_SETUP_SONWINDOW_BUT4:
			s_lastChoseGrade = (INT)(choiceID - IDC_ANALY_SETUP_SONWINDOW_BUT1 + 1); 
			CheckDlgButton(hWnd,choiceID,TRUE);//相应的单选框设选中状态
			break;
		case IDC_ANALY_SETUP_SONWINDOW_BUT5://按下确认
			if(FhrConfig.defaultAnalyType != s_lastChoseGrade)
			{
				FhrConfig.defaultAnalyType = s_lastChoseGrade;
				Save_Config(CFG_KEYID_DEFAULTANALYTYPE);
			}
			EndDialog(hWnd, IDOK);
			break;
		default:
			return 0;
			break;
	}
	return 1;
}
static void ChoseAnalyDefaultWindowInit(HWND hWnd)
{	
	s_lastChoseGrade = FhrConfig.defaultAnalyType;
	HWND hCtrl;
	INT32 i;
	for (i = IDC_ANALY_SETUP_SONWINDOW_BUT1; i <= IDC_ANALY_SETUP_SONWINDOW_BUT5; i++)
	{
		hCtrl = GetDlgItem(hWnd, i);
		if (!hCtrl)
			return;
		SetWindowBkColor(hCtrl, ((PWIN)hWnd)->iBkColor);
	}
}
static void ShowChoseAnalyDefaultWindow(HWND hWnd)
{		
	CHAR *txt = NULL;
	HWND hCtrl = 0;
	INT  i;
	for (i = 0; i < 4; i++)
	{
		hCtrl = GetDlgItem(hWnd,IDC_ANALY_SETUP_SONWINDOW_BUT1+ i);
		if (0 != (hCtrl))
		{
			if (FhrConfig.defaultAnalyType == i+1)//上次选中的打勾
				CheckDlgButton(hWnd,i+IDC_ANALY_SETUP_SONWINDOW_BUT1,TRUE);
		}
		
	}
}
static INT32 PtnRecallDlgChoseAnalyWindow (HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	switch(message)
	{
		case MSG_INITDIALOG:
			ChoseAnalyDefaultWindowInit(hWnd);
			break;
		case MSG_SHOWWINDOW:
			ShowChoseAnalyDefaultWindow(hWnd);
			break;
		case MSG_COMMAND:
			if(ChoseAnalysDlg_OnCommand(hWnd, wParam))
				return 0;	
			break;
		default:
			break;
	}
	
	return DefaultDialogProc (hWnd, message, wParam, lParam);

}
VOID SetDefaultAnalyDialog(HANDLE hOwner)
{
	enum dlg_size{
		DLG_WIDTH = 320,
		DLG_HEIGHT =380,
		DLG_START_X = 70,
		STR_START_X = 100,
		DLG_START_Y = 30,
	};
	static BUTTONDATA cbox[4];
	static BUTTONDATA btn_ok;
	memset(cbox, 0, sizeof(cbox));
	memset(&btn_ok, 0, sizeof(btn_ok));
	CTRLDATA ctrl_data[] = {
	//带文字的四个小方格
		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_CHECKBOX, WS_EX_NONE,
			DLG_START_X, DLG_START_Y+KEY_HEIGHT,
			STATIC_HEIGHT+140, STATIC_HEIGHT,
			IDC_ANALY_SETUP_SONWINDOW_BUT1, STR_DLG_ANLS_NST, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_CHECKBOX, WS_EX_NONE,
			DLG_START_X, DLG_START_Y+KEY_HEIGHT*2,
			STATIC_HEIGHT+140, STATIC_HEIGHT,
			IDC_ANALY_SETUP_SONWINDOW_BUT2, STR_DLG_ANLS_FISCHER, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_CHECKBOX, WS_EX_NONE,
			DLG_START_X,DLG_START_Y+KEY_HEIGHT*3,
			STATIC_HEIGHT+140, STATIC_HEIGHT,
			IDC_ANALY_SETUP_SONWINDOW_BUT3, STR_DLG_ANLS_KREBS, 0L, 0L },

		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_CHECKBOX, WS_EX_NONE,
			DLG_START_X,DLG_START_Y+KEY_HEIGHT*4,STATIC_HEIGHT+140,STATIC_HEIGHT,
			IDC_ANALY_SETUP_SONWINDOW_BUT4, STR_DLG_ANLS_CST, 0L, 0L },
////一个确定按钮
		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			STR_START_X+30,DLG_START_Y+KEY_HEIGHT*6,50,30,
			IDC_ANALY_SETUP_SONWINDOW_BUT5, STR_DLG_CHAR_OK, 0L, 0L }
	};
	
	DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   DLG_OFFSET+60, CTRL_HEIGHT, DLG_WIDTH, DLG_HEIGHT,
	   STR_DLG_SETUP_FETAL, 0, NULL, 0L,
	};
	INT16 i, loops;
	loops = TABLESIZE(ctrl_data);

	WNDMEM   wndMem;
	wndMem.pMainWin = GetMainWndMem(IDD_ANALY_SETUP_DEFAULT);
	wndMem.pControl = GetCtrlWndMem(IDC_ANALY_SETUP_DEFAULT_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;
	
	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;
	for(i = 0; i < loops; i++)
	{
		
		SetCtrlDataAddData2(ctrl_data, loops, IDC_ANALY_SETUP_SONWINDOW_BUT1 + i, 
							(UINT32)&cbox[i]);
	}
	
	SetCtrlDataAddData2(ctrl_data, loops, IDC_ANALY_SETUP_SONWINDOW_BUT5, 
						(UINT32)&btn_ok);
	DialogBoxIndirectParam(&dlg_data, hOwner, IDD_PATIENT_RECALL, PtnRecallDlgChoseAnalyWindow, 0,
							&wndMem);

}

static BOOL FetalRecallOnCommand(HWND hWnd, WORD ctrl, WORD code)
{
	BOOL ret = TRUE;
	//printf("ctrl = %d RecallAnalyFlag =%d IDC_FETAL_RECALL_PRINTPAGE_B=%d\n",ctrl,RecallAnalyFlag,IDC_FETAL_RECALL_PRINTPAGE_B);
	switch (ctrl)
	{
		case IDC_FETAL_RECALL_ANALY_B:
			//modify by vinyin2015-05-05!RecallAnalyFlag;从单一评分拓展到4种评分
			RecallAnalyFlag = !RecallAnalyFlag;
			printf("你好RecallAnalyFlag=%d\n",RecallAnalyFlag);
			ShowPatientAnalysis(hWnd, RecallAnalyFlag);
			break;
			
		case IDC_FETAL_RECALL_INFO_B:
			RecallInfoFlag = !RecallInfoFlag;
			ShowPatientInformation(hWnd, RecallInfoFlag);
			break;

		case IDC_FETAL_RECALL_PAGEUP_B:
			if (--RecallPage < 0)
				RecallPage = 0;
			FetalRecallShow(hWnd);
			break;

		case IDC_FETAL_RECALL_PAGEDN_B:
			if (++RecallPage >= MaxRecallPage)
				RecallPage = MaxRecallPage - 1;
			FetalRecallShow(hWnd);
			break;
		case IDC_FETAL_RECALL_PRINTPAGE_B://评分打印 现改为评分设置
			SetDefaultAnalyDialog(hWnd);
			break;

		case IDC_FETAL_RECALL_PRINTALL_B://全部打印
			printf("全部打印\n");
		 	RecordService(REC_RECALL_ALL);
			break;

		case IDC_FETAL_RECALL_EXIT_B:
			EndDialog(hWnd, IDOK);
			break;

		default:
			break;
	}
	return ret;
}

static INT32 
FetalRecallProc(HWND hWnd, INT32 message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		case MSG_INITDIALOG:
			FetalRecallInit(hWnd);
			break;

		case MSG_SHOWWINDOW:
			printf("MSG_SHOWWINDOW111\n");
			FetalRecallShow(hWnd);
			printf("MSG_SHOWWINDOW222\n");
			ShowPationInfo(hWnd);
			printf("MSG_SHOWWINDOW333\n");
			break;

		case MSG_COMMAND:
			if (FetalRecallOnCommand(hWnd, LOWORD(wParam), HIWORD(wParam)))
				return 0;
			break;

		default:
			break;
	}
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}

VOID FetalRecallDialog(HANDLE hOwner, INT16 index)
{
	printf("取出历史数据,%d\n",index);
	RecallPatientPtr = FmsPtr->GetDataFile(FmsPtr, index);
	
	if (RecallPatientPtr == NULL)
	{
		return;
	}
	RecEventClass.prntFileAddData = RecallPatientPtr;
	#if 1
	char log[256];
	char name[9];
	name[8] = '\0';
	sprintf(log, "FetalRecallDialog::RecallPatientPtr:%p\n", RecallPatientPtr);
	PutSystemLog(log);
	sprintf(log, "|>info(%p), ansis(%p), data(%p)\n", &(RecallPatientPtr->info),
		&(RecallPatientPtr->ansis), &(RecallPatientPtr->data));
	PutSystemLog(log);
	memcpy(name, RecallPatientPtr->info.name, 8);
	sprintf(log, "--|>info::name:%s, createTime:%d\n",
		name, RecallPatientPtr->info.createTime);
	PutSystemLog(log);
	memcpy(name, RecallPatientPtr->ansis.name, 8);
	sprintf(log, "--|>ansis::name:%s, len:%d, type:%d, buffer[%d]:%p\n",
		name, RecallPatientPtr->ansis.len, RecallPatientPtr->ansis.type,
		sizeof(RecallPatientPtr->ansis.buffer),	RecallPatientPtr->ansis.buffer);
	PutSystemLog(log);
	memcpy(name, RecallPatientPtr->data.name, 8);
	sprintf(log,
"--|>data::name:%s, index:%d, info[0]:(%d, %d), info[1]:(%d, %d), data[%d]:%p\n",
		name, RecallPatientPtr->data.index,
		RecallPatientPtr->data.info[0].index,
		RecallPatientPtr->data.info[0].count,
		RecallPatientPtr->data.info[1].index,
		RecallPatientPtr->data.info[1].count,
		DATA_SAVE_LEN, RecallPatientPtr->data.data);
	PutSystemLog(log);
	sprintf(log, "The file is %s::%s\n\n",
		RecallPatientPtr->info.patientName, RecallPatientPtr->info.patientID);
	PutSystemLog(log);
	#endif
	
	enum {
		FETAL_GPH_WIDTH = 648,
		FHR_GPH_HEIGHT = 252 + 2,
		TOCO_GPH_HEIGHT = 122 + 2,
		TIME_WIDTH = 160,
		DLG_WIDTH = SCREEN_WIDTH - 4,
		DLG_HEIGHT = SCREEN_HIGH - 4,
		REMAIN_WIDTH = DLG_WIDTH - DLG_OFFSET * 3 - FETAL_GPH_WIDTH+20,
	}DLG_SIZE;
	CTRLDATA ctrl_data[] = {
		{   CTRL_STATIC,
			SS_SIMPLE | WS_VISIBLE, WS_EX_NONE,
			DLG_OFFSET,
			DLG_OFFSET,
			FETAL_GPH_WIDTH,
			FHR_GPH_HEIGHT,
			IDC_FETAL_RECALL_FHRGPH_L, STR_NULL,
			0L, 0L
		},
		{   CTRL_STATIC,
			SS_SIMPLE | WS_VISIBLE, WS_EX_NONE,
			DLG_OFFSET,
			DLG_OFFSET * 2 + FHR_GPH_HEIGHT,
			FETAL_GPH_WIDTH,
			TOCO_GPH_HEIGHT,
			IDC_FETAL_RECALL_TOCOGPH_L, STR_NULL,
			0L, 0L
		},
		{   CTRL_STATIC,
			SS_SIMPLE | WS_VISIBLE, WS_EX_NONE,
			DLG_OFFSET,
			DLG_OFFSET * 2 + FHR_GPH_HEIGHT + TOCO_GPH_HEIGHT,
			TIME_WIDTH,
			STATIC_HEIGHT,
			IDC_FETAL_RECALL_TIME_L, STR_DLG_RECALL_TIME,
			0L, 0L
		},
		{   CTRL_STATIC,
			SS_SIMPLE | WS_VISIBLE, WS_EX_NONE,
			DLG_OFFSET * 2 + TIME_WIDTH,
			DLG_OFFSET * 2 + FHR_GPH_HEIGHT + TOCO_GPH_HEIGHT,
			FETAL_GPH_WIDTH - DLG_OFFSET - TIME_WIDTH,
			STATIC_HEIGHT,
			IDC_FETAL_RECALL_SCROLL_L, STR_NULL,
			0L, 0L
		},
///////////////
		{   CTRL_BUTTON,//评分结果
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET * 2 + FETAL_GPH_WIDTH-10,
			FHR_GPH_HEIGHT - KEY_HEIGHT * 2,
			REMAIN_WIDTH,
			KEY_HEIGHT,
			IDC_FETAL_RECALL_ANALY_B, STR_DLG_ANALY_SHOW,
			0L, 0L
		},
		{   CTRL_BUTTON,//全部打印-->打印
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET * 2 + FETAL_GPH_WIDTH-10,
			DLG_OFFSET + FHR_GPH_HEIGHT - KEY_HEIGHT,
			REMAIN_WIDTH,
			KEY_HEIGHT,
			IDC_FETAL_RECALL_PRINTALL_B, STR_DLG_RECALL_PRINT_ALL,
			0L, 0L
		},	
		{   CTRL_BUTTON,//评分打印--->评分设置
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET * 2 + FETAL_GPH_WIDTH-10,
			DLG_OFFSET * 2 + FHR_GPH_HEIGHT,
			REMAIN_WIDTH,
			KEY_HEIGHT,
			IDC_FETAL_RECALL_PRINTPAGE_B, STR_DLG_RECALL_PRINT_PAGE,
			0L, 0L
		},		
		{   CTRL_BUTTON,//详细信息
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET * 2 + FETAL_GPH_WIDTH-10,
			DLG_OFFSET * 3 + FHR_GPH_HEIGHT + KEY_HEIGHT,
			REMAIN_WIDTH,
			KEY_HEIGHT,
			IDC_FETAL_RECALL_INFO_B, STR_DLG_RECALL_INFO,
			0L, 0L
		},
		////////////
		{   CTRL_BUTTON,
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_OFFSET * 2 + FETAL_GPH_WIDTH-10,
			DLG_OFFSET * 4 + FHR_GPH_HEIGHT + KEY_HEIGHT * 2,
			CTRL_HEIGHT,
			KEY_HEIGHT,
			IDC_FETAL_RECALL_PAGEUP_B, STR_ARROW_LEFT,
			0L, 0L
		},	  
		{   CTRL_BUTTON,
			WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
			DLG_WIDTH - CTRL_HEIGHT - DLG_OFFSET+10,
			DLG_OFFSET * 4 + FHR_GPH_HEIGHT + KEY_HEIGHT * 2,
			CTRL_HEIGHT,
			KEY_HEIGHT,
			IDC_FETAL_RECALL_PAGEDN_B, STR_ARROW_RIGHT,
			0L, 0L
		},
		{   CTRL_BUTTON,
			WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE,
			DLG_WIDTH - EXIT_ICON_WIDTH - DLG_OFFSET,
			-(DLG_MENU_HIGHT + EXIT_ICON_HIGH) / 2,
			EXIT_ICON_WIDTH,
			EXIT_ICON_HIGH,
			IDC_FETAL_RECALL_EXIT_B, STR_DLG_EXIT,
			0L, 0L
		}
	};
	BUTTONDATA btn[6] = {0};
	BUTTONDATA btn_exit = gBtn_Exit;
	
	DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   0, 0, DLG_WIDTH, DLG_HEIGHT,  STR_DLG_RECALL_CAPTION, 0, NULL, 0L,
	};

	
	INT16 i, loops;
	loops = TABLESIZE(ctrl_data);
	WNDMEM   wndMem;
	
	wndMem.pMainWin = GetMainWndMem(IDD_FETAL_RECALL);
	wndMem.pControl = GetCtrlWndMem(IDC_FETAL_RECALL_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;
	
	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;
	i = 0;
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_FETAL_RECALL_ANALY_B,		(UINT32)&btn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_FETAL_RECALL_INFO_B,		(UINT32)&btn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_FETAL_RECALL_PAGEUP_B,	  (UINT32)&btn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_FETAL_RECALL_PAGEDN_B,	  (UINT32)&btn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_FETAL_RECALL_PRINTPAGE_B,   (UINT32)&btn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_FETAL_RECALL_PRINTALL_B,	(UINT32)&btn[i++]);
	SetCtrlDataAddData2(ctrl_data, loops,
		IDC_FETAL_RECALL_EXIT_B,		(UINT32)&btn_exit);

	DialogBoxIndirectParam(&dlg_data, hOwner, IDD_FETAL_RECALL,
							FetalRecallProc, 0, &wndMem);
}

