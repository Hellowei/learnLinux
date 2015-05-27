#include "includes.h"

#if _ENB_REC_FUNC
#define MAX_RECPARAMROWS_150		14
#define MAX_RECPARAMLINES_150	   60
#define FETAL_EVENT_MARK_FLAG	   0x08
#define FETAL_TOCO_ZERO_FLAG		0x04
#define FETAL_AMOVEMENT_FLAG		0x02
#define FETAL_MOVEMENT_FLAG		 0x01
typedef enum {
	PRINT_CURR,		 // 只有实时打印时有效,根据实际波形当前指针打印
	PRINT_PAGESTART,	// 打印从当前页开始,实时打印时根据实际波形当前指针打印
	PRINT_PAGE		  // 打印当前页,打印本页数据
}PRINT_MODE;

typedef enum{
	PRINT_MANUALLY,
	PRINT_10MIN,
	PRINT_15MIN,
	PRINT_20MIN,
	PRINT_30MIN,
	PRINT_40MIN,
	PRINT_50MIN,
	PRINT_60MIN,
}PRINT_TIME;

UCHAR   sParams_150[MAX_RECPARAMROWS_150][MAX_RECPARAMLINES_150];
static INT16  sLastWavedata[3] = {-1, -1, -1};
static STRINGID Timer[] = {
	STR_DLG_FM_MOVEMENTCAL_MANUAL,
	STR_DLG_10MIN,
	STR_DLG_15MIN,
	STR_DLG_20MIN,
	STR_DLG_30MIN,
	STR_DLG_40MIN,
	STR_DLG_50MIN,
	STR_DLG_60MIN,
};

#define RecTextOut(this, x, y, txt) \
	this->pRecClass->RecPreShowCharacter(this->pRecClass, x, y, NULL, 1, 0, txt)


/*****************************************************************************************
* Function	: RecTextOM
* Description : recorder multi-text output
* Input Para  : 
* Output Para : 
* Return Value: 
*****************************************************************************************/
static INT32 RecTextOM
			(PRECEVENTCLASS this,INT32 x, INT32 y, INT32 w, INT32 h, char *txt)
{
	INT32 len = strlen(txt) + 1;
	PCHAR pStr = (PCHAR)TextNew(len);
	INT32 out = 0;
	INT32 off = 0;
	INT32 width;
	INT32 max_width = 0;
	PLOGFONT pFont = (PLOGFONT)this->pRecClass->font_normal;
	
	if (!pStr) return 0;

	while(off < len - 1)
	{
		out = GetAreaStrLen(pFont, w, txt + off);
		memset(pStr, '\0', len);
		strncpy(pStr, txt + off, out);
		width = RecTextOut(this, x, y, pStr);
		if (max_width < width)
			max_width = width;
		y = y + pFont->size + 1;
		h -= pFont->size + 1;
		if (h < pFont->size)
		{
			break;
		}
		off += out;
	}
	TextDel(pStr);
	return max_width;
}

/*****************************************************************************************
* Function	: RecTextOC
* Description : recorder text output in center
* Input Para  : 
* Output Para : 
* Return Value: 
*****************************************************************************************/
static INT32 RecTextOC(PRECEVENTCLASS this,
				INT32 x, INT32 y, INT32 w, INT32 h, char *txt)
{
	SIZE		size;
	INT32	   len = strlen(txt);
	INT32	   x1, y1;
	PLOGFONT	pFont = (PLOGFONT)this->pRecClass->font_normal;

	if (w < 0 || h < 0)
	{
		x += w;
		w = -w;
	}
	if (h < 0)
	{
		y += h;
		h =- h;
	}
	if (x < 0 || y < 0 || y > RECORD_WIDTH_PAPER)
	{
		return 0;
	}
	gdi_get_TextOut_extent(NULL, pFont, txt, len, &size);
	if (w < size.cx)
	{
		x1 = 1;
		if (pFont->size * 2 < h && w )
		{
			// 多行显示
			return RecTextOM(this, x, y, w, h, txt);	
		}
		else
		{
			// 减少输出
			INT32 out = len;
			char *tmp = (char*)TextNew(len);
			if (!tmp) return 0;
			memset(tmp, '\0', len);
			out --;
			while(w < size.cx)
			{
				strncpy(tmp, txt, out);
				gdi_get_TextOut_extent(NULL, pFont, tmp, out, &size);
				strcpy(txt, tmp);
				memset(tmp, '\0', len);
				out = strlen(txt) - 1;
				if (out < 2)
				{
					return 0;
				}
			}
		}
	}
	else
	{
		x1 = x + (w - size.cx) / 2;
	}
	if (h < size.cy)
	{
		return 0;
	}
	else
	{
		y1 = y + (h - size.cy) / 2;
	}
	return RecTextOut(this, x1, y1, txt);	
}
/*******************************************************************************
* Function	: RecGetParamPerFhr
* Description : 
* Input Para  : 
* Output Para : 
* Return Value: 
*******************************************************************************/
VOID RecGetParamPerFhr(VOID)
{
	CHAR	 tbuf[MAX_RECPARAMLINES_150];
	INT32	i;
	DATETIME end_time;
	
	STRINGID SweepSpeed[] = {
		STR_SWEEP_SPEED_1,
		STR_SWEEP_SPEED_2,
		STR_SWEEP_SPEED_3,
	};
	
	for (i = 0; i < MAX_RECPARAMROWS_150; ++ i)
	{
		memset(sParams_150[i], 0, MAX_RECPARAMLINES_150);
	}

	// REAL TIME RECORDER
	strcpy(sParams_150[0], LoadString(STR_PRINT_TYPE_FETAL));
	FormatDateString(&DateTime, tbuf);
	sprintf(sParams_150[1], "%s:%s  %02d:%02d:%02d",
		LoadString(STR_PRINT_TIME_START), tbuf,
		DateTime.hour, DateTime.minute, DateTime.second);
	sprintf(sParams_150[2], "%s ", LoadString(STR_MAIN_BOTTOM_PERIOD));
	strcat (sParams_150[2], LoadString(Timer[FhrConfig.printLength]));
	
	sprintf(sParams_150[3], "%s %s",
		LoadString(STR_PRINT_NAME), PatientInfo.patientName);
	
	sprintf(sParams_150[4], "%s %s",
		LoadString(STR_PRINT_ID), PatientInfo.patientID);

	if (MonitorConfig.language == CHINESE)
	{
		if (PatientInfo.gestationalWeeks > 20 
			&& PatientInfo.gestationalWeeks < 45)
		{
			sprintf(sParams_150[5], "%s %-2d 周 %d 天",
				LoadString(STR_DLG_PATIENT_GESTATIONAL),
				PatientInfo.gestationalWeeks,
				PatientInfo.gestationalDay);
		}
		else
		{
			sprintf(sParams_150[5], "%s    周    天",
				LoadString(STR_DLG_PATIENT_GESTATIONAL));
		}
	}
	else
	{
		if (PatientInfo.gestationalWeeks > 20 
			&& PatientInfo.gestationalWeeks < 45)
		{
			sprintf(sParams_150[5], "%s %-2d W %d D",
				LoadString(STR_DLG_PATIENT_GESTATIONAL),
				PatientInfo.gestationalWeeks,
			  	PatientInfo.gestationalDay);
		}
		else
		{
			sprintf(sParams_150[5], "%s    W    D",
				LoadString(STR_DLG_PATIENT_GESTATIONAL));
		}
	}
	if (PatientInfo.gestationalTimes < 1)
	{
		sprintf(sParams_150[6], "%s", LoadString(STR_DLG_PATIENT_GTIMES));
	}
	else
	{
		sprintf(sParams_150[6], "%s %d", LoadString(STR_DLG_PATIENT_GTIMES),
			PatientInfo.gestationalTimes);
	}
	sprintf(sParams_150[7], "%s %s", LoadString(STR_DLG_SETUP_SPEED),
		LoadString(SweepSpeed[FhrConfig.sweep%TABLESIZE(SweepSpeed)]));
		
	if (FhrConfig.detach){
    	sprintf(sParams_150[7+1], "%s: %3d", LoadString(STR_DLG_FHR_DETACH_SPLINE),
    		20/*FhrConfig.detachSplineVal*/);
    }
    #if 0
	strcpy(sParams_150[8], LoadString(STR_REC_LEGEND));

	strcpy(sParams_150[9], LoadString(STR_REC_FETAL_MOVEMENT));

	strcpy(sParams_150[10], LoadString(STR_REC_AUTO_FETAL_MOV));
	
	strcpy(sParams_150[11], LoadString(STR_HK_FHR_RESETTOCO));
	#else
	if (MonitorConfig.language == CHINESE)
	{
		strcpy(sParams_150[8+1],  "图例");

		strcpy(sParams_150[9+1],  "胎动标记");

		strcpy(sParams_150[11+1], "宫压归零");
	}
	else if (MonitorConfig.language == RUSSIAN)
		 
	{
		strcpy(sParams_150[8+1],  " ");

		strcpy(sParams_150[9+1],  "ДП");

		strcpy(sParams_150[11+1], "ТОКО");
	}
	else 
	{
		strcpy(sParams_150[8+1],  " ");

		strcpy(sParams_150[9+1],  "FM");

		strcpy(sParams_150[11+1], "TOCO");
	}
	#endif
}


/*******************************************************************************
* Function	: RecSendParamPerFhr
* Description : 
* Input Para  : 
* Output Para : 
* Return Value: 
*******************************************************************************/
VOID RecSendParamPerFhr(PRECEVENTCLASS this)
{
	UINT16 pos_row[MAX_RECPARAMROWS_150];
	UINT16 line_w[MAX_RECPARAMROWS_150];
	UINT32 x_start;
	UINT32 y_start;
	UINT32 y_end;
	UINT32 y_dist;
	UINT16 i;
	UINT16 max_width = 0;
	UINT16 legend_width = 0;
	
	memset (line_w, 0, sizeof(line_w));
	//计算字符显示的各个位置
#if MYFB_RECORD_DEBUG
	x_start = 0;  //adjust its position
#else
	x_start = 40;//前切纸5mm
#endif
	y_start = RecConfig.regStar[PAPER_REG_FHR];
	
	y_dist  = ((PLOGFONT)(this->pRecClass->font_cutter))->size * 3 / 2;
	//GetSystemFont(SYSLOGFONT_ARTEMIS_MID)->size * 3 / 2;
	for (i = 0; i <= 7; i++)
	{
		pos_row[i] = y_start + i * y_dist;
	}
	for (i = 0; i <= 7; i++)
	{		
		line_w[i] = this->pRecClass->RecPreShowCharacter(this->pRecClass,
			x_start, pos_row[i], (PLOGFONT)(this->pRecClass->font_cutter),
			1, 0, sParams_150[i]);
		if (max_width < line_w[i])
		{
			max_width = line_w[i];
		}		
	}
	
	if (FhrConfig.detach)//显示曲线分离值
	{
		pos_row[i] = RecConfig.regStar[PAPER_REG_FHR]
					+ (RecConfig.regEnd[PAPER_REG_FHR]
						- RecConfig.regStar[PAPER_REG_FHR]) * 4 / 7;
		if (pos_row[i] < pos_row[i - 1] + y_dist)
			pos_row[i] = pos_row[i - 1] + y_dist;
		line_w[i]  = this->pRecClass->RecPreShowCharacter(this->pRecClass,
			x_start, pos_row[i], (PLOGFONT)(this->pRecClass->font_cutter),
			1, 0, sParams_150[i]);
		if (max_width < line_w[i])
		{
			max_width = line_w[i];
		}		
		i++;
	}
	#if 1
	if (pos_row[i - 1] < RecConfig.regStar[PAPER_REG_TOCO])
	{
		UINT16 index;
		UINT16 icon_xpos;
		index = 9;
		i = index;
		pos_row[i] = RecConfig.regStar[PAPER_REG_TOCO] + y_dist;
		x_start += 100;
//		line_w[i]  = this->pRecClass->RecPreShowCharacter(this->pRecClass,
//			x_start, pos_row[i], NULL, 1, 0, sParams_150[i]);
		line_w[i] = RecTextOut(this, x_start, pos_row[i], sParams_150[i]);
		if (legend_width < line_w[i])
		{
			legend_width = line_w[i];
		}
		pos_row[i+1] = pos_row[i] + y_dist;
		i++;
//		line_w[i]  = this->pRecClass->RecPreShowCharacter(this->pRecClass,
//			x_start, pos_row[i], NULL, 1, 0, sParams_150[i]);
		line_w[i] = RecTextOut(this, x_start, pos_row[i], sParams_150[i]);
		if (legend_width < line_w[i])
		{
			legend_width = line_w[i];
		}
		pos_row[i+1] = pos_row[i] + y_dist;
		i++;
//		line_w[i]  = this->pRecClass->RecPreShowCharacter(this->pRecClass,
//			x_start, pos_row[i], NULL, 1, 0, sParams_150[i]);
		line_w[i] = RecTextOut(this, x_start, pos_row[i], sParams_150[i]);
		if (legend_width < line_w[i])
		{
			legend_width = line_w[i];
		}		
		pos_row[i+1] = pos_row[i] + y_dist;
		i++;
//		line_w[i]  = this->pRecClass->RecPreShowCharacter(this->pRecClass,
//			x_start, pos_row[i], NULL, 1, 0, sParams_150[i]);
		line_w[i] = RecTextOut(this, x_start, pos_row[i], sParams_150[i]);
		if (legend_width < line_w[i])
		{
			legend_width = line_w[i];
		}
		i = index + 1;
		icon_xpos = x_start * 2 + legend_width;
		line_w[i] = icon_xpos;
		line_w[i] += PrinterPutIcon(this, icon_xpos + 6, pos_row[i],
			REC_ICON_UPARROW);
		if (legend_width < line_w[i])
		{
			legend_width = line_w[i];
		}
		i++;
//		line_w[i] = icon_xpos;
//		line_w[i] += PrinterPutIcon(this, icon_xpos + 6, pos_row[i],
//			REC_ICON_UPARROW);
//		if (legend_width < line_w[i])
//		{
//			legend_width = line_w[i];
//		}
		i++;
		line_w[i] = icon_xpos;
		line_w[i] += PrinterPutIcon(this, icon_xpos, pos_row[i],
			REC_ICON_TOCOZERO);
		if (legend_width < line_w[i])
		{
			legend_width = line_w[i];
		}
		pos_row[i+1] = pos_row[i] + y_dist;
		i++;
		line_w[i] = 0;
		while(line_w[i] < legend_width)
		{
//			this->pRecClass->RecPreShowCharacter(this->pRecClass,
//				x_start + line_w[i], pos_row[i], NULL, 1, 0, "*");
//			line_w[i] += this->pRecClass->RecPreShowCharacter(this->pRecClass,
//				x_start + line_w[i], RecConfig.regStar[PAPER_REG_TOCO], 
//				NULL, 1, 0, "*");
			RecTextOut(this, x_start + line_w[i], pos_row[i], "*");
			line_w[i] += RecTextOut(this, x_start + line_w[i],
				RecConfig.regStar[PAPER_REG_TOCO], "*");
		}
		if (max_width < legend_width)
		{
			max_width = legend_width;
		}		
	}
	#endif
	max_width += 80 - (max_width % 8);
	this->pRecClass->RecWriteIndexADD (this->pRecClass, max_width);//切纸1cm
	if (this->semaphore == FALSE)
	{
		GET_RECSTARTUP_PERMIT();
		this->semaphore = TRUE;
		RELEASE_STARTUP_PERMIT();
	}
}


/*******************************************************************************
* Function	: GetPrintTime
* Description : 
* Input Para  : 
* Output Para : 
* Return Value: 
*******************************************************************************/
static UINT32 GetPrintTime(PRINT_TIME time)
{
	switch (time)
	{
		case PRINT_10MIN:
			return (10 * 60);

		case PRINT_15MIN:
			return (15 * 60);

		case PRINT_20MIN:
			return (20 * 60);

		case PRINT_30MIN:
			return (30 * 60);

		case PRINT_40MIN:
			return (40 * 60);

		case PRINT_50MIN:
			return (50 * 60);

		case PRINT_60MIN:
			return (60 * 60);

		default:
			return 0;
	}
}


/*******************************************************************************
* Function	: GetPrintEndPrt
* Description : 
* Input Para  : 
* Output Para : 
* Return Value: 
*******************************************************************************/
VOID GetPrintEndPrt(PRECFHRCONTROL this)
{
	this->pFHREnd = FetalWavePrint->pCurr;
	return;
//	PFHRWAVE pWave = FetalWavePrint;
//	if (pWave->PgNdx == 0)// 当前实时刷新, 这种情况调用本函数频率最高,优先处理
//	{
//		this->pFHREnd = pWave->pCurr;
//		return;
//	}
//	if (this->periodTime == 0)
//	{
//		this->pFHREnd = pWave->pCurr;
//		return;
//	}
//	if (this->periodTime > DATA_SAVE_LEN)
//	{
//		this->pFHREnd = this->pFHRStart;
//		return;
//	}
//	// 开始计算指针指针偏移量
//	UINT32 offset = this->periodTime * this->recRate * sizeof(FETALWAVEDATA);
//	FETALWAVEDATA *p = this->pFHRStart + offset;
//	if (PTR_CPR(this->pFHRTail, p))
//	{
//		offset = (this->pFHRTail - this->pFHRHead) * sizeof(FETALWAVEDATA);
//		p = (FETALWAVEDATA *)PTR_SUB(p, offset);
//	}
//	if (PTR_CPR(pWave->pCurr, this->pFHRStart)) // 当前指针已回绕
//	{
//		if (PTR_CPR(p, this->pFHRStart))		// 结束指针已回绕
//		{
//			if (PTR_CPR(pWave->pCurr, p))	   // 结束指针越过当前指针
//			{
//				p = pWave->pCurr;
//			}
//		}
//	}
//	else										// 当前指针未回绕
//	{
//		if (PTR_CPR(p, this->pFHRStart))		// 结束指针已回绕
//		{
//			p = pWave->pCurr;
//		}
//		else									// 结束指针未回绕
//		{
//			if (PTR_CPR(pWave->pCurr, p))	   // 结束指针越过当前指针
//			{
//				p = pWave->pCurr;
//			}
//		}
//	}
//	this->pFHREnd = p;
//	return;
}



/*******************************************************************************
* Function	: RecFetalInitPtr
* Description : 
* Input Para  : 
* Output Para : 
* Return Value: 
*******************************************************************************/
VOID RecFetalInitPtr(PRECFHRCONTROL this)
{
	// 打印方式在这里初始化,启动打印后修改打印方式不影响本次打印
	this->rec_type = FhrConfig.printMode;
	// 打印速度在这里初始化,启动打印后修改打印速度不影响本次打印
	this->recRate = (FhrConfig.sweep + 1) * FETAL_SAMPLE_RATE;
	// 打印开始标志位
	this->isBegin = TRUE;
	// 打印结束后如果是定时打印,比较过去时间和定时时间来决定是否停止打印
	this->periodTime = GetPrintTime((PRINT_TIME)FhrConfig.printLength);
	// 重置打印过去时间
	this->elapseSec = 0;
	// 重置打印超时标志
	this->timeover = FALSE;
	// 初始化打印指针
	this->pFHRHead = FetalWavePrint->pHead;
	this->pFHRTail = FetalWavePrint->pTail;
	int i;
	for (i = 0; i < REC_FHR_CURVE_POINTS; i++)
	{
		RecFhr1RealSave[i] = -1;
		RecFhr2RealSave[i] = -1;
		RecTocoRealSave[i] = -1;
		RecAutoRealSave[i] = -1;
	}
	switch (this->rec_type)
	{
		case PRINT_CURR:
			this->pFHRStart = FetalWavePrint->pCurr;
			break;

		case PRINT_PAGESTART:
			this->pFHRStart = FetalWavePrint->pPage;
			break;

		case PRINT_PAGE:
			this->pFHRStart = FetalWavePrint->pPage;
			this->timeover = TRUE;
			this->periodTime = WAVE_CX_CM / (FhrConfig.sweep + 1) * 60;
			break;
	}
	// 由this->pFHREnd指针决定打印结束,打印结束不代表打印停止
	GetPrintEndPrt(this);
	// 同步打印机状态,打印机忙或打印机故障时暂缓打印
	this->recStatus = RecConfig.recstatus;
}


/*******************************************************************************
* Function	: RecFetalMovePtr
* Description : 
* Input Para  : 
* Output Para : 
* Return Value: 
*******************************************************************************/
VOID RecFetalMovePtr(PRECFHRCONTROL this)
{
	this->pFHREnd = FetalWavePrint->pCurr;
}


/*******************************************************************************
函数名称:	INT32 RecFhrUpdataBuff_150 (INT16 data_num)
版本号:		1.0.0
生成日期:	2011.11.15
作者:		zondan
功能说明:	实时更新胎监打印缓冲区中的数据
输入参数:	
输出参数:	
其它说明:	采用抽值法采样,不进行平均值计算,每12个数据发送一次
函数返回:   不足12个数据返回0,数据足够返回打印长度
*******************************************************************************/
INT32 RecFetalUpdataBuff (PRECEVENTCLASS this, int source)
{
	static UINT32 oldSecond = 0;
	INT32  i;
	INT32  j;
	INT32  offset;
	//FHR_REAL_PARAMS tmp_fhr_para;
	PRECFHRCONTROL  pFhrCtrl = this->fetalAddData;
	FETALWAVEDATA *p;
	FETALWAVEDATA *pStart;
	if (pFhrCtrl == NULL)
		return 0;
	if((UINT32)pFhrCtrl->pFHRStart <= (UINT32)pFhrCtrl->pFHREnd)
	{
		offset = pFhrCtrl->pFHREnd - pFhrCtrl->pFHRStart;
	}
	else
	{
		offset = pFhrCtrl->pFHRTail - pFhrCtrl->pFHREnd;
		offset += pFhrCtrl->pFHRStart - pFhrCtrl->pFHRHead;
	}
	//prinfo("pFHREnd, pFHRStart ... %p, %p\r\n", this->fetalAddData->pFHREnd, this->fetalAddData->pFHRStart);
	if (offset < REC_FHR_CURVE_POINTS)
		return 0;
	//printf("offset %d\n", offset);
	if (RecFHRControl.elapseSec == oldSecond)
		return 0;
	//if (RecFHRControl.elapseSec % 3 != 0)
		//return 0;
	oldSecond = RecFHRControl.elapseSec;
	ZeroMemory(&RecEventRealSave, sizeof(RecEventRealSave));
	pStart = pFhrCtrl->pFHRStart;
	for (i = 0; i < pFhrCtrl->recRate; i++)
	{
		j = (INT32)((FLOAT)i * REC_FHR_CURVE_POINTS / pFhrCtrl->recRate + 0.5);
		p = pStart + j;
		//printf("p=%p j=%d\n",p,j);
		if (p > pFhrCtrl->pFHRTail)
		{
			p = pFhrCtrl->pFHRHead + (j - (pFhrCtrl->pFHRTail - pStart));
		}
		RecFhr1RealSave[i] = p->fhr1;
		RecFhr2RealSave[i] = p->fhr2;
		RecTocoRealSave[i] = p->toco;
		//printf("RecTocoRealSave[%d] = %d\n",i, RecTocoRealSave[i]);
		//RecAutoRealSave[i] = ;
		RecEventRealSave[i] = p->event;
		RecMarkRealSave[i] = 0;
		if (p->zerobits)
			RecMarkRealSave[i] |= FETAL_TOCO_ZERO_FLAG;
		if (p->fmbits)
			RecMarkRealSave[i] |= FETAL_MOVEMENT_FLAG;
		if (p->afmbits)
			RecMarkRealSave[i] |= FETAL_AMOVEMENT_FLAG;
		if (p->event < 16 && p->event > 0)
			RecMarkRealSave[i] |= FETAL_EVENT_MARK_FLAG;
	}
//	p++;
//	if (p > pFhrCtrl->pFHRTail)
//		p = pFhrCtrl->pFHRHead;
//	pFhrCtrl->pFHRStart = p;
    if (0)//(oldSecond % 25 == 0)  //25秒补一个点,由于112打印机启动/停止时存在1%的误差
    {
        pFhrCtrl->pFHRStart += (REC_FHR_CURVE_POINTS - 1); //指针向前多走一个点来增加数据
    }
    else
    {
        pFhrCtrl->pFHRStart += REC_FHR_CURVE_POINTS;
    }
    if (pFhrCtrl->pFHRStart > pFhrCtrl->pFHRTail)
        pFhrCtrl->pFHRStart = pFhrCtrl->pFHRStart - pFhrCtrl->pFHRTail + pFhrCtrl->pFHRHead;
	return (pFhrCtrl->recRate);
}



/*******************************************************************************
函数名称:	INT32 RecBuildFetalGraph (INT32 *databuf, INT32 len, UINT16 index)
版本号:		1.0.0
生成日期:	2011.11.15
作者:		zondan
功能说明:	构建打印图形
输入参数:	
输出参数:	
其它说明:	尤其注意边界的处理
*******************************************************************************/
INT32 
RecBuildFetalGraph(PRECEVENTCLASS this, INT32 *databuf, INT32 len, UINT16 index)
{
	INT16  value;
	INT16  last_value = INVALID_PARAM_INT;
	INT16  i;

	for (i = 0; i <= len; ++ i)
	{
		if (i == len)
		{
			sLastWavedata[index] = databuf[i - 1];
			break;
		}
		//开始时的边界处理
		if (i == 0)
		{
			if (sLastWavedata[index] != -1)
			{
				value = databuf[0];
				last_value = sLastWavedata[index];
				if (last_value > 0)
				{
					if (ABS(value - last_value) < 30 || index == 2)//胎心不画超过12mm的直线
					{
						this->pRecClass->RecPreLine (this->pRecClass,
													i, value, i, last_value, 1);
					}
				}			
			}
			continue;
		}
		if (databuf[i] > 0)
		{
			value = databuf[i];
			if (last_value > 0)
			{
				if (ABS(value - last_value) < 30 || index == 2)//胎心不画超过12mm的直线
				{
					this->pRecClass->RecPreLine (this->pRecClass,
												i - 1, last_value, i, value, 1);
				}
			}
			else
			{
				this->pRecClass->RecPreLine (this->pRecClass,
											i, value, i, value, 1);
			}
			last_value = value;
		}
		else
		{
			last_value = INVALID_PARAM_INT;
		}
	}
	return len;
}




/*******************************************************************************
* Function	: RecPutEventMarkGraph
* Description : 
* Input Para  : 
* Output Para : 
* Return Value: 
*******************************************************************************/
VOID 
RecPutEventMarkGraph(PRECEVENTCLASS this, INT32 *pos, INT32 *high, INT32 len)
{
	UINT8 event[REC_FHR_CURVE_POINTS];
	UINT8 drmtype[REC_FHR_CURVE_POINTS];
	INT32 i;
	STRINGID drMarkTypeStr[] = {
		STR_NULL,
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
	memcpy ((char *)&event, (char *)&RecMarkRealSave, REC_FHR_CURVE_POINTS);
	memcpy ((char *)&drmtype, (char *)&RecEventRealSave, REC_FHR_CURVE_POINTS);
	#if 1
	for (i = 0; i < len; ++ i)
	{
		while (this->semaphore)
		{
			GET_RECSTARTUP_PERMIT();
			this->semaphore = FALSE;
			RELEASE_STARTUP_PERMIT();
			ms_sleep(RECORD_DELAYTICKS);
		}
//		if (event[i].eventA)
//		{
//			PrinterPutIcon(this, i, pos[0] - high[0], REC_ICON_EVENTFLAG1);
//		}
//		
//		if (event[i].eventB)
//		{
//			PrinterPutIcon(this, i, pos[0] - high[0] + 24, REC_ICON_EVENTFLAG2);
//		}
//		
//		if (event[i].eventC)
//		{
//			PrinterPutIcon(this, i, pos[0] - high[0] + 48, REC_ICON_EVENTFLAG3);
//		}
//		
//		if (event[i].eventD)
//		{
//			PrinterPutIcon(this, i, pos[0] - high[0] + 72, REC_ICON_EVENTFLAG4);
//		}

		if (event[i] & FETAL_MOVEMENT_FLAG)
		{
			PrinterPutIcon(this, i, pos[2] - high[2], REC_ICON_UPARROW);
		}

		if (event[i] & FETAL_TOCO_ZERO_FLAG)
		{
			PrinterPutIcon(this, i, pos[2] - 40, REC_ICON_TOCOZERO);
		}

		if (event[i] & FETAL_AMOVEMENT_FLAG)
		{
			PrinterPutIcon(this, i, pos[2] - high[2] + 30, REC_ICON_UPARROW);
		}

		if(event[i] & FETAL_EVENT_MARK_FLAG) // 医生标记
		{
			if(drmtype[i] < TABLESIZE(drMarkTypeStr) && drmtype[i] > 0)
			{
				this->pRecClass->RecPreShowCharacter(this->pRecClass, i,
					pos[0] - high[0] + 100, 
					//GetSystemFont(SYSLOGFONT_FIXED),0,0,
					(PLOGFONT)this->pRecClass->font_cutter, 0, 0,
					LoadString(drMarkTypeStr[drmtype[i]]));
			}
		}
		GET_RECSTARTUP_PERMIT();
		this->semaphore = TRUE;
		RELEASE_STARTUP_PERMIT();
	}
	#endif
}

VOID RecPutMarker(PRECEVENTCLASS this,
				  INT32 *pos, INT32 *high, INT32 type, UCHAR *event, INT32 len)
{
	INT32 i;
	INT32 sum = 0;
	STRINGID drMarkTypeStr[] = {
		STR_NULL,
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
	switch (type)
	{
		case FETAL_MOVEMENT_FLAG:
			for (i = 0; i < len; i++)
			{
				if (*(event + i) && (sum == 0))
				{
					PrinterPutIcon(this, i, pos[2] - high[2], REC_ICON_UPARROW);
					sum = 40;
				}
				if (sum > 0)
					sum--;
			}
			break;

		case FETAL_AMOVEMENT_FLAG:
			for (i = 0; i < len; i++)
			{
				if (*(event + i) && (sum == 0))
				{
					PrinterPutIcon(this, i, pos[3], REC_ICON_UPARROW);
					sum = 40;
				}
				if (sum > 0)
					sum--;
			}
			break;

		case FETAL_TOCO_ZERO_FLAG:
			for (i = 0; i < len; i++)
			{
				if (*(event + i) && (sum == 0))
				{
					PrinterPutIcon(this, i, pos[2] - 40, REC_ICON_TOCOZERO);
					sum = 40;
				}
				if (sum > 0)
					sum--;
			}
			break;

		case FETAL_EVENT_MARK_FLAG:
			for (i = 0; i < len; i++)
			{
				if ((*(event + i) > 0)
					&& (*(event + i) < TABLESIZE(drMarkTypeStr))
					&& (sum == 0))
				{
					this->pRecClass->RecPreShowCharacter(this->pRecClass, i,
								pos[0] - high[0] + 100, NULL,0,0,
								LoadString(drMarkTypeStr[*(event + i) - 1]));
					sum = 16;
				}
				if (sum > 0)
					sum--;
			}
			break;

		default:
			break;
	}
}

static VOID RecGetWavePos(INT32 top[4], INT32 bot[4])
{
	INT32 FhrMin[2] = { 30,  60};
	INT32 FhrMax[2] = {240, 210};
	if (RecConfig.fhrMin == 1 && RecConfig.fhrMax == 1)
	{
		top[0] = RecConfig.regStar[PAPER_REG_FHR];
		bot[0] = RecConfig.regEnd[PAPER_REG_FHR];
	}
	else
	{
		INT32 start = RecConfig.regStar[PAPER_REG_FHR];
		INT32 end = RecConfig.regEnd[PAPER_REG_FHR];
		INT32 offset = ABS((end - start) * 30
	//		/ (FhrMax[RecConfig.fhrMax] - FhrMin[RecConfig.fhrMin]));
			/ (FhrMax[1] - FhrMin[1]));
		top[0] = start - offset * (1 - RecConfig.fhrMax);
		bot[0] = end + offset * (1 - RecConfig.fhrMin);
	}
	top[1] = top[0];
	bot[1] = bot[0];
	top[2] = RecConfig.regStar[PAPER_REG_TOCO];
	bot[2] = RecConfig.regEnd[PAPER_REG_TOCO];
	top[3] = top[2];
	bot[3] = bot[2] - (bot[2] - top[2]) * 3 / 5;
}

/*******************************************************************************
函数名称:	INT32 PrintFetalGraph (INT32 data_num)
版本号:		1.0.0
生成日期:	2011.11.15
作者:		zondan
功能说明:	构建好打印图形发送给打印机
输入参数:	
输出参数:	
其它说明:	
*******************************************************************************/
INT32 PrintFetalGraph (PRECEVENTCLASS this, INT32 data_num)
{	
	INT	i;
	UINT8  *p;
	INT32 databuf[3][REC_FHR_CURVE_POINTS];
	const INT32 FhrMin[2] = { 30,  60};
	const INT32 FhrMax[2] = {240, 210};
#if MYFB_RECORD_DEBUG
	INT32 pos[3]  = {247, 247, 367};
	INT32 high[3] = {204, 204, 124};
#else
	INT32 pos[3];
	INT32 high[3];
	pos[0] = RecConfig.regEnd[PAPER_REG_FHR];
	pos[1] = pos[0];
	pos[2] = RecConfig.regEnd[PAPER_REG_TOCO];
	high[0] = RecConfig.regEnd[PAPER_REG_FHR]-RecConfig.regStar[PAPER_REG_FHR];
	high[1] = high[0];
	high[2] =RecConfig.regEnd[PAPER_REG_TOCO]-RecConfig.regStar[PAPER_REG_TOCO];
#endif	
	for (i = 0; i < REC_FHR_CURVE_POINTS; i++)
	{
		databuf[0][i] = RecFhr1RealSave[i];
		if (FhrConfig.detach)
		    databuf[1][i] = RecFhr2RealSave[i] - 20;
		else
		    databuf[1][i] = RecFhr2RealSave[i];
		databuf[2][i] = RecTocoRealSave[i];
	}
	INT32 top[4];
	INT32 bot[4];
	RecGetWavePos(top, bot);
	//根据打印纸上波形区域的高度对波形数据进行增益调节
	RecScaleWave(top[0], bot[0], FhrMin[RecConfig.fhrMin],
					FhrMax[RecConfig.fhrMax], databuf[0], data_num);
	RecScaleWave(top[1], bot[1], FhrMin[RecConfig.fhrMin],
					FhrMax[RecConfig.fhrMax], databuf[1], data_num);
	RecScaleWave(top[2], bot[2], 0, 100, databuf[2], data_num);
	if (FhrConfig.mode != 1)
	{
		RecBuildFetalGraph (this, databuf[0], data_num, 0);
	}
	if (FhrConfig.mode > 0)
	{
		RecBuildFetalGraph (this, databuf[1], data_num, 1);
	}
	RecBuildFetalGraph (this, databuf[2], data_num, 2);
	RecPutEventMarkGraph(this, pos, high, data_num);
	this->pRecClass->RecWriteIndexADD(this->pRecClass, data_num);
	return TRUE;
}

/*****************************************************************************************
函数名称:	VOID PrintFetalParamEnd(VOID)
版本号:		1.0.0
生成日期:	2011.11.15
作者:		zondan
功能说明:	将参数信息封装成打印位图并发送给打印机
输入参数:	
输出参数:	
其它说明:	
*****************************************************************************************/
VOID PrintFetalParamEnd(PRECEVENTCLASS this)
{
	UINT16 pos_row[MAX_RECPARAMROWS_150];
	UINT16 line_w[MAX_RECPARAMROWS_150];
	UINT32 x_start = 0;
	UINT32 y_start;
	UINT32 y_end;
	UINT32 y_dist;
	UINT16 i;
	UINT16 max_width = 0;

	memset (line_w, 0, sizeof(line_w));
	//计算字符显示的各个位置
	y_start = RecConfig.regStar[PAPER_REG_FHR];
	y_dist  = GetSystemFont(SYSLOGFONT_YAHEI17_FONT)->size * 3 / 2;
	for (i = 0; i < MAX_RECPARAMROWS_150; i++)
	{
		pos_row[i] = y_start + i * y_dist;
	}
	for (i = 0; i < MAX_RECPARAMROWS_150; i++)
	{
		if(sParams_150[i][0] == '\0')
			break;
//		line_w[i] = this->pRecClass->RecPreShowCharacter(this->pRecClass,
//					x_start, pos_row[i], NULL, 1, 0, sParams_150[i]);
		RecTextOut(this, x_start, pos_row[i], sParams_150[i]);
		if (max_width < line_w[i])
		{
			max_width = line_w[i];
		}		
	}
	this->pRecClass->RecWriteIndexADD (this->pRecClass, max_width + 240);
	if (this->semaphore == FALSE)
	{
		GET_RECSTARTUP_PERMIT();
		this->semaphore = TRUE;
		RELEASE_STARTUP_PERMIT();
	}
}

/*******************************************************************************
函数名称:	VOID RecGetFetalParamEnd(VOID)
版本号:		1.0.0
生成日期:	2011.11.15
作者:		zondan
功能说明:	获取母婴打印时的参数信息
输入参数:	
输出参数:	
其它说明:	
*******************************************************************************/
VOID RecGetFetalParamEnd(VOID)
{
	CHAR	 tbuf[MAX_RECPARAMLINES_150];
	INT32	i;
	DATETIME end_time;
	
	for (i = 0; i < MAX_RECPARAMROWS_150; ++ i)
	{
		memset(sParams_150[i], 0, MAX_RECPARAMLINES_150);
	}

	// REAL TIME RECORDER
	strcpy(sParams_150[0], LoadString(STR_PRINT_TYPE_FETAL));
	strcpy(sParams_150[1], LoadString(STR_PRINT_TIME_END));
	
	if (MonitorConfig.language == CHINESE)
	{
		sprintf(sParams_150[2], "%04d-%02d-%02d",
			DateTime.year, DateTime.month, DateTime.day);
	}
	else
	{
		sprintf(sParams_150[2], "%02d-%02d-%04d",
			DateTime.month, DateTime.day, DateTime.year);
	}
	sprintf(sParams_150[3], "%02d:%02d:%02d",
		DateTime.hour, DateTime.minute, DateTime.second);
	strcpy(sParams_150[4], LoadString(STR_PRINT_TIME_TIMING));
	strcat (sParams_150[5], LoadString(Timer[RecFHRControl.rec_type]));
}


/*****************************************************************************************
函数名称:	VOID PrintCurTime (VOID)
版本号:		1.0.0
生成日期:	2011.11.15
作者:		zondan
功能说明:	2min定时时间到后，显示当前时间
输入参数:	
输出参数:	
其它说明:	
*****************************************************************************************/
VOID PrintCurTime (PRECEVENTCLASS this)
{
	UINT8  buff[50];
	INT32  width;
	INT32  start_x;
	INT32  y_pos;
	PLOGFONT pFont;
	memset(buff, 0, sizeof(buff));
	if (this->semaphore)
	{

		GET_RECSTARTUP_PERMIT();	
		this->semaphore = FALSE;
		RELEASE_STARTUP_PERMIT();
		//确保打印机已经关闭
		//ms_sleep(RECORD_DELAYTICKS);
	}
	sprintf(buff, "%02d:%02d", DateTime.hour, DateTime.minute);	
 	y_pos = RecConfig.regStar[PAPER_REG_FHR] + 2;
	pFont = (PLOGFONT)this->pRecClass->font_normal;
//	if (y_pos > RECORD_WIDTH_112 - pFont->size)
//		y_pos = RECORD_WIDTH_112 - pFont->size;
//	width = this->pRecClass->RecPreShowCharacter (this->pRecClass, 0, y_pos, 
//							NULL, 1, 0, buff);
	width = RecTextOut(this, 0, y_pos, buff);
	GET_RECSTARTUP_PERMIT();
	this->semaphore = TRUE;
	RELEASE_STARTUP_PERMIT();

}


/*******************************************************************************
* Function	: RecFhrGraph_112
* Description : 
* Input Para  : 
* Output Para : 
* Return Value: 
*******************************************************************************/
VOID RecFhrGraph_112(PRECEVENTCLASS this)
{
	INT32 ret;
	INT32 cnt = 0;
	
	GetPrintEndPrt(this->fetalAddData);
	while(ret = RecFetalUpdataBuff (this, 0))
	{
		PrintFetalGraph (this, ret);
	}
	if (this->semaphore == FALSE)
	{
		GET_RECSTARTUP_PERMIT();
		this->semaphore = TRUE;
		RELEASE_STARTUP_PERMIT();
	}
}


/*******************************************************************************
* Function	: RecFetalEnd
* Description : 
* Input Para  : 
* Output Para : 
* Return Value: 
*******************************************************************************/
VOID RecFetalEnd(PRECEVENTCLASS this)
{
	PRECFHRCONTROL pFhrCtrl = this->fetalAddData;	
	INT32  i;

	pFhrCtrl->isBegin	= FALSE; //关闭定时器

	//关闭打印机之后对控制结构体做相应的处理
	pFhrCtrl->elapseSec  = 0;
	pFhrCtrl->periodTime = 0;
	pFhrCtrl->pFHRStart  = NULL;
	pFhrCtrl->pFHREnd	= NULL;
	pFhrCtrl->pFHRHead   = NULL;
	pFhrCtrl->pFHRTail   = NULL;

	this->RecPutEndLine(this);
	//处理波形边界数值，为下一次打印做准备
	for (i = 0; i < 3; i++)
	{
		sLastWavedata[i] = -1;
	}	
}


/*******************************************************************************
* Function	: RecFhrElapseOneSec
* Description : 
* Input Para  : 
* Output Para : 
* Return Value: 
*******************************************************************************/
VOID RecFhrElapseOneSec (VOID)
{
	static UINT32 second = 0;
	PRECEVENTCLASS this = &RecEventClass;
	RecFHRControl.elapseSec ++;
	if (RecFHRControl.periodTime > 0) // 定时打印
	{

//		prinfo("RecGetReadIndex...%d, RecFHRControl.elapseSec...%d\r\n",
//			this->pRecClass->RecGraphInfo.readIndex, RecFHRControl.elapseSec);
		if (RecFHRControl.elapseSec >= RecFHRControl.periodTime)
		{

			RecFHRControl.timeover = TRUE;
		}  	
		if (RecFHRControl.timeover)
		{

			RecGetFetalParamEnd ();
			PrintFetalParamEnd (this);
			RecFetalEnd (this);
		}
	}

	if ((RecFHRControl.elapseSec % 60) == 5)
//		% (60 * RecFHRControl.recRate / FETAL_SAMPLE_RATE) == 5)
	{

		PrintCurTime (this);
	}
	if (RecFHRControl.elapseSec > 180 * 10,000,000)//保证在回绕的时候不会出现问题
    {
        RecFHRControl.elapseSec = RecFHRControl.periodTime;
    }
}


/*******************************************************************************
函数名称:	BOOL RecFetalStart (VOID)
版本号:		1.0.0
生成日期:	2011.11.15
作者:		zondan
功能说明:	开始打印胎监波形时的预处理
输入参数:	
输出参数:	
其它说明:	
*******************************************************************************/
VOID RecFetalStart (PRECEVENTCLASS this)
{
	INT32  i;
	PRECFHRCONTROL pFhrCtrl = this->fetalAddData;
	RecFetalInitPtr(pFhrCtrl);
#if MYFB_RECORD_DEBUG
	EnterStandby();
	fb_fillrect_ex(0, 0, 0, SCREEN_WIDTH, SCREEN_HIGH, 0, 0, 0);
#endif	
	RecGetParamPerFhr();
	RecSendParamPerFhr(this);
	pFhrCtrl->timeover  = FALSE;
	pFhrCtrl->elapseSec = 0;
	pFhrCtrl->isBegin   = TRUE;
}


extern void time2datetime(int t, DATETIME *dt);
/*******************************************************************************
* Function	: RecGetRecallParam
* Description : 胎监回顾打印信息
* Input Para  : 
* Output Para : 
* Return Value: 
*******************************************************************************/
static VOID RecGetRecallParam(PTRPARIENT this)
{
	CHAR	 tbuf[MAX_RECPARAMLINES_150];
	INT32	i = 0;
	INT32	j = 0;
	INT32	k;
	DATETIME dt;
	memset(sParams_150, 0, sizeof(sParams_150));
	if (this->info.patientName[0] != '\0')
	{
		sprintf(sParams_150[i++], "%s %s", LoadString(STR_PRINT_NAME),
				this->info.patientName);
	}
	else
	{
		sprintf(sParams_150[i++], "%s", LoadString(STR_PRINT_NAME));
	}
	if (this->info.patientID[0] != '\0')
	{
		sprintf(sParams_150[i++], "%s %s", LoadString(STR_PRINT_ID),
				this->info.patientID);
	}
	else
	{
		sprintf(sParams_150[i++], "%s", LoadString(STR_PRINT_ID));
	}
	if (this->info.patientAge > 1)
	{
		sprintf(sParams_150[i++], "%s %d", LoadString(STR_PRINT_AGE),
				this->info.patientAge);
	}
	else
	{
		sprintf(sParams_150[i++], "%s", LoadString(STR_PRINT_AGE));
	}
	if (this->info.gestationalWeeks > 19)
	{
		sprintf(sParams_150[i++], "%s %d/%d", LoadString(STR_PRINT_WEEK),
				this->info.gestationalWeeks, this->info.gestationalDay);
	}
	else
	{
		sprintf(sParams_150[i++], "%s   / ", LoadString(STR_PRINT_WEEK));
	}
	if (this->info.gestationalTimes > 0)
	{
		sprintf(sParams_150[i++], "%s %d", LoadString(STR_PRINT_TIMES),
				this->info.gestationalTimes);
	}
	else
	{
		sprintf(sParams_150[i++], "%s 1", LoadString(STR_PRINT_TIMES));	   
	}
	time2datetime(this->data.data[this->data.info[0].index].time, &dt);
	sprintf(sParams_150[i++], "%s %02d:%02d:%02d",
		LoadString(STR_PRINT_TIME_END), dt.hour, dt.minute, dt.second);
	sprintf(sParams_150[i++], "%s %d:%02d:%02d",
		LoadString(STR_PRINT_TIME_LENGTH), this->data.info[0].count / 3600,
		(this->data.info[0].count % 3600) / 60, this->data.info[0].count % 60);
	sprintf(sParams_150[i], "%s", LoadString(STR_PRINT_NOTE));
	if (this->info.note[j] != '\0')
	{
		memset(tbuf, '\0', sizeof(tbuf));
		k = MAX_RECPARAMLINES_150 - strlen(sParams_150[i]) - 1;
		strncpy(tbuf, &(this->info.note[j]), k);
		strcat(sParams_150[i],  tbuf);
		j += strlen(tbuf);
		k = MAX_RECPARAMLINES_150 - 1;
		if (strlen(&(this->info.note[j])) > strlen(tbuf))
		{
			for(i; i < MAX_RECPARAMROWS_150; i++)
			{
				strncpy(sParams_150[i], &(this->info.note[j]), k);
				if (strlen(sParams_150[i]) < k)
					break;
				j += strlen(sParams_150[i]);
				if (strlen(&(this->info.note[j])) == 0)
					break;
			}
		}
	}
}


/*****************************************************************************************
* Function	: RecPutRecallParam
* Description : 输出胎监回顾信息
* Input Para  : 
* Output Para : 
* Return Value: 
*****************************************************************************************/
static INT32 RecPutRecallParam (PRECEVENTCLASS this, INT32 start)
{
	int i, x, y, offset;
	int w, max;
	start += 20;
	x = start;
	max = 0;
	offset = RECPAPERWIDTH_112 / (MAX_RECPARAMROWS_150 + 1) * 8;
	y = offset;
	for (i = 0; i < MAX_RECPARAMROWS_150; i++)
	{
		w = RecTextOut(this, x, y, sParams_150[i]);
		if (max < w)
			max = w;
		y += offset;
	}
//	this->pRecClass->RecWriteIndexADD (this->pRecClass, max + 16);
	return (max + 16);
}

static PFETALDATA GetAnalysisStartDataPtr(INT32 endtime, INT32 second,
					PFETALDATA pHead, PFETALDATA pTail, PFETALDATA pEnd)
{
	int i;
	PFETALDATA pCurr = pHead;
#if 0
	prinfo("\n");
	for (i = 0; i < DATA_SAVE_LEN; i++)
	{
		if (pCurr->time == endtime)
		{
			pCurr = pCurr - second;
			if (pCurr < pHead)
			{
				pCurr = pTail - pHead + pCurr;
			}
			prinfo("\n");
			return pCurr;
		}
		pCurr++;
		if (pCurr > pTail)
			break;
	}
#endif
	for (i = 0; i < DATA_SAVE_LEN; i++)
	{
		if (pCurr->time == endtime - 1)
		{
			pCurr = pCurr - second;
			if (pCurr < pHead)
			{
				pCurr = pTail - pHead + pCurr;
			}
			return pCurr;
		}
		pCurr++;
		if (pCurr > pTail)
			break;
	}
	return NULL;
}

typedef struct __tagPutRecallGraphProcess
{
	INT32 buflen;
	INT32 len;
	INT32 currIndex;
	INT32 TimeYpos;
	INT32 AnalyYpos;
	INT32 EventYpos;
	INT32 FmFlagYpos;
	INT32 AfmFlagYpos;
	INT32 ZeroFlagYpos;
	INT32 LineThick;
	INT32 *pFhr1;
	INT32 *pFhr2;
	INT32 *pToco;
	INT32 *pAfm;
	UINT8 *pAnaly;
	UINT8 *pEvent;
	UINT8 *pFmFlag;
	UINT8 *pAfmFlag;
	UINT8 *pZeroFlag;
}TPRGP, *PTPRGP;

static BOOL PutRecallGraph_Process(PRECDRVCLASS this, INT32 *pp)
{
	BOOL ret = TRUE;
	if (pp && this)
	{
		INT32 sendlen = 400;
		INT32 readIndex = this->RecGetReadIndex(this);
		INT32 writeIndex = this->RecGetWriteIndex(this);
		INT32 tailIndex = this->RecGetTailIndex(this);
		INT32 remain;
		if (writeIndex > readIndex)
		{
			remain = writeIndex - readIndex;
		}
		else
		{
			remain = writeIndex + tailIndex + 1 - readIndex;
		}
//		printf("PutRecallGraph_Process::remain %d\n", remain);
		if (remain > sendlen)
			return FALSE;
		
		PTPRGP pTprgp = (PTPRGP)pp;
		int i, loops, x;
		STRINGID drMarkTypeStr[] = {
			STR_NULL,
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
		i = pTprgp->currIndex;
		loops = i + sendlen;
		if (loops >= pTprgp->len)
		{
			loops = pTprgp->len - 1;
			sendlen = loops - i + RECORD_112_ENDLEN * 3;
		}
		else
		{
			ret = FALSE;
		}
		pTprgp->currIndex = loops;
		x = 0;
		for (; i < loops; i++)
		{
			if ((ABS(pTprgp->pFhr1[i] - pTprgp->pFhr1[i+1]) < 50)
				&& (pTprgp->pFhr1[i+1] > 0))
			{
				this->RecPreLine(this, x, pTprgp->pFhr1[i], x + 1,
					pTprgp->pFhr1[i+1], pTprgp->LineThick);
			}
			if ((ABS(pTprgp->pFhr2[i] - pTprgp->pFhr2[i+1]) < 50)
				&& (pTprgp->pFhr2[i+1] > 0))
			{
				this->RecPreLine(this, x, pTprgp->pFhr2[i], x + 1,
					pTprgp->pFhr2[i+1], pTprgp->LineThick);
			}
			if (pTprgp->pToco[i] > 0)
			{
				this->RecPreLine(this, x, pTprgp->pToco[i], x + 1,
					pTprgp->pToco[i+1], pTprgp->LineThick);
			}
			if (pTprgp->pAfm[i] > 0)
			{
				this->RecPreLine(this, x, pTprgp->pAfm[i], x + 1,
					pTprgp->pAfm[i+1], pTprgp->LineThick);
			}
			if (pTprgp->pAnaly[i] > 0)
			{
//				this->RecPreShowCharacter(this, x, pTprgp->AnalyYpos, 
//					(PLOGFONT)this->font_cutter, 0, 0,
//					LoadString(AnalyStr[pTprgp->pAnaly[i]]));
			}
			if (pTprgp->pEvent[i] > 0)
			{
				this->RecPreShowCharacter(this, x, pTprgp->EventYpos, 
					(PLOGFONT)this->font_cutter, 0, 0,
					LoadString(drMarkTypeStr[pTprgp->pEvent[i]]));
			}
			if (pTprgp->pFmFlag[i] > 0)
			{
				this->RecDrawBitmap(this, x, pTprgp->FmFlagYpos,
					REC_ICON_UPARROW);
			}
			if (pTprgp->pAfmFlag[i] > 0)
			{
				this->RecDrawBitmap(this, x, pTprgp->AfmFlagYpos,
					REC_ICON_UPARROW);
			}
			if (pTprgp->pZeroFlag[i] > 0)
			{
				this->RecDrawBitmap(this, x, pTprgp->ZeroFlagYpos,
					REC_ICON_TOCOZERO);
			}
			x++;
		}
		this->RecWriteIndexADD(this, sendlen);
	}
	return ret;
}

static INT32 *PutRecallGraph_Init(INT32 *AddData)
{
	INT32 *p = NULL;
	INT32 *buf;
	INT32 len = AddData[2];
	INT32 bufSize = 0;
	// 4字节对齐,再乘于4(FETALDATA.wave[4])
	INT32 buflen = (((len + 3) >> 2) << 4); 
	bufSize += sizeof(TPRGP);//变量需要的内存
	bufSize += buflen * (sizeof(INT32) * 4 + sizeof(UINT8) * 5);//波形需要的内存
	buf = (INT32*)malloc(bufSize);
	if (buf)
	{
		p = buf;
		PTPRGP pTprgp = (PTPRGP)p;
		PRECEVENTCLASS pRecEvent = (PRECEVENTCLASS)AddData[0];
		
		PFETALDATA pHead = &(pRecEvent->prntFileAddData->data.data[0]);
		PFETALDATA pTail = 
			&(pRecEvent->prntFileAddData->data.data[DATA_SAVE_LEN - 1]);
		PFETALDATA pCurr = (PFETALDATA)AddData[1];
		PLOGFONT pFont = (PLOGFONT)pRecEvent->pRecClass->font_cutter;
		// 初始化变量
		pTprgp->buflen = bufSize;
		pTprgp->currIndex = 0;
		pTprgp->TimeYpos = RecConfig.regStar[PAPER_REG_FHR];
		pTprgp->EventYpos = RecConfig.regStar[PAPER_REG_FHR] + pFont->size + 8;
		pTprgp->AnalyYpos = (RecConfig.regEnd[PAPER_REG_FHR]
							+ RecConfig.regStar[PAPER_REG_FHR]) / 2;
		pTprgp->FmFlagYpos = RecConfig.regStar[PAPER_REG_TOCO];
		pTprgp->AfmFlagYpos = RecConfig.regStar[PAPER_REG_TOCO] + 40;
		pTprgp->ZeroFlagYpos = RecConfig.regEnd[PAPER_REG_TOCO] - 40;
		pTprgp->LineThick = 1;
		// 分配内存
		pTprgp->pFhr1 = (INT32*)PTR_ADD(p, sizeof(TPRGP));
		p = pTprgp->pFhr1;
		
		pTprgp->pFhr2 = (INT32*)PTR_ADD(p, sizeof(INT32) * buflen);
		p = pTprgp->pFhr2;
		
		pTprgp->pToco = (INT32*)PTR_ADD(p, sizeof(INT32) * buflen);
		p = pTprgp->pToco;
		
		pTprgp->pAfm = (INT32*)PTR_ADD(p, sizeof(INT32) * buflen);
		p = pTprgp->pAfm;
		
		pTprgp->pAnaly = (UINT8*)PTR_ADD(p, sizeof(INT32) * buflen);
		p = (INT32*)pTprgp->pAnaly;
		ZeroMemory(p, sizeof(UINT8) * buflen);//需要先清空内存,后面可能不会赋值
		
		pTprgp->pEvent = (UINT8*)PTR_ADD(p, sizeof(UINT8) * buflen);
		p = (INT32*)pTprgp->pEvent;
		ZeroMemory(p, sizeof(UINT8) * buflen);//需要先清空内存,后面可能不会赋值
		
		pTprgp->pFmFlag	= (UINT8*)PTR_ADD(p, sizeof(UINT8) * buflen);
		p = (INT32*)pTprgp->pFmFlag;
		
		pTprgp->pAfmFlag = (UINT8*)PTR_ADD(p, sizeof(UINT8) * buflen);
		p = (INT32*)pTprgp->pAfmFlag;
		
		pTprgp->pZeroFlag = (UINT8*)PTR_ADD(p, sizeof(UINT8) * buflen);
		// 将波形数据映射到分配好的内存
		INT32 top[4];
		INT32 bot[4];
		RecGetWavePos(top, bot);
		INT32 FhrMin[2] = { 30,  60};
		INT32 FhrMax[2] = {240, 210};
//		if (RecConfig.fhrMin == 1 && RecConfig.fhrMax == 1)
//		{
//			top[0] = RecConfig.regStar[PAPER_REG_FHR];
//			bot[0] = RecConfig.regEnd[PAPER_REG_FHR];
//		}
//		else
//		{
//			INT32 start = RecConfig.regStar[PAPER_REG_FHR];
//			INT32 end = RecConfig.regEnd[PAPER_REG_FHR];
//			INT32 offset = ABS((end - start) * 30
//				/ (FhrMax[RecConfig.fhrMax] - FhrMin[RecConfig.fhrMin]));
//			top[0] = start - offset * (1 - RecConfig.fhrMax);
//			bot[0] = end + offset * (1 - RecConfig.fhrMin);
//		}
//		top[1] = top[0];
//		bot[1] = bot[0];
//		top[2] = RecConfig.regStar[PAPER_REG_TOCO];
//		bot[2] = RecConfig.regEnd[PAPER_REG_TOCO];
//		top[3] = top[2];
//		bot[3] = bot[2] - (bot[2] - top[2]) * 2 / 5;
		pTprgp->AfmFlagYpos = bot[3];
		int i, j, k;
		k = 0;
		for (i = 0; i < len; i++)
		{
			pTprgp->pAnaly[k] = pCurr->analysis;
			pTprgp->pEvent[k] = pCurr->event;
			for (j = 0; j < 4; j++)
			{
				pTprgp->pFhr1[k] = pCurr->wave[j].fhr1;
				pTprgp->pFhr2[k] = pCurr->wave[j].fhr2;
				pTprgp->pToco[k] = pCurr->wave[j].toco;
				pTprgp->pAfm[k] = pCurr->wave[j].afm;
				pTprgp->pFmFlag[k] = pCurr->wave[j].fmbits;
				pTprgp->pAfmFlag[k] = pCurr->wave[j].afmbits;
				pTprgp->pZeroFlag[k] = pCurr->wave[j].zerobits;
				k++;
			}
			if (++pCurr > pTail)
			{
				pCurr = pHead;
			}
		}
		pTprgp->len = k;
		//根据打印纸上波形区域的高度对波形数据进行增益调节
		RecScaleWave(top[0], bot[0], FhrMin[RecConfig.fhrMin],
						FhrMax[RecConfig.fhrMax], pTprgp->pFhr1, k);
		RecScaleWave(top[1], bot[1], FhrMin[RecConfig.fhrMin],
						FhrMax[RecConfig.fhrMax], pTprgp->pFhr2, k);
		RecScaleWave(top[2], bot[2], 0, 100, pTprgp->pToco, k);
		RecScaleWave(top[3], bot[3], 0, 40, pTprgp->pAfm, k);
	}
	return buf;
}

static VOID TrusteeshipRecallGraph(PRECDRVCLASS this, INT32 *AddData)
{
	static INT32 *pp = NULL;// 所有托管数据都保存在申请的内存里,仅有一个静态变量
	if (this != NULL)
	{
		if (AddData)
		{
			// 执行初始化,分配资源
			INT32 len = AddData[2];
			if (AddData[0] && AddData[1] && (AddData[2] > 0))
			{
				// 传入附加数据有效,分配所需的内存
				pp = PutRecallGraph_Init(AddData);
				// 加载
				this->RecTrusteeship = TrusteeshipRecallGraph;
				return;
			}
		}
		if(pp)
		{
			if (TRUE ==PutRecallGraph_Process(this, pp))
			{
				// 自动卸载
				this->RecTrusteeship = NULL;
				this = NULL;
			}
		}
		else
		{
			this = NULL;
		}
	}
	if (this == NULL)
	{
		// 释放资源
		if (pp)
			free(pp);
		pp = NULL;
		if (AddData)
		{
			// 外部卸载
			PRECEVENTCLASS pEvent = (PRECEVENTCLASS)AddData;
			pEvent->pRecClass->RecTrusteeship = NULL;
		}
	}
}

/*******************************************************************************
* Function	: RecPutRecallGraph
* Description : 将指定的胎监波形数据输出到打印机,不能一次生成全部位图,需要分次
* Input Para  : 
* Output Para : 
* Return Value: 
*******************************************************************************/
static VOID RecPutRecallGraph (PRECEVENTCLASS this, PFETALDATA pdata, INT32 len)
{
	if (this->pRecClass->RecTrusteeship)
		return;
	INT32 addData[3] = {(INT32)this, (INT32)pdata, len};
	GET_RECDATA_PERMIT();
	TrusteeshipRecallGraph(this->pRecClass, addData);
	RELEASE_RECDATA_PERMIT();
	return;
}

static VOID RecPutRecallAnalyWave(PRECEVENTCLASS this)
{
	INT32 len = this->prntFileAddData->data.info[0].count;
	INT32 index = this->prntFileAddData->data.info[0].index;
	PFETALDATA pdata = &(this->prntFileAddData->data.data[index]);
	PFETALDATA pHead = &(this->prntFileAddData->data.data[0]);
	PFETALDATA pTail = &(this->prntFileAddData->data.data[DATA_SAVE_LEN - 1]);

	if (this->prntFileAddData->ansis.len == 0)
	{
		return;
	}
	
	switch (this->prntFileAddData->ansis.type)
	{
		case 1:
		{
			ARET_SAVE *pNst = (ARET_SAVE*)this->prntFileAddData->ansis.buffer;
			pdata = GetAnalysisStartDataPtr(pNst->endtime, pNst->second,
											pHead, pTail, pdata);
			if (NULL == pdata)
				return;
			RecPutRecallGraph(this, pdata, pNst->second);
		}
			break;

		default:
			return;
	}
}

static VOID RecPutRecallAllWave(PRECEVENTCLASS this)
{
	PFETALDATA pdata;
	INT32 len = this->prntFileAddData->data.info[0].count;
	INT32 index = this->prntFileAddData->data.info[0].index;
	if (DATA_SAVE_LEN == len)
	{
		index = (index + 1) % DATA_SAVE_LEN;
	}
	else
	{
		index = 0;
	}
	pdata = &(this->prntFileAddData->data.data[index]);
	RecPutRecallGraph(this, pdata, len);
}
//打印CST表格
static INT32 PrintCSTResult(PRECEVENTCLASS this,INT32 *X,INT32 *Y,ARET_SAVE *pResult)
{
	INT16 w,h,x,y,x1,y1,w_add,thick;
	x1 = *X;
	y1 = *Y;
	x = x1;
	y = y1;
	w = 120;
	h = 62;
	thick = 1;
	UCHAR txt[64];
	w_add=(MonitorConfig.language == RUSSIAN)?230:0;
	
	//从上到下是 项目 胎心基线 振幅摆动 频率摆动 加速 减速 
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ITEMS));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FHR_BASE));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_AMPLITUDE_VAR));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_PERIOD_VAR));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ACCELRATION));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_SLOWDOWN));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	//从上到下是 0分 >100,<180 <5 <2 无 晚期+其它
	x1 += w+w_add;
	y1 = y;
	sprintf(txt, "0");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "<100,>180");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "<5");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "<2");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_NOTHING));
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "%s",LoadString(STR_DLG_ANLS_LDOROTHER));
	RecTextOC(this, x1, y1, w, h, txt);
	//从上到下是 1分 100~119,161~180 5-9,>25 周期性 变异
	x1 += w;
	y1 = y;
	sprintf(txt, "1");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "100~119,161~180");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "5-9,>25");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "2-6");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "%s",LoadString(STR_DLG_ANLS_ACCELRATION_TYPE1));
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "%s",LoadString(STR_DLG_ANLS_CHANGE));
	RecTextOC(this, x1, y1, w, h, txt);
	//从上到下是 2分 120~160 "10-25" ">6" 散在性 无
	x1 += w;
	y1 = y;
	sprintf(txt, "2");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "120-160");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "10-25");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, ">6");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "%s",LoadString(STR_DLG_ANLS_ACCELRATION_TYPE2));
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_NOTHING));
	RecTextOC(this, x1, y1, w, h, txt);
	//从上到下是 本例结果 结果1 结果2 结果3
	x1 += w;
	y1 = y;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_RESULT));
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	if (pResult->fhr_JX)
		sprintf(txt, "%d", pResult->fhr_JX);
	else
		strcpy(txt, "--");
	RecTextOC(this, x1, y1, w, h, txt);
	//振幅
	y1 += h;
	if (pResult->fhr_ZV)
		sprintf(txt, "%d", pResult->fhr_ZV);
	else
		strcpy(txt, "--");
	RecTextOC(this, x1, y1, w, h, txt);
	
	y1 += h;//周期
	if (pResult->fhr_QV)
		sprintf(txt, "%d", pResult->fhr_QV);
	else
		strcpy(txt, "--");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;//加速
	if (pResult->tdfast)//
		if(pResult->fastType == 1)//周期性
			sprintf(txt, "%d,%s",pResult->tdfast, LoadString(STR_DLG_ANLS_ACCELRATION_TYPE1));
		else if(pResult->fastType == 2)//散在性
			sprintf(txt, "%d,%s",pResult->tdfast,LoadString(STR_DLG_ANLS_ACCELRATION_TYPE2));
		else
			strcpy(txt, "--");
	else
		sprintf(txt, "%s", LoadString(STR_DLG_ANLS_NOTHING));
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;//减速
	if (pResult->tdslow)
		if(pResult->slowType == 1)//晚期减速
			sprintf(txt, "%s", LoadString(STR_DLG_ANLS_LASTSLOW));
		else if(pResult->slowType == 2)//早期减速
			sprintf(txt, "%s", LoadString(STR_DLG_ANLS_EDSLOW));
		else if(pResult->slowType == 3)//变异
			sprintf(txt, "%s", LoadString(STR_DLG_ANLS_CHANGE));
		else
			strcpy(txt, "--");
	else
		sprintf(txt, "%s", LoadString(STR_DLG_ANLS_NOTHING));
	RecTextOC(this, x1, y1, w, h, txt);
	//画表格 先横后竖
	y1 = y;
	x1 += w;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	//竖线
	x1 = x;	
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	x1 += (w+w_add);
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	x1 += w;
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	x1 += w;
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	x1 += w;
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	x1 += w;
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	*X = x1;
	*Y = y1;
}

//打印FisCher表格
static INT32 PrintFisCherResult(PRECEVENTCLASS this,INT32 *X,INT32 *Y,ARET_SAVE *pResult)
{
	//printf("打印FisCher表格\n");
	INT16 w,h,x,y,x1,y1,w_add,thick;
	x1 = *X;
	y1 = *Y;
	x = x1;
	y = y1;
	w = 120;
	h = 62;
	thick = 1;
	UCHAR txt[64];
	w_add=(MonitorConfig.language == RUSSIAN)?230:0;
	//从上到下是 项目 胎心率基线 振幅变异 周期变异  加速 减速
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ITEMS));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_BASE_LINE));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_AMPLITUDE_VAR));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_PERIOD_VAR));
								  
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ACCELRATION));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_SLOWDOWN));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	//从上到下是 0分  <100,>180   <5   <2   无   LD,>=8
	x1 += w+w_add;
	y1 = y;
	sprintf(txt, "0");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "<100,>180");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "<5");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "<2");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ACCELRATION_TYPE0));
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "%s",LoadString(STR_DLG_ANLS_SLOWDOWN_TYPE0));
	RecTextOC(this, x1, y1, w, h, txt);
	//从上到下是 1分  100~119\n161~180   5~9,>30   2~6  1~4 4~7,VD 
	x1 += w;
	y1 = y;
	sprintf(txt, "1");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "100~119,161~180");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "5~9,>30");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "2-6");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "1~4");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "4~7,VD");
	RecTextOC(this, x1, y1, w, h, txt);
	//从上到下是 2分  120~160   10~30   >6  >4 无,其他
	x1 += w;
	y1 = y;
	sprintf(txt, "2");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "120-160");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "10-30");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, ">6");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, ">4");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_SLOWDOWN_TYPE2));
	RecTextOC(this, x1, y1, w, h, txt);
	//从上到下是 本例结果 结果1 结果2 结果3
	x1 += w;
	y1 = y;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_RESULT));
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	if (pResult->fhr_JX)
		sprintf(txt, "%d", pResult->fhr_JX);
	else
		strcpy(txt, "--");
	RecTextOC(this, x1, y1, w, h, txt);
	//振幅
	y1 += h;
	if (pResult->fhr_ZV)
		sprintf(txt, "%d", pResult->fhr_ZV);
	else
		strcpy(txt, "--");
	RecTextOC(this, x1, y1, w, h, txt);
	
	y1 += h;//周期
	if (pResult->fhr_QV)
		sprintf(txt, "%d", pResult->fhr_QV);
	else
		strcpy(txt, "--");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;//加速
	sprintf(txt, "%d", pResult->tdfast);
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;//减速
	if (pResult->tdslow)
		if(pResult->slowType == 1)//晚期减速
			sprintf(txt, "%d,LD",pResult->tdslow);//, LoadString(STR_DLG_ANLS_LASTSLOW));
		else if(pResult->slowType == 2)//早期减速
			sprintf(txt, "%d,ED",pResult->tdslow);//, LoadString(STR_DLG_ANLS_EDSLOW));
		else if(pResult->slowType == 3)//变异
			sprintf(txt, "%d,VD",pResult->tdslow);//, LoadString(STR_DLG_ANLS_CHANGE));
		else
			sprintf(txt, "%d",pResult->tdslow);
	else
		sprintf(txt, "%s", LoadString(STR_DLG_ANLS_NOTHING));
	RecTextOC(this, x1, y1, w, h, txt);
	//画表格 先横后竖
	y1 = y;
	x1 += w;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	//竖线
	x1 = x;	
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	x1 += (w+w_add);
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	x1 += w;
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	x1 += w;
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	x1 += w;
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	x1 += w;
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	*X = x1;
	*Y = y1;
}
//打印Krebs表格
static INT32 PrintKrebsResult(PRECEVENTCLASS this,INT32 *X,INT32 *Y,ARET_SAVE *pResult)
{
	//printf("打印Krebs表格\n");
	INT16 w,h,x,y,x1,y1,w_add,thick;
	x1 = *X;
	y1 = *Y;
	x = x1;
	y = y1;
	w = 120;
	h = 62;
	thick = 1;
	UCHAR txt[64];
	w_add=(MonitorConfig.language == RUSSIAN)?230:0;
	//从上到下是 项目 心率基线 振幅变异 周期变异 加速 减速 胎动 
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ITEMS));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FHR_BASE));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_AMPLITUDE_VAR));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_PERIOD_VAR));
								  
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ACCELRATION));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_SLOWDOWN));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FETALMOVIE));
	RecTextOC(this, x1, y1, w+w_add, h, txt);
	//从上到下是 0分  <100,>180   <5   <3  无 >=2  0  
	x1 += w+w_add;
	y1 = y;
	sprintf(txt, "0");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "<100,>180");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "<5");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "<3");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_NOTHING));
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, ">=2");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "0");
	RecTextOC(this, x1, y1, w, h, txt);
	//从上到下是 1分  100~119,161~180 5~9,>25 3~6 1~4 1 1~4
	x1 += w;
	y1 = y;
	sprintf(txt, "1");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "100~119,161~180");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "5~9,>25");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "3-6");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "1~4");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "1");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "1~4");
	RecTextOC(this, x1, y1, w, h, txt);
	//从上到下是 2分  
	x1 += w;
	y1 = y;
	sprintf(txt, "2");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "120-160");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "10-25");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, ">6");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, ">4");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_NOTHINGORED));
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	sprintf(txt, ">4");
	RecTextOC(this, x1, y1, w, h, txt);
	//从上到下是 本例结果  结果1 结果2 结果3 结果4 结果5
	x1 += w;
	y1 = y;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_RESULT));
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;
	if (pResult->fhr_JX)//基线
		sprintf(txt, "%d", pResult->fhr_JX);
	else
		strcpy(txt, "--");
	RecTextOC(this, x1, y1, w, h, txt);
	//振幅
	y1 += h;
	if (pResult->fhr_ZV)
		sprintf(txt, "%d", pResult->fhr_ZV);
	else
		strcpy(txt, "--");
	RecTextOC(this, x1, y1, w, h, txt);
	
	y1 += h;//周期
	if (pResult->fhr_QV)
		sprintf(txt, "%d", pResult->fhr_QV);
	else
		strcpy(txt, "--");
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;//加速
	sprintf(txt, "%d", pResult->tdfast);
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;//减速
	//----------
	if ((pResult->tdslow) && (pResult->slowType == 2))//早期减速
		sprintf(txt, "%d,ED", pResult->tdslow);
	else
		sprintf(txt, "%d", pResult->tdslow);
	//----------
	RecTextOC(this, x1, y1, w, h, txt);
	y1 += h;	//胎动
	sprintf(txt, "%d", pResult->fm_nr);
	RecTextOC(this, x1, y1, w, h, txt);
	//画表格 先横后竖
	y1 = y;
	x1 += w;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	y1 += h;
	this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
	//竖线
	x1 = x;	
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	x1 += (w+w_add);
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	x1 += w;
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	x1 += w;
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	x1 += w;
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	x1 += w;
	this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
	*X = x1;
	*Y = y1;
}

/*******************************************************************************
* Function	: RecPutRecallAnaly
* Description : 将指定的胎监分析结果输出到打印机
* Input Para  : 
* Output Para : 
* Return Value: 
*******************************************************************************/
static INT32 RecPutRecallAnaly (PRECEVENTCLASS this, INT32 start)
{
	
//	this->pRecClass->RecPreShowCharacter(this->pRecClass, )
	PTRPARIENT pFile = this->prntFileAddData;
	if (pFile == NULL)
		return start;
	if (pFile->ansis.len == 0)
		return start;

	start += 40;
	INT32 x = start;
	//INT32 y = 0;
	INT32 y = 100;

	INT32 h, w, x1, y1, x2, y2;
	INT32 thick = 1;
	UCHAR txt[64];
	RECT rc;
    INT32 w_add=0;
	x1 = x + RecTextOut(this, x, y, LoadString(STR_PRINT_NAME));
	
	if (pFile->info.patientName[0] != '\0' )
	{
		RecTextOut(this, x1, y, pFile->info.patientName);
	}
	x += 300;
	x1 = x + RecTextOut(this, x, y, LoadString(STR_PRINT_ID));
	if (pFile->info.patientName[0] != '\0' )
	{
		RecTextOut(this, x1, y, pFile->info.patientID);
	}
	x += 300;
	if (pFile->info.patientAge > 1)
	{
		sprintf(txt, "%s %2d", LoadString(STR_PRINT_AGE), pFile->info.patientAge);
	}
	else
	{
		sprintf(txt, "%s   ", LoadString(STR_PRINT_AGE));
	}
	RecTextOut(this, x, y, txt);
	x += 160;
	if (pFile->info.gestationalTimes < 1)
	{
		sprintf(txt, "%s  ", LoadString(STR_PRINT_TIMES));
	}
	else
	{
		sprintf(txt, "%s %d", LoadString(STR_PRINT_TIMES),
			pFile->info.gestationalTimes);
	}
	RecTextOut(this, x, y, txt);
	x += 160;
	if (pFile->info.gestationalWeeks > 20)
	{
		sprintf(txt, "%s %2d/%d", LoadString(STR_PRINT_WEEK),
			pFile->info.gestationalWeeks, pFile->info.gestationalDay);
	}
	else
	{
		sprintf(txt, "%s   /  ", LoadString(STR_PRINT_WEEK));
	}
	RecTextOut(this, x, y, txt);

    //针对俄语调整打印宽度
	if (MonitorConfig.language == RUSSIAN)
	{
       w_add=230;
	}

	x2 = x + 160+w_add;
	x = start;
	y += 50;
	this->pRecClass->RecPreLine(this->pRecClass, x, y, x2, y, thick);
	
	y += 20;
	h = 62;
	w = 120;
	x1 = x;
	y1 = y;
	ARET_SAVE *pResult = (ARET_SAVE*)pFile->ansis.buffer;
	//打印NST方法
	if (FhrConfig.defaultAnalyType == 1)//NST评分法
	{	//printf("打印NST方法\n");
		this->pRecClass->RecPreLine(this->pRecClass, x, y1, x, y1, thick);
		sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ITEMS));
		RecTextOC(this, x1, y1, w+w_add, h, txt);
		y1 += h;
		sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FHR_BASE));
		RecTextOC(this, x1, y1, w+w_add, h, txt);
		y1 += h;
		sprintf(txt, "%s", LoadString(STR_DLG_ANLS_AMPLITUDE));
		RecTextOC(this, x1, y1, w+w_add, h, txt);
		y1 += h;
		sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FAST_TIME));
		RecTextOC(this, x1, y1, w+w_add, h, txt);
		y1 += h;
		sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FAST_AMPL));
		RecTextOC(this, x1, y1, w+w_add, h, txt);
		y1 += h;
		sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FM_TIMES));
		RecTextOC(this, x1, y1, w+w_add, h, txt);
		x1 += w+w_add;
		y1 += h;
		this->pRecClass->RecPreLine(this->pRecClass, x, y, x, y1, thick);
		this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
		y1 = y;
		sprintf(txt, "0");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		sprintf(txt, "<100");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		sprintf(txt, "<5");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		sprintf(txt, "<10");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		sprintf(txt, "<10");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		sprintf(txt, "0");
		RecTextOC(this, x1, y1, w, h, txt);
		x1 += w;
		y1 += h;
		this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
		y1 = y;
		sprintf(txt, "1");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		sprintf(txt, "100-119,  >160");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		sprintf(txt, "5-9,>30");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		sprintf(txt, "10-14");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		sprintf(txt, "10-14");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		sprintf(txt, "1-2");
		RecTextOC(this, x1, y1, w, h, txt);
		x1 += w;
		y1 += h;
		this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
		y1 = y;
		sprintf(txt, "2");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		sprintf(txt, "120-160");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		sprintf(txt, "10-30");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		sprintf(txt, ">=15");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		sprintf(txt, ">=15");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		sprintf(txt, ">3");
		RecTextOC(this, x1, y1, w, h, txt);
		x1 += w;
		y1 += h;
		this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
		y1 = y;
		sprintf(txt, "%s", LoadString(STR_DLG_ANLS_RESULT));
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		if (pResult->fhr_JX)
			sprintf(txt, "%d", pResult->fhr_JX);
		else
			strcpy(txt, "--");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		if (pResult->fhr_ZV)
			sprintf(txt, "%d", pResult->fhr_ZV);
		else
			strcpy(txt, "--");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		if (pResult->fasttime)
			sprintf(txt, "%d", pResult->fasttime);
		else
			strcpy(txt, "--");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		if (pResult->fasthigh)
			sprintf(txt, "%d", pResult->fasthigh);
		else
			strcpy(txt, "--");
		RecTextOC(this, x1, y1, w, h, txt);
		y1 += h;
		if (pResult->fm_nr)
			sprintf(txt, "%d", pResult->fm_nr);
		else
			strcpy(txt, "--");
	//	printf("pResult->fm_nr=%d ,pResult->fm_nr= %u\n",pResult->fm_nr,pResult->fm_nr);
		RecTextOC(this, x1, y1, w, h, txt);
		x1 += w;
		y1 += h;
		this->pRecClass->RecPreLine(this->pRecClass, x1, y, x1, y1, thick);
		
		y1 = y;
		this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
		y1 += h;
		this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
		y1 += h;
		this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
		y1 += h;
		this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
		y1 += h;
		this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
		y1 += h;
		this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
		y1 += h;
		this->pRecClass->RecPreLine(this->pRecClass, x, y1, x1, y1, thick);
		sprintf(txt, "%s", LoadString(STR_DLG_ANLS_NAME));
	}
	else if (FhrConfig.defaultAnalyType == 2)
	{
		PrintFisCherResult(this,&x1,&y1,pResult);
		sprintf(txt, "%s", LoadString(STR_DLG_ANLS_FISCHER));
	}
	else if (FhrConfig.defaultAnalyType == 3)
	{
		PrintKrebsResult(this,&x1,&y1,pResult);
		sprintf(txt, "%s", LoadString(STR_DLG_ANLS_KREBS));
	}
	else if (FhrConfig.defaultAnalyType == 4)
	{
		PrintCSTResult(this,&x1,&y1,pResult);
		sprintf(txt, "%s", LoadString(STR_DLG_ANLS_CST));
	}
	/////////表格的内容到此为止，以下部分又是固定的了
	y2 = y1;
	y1 = y + 20;
	x1 += 40;
	RecTextOut(this, x1, y1, txt);
	y1 += h;
	sprintf(txt, "%s %4d:%02d", LoadString(STR_DLG_ANLS_TIME),
		pResult->second / 60, pResult->second % 60);
	RecTextOut(this, x1, y1, txt);
	y1 += h;
	sprintf(txt, "%s %d%%", LoadString(STR_DLG_ANLS_VALID), pResult->vld_pct);
	RecTextOut(this, x1, y1, txt);
	y1 += h;
	
	struct tm *plocal_time;
	UINT32 time = pResult->endtime - pResult->second;
	plocal_time = localtime((const time_t *)&time);
	sprintf(txt, "%s: %02d:%02d:%02d", LoadString(STR_PRINT_TIME_START), 
		plocal_time->tm_hour, plocal_time->tm_min, plocal_time->tm_sec);
	RecTextOut(this, x1, y1, txt);
	y1 += h;
	
	plocal_time = localtime((const time_t *)&(pResult->endtime));
	sprintf(txt, "%s: %02d:%02d:%02d", LoadString(STR_PRINT_TIME_END), 
		plocal_time->tm_hour, plocal_time->tm_min, plocal_time->tm_sec);
	RecTextOut(this, x1, y1, txt);
	y1 += h;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_ANALYSIS_RESULT));
	RecTextOut(this, x1, y1, txt);
	
	x1 = x;
	y = y2 + 20;
	sprintf(txt, "%s",LoadString(STR_DLG_ANLS_DIAGNOSIS));
	RecTextOut(this, x1, y, txt);
	
	x1 = x;
	y = y2 + 60;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_DIAGNOSIS));
	RecTextOut(this, x1, y, txt);
	x1 = ((x2 >> 2) << 1);
	y = RecConfig.regEnd[PAPER_REG_TOCO] - 40;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_SIGNATURE));
	RecTextOut(this, x1, y, txt);
	x1 = x2 * 3 / 4;
	sprintf(txt, "%s", LoadString(STR_DLG_ANLS_DATE));
	RecTextOut(this, x1, y, txt);
//	this->pRecClass->RecWriteIndexADD(this->pRecClass, x2 + 40);
	return (x2 + 40);
}

/*******************************************************************************
* Function	: RecRecallPageStart
* Description : 胎监记录打印当前页
* Input Para  : 
* Output Para : 
* Return Value: 
*******************************************************************************/
VOID RecRecallPageStart (PRECEVENTCLASS this)
{
	PTRPARIENT pRecall = this->prntFileAddData;
	INT32 start = 0;
	RecGetRecallParam(pRecall);
	start = RecPutRecallParam(this, start);
	start = RecPutRecallAnaly(this, start);
	this->pRecClass->RecWriteIndexADD(this->pRecClass, start);
	RecPutRecallAnalyWave(this);// 改为打印胎监分析区域波形
}

/*******************************************************************************
* Function	: RecRecallAllStart
* Description : 胎监记录打印全部
* Input Para  : 
* Output Para : 
* Return Value: 
*******************************************************************************/
VOID RecRecallAllStart (PRECEVENTCLASS this)
{
	PTRPARIENT pRecall = this->prntFileAddData;
	INT32 start = 0;
	RecGetRecallParam(pRecall);
	start = RecPutRecallParam(this, start);
	start = RecPutRecallAnaly(this, start);
	this->pRecClass->RecWriteIndexADD(this->pRecClass, start);
	RecPutRecallAllWave(this);
}
#endif

