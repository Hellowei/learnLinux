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
#define   SYSFUNC_GLOBALS
#include  "includes.h"

#define  SYSFUNC_TEST 0

/*
 *   TRUE, 使用用户默认配置; FALSE,  ;
 *   检查判断在，Load_Sys_Config, Load_temp_Config, Load_Ibp_Config
 *
 */
BOOL	 gDefaultFlag = FALSE;

/* 
 * TRUE,  记录的波形名称发生了改变，需要重新初始化记录波形列表；
 * FALSE, 不需要重新初始化；
 * 只在 "界面布局调整" 函数中回检查判断；
 */
BOOL	 gChangeRecWaveFlag = FALSE;

/*
 * TRUE, 打开所有波形配置; 本意，是打开所有可用的配置，而不涉及其它用户配置项。
 * FALSE,  ;
 *
 */
BOOL	 gOpenAllConfig = FALSE;

INT8	 gOldPatientType, gOldFace, gOldScanMode, gOldShowLimits;

static   char  Sys_VersionInfo[40];   //系统软件版本

INT16	DemoPassWord	= 0;		//modified by empty 2011/03/23
INT16	UserPassWord	= 0;		//modified by empty 2011/03/23
INT16	FactoryPassWord = 0;		//modified by empty 2011/03/23
INT16	AnalysisPassWord = 0;
char	 CompanyName[26];			//下载的公司名称
char	 SysRight[40];			   //下载的公司名称和版权信息
char	 LogoPicFileName[20];		//开机画面图片文件的路径名称
char	 CaptionPicFileName[20];	 //标题图标文件的路径名称






/************************************************************************/
/*  函数名：ShowDemoScale											   */
/*  描述：  根据DEMO时热键的选择显示IBP和ECG波形标尺的函数			  */
/*  参数：  无														  */
/*  返回值：无														  */
/************************************************************************/
VOID  ShowDemoScale (VOID)
{
	INT16 i;
	
	InitHotkeyChoice();				  // 得到热键的当前值	
	return;
}


/************************************************************************/
/*  函数名：ChangeSysSetup											  */
/*  描述：  采用缺省配置后改变系统所有设置的函数						*/
/*  参数：  无														  */
/*  返回值：无														  */
/************************************************************************/
VOID  ChangeSysSetup (VOID)
{
	// 改变波形走速
#if _ENB_WAVE_DRIVE > 0
	SetWaveDotStep(WAVE_TYPE_MAX, TRUE);
#endif
	// 初始化键盘音量
	//KbSetKeyVolume(MonitorConfig.kbVol);
	// 打开所有的波形
#if _ENB_WAVE_DRIVE > 0
	InitWaveTypeInfo();
	InitWaveColor(); // 设置显示颜色
#endif
	StartLayoutSession();

	return;
}





//计算本月的日期数函数
//INT16 DaysInThisMonth( INT16 year, INT16 month )
//描述：计算本月的日期数指针。
//输入：
//  year:年份
//  month:月份
//输出：
//  无
//调用：
//  无
//被调用：
//  IncreaseLongTrendPointers()
//返回值：
//无
INT16  DaysInThisMonth (INT16 year, INT16 month)
{
	switch (month) {
		case 0:  //Dec
			return 31;
			
		case 1 : //Jan
			return 31;
			
		case 2 :
			if( IsLeapYear( year ) )
				return 29;
			else
				return 28;
				
		case 3 :
			return 31;
			
		case 4 :
			return 30;
			
		case 5 :
			return 31;
			
		case 6 :
			return 30;
			
		case 7 :
			return 31;
			
		case 8 :
			return 31;
			
		case 9 :
			return 30;
			
		case 10:
			return 31;
			
		case 11:
			return 30;
			
		case 12 :
			return 31;
			
		default:
			return FALSE;
	}
}


//判断本年度是否闰年函数
//BOOL  IsLeapYear( INT16 year )
//描述：判断本年度是否闰年。
//输入：
//  year:年份
//输出：
//  无
//调用：
//  无
//被调用：
//  INT16 DaysInThisMonth( INT16 year, INT16 month )
//返回值：
//无
BOOL  IsLeapYear (INT16 year)
{
	if ((year % 4) == 0) 
	{
		if ((year % 100) == 0) 
		{
			if ((year % 400) == 0) 
			{
				return TRUE;
			} 
			else 
			{
				return FALSE;
			}
		} 
		else 
		{
			return TRUE;
		}
	} 
	else 
	{
			return FALSE;
	}
}


// ----------------------------------------------------------------------
//  函数名：DateToStr												   
//  描述：  将日期转换为字符串
//		  (1) 根据传入的系统软件版本和机器类型，找到对应机型对应版本的GUI资源，然后根据GUI控件的定义进行加载
//			  同时，给两个GUI控制变量GUI_HEADER、GUI_CTRL_HEADER_INFO进行初始化
//		  (2) 初始化GUI通用颜色：屏幕背景色, 字符颜色, 菜单背景色, 菜单标题颜色, 菜单标题背景色, 控件被选中的边框颜色, 被选中的控件的背景色(列表框、SPINBOX),下拉框颜色 ，
//  参数：															  
//		  DATETIME - date
//	  string	- 返回的字符串
//	  style	 - 0，英文格式07-31-2001, 1, 中文格式2001-07-31
//				  缺省为0(英文格式)
//  返回值：
//		  无
// ----------------------------------------------------------------------
VOID  DateToStr (char *string, DATETIME *date, INT style)
{
	char day[3];
	char month[3];
	char year[5];
	
	if (date->day > 9) 
	{
		sprintf(day, "%d", date->day);
	} 
	else 
	{
		sprintf(day, "0%d", date->day);  
	}

	if (date->month > 9) 
	{
		sprintf(month, "%d", date->month);
	} 
	else 
	{
		sprintf(month, "0%d", date->month);  
	}
	sprintf(year, "%d", date->year); 
	
	if (style == 0) 
	{
		sprintf(string, "%s-%s-%s", month, day, year);
	} 
	else 
	{
		sprintf(string, "%s-%s-%s", year, month, day);
	}

	return;
}




/*	SVN 版本信息显示		   */ 
VOID  InitVersionInfo (VOID)
{   
  CHAR *text;
  CHAR *pchar;
  
//  text = LoadString(STR_DLG_VERSION1);
  if( MonitorConfig.language == CHINESE )
	  pchar = strcpy(text, "版本号 :DS120C_2410_SVN_3663");
  else
	pchar = strcpy(text, "VERSION :DS120C_2410_SVN_3663");

  return;
}

/**
 ** 公司名称可以由monitor.ini文件指定；
 ** 如果没有指定，则用本公司名称；
 **/
VOID  GetCompanyNameVersion (VOID)
{
  CHAR *pchar;
  
  if( MonitorConfig.language == CHINESE )
	  sprintf( SysRight,"%s","公司信息:深圳市和心重典医疗设备有限公司" );
  else
	  sprintf( SysRight,"%s","COMPANY:ZONDAN Medical Equipment Co.,Ltd." );

  pchar = strcpy( CompanyName,SysRight );
  
//  GlobalStr[STR_DLG_VERSION2] = CompanyName;

  return;
}

VOID EnterStandby(VOID);
VOID SysPowerOff(VOID)
{
	EnterStandby();
	KillSignal = TRUE;
	//关闭文件管理
	FmsPtr->ClosePtnFile(FmsPtr);
	sync();
	umask(0);	   //重设文件创建掩模
	ms_sleep(100);  //延时，防止缓冲区未写入成功就断电
}

VOID  EnterFrozen (VOID)
{
	MonitorInfo.inFrozen = TRUE;
	FetalWavePrint->drawFlag = FALSE;
	FetalWavePrint->redrawFlag = FALSE;
}

VOID  ExitFrozen (VOID)
{
	MonitorInfo.inFrozen = FALSE;
	FetalWavePrint->drawFlag = TRUE;
	FetalWavePrint->redrawFlag = TRUE;
}

VOID EnterStandby(VOID)
{
	INT32	bmpWidth, bmpHeight;
	INT32	x0, y0;
	PLOGFONT pOldFont;
	SIZE	 size;
	bmpWidth  = 0;
	bmpHeight = 0;
	//关闭界面显示
	MonitorInfo.standby = 1;
	fb_fillrect_ex(0, 0, 0, SCREEN_WIDTH, SCREEN_HIGH, 0, 0, 0);

	//关闭报警、脉搏、心跳等的声音处理
	AlmGlbCtlr.AlmSilent = TRUE;
	
	Red_led_gpio_value(OFF);
	Yellow_led_gpio_value(OFF);
	Blue_led_gpio_value(OFF);
	
	//提示信息显示	
	//图片居中显示


	// 降低屏幕亮度
	// 使用 ScrBrightnessDlg_OnCommand::IDC_SCREEN_BRIGHTNESS_LB:的处理方式将亮度降低
}


VOID ExitStandby(VOID)
{
	MonitorInfo.standby = 0;
	AlmGlbCtlr.AlmSilent = FALSE;
	//SoundSetBeatVolume(EcgConfig.beatVolume);
	//SoundSetPulseVolume(Spo2Config.pulseVol);
	//SendMessage(SysGui_HTSK, MSG_SCRMAN, SM_START_LAYOUT, 0);
	StartLayoutSession();
}

