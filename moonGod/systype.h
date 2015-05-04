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

#ifndef  _MYSYS_TYPES_H
#define  _MYSYS_TYPES_H

// the maximal number of waves one single parameter of a module can have
#define MAX_WAVE_NUM_OF_MODULE	  4

// The channel number of fetal module
#define FETAL_CHANNEL_NUM	  2

// The maximal number of pace pulse in one second
#define MAX_PACE_NUM	  15

// if pace pulse in one second greater than this number, signal of this
// second will be treated as noise.
#define  PACE_NUM_ALLOWED  10

// A value indicate that pace pulse position is invalid
#define INVALID_PACE_POS   300

/* Alarm controlling: a trigger with 0x4000 will cause the alarm a
   prompt only */
#define  PROMPT_ONLY	 (0x4000)

// for MULTI-LANGUAGE & ECG MULTI-LEADS DISPLAY
#define MAX_LANGUAGE_NUM_PERMITTED  27

#define ECG_WAVE_NUM		6	   // ECG wave num in MULTI-LEADS display mode.

#define TECH_PROMPT_WIDTH	 320
#define FREEZE_INFO_WIDTH	 84
#define DEMO_INFO_WIDTH	   84
#define BATTERY_INFO_WIDTH	155
#define DLG_BUTTON_WIDTH	  152

//#pragma enum(1)

/* 默认配置类型 */
typedef enum {
	DEFAULT_FACTORY,
	DEFAULT_USER
} DEFAULT_TYPE;

/* 病人类型 */
typedef enum {
   PATIENT_ADULT,
   PATIENT_PEDIATRIC,
   PATIENT_MAX
}PATIENT_TYPE;

/* 血型 */
typedef enum {
	BLOOD_TYPE_A,
	BLOOD_TYPE_B,
	BLOOD_TYPE_O,
	BLOOD_TYPE_AB,
	BLOOD_TYPE_NA
}BLOOD_TYPE ;

/* 报警记录的波形长度,单位,分钟. */
typedef enum {
	ALM_REC_LEN_1min,
	ALM_REC_LEN_2min,
	ALM_REC_LEN_3min
}ALM_REC_LEN;

/* 报警挂起的时间 */
typedef enum {
	ALM_SUSPEND_1min,
	ALM_SUSPEND_2min,
	ALM_SUSPEND_3min
}ALM_SUSPEND_DURATION;

/* 在读写配置时的出错代码, (access eeprom)  */
typedef enum {
   ERROR_NO_ERROR,
   ERROR_IN_COMPARE_STORAGE
}ERROR_CODE;

/* 监护仪的语言 */
typedef enum {
  ENGLISH,
  CHINESE,
  RUSSIAN,
  SPANISH,
  TURKISH,
  MAX_LANGUAGE  
}LANGUAGE;

#define  FIRST_LANGUAGE	  ENGLISH
#define  DEFAULT_LANGUAGE	CHINESE
// 波形显示方式
typedef enum {
   SWEEP, //刷新
   SCROLL //滚动
}WAVESWEEPMODE;

// 显示设备类型
typedef enum {
   TFT,
   CRT
}DEVICETYPE;


/* 屏的大小尺寸 */
typedef enum {
	VGA_TFT_7INCH,
	VGA_TFT_8INCH,
	VGA_TFT_10INCH,  
	VGA_TFT_12INCH,
	VGA_SIZE_MAX
}VGA_SIZE;

/* 屏的分辨率screen resolution */
typedef enum {
	RSLT_800X480,
	RSLT_1280X800,
	RSLT_800X600,
	RSLT_1024X768,
	
	RSLT_MAX,
}RESOLUTION;


/* 报警级别 */
typedef enum {
   ALM_LEV_HIGH,
   ALM_LEV_MED,
   ALM_LEV_LOW
}ALM_LEVEL;

/* 按键板按键音量 */
typedef enum {
   KB_SILENCE,
   KB_VOL_LOW,
   KB_VOL_MED,
   KB_VOL_HIGH,
   KB_VOL_MAX = 4
}KBVOLUME;

/* 按键板报警音量 */
typedef enum {
   ALM_SILENCE,
   ALM_VOL_LOW,
   ALM_VOL_MED,
   ALM_VOL_HIGH,
   ALM_VOL_MAX = 4
}ALARM_VOLUME;

/* 初始化状态 */
typedef enum {
   INIT_NOT_DONE,
   INIT_SUCCESS,
   INIT_FAILED
}INIT_STATUS;

/* 按键事件代码code */
typedef enum {
	KEY_UNDEFINED,

	KEY_MENU,
	KEY_SILENCE,
	KEY_MAIN,
	KEY_FREEZE,
	KEY_PAUSE,
	KEY_ALARM_SETUP,
	KEY_KNOB_PRESSED,
	KEY_KNOB_ROTATE_RIGHT,
	KEY_KNOB_ROTATE_LEFT,
	KEY_NIBP_START_STOP,
	KEY_REC_START_STOP,
	KEY_SOS_PATIENT,
	KEY_SOS_POWER,
	KEY_VOL_PLUS,
	KEY_VOL_MINUS,
	KEY_NEW_PATIENT,
	KEY_TOCO,
	KEY_EVENT,
	KEY_EXIT,
	#if _ENB_TOUCH
	KEY_TOUCH,
	#endif

	KEY_MSG_ALL,
	KEY_PRESSD = 0x7F
}KEY_CODE;

#if _ENB_TOUCH
/* 按键事件代码code */
typedef enum
{
	TOUCH_UNDEFINED,

	TOUCH_PRESSED,
	TOUCH_RELEASE,

	TOUCH_MSG_ALL,
}TOUCH_CODE;
#endif

/* 模块类型 */
#define  MID_NULL   (-1)
#define  MID_REC	(100)
typedef enum {
	MID_KB,
	MID_FHR,
	MID_RECODER,
	MID_MAX
} MODULE_ID;

/* 时间类型 */
typedef struct _tag_datetime {

   INT16  second;
   INT16  minute;
   INT16  hour;
   INT16  day;
   INT16  month;
   INT16  year;
} __attribute__ ((packed, aligned(2))) DATETIME;

#ifndef _TIME_H
struct tm {
	int tm_sec;		 /* seconds */
	int tm_min;		 /* minutes */
	int tm_hour;		/* hours */
	int tm_mday;		/* day of the month */
	int tm_mon;		 /* month */
	int tm_year;		/* year */
	int tm_wday;		/* day of the week */
	int tm_yday;		/* day in the year */
	int tm_isdst;	   /* daylight saving time */
}DATETIMEEX;
#endif

/* 系统界面类型 */
typedef enum _enum_face_type {
	FACE_STD,
	FACE_BIGFONT,

	FACE_STD_SINGLE,
	FACE_BIGFONT_SINGLE,

	FACE_MAX
}FACE_TYPE;

#define  CONFIGID_ALL   (100)
typedef enum {
  CONFIGID_SYS,
  CONFIGID_FHR,
  CONFIGID_MAX  
} CONFIG_ID;

/* 配置类型 */
typedef enum {
	CONFIG_TYPE_CURRENT,
	CONFIG_TYPE_USER,
	CONFIG_TYPE_DEFAULT
}CONFIG_TYPE;

/* 波形类型名称  */
typedef enum {
	WAVE_TYPE_FHR,
	WAVE_TYPE_TOCO,
	WAVE_TYPE_MAX
} WAVE_TYPE;

/* 波形名称 */
typedef enum { 
	WAVE_FHR_CH1,
	WAVE_FHR_CH2,
	WAVE_TOCO,
	WAVE_AFM,
	WAVE_MAX
} WAVE_NAME;

typedef enum { 
	MARK_ANALY = 0x10,
	MARK_EVENT,
	MARK_FM,
	MARK_AFM,
	MARK_ZERO
} MARK_NAME;

#define	WAVE_OFF	(WAVE_MAX)

/* 参数块名称 */
typedef enum {
	PARA_BLOCK_FHR1,
	PARA_BLOCK_FHR2,
	PARA_BLOCK_TOCO,
	PARA_BLOCK_FM,
	PARA_BLOCK_MAX,
	
	// 以下两个常数只于读取缺省配置时使用，
	PARA_BLOCK_SYS, // 读取系统缺省配置
	PARA_BLOCK_ALL  // 读取所有缺省配置

} PARABLOCKNAME;

/* 传感器ID */
typedef enum {
	SENSOR_FIRST,
	SENSOR_FHR_CH1 = SENSOR_FIRST,
	SENSOR_FHR_CH2,
	SENSOR_TOCO,
	SENSOR_FM,
	SENSOR_MAX
}SENSORINDEX;

/* 参数类型 */
typedef enum {
   PARAM_MAX
}PARAM_INDEX;

/* 报警类型 */
typedef enum {
   ALM_PARAM_MAX
}PARAM_ALARM_CODE_INDEX;


/* 实时记录的波形长度,单位,秒. */
typedef enum {
	RT_REC_LEN_CONTINUE,   /* 连续 */
	RT_REC_LEN_8s,		 /*  */
	RT_REC_LEN_16s,		/*  */
	RT_REC_LEN_32s		 /*  */
}RT_REC_LEN;

/* 实时记录模式. */
typedef enum {
	RT_REC_MANUAL ,		/* 手动方式 */
	RT_REC_AUTO			/* 自动方式 */
}RT_MODE;

/* 记录波形速度. mm/s */
typedef enum {
  REC_SPEED_25,
  REC_SPEED_50
} REC_SWEEPSPEED;

/* 自动记录的时间间隔 */
typedef enum {
  REC_PERIOD_OFF,	/* 关闭自动记录功能 */
  REC_PERIOD_10MIN,
  REC_PERIOD_20MIN,
  REC_PERIOD_30MIN,
  REC_PERIOD_40MIN,
  REC_PERIOD_50MIN,
  REC_PERIOD_1HOUR,
  REC_PERIOD_2HOUR,
  REC_PERIOD_3HOUR,
  REC_PERIOD_4HOUR
} REC_AUTOPERIOD;

//整数类型
typedef enum  {
   INT_RAW,	 //整数用原始
   INT_X10,	 //整数放大了10倍；
   INT_X100,	//整数放大了100倍；
   INT_X1000	//整数放大了1000倍；
}  INT_TYPE;

typedef enum {
	FORMAT_YYYY_MM_DD,
	FORMAT_MM_DD_YYYY,
	FORMAT_DD_MM_YYYY,
	FORMAT_HH_MM_SS,
	FORMAT_HH_MM,
	FORMAT_TT_HH_MM_SS,
	FORMAT_TT_HH_MM,
	FORMAT_DATETIME_MAX
}DATETIME_FORMAT_TYPE;

typedef enum __tag_ascii_code
{
	ASCII_NUT = 0X00,
	ASCII_SOH,
	ASCII_STX,
	ASCII_ETX,
	ASCII_EOT,
	ASCII_ENQ,
	ASCII_ACK,
	ASCII_BEL,
	ASCII_BS,
	ASCII_HT,
	ASCII_LF,
	ASCII_VT,
	ASCII_FF,
	ASCII_CR,
	ASCII_SO,
	ASCII_SI,
	ASCII_DLE,
	ASCII_DC1,
	ASCII_DC2,
	ASCII_DC3,
	ASCII_DC4,
	ASCII_NAK,
	ASCII_SYN,
	ASCII_TB,
	ASCII_CAN,
	ASCII_EM,
	ASCII_SUB,
	ASCII_ESC,
	ASCII_FS,
	ASCII_GS,
	ASCII_RS,
	ASCII_US,
	ASCII_SPACE = ' ',
}ASCII_CODE;

//#pragma enum(pop)

#endif
