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

#ifndef  _MONITOR_H
#define  _MONITOR_H

#define MAX_COMPANY_NAME_LEN   24
#define MAX_PASSWORD_LEN		8
#define DEMO_PASSWORD_LEN	   4


#define  NULL_STRING				   ""
#define  VERSION_START				 "Copyright(c) "
#define  VERSION_TM					"Copyright(c)  Ltd."
#define  COMPANY_TM					" "
#define  CAPTION_PIC_FILE_DEF		  "caption.bmp" //��˾ͼ��ͼƬ��Ĭ���ļ�����
#define  LOGO_PIC_FILE_DEF			 "logo.pcx"	//��������ͼƬ��Ĭ���ļ�����


#define  DEF_DEMO_PASSWORD		(5188)
#define  DEF_USER_PASSWORD		(2016)
#define  DEF_FACTORY_PASSWORD	(3021)
#define  DEF_ANALYSIS_PASSWORD	(225)

#define  DEMO_PASSWORD		DemoPassWord
#define  USER_PASSWORD		UserPassWord
#define  FACTORY_PASSWORD	FactoryPassWord
#define  ANALYSIS_PASSWORD	AnalysisPassWord
#define  CAPTION_PIC_FILE	CaptionPicFileName
#define  LOGO_PIC_FILE		LogoPicFileName


#define  SECTION_FUNCTION			  "function"
#define  SECTION_COMPANY			   "companyinfo"
#define  SECTION_PASSWORD			  "passwordinfo"
#define  SECTION_LOGO				  "logoinfo"
#define  SECTION_ICON				  "iconinfo"

#define  KEY_DYNAMIC_TREND			 "dynamicTrend"
#define  KEY_OXYCRG					"oxyCRG"
#define  KEY_WAVE_SCROLL			   "waveScroll"
#define  KEY_ALARM_LIMITS			  "alarmLimits"
#define  KEY_DRUGCAL				   "drugCal"
#define  KEY_ARR					   "arr"
#define  KEY_ECG_LEADTYPE			  "ecgLeadType"
#define  KEY_ECG_DISPMODE			  "ecgDisplayMode"
#define  KEY_NIBPLIST				  "nibpList"
#define  KEY_ALARM_VOLUME			  "alarmVolumeOff"
#define  KEY_OEM					   "oem"
#define  KEY_PACE_SMOOTH			   "paceSmooth"
#define  KEY_NURSE_CALL				"NurseCall"
#define  KEY_VIEW_BED				  "viewBed"
#define  KEY_BIGFONT				   "bigFont"

#define  KEY_NAME					  "name"
#define  KEY_VERSION				   "version"

#define  KEY_USER					  "user"
#define  KEY_FACTORY				   "factory"
#define  KEY_DEMO					  "demo"

#define  KEY_LOGO					  "logo"
#define  KEY_FILE					  "file"
#define  KEY_CAPTION				   "caption"


/* SysPixelColor[]����һ��. */
typedef enum _color_index
{
	COLOR_BLACK,		// black		 --0
	COLOR_DARKBLUE,	 // dark blue	 --1
	COLOR_DARKGREEN,	// dark green	--2
	COLOR_DARKCYAN,	 // dark cyan	 --3
	COLOR_DARKRED,	  // dark red	  --4
	COLOR_DARKMAGENTA,  // dark magenta  --5
	COLOR_DARKYELLOW,   // dark yellow   --6
	COLOR_DARKGRAY,	 // dark gray	 --7
	COLOR_LIGHTGRAY,	// light gray	--8
	COLOR_BLUE,		 // blue		  --9
	COLOR_GREEN,		// green		 --10
	COLOR_CYAN,		 // cyan		  --11
	COLOR_RED,		  // red		   --12
	COLOR_MAGENTA,	  // magenta	   --13
	COLOR_YELLOW,	   // yellow		--14
	COLOR_WHITE,		// light white   --15
	COLOR_MAX
}COLOR_INDEX;

// ������Ĭ����ɫ.�û�����ѡ��������ɫ.
#define BLOCK_ECG_COLOR	COLOR_GREEN   //PIXEL_green
#define BLOCK_SPO2_COLOR   COLOR_CYAN	//PIXEL_cyan
#define BLOCK_NIBP_COLOR   COLOR_WHITE   //PIXEL_white
#define BLOCK_IBP_COLOR	COLOR_RED	 //PIXEL_red
#define BLOCK_RESP_COLOR   COLOR_YELLOW  //PIXEL_yellow
#define BLOCK_TEMP_COLOR   COLOR_WHITE   //PIXEL_white


#if _ENB_FHR_FUNC// lookingout
#define BLOCK_FHR1_COLOR   WEC_EXCOLOR_MAGENTA
#define BLOCK_FHR2_COLOR   WEC_EXCOLOR_YELLOW
#define BLOCK_TOCO_COLOR   WEC_EXCOLOR_LIME
#define BLOCK_AFM_COLOR	WEC_EXCOLOR_MAGENTA
#endif

#define BLOCK_OTHER_COLOR  COLOR_WHITE   //PIXEL_white

#define PARAM_REGION_BKCOLOR   PIXEL_black  // ����������ɫ
#define WAVE_REGION_BKCOLOR	PIXEL_black  // ����������ɫ


/* ��ǰ���ͱ���ɫ��ȡ��ͬ���м�ɫ.  fg, bg�ֱ���ǰ���ͱ���ɫ, 32λ�� */
#define  get_light_color(fg,bg)	(bg+(fg-bg)/4)
#define  get_medium_color(fg,bg)   (bg+(fg-bg)*2/4)
#define  get_dark_color(fg, bg)	(bg+(fg-bg)*3/4)


// Ϊϵͳ��HOTKEY���Ϳؼ���ĵ�id. 
typedef enum {
	HOT_CTRL_MAX
}HOTKEYID;

//hotkey�ؼ��ĵ�ǰ��ת��ecg lead mode���Ƕ�Ӧ��.lead modeȡֵ��1~7; hotkey��ѡ����0~6
#define   HOTKEY_2_LEADMODE(curr)		(curr + 1)	   // hotkey_item -> lead_mode
#define   LEADMODE_2_HOTKEY(lead_mode)   (lead_mode - 1)  // lead_mode -> hotkey_item;

/**
 ** ������APP������, ����Ϣ���ݹ�����;ָ�����ö���ID��.(calling obj);
 ** ����, ��gui������, post message to App ����ʼһ��io����, ��wParam�����п���ָ��
 ** OBJID_GUI, ������ App�����о�֪����gui���񷢳�������.
 **/
typedef enum _obj_id {
  OBJID_SYS,
  OBJID_GUI,
  OBJID_DATA,
  OBJID_APP,

  OBJID_MAX
} TSKOBJ_ID;


/* ��������; ���ɳ��Ҿ�����. */
typedef struct _monitor_function {
	INT8 dynamicTrendEnabled;		// ��̬�����ƽ����Ƿ����  1����  0����
	INT8 oxyCRGEnabled;				// oxyCRG�����Ƿ����  1����  0����
	INT8 viewBedEnabled;			// �����۲�����Ƿ����  1����  0����
	INT8 waveScrollEnabled;		 // ���ι�����ʾ�Ƿ����  1����  0����
	INT8 alarmLimitsEnabled;		// ��������ʾ�Ƿ����  1����  0����
	INT8 drugCalEnabled;			// ҩ����㹦���Ƿ����  1����  0����
	INT8 arrEnabled;				// ����ʧ��������ST�η����Ƿ����  1����  0����
	INT8 ecgLeadType;				// ECG��������ѡ��  1��5����  0��3����
	INT8 ecgDisplayModeEnabled;		// ECG�ർ����ʾ�Ƿ����  1����  0����
	INT8 nibpListEnabled;			// NIBP������������ʾ�Ƿ����  1����  0����
	INT8 alarmVolumeOffEnabled;	 // ���������ر��Ƿ����  1����  0����
	//IN8 isOEM; Is OEM production.

	INT8 isPasswordEnabled;		 // Download password??
	INT8 isMultiLanguageEnabled;	// Download Multi language??
	INT8 isPaceSmoothEnabled;	   // choose pace smooth??
	INT8 isCompanyNameEnabled;	  // download company name??

	INT8 isNurseCallEnable;
	INT8 isBigFontEnable;
}  MONITOR_FUNC;

/* ģ��İ汾�� */
typedef struct _version_info {
   CHAR   ver[10];
} VERINFO;

typedef struct _module_info {
   INT8   Id;
   INT8   OnLine;  // Is this module in monitoring
   UINT8  OnLineFalag; //2011/03/15
} MODULE_INFO;

/* �໤������;�����û����õ�. */
typedef struct _monitor_config {
	/* miscellaneous */
	INT8	kbVol;		   // Keyboard volume
	INT8	nightModeOn;	 // Night mode is On or not;Ӱ������������.
	INT8	showHelp;		// Want to show help information for menu system?
	INT8	showAlarmLimits; // Show alarm limits or not
	INT8	brightness;	  // ��ʾ��������.

	/* patient's information */
	UINT8   bedNo;
	CHAR	patientName[32];
	CHAR	patientNum[32];
	char	patientAge;
	char	gestationalWeeks;   // ����
	char	gestationalDay;	 // 
	char	gestationalTimes;
	char	sex;				// �Ա�:0 females,1 males
	char	patientType;		// ��������:0 adult,1 kids,0 neo
	short   height;			 // ���:cm
	short   weight;			 // ����:kg
	INT8	heightUnit;   // Height Unit: 0/cm, 1/inch.
	INT8	weightUnit;   // Weight Unit: 0/kg, 1/lb
	char	bloodType;		  // Ѫ��:0 O,1 A,2 B,3 AB

	INT8	patientIsPace;

	DATETIME birthday;
	DATETIME admitDate;

	CHAR	department[13];
	CHAR	doctorName[13];

	/* Screen interface type: standard, oxyCRG, dynamic trends, */
	INT8	faceType;

	/* Alarm system settings  */
	INT8	alarmVolume;
	INT8	alarmWaveRecordLength;
	INT8	alarmSuspendTime;
	INT8	alarmLatched;
	INT8	alarmSoundOn;

	DATETIME	dateTime;
	MODULE_INFO moduleInfo[MID_MAX];

	/* Recorder settings */
	INT8	 recWave1Name;
	INT8	 recWave2Name;
	INT8	 recRTMode;			 // Wave length for real-time recording
	INT8	 recPeriod;			 // interval of periodical recording
	INT8	 recSweepSpeed;
	INT8	 recDrawGrid;

	/* analog output  */
	INT8	analogOutputEnabled;
	INT8	analogOutputWaveName;

	/* Color defined for parameters or/and waves  */
	UINT8   colorParam[PARA_BLOCK_MAX];

	/* Factory settings  */
	INT8   arrhythmiaInstalled;
	INT8   leadSystem;		// ECG lead system(0:5-lead system, 1: 3-lead system)
	INT8   leadStyle;		// ECG lead naming style(0: AHA, 1: EURO)
	INT8   language;			// current language
	INT8   vgasize;			// TFT/CRT monitor size(0:8.4' TFT; 1: 12' TFT; 2: 15' CRT  
	INT8   drawWaveMode;	 // ������ģʽ(1:ɫ�׻���;0:��ɫ���ݻ���).

	char	date_delimiter;
	char	time_delimiter;
	char	date_format_type;
	char	time_format_type;
	
	INT8	MonitorName;
	INT8	RecorderType;
#if _ENB_TOUCH > 0
	INT8	UseTouch;
	INT16 	offsetX;
	INT16 	offsetY;
	FLOAT 	scaleX;
	FLOAT 	scaleY;
#endif
} MONITORCONFIG;


/* ������Ϣ.�����ڳ������й����з�Ӧ�˼໤���ڲ�������״̬.�����û��ǲ��ɼ���. */
typedef struct _monitor_info {
	INT8		inDemo;			 // �Ƿ�����ʾģʽ(TRUE: ��).
	INT8		inFrozen;		   // ��Ļ�Ƿ񱻶���(TRUE: ��).
	INT8		skipKeyMessage;	 // �Ƿ���԰�����Ϣ(TRUE: ��).
	INT8		blinkFlag;		  // ����������µ������˸��־(TRUE:����,FALSE:����)
	INT8		backToBigFontFace;  // �˳��˵����Ƿ�Ӧ�÷��ص����������(TRUE:��)
	INT8		ecgGainAutoChanged; // ECG�������Ƿ��Զ����Ĺ�
	INT8		nibpValTimeOut;	 // NIBP���������ʾ�Ƿ��Ѿ���ʱ(FALSE:��)

	KEY_CODE	keyCode;			// ��������Ϣ
	INT8		menuLev;			// �˵��ļ���
	INT16	   waveHeight;		   // ���θ߶�

	/* ����ģ��Ĺ�����־. */
	INT8		ecgWorkFlag;
	INT8		respWorkFlag;
	INT8		tempWorkFlag;
	INT8		spo2WorkFlag;
	INT8		nibpWorkFlag;
	INT8		ibpWorkFlag;
	INT8		co2WorkFlag;

#if _ENB_FHR_FUNC
	INT8		fhrWorkFlag;
#endif

	INT8		waveTypeNum;					 // ����������
	INT8		waveTypeSeq[WAVE_TYPE_MAX];	  // ��������˳��
	INT8		moduleNum;					   // �ڼ໤���е�ǰ���ڹ������������ģ��.�����岻��.
	DEVICEINFO  deviceInfo[DEV_MAX];

	INT8	faceChanged;	/* �����Ƿ�ı�; TRUE, �ı���; FALSE, δ��. */
	INT8	battVolume;		/* ��ص���,�ɰ������ṩ. 0~15, (-1)��ʾû�е��.*/
	UINT8	powerStatus;	/* ��Դ״̬,�ɰ������ṩ. */
	INT8	standby;
#if _ENB_TOUCH > 0
	INT8	enableTouch;
	INT8	touchCal;
	UINT8	touchCalFlag;	//�������Ƿ��ѽ��й�У׼
#endif
	UINT32	SystemRunTime;	// ϵͳ����ʱ��
	UINT32	PatientTime;	// �໤ʱ��
} MONITORINFO;


typedef struct _param_info {
   // �����Ƿ���ã�TRUE�����ã��������Ƿ��������صĵ�������״̬Ӱ�죬���磺
   // ���SensorStatus[SENSOR_SPO2].isNormal == FALSE����ô��SPO2��PR�Ͳ�
   // ����
   INT8  canUsing;
}PARAM_INFO;


typedef struct _sensor_status {
   INT8  isNormal;	 // �������Ƿ�������������û�е������䣩��TRUE��������
   INT8  alarmAllowed; // �Ƿ������������䱨����TRUE���ǣ�
   
   /**
	  �������ָ������ж೤ʱ���ˣ�ÿ�δ�����������0��ֵ������������ʱ��
	  �ۼӴ�ֵ��һ����ֵ; ��λ, ��
   **/
   INT8  recoveredSeconds;
}SENSOR_STATUS;


/**def{{{ ������Ϣ��ؼ������ݽṹ **/

/** 
	��Ϣ�����������
**/
#define MAX_MESSAGE_ITEM_NUM		20  

/*  ע����Ϣʱʹ�õ���Ϣ  */
typedef struct _prompt_info {
	STRINGID	 prompt;				// ��������Ϣ
	GAL_PIXEL	color;				 // ��ʾ��ɫ
	INT16		duration;			  // ����ʱ��(��) (��ʱ��ָ��Ϣȷʵ����ʾ��ʱ��)
	INT8		 exclusiveShow;		 // �Ƿ��ռ��ʾ  TRUE����
} PROMPT_INFO;

// ��Ϣ����
typedef struct _prompt_item {
	INT8		 next;				  // ��һ����Ϣ
	INT8		 last;				  // ��һ����Ϣ

	STRINGID	 prompt;				// ��������Ϣ
	GAL_PIXEL	color;				 // ��ʾ��ɫ
	INT16		duration;			  // ����Ҫ������ʱ��(��)
	INT8		 exclusiveShow;		 // �Ƿ��ռ��ʾ  TRUE����
} PROMPT_ITEM;

typedef struct  _prompt_box {
	INT16   total;				// ��Ϣ������
	INT16   current;			  // ��ǰһ����Ϣ
	INT16   last;				 // ���һ����Ϣ
	INT16   free;				 // δ�õ���Ϣ����ͷ

	INT8	inShowing;			// �Ƿ�����Ϣ������ʾ(TRUE: ��, FALSE: ��)
	INT8	isInProcess;		  // �Ƿ����ڽ��д���, ���øñ�����ֹ�ڲ�ͬ���߳�����ͬһ����Ϣ��ͬʱע����Ϣ��

	PROMPT_ITEM  items[MAX_MESSAGE_ITEM_NUM];
} PROMPT_BOX;

/*  ����'��Ϣ��'��'��ʾ��'�������Ϊ��ͬ����˼.  */
#define   MAX_SYSINFO_ITEM_NUM		20  

/*  ע����ʾ��ʱʹ�õĽṹ  */
typedef struct _hint_info {
	STRINGID	 infoId;				// ��������Ϣ
	GAL_PIXEL	color;				 // ��ʾ��ɫ
	INT16		duration;			  // ����ʱ��(��) (��ʱ��ָ��Ϣȷʵ����ʾ��ʱ��)
	INT8		 exclusiveShow;		 // �Ƿ��ռ��ʾ  TRUE����
} HINT_INFO, *PHINT_INFO;

// ϵͳ��Ϣ���Ľṹ
typedef struct _sys_item {
	PCHAIN_NODE  next;				  // ��һ����Ϣ
	PCHAIN_NODE  prev;				  // ��һ����Ϣ

	//�����HINT_INFO�ṹ��һ����.
	INT16		id;			  // ÿ����Ԫ��id,����Ψһ�ı��;������remove infoʹ��.
	STRINGID	 infoId;		  // ��������Ϣ
	GAL_PIXEL	color;		   // ��ʾ��ɫ
	INT16		duration;		// ����Ҫ������ʱ��(��)
	INT8		 exclusiveShow;   // �Ƿ��ռ��ʾ  TRUE����
} SYSINFO_ITEM, *PSYSINFO_ITEM;

// ϵͳ��Ϣ��������ݽṹ. ���ڿ���bottom bar����Ϣ����ʾ. info bar.
typedef struct  _sysinfo_man {
	INT16		   total;   // ��Ϣ������
	PSYSINFO_ITEM   curr;	// ��ǰ��ʾ����Ϣ��
	//INT16		   curr;	// ��ǰ��ʾ����Ϣ��
	
	CHAIN_CONTROL   free;	// ���ж���
	CHAIN_CONTROL   work;	// ��������

	INT8			inShow;  // �Ƿ�����Ϣ������ʾ(TRUE: ��, FALSE: ��)
	//INT8	isInProcess;	 // �Ƿ����ڽ��д���, ���øñ�����ֹ�ڲ�ͬ���߳�����ͬһ����Ϣ��ͬʱע����Ϣ��

	HANDLE		   semaphore; // �ź���, ������item�Ĵ�ȡ.
	SYSINFO_ITEM	 items[MAX_MESSAGE_ITEM_NUM];
	//PSYSINFO_ITEM   items;
} SYSINFO_MAN;

/* def}}}������Ϣ��ؼ������ݽṹ */

/*  ��������ID  */
typedef enum _alm_para_type {
	ALM_PARA_FHR1,
	ALM_PARA_FHR2,
	ALM_PARA_TOCO,

	ALM_PARA_MAX
}ALM_PARAM_TYPE ;

/* def{{{ �������������õ�Ĭ��ֵ�Ĺ��� */

typedef struct _param_alm_info {
	UINT8	ModuleID;		  // ģ�����
	UINT8	ParaID;			// ��������
	INT8	 IsLoad;			// �Ƿ񱻼���
	INT16	ParaType;		  // �������ͣ�0���Σ�1������.1�� 2������.2
	STRINGID LimitErrStr;	   // �����޴�����ַ���
	STRINGID HighStr;		   // �����޵��ַ���
	STRINGID LowStr;			// �����޵��ַ���
	INT8	 AlarmLimitIsChangingFlag;
}PARAM_ALM_INFO;

typedef struct _redundant_info{
	UINT8  type;  // ��enum  INT_TYPE;

	INT16  alm;
	INT16  high;
	INT16  low;
}REDUNDANT_INFO;

/* def}}} ��������������Ĭ��ֵ�Ĺ��� */

typedef struct  {
   INT8   hasCommStpAlm;
   INT8   hasCommErrAlm;  // overrun, parity, frame error

   INT16  timeForCommStp; // in 5 millisecond
   INT16  commErrAllowed; // the number of communication error allowed
} COMMERRINFO;


/* def{{{ �û����õ��籣����� */
#define BLOOD_INVALID			(BLOOD_TYPE_NA + 1)
#define DATE_INVALID			 0
#define HEIGHT_INVALID		   0
#define WEIGHT_INVALID		   0
#define BEDNO_INVALID			0


#define SAVE_ALLINFO   (-1)

typedef struct
{
	INT8	alarm;		  // ��������
	INT8	alarmLevel;	 // ��������
	INT8	type;		   // ̥��ģʽ ��/˫
	INT8	volume;		 // ̥����
	INT8	source;		 // ̥����ͨ��
	INT8	sweep;		  // ɨ���ٶ�
	INT8	zero;		   // ��ѹ����ֵ
	INT8	threshold;	  // ���߷���ֵ
	INT8	movement_calc;  // �Զ�̥����ֵ
	INT8	recording;	  // ��ӡ״̬

	INT16	FhrAlarmLimitHi;
	INT16	FhrAlarmLimitLo;
} DEMO_SAVING;


VOID  EnterDemoMode(VOID);
VOID  LeaveDemoMode(VOID);
VOID  NewPatient(VOID);
VOID  InitParaForNewPatient(VOID);
VOID  ClearAllAlmForNewPatient(VOID);


typedef enum config_key_id{
	CFG_KEYID_MONITORTYPE,
	CFG_KEYID_DATETIME_FORMAT,
	CFG_KEYID_MODULEKEYBOARDONLINE,
	CFG_KEYID_MODULEFETALONLINE,
	CFG_KEYID_MODULEPRINTERONLINE,
	CFG_KEYID_KEYBOARDCOM,
	CFG_KEYID_FETALCOM,
	CFG_KEYID_PRINTERCOM,
	CFG_KEYID_KEYVOLUME,
	CFG_KEYID_LANGUAGE,
	CFG_KEYID_NIGHTMODE,
	CFG_KEYID_HELPINFO,
	CFG_KEYID_FACETYPE,
	CFG_KEYID_BEDNUMBER,
	CFG_KEYID_FHR1COLOR,
	CFG_KEYID_FHR2COLOR,
	CFG_KEYID_TOCOCOLOR,
	CFG_KEYID_FMCOLOR,
	CFG_KEYID_ALARMFHRHI,
	CFG_KEYID_ALARMFHRLO,
	CFG_KEYID_ALARMSWITCH,
	CFG_KEYID_ALARMVOLUME,
	CFG_KEYID_ALARMSILENCE,
	CFG_KEYID_FETALMODE,
	CFG_KEYID_FHRVOICECHANNEL,
	CFG_KEYID_FHRVOLUME,
	CFG_KEYID_TOCOZEROVALUE,
	CFG_KEYID_FETALMOVECALC,
	CFG_KEYID_PRINTFAST,
	CFG_KEYID_PRINTTYPE,
	CFG_KEYID_PRINTSPEED,
	CFG_KEYID_PRINTDETACH,
	CFG_KEYID_PRINTLENGTH,
	CFG_KEYID_PRINTAUTO,
	CFG_KEYID_PRINTMODE,
	CFG_KEYID_PRINTCHROMA,
	CFG_KEYID_PRINTREGIONSTART,
	CFG_KEYID_PRINTREGIONEND,
	CFG_KEYID_PRINTSCALE,
	CFG_KEYID_PRINTFHRMAX,
	CFG_KEYID_PRINTFHRMIN,
	CFG_KEYID_ANALYTYPE,
	CFG_KEYID_ANALYAUTO,
	CFG_KEYID_NETWORKCFGFILE,
	CFG_KEYID_NETWORKAUTO,
	CFG_KEYID_NETWORKNAME,
	CFG_KEYID_NETWORKIP,
	CFG_KEYID_NETWORKMAC,
	CFG_KEYID_NETWORKSERVER,
	CFG_KEYID_NETWORKGATEWAY,
	CFG_KEYID_NETWORKMASK,
	CFG_KEYID_TOUCHCOM,
	CFG_KEYID_TOUCHENABLE,
	CFG_KEYID_TOUCHCALFLAG,
	CFG_KEYID_TOUCHOFFSETX,
	CFG_KEYID_TOUCHOFFSETY,
	CFG_KEYID_TOUCHSCALEX,
	CFG_KEYID_TOUCHSCALEY,
	CFG_KEYID_SYS_LCBOARD,
	CFG_KEYID_DEFAULTANALYTYPE,//�û��������������Ĭ��ֵ
	CFG_KEYID_MAX
}CFG_KEYID;


#define   ICS_P1861_E2P_SIZE   512  /*K1861����e2prom������;��λ, byte. */
#define	 USER_CFG_CACHE_SIZE	 (60 * 1024)//60K
#define	 USER_CFG_HEAD		   "Config"
#define	 MONITOR_TYPE_NAME	   "Artemis4S"

/* def}}} �û����õ��籣����� */

/* def{{{���������޵Ĺ��� */

typedef struct _param_litmits {
   UINT8  high;
   UINT8  low;

   UINT8  ripple;
   UINT8  hasRangeExceedAlarm;
}PARAM_LIMITS;


typedef struct _param_limit_info {
   INT8   isFloatType;		 // is this parameter float type?
   INT8   hasRangeExceedAlarm; // Should we check range exceeding for this parameter
   UINT8  type;				// ϵͳ���������渡����������Ҫ֪�����ݷŴ��˶��ٱ���
}PARAM_LMTINFO;

/* def}}} ���������޵Ĺ��� */

typedef enum  _param_lmts_id {
	PARAM_LMTS_MIN,
	PARAM_LMTS_FHR = PARAM_LMTS_MIN,  // FHR
	PARAM_LMTS_TOCO,					// TOCO
	PARAM_LMTS_AFM,
	PARAM_LMTS_FM,
	PARAM_LMTS_MAX
}PARAM_LMTS_ID;

typedef enum monitor_struct_id{
	MONITOR_STATUS_AC,
	MONITOR_STATUS_BATT,
	MONITOR_STATUS_NETWORK,
	MONITOR_STATUS_REC,
	MONITOR_STATUS_FHRVOL,
	MONITOR_STATUS_ALMVOL,
	
	MONITOR_STATUS_MAX
}MONITOR_STATUS;

typedef enum monitor_type
{
	MONITOR_TYPE_AR4S,
	MONITOR_TYPE_AR2,
	
	MONITOR_TYPE_MAX
}MONITOR_TYPE;


/* def{{{ �������ñ��ݹ��� */

/**
   ��Ӧ�ù�����,�������ֵ���û����ù�������Ҫ����,���û���ĳЩ����µĻָ�.
   ����, �û��������ñ�������Ϊ�м�; ����, �ֹر��˱�����; ���ٴδ�ʱ����
   ��ʱ,Ӧ�ûָ���������м�����.
   ͬ�������Ҳ������demo�����, ����demoʱ�����һЩ�涨�Ĺ���.���˳�demoʱ,
   Ӧ�ûָ���ǰ������.
   ��ʱ,���ֻ��һ�������ǲ��е�.monitorconfig, ecgconfig, etc.����,Ҫ��������.
   ע��, ��������Ҫ��monitorconfig, ecgconfig, ��һ��.
**/
typedef struct _config_backup {
	INT8 alarmVolume;
	
	INT8 recWave1Name;
	INT8 recWave2Name;

	INT8 anaWaveName;
	
} CONFIG_BACKUP;

/* def}}} �������ñ��ݹ��� */

/* ������ʾ */

typedef struct {
	INT16	 x, y;		  // ����������Ƶ�����
	STRINGID  strId;		 // �������Ƶ��ַ���
} PARANAME;

// ������ʾ����ֵ�����ݽṹ
typedef struct {
	CHAR	no;			  // ����ֵ������
	CHAR	type;			// ����ֵ������
	INT16   x, y;			// �������ֵ������
	CHAR	font;			// �������ֵ������
} PARAVALUE;

// ������ʾ������λ�����ݽṹ
typedef struct {
	INT16	 x, y;		  // �����λ������
	INT16	 choiNum;	   // ��λ�ĸ���
	INT16	 curChoi;	   // ��ǰѡ��ĵ�λ
	STRINGID* str;		   // ��λ�ľ�������
} PARAUNIT;

// ������ʾ����������ݽṹ
typedef struct
{
	CHAR		no;		  // �����������
	GAL_PIXEL   color;	   // ��ʾ��������ɫ
	CHAR		numName;	 // �������Ƶĸ���
	CHAR		numVal;	  // ����ֵ�ĸ���
	CHAR		numUnit;	 // ������λ�ĸ���
	PARANAME*   str;		 // �������Ƶľ�������
	PARAVALUE*  val;		 // ����ֵ�ľ�������
	PARAUNIT*   unit;		// ������λ�ľ�������
} PARAREGION;

/* end of ������ʾ*/


extern PARAM_LIMITS   *ParamLmtsOfPatients[];
extern PARAM_ALM_INFO  ParaAlarmInfo[];

extern  INT16	DemoPassWord;
extern  INT16	UserPassWord;
extern  INT16	FactoryPassWord;
extern  INT16	AnalysisPassWord;
extern  char	 CompanyName[];		//���صĹ�˾����
extern  char	 LogoPicFileName[];
extern  char	 CaptionPicFileName[];
extern  VOID	UpdateAlmVolIcon(VOID);
#endif
