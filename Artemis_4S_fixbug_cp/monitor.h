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

#ifndef  _MONITOR_H
#define  _MONITOR_H

#define MAX_COMPANY_NAME_LEN   24
#define MAX_PASSWORD_LEN		8
#define DEMO_PASSWORD_LEN	   4


#define  NULL_STRING				   ""
#define  VERSION_START				 "Copyright(c) "
#define  VERSION_TM					"Copyright(c)  Ltd."
#define  COMPANY_TM					" "
#define  CAPTION_PIC_FILE_DEF		  "caption.bmp" //公司图标图片的默认文件名；
#define  LOGO_PIC_FILE_DEF			 "logo.pcx"	//开机画面图片的默认文件名；


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


/* SysPixelColor[]次序一致. */
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

// 参数的默认颜色.用户可以选择其它颜色.
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

#define PARAM_REGION_BKCOLOR   PIXEL_black  // 参数区背景色
#define WAVE_REGION_BKCOLOR	PIXEL_black  // 波形区背景色


/* 在前景和背景色中取不同的中间色.  fg, bg分别是前景和背景色, 32位数 */
#define  get_light_color(fg,bg)	(bg+(fg-bg)/4)
#define  get_medium_color(fg,bg)   (bg+(fg-bg)*2/4)
#define  get_dark_color(fg, bg)	(bg+(fg-bg)*3/4)


// 为系统中HOTKEY类型控件编的的id. 
typedef enum {
	HOT_CTRL_MAX
}HOTKEYID;

//hotkey控件的当前项转成ecg lead mode不是对应的.lead mode取值从1~7; hotkey的选项是0~6
#define   HOTKEY_2_LEADMODE(curr)		(curr + 1)	   // hotkey_item -> lead_mode
#define   LEADMODE_2_HOTKEY(lead_mode)   (lead_mode - 1)  // lead_mode -> hotkey_item;

/**
 ** 用于在APP任务中, 在消息传递过程中;指定调用对象ID号.(calling obj);
 ** 比如, 在gui任务中, post message to App 任务开始一次io操作, 在wParam参数中可以指定
 ** OBJID_GUI, 于是在 App任务中就知道是gui任务发出的请求.
 **/
typedef enum _obj_id {
  OBJID_SYS,
  OBJID_GUI,
  OBJID_DATA,
  OBJID_APP,

  OBJID_MAX
} TSKOBJ_ID;


/* 功能配置; 是由厂家决定的. */
typedef struct _monitor_function {
	INT8 dynamicTrendEnabled;		// 动态短趋势界面是否可用  1：是  0：否
	INT8 oxyCRGEnabled;				// oxyCRG界面是否可用  1：是  0：否
	INT8 viewBedEnabled;			// 它床观察界面是否可用  1：是  0：否
	INT8 waveScrollEnabled;		 // 波形滚动显示是否可用  1：是  0：否
	INT8 alarmLimitsEnabled;		// 报警限显示是否可用  1：是  0：否
	INT8 drugCalEnabled;			// 药物计算功能是否可用  1：是  0：否
	INT8 arrEnabled;				// 心律失常分析和ST段分析是否可用  1：是  0：否
	INT8 ecgLeadType;				// ECG导联类型选择  1：5导联  0：3导联
	INT8 ecgDisplayModeEnabled;		// ECG多导联显示是否可用  1：是  0：否
	INT8 nibpListEnabled;			// NIBP多组测量结果显示是否可用  1：是  0：否
	INT8 alarmVolumeOffEnabled;	 // 报警音量关闭是否可用  1：是  0：否
	//IN8 isOEM; Is OEM production.

	INT8 isPasswordEnabled;		 // Download password??
	INT8 isMultiLanguageEnabled;	// Download Multi language??
	INT8 isPaceSmoothEnabled;	   // choose pace smooth??
	INT8 isCompanyNameEnabled;	  // download company name??

	INT8 isNurseCallEnable;
	INT8 isBigFontEnable;
}  MONITOR_FUNC;

/* 模块的版本号 */
typedef struct _version_info {
   CHAR   ver[10];
} VERINFO;

typedef struct _module_info {
   INT8   Id;
   INT8   OnLine;  // Is this module in monitoring
   UINT8  OnLineFalag; //2011/03/15
} MODULE_INFO;

/* 监护仪配置;是由用户设置的. */
typedef struct _monitor_config {
	/* miscellaneous */
	INT8	kbVol;		   // Keyboard volume
	INT8	nightModeOn;	 // Night mode is On or not;影响了屏的亮度.
	INT8	showHelp;		// Want to show help information for menu system?
	INT8	showAlarmLimits; // Show alarm limits or not
	INT8	brightness;	  // 显示屏的亮度.

	/* patient's information */
	UINT8   bedNo;
	CHAR	patientName[32];
	CHAR	patientNum[32];
	char	patientAge;
	char	gestationalWeeks;   // 孕周
	char	gestationalDay;	 // 
	char	gestationalTimes;
	char	sex;				// 性别:0 females,1 males
	char	patientType;		// 病人类型:0 adult,1 kids,0 neo
	short   height;			 // 身高:cm
	short   weight;			 // 体重:kg
	INT8	heightUnit;   // Height Unit: 0/cm, 1/inch.
	INT8	weightUnit;   // Weight Unit: 0/kg, 1/lb
	char	bloodType;		  // 血型:0 O,1 A,2 B,3 AB

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
	INT8   drawWaveMode;	 // 画波形模式(1:色阶画法;0:单色阶梯画法).

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


/* 机器信息.这是在程序运行过程中反应了监护仪内部的运行状态.它对用户是不可见的. */
typedef struct _monitor_info {
	INT8		inDemo;			 // 是否在演示模式(TRUE: 是).
	INT8		inFrozen;		   // 屏幕是否被冻结(TRUE: 是).
	INT8		skipKeyMessage;	 // 是否忽略按键消息(TRUE: 是).
	INT8		blinkFlag;		  // 大字体界面下的软件闪烁标志(TRUE:闪灭,FALSE:闪亮)
	INT8		backToBigFontFace;  // 退出菜单后是否应该返回到大字体界面(TRUE:是)
	INT8		ecgGainAutoChanged; // ECG的增益是否被自动更改过
	INT8		nibpValTimeOut;	 // NIBP测量结果显示是否已经超时(FALSE:否)

	KEY_CODE	keyCode;			// 按键的消息
	INT8		menuLev;			// 菜单的级数
	INT16	   waveHeight;		   // 波形高度

	/* 参数模块的工作标志. */
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

	INT8		waveTypeNum;					 // 波形类型数
	INT8		waveTypeSeq[WAVE_TYPE_MAX];	  // 波形类型顺序
	INT8		moduleNum;					   // 在监护仪中当前正在工作的生理参数模块.按键板不算.
	DEVICEINFO  deviceInfo[DEV_MAX];

	INT8	faceChanged;	/* 界面是否改变; TRUE, 改变了; FALSE, 未变. */
	INT8	battVolume;		/* 电池电量,由按键板提供. 0~15, (-1)表示没有电池.*/
	UINT8	powerStatus;	/* 电源状态,由按键板提供. */
	INT8	standby;
#if _ENB_TOUCH > 0
	INT8	enableTouch;
	INT8	touchCal;
	UINT8	touchCalFlag;	//触摸屏是否已进行过校准
#endif
	UINT32	SystemRunTime;	// 系统运行时间
	UINT32	PatientTime;	// 监护时间
} MONITORINFO;


typedef struct _param_info {
   // 参数是否可用（TRUE：可用），参数是否可用受相关的导联连接状态影响，例如：
   // 如果SensorStatus[SENSOR_SPO2].isNormal == FALSE，那么，SPO2和PR就不
   // 可用
   INT8  canUsing;
}PARAM_INFO;


typedef struct _sensor_status {
   INT8  isNormal;	 // 传感器是否连接正常（即没有导联脱落）（TRUE：正常）
   INT8  alarmAllowed; // 是否允许传感器脱落报警（TRUE：是）
   
   /**
	  传感器恢复正常有多长时间了，每次传感器脱落清0此值，传感器正常时，
	  累加此值到一上限值; 单位, 秒
   **/
   INT8  recoveredSeconds;
}SENSOR_STATUS;


/**def{{{ 定义消息框控件的数据结构 **/

/** 
	消息条的最多条数
**/
#define MAX_MESSAGE_ITEM_NUM		20  

/*  注册消息时使用的信息  */
typedef struct _prompt_info {
	STRINGID	 prompt;				// 多语言消息
	GAL_PIXEL	color;				 // 显示颜色
	INT16		duration;			  // 持续时间(秒) (该时间指信息确实在显示的时间)
	INT8		 exclusiveShow;		 // 是否独占显示  TRUE：是
} PROMPT_INFO;

// 消息队列
typedef struct _prompt_item {
	INT8		 next;				  // 下一条消息
	INT8		 last;				  // 上一条消息

	STRINGID	 prompt;				// 多语言消息
	GAL_PIXEL	color;				 // 显示颜色
	INT16		duration;			  // 还需要持续的时间(秒)
	INT8		 exclusiveShow;		 // 是否独占显示  TRUE：是
} PROMPT_ITEM;

typedef struct  _prompt_box {
	INT16   total;				// 消息的总数
	INT16   current;			  // 当前一条消息
	INT16   last;				 // 最后一条消息
	INT16   free;				 // 未用的消息条链头

	INT8	inShowing;			// 是否有消息正在显示(TRUE: 是, FALSE: 否)
	INT8	isInProcess;		  // 是否正在进行处理, 利用该变量防止在不同的线程中向同一个消息框同时注册消息，

	PROMPT_ITEM  items[MAX_MESSAGE_ITEM_NUM];
} PROMPT_BOX;

/*  这里'消息条'和'提示条'可以理解为相同的意思.  */
#define   MAX_SYSINFO_ITEM_NUM		20  

/*  注册提示条时使用的结构  */
typedef struct _hint_info {
	STRINGID	 infoId;				// 多语言消息
	GAL_PIXEL	color;				 // 显示颜色
	INT16		duration;			  // 持续时间(秒) (该时间指信息确实在显示的时间)
	INT8		 exclusiveShow;		 // 是否独占显示  TRUE：是
} HINT_INFO, *PHINT_INFO;

// 系统消息条的结构
typedef struct _sys_item {
	PCHAIN_NODE  next;				  // 下一条消息
	PCHAIN_NODE  prev;				  // 上一条消息

	//下面和HINT_INFO结构是一样的.
	INT16		id;			  // 每个单元的id,它是唯一的编号;用于在remove info使用.
	STRINGID	 infoId;		  // 多语言消息
	GAL_PIXEL	color;		   // 显示颜色
	INT16		duration;		// 还需要持续的时间(秒)
	INT8		 exclusiveShow;   // 是否独占显示  TRUE：是
} SYSINFO_ITEM, *PSYSINFO_ITEM;

// 系统消息管理的数据结构. 用于控制bottom bar的消息栏显示. info bar.
typedef struct  _sysinfo_man {
	INT16		   total;   // 消息的总数
	PSYSINFO_ITEM   curr;	// 当前显示的信息条
	//INT16		   curr;	// 当前显示的信息条
	
	CHAIN_CONTROL   free;	// 空闲队列
	CHAIN_CONTROL   work;	// 工作队列

	INT8			inShow;  // 是否有消息正在显示(TRUE: 是, FALSE: 否)
	//INT8	isInProcess;	 // 是否正在进行处理, 利用该变量防止在不同的线程中向同一个消息框同时注册消息，

	HANDLE		   semaphore; // 信号量, 保护对item的存取.
	SYSINFO_ITEM	 items[MAX_MESSAGE_ITEM_NUM];
	//PSYSINFO_ITEM   items;
} SYSINFO_MAN;

/* def}}}定义消息框控件的数据结构 */

/*  报警参数ID  */
typedef enum _alm_para_type {
	ALM_PARA_FHR1,
	ALM_PARA_FHR2,
	ALM_PARA_TOCO,

	ALM_PARA_MAX
}ALM_PARAM_TYPE ;

/* def{{{ 参数报警和配置的默认值的管理 */

typedef struct _param_alm_info {
	UINT8	ModuleID;		  // 模块代码
	UINT8	ParaID;			// 参数代码
	INT8	 IsLoad;			// 是否被加载
	INT16	ParaType;		  // 参数类型，0整形，1浮点型.1， 2浮点型.2
	STRINGID LimitErrStr;	   // 报警限错误的字符串
	STRINGID HighStr;		   // 超高限的字符串
	STRINGID LowStr;			// 超低限的字符串
	INT8	 AlarmLimitIsChangingFlag;
}PARAM_ALM_INFO;

typedef struct _redundant_info{
	UINT8  type;  // 见enum  INT_TYPE;

	INT16  alm;
	INT16  high;
	INT16  low;
}REDUNDANT_INFO;

/* def}}} 参数报警和配置默认值的管理 */

typedef struct  {
   INT8   hasCommStpAlm;
   INT8   hasCommErrAlm;  // overrun, parity, frame error

   INT16  timeForCommStp; // in 5 millisecond
   INT16  commErrAllowed; // the number of communication error allowed
} COMMERRINFO;


/* def{{{ 用户配置调电保存管理 */
#define BLOOD_INVALID			(BLOOD_TYPE_NA + 1)
#define DATE_INVALID			 0
#define HEIGHT_INVALID		   0
#define WEIGHT_INVALID		   0
#define BEDNO_INVALID			0


#define SAVE_ALLINFO   (-1)

typedef struct
{
	INT8	alarm;		  // 报警开关
	INT8	alarmLevel;	 // 报警级别
	INT8	type;		   // 胎监模式 单/双
	INT8	volume;		 // 胎心音
	INT8	source;		 // 胎心音通道
	INT8	sweep;		  // 扫描速度
	INT8	zero;		   // 宫压归零值
	INT8	threshold;	  // 曲线分离值
	INT8	movement_calc;  // 自动胎动阀值
	INT8	recording;	  // 打印状态

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
	CFG_KEYID_DEFAULTANALYTYPE,//用户保存的评分设置默认值
	CFG_KEYID_MAX
}CFG_KEYID;


#define   ICS_P1861_E2P_SIZE   512  /*K1861板载e2prom的容量;单位, byte. */
#define	 USER_CFG_CACHE_SIZE	 (60 * 1024)//60K
#define	 USER_CFG_HEAD		   "Config"
#define	 MONITOR_TYPE_NAME	   "Artemis4S"

/* def}}} 用户配置调电保存管理 */

/* def{{{参数报警限的管理 */

typedef struct _param_litmits {
   UINT8  high;
   UINT8  low;

   UINT8  ripple;
   UINT8  hasRangeExceedAlarm;
}PARAM_LIMITS;


typedef struct _param_limit_info {
   INT8   isFloatType;		 // is this parameter float type?
   INT8   hasRangeExceedAlarm; // Should we check range exceeding for this parameter
   UINT8  type;				// 系统用整数代替浮点数，所以要知道数据放大了多少倍；
}PARAM_LMTINFO;

/* def}}} 参数报警限的管理 */

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


/* def{{{ 参数配置备份管理 */

/**
   在应用过程中,诸多配置值在用户设置过程中需要备份,以用户在某些情况下的恢复.
   比如, 用户首先设置报警音量为中级; 后来, 又关闭了报警音; 当再次打开时报警
   音时,应该恢复到最初的中级音量.
   同样的情况也适用于demo情况下, 进入demo时会采用一些规定的规则.当退出demo时,
   应该恢复以前的设置.
   这时,如果只有一个变量是不行的.monitorconfig, ecgconfig, etc.所以,要建立备份.
   注意, 变量类型要与monitorconfig, ecgconfig, 等一致.
**/
typedef struct _config_backup {
	INT8 alarmVolume;
	
	INT8 recWave1Name;
	INT8 recWave2Name;

	INT8 anaWaveName;
	
} CONFIG_BACKUP;

/* def}}} 参数配置备份管理 */

/* 参数显示 */

typedef struct {
	INT16	 x, y;		  // 输出参数名称的坐标
	STRINGID  strId;		 // 参数名称的字符串
} PARANAME;

// 定义显示参数值的数据结构
typedef struct {
	CHAR	no;			  // 参数值的名称
	CHAR	type;			// 参数值的类型
	INT16   x, y;			// 输出参数值的坐标
	CHAR	font;			// 输出参数值的字体
} PARAVALUE;

// 定义显示参数单位的数据结构
typedef struct {
	INT16	 x, y;		  // 输出单位的坐标
	INT16	 choiNum;	   // 单位的个数
	INT16	 curChoi;	   // 当前选择的单位
	STRINGID* str;		   // 单位的具体内容
} PARAUNIT;

// 定义显示参数块的数据结构
typedef struct
{
	CHAR		no;		  // 参数块的名称
	GAL_PIXEL   color;	   // 显示参数的颜色
	CHAR		numName;	 // 参数名称的个数
	CHAR		numVal;	  // 参数值的个数
	CHAR		numUnit;	 // 参数单位的个数
	PARANAME*   str;		 // 参数名称的具体内容
	PARAVALUE*  val;		 // 参数值的具体内容
	PARAUNIT*   unit;		// 参数单位的具体内容
} PARAREGION;

/* end of 参数显示*/


extern PARAM_LIMITS   *ParamLmtsOfPatients[];
extern PARAM_ALM_INFO  ParaAlarmInfo[];

extern  INT16	DemoPassWord;
extern  INT16	UserPassWord;
extern  INT16	FactoryPassWord;
extern  INT16	AnalysisPassWord;
extern  char	 CompanyName[];		//下载的公司名称
extern  char	 LogoPicFileName[];
extern  char	 CaptionPicFileName[];
extern  VOID	UpdateAlmVolIcon(VOID);
#endif
