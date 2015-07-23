/*****************************************************************************************
版权所有:			和心重典
版本号:				1.0.0
生成日期:			2011.04.15
文件名:				
作者:				和心重典
功能说明:			
其它说明:			无
所属文件关系:		本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*****************************************************************************************/
#define   DISPPARA_GLOBALS 
#include  "includes.h"

#ifndef INITVALUE
#define INITVALUE	   -50
#endif

#ifndef NOVALUE
#define NOVALUE		-100
#endif

enum {
	DISP_GRP_FIRST,
	DISP_FHR1_GRP = DISP_GRP_FIRST,
	DISP_FHR2_GRP,
	DISP_TOCO_GRP,
	DISP_FETALMOVE_GRP,
	DISP_GRP_MAX
};

enum {
	DISP_FHR1_FIRST,
	DISP_FHR1 = DISP_FHR1_FIRST,
	DISP_FHR1_VAL,
	DISP_FHR1_SIGN,
	DISP_FHR1_ALARM,
	DISP_FHR1_MAX
};
enum {
	DISP_FHR2_FIRST,
	DISP_FHR2 = DISP_FHR2_FIRST,
	DISP_FHR2_VAL,
	DISP_FHR2_SIGN,
	DISP_FHR2_ALARM,
	DISP_FHR2_MAX
};
enum {
	DISP_FM_FIRST,
	DISP_FM = DISP_FM_FIRST,
	DISP_FM_VAL,
	DISP_FM_MAX
};
enum {
	DISP_TOCO_FIRST,
	DISP_TOCO = DISP_TOCO_FIRST,
	DISP_TOCO_VAL,
	
	DISP_TOCO_MAX
};

static ALL_PARAMS   LastParams;		  //最近一次的全局生理参数值.
static ALL_PARAMS   Disp_AllParams;	  //拷贝的用于显示的全局生理参数值.

static POINT ParamCtrlGroupPos[DISP_GRP_MAX][FACE_MAX] = {
	{ { PARAM_LEFT,  30 }, { 100,  29 }, { PARAM_LEFT,  30 }, {  10, 130 } }, // DISP_FHR1_GRP
	{ { PARAM_LEFT, 114 }, { 400,  29 }, { PARAM_LEFT,  30 }, {  10, 130 } }, // DISP_FHR2_GRP
	{ { PARAM_LEFT, 198 }, { 100, 229 }, { PARAM_LEFT, 130 }, { 270, 130 } }, // DISP_TOCO_GRP
	{ { PARAM_LEFT, 282 }, { 400, 229 }, { PARAM_LEFT, 230 }, { 530, 130 } }  // DISP_FETALMOVE_GRP
};
static SIZE ParamCtrlGroupSIZE[DISP_GRP_MAX][FACE_MAX] = {
	{ { PARAM_WIDTH,  82 }, { 300, 200 }, { PARAM_WIDTH,  90 }, { 260, 200 } }, // DISP_FHR1_GRP
	{ { PARAM_WIDTH,  82 }, { 300, 200 }, { PARAM_WIDTH,  90 }, { 260, 200 } }, // DISP_FHR2_GRP
	{ { PARAM_WIDTH,  82 }, { 300, 200 }, { PARAM_WIDTH,  90 }, { 260, 200 } }, // DISP_TOCO_GRP
	{ { PARAM_WIDTH,  82 }, { 300, 200 }, { PARAM_WIDTH,  90 }, { 260, 200 } }  // DISP_FETALMOVE_GRP
};
static RESID ParamCtrlGroupID[DISP_GRP_MAX] = {
	IDC_MAIN_PARAM_FHR1_G,
	IDC_MAIN_PARAM_FHR2_G,
	IDC_MAIN_PARAM_TOCO_G,
	IDC_MAIN_PARAM_FM_G
};

// DISP_FHR1_GRP,
// DISP_FHR2_GRP,
// DISP_FETALMOVE_GRP,
// DISP_TOCO_GRP,
static POINT Fhr1_CtrlPos[DISP_FHR1_MAX];
static POINT Fhr1ParamCtrlPos[DISP_FHR1_MAX][FACE_MAX] = {
	 {{   3,   3 },{   5,   5 }, {   3,   3 },{   5,   5 }}	// DISP_FHR1
	,{{  10,  19 },{  40,  30 }, {  10,  25 },{  10,  30 }}	// DISP_FHR1_VAL
	,{{  40,   3 },{  40,   5 }, {  40,   3 },{  40,   5 }}	// DISP_FHR1_SIGN
	,{{  60,   3 },{  60,   5 }, {  60,   3 },{  60,   5 }}	// DISP_FHR1_ALARM
};
static SIZE Fhr1ParamItemSize[DISP_FHR1_MAX][FACE_MAX] = {
	  {{  33,  17 },{  33,  17 }, {  33,  20 },{  33,  20 }}	// DISP_FHR1
	 ,{{ 121,  61 },{ 241, 121 }, { 121,  64 },{ 241, 128 }}	// DISP_FHR1_VAL
	 ,{{  16,  17 },{  16,  17 }, {  16,  20 },{  16,  20 }}	// DISP_FHR1_SIGN
	 ,{{  17,  17 },{  17,  17 }, {	 17,  17 },{  17,  17 }}	// DISP_FHR1_ALARM
};
static INT8 Fhr1ParamItemFont[DISP_FHR1_MAX][FACE_MAX] = {
       //panhonghui,改变字体大小
	  { SYSLOGFONT_NOR_RUS,		SYSLOGFONT_NOR_RUS,		SYSLOGFONT_NOR_RUS,		SYSLOGFONT_NOR_RUS	  }	// DISP_FHR1

	 // { SYSLOGFONT_FIXED,		SYSLOGFONT_FIXED,		SYSLOGFONT_FIXED,		SYSLOGFONT_FIXED	  }	// DISP_FHR1
	 ,{ SYSLOGFONT_BIG_PARAM,	SYSLOGFONT_HUGE_PARAM,	SYSLOGFONT_BIG_PARAM,	SYSLOGFONT_HUGE_PARAM }	// DISP_FHR1_VAL
	 ,{ SYSLOGFONT_BIG_PARAM,	SYSLOGFONT_HUGE_PARAM,	SYSLOGFONT_BIG_PARAM,	SYSLOGFONT_HUGE_PARAM }	// DISP_FHR1_VAL
	 ,{ SYSLOGFONT_DEF_ASC,		SYSLOGFONT_DEF_ASC,		SYSLOGFONT_DEF_ASC,		SYSLOGFONT_DEF_ASC }	// DISP_FHR1_VAL
};
static RESID Fhr1Param_CtrlID[DISP_FHR1_MAX] = {
	IDC_MAIN_PARAM_FHR1_NAME,	// DISP_FHR1
	IDC_MAIN_PARAM_FHR1_PARAM,	// DISP_FHR1_VAL
	IDC_MAIN_PARAM_FHR1_SIGN,
	IDC_MAIN_PARAM_FHR1_ALARM
};
static STRINGID Fhr1ParamCaption[DISP_FHR1_MAX] = {
	STR_MAIN_PARAM_FHR1,		// DISP_FHR1
	STR_MAIN_PARAM_FHR1_VAL,	// DISP_FHR1_VAL
	STR_NULL,
	STR_NULL
};


static POINT Fhr2_CtrlPos[DISP_FHR2_MAX];
static POINT Fhr2ParamCtrlPos[DISP_FHR2_MAX][FACE_MAX] = {
	 {{   3,   3 },{   5,   5 }, {   3,   3 },{   5,   5 }}	// DISP_FHR2
	,{{  10,  19 },{  40,  30 }, {  10,  25 },{  10,  30 }}	// DISP_FHR2_VAL
	,{{  40,   3 },{  40,   5 }, {  40,   3 },{  40,   5 }}
	,{{  60,   3 },{  60,   5 }, {  60,   3 },{  60,   5 }}	// DISP_FHR1_ALARM
};
static SIZE Fhr2ParamItemSize[DISP_FHR2_MAX][FACE_MAX] = {
	 {{  33,  17 },{  33,  17 }, {  33,  20 },{  33,  20 }}	// DISP_FHR2
	,{{ 121,  61 },{ 241, 121 }, { 121,  64 },{ 241, 128 }}	// DISP_FHR2_VAL
	,{{  16,  17 },{  16,  17 }, {  16,  20 },{  16,  20 }}	// DISP_FHR2_SIGN
	,{{  17,  17 },{  17,  17 }, {	17,  17 },{  17,  17 }}	// DISP_FHR2_ALARM
};
static INT8 Fhr2ParamItemFont[DISP_FHR2_MAX][FACE_MAX] = {
	       //panhonghui,改变字体大小
	  { SYSLOGFONT_NOR_RUS,		SYSLOGFONT_NOR_RUS,		SYSLOGFONT_NOR_RUS,		SYSLOGFONT_NOR_RUS	  }	// DISP_FHR1

	 // { SYSLOGFONT_FIXED,		SYSLOGFONT_FIXED,		SYSLOGFONT_FIXED,		SYSLOGFONT_FIXED	  }	// DISP_FHR1
	,{ SYSLOGFONT_BIG_PARAM,	SYSLOGFONT_HUGE_PARAM,	SYSLOGFONT_BIG_PARAM,	SYSLOGFONT_HUGE_PARAM }	// DISP_FHR1_VAL
	,{ SYSLOGFONT_BIG_PARAM,	SYSLOGFONT_HUGE_PARAM,	SYSLOGFONT_BIG_PARAM,	SYSLOGFONT_HUGE_PARAM }	// DISP_FHR1_VAL
	,{ SYSLOGFONT_DEF_ASC,		SYSLOGFONT_DEF_ASC,		SYSLOGFONT_DEF_ASC,		SYSLOGFONT_DEF_ASC }    // DISP_FHR1_VAL
};
static RESID Fhr2Param_CtrlID[DISP_FHR2_MAX] = {
	IDC_MAIN_PARAM_FHR2_NAME,   // DISP_FHR1
	IDC_MAIN_PARAM_FHR2_PARAM,  // DISP_FHR1_VAL
	IDC_MAIN_PARAM_FHR2_SIGN,
	IDC_MAIN_PARAM_FHR2_ALARM
};
static STRINGID Fhr2ParamCaption[DISP_FHR2_MAX] = {
	STR_MAIN_PARAM_FHR2,		// DISP_FHR1
	STR_MAIN_PARAM_FHR2_VAL,	 // DISP_FHR1_VAL
	STR_NULL,
	STR_NULL
};


static POINT Fm_CtrlPos[DISP_FM_MAX];
static POINT FmParamCtrlPos[DISP_FM_MAX][FACE_MAX] = {
	 {{   3,   3 },{   5,   5 }, {   3,   3 },{   5,   5 }}	// DISP_FETALMOVE
	,{{  10,  19 },{  40,  30 }, {  10,  25 },{  10,  30 }}	// DISP_FM_VAL
};
static SIZE FmParamItemSize[DISP_FM_MAX][FACE_MAX] = {
	 {{  33,  17 },{  33,  17 }, {  33,  20 },{  33,  20 }}	// DISP_FM
	,{{ 121,  61 },{ 241, 121 }, { 121,  64 },{ 241, 128 }}	// DISP_FM_VAL
};
static INT8 FmParamItemFont[DISP_FM_MAX][FACE_MAX] = {
	       //panhonghui,改变字体大小
	  { SYSLOGFONT_NOR_RUS,		SYSLOGFONT_NOR_RUS,		SYSLOGFONT_NOR_RUS,		SYSLOGFONT_NOR_RUS	  }	// DISP_FHR1

	 // { SYSLOGFONT_FIXED,		SYSLOGFONT_FIXED,		SYSLOGFONT_FIXED,		SYSLOGFONT_FIXED	  }	// DISP_FHR1
	,{ SYSLOGFONT_BIG_PARAM, SYSLOGFONT_HUGE_PARAM, SYSLOGFONT_BIG_PARAM, SYSLOGFONT_HUGE_PARAM }	// DISP_FM_VAL
};
static RESID FmParam_CtrlID[DISP_FM_MAX] = {
	IDC_MAIN_PARAM_FM_NAME,
	IDC_MAIN_PARAM_FM_PARAM,
};
static STRINGID FmParamCaption[DISP_FM_MAX] = {
	STR_MAIN_PARAM_FM,
	STR_MAIN_PARAM_FM_VAL,
};


static POINT Toco_CtrlPos[DISP_TOCO_MAX];
static POINT TocoParamCtrlPos[DISP_TOCO_MAX][FACE_MAX] = {
	 {{   3,   3 },{   5,   5 }, {   3,   3 },{   5,   5 }}	// DISP_TOCO
	,{{  10,  19 },{  40,  30 }, {  10,  25 },{  10,  30 }}	// DISP_TOCO_VAL
};
static SIZE TocoParamItemSize[DISP_TOCO_MAX][FACE_MAX] = {
	 {{  33,  17 },{  33,  17 }, {  33,  20 },{  33,  20 }}	// DISP_FHR1
	,{{ 121,  61 },{ 241, 121 }, { 121,  64 },{ 241, 128 }}	// DISP_FHR1_VAL
};
static INT8 TocoParamItemFont[DISP_TOCO_MAX][FACE_MAX] = {
	       //panhonghui,改变字体大小
	  { SYSLOGFONT_NOR_RUS,		SYSLOGFONT_NOR_RUS,		SYSLOGFONT_NOR_RUS,		SYSLOGFONT_NOR_RUS	  }	// DISP_FHR1

	 // { SYSLOGFONT_FIXED,		SYSLOGFONT_FIXED,		SYSLOGFONT_FIXED,		SYSLOGFONT_FIXED	  }	// DISP_FHR1
	,{ SYSLOGFONT_BIG_PARAM, SYSLOGFONT_HUGE_PARAM, SYSLOGFONT_BIG_PARAM, SYSLOGFONT_HUGE_PARAM }	// DISP_FHR1_VAL
};
static RESID TocoParam_CtrlID[DISP_TOCO_MAX] = {
	IDC_MAIN_PARAM_TOCO_NAME,   // DISP_FHR1
	IDC_MAIN_PARAM_TOCO_PARAM   // DISP_FHR1_VAL
};
static STRINGID TocoParamCaption[DISP_TOCO_MAX] = {
	STR_MAIN_PARAM_TOCO,		// DISP_FHR1
	STR_MAIN_PARAM_TOCO_VAL	 // DISP_FHR1_VAL
};

/************************************************************************/
/*  函数名：GetAllDispParaPos										   */
/*  描述：  得到所有显示参数的坐标;必须要等到主窗口创建以后.			*/
/*  参数：  无														  */
/*  返回值：无														  */
/************************************************************************/
static BOOL CalcAllDispParaPos(INT8 face)
{
	INT16 i;
	for (i = DISP_FHR1_FIRST; i < DISP_FHR1_MAX; i++)
	{
		Fhr1_CtrlPos[i].x = ParamCtrlGroupPos[DISP_FHR1_GRP][face].x 
							+ Fhr1ParamCtrlPos[i][face].x;
		Fhr1_CtrlPos[i].y = ParamCtrlGroupPos[DISP_FHR1_GRP][face].y 
							+ Fhr1ParamCtrlPos[i][face].y;
	}
	for (i = DISP_FHR2_FIRST; i < DISP_FHR2_MAX; i++)
	{
		Fhr2_CtrlPos[i].x = ParamCtrlGroupPos[DISP_FHR2_GRP][face].x 
							+ Fhr2ParamCtrlPos[i][face].x;
		Fhr2_CtrlPos[i].y = ParamCtrlGroupPos[DISP_FHR2_GRP][face].y 
							+ Fhr2ParamCtrlPos[i][face].y;
	}
	for (i = DISP_FM_FIRST; i < DISP_FM_MAX; i++)
	{
		Fm_CtrlPos[i].x = ParamCtrlGroupPos[DISP_FETALMOVE_GRP][face].x 
							+ FmParamCtrlPos[i][face].x;
		Fm_CtrlPos[i].y = ParamCtrlGroupPos[DISP_FETALMOVE_GRP][face].y 
							+ FmParamCtrlPos[i][face].y;
		if ((MONITOR_TYPE_AR2 == MonitorConfig.MonitorName) && (FACE_BIGFONT == face))
		{
			Fm_CtrlPos[i].y -= (ARTEMIS2_TOP_OFFSET+ARTEMIS2_BOTTOM_OFFSET)/2;
		}
	}
	for (i = DISP_TOCO_FIRST; i < DISP_TOCO_MAX; i++)
	{
		Toco_CtrlPos[i].x = ParamCtrlGroupPos[DISP_TOCO_GRP][face].x 
							+ TocoParamCtrlPos[i][face].x;
		Toco_CtrlPos[i].y = ParamCtrlGroupPos[DISP_TOCO_GRP][face].y 
							+ TocoParamCtrlPos[i][face].y;
		if ((MONITOR_TYPE_AR2 == MonitorConfig.MonitorName) && (FACE_BIGFONT == face))
		{
			Toco_CtrlPos[i].y -= (ARTEMIS2_TOP_OFFSET+ARTEMIS2_BOTTOM_OFFSET)/2;
		}
	}
	return TRUE;
}

VOID GetIntParamText(INT16 value, char *text)
{
	if (value == NOVALUE)
	{
		strcpy(text, "---");
	}
	else if (value == UNKNOWN_PARAM)
	{
		strcpy(text, "-?-");
	}
	else
	{
		sprintf(text, "%3d", value);
	}
}

VOID SetIntParamValue(RESID id, STRINGID str_id, INT16 value)
{
	HWND hCtrl;
	CHAR *text;
	text = LoadString(str_id);
	GetIntParamText(value, text);
	hCtrl = GetDlgItem(MainScnHWnd, id);
	if (hCtrl)
	{
		SetWindowText(hCtrl, str_id);
	}
}

VOID DispFhr1Param(VOID)
{
	if (AlmPrsntInfo.Blink.FHR1Blink & (BLINK_MASK_BLINK | BLINK_MASK_FLUSH))
		LastParams.fhr1 = INITVALUE;
	if (LastParams.fhr1 != Disp_AllParams.fhr1)
	{
		INT16 dispvalue = Disp_AllParams.fhr1;
		LastParams.fhr1 = Disp_AllParams.fhr1;
		if (dispvalue < 30)
			dispvalue = NOVALUE;
		SetIntParamValue(IDC_MAIN_PARAM_FHR1_PARAM, STR_MAIN_PARAM_FHR1_VAL,
							dispvalue);
	}
}

VOID BlinkFhr1Param(VOID)
{
	HWND hCtrl = 0;
	if (AlmPrsntInfo.Blink.FHR1Blink & BLINK_MASK_BLINK)
	{
		hCtrl = GetDlgItem(MainScnHWnd, IDC_MAIN_PARAM_FHR1_PARAM);
		if (hCtrl)
		{
			SetWindowText(hCtrl, 0);
		}
	}
}

VOID DispFhr2Param(VOID)
{
	if (AlmPrsntInfo.Blink.FHR2Blink & (BLINK_MASK_BLINK | BLINK_MASK_FLUSH))
		LastParams.fhr2 = INITVALUE;
	if (LastParams.fhr2 != Disp_AllParams.fhr2)
	{
		INT16 dispvalue = Disp_AllParams.fhr2;
		LastParams.fhr2 = Disp_AllParams.fhr2;
		if (dispvalue < 30)
			dispvalue = NOVALUE;
		SetIntParamValue(IDC_MAIN_PARAM_FHR2_PARAM, STR_MAIN_PARAM_FHR2_VAL,
							dispvalue);
	}
}

VOID BlinkFhr2Param(VOID)
{
	HWND hCtrl = 0;
	if (AlmPrsntInfo.Blink.FHR2Blink & BLINK_MASK_BLINK)
	{
		hCtrl = GetDlgItem(MainScnHWnd, IDC_MAIN_PARAM_FHR2_PARAM);
		if (hCtrl)
		{
			SetWindowText(hCtrl, 0);
		}
	}
}


VOID DispTocoParam(VOID)
{
	if (AlmPrsntInfo.Blink.TOCOBlink & (BLINK_MASK_BLINK | BLINK_MASK_FLUSH))
		LastParams.toco = INITVALUE;
	if (LastParams.toco != Disp_AllParams.toco)
	{
		LastParams.toco = Disp_AllParams.toco;
		SetIntParamValue(IDC_MAIN_PARAM_TOCO_PARAM, STR_MAIN_PARAM_TOCO_VAL,
							Disp_AllParams.toco);
	}
}

VOID BlinkTocoParam(VOID)
{
	HWND hCtrl = 0;
	if (AlmPrsntInfo.Blink.TOCOBlink & BLINK_MASK_BLINK)
	{
		hCtrl = GetDlgItem(MainScnHWnd, IDC_MAIN_PARAM_TOCO_PARAM);
		if (hCtrl)
		{
			SetWindowText(hCtrl, 0);
		}
	}
}


VOID DispFMParam(VOID)
{
	if (AlmPrsntInfo.Blink.FMBlink & (BLINK_MASK_BLINK | BLINK_MASK_FLUSH))
		LastParams.fm = INITVALUE;
	if (LastParams.fm != Disp_AllParams.fm)
	{
		LastParams.fm = Disp_AllParams.fm;
		SetIntParamValue(IDC_MAIN_PARAM_FM_PARAM, STR_MAIN_PARAM_FM_VAL,
							Disp_AllParams.fm);
	}
}


VOID BlinkFMParam(VOID)
{
	HWND hCtrl;
	if (AlmPrsntInfo.Blink.FMBlink & BLINK_MASK_FLUSH)
	{
		hCtrl = GetDlgItem(MainScnHWnd, IDC_MAIN_PARAM_FM_PARAM);
		if (hCtrl)
		{
			SetWindowText(hCtrl, 0);
		}
	}
}

static VOID DispFhrSignal(VOID)
{
	HWND hCtrl;
	HDC hdc;
	GAL_PIXEL color;
	char signal;
	char i;
	if (AlmPrsntInfo.Blink.FHR1Blink & (BLINK_MASK_BLINK | BLINK_MASK_FLUSH))
		LastParams.signal = INITVALUE;
	if (AlmPrsntInfo.Blink.FHR2Blink & (BLINK_MASK_BLINK | BLINK_MASK_FLUSH))
		LastParams.signal = INITVALUE;
	if (LastParams.signal == Disp_AllParams.signal)
		return;
	color = GetWindowElementColor(MonitorConfig.colorParam[PARA_BLOCK_FHR1]);
	if (FhrConfig.mode != 1)
	{
		if (hCtrl = GetDlgItem(MainScnHWnd, IDC_MAIN_PARAM_FHR1_SIGN))
		{
			if ((LastParams.signal & 0x03) != (Disp_AllParams.signal & 0x03))
			{
				SetWindowText(hCtrl, 0);
				signal = Disp_AllParams.signal & 0x03;
				if (signal > 0)
				{
					hdc = GetDC(hCtrl);
					color = SetPenColor(hdc, color);
					for (i = 0; i < signal; i++)
					{
						Line(hdc, i * 6 + 0, 7 - i*3, i * 6 + 0, 15);
						Line(hdc, i * 6 + 1, 7 - i*3, i * 6 + 1, 15);
						Line(hdc, i * 6 + 2, 7 - i*3, i * 6 + 2, 15);
					}
					SetPenColor(hdc, color);
					ReleaseDC(hdc);
				}
			}
		}
	}
	color = GetWindowElementColor(MonitorConfig.colorParam[PARA_BLOCK_FHR2]);
	if (FhrConfig.mode > 0)
	{
		if (hCtrl = GetDlgItem(MainScnHWnd, IDC_MAIN_PARAM_FHR2_SIGN))
		{
			if ((LastParams.signal & 0x0C) != (Disp_AllParams.signal & 0x0C))
			{
				SetWindowText(hCtrl, 0);
				signal = (Disp_AllParams.signal & 0x0C) >> 2;
				if (signal > 0)
				{
					hdc = GetDC(hCtrl);
					color = SetPenColor(hdc, color);
					for (i = 0; i < signal; i++)
					{
						Line(hdc, i * 6 + 0, 7 - i*3, i * 6 + 0, 15);
						Line(hdc, i * 6 + 1, 7 - i*3, i * 6 + 1, 15);
						Line(hdc, i * 6 + 2, 7 - i*3, i * 6 + 2, 15);
					}
					SetPenColor(hdc, color);
					ReleaseDC(hdc);
				}
			}
		}
	}
	LastParams.signal = Disp_AllParams.signal;
}

VOID DispFetalInfo(VOID)
{
	UINT32 savetime = MonitorInfo.PatientTime;
	UINT32 elapsetime = RecFHRControl.elapseSec;
	UINT32 periodtime = RecFHRControl.periodTime;
	HWND   hCtrl;
	UCHAR *txt;
	UINT32 hour, min,sec;
	if (hCtrl = GetDlgItem(MainScnHWnd, IDC_PATIENTINFO_SAVE_TIME_L))
	{
		hour = savetime / 3600;
		if (hour > 99)
		{
			hour = 99;
			min  = 59;
			sec  = 59;
		}
		else
		{
			min  = savetime - hour * 3600;
			sec  = min % 60;
			min /= 60;
		}
		txt = LoadString(STR_MAIN_BOTTOM_SAVE_TIME);
		sprintf(txt, "%-13s %2d:%02d:%02d", LoadString(STR_MAIN_BOTTOM_SAVE),
			hour, min, sec);
		SetWindowText(hCtrl, STR_MAIN_BOTTOM_SAVE_TIME);
	}
	if (hCtrl = GetDlgItem(MainScnHWnd, IDC_PRINTERINFO_ELAPSE_TIME_L))
	{
		txt = LoadString(STR_MAIN_BOTTOM_ELAPSE_TIME);
		if (periodtime == 0) // 无定时,显示打印时长
		{
			hour = elapsetime / 3600;
			if (hour > 99)
			{
				hour = 99;
				min  = 59;
				sec  = 59;
			}
			else
			{
				min  = elapsetime - hour * 3600;
				sec  = min % 60;
				min  = min / 60;
			}
			sprintf(txt, "%-13s %2d:%02d:%02d", LoadString(STR_MAIN_BOTTOM_ELAPSE),
				hour, min, sec);
		}
		else// 显示剩余时间
		{
			UINT32 remain = periodtime - elapsetime;
			hour = remain / 3600;
			if (hour > 99)
			{
				hour = 99;
				min  = 59;
				sec  = 59;
			}
			else
			{
				min  = remain % 3600;
				sec  = min % 60;
				min  = min / 60;
			}
			sprintf(txt, "%-13s %2d:%02d:%02d", LoadString(STR_MAIN_BOTTOM_REMAIN),
				hour, min, sec);
		}
		SetWindowText(hCtrl, STR_MAIN_BOTTOM_ELAPSE_TIME);
	}
	if (hCtrl = GetDlgItem(MainScnHWnd, IDC_PRINTERINFO_PERIOD_TIME_L))
	{
		txt = LoadString(STR_MAIN_BOTTOM_PERIOD_TIME);
		if (periodtime > 0)
		{
			hour = periodtime / 3600;
			min  = (periodtime - hour * 3600) / 60;
			sec  = 0;
			sprintf(txt, "%-13s %2d:%02d:%02d", LoadString(STR_MAIN_BOTTOM_PERIOD),
				hour, min, sec);
		}
		else
		{
			sprintf(txt, "%-13s  %s",  LoadString(STR_MAIN_BOTTOM_PERIOD),
				 LoadString(STR_DLG_FM_MOVEMENTCAL_MANUAL));
		}
		SetWindowText(hCtrl, STR_MAIN_BOTTOM_PERIOD_TIME);
	}
}

VOID ShowParaRegion(VOID)
{
	return;
}

VOID GetAllDispParamValue (VOID)
{
	Disp_AllParams = AllParams;
}


/************************************************************************/
/*  函数名：FrushParaVal												*/
/*  描述：  刷新所有显示参数的值;一秒钟刷新一次.						*/
/*  参数：  无														  */
/*  返回值：无														  */
/************************************************************************/
VOID  FlushParamValue (VOID)
{
	static UINT8 count = 0;
	if (LayoutInProcess)
		return;
	//if (++count >= 10)
	{
		//count = 0;
		GetAllDispParamValue();
		if (1)//(MonitorInfo.fhrWorkFlag)
		{
			DispFhr1Param();
			DispFhr2Param();
			DispTocoParam();
			DispFMParam();
			DispFhrSignal();
			DispFetalInfo();
		}
	}
	return;
}



/**
 ** 实现闪烁功能; 100ms刷新一次.
**/
VOID  BlinkParamValue (VOID)
{
	static UINT8 count = 0;
	UINT8 maxCnt = 10;
	UINT8 hideCnt = 7;
	if (LayoutInProcess)
		return;
	if (++count >= 10)
		count = 0;

	if (count == hideCnt)
	{
		BlinkFhr1Param();
		BlinkFhr2Param();
		BlinkTocoParam();
		BlinkFMParam();
	}
	return;
}


/************************************************************************/
/*  函数名：InitLastParaValue										   */
/*  描述：  初始化前一秒钟参数的值									  */
/*  参数：  无														  */
/*  返回值：无														  */
/************************************************************************/
VOID  InitLastParaValue (VOID)
{
	LastParams.fhr1 = 0;
	LastParams.fhr2 = 0;
	LastParams.toco = INITVALUE;
	LastParams.fm   = INITVALUE;
	LastParams.afm  = INITVALUE;
	LastParams.signal = INITVALUE;
	return;
}

GAL_PIXEL GetDarkColor(GAL_PIXEL pixel)
{
    GAL_COLOR color;

    UnmapPixel (&scrdev, pixel, &color);

    color.r = (color.r >> 1);
    color.g = (color.g >> 1);
    color.b = (color.b >> 1);

    return MapColor (&scrdev, &color);
}


VOID CreateParamBoard(INT8 face)
{
	PCONTROL pCtrl;
	HWND hCtrl;
	INT16 x;
	INT16 w;
	GAL_PIXEL bkColor;
	
	bkColor = GetWindowElementColor(WEC_EXCOLOR_CORNFLOWERBLUE);
	if (MonitorConfig.nightModeOn)
	{
		bkColor = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_DIMGRAY);
	}
	if (FACE_MAX <= face)
	{
		bkColor = GetWindowElementColor(BKC_DLG);
	}

	x  = PARAM_LEFT;
	w  = PARAM_WIDTH;
	if (face == FACE_BIGFONT || face == FACE_BIGFONT_SINGLE)
	{
		x  = 0;
		w  = SCREEN_WIDTH;
	}
	pCtrl = GetCtrlWndMem(IDC_MAIN_PATAM_BOARD_L);
	hCtrl = CreateWindowEx(CTRL_STATIC, 0, WS_VISIBLE | SS_SIMPLE, 0,
						   IDC_MAIN_PATAM_BOARD_L,
						   x,
						   TOPBAR_HEIGHT,
						   w,
						   MIDDLE_HEIGHT,
						   MainScnHWnd,
						   0,
						   0,
						   pCtrl);
	if (hCtrl == HWND_INVALID)
	{
		return;
	}
	SetWindowBkColor(hCtrl, bkColor);
}

BOOL CreateParamCtrlGroup(INT8 face)
{
	PCONTROL pCtrl;
	HWND hCtrl;
	RESID id;
	INT16 index;
	INT16 x;
	INT16 y;
	INT16 w;
	INT16 h;
	INT16 i;
	extern GROUPBOXDATA gGroupboxAdddata[GPB_SYS_INDEX_MAX];

	GAL_PIXEL bkColor;
	bkColor = GetWindowElementColor(WEC_EXCOLOR_CORNFLOWERBLUE);
	if (MonitorConfig.nightModeOn)
	{
		bkColor = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_DIMGRAY);
	}

	for (i = DISP_GRP_FIRST; i < DISP_GRP_MAX; i++)
	{
		
		if (FhrConfig.mode == 0 && i == DISP_FHR2_GRP)
		{
			continue;
		}
		if (FhrConfig.mode == 1 && i == DISP_FHR1_GRP)
		{
			continue;
		}
		id = ParamCtrlGroupID[i];
		index = GPB_MAIN_FHR1 + i;
		x = ParamCtrlGroupPos[i][face].x;
		y = ParamCtrlGroupPos[i][face].y;
		w = ParamCtrlGroupSIZE[i][face].cx;
		h = ParamCtrlGroupSIZE[i][face].cy;
		if ((MONITOR_TYPE_AR2 == MonitorConfig.MonitorName) && (FACE_BIGFONT == face))
		{
			h -= (ARTEMIS2_TOP_OFFSET+ARTEMIS2_BOTTOM_OFFSET)/2;
			y += ARTEMIS2_TOP_OFFSET;
			if (i >= DISP_TOCO_GRP && i <= DISP_FETALMOVE_GRP)
			{
				y -= (ARTEMIS2_TOP_OFFSET+ARTEMIS2_BOTTOM_OFFSET)/2;
			}
		}
		pCtrl = GetCtrlWndMem(id);
		hCtrl = CreateWindowEx(CTRL_GROUPBOX, 0, WS_VISIBLE | WS_TABSTOP, 0,
							   id,
							   x,
							   y,
							   w,
							   h,
							   MainScnHWnd,
							   0,
							   (DWORD)&gGroupboxAdddata[index],
							   pCtrl);
		if (hCtrl == HWND_INVALID)
		{
			return FALSE;
		}
		EnableWindow(hCtrl, FALSE);
		if (FACE_MAX <= face)
		{
			bkColor = GetWindowElementColor(BKC_DLG);
		}
		SetWindowBkColor(hCtrl, bkColor);
	}
}


BOOL CreateFhr1CtrlGroup(INT8 face)
{
	HWND hCtrl;
	PCONTROL pCtrl;
	INT16 i;
	GAL_PIXEL color;
	GAL_PIXEL bkColor;
	bkColor = GetWindowElementColor(WEC_EXCOLOR_CORNFLOWERBLUE);
	if (MonitorConfig.nightModeOn)
	{
		bkColor = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_DIMGRAY);
	}
	if (FACE_MAX <= face)
	{
		bkColor = GetWindowElementColor(BKC_DLG);
	}
	color = GetWindowElementColor(MonitorConfig.colorParam[PARA_BLOCK_FHR1]);//PIXEL_magenta;
	DWORD style[DISP_FHR1_MAX] = {
		WS_VISIBLE | SS_SIMPLE,
		WS_VISIBLE | SS_CENTER,
		WS_VISIBLE | SS_SIMPLE,
		WS_VISIBLE | SS_BITMAP
	};
	for (i = DISP_FHR1_FIRST; i < DISP_FHR1_MAX; i++)
	{
		pCtrl = GetCtrlWndMem(Fhr1Param_CtrlID[i]);
		hCtrl = CreateWindowEx(CTRL_STATIC,
							   Fhr1ParamCaption[i],
							   style[i],
							   0,
							   Fhr1Param_CtrlID[i],
							   Fhr1_CtrlPos[i].x,
							   Fhr1_CtrlPos[i].y,
							   Fhr1ParamItemSize[i][face].cx,
							   Fhr1ParamItemSize[i][face].cy,
							   MainScnHWnd,
							   0,
							   0,
							   pCtrl);
		if (hCtrl == HWND_INVALID)
		{
			return FALSE;
		}
		SetWindowBkColor(hCtrl, bkColor);
		if (DISP_FHR1_FIRST == i)
		{
			SetWindowTextColor(hCtrl, GetDarkColor(color));
		}
		else
		{
			SetWindowTextColor(hCtrl, color);
		}
		SetWindowFont(hCtrl, GetSystemFont(Fhr1ParamItemFont[i][face]));
	}
	return TRUE;
}


BOOL CreateFhr2CtrlGroup(INT8 face)
{
	HWND hCtrl;
	PCONTROL pCtrl;
	INT16 i;
	GAL_PIXEL color;
	GAL_PIXEL bkColor;
	bkColor = GetWindowElementColor(WEC_EXCOLOR_CORNFLOWERBLUE);
	if (MonitorConfig.nightModeOn)
	{
		bkColor = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_DIMGRAY);
	}
	if (FACE_MAX <= face)
	{
		bkColor = GetWindowElementColor(BKC_DLG);
	}
	color = GetWindowElementColor(MonitorConfig.colorParam[PARA_BLOCK_FHR2]);//PIXEL_yellow;
	DWORD style[DISP_FHR2_MAX] = {
		WS_VISIBLE | SS_SIMPLE,
		WS_VISIBLE | SS_CENTER,
		WS_VISIBLE | SS_SIMPLE,
		WS_VISIBLE | SS_BITMAP
	};
	for (i = DISP_FHR2_FIRST; i < DISP_FHR2_MAX; i++)
	{
		pCtrl = GetCtrlWndMem(Fhr2Param_CtrlID[i]);
		hCtrl = CreateWindowEx(CTRL_STATIC,
							   Fhr2ParamCaption[i],
							   style[i],
							   0,
							   Fhr2Param_CtrlID[i],
							   Fhr2_CtrlPos[i].x,
							   Fhr2_CtrlPos[i].y,
							   Fhr2ParamItemSize[i][face].cx,
							   Fhr2ParamItemSize[i][face].cy,
							   MainScnHWnd,
							   0,
							   0,
							   pCtrl);
		if (hCtrl == HWND_INVALID)
		{
			return FALSE;
		}
		SetWindowBkColor(hCtrl, bkColor);
		if (DISP_FHR2_FIRST == i)
		{
			SetWindowTextColor(hCtrl, GetDarkColor(color));
		}
		else
		{
			SetWindowTextColor(hCtrl, color);
		}
		SetWindowFont(hCtrl, GetSystemFont(Fhr2ParamItemFont[i][face]));
	}
	return TRUE;
}



BOOL CreateTocoCtrlGroup(INT8 face)
{
	HWND hCtrl;
	PCONTROL pCtrl;
	INT16 i;
	GAL_PIXEL color;
	GAL_PIXEL bkColor;
	bkColor = GetWindowElementColor(WEC_EXCOLOR_CORNFLOWERBLUE);
	if (MonitorConfig.nightModeOn)
	{
		bkColor = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_DIMGRAY);
	}
	if (FACE_MAX <= face)
	{
		bkColor = GetWindowElementColor(BKC_DLG);
	}
	color = GetWindowElementColor(MonitorConfig.colorParam[PARA_BLOCK_TOCO]);//PIXEL_green;
	DWORD style[DISP_TOCO_MAX] = {
		WS_VISIBLE | SS_SIMPLE,
		WS_VISIBLE | SS_CENTER
	};
	for (i = DISP_TOCO_FIRST; i < DISP_TOCO_MAX; i++)
	{
		pCtrl = GetCtrlWndMem(TocoParam_CtrlID[i]);
		hCtrl = CreateWindowEx(CTRL_STATIC,
							   TocoParamCaption[i],
							   style[i],
							   0,
							   TocoParam_CtrlID[i],
							   Toco_CtrlPos[i].x,
							   Toco_CtrlPos[i].y,
							   TocoParamItemSize[i][face].cx,
							   TocoParamItemSize[i][face].cy,
							   MainScnHWnd,
							   0,
							   0,
							   pCtrl);
		if (hCtrl == HWND_INVALID)
		{
			return FALSE;
		}
		SetWindowBkColor(hCtrl, bkColor);
		if (DISP_TOCO_FIRST == i)
		{
			SetWindowTextColor(hCtrl, GetDarkColor(color));
		}
		else
		{
			SetWindowTextColor(hCtrl, color);
		}
		SetWindowFont(hCtrl, GetSystemFont(TocoParamItemFont[i][face]));
	}
	return TRUE;
}



BOOL CreateFmCtrlGroup(INT8 face)
{
	HWND hCtrl;
	PCONTROL pCtrl;
	INT16 i;
	GAL_PIXEL color;
	CTRLDATA   ctrl_data[DISP_FM_MAX] = {
		{CTRL_STATIC, WS_VISIBLE | SS_SIMPLE, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{CTRL_STATIC, WS_VISIBLE | SS_CENTER, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};
	//color = GetWindowElementColor(WEC_EXCOLOR_CYAN);
	GAL_PIXEL bkColor;
	bkColor = GetWindowElementColor(WEC_EXCOLOR_CORNFLOWERBLUE);
	if (MonitorConfig.nightModeOn)
	{
		bkColor = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_DIMGRAY);
	}
	if (FACE_MAX <= face)
	{
		bkColor = GetWindowElementColor(BKC_DLG);
	}

	color = GetWindowElementColor(MonitorConfig.colorParam[PARA_BLOCK_FM]);
	for (i = DISP_FM_FIRST; i < DISP_FM_MAX; i++)
	{
		ctrl_data[i].caption = FmParamCaption[i];
		ctrl_data[i].id = FmParam_CtrlID[i];
		ctrl_data[i].x = Fm_CtrlPos[i].x;
		ctrl_data[i].y = Fm_CtrlPos[i].y;
		ctrl_data[i].w = FmParamItemSize[i][face].cx;
		ctrl_data[i].h = FmParamItemSize[i][face].cy;
		if (ctrl_data[i].w == 0 || ctrl_data[i].h == 0)
			continue;
		pCtrl = GetCtrlWndMem(ctrl_data[i].id);
		hCtrl = CreateWindowEx(ctrl_data[i].class_name,
							   ctrl_data[i].caption,
							   ctrl_data[i].dwStyle,
							   ctrl_data[i].dwExStyle,
							   ctrl_data[i].id,
							   ctrl_data[i].x,
							   ctrl_data[i].y,
							   ctrl_data[i].w,
							   ctrl_data[i].h,
							   MainScnHWnd,
							   ctrl_data[i].dwAddData,
							   ctrl_data[i].dwAddData2,
							   pCtrl);
		if (hCtrl == HWND_INVALID)
		{
			return FALSE;
		}
		SetWindowBkColor(hCtrl, bkColor);
		if (DISP_FM_FIRST == i)
		{
			SetWindowTextColor(hCtrl, GetDarkColor(color));
		}
		else
		{
			SetWindowTextColor(hCtrl, color);
		}
		SetWindowFont(hCtrl, GetSystemFont(FmParamItemFont[i][face]));
	}
	return TRUE;
}

BOOL CreateFetalInfo(VOID)
{
	PCONTROL pCtrl;
	HWND hCtrl;
	INT16 x, y;
	INT16 w, h;
	GAL_PIXEL backColor, foreColor;
	foreColor = PIXEL_white;
	backColor = GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE);
	if (MonitorConfig.nightModeOn)
	{
		backColor = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_DIMGRAY);
	}

	w  = 180;
	x  = SCREEN_WIDTH - 85 - w - 1;
	y  = SCREEN_HIGH - BOTBAR_HEIGHT + 2;;
	h  = 14;
	
	if (MONITOR_TYPE_AR2 == MonitorConfig.MonitorName)
	{
		y -= ARTEMIS2_BOTTOM_OFFSET;
	}

	pCtrl = GetCtrlWndMem(IDC_PATIENTINFO_SAVE_TIME_L);
	hCtrl = CreateWindowEx(CTRL_STATIC, 0, WS_VISIBLE | SS_SIMPLE, 
						   STR_MAIN_BOTTOM_SAVE_TIME,
						   IDC_PATIENTINFO_SAVE_TIME_L,
						   x,
						   y,
						   w,
						   h,
						   MainScnHWnd,
						   0,
						   0,
						   pCtrl);
	if (hCtrl == HWND_INVALID)
	{
		return;
	}
	SetWindowBkColor(hCtrl, backColor);
	SetWindowTextColor(hCtrl, foreColor);

	y += h + 1;
	pCtrl = GetCtrlWndMem(IDC_PRINTERINFO_ELAPSE_TIME_L);
	hCtrl = CreateWindowEx(CTRL_STATIC, 0, WS_VISIBLE | SS_SIMPLE,
						   STR_MAIN_BOTTOM_ELAPSE_TIME,
						   IDC_PRINTERINFO_ELAPSE_TIME_L,
						   x,
						   y,
						   w,
						   h,
						   MainScnHWnd,
						   0,
						   0,
						   pCtrl);
	if (hCtrl == HWND_INVALID)
	{
		return;
	}
	SetWindowBkColor(hCtrl, backColor);
	SetWindowTextColor(hCtrl, foreColor);

	y += h + 1;
	pCtrl = GetCtrlWndMem(IDC_PRINTERINFO_PERIOD_TIME_L);
	hCtrl = CreateWindowEx(CTRL_STATIC, 0, WS_VISIBLE | SS_SIMPLE,
						   STR_MAIN_BOTTOM_PERIOD_TIME,
						   IDC_PRINTERINFO_PERIOD_TIME_L,
						   x,
						   y,
						   w,
						   h,
						   MainScnHWnd,
						   0,
						   0,
						   pCtrl);
	if (hCtrl == HWND_INVALID)
	{
		return;
	}
	SetWindowBkColor(hCtrl, backColor);
	SetWindowTextColor(hCtrl, foreColor);
}

BOOL CreateParamGroup(VOID)
{
	INT8 face = MonitorConfig.faceType;
	if (FhrConfig.mode <= 1)
	{
		if (face  < FACE_STD_SINGLE)
			face += FACE_STD_SINGLE;
	}
	else
	{
		if (face >= FACE_STD_SINGLE)
			face -= FACE_STD_SINGLE;
	}
	MonitorConfig.faceType = face;
	CreateParamCtrlGroup(face);
	CreateParamBoard(face);
	if (CalcAllDispParaPos(face))
	{
		if (FhrConfig.mode > 0)
		{
			CreateFhr2CtrlGroup(face);
		}
		if ((FhrConfig.mode > 1) || (FhrConfig.mode == 0))
		{
			CreateFhr1CtrlGroup(face);
		}
		CreateTocoCtrlGroup(face);
		CreateFmCtrlGroup(face);
	}
	CreateFetalInfo();
}

BOOL CreateHelpInfoLabel(VOID)
{
	PCONTROL pCtrl;
	HWND hCtrl;
	INT16 x, y;
	INT16 w, h;
	GAL_PIXEL backColor, foreColor;
	foreColor = PIXEL_white;
	backColor = PIXEL_black;

	w  = 160;
	x  = SCREEN_WIDTH - 90 - 180 - w;
	y  = SCREEN_HIGH - BOTBAR_HEIGHT + 2;
	h  = BOTBAR_HEIGHT - 4;
	if (MONITOR_TYPE_AR2 == MonitorConfig.MonitorName)
	{
		y -= ARTEMIS2_BOTTOM_OFFSET;
	}
	pCtrl = GetCtrlWndMem(IDC_HELP_INFORMATION_L);
	hCtrl = CreateWindowEx(CTRL_STATIC, 0, WS_VISIBLE | SS_LEFTNOWORDWRAP, 
						   0, IDC_HELP_INFORMATION_L,
						   x,
						   y,
						   w,
						   h,
						   MainScnHWnd,
						   0,
						   0,
						   pCtrl);
	if (hCtrl == HWND_INVALID)
	{
		return;
	}
	SetWindowBkColor(hCtrl, backColor);
	SetWindowTextColor(hCtrl, foreColor);
	pCtrl = (PCONTROL)hCtrl;
//	printf("pCtrl->id %d, pCtrl->pMainWin %p, pCtrl->pMainWin->id %d\n", pCtrl->id, pCtrl->pMainWin, pCtrl->pMainWin->id);
}


BOOL CreateDemoLabel(VOID)
{
	PCONTROL pCtrl;
	HWND hCtrl;
	INT16 xPos[4];
	INT16 yPos[4];
	INT16 face = MonitorConfig.faceType;
	PLOGFONT pFont = GetSystemFont(SYSLOGFONT_YAHEI17_FONT);
	SIZE size;
	int i;
	STRINGID str_id = MonitorInfo.inDemo ? STR_DLG_SETUP_DEMO : STR_NULL;
	GAL_PIXEL bkColor;
	bkColor = GetWindowElementColor(WEC_EXCOLOR_CORNFLOWERBLUE);
	if (MonitorConfig.nightModeOn)
	{
		bkColor = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_DIMGRAY);
	}
	if (FACE_MAX <= face)
	{
		bkColor = GetWindowElementColor(BKC_DLG);
	}
	if (face == FACE_STD|| face == FACE_STD_SINGLE)
	{
		return 0;
	}
	GetTextExtentEx(pFont, LoadString(STR_DLG_SETUP_DEMO), -1, &size);
	xPos[0] = 1;
	yPos[0] = TOPBAR_HEIGHT + 1;
	xPos[1] = SCREEN_WIDTH - size.cx - 1;
	yPos[1] = TOPBAR_HEIGHT + 1;
	xPos[2] = 1;
	yPos[2] = SCREEN_HIGH - BOTBAR_HEIGHT - size.cy - 5;
	xPos[3] = SCREEN_WIDTH - size.cx - 1;
	yPos[3] = SCREEN_HIGH - BOTBAR_HEIGHT - size.cy - 5;
	
	if (MONITOR_TYPE_AR2 == MonitorConfig.MonitorName)
	{
		for (i = 0; i < TABLESIZE(yPos); i++)
		{
			if (yPos[i] < SCREEN_HIGH / 2)
				yPos[i] += ARTEMIS2_TOP_OFFSET;
			else
				yPos[i] -= ARTEMIS2_BOTTOM_OFFSET + 2;
		}
	}
	for (i = 0; i < 4; i++)
	{
		pCtrl = GetCtrlWndMem(i + IDC_DESKTOP_DEMO1_L);
		hCtrl = CreateWindowEx(CTRL_STATIC, str_id, WS_VISIBLE | SS_CENTER, 0,
							   i + IDC_DESKTOP_DEMO1_L,
							   xPos[i],
							   yPos[i],
							   size.cx + 1,
							   size.cy + 1,
							   MainScnHWnd,
							   0,
							   0,
							   pCtrl);
		if (hCtrl == HWND_INVALID)
		{
			return;
		}
		if (FACE_MAX > face)
		{
			SetWindowBkColor(hCtrl, bkColor);
			if(MonitorConfig.language == RUSSIAN)
				SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_NOR_RUS));
			else
				SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_YAHEI17_FONT));
			SetWindowTextColor(hCtrl, PIXEL_yellow);
		}
		else
		{
			SetWindowBkColor(hCtrl, bkColor);
		}
	}
}

/**
 ** 把整数值显示成浮点数形式.
 ** \a str,  字符串保存的地址.
 ** \a len,  保存区的长度.
 ** \a value,数值; 
 ** \a base, 放大倍数,目前只能是10,100,或1000;
 ** \a foramt, 格式,目前只能是 FORM_41F, FORM_51F, FORM_52F, FORM_53F, FORM_72F,
 **  调用者需要注意, 放大倍数和格式的关系.比如,放大10倍,使用41F, 51F都是可以的.
 **  如果使用52F, 53F就不行了.
 **/
INT16  GetFloatText (CHAR *str, INT16 len, INT32 value, INT32 base, UINT8 format)
{
	INT16  ret;
	CHAR   text[100];
	INT16  str_len;
	INT32  residue;
	INT32  quotient;
	BOOL   minus;

	minus = (value < 0);
	
	if (base == 10) 
	{
		quotient = value / 10;
		residue  = value % 10;
	}
	else if (base == 100) 
	{
		quotient = value / 100;
		residue  = value % 100;
	}
	else if (base == 1000)
	{
		quotient = value / 1000;
		residue  = value % 1000;
	}
	else 
	{
		return (-1);
	}

	if (minus) 
	{
		residue = -residue; //如果是负数,余数则取绝对值;只需要在商的前面显示负号.
	}

	switch (format) 
	{
		case FORM_41F:
			if (minus && (0 == quotient))
				sprintf(text, "-%2d.%1d", quotient, residue);
			else 
				sprintf(text, "%2d.%1d", quotient, residue);
			break;

		case FORM_51F:
			if (minus && (0 == quotient))
				sprintf(text, "-%2d.%1d", quotient, residue);
			else
				sprintf(text, "%3d.%1d", quotient, residue);
			break;
			
		case FORM_52F:
			if (minus && (0 == quotient))
				sprintf(text, "-%1d.%02d", quotient, residue);
			else
				sprintf(text, "%2d.%02d", quotient, residue);
			break;
			
		case FORM_53F:
			if (minus && (0 == quotient))
				sprintf(text, "-%1d.%03d", quotient, residue);
			else
				sprintf(text, "%1d.%03d", quotient, residue);
			break;
			
		case FORM_72F:
			if (minus && (0 == quotient))
				sprintf(text, "-%3d.%02d", quotient, residue);
			else
				sprintf(text, "%4d.%02d", quotient, residue);
			break;

		default:
			return -1;
	}

	if (strlen(text) > len) 
	   return (-2);

	strcpy(str, text);

	return 0;
}

VOID DisplayAlarmSign(VOID)
{
	HWND hCtrl;
	DWORD item = 0;
	if (FALSE == FhrConfig.alarm)
	{
		item = (DWORD)DisableAlarm_icon[MonitorConfig.nightModeOn];
	}
	if (hCtrl = GetDlgItem(MainScnHWnd, IDC_MAIN_PARAM_FHR1_ALARM))
	{
		SetWindowItem(hCtrl, item);
	}
	if (hCtrl = GetDlgItem(MainScnHWnd, IDC_MAIN_PARAM_FHR2_ALARM))
	{
		SetWindowItem(hCtrl, item);
	}
}


void SetMonitorTypeLayoutParamPos(void)
{
	const POINT Ar2ParamCtrlGroupPos[DISP_GRP_MAX][FACE_MAX] = {
		{ { PARAM_LEFT,  30 }, { 100,  29 }, { PARAM_LEFT,  30 }, {  10, 130 } }, // DISP_FHR1_GRP
		{ { PARAM_LEFT, 114 }, { 400,  29 }, { PARAM_LEFT,  30 }, {  10, 130 } }, // DISP_FHR2_GRP
		{ { PARAM_LEFT, 198 }, { 100, 229 }, { PARAM_LEFT, 130 }, { 270, 130 } }, // DISP_TOCO_GRP
		{ { PARAM_LEFT, 282 }, { 400, 229 }, { PARAM_LEFT, 230 }, { 530, 130 } }  // DISP_FETALMOVE_GRP
	};
	const POINT Ar4ParamCtrlGroupPos[DISP_GRP_MAX][FACE_MAX] = {
		{ { PARAM_LEFT,  30 }, { 100,  29 }, { PARAM_LEFT,  30 }, {  10, 130 } }, // DISP_FHR1_GRP
		{ { PARAM_LEFT, 114 }, { 400,  29 }, { PARAM_LEFT,  30 }, {  10, 130 } }, // DISP_FHR2_GRP
		{ { PARAM_LEFT, 198 }, { 100, 229 }, { PARAM_LEFT, 130 }, { 270, 130 } }, // DISP_TOCO_GRP
		{ { PARAM_LEFT, 282 }, { 400, 229 }, { PARAM_LEFT, 230 }, { 530, 130 } }  // DISP_FETALMOVE_GRP
	};
	if (MONITOR_TYPE_AR2 == MonitorConfig.MonitorName)
	{
		memcpy(ParamCtrlGroupPos, Ar2ParamCtrlGroupPos,
			sizeof(Ar4ParamCtrlGroupPos));
	}
	if (MONITOR_TYPE_AR4S == MonitorConfig.MonitorName)
	{
		memcpy(ParamCtrlGroupPos, Ar4ParamCtrlGroupPos,
			sizeof(Ar4ParamCtrlGroupPos));
	}
}

