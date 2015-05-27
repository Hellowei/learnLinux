/******************************************************************************
***********
版权所有:			和心重典
版本号:				1.0.0
生成日期:			2010.05.11
文件名:				
作者:				ZONDAN
功能说明:			应用层主文件
其它说明:			
所属文件关系:		本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*******************************************************************************
**********/
#define  RECMAIN_GLOBALS
#include "includes.h"
#include "math.h"

#if _ENB_REC_FUNC


BOOL RecClassInitOps(VOID)
{
	UINT16 i;

	for (i = PAPER_TYPE_110MM; i < PAPER_TYPE_MAX; i++)
	{
		RecCurveClassPtr[i] = RecCurveClass + i;
		RecRegisterOps(RecCurveClassPtr[i], i);
		//RecCurveClassPtr[i]->RecInit(RecCurveClassPtr[i]);
	}
}


/*****************************************************************************************
函数名称:	static VOID gen_RecPutGutter (PRECEVENTCLASS this)
版本号:		1.0.0
生成日期:	2011.11.07
作者:		zondan
功能说明:	打印机构建装订线函数
输入参数:	
输出参数:	
其它说明:	
*****************************************************************************************/
static VOID gen_RecPutGutter(PRECEVENTCLASS this)
{
	UINT8  tmp 		   = '$';
	INT32  font_height1, font_height2;
	INT32  y_start;
	INT32  y_dist;
	INT32  dist;
	UINT8  buf[100];
	UINT8  **str_cut;
	INT32  num;
	INT32  line_w;
	INT32  len;
	INT32  i, index;
	PLOGFONT pLogFont;

	this->pRecClass->RecWriteIndexADD (this->pRecClass, 40);
	return;//仅加前切纸
	pLogFont	 = (PLOGFONT)(this->pRecClass->font_normal);
	font_height1 = pLogFont->size;

	pLogFont	 = (PLOGFONT)(this->pRecClass->font_cutter);
	font_height2 = pLogFont->size;

	y_start = this->pRecClass->RecPaperInfo.startPos;
	num	 = this->pRecClass->RecPaperInfo.maxHeight / font_height1;
	memset (buf, ' ', sizeof(buf));
	
	for (i = 0; i < num; i++)
	{
		if (i % 2 == 0)
		{
			buf[i] = tmp;
		}
	}
	buf[num] = 0;
	line_w = this->pRecClass->RecPreShowCharacter(this->pRecClass, 0, y_start,
													pLogFont, 0, 0, buf);

	memset (buf, ' ', sizeof(buf));
	len  = 0;
	switch (this->source)
	{
		case REC_EVENT_MONITOR:
			if (MonitorConfig.language == CHINESE)
			{
				sprintf (buf, "%s", "基本类型打印部分");
				len = 8;
			}
			else
			{
				sprintf (buf, "%s", "BASETYPE");
				len = 8;				
			}
			break;

		case REC_EVENT_TRENDGRAPH:
			if (MonitorConfig.language == CHINESE)
			{
				sprintf (buf, "%s", "趋势图打印部分");
				len = 7;
			}
			else
			{
				sprintf (buf, "%s", "TRENDGRAPH");
				len = 10;				
			}
			break;

		case REC_EVENT_TRENDTABLE:
			if (MonitorConfig.language == CHINESE)
			{
				sprintf (buf, "%s", "趋势表打印部分");
				len = 7;
			}
			else
			{
				sprintf (buf, "%s", "TRENDTABLE");
				len = 10;			
			}
			break;

		case REC_EVENT_OXYCRT:
			if (MonitorConfig.language == CHINESE)
			{
				sprintf (buf, "%s", "氧合呼吸图打印部分");
				len = 9;
			}
			else
			{
				sprintf (buf, "%s", "OXYCRG");
				len = 6;
			}
			break;

		case REC_EVENT_ALM_RECALL:
			if (MonitorConfig.language == CHINESE)
			{
				sprintf (buf, "%s", "报警事件回顾打印部分");
				len = 10;
			}
			else
			{
				sprintf (buf, "%s", "ALARM EVENT RECALL");
				len = 18;				
			}
			break;

		case REC_EVENT_NIBPLIST:
			if (MonitorConfig.language == CHINESE)
			{
				sprintf (buf, "%s", "NIBP测量回顾打印部分");
				len = 12;
			}
			else
			{
				sprintf (buf, "%s", "NIBP MEASURE RECALL");
				len = 19;			
			}
			break;

		case REC_EVENT_WAVERECALL:
			if (MonitorConfig.language == CHINESE)
			{
				sprintf (buf, "%s", "波形回顾打印部分");
				len = 8;
			}
			else
			{
				sprintf (buf, "%s", "WAVE RECALL");
				len = 11;
			}
			break;
		case REC_EVENT_FREEZE:
			if (MonitorConfig.language == CHINESE)
			{
				sprintf (buf, "%s", "冻结打印部分");
				len = 6;
			}
			else
			{
				sprintf (buf, "%s", "FREEZE");
				len = 6;
			}
			break;

		case REC_EVENT_SELFTEST:
			sprintf(buf, "%s", "SELF TEST");
			len = 9;
			break;

		case REC_EVENT_FETAL:
			if (MonitorConfig.language == CHINESE)
			{
				sprintf (buf, "%s", "胎监打印部分");
				len = 6;
			}
			else
			{
				sprintf (buf, "%s", "FETAL");
				len = 6;
			}
			break;

		default:
			return;
	}
	str_cut = (UCHAR **)malloc (sizeof(UCHAR *) * len);
	for (i = 0; i < len; i++)
	{
		str_cut[i] = (UCHAR *)malloc (sizeof(UCHAR) * 3);
		memset (str_cut[i], 0, 3);
	}
	
	index = 0;
	for (i = 0; i < strlen(buf); i += dist)
	{
		if (buf[i] >= 0x80)
		{
			str_cut[index][0] = buf[i];
			str_cut[index][1] = buf[i + 1];
			dist = 2;
		}
		else
		{
			str_cut[index][0] = buf[i];
			dist = 1;
		}
		index ++;
	}
	y_start = this->pRecClass->RecPaperInfo.startPos;
	y_dist  = this->pRecClass->RecPaperInfo.maxHeight / len;

	for (i = 0; i < len; i++)
	{
		this->pRecClass->RecPreShowCharacter(this->pRecClass,
			20 + line_w, y_start + i * y_dist, pLogFont, 1, 0, str_cut[i]);	   
	}

	for (i = 0; i < len; i++)
	{
		free (str_cut[i]);
	}
	free (str_cut);
	
	this->pRecClass->RecWriteIndexADD (this->pRecClass, line_w + 32 + 20 + 20); //32是字符宽度，20为间距
}


static VOID gen_RecPrintFetalScale(PRECEVENTCLASS this, BOOL isScale)
{
	UCHAR szStr[12];
	INT32 start_x = 0;
	INT32 width = 0;
	INT32 maxwidth = 0;
	PLOGFONT pFont;
	INT32 fontoffset;
	if (isScale == FALSE)
	{
		return;
	}
	pFont = GetSystemFont(SYSLOGFONT_FIXED);

	fontoffset = pFont->size / 2;
	strcpy(szStr, "FHR 210");
	width = this->pRecClass->RecPreShowCharacter(this->pRecClass,
		start_x, RecConfig.regStar[PAPER_REG_FHR] - fontoffset,
		pFont, 1, 0, szStr);
	if (width + start_x > maxwidth)
		maxwidth = width + start_x;
	if (ABS(RecConfig.regEnd[PAPER_REG_FHR] - RecConfig.regStar[PAPER_REG_TOCO])
		<= pFont->size)
	{
		if (RecConfig.regEnd[PAPER_REG_FHR] <= RecConfig.regStar[PAPER_REG_TOCO])
		{
			strcpy(szStr, "FHR 60");
			width = this->pRecClass->RecPreShowCharacter(this->pRecClass,
				start_x, RecConfig.regEnd[PAPER_REG_FHR] - fontoffset * 2,
				pFont, 1, 0, szStr);
			if (width + start_x > maxwidth)
				maxwidth = width + start_x;
			strcpy(szStr, "TOCO 100");
			width = this->pRecClass->RecPreShowCharacter(this->pRecClass,
				start_x, RecConfig.regStar[PAPER_REG_TOCO], pFont, 1, 0, szStr);
			if (width + start_x > maxwidth)
				maxwidth = width + start_x;
		}
		else
		{
			strcpy(szStr, "FHR 60");
			width = this->pRecClass->RecPreShowCharacter(this->pRecClass,
				start_x, RecConfig.regEnd[PAPER_REG_FHR], pFont, 1, 0, szStr);
			if (width + start_x > maxwidth)
				maxwidth = width + start_x;
			strcpy(szStr, "TOCO 100");
			width = this->pRecClass->RecPreShowCharacter(this->pRecClass,
				start_x, RecConfig.regStar[PAPER_REG_TOCO] - fontoffset * 2,
				pFont, 1, 0, szStr);
			if (width + start_x > maxwidth)
				maxwidth = width + start_x;
		}
	}
	else
	{
		strcpy(szStr, "FHR 60");
		width = this->pRecClass->RecPreShowCharacter(this->pRecClass,
			start_x, RecConfig.regEnd[PAPER_REG_FHR] - fontoffset,
			pFont, 1, 0, szStr);
		if (width + start_x > maxwidth)
			maxwidth = width + start_x;
		strcpy(szStr, "TOCO 100");
		width = this->pRecClass->RecPreShowCharacter(this->pRecClass,
			start_x, RecConfig.regStar[PAPER_REG_TOCO] - fontoffset,
			pFont, 1, 0, szStr);
		if (width + start_x > maxwidth)
			maxwidth = width + start_x;
	}
	strcpy(szStr, "TOCO 0");
	width = this->pRecClass->RecPreShowCharacter(this->pRecClass,
		start_x, RecConfig.regEnd[PAPER_REG_TOCO] - fontoffset,
		pFont, 1, 0, szStr);
	if (width + start_x > maxwidth)
		maxwidth = width + start_x;
	
	start_x = maxwidth + 8;
		// 直线
	this->pRecClass->RecPreLine(this->pRecClass,
		start_x, RecConfig.regStar[PAPER_REG_FHR],
		start_x + 40, RecConfig.regStar[PAPER_REG_FHR], 0);

	this->pRecClass->RecPreLine(this->pRecClass,
		start_x, RecConfig.regEnd[PAPER_REG_FHR],
		start_x + 40, RecConfig.regEnd[PAPER_REG_FHR], 0);

	this->pRecClass->RecPreLine(this->pRecClass,
		start_x, RecConfig.regStar[PAPER_REG_TOCO],
		start_x + 40, RecConfig.regStar[PAPER_REG_TOCO], 0);

	this->pRecClass->RecPreLine(this->pRecClass,
		start_x, RecConfig.regEnd[PAPER_REG_TOCO],
		start_x + 40, RecConfig.regEnd[PAPER_REG_TOCO], 0);

	start_x += 40;
	this->pRecClass->RecWriteIndexADD (this->pRecClass, start_x);
}

VOID gen_RecPutEndLine(PRECEVENTCLASS this)
{
//	UCHAR buf[64], end[3] = {'E', 'N', 'D'};
//	INT32 i, num, y_start, line_w;
//	PLOGFONT pLogFont = (PLOGFONT)this->pRecClass->font_normal;
//	memset (buf, ' ', sizeof(buf));
//	num = this->pRecClass->RecPaperInfo.maxHeight / pLogFont->size;
//	for (i = 0; i < num; i++)
//	{
//		if (i % 2 == 0)
//		{
//			buf[i] = '$';
//		}
//	}
//	memcpy(&buf[2], end, sizeof(end));
//	memcpy(&buf[(num - sizeof(end) + 1) / 2], end, sizeof(end));
//	memcpy(&buf[num - sizeof(end) - 3], end, sizeof(end));
//	buf[num] = 0;
//	y_start = this->pRecClass->RecPaperInfo.startPos;
//	line_w = this->pRecClass->RecPreShowCharacter(this->pRecClass, 0, y_start,
//													pLogFont, 0, 0, buf);
//	this->pRecClass->RecWriteIndexADD(this->pRecClass, line_w);
	/* 后切纸30mm */
	this->pRecClass->RecWriteIndexADD(this->pRecClass, RECORD_112_ENDLEN * 3);
}

static VOID DoNothing(PRECEVENTCLASS this)
{
	this = this;
}

static VOID RecSelfTest(PRECEVENTCLASS this);

BOOL RecEventClassInitOps(VOID)
{
	INT32 i;
	INT32 j;
	
	for (i = REC_EVENT_NOTHING; i < REC_EVENT_MAX; i++)
	{
		switch (i)
		{
			case REC_EVENT_NOTHING:
				RecEventClass.func[i] = DoNothing;
				break;

			case REC_EVENT_MONITOR:
				//RecEventClass.func[i] = RecRealTimeWave;
				RecEventClass.func[i] = RecTestWave;
				break;

			case REC_EVENT_TRENDGRAPH:
				RecEventClass.func[i] = DoNothing;//RecTrendGraphStart;
				break;

			case REC_EVENT_TRENDTABLE:
				RecEventClass.func[i] = DoNothing;//RecTrendTableStart;
				break;

			case REC_EVENT_OXYCRT:
				RecEventClass.func[i] = DoNothing;//RecOXYCRGStart;
				break;

			case REC_EVENT_ALM_RECALL:
				RecEventClass.func[i] = DoNothing;//RecAlmRecallStart;
				break;

			case REC_EVENT_NIBPLIST:
				RecEventClass.func[i] = DoNothing;//RecNibpListStart;
				break;

			case REC_EVENT_WAVERECALL:
				RecEventClass.func[i] = DoNothing;//RecWaveRecallStart;
				break;

			case REC_EVENT_FREEZE:
				RecEventClass.func[i] = DoNothing;//RecRealTimeWave;
				break;

			case REC_EVENT_SELFTEST:
				RecEventClass.func[i] = RecSelfTest;
				break;

			case REC_EVENT_FETAL:
				RecEventClass.func[i] = RecFetalStart;//RecRealTimeWave;
				RecEventClass.fetalAddData = &RecFHRControl;
				break;

			case REC_EVENT_RECALLPAGE:
				RecEventClass.func[i] = RecRecallPageStart;
				break;

			case REC_EVENT_RECALLALL:
				printf("lPPPPPPPPPPp\n");
				RecEventClass.func[i] = RecRecallAllStart;
				break;

			default:
				break;
		}		
	}
	//封装打印机装订线打印函数
	RecEventClass.RecPutGutter = gen_RecPutGutter;
	//封装打印机标尺打印函数
	RecEventClass.RecPutScale = gen_RecPrintFetalScale;
	//封装打印结束线打印函数
	RecEventClass.RecPutEndLine = gen_RecPutEndLine;
	
	RecEventClass.semaphore  = FALSE;
	if (PAPER_TYPE_112MM == MonitorConfig.RecorderType)
	{
		RecEventClass.pRecClass  = &RecCurveClass[PAPER_TYPE_112MM];
	}
	else
	{
		RecEventClass.pRecClass  = &RecCurveClass[PAPER_TYPE_PT1561P];
	}
	RecEventClass.lastSource = REC_EVENT_NOTHING;
	RecEventClass.source	 = REC_EVENT_NOTHING;	

	return TRUE;
}




/*****************************************************************************************
函数名称:	INT32  RecDataScale (INT32 data)
版本号:		1.0.0
生成日期:	2011.11.07
作者:		zondan
功能说明:	由于心电波形的特殊性，必须满足1mv标尺 = 1cm的要求，对心电波形进行增益调节
输入参数:	
输出参数:	
其它说明:	通过截取1mv校准信号后得知，数据最大值为152，最小值为98，若想在纸上变成1cm = 80pixel，
			必须对数据进行先一步的处理。
*****************************************************************************************/
INT32 RecDataScale (INT32 data)
{
	INT32  i;
	INT32  tmp_data = data;

	tmp_data -= 128;
	tmp_data = tmp_data * 5 / 3;
	tmp_data += 128;

	if (tmp_data < 0)
	{
		tmp_data = 0;
	}
	if (tmp_data > 255)
	{
		tmp_data = 255;
	}
	return tmp_data;
}


// The demo data of ecga channel one
#define ECG_SAMPLE_RATE 250
const UINT8 Ecg1_DemoData[ECG_SAMPLE_RATE + 6] = {
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7E, 0x7F, 0x81, 0x83, 0x83, 0x84, 0x85, 0x86,
  0x87, 0x87, 0x87, 0x87, 0x86, 0x85, 0x84, 0x83,

  0x82, 0x80, 0x7F, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7C, 0x7B, 0x7A, 0x78, 0x76, 0x79, 0x85,
  0x90, 0x9B, 0xA5, 0xB0, 0xB4, 0xAA, 0x9F, 0x94,
  0x89, 0x7E, 0x76, 0x77, 0x79, 0x7A, 0x7C, 0x7C,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D,
  0x7E, 0x80, 0x80, 0x82, 0x83, 0x84, 0x86, 0x87,
  0x88, 0x89, 0x8A, 0x8B, 0x8B, 0x8C, 0x8D, 0x8E,
  0x8F, 0x8F, 0x8F, 0x90, 0x90, 0x90, 0x90, 0x90,
  0x8F, 0x8E, 0x8D, 0x8C, 0x8B, 0x89, 0x89, 0x88,
  0x86, 0x85, 0x83, 0x82, 0x80, 0x7F, 0x7E, 0x7D,
  0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D, 0x7D
};
/*****************************************************************************************
函数名称:	VOID RecTestWave (VOID)
版本号:		1.0.0
生成日期:	2011.11.07
作者:		zondan
功能说明:	打印机测试函数，可根据需要进行适当的修改
输入参数:	
输出参数:	
其它说明:	
*****************************************************************************************/
VOID RecTestWave(PRECEVENTCLASS this)
{
	UINT8  test_buff[ECG_SAMPLE_RATE];
	UINT8  buff[3][200];
	INT32  x;
	INT32  i;
	UINT8  tmp;
	INT32  rate;
	INT32  index;
	INT32  offset;
	INT32  factor;
	INT32  sec = 0;
	INT32  data;
	UINT8  *ptr;
	UINT8  n1;
	UINT8  n2;

#if 0
	extern const INT8U *Ecg1_DemoDataHead;
	memcpy (test_buff, Ecg1_DemoDataHead, sizeof(test_buff));
#if _ENB_MYFB_RECORD_DEBUG_FUNC
	SetPenColor (HDC_SCREEN, PIXEL_magenta);
#endif
	for (i = 0; i < ECG_SAMPLE_RATE; i++)
	{
		tmp = test_buff[i];
		tmp = RecDataScale (tmp);
		test_buff[i] = tmp;
	}	
	for (x = 0; x < ECG_SAMPLE_RATE - 1; x++)
	{
		this->pRecClass->RecPreLine(this->pRecClass, x , test_buff[x], x + 1, test_buff[x + 1], 0);
#if _ENB_MYFB_RECORD_DEBUG_FUNC
		Line(HDC_SCREEN, x, SCREEN_HIGH - test_buff[x] - 100, x + 1, SCREEN_HIGH - test_buff[x + 1] - 100);
#endif
	}
	this->pRecClass->RecWriteIndexADD(this->pRecClass, ECG_SAMPLE_RATE);
#endif
#if 1
	UINT8 szStr[50] = "123456789ahjsgdf";
	UINT8 szChinese[80] = "深圳市和心重典医疗设备有限公司";
	INT32 width;

	this->pRecClass->RecPreShowCharacter(this->pRecClass, 0, 0,
						GetSystemFont(SYSLOGFONT_MINI), 1, 0, szStr);
	this->pRecClass->RecPreShowCharacter(this->pRecClass, 0, 10,
						GetSystemFont(SYSLOGFONT_DEFAULT), 1, 0, szStr);
	this->pRecClass->RecPreShowCharacter(this->pRecClass, 0, 30,
						GetSystemFont(SYSLOGFONT_WCHAR_DEF), 1, 0, szStr);
	this->pRecClass->RecPreShowCharacter(this->pRecClass, 0, 50,
						GetSystemFont(SYSLOGFONT_MICRO_PARAM), 1, 0, szStr);
	this->pRecClass->RecPreShowCharacter(this->pRecClass, 0, 80,
						GetSystemFont(SYSLOGFONT_SMALL_PARAM), 1, 0, szStr);
	this->pRecClass->RecPreShowCharacter(this->pRecClass, 0, 120,
						GetSystemFont(SYSLOGFONT_MID_PARAM), 1, 0, szStr);	
	this->pRecClass->RecPreShowCharacter(this->pRecClass, 0, 180,
						GetSystemFont(SYSLOGFONT_BIG_PARAM), 1, 0, szStr);	
	this->pRecClass->RecPreShowCharacter(this->pRecClass, 0, 350,
						GetSystemFont(SYSLOGFONT_WCHAR_DEF), 1, 0, szChinese);
	this->pRecClass->RecPreShowCharacter(this->pRecClass, 0, 400,
						GetSystemFont(SYSLOGFONT_FIXED),
						1, 0, szChinese);
	memcpy (test_buff, Ecg1_DemoData, sizeof(test_buff));
#if _ENB_MYFB_RECORD_DEBUG_FUNC
	SetPenColor (HDC_SCREEN, PIXEL_magenta);
#endif
	for (i = 0; i < ECG_SAMPLE_RATE; i++)
	{
		tmp = test_buff[i];
		tmp = RecDataScale (tmp);
		test_buff[i] = tmp;
	}	
	for (x = 0; x < ECG_SAMPLE_RATE - 1; x++)
	{
		this->pRecClass->RecPreLine (this->pRecClass, x , SCREEN_HIGH - test_buff[x] + 50, x + 1, SCREEN_HIGH - test_buff[x + 1] + 50, 0);
#if _ENB_MYFB_RECORD_DEBUG_FUNC
		Line(HDC_SCREEN, x, SCREEN_HIGH - test_buff[x] - 100, x + 1, SCREEN_HIGH - test_buff[x + 1] - 100);
#endif
	}
	this->pRecClass->RecWriteIndexADD(this->pRecClass, 780);
	this->RecPutEndLine(this);
#endif
}

// 输出标准三角波
static VOID TriangularWave(PRECEVENTCLASS this)
{
	INT32 i, loops, x, y1, y2, offset;
	UCHAR szStr[128];
	loops = 20;
	offset = 80;
	y1 = 350;
	y2 = y1 + offset;
	x = 0;
	sprintf(szStr, "x=%d, y1=%d, y2=%d, offset=%d, loops= %d",
					x,	y1,	y2,	offset,	loops);
	this->pRecClass->RecPreShowCharacter(this->pRecClass,
		x, 300, NULL, 1, 0, szStr);
	for (i = 0; i < loops; i++)
	{
		this->pRecClass->RecPreLine (this->pRecClass, x, y2, x+offset, y1, 1);
		x += offset;
		this->pRecClass->RecPreLine (this->pRecClass, x, y1, x+offset, y2, 1);
		x += offset;
	}
	i = 0;
	while(i < x + 48)
	{
		if (!RecEventClass.semaphore)
		{
			GET_RECSTARTUP_PERMIT();
			RecEventClass.semaphore = TRUE;  //stop recording
			RELEASE_STARTUP_PERMIT();
		}
		this->pRecClass->RecWriteIndexADD(this->pRecClass, offset);
		i += offset;
		ms_sleep(10000);
	}
}

VOID Printer112SendEndCommand(PRECDRVCLASS this)
{
	int toSend = 0;
	INT32 Send;
	UCHAR *p = (UCHAR *)this->Data;
	*(p + 3) = 4;
	*(p + 5) = 0x81;
	*(p + 6) = 0;
	*(p + 7) = 0;
	toSend = BuildPacket(PRINT_MODULE_ID, PRINT_RTN_CMD_ID, this->Data);
	MdlUartTran(this->uartPort, this->Data, toSend, &Send);
}

static VOID RecSelfTest(PRECEVENTCLASS this)
{
//	TriangularWave(this);return;
	UCHAR szStr[16];
	INT32 start_x = 0;
	INT32 width = 0;
	INT32 maxwidth = 0;
	// 预打印标尺
	if (!RecConfig.isScale)
		this->RecPutScale(this, TRUE);
	
	maxwidth += 40;
	#if 1
	// "打印机自检..."
	strcpy(szStr, "Test");
	width = this->pRecClass->RecPreShowCharacter(this->pRecClass, start_x, 
		(RecConfig.regStar[PAPER_REG_FHR]+RecConfig.regEnd[PAPER_REG_FHR])/2,
		NULL, 1, 0, szStr);
	
	width = this->pRecClass->RecPreShowCharacter(this->pRecClass, start_x, 
		(RecConfig.regStar[PAPER_REG_TOCO]+RecConfig.regEnd[PAPER_REG_TOCO])/2,
		NULL, 1, 0, szStr);

	#endif
	#if 1 // 多行直线
	int i;
	int hi;
	hi = RecConfig.regEnd[PAPER_REG_TOCO] - RecConfig.regStar[PAPER_REG_TOCO];
	for (i = 0; i <= 10; i++)
	{
		this->pRecClass->RecPreLine(this->pRecClass,
		start_x, RecConfig.regStar[PAPER_REG_TOCO] + hi * i / 10,
		start_x + 40, RecConfig.regStar[PAPER_REG_TOCO] + hi * i / 10, 0);
	}
	hi = RecConfig.regEnd[PAPER_REG_FHR] - RecConfig.regStar[PAPER_REG_FHR];
	for (i = 0; i <= 15; i++)
	{
		this->pRecClass->RecPreLine(this->pRecClass,
		start_x, RecConfig.regStar[PAPER_REG_FHR] + hi * i / 15,
		start_x + 40, RecConfig.regStar[PAPER_REG_FHR] + hi * i / 15, 0);
	}
	maxwidth += 40;
	#endif
	#if 1 // top
	if (RecConfig.fhrMax > 0)
	{
		//210
		this->pRecClass->RecPreLine(this->pRecClass,
			start_x, RecConfig.regStar[PAPER_REG_FHR] + 10,
			start_x + 10, RecConfig.regStar[PAPER_REG_FHR], 1);
		this->pRecClass->RecPreLine(this->pRecClass,
			start_x + 10, RecConfig.regStar[PAPER_REG_FHR],
			start_x + 20, RecConfig.regStar[PAPER_REG_FHR] + 10, 1);
		this->pRecClass->RecPreLine(this->pRecClass,
			start_x + 9, RecConfig.regStar[PAPER_REG_FHR],
			start_x + 9, RecConfig.regStar[PAPER_REG_FHR] + 16, 1);
		
		strcpy(szStr, "Top");
		int i = this->pRecClass->RecPreShowCharacter(this->pRecClass,
			start_x, RecConfig.regStar[PAPER_REG_FHR] + 30, NULL, 1, 0,
			szStr);
		if (width < i)
			width = i;
	}
	else
	{
		int hi;
		hi = RecConfig.regEnd[PAPER_REG_FHR] - RecConfig.regStar[PAPER_REG_FHR];
		hi = hi * (240 - 210) / (210 - 60);
		hi = RecConfig.regStar[PAPER_REG_FHR] - hi;
		if (hi < 0)
		{
			hi = 0;
		}
		//240
		this->pRecClass->RecPreLine(this->pRecClass,
			start_x, hi + 10, start_x + 10, hi, 1);
		this->pRecClass->RecPreLine(this->pRecClass,
			start_x + 10, hi, start_x + 20, hi + 10, 1);
		this->pRecClass->RecPreLine(this->pRecClass,
			start_x + 9, hi, start_x + 9, hi + 30, 1);
		
		strcpy(szStr, "Top");
		i = this->pRecClass->RecPreShowCharacter(this->pRecClass,
			start_x, hi + 32, NULL, 1, 0, szStr);
		if (width < i)
			width = i;
	}
	#endif
	if (maxwidth < width + start_x)
		maxwidth = width + start_x;
	this->pRecClass->RecWriteIndexADD(this->pRecClass, maxwidth + 8);
	this->RecPutEndLine(this);
}

INT32 PrinterPutIcon(PRECEVENTCLASS this,INT32 x, INT32 y, RECICONID icon)
{
	return (this->pRecClass->RecDrawBitmap(this->pRecClass, x, y, icon));
}

INT32 RecordService(INT32 rec_type)
{
	if (RecEventClass.semaphore)
	{
		GET_RECSTARTUP_PERMIT();
		RecEventClass.semaphore = FALSE;  //stop recording
		RELEASE_STARTUP_PERMIT();
	}
  	PostMessage(SysRec_HTSK, MSG_PRTCL_PRINTER, rec_type, 0);
	return 0;
}


/*****************************************************************************************
函数名称:	VOID RecScaleWave (UINT16 top, UINT16 bottom, UINT16 mindata, 
											UINT16 maxdata, INT16 *data, UINT16 len)
版本号:		1.0.0
生成日期:	2011.11.15
作者:		zondan
功能说明:	根据波形区域和波形值的范围计算出相对于打印纸位置的数据
输入参数:	
输出参数:	
其它说明:	
*****************************************************************************************/
VOID RecScaleWave(INT32 top, INT32 bottom, INT32 mindata, INT32 maxdata, INT32 *data, INT32 len)
{
	INT32 i;
	UINT32 sum;
	INT32  diff = maxdata - mindata;
	INT32  tmp  = 0;
	INT32  high = bottom - top;

	for (i = 0; i < len; i++)
	{
		if (data[i] != INVALID_PARAM)
		{
			if (data[i] < mindata)
			{
				data[i] = -1;
				continue;
			}
			else if (data[i] > maxdata)
			{
				data[i] = -1;
				continue;
			}
			sum = (data[i] - mindata) * high;
			tmp = bottom - (UINT16)((double)sum / diff + 0.5);
			if (tmp < top)
			{
				data[i] = top;
			}
			else
			{
				data[i] = tmp;
			}
		}
	}
}


/*****************************************************************************************
函数名称:	VOID TskPrintComSend (VOID *pdata)
版本号:		1.0.0
生成日期:	2011.11.15
作者:		zondan
功能说明:	根据波形区域和波形值的范围计算出相对于打印纸位置的数据
输入参数:	
输出参数:	
其它说明:	一定要注意这里的时序，不然readIndex会在多任务中被修改
*****************************************************************************************/
VOID TskPrintComSend(VOID *pdata)
{
	INT32	i;
	INT32	read_x;
	INT32	write_x;
	INT32	head_x;
	INT32	tail_x;
	PRECDRVCLASS this	= RecEventClass.pRecClass;
	BOOL	*SendFlag	= &RecEventClass.isUartSending;
	INT32	*semaphore	= &RecEventClass.semaphore;
	INT32	interval	= 0;
	read_x	= 0;
	write_x	= 0;
	head_x	= 0;
	tail_x	= 0;
	while (1)
	{
		//Pt1561DebugProc();
		GET_RECDATA_PERMIT();
		if (this->RecTrusteeship)
		{
			this->RecTrusteeship(this, NULL);
		}
		RELEASE_RECDATA_PERMIT();
		if (head_x == tail_x)
		{
			head_x	= this->RecGetHeadIndex (this);
			tail_x	= this->RecGetTailIndex (this);
		}
		read_x	= this->RecGetReadIndex (this);
		write_x = this->RecGetWriteIndex(this);
		if (read_x == write_x)			
		{
			ms_sleep(RECORD_DELAYTICKS);
			continue;
		}
		if (*semaphore)
		{
			switch (this->RecPaperInfo.paperType)
			{
				case PAPER_TYPE_150MM:
				{		
					*SendFlag = TRUE;
					this->RecPrintSend (this);
					GET_RECGRAPH_PERMIT();
					read_x  = this->RecGetReadIndex (this);
					write_x = this->RecGetWriteIndex(this);
					if (read_x >= tail_x)
					{
						read_x = head_x;
					}
					else
					{
						read_x ++;
					}
					this->RecSetReadIndex(this, read_x);
					RELEASE_RECGRAPH_PERMIT();
					*SendFlag = FALSE;
					break;
				}
				case PAPER_TYPE_110MM:
				{
					*SendFlag = TRUE;
					this->RecPrintSend (this);
					GET_RECGRAPH_PERMIT();
					read_x  = this->RecGetReadIndex (this);
					write_x = this->RecGetWriteIndex(this);
					if (read_x > write_x)
					{
						interval = write_x + tail_x + 1 - read_x;
					}
					else
					{
						interval = write_x - read_x;
					}

					/* 若图形区大于24，则正常输出，
					但是须注意边界部分的回绕处理 */
					if (interval >= 24)
					{
						for (i = 0; i < 24; i++)
						{
							if (++ read_x > tail_x)
							{
								read_x = head_x;
							}
						}
					}
					else
					{
						/* 若不足24，则认为补齐，
						但是读指针不应超过写指针，
						导致错误发生 */
						read_x = write_x;
					}
					this->RecSetReadIndex(this, read_x);
					RELEASE_RECGRAPH_PERMIT();
					*SendFlag = FALSE;
					break;
				}
				case PAPER_TYPE_112MM:
				{
					if (RecConfig.recstatus)//打印机异常,停止发送
					{
//						printf("RecConfig.recstatus...%p\n", RecConfig.recstatus);
						break;
					}
					*SendFlag = TRUE;
					GET_RECGRAPH_PERMIT();
					read_x	= this->RecGetReadIndex(this);
					write_x = this->RecGetWriteIndex(this);
					if (read_x != write_x)
					{
						for (i = 0; i < 12; i++) // 50mm/s 4p/10ms
						{
							this->RecPrintSend (this);
//	printf ("TskPrintComSend:1:read_x, write_x ... %d,%d\r\n", read_x, write_x);
							if (read_x >= tail_x)
							{
								read_x = head_x;
							}
							else
							{
								read_x ++;
							}
//	printf ("TskPrintComSend:2:read_x, write_x ... %d,%d\r\n", read_x, write_x);
							this->RecSetReadIndex(this, read_x);
							if (read_x == write_x) break;
						}
					}
					RELEASE_RECGRAPH_PERMIT();
					*SendFlag = FALSE;
					break;
				}

				case PAPER_TYPE_PT1561P:
					//Pt1561DebugProc();
					//ms_sleep(RECORD_DELAYTICKS);
					if (RecConfig.recstatus)//打印机异常,停止发送
					{
						//printf("RecConfig.recstatus...%ld\n", RecConfig.recstatus);
						break;
					}
					*SendFlag = TRUE;
					this->RecPrintSend (this);
					GET_RECGRAPH_PERMIT();
					read_x  = this->RecGetReadIndex (this);
					write_x = this->RecGetWriteIndex(this);
					//printf ("TskPrintComSend:read_x, write_x ... %d,%d\r\n", read_x, write_x);
					if (read_x != write_x)
					{
						if (read_x >= tail_x)
						{
							read_x = head_x;
						}
						else
						{
							read_x ++;
						}
						this->RecSetReadIndex(this, read_x);
					}
					RELEASE_RECGRAPH_PERMIT();
					*SendFlag = FALSE;
					break;

				default:
				{
					*SendFlag = TRUE;
					this->RecPrintSend (this);
					GET_RECGRAPH_PERMIT();
					read_x  = this->RecGetReadIndex (this);
					write_x = this->RecGetWriteIndex(this);
					if (read_x >= tail_x)
					{
						read_x = head_x;
					}
					else
					{
						read_x ++;
					}
					this->RecSetReadIndex(this, read_x);
					RELEASE_RECGRAPH_PERMIT();
					*SendFlag = FALSE;
					break;
				}
			}
			#if (!_ENB_MYFB_RECORD_DEBUG_FUNC)
			ms_sleep(RECORD_DELAYTICKS);
			#endif			
		}
		else
		{
			ms_sleep(RECORD_DELAYTICKS);
		}
		if (KillSignal)
		{
			KillSignal++;
			break;
		}
	}
	if (KillSignal > 1)
		KillSignal--;
}


/*******************************************************************************
函数名称:	VOID RecDealWithEvents (INT32 source)
版本号:		1.0.0
生成日期:	2011.11.15
作者:		zondan
功能说明:	打印机事件处理函数
输入参数:	
输出参数:	
其它说明:	打印机事件包括:新事件发生、中断事件发生、打印机停止
*******************************************************************************/
VOID RecDealWithEvents(INT32 source)
{
	PRECEVENTCLASS this = &RecEventClass;
	INT32  tmp_rindex = 0;
	INT32  tmp_windex = 0;
	INT32  i;	
	INT32  tailIndex = this->pRecClass->RecGetTailIndex (this->pRecClass);
	INT32  headIndex = this->pRecClass->RecGetHeadIndex (this->pRecClass);
	INT32  diff      = 0;
	UINT32 beginFlag = this->fetalAddData->isBegin;
	this->source = source;
	this->fetalAddData->isBegin = FALSE;
	tmp_rindex   = this->pRecClass->RecGetReadIndex(this->pRecClass);
	tmp_windex   = this->pRecClass->RecGetWriteIndex(this->pRecClass);

	GET_RECDATA_PERMIT();
	if (this->pRecClass->RecTrusteeship)
	{
		// 有托管打印发生,传入NULL以释放资源
		this->pRecClass->RecTrusteeship(NULL, (INT32*)this);
	}
	RELEASE_RECDATA_PERMIT();
	//中断打印事件发生
	if (tmp_rindex != tmp_windex || beginFlag)
	{
		if (tmp_windex > tmp_rindex)
		{
			diff = tmp_windex - tmp_rindex;
		}
		else
		{
			diff = tmp_windex + tailIndex + 1 - tmp_rindex;
		}
		for (i = 0; i < diff; i++)
		{
			if (++ tmp_rindex > tailIndex)
			{
				tmp_rindex = headIndex;
			}
			this->pRecClass->RecClrGraphBuff(this->pRecClass, tmp_rindex);
		}
		
		GET_RECGRAPH_PERMIT();
		this->pRecClass->RecSetReadIndex(this->pRecClass, tmp_windex);
		RELEASE_RECGRAPH_PERMIT();
		
		tmp_rindex	 = this->pRecClass->RecGetReadIndex(this->pRecClass);
		tmp_windex	 = this->pRecClass->RecGetWriteIndex(this->pRecClass);
		//打印结束命令
		Printer112SendEndCommand(this->pRecClass);

		//缓冲区已清理，开启打印机
		GET_RECSTARTUP_PERMIT();
		this->semaphore = TRUE;
		RELEASE_STARTUP_PERMIT();
		// 后切纸处理
		if (beginFlag)
		{
			RecFetalEnd(this);
		}
		else
		{
			this->RecPutEndLine(this);
		}
		
		if (this->lastSource != this->source)
		{
			RecPreStartup (this);
		}		
	}
	//不为中断打印事件
	else
	{
		//首先恢复打印机
		GET_RECSTARTUP_PERMIT();
		this->semaphore = TRUE;
		RELEASE_STARTUP_PERMIT();

		//构建打印缓冲区数据
		RecPreStartup(this);
	}
	this->lastSource = this->source;
}


/*****************************************************************************************
函数名称:	VOID RecPreStartup (PRECEVENTCLASS this)
版本号:		1.0.0
生成日期:	2011.11.15
作者:		zondan
功能说明:	切纸及开始封装打印缓冲区
输入参数:	
输出参数:	
其它说明:	目前设计:前切纸0.5cm，后切纸1.5cm
*****************************************************************************************/
VOID RecPreStartup(PRECEVENTCLASS this)
{
	while (this->isUartSending)
	{
		OSTimeDlyHMSM (0, 0, 0, RECORD_DELAYTICKS);
	}

#if _ENB_MYFB_RECORD_DEBUG_FUNC
	BacktoMainScreen ();
	//MonitorInfo.standby = 1;
	EnterStandby();
	fb_fillrect_ex(0, 0, 0, SCREEN_WIDTH, SCREEN_HIGH, 0, 0, 0);
	this->pRecClass->RecSetReadIndex(this->pRecClass, 0);
	this->pRecClass->RecSetWriteIndex(this->pRecClass, 0);
#endif
	
#if (!_ENB_MYFB_RECORD_DEBUG_FUNC)
	this->pRecClass->RecPrintCR(this->pRecClass, this->pRecClass->RecPaperInfo.printHeadWidth * 10); //出纸1cm
#endif

	this->RecPutGutter(this);
	this->RecPutScale(this, RecConfig.isScale);
	this->func[this->source](this);
	
#if (!_ENB_MYFB_RECORD_DEBUG_FUNC)
	this->pRecClass->RecPrintCR(this->pRecClass, this->pRecClass->RecPaperInfo.printHeadWidth * 15); //出纸1.5cm
#endif
}

VOID PrinterSendPacket(PACKETFRAME *pack)
{
	INT32 send, len;
	len = BuildPacket2(pack);
	MdlUartTran(UART_PORT_PRINTER, pack, len, &send);
	if (len != send)
	{
		printf("FetalSendPack::injure packet!!\r\n");
	}
}

BOOL PrinterPacketFound(PACKETFRAME *pack)
{
	if (pack->frame.id == PRINT_MODULE_ID)
	{
		UCHAR i;
		printf("PrinterPacketFound::\r\ndata::");
		for (i = 0; i < pack->frame.len; i++)
		{
			printf("0x%02X,", pack->frame.data[i]);
		}
		printf("\r\n");
		return TRUE;
	}
	return FALSE;
}

INT32
PrinterDataCompression(PRECDRVCLASS this, UCHAR *buffer)
{
	int i;
	int ct00 = 0;
	int ctff = 0;
	int ser  = 5;   // data is begin from the fifth

	UCHAR *p = (UCHAR *)this->Data;
	//ZeroMemory(this->Data, 215);
//	printf("\n");
	for (i = 0; i < this->imgLineLen; i++)
	{
		switch(buffer[i])
		{
			case 0x00:
				if( ctff >0)
				{
					*(p + ser) = ctff;
					ser++;
					ctff = 0;
				}
				ct00++;
				if (ct00 == 1)
				{
					*(p + ser) = 0x00;
					ser++;
				}
				if (i == 103)
				{
					*(p + ser) = ct00;
					ser++;
				}
				break;
				
			case 0xff:
				if (ct00 > 0)
				{
					*(p + ser) = ct00;
					ser++;
					ct00 = 0;
				}
				ctff++;
				if (ctff == 1)
				{
					*(p + ser) = 0xff;
					ser++;
				}
				if (i == 103)
				{
					*(p + ser) = ctff;
					ser++;
				}
				break;
				
			default:
				if (ctff >0)
				{
					*(p + ser) = ctff;
					ser++;
					ctff = 0;
				}
				if (ct00 >0)
				{
					*(p + ser) = ct00;
					ser++;
					ct00 = 0;
				}
				*(p + ser) = buffer[i];
				ser++;
				break;
		}
//		printf("0x%02X,", buffer[i]);
	}
	*(p + 3) = ser - 4;
	return BuildPacket(PRINT_MODULE_ID, PRINT_RTN_DATA_ID, this->Data);
	#if 0
	this->Data[0] = CommPrintPackHead[PRINT_RTN_DATA_INDEX_DATA][0];
	this->Data[1] = CommPrintPackHead[PRINT_RTN_DATA_INDEX_DATA][1];
	this->Data[2] = CommPrintPackHead[PRINT_RTN_DATA_INDEX_DATA][2];
	this->Data[3] = ser - 4;
	this->Data[4] = CommPrintPackHead[PRINT_RTN_DATA_INDEX_DATA][4];
	this->Data[ser++] = GetChkSum(this->Data);
	this->Data[ser++] = cUCAllCommPackEnd;
	return ser;
	#endif
}

void PrintLine_112mm(PRECDRVCLASS this)
{
	if(this->RecPaperInfo.paperType == PAPER_TYPE_112MM)
	{
		INT32 toSend, Send, i;
		UCHAR *buff = this->RecGraphInfo.imgbuff[this->RecGraphInfo.readIndex];
		//printf("PrintLine_112mm::this->imgLineLen:%d\r\n", this->imgLineLen);
		toSend = PrinterDataCompression(this, buff);
//		UCHAR temp[] = {0x55, 0x02, 0x79, 0x03, 0x31, 0x00, 0x68, 0x00, 0x03};
//		MdlUartTran(this->uartPort, temp, sizeof(temp), &Send);
		MdlUartTran(this->uartPort, this->Data, toSend, &Send);
		if (toSend > Send)
		{
			//printf("PrintLine_112mm::injure packet!!\r\n");
		}
#if 0
		prinfo("this->uartPort, toSend, Send...%d, %d, %d\r\n", this->uartPort, toSend, Send);
		printf("outdata...");
		for (i = 0; i < toSend; i++)
		{
			if (i % 10 == 0)
				printf("\r\n");
			printf("0x%02X,", *((UCHAR*)this->Data + i));
		}
		printf("\r\n");
#endif
	}
}

VOID PrinterTestFunc(VOID)
{
	static UCHAR tsbuff[104] = {0};
	tsbuff[10] = 0x66;
	tsbuff[20] = 0x81;
	tsbuff[30] = 0x42;
	memcpy(RecCurveClass[PAPER_TYPE_112MM].RecGraphInfo.imgbuff[0], tsbuff, sizeof(tsbuff));
	RecCurveClass[PAPER_TYPE_112MM].RecSetReadIndex(&RecCurveClass[PAPER_TYPE_112MM], 0);
	RecCurveClass[PAPER_TYPE_112MM].RecSetWriteIndex(&RecCurveClass[PAPER_TYPE_112MM], 1);
	//memset(tsbuff, 0xAA, sizeof(tsbuff));
	PrintLine_112mm(&RecCurveClass[PAPER_TYPE_112MM]);
}

extern UINT8 LCSysBoard;
VOID PrinterInitFunc(PRECDRVCLASS this)
{
	if (LCSysBoard && MONITOR_TYPE_AR4S == MonitorConfig.MonitorName)
	{
		this->uartPort = UART_PORT_KB;
	}
	else
	{
		MDL_UARTCFG ComCfg;
		ComCfg.baudRate = MapUartBPS(115200);
		ComCfg.parity   = PARITY_NO;
		ComCfg.dataBits = DBTS_8;
		ComCfg.stopBits = STOPBITS_1;
		MdlUartSetup(this->uartPort, &ComCfg);
		if (MdlUartOpen(this->uartPort))
		{
			return;
		}
	}
	if (this->RecPaperInfo.paperType == PAPER_TYPE_112MM)
	{
		int toSend = 0;
		INT32 Send;
		UCHAR *p = (UCHAR *)this->Data;
		*(p + 3) = 4;
		*(p + 5) = 1;
		*(p + 6) = 0;
		*(p + 7) = 0;
		toSend = BuildPacket(PRINT_MODULE_ID, PRINT_RTN_CMD_ID, this->Data);
		MdlUartTran(this->uartPort, this->Data, toSend, &Send);
	}
	if (this->RecPaperInfo.paperType == PAPER_TYPE_PT1561P)
	{
		char start[3] = { 0x1B, 0x3D, 0x01 };
		Pt1561SendPacket(start, sizeof(start)); // allow recorder
		char initcmd[2] = { 0x1B, 0x40 };
		Pt1561SendPacket(initcmd, sizeof(initcmd));// init recorder
		char freeback[3] = { 0x1B, 0x1B, 0x01 };
		Pt1561SendPacket(freeback, sizeof(freeback));
		char version[3] = { 0x1B, 0x1B, 0x03 };
		Pt1561SendPacket(version, sizeof(version));
	}
#if 0
	int i;
	prinfo("toSend, Send...%d, %d\r\n", toSend, Send);
	printf("outdata...");
	for (i = 0; i < toSend; i++)
	{
		if (i % 10 == 0)
			printf("\r\n");
		printf("0x%02X,", *(p + i));
	}
	printf("\r\n");
#endif
}


VOID PrinterSetChroma(PRECDRVCLASS this)
{
	int toSend = 0;
	INT32 Send;
	UCHAR *p = (UCHAR *)this->Data;
	*(p + 3) = 4;
	*(p + 5) = 2;
	*(p + 6) = ((UCHAR)RecConfig.chroma >> 1);
	*(p + 7) = 0;
	toSend = BuildPacket(PRINT_MODULE_ID, PRINT_RTN_CMD_ID, this->Data);
	MdlUartTran(this->uartPort, this->Data, toSend, &Send);
	
#if 0
	int i;
	prinfo("toSend, Send...%d, %d\r\n", toSend, Send);
	printf("outdata...");
	for (i = 0; i < toSend; i++)
	{
		if (i % 10 == 0)
			printf("\r\n");
		printf("0x%02X,", *(p + i));
	}
	printf("\r\n");
#endif
}

BOOL Pt1561SendPacket(void *buff, int len)
{
/**
	HEAD  n  DATA1  DAT2  DATE3  ??  DATEn  CHECK  END
	其中:
	HEAD = 0XAA
	END = 0XBB
	N <= 46 为数据长度(不包含校验)
	CHECK = DATA1 XOR DATA2 XOR DATA3 XOR DATA4 XOR ?? XOR DATAn
**/
	BOOL ret = TRUE;
	PRECDRVCLASS this	= RecEventClass.pRecClass;
	INT32 toSend = 0;
	INT32 Send = 0;
	char *pbuff = (char*)buff;
	char foo[50];
	int i;
	int ndx = 0;
	char chksum = 0;
	int j;
	int remain = 0;
	foo[0] = 0xAA;
	if (len > 46)
	{
		foo[1] = 46;
		remain = len - foo[1];
	}
	else
	{
		foo[1] = len;
	}
	memcpy(&foo[2], pbuff, (size_t)foo[1]);
	for (i = 0; i < foo[1]; i++)
	{
		chksum ^= foo[2 + i];
	}
	foo[2 + foo[1]] = chksum;
	foo[3 + foo[1]] = 0xBB;
	pbuff += (int)foo[1];
	toSend = foo[1] + 4;
	MdlUartTran(this->uartPort, foo, toSend, &Send);
	if (toSend != Send)
	{
		ret = FALSE;
	}
	#if 0
	else
	{
		printf("Pt1561SendPacket::");
		for (i = 0; i < Send; i++)
		{
			printf("0x%02X,", foo[i]);
		}
		printf("\n");
	}
	#endif
	if (remain > 0)
		ret &= Pt1561SendPacket(pbuff, remain);
	return ret;
}

void SetPt1561pVersion(char *ver)
{
	printf("PT1561P Version %d.%d.%d\n", ver[0], ver[1], ver[2]);
}

void Pt1561pAlarmPacket(char *alarm)
{
	switch (*alarm)
	{
		case 0x01:
			if (RecConfig.recstatus == PRINT_RTN_PAPER)
			{
				if (*(alarm + 1) == 0)
				{
					RecConfig.recstatus = 0;
					TriggerAlarm(FALSE, STR_ALM_PRINTER_PAPER_OUT);
				}
			}
			else if (RecConfig.recstatus == 0)
			{
				if (*(alarm + 1) == 1)
				{
					RecConfig.recstatus = PRINT_RTN_PAPER;
					//printf("Pt1561pAlarmPacket::PRINT_RTN_PAPER\n");
					TriggerAlarm(TRUE, STR_ALM_PRINTER_PAPER_OUT);
				}
			}
			break;

		case 0x02:
			if (RecConfig.recstatus == PRINT_RTN_OPEN)
			{
				if (*(alarm + 1) == 0)
				{
					RecConfig.recstatus = 0;
					TriggerAlarm(FALSE, STR_ALM_PRINTER_DOOR_NOT_CLOSED);
				}
			}
			else
			{
				if (*(alarm + 1) == 0x01)
				{
					RecConfig.recstatus = PRINT_RTN_OPEN;
					//printf("Pt1561pAlarmPacket::PRINT_RTN_OPEN\n");
					TriggerAlarm(TRUE, STR_ALM_PRINTER_DOOR_NOT_CLOSED);
				}
			}
			break;

		case 0x03:
			if (*(alarm + 1) == 0x01)
			{
				printf("Pt1561pAlarmPacket::Paper type is American Standard\n");
			}
			else
			{
				printf("Pt1561pAlarmPacket::Paper type is European Standard\n");
			}
			break;

		default:
			break;
	}
}

int str2hex(UCHAR *str)
{
	UCHAR swap;
	UCHAR flag = 0;
	UCHAR *p = str;
	UCHAR *phex = str;
	while(*p != '\0')
	{
		if (*p >= '0' && *p <= '9')
		{
			swap = *p - '0';
			flag++;
		}
		else if (*p >= 'A' && *p <= 'F')
		{
			swap = *p - 'A' + 0x0A;
			flag++;
		}
		else if (*p >= 'a' && *p <= 'f')
		{
			swap = *p - 'a' + 0x0A;
			flag++;
		}
		else if (flag == 1)
		{
			swap = 0xFF;
			flag = 2;
		}
		if (flag == 1)
		{
			*phex = swap;
		}
		if (flag == 2)
		{
			if (swap > 0x0F)
			{
				phex++;
			}
			else
			{
				*phex++ = swap + ((*phex) << 4);
			}
			swap = 0;
			flag = 0;
		}
		p++;
	}
	if (flag == 1)
		phex++;
	return (phex - str);
}

/**
	for test packet
**/
void Pt1561DebugProc(void)
{
	static FILE *fp = NULL;
	if (fp == NULL)
	{
		unlink("/tmp/pt1561");
		int ret = mkfifo("/tmp/pt1561", 0777);
		if (ret == 0)
		{
			fp = fopen("/tmp/pt1561", "r");
		}
	}
	if (fp != NULL)
	{
		char cmd[512];
		cmd[0] = 0;
		fseek(fp, 0, SEEK_SET);
		if (NULL != fgets(cmd, sizeof(cmd), fp))
		{
			char flag = cmd[0];
			int nr = str2hex(cmd);
			if (nr > 0)
			{
				if (flag != '+')
				{
					INT32 toSend = nr;
					INT32 Send = 0;
					MdlUartTran(RecEventClass.pRecClass->uartPort,
						cmd, toSend, &Send);
					printf("Pt1561DebugProc::");
					for (nr = 0; nr < toSend; nr++)
						printf("0x%02X,", cmd[nr]);
					printf("\n");
					ms_sleep(100);
				}
				else
				{
					Pt1561SendPacket(cmd, nr);
				}
			}
		}
	}
}


VOID UpdatePrinterStatus(VOID)
{
	static UCHAR AlmFlag = 0;
//	PROMPT_ONLY
	switch (LOBYTE(RecConfig.recstatus))
	{
		case PRINT_RTN_HOT:
			if (AlmFlag != LOBYTE(RecConfig.recstatus))
			{
				TriggerAlarm(FALSE, STR_ALM_PRINTER_DOOR_NOT_CLOSED);
				TriggerAlarm(FALSE, STR_ALM_PRINTER_PAPER_OUT);
				TriggerAlarm(TRUE, STR_ALM_PRINTER_HEAD_HOT);
			}
			break;

		case PRINT_RTN_OPEN:
			if (AlmFlag != LOBYTE(RecConfig.recstatus))
			{
				TriggerAlarm(TRUE, STR_ALM_PRINTER_DOOR_NOT_CLOSED);
				TriggerAlarm(FALSE, STR_ALM_PRINTER_PAPER_OUT);
				TriggerAlarm(FALSE, STR_ALM_PRINTER_HEAD_HOT);
			}
			break;

		case PRINT_RTN_PAPER:
			if (AlmFlag != LOBYTE(RecConfig.recstatus))
			{
				TriggerAlarm(FALSE, STR_ALM_PRINTER_DOOR_NOT_CLOSED);
				TriggerAlarm(TRUE, STR_ALM_PRINTER_PAPER_OUT);
				TriggerAlarm(FALSE, STR_ALM_PRINTER_HEAD_HOT);
			}
			break;

		default:
			TriggerAlarm(FALSE, STR_ALM_PRINTER_DOOR_NOT_CLOSED);
			TriggerAlarm(FALSE, STR_ALM_PRINTER_PAPER_OUT);
			TriggerAlarm(FALSE, STR_ALM_PRINTER_HEAD_HOT);
			break;
	}
	if (AlmFlag != LOBYTE(RecConfig.recstatus))
		AlmFlag = LOBYTE(RecConfig.recstatus);		
}

static STRINGID StrID_FhrMax[2] = { STR_DLG_PRINTER_240, STR_DLG_PRINTER_210 };
static STRINGID StrID_FhrMin[2] = { STR_DLG_PRINTER_30,  STR_DLG_PRINTER_60  };
VOID InitRceRegion(VOID)
{
	if ((RecConfig.regStar[PAPER_REG_FHR] > REC_REGION_FHR210_MAX)
		||(RecConfig.regStar[PAPER_REG_FHR] < REC_REGION_FHR210_MIN))
	{
		RecConfig.regStar[PAPER_REG_FHR] = REC_REGION_FHR210_112;
	}
	if ((RecConfig.regEnd[PAPER_REG_FHR] > REC_REGION_FHR60_MAX)
		||(RecConfig.regEnd[PAPER_REG_FHR] < REC_REGION_FHR60_MIN))
	{
		RecConfig.regEnd[PAPER_REG_FHR] = REC_REGION_FHR60_112;
	}
	if ((RecConfig.regStar[PAPER_REG_TOCO] > REC_REGION_TOCO100_MAX)
		||(RecConfig.regStar[PAPER_REG_TOCO] < REC_REGION_TOCO100_MIN))
	{
		RecConfig.regStar[PAPER_REG_TOCO] = REC_REGION_TOCO100_112;
	}
	if ((RecConfig.regEnd[PAPER_REG_TOCO] > REC_REGION_TOCO0_MAX)
		||(RecConfig.regEnd[PAPER_REG_TOCO] < REC_REGION_TOCO0_MIN))
	{
		RecConfig.regEnd[PAPER_REG_TOCO] = REC_REGION_TOCO0_112;
	}
}

INLINE STATIC VOID PrinterSetupDlgInit(HWND hWnd)
{
	HWND hCtrl;
	int i;
	for (i = IDC_PRINTER_SETUP_FHR60_L; i <= IDC_PRINTER_SETUP_CONTRAST_L; i++)
	{
		hCtrl = GetDlgItem(hWnd, i);
		if (hCtrl != 0)
		{
			SetWindowBkColor(hCtrl,((PCONTROL)hWnd)->iBkColor);
		}
	}
	hCtrl = GetDlgItem(hWnd, IDC_PRINTER_SETUP_DEFAULT_B);
	if (hCtrl != 0)
	{
		SetWindowBkColor(hCtrl,((PCONTROL)hWnd)->iBkColor);
	}
	hCtrl = GetDlgItem(hWnd, IDC_PRINTER_SETUP_SELFTEST_B);
	if (hCtrl != 0)
	{
		SetWindowBkColor(hCtrl,((PCONTROL)hWnd)->iBkColor);
	}
	InitRceRegion();
	SetSpinBoxIntValue(IDD_PRINTER_SETUP, IDC_PRINTER_SETUP_FHR60_SB,
		RecConfig.regEnd[PAPER_REG_FHR],
		REC_REGION_FHR60_MAX, REC_REGION_FHR60_MIN);
	SetSpinBoxIntValue(IDD_PRINTER_SETUP, IDC_PRINTER_SETUP_FHR210_SB,
		RecConfig.regStar[PAPER_REG_FHR],
		REC_REGION_FHR210_MAX,  REC_REGION_FHR210_MIN);
	SetSpinBoxIntValue(IDD_PRINTER_SETUP, IDC_PRINTER_SETUP_TOCO100_SB,
		RecConfig.regStar[PAPER_REG_TOCO],
		REC_REGION_TOCO100_MAX, REC_REGION_TOCO100_MIN);
	SetSpinBoxIntValue(IDD_PRINTER_SETUP, IDC_PRINTER_SETUP_TOCO0_SB,
		RecConfig.regEnd[PAPER_REG_TOCO],
		REC_REGION_TOCO0_MAX, REC_REGION_TOCO0_MIN);
	SetSpinBoxIntCurValue(IDD_PRINTER_SETUP, IDC_PRINTER_SETUP_CONTRAST_SB,
		RecConfig.chroma);
	hCtrl = GetDlgItem(hWnd, IDC_PRINTER_SETUP_CONTRAST_SB);
	if (hCtrl != 0)
	{
		EnableWindow(hCtrl, (PAPER_TYPE_112MM == MonitorConfig.RecorderType));
	}
	INT16 cur_choice = 0;
	SetListBoxString(IDD_PRINTER_SETUP, IDC_PRINTER_SETUP_FHRMIN_LB,
		StrID_FhrMin, TABLESIZE(StrID_FhrMin));
	SetListBoxString(IDD_PRINTER_SETUP, IDC_PRINTER_SETUP_FHRMAX_LB,
		StrID_FhrMax, TABLESIZE(StrID_FhrMax));
	SetListBoxString(IDD_PRINTER_SETUP, IDC_PRINTER_SETUP_SCALE_LB,
		gOnOff, 2);
	SetListBoxCurChoi(IDD_PRINTER_SETUP, IDC_PRINTER_SETUP_FHRMIN_LB,
		RecConfig.fhrMin);
	SetListBoxCurChoi(IDD_PRINTER_SETUP, IDC_PRINTER_SETUP_FHRMAX_LB,
		RecConfig.fhrMax);
	SetListBoxCurChoi(IDD_PRINTER_SETUP, IDC_PRINTER_SETUP_SCALE_LB,
		RecConfig.isScale);
}

static INT32
PrinterSetupDlgProc(HWND hWnd, INT32 message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case MSG_INITDIALOG:
			PrinterSetupDlgInit(hWnd);
			break;

		case MSG_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDC_PRINTER_SETUP_FHR60_SB:
					if (HIWORD(wParam) == SBN_CHANGED)
					{
						RecConfig.regEnd[PAPER_REG_FHR] =
							GetSpinBoxIntCurValue(IDD_PRINTER_SETUP,
													LOWORD(wParam));
						Save_Config(CFG_KEYID_PRINTREGIONEND);
					}
					break;
					
				case IDC_PRINTER_SETUP_FHR210_SB:
					if (HIWORD(wParam) == SBN_CHANGED)
					{
						RecConfig.regStar[PAPER_REG_FHR] =
							GetSpinBoxIntCurValue(IDD_PRINTER_SETUP,
													LOWORD(wParam));
						Save_Config(CFG_KEYID_PRINTREGIONSTART);
					}
					break;
					
				case IDC_PRINTER_SETUP_TOCO100_SB:
					if (HIWORD(wParam) == SBN_CHANGED)
					{
						RecConfig.regStar[PAPER_REG_TOCO] =
							GetSpinBoxIntCurValue(IDD_PRINTER_SETUP,
													LOWORD(wParam));
						SetSpinBoxIntMinValue(IDD_PRINTER_SETUP,
							IDC_PRINTER_SETUP_TOCO0_SB,
							RecConfig.regStar[PAPER_REG_TOCO] + 100);
						Save_Config(CFG_KEYID_PRINTREGIONSTART);
					}
					break;
					
				case IDC_PRINTER_SETUP_TOCO0_SB:
					if (HIWORD(wParam) == SBN_CHANGED)
					{
						RecConfig.regEnd[PAPER_REG_TOCO] =
							GetSpinBoxIntCurValue(IDD_PRINTER_SETUP,
													LOWORD(wParam));
						SetSpinBoxIntMaxValue(IDD_PRINTER_SETUP,
							IDC_PRINTER_SETUP_TOCO100_SB,
							RecConfig.regEnd[PAPER_REG_TOCO] - 100);

						Save_Config(CFG_KEYID_PRINTREGIONEND);
					}
					break;
					
				case IDC_PRINTER_SETUP_CONTRAST_SB:
					if (HIWORD(wParam) == SBN_CHANGED)
					{
						INT16 ret;
						ret = GetSpinBoxIntCurValue(IDD_PRINTER_SETUP,
												IDC_PRINTER_SETUP_CONTRAST_SB);
						if (ret != RecConfig.chroma)
						{
							RecConfig.chroma = ret;
							PrinterSetChroma(RecEventClass.pRecClass);
							Save_Config(CFG_KEYID_PRINTCHROMA);
						}
						
					}
					break;
					
				case IDC_PRINTER_SETUP_FHRMIN_LB:
					if (HIWORD(wParam) == LBN_CHANGED)
					{
						RecConfig.fhrMin =
							GetListBoxCurChoi(IDD_PRINTER_SETUP,
													LOWORD(wParam));
						Save_Config(CFG_KEYID_PRINTFHRMIN);
					}
					break;
					
				case IDC_PRINTER_SETUP_FHRMAX_LB:
					if (HIWORD(wParam) == LBN_CHANGED)
					{
						RecConfig.fhrMax=
							GetListBoxCurChoi(IDD_PRINTER_SETUP,
													LOWORD(wParam));
						Save_Config(CFG_KEYID_PRINTFHRMAX);
					}
					break;
					
				case IDC_PRINTER_SETUP_SCALE_LB:
					if (HIWORD(wParam) == LBN_CHANGED)
					{
						RecConfig.isScale=
							GetListBoxCurChoi(IDD_PRINTER_SETUP,
													LOWORD(wParam));
						Save_Config(CFG_KEYID_PRINTSCALE);
					}
					break;

				case IDC_PRINTER_SETUP_DEFAULT_B:
					if (IDYES == MessageBox(hWnd,
						STR_MSGBOX_PRO_DEFAULT_CONFIG, STR_NULL,
						STR_DLG_SETUP_DEFAULT,
						MB_ALIGNCENTER | MB_YESNO, SysGui_HTSK))
					{
						Load_DefCfg_Recorder();
						Save_Record_Config(0, 0);
						PrinterSetupDlgInit(hWnd);
					}
					break;
					
				case IDC_PRINTER_SETUP_SELFTEST_B:
					RecordService(REC_SELF_TEST);
					break;

				case IDC_PRINTER_SETUP_EXIT_B:
					EndDialog(hWnd, IDOK);
					return 0;
					
				default:
					break;
			}
			break;
	}
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}

VOID PrinterSetupDialog(HANDLE hOwner)
{
	enum __dialog_layout{
		CTRL1_W	 = 180,
		CTRL2_W	 = 180,
		CTRL3_W	 = CTRL1_W + CTRL2_W + DLG_OFFSET,
		CTRL_H	  = KEY_HEIGHT,
		LABEL_OFF   = (KEY_HEIGHT - STATIC_HEIGHT) / 2,
		COLUMN1X	= DLG_OFFSET,
		COLUMN2X	= DLG_OFFSET * 2 + CTRL1_W,
		ROW1_Y	  = DLG_OFFSET,
		ROW2_Y	  = DLG_OFFSET + ROW1_Y + CTRL_H,
		ROW3_Y	  = DLG_OFFSET + ROW2_Y + CTRL_H,
		ROW4_Y	  = DLG_OFFSET + ROW3_Y + CTRL_H,
		ROW5_Y	  = DLG_OFFSET + ROW4_Y + CTRL_H,
		ROW6_Y	  = DLG_OFFSET + ROW5_Y + CTRL_H,
		ROW7_Y	  = DLG_OFFSET + ROW6_Y + CTRL_H,
		ROW8_Y	  = DLG_OFFSET + ROW7_Y + CTRL_H,
		ROW9_Y	  = DLG_OFFSET + ROW8_Y + CTRL_H,
		DIALOG_W	= COLUMN2X + CTRL2_W + DLG_OFFSET,
		DIALOG_H	= ROW9_Y + KEY_HEIGHT + DLG_OFFSET + DLG_MENU_HIGHT,
			COLUMN3X	= DIALOG_W - CTRL1_W - DLG_OFFSET,
	};
	
	DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   0, 0, DIALOG_W, DIALOG_H,  STR_DLG_SETUP_PRINTER, 0, NULL, 0L,
	};
	
	CTRLDATA ctrl_data [] =
	{
		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE,
		   COLUMN1X, ROW1_Y + LABEL_OFF, CTRL1_W, CTRL_H,
			IDC_PRINTER_SETUP_FHR60_L,  STR_DLG_PRINTER_FHR60,	  0L, 0L}
	   ,{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE,
		   COLUMN1X, ROW2_Y + LABEL_OFF, CTRL1_W, CTRL_H,
			IDC_PRINTER_SETUP_FHR210_L, STR_DLG_PRINTER_FHR210,	 0L, 0L}
	   ,{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE,
		   COLUMN1X, ROW3_Y + LABEL_OFF, CTRL1_W, CTRL_H,
			IDC_PRINTER_SETUP_FHRMIN_L, STR_DLG_PRINTER_FHRMIN,	 0L, 0L}
	   ,{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE,
		   COLUMN1X, ROW4_Y + LABEL_OFF, CTRL1_W, CTRL_H,
			IDC_PRINTER_SETUP_FHRMAX_L, STR_DLG_PRINTER_FHRMAX,	 0L, 0L}
	   ,{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE,
		   COLUMN1X, ROW5_Y + LABEL_OFF, CTRL1_W, CTRL_H,
			IDC_PRINTER_SETUP_TOCO100_L,STR_DLG_PRINTER_TOCO100,	0L, 0L}
	   ,{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE,
		   COLUMN1X, ROW6_Y + LABEL_OFF, CTRL1_W, CTRL_H,
			IDC_PRINTER_SETUP_TOCO0_L,  STR_DLG_PRINTER_TOCO0,	  0L, 0L}
	   ,{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE,
		   COLUMN1X, ROW7_Y + LABEL_OFF, CTRL1_W, CTRL_H,
			IDC_PRINTER_SETUP_SCALE_L,  STR_DLG_PRINTER_SCALE,	  0L, 0L}
	   ,{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE,
		   COLUMN1X, ROW8_Y + LABEL_OFF, CTRL1_W, CTRL_H,
			IDC_PRINTER_SETUP_CONTRAST_L,STR_DLG_SETUP_PRINTCONTRAST,0L,0L}
	   ,{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
		   COLUMN2X, ROW1_Y, CTRL2_W, CTRL_H,
			IDC_PRINTER_SETUP_FHR60_SB,	 0,					  0L, 0L}
	   ,{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
		   COLUMN2X, ROW2_Y, CTRL2_W, CTRL_H,
			IDC_PRINTER_SETUP_FHR210_SB,	0,					  0L, 0L}
	   ,{ CTRL_LISTBOX,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
		   COLUMN2X, ROW3_Y, CTRL2_W, CTRL_H,
			IDC_PRINTER_SETUP_FHRMIN_LB,	0,					  0L, 0L}
	   ,{ CTRL_LISTBOX,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
		   COLUMN2X, ROW4_Y, CTRL2_W, CTRL_H,
			IDC_PRINTER_SETUP_FHRMAX_LB,	0,					  0L, 0L}
	   ,{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
		   COLUMN2X, ROW5_Y, CTRL2_W, CTRL_H,
			IDC_PRINTER_SETUP_TOCO100_SB,   0,					  0L, 0L}
	   ,{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
		   COLUMN2X, ROW6_Y, CTRL2_W, CTRL_H,
			IDC_PRINTER_SETUP_TOCO0_SB,	 0,					  0L, 0L}
	   ,{ CTRL_LISTBOX,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
		   COLUMN2X, ROW7_Y, CTRL2_W, CTRL_H,
			IDC_PRINTER_SETUP_SCALE_LB,	 0,					  0L, 0L}
	   ,{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
		   COLUMN2X, ROW8_Y, CTRL2_W, CTRL_H,
			IDC_PRINTER_SETUP_CONTRAST_SB,	 0,					  0L, 0L}
	   ,{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
		   COLUMN1X, ROW9_Y, CTRL1_W, CTRL_H,
			IDC_PRINTER_SETUP_DEFAULT_B,	STR_DLG_SETUP_DEFAULT, 0L, 0L}
	   ,{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
		   COLUMN3X, ROW9_Y, CTRL1_W, CTRL_H,
			IDC_PRINTER_SETUP_SELFTEST_B,   STR_DLG_PRINTER_SELFTEST, 0L, 0L}
	   ,{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE,
		   DIALOG_W - EXIT_ICON_WIDTH - DLG_OFFSET,
		   -(DLG_MENU_HIGHT + EXIT_ICON_HIGH) / 2,
		   EXIT_ICON_WIDTH,  EXIT_ICON_HIGH,
			IDC_PRINTER_SETUP_EXIT_B,   STR_DLG_EXIT,			   0L, 0L}
	};

	SPINBOXDATA sb_fhr210  =
		{ FORM_3D, SBTXT_NUM, 0, 0, 0, 0,  40,  240,  80, 1, 0, 0, 0 };
	SPINBOXDATA sb_fhr60  =
		{ FORM_3D, SBTXT_NUM, 0, 0, 0, 0, 300,  640, 528, 1, 0, 0, 0 };
	SPINBOXDATA sb_toco100 =
		{ FORM_3D, SBTXT_NUM, 0, 0, 0, 0, 480,  900, 528, 1, 0, 0, 0 };
	SPINBOXDATA sb_toco0 =
		{ FORM_3D, SBTXT_NUM, 0, 0, 0, 0, 700, 1200, 800, 1, 0, 0, 0 };
	SPINBOXDATA sb_cont =
		{ FORM_3D, SBTXT_NUM, 0, 0, 0, 0,  20,  100,  80, 1, 0, 0, 0 };
		
	LISTBOXDATA lb_fhrmax =
		{ TABLESIZE(StrID_FhrMin), 0, 5, 0, 0, StrID_FhrMin, 0, 0, 0, 0 };
	LISTBOXDATA lb_fhrmin =
		{ TABLESIZE(StrID_FhrMax), 0, 5, 0, 0, StrID_FhrMax, 0, 0, 0, 0 };
	LISTBOXDATA lb_scale  =
		{ TABLESIZE(gOnOff),	   0, 5, 0, 0, gOnOff,	   0, 0, 0, 0 };

	BUTTONDATA  btn_def  = {0};
	BUTTONDATA  btn_test = {0};
	BUTTONDATA  btn_exit = gBtn_Exit;

	INT16 ctrl_nr = TABLESIZE(ctrl_data);

	dlg_data.controlnr = TABLESIZE(ctrl_data);
	dlg_data.controls  = ctrl_data;

	WNDMEM wndMem;

	wndMem.pMainWin = GetMainWndMem(IDD_PRINTER_SETUP);
	wndMem.pControl = GetCtrlWndMem(IDC_PRINTER_SETUP_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;

	SetCtrlDataAddData2(ctrl_data, ctrl_nr,
		IDC_PRINTER_SETUP_FHR60_SB, (UINT32)&sb_fhr60);
	SetCtrlDataAddData2(ctrl_data, ctrl_nr,
		IDC_PRINTER_SETUP_FHR210_SB, (UINT32)&sb_fhr210);
	SetCtrlDataAddData2(ctrl_data, ctrl_nr,
		IDC_PRINTER_SETUP_TOCO100_SB, (UINT32)&sb_toco100);
	SetCtrlDataAddData2(ctrl_data, ctrl_nr,
		IDC_PRINTER_SETUP_TOCO0_SB, (UINT32)&sb_toco0);
	SetCtrlDataAddData2(ctrl_data, ctrl_nr,
		IDC_PRINTER_SETUP_CONTRAST_SB, (UINT32)&sb_cont);
	SetCtrlDataAddData2(ctrl_data, ctrl_nr,
		IDC_PRINTER_SETUP_FHRMIN_LB, (UINT32)&lb_fhrmin);
	SetCtrlDataAddData2(ctrl_data, ctrl_nr,
		IDC_PRINTER_SETUP_FHRMAX_LB, (UINT32)&lb_fhrmax);
	SetCtrlDataAddData2(ctrl_data, ctrl_nr,
		IDC_PRINTER_SETUP_SCALE_LB, (UINT32)&lb_scale);
	SetCtrlDataAddData2(ctrl_data, ctrl_nr,
		IDC_PRINTER_SETUP_DEFAULT_B, (UINT32)&btn_def);
	SetCtrlDataAddData2(ctrl_data, ctrl_nr,
		IDC_PRINTER_SETUP_SELFTEST_B, (UINT32)&btn_test);
	SetCtrlDataAddData2(ctrl_data, ctrl_nr,
		IDC_PRINTER_SETUP_EXIT_B, (UINT32)&btn_exit);
	
	DialogBoxIndirectParam(&dlg_data, hOwner, IDD_PRINTER_SETUP,
		PrinterSetupDlgProc, 0, &wndMem);
}



static INT32
PrintSetupDlgProc(HWND hWnd, INT32 message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case MSG_INITDIALOG:
			{
				HWND hCtrl;
				if (hCtrl = GetDlgItem(hWnd, IDC_PRINT_SETUP_LEN_L))
					SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
				if (hCtrl = GetDlgItem(hWnd, IDC_PRINT_SETUP_AUTO_L))
					SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
				if (hCtrl = GetDlgItem(hWnd, IDC_PRINT_SETUP_PRINTER_B))
					SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);

				SetListBoxCurChoi(IDD_PRINT_SETUP, 
					IDC_PRINT_SETUP_LEN_LB, FhrConfig.printLength);
				SetListBoxCurChoi(IDD_PRINT_SETUP, 
					IDC_PRINT_SETUP_AUTO_LB, FhrConfig.autoPrint);

				if (MonitorInfo.inDemo)
				{
					if (hCtrl = GetDlgItem(hWnd, IDC_PRINT_SETUP_LEN_LB))
						EnableWindow(hCtrl, FALSE);
					if (hCtrl = GetDlgItem(hWnd, IDC_PRINT_SETUP_AUTO_LB))
						EnableWindow(hCtrl, FALSE);
					if (hCtrl = GetDlgItem(hWnd, IDC_PRINT_SETUP_PRINTER_B))
						EnableWindow(hCtrl, FALSE);
				}
			}
			break;

		case MSG_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDC_PRINT_SETUP_LEN_LB:
					if (HIWORD(wParam) == LBN_CHANGED
						|| HIWORD(wParam) == LBN_ENTER)
					{
						INT16 ret = FhrConfig.printLength;
						if (HIWORD(wParam) == LBN_CHANGED)
						{
							ret = GetListBoxCurChoi(IDD_PRINT_SETUP,
													IDC_PRINT_SETUP_LEN_LB);
						}
						if (HIWORD(wParam) == LBN_ENTER)
						{
							ret = OnTouchListbox(hWnd, IDD_PRINT_SETUP,
							IDC_PRINT_SETUP_LEN_LB, STR_DLG_SETUP_TIMER);
						}
						if (ret != FhrConfig.printLength)
						{
							FhrConfig.printLength = ret;
							Save_Config(CFG_KEYID_PRINTLENGTH);
						}
					}
					return 0;

				case IDC_PRINT_SETUP_AUTO_LB:
					if (HIWORD(wParam) == LBN_CHANGED
						|| HIWORD(wParam) == LBN_ENTER)
					{
						INT16 ret = FhrConfig.autoPrint;
						if (HIWORD(wParam) == LBN_CHANGED)
						{
							ret = GetListBoxCurChoi(IDD_PRINT_SETUP,
													IDC_PRINT_SETUP_AUTO_LB);
						}
						if (HIWORD(wParam) == LBN_ENTER)
						{
							ret = OnTouchListbox(hWnd, IDD_PRINT_SETUP,
							IDC_PRINT_SETUP_AUTO_LB, STR_DLG_SETUP_AUTOPRINT);
						}
						if (ret != FhrConfig.autoPrint)
						{
							FhrConfig.autoPrint = ret;
							Save_Config(CFG_KEYID_PRINTAUTO);
						}
					}
					return 0;

				case IDC_PRINT_SETUP_PRINTER_B:
					//PrinterSetupDialog(hWnd);
					RecordService(REC_SELF_TEST);
					return 0;

				case IDC_PRINT_SETUP_EXIT_B:
					EndDialog(hWnd, IDOK);
					break;

				default:
					break;
			}
			break;
	}
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}



VOID PrintSetupDialog(HANDLE hOwner)
{
	enum __dialog_layout{
		CTRL_W	  = 120,
		CTRL_H	  = KEY_HEIGHT,
		LABEL_OFF   = (KEY_HEIGHT - STATIC_HEIGHT) / 2,
		COLUMN1X	= DLG_OFFSET,
		COLUMN2X	= DLG_OFFSET * 2 + CTRL_W,
		ROW1_Y	  = DLG_OFFSET,
		ROW2_Y	  = DLG_OFFSET + ROW1_Y + CTRL_H,
		ROW3_Y	  = DLG_OFFSET + ROW2_Y + CTRL_H,
		DIALOG_W	= COLUMN2X + CTRL_W + DLG_OFFSET,
		DIALOG_H	= ROW3_Y + KEY_HEIGHT + DLG_OFFSET + DLG_MENU_HIGHT,
	};
	
	DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   0, 0, DIALOG_W, DIALOG_H,  STR_DLG_SETUP_PRINT, 0, NULL, 0L,
	};
	
	CTRLDATA ctrl_data [] =
	{
		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE,
		   COLUMN1X, ROW1_Y + LABEL_OFF, CTRL_W, STATIC_HEIGHT,
			IDC_PRINT_SETUP_LEN_L,  STR_DLG_SETUP_TIMER,	  0L, 0L}
	   ,{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE, WS_EX_NONE,
		   COLUMN1X, ROW2_Y + LABEL_OFF, CTRL_W, STATIC_HEIGHT,
			IDC_PRINT_SETUP_AUTO_L, STR_DLG_SETUP_AUTOPRINT,	 0L, 0L}
	   ,{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
		   COLUMN2X, ROW1_Y, CTRL_W, CTRL_H,
			IDC_PRINT_SETUP_LEN_LB,	 0,					  0L, 0L}
	   ,{ CTRL_LISTBOX, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
		   COLUMN2X, ROW2_Y, CTRL_W, CTRL_H,
			IDC_PRINT_SETUP_AUTO_LB,	0,					  0L, 0L}
	   ,{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP, WS_EX_NONE,
		   COLUMN1X, ROW3_Y, CTRL_W * 2 + DLG_OFFSET, CTRL_H,
			IDC_PRINT_SETUP_PRINTER_B,   
			STR_DLG_PRINTER_SELFTEST/*STR_DLG_SETUP_PRINTER_B*/, 0L, 0L}
	   ,{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_ICON, WS_EX_NONE,
		   DIALOG_W - EXIT_ICON_WIDTH - DLG_OFFSET,
		   -(DLG_MENU_HIGHT + EXIT_ICON_HIGH) / 2,
		   EXIT_ICON_WIDTH,  EXIT_ICON_HIGH,
			IDC_PRINT_SETUP_EXIT_B,   STR_DLG_EXIT,			   0L, 0L}
	};
	STRINGID Timer[] = {
		STR_DLG_FM_MOVEMENTCAL_MANUAL,
		STR_DLG_10MIN,
		STR_DLG_15MIN,
		STR_DLG_20MIN,
		STR_DLG_30MIN,
		STR_DLG_40MIN,
		STR_DLG_50MIN,
		STR_DLG_60MIN,
	};
	LISTBOXDATA lb_len =
		{ 8, 0, 8, 0, 0, Timer,  0, 0, 0, 0 };
	LISTBOXDATA lb_auto =
		{ 2, 1, 2, 0, 0, gOnOff, 0, 0, 0, 0 };

	BUTTONDATA  btn_set  = {0};
	BUTTONDATA  btn_exit = gBtn_Exit;

	INT16 ctrl_nr = TABLESIZE(ctrl_data);

	dlg_data.controlnr = TABLESIZE(ctrl_data);
	dlg_data.controls  = ctrl_data;

	WNDMEM wndMem;

	wndMem.pMainWin = GetMainWndMem(IDD_PRINT_SETUP);
	wndMem.pControl = GetCtrlWndMem(IDC_PRINT_SETUP_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;

	SetCtrlDataAddData2(ctrl_data, ctrl_nr,
		IDC_PRINT_SETUP_LEN_LB, (UINT32)&lb_len);
	SetCtrlDataAddData2(ctrl_data, ctrl_nr,
		IDC_PRINT_SETUP_AUTO_LB, (UINT32)&lb_auto);

	SetCtrlDataAddData2(ctrl_data, ctrl_nr,
		IDC_PRINT_SETUP_PRINTER_B, (UINT32)&btn_set);
	SetCtrlDataAddData2(ctrl_data, ctrl_nr,
		IDC_PRINT_SETUP_EXIT_B, (UINT32)&btn_exit);
	
	DialogBoxIndirectParam(&dlg_data, hOwner, IDD_PRINT_SETUP,
		PrintSetupDlgProc, 0, &wndMem);
}


/*****************************************************************************************
函数名称:	BOOL RecInit (VOID)
版本号:		1.0.0
生成日期:	2011.11.07
作者:		zondan
功能说明:	初始化打印机的控制参数
输入参数:	
输出参数:	
其它说明:	
*****************************************************************************************/
BOOL RecInit(VOID)
{
	RecConfig.firstConnect	  = FALSE;
	InitRceRegion();
	RecEventClass.pRecClass->RecInit(RecEventClass.pRecClass);
}

#endif


