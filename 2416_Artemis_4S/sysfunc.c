/*****************************************************************************************
��Ȩ����:			�����ص�
�汾��:				1.0.0
��������:			2011.04.15
�ļ���:				
����:				�����ص�
����˵��:			
����˵��:			��
�����ļ���ϵ:		���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
*****************************************************************************************/
#define   SYSFUNC_GLOBALS
#include  "includes.h"

#define  SYSFUNC_TEST 0

/*
 *   TRUE, ʹ���û�Ĭ������; FALSE,  ;
 *   ����ж��ڣ�Load_Sys_Config, Load_temp_Config, Load_Ibp_Config
 *
 */
BOOL	 gDefaultFlag = FALSE;

/* 
 * TRUE,  ��¼�Ĳ������Ʒ����˸ı䣬��Ҫ���³�ʼ����¼�����б�
 * FALSE, ����Ҫ���³�ʼ����
 * ֻ�� "���沼�ֵ���" �����лؼ���жϣ�
 */
BOOL	 gChangeRecWaveFlag = FALSE;

/*
 * TRUE, �����в�������; ���⣬�Ǵ����п��õ����ã������漰�����û������
 * FALSE,  ;
 *
 */
BOOL	 gOpenAllConfig = FALSE;

INT8	 gOldPatientType, gOldFace, gOldScanMode, gOldShowLimits;

static   char  Sys_VersionInfo[40];   //ϵͳ����汾

INT16	DemoPassWord	= 0;		//modified by empty 2011/03/23
INT16	UserPassWord	= 0;		//modified by empty 2011/03/23
INT16	FactoryPassWord = 0;		//modified by empty 2011/03/23
INT16	AnalysisPassWord = 0;
char	 CompanyName[26];			//���صĹ�˾����
char	 SysRight[40];			   //���صĹ�˾���ƺͰ�Ȩ��Ϣ
char	 LogoPicFileName[20];		//��������ͼƬ�ļ���·������
char	 CaptionPicFileName[20];	 //����ͼ���ļ���·������






/************************************************************************/
/*  ��������ShowDemoScale											   */
/*  ������  ����DEMOʱ�ȼ���ѡ����ʾIBP��ECG���α�ߵĺ���			  */
/*  ������  ��														  */
/*  ����ֵ����														  */
/************************************************************************/
VOID  ShowDemoScale (VOID)
{
	INT16 i;
	
	InitHotkeyChoice();				  // �õ��ȼ��ĵ�ǰֵ	
	return;
}


/************************************************************************/
/*  ��������ChangeSysSetup											  */
/*  ������  ����ȱʡ���ú�ı�ϵͳ�������õĺ���						*/
/*  ������  ��														  */
/*  ����ֵ����														  */
/************************************************************************/
VOID  ChangeSysSetup (VOID)
{
	// �ı䲨������
#if _ENB_WAVE_DRIVE > 0
	SetWaveDotStep(WAVE_TYPE_MAX, TRUE);
#endif
	// ��ʼ����������
	//KbSetKeyVolume(MonitorConfig.kbVol);
	// �����еĲ���
#if _ENB_WAVE_DRIVE > 0
	InitWaveTypeInfo();
	InitWaveColor(); // ������ʾ��ɫ
#endif
	StartLayoutSession();

	return;
}





//���㱾�µ�����������
//INT16 DaysInThisMonth( INT16 year, INT16 month )
//���������㱾�µ�������ָ�롣
//���룺
//  year:���
//  month:�·�
//�����
//  ��
//���ã�
//  ��
//�����ã�
//  IncreaseLongTrendPointers()
//����ֵ��
//��
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


//�жϱ�����Ƿ����꺯��
//BOOL  IsLeapYear( INT16 year )
//�������жϱ�����Ƿ����ꡣ
//���룺
//  year:���
//�����
//  ��
//���ã�
//  ��
//�����ã�
//  INT16 DaysInThisMonth( INT16 year, INT16 month )
//����ֵ��
//��
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
//  ��������DateToStr												   
//  ������  ������ת��Ϊ�ַ���
//		  (1) ���ݴ����ϵͳ����汾�ͻ������ͣ��ҵ���Ӧ���Ͷ�Ӧ�汾��GUI��Դ��Ȼ�����GUI�ؼ��Ķ�����м���
//			  ͬʱ��������GUI���Ʊ���GUI_HEADER��GUI_CTRL_HEADER_INFO���г�ʼ��
//		  (2) ��ʼ��GUIͨ����ɫ����Ļ����ɫ, �ַ���ɫ, �˵�����ɫ, �˵�������ɫ, �˵����ⱳ��ɫ, �ؼ���ѡ�еı߿���ɫ, ��ѡ�еĿؼ��ı���ɫ(�б��SPINBOX),��������ɫ ��
//  ������															  
//		  DATETIME - date
//	  string	- ���ص��ַ���
//	  style	 - 0��Ӣ�ĸ�ʽ07-31-2001, 1, ���ĸ�ʽ2001-07-31
//				  ȱʡΪ0(Ӣ�ĸ�ʽ)
//  ����ֵ��
//		  ��
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




/*	SVN �汾��Ϣ��ʾ		   */ 
VOID  InitVersionInfo (VOID)
{   
  CHAR *text;
  CHAR *pchar;
  
//  text = LoadString(STR_DLG_VERSION1);
  if( MonitorConfig.language == CHINESE )
	  pchar = strcpy(text, "�汾�� :DS120C_2410_SVN_3663");
  else
	pchar = strcpy(text, "VERSION :DS120C_2410_SVN_3663");

  return;
}

/**
 ** ��˾���ƿ�����monitor.ini�ļ�ָ����
 ** ���û��ָ�������ñ���˾���ƣ�
 **/
VOID  GetCompanyNameVersion (VOID)
{
  CHAR *pchar;
  
  if( MonitorConfig.language == CHINESE )
	  sprintf( SysRight,"%s","��˾��Ϣ:�����к����ص�ҽ���豸���޹�˾" );
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
	//�ر��ļ�����
	FmsPtr->ClosePtnFile(FmsPtr);
	sync();
	umask(0);	   //�����ļ�������ģ
	ms_sleep(100);  //��ʱ����ֹ������δд��ɹ��Ͷϵ�
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
	//�رս�����ʾ
	MonitorInfo.standby = 1;
	fb_fillrect_ex(0, 0, 0, SCREEN_WIDTH, SCREEN_HIGH, 0, 0, 0);

	//�رձ����������������ȵ���������
	AlmGlbCtlr.AlmSilent = TRUE;
	
	Red_led_gpio_value(OFF);
	Yellow_led_gpio_value(OFF);
	Blue_led_gpio_value(OFF);
	
	//��ʾ��Ϣ��ʾ	
	//ͼƬ������ʾ


	// ������Ļ����
	// ʹ�� ScrBrightnessDlg_OnCommand::IDC_SCREEN_BRIGHTNESS_LB:�Ĵ���ʽ�����Ƚ���
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

