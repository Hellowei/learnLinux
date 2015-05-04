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

/* Ĭ���������� */
typedef enum {
	DEFAULT_FACTORY,
	DEFAULT_USER
} DEFAULT_TYPE;

/* �������� */
typedef enum {
   PATIENT_ADULT,
   PATIENT_PEDIATRIC,
   PATIENT_MAX
}PATIENT_TYPE;

/* Ѫ�� */
typedef enum {
	BLOOD_TYPE_A,
	BLOOD_TYPE_B,
	BLOOD_TYPE_O,
	BLOOD_TYPE_AB,
	BLOOD_TYPE_NA
}BLOOD_TYPE ;

/* ������¼�Ĳ��γ���,��λ,����. */
typedef enum {
	ALM_REC_LEN_1min,
	ALM_REC_LEN_2min,
	ALM_REC_LEN_3min
}ALM_REC_LEN;

/* ���������ʱ�� */
typedef enum {
	ALM_SUSPEND_1min,
	ALM_SUSPEND_2min,
	ALM_SUSPEND_3min
}ALM_SUSPEND_DURATION;

/* �ڶ�д����ʱ�ĳ������, (access eeprom)  */
typedef enum {
   ERROR_NO_ERROR,
   ERROR_IN_COMPARE_STORAGE
}ERROR_CODE;

/* �໤�ǵ����� */
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
// ������ʾ��ʽ
typedef enum {
   SWEEP, //ˢ��
   SCROLL //����
}WAVESWEEPMODE;

// ��ʾ�豸����
typedef enum {
   TFT,
   CRT
}DEVICETYPE;


/* ���Ĵ�С�ߴ� */
typedef enum {
	VGA_TFT_7INCH,
	VGA_TFT_8INCH,
	VGA_TFT_10INCH,  
	VGA_TFT_12INCH,
	VGA_SIZE_MAX
}VGA_SIZE;

/* ���ķֱ���screen resolution */
typedef enum {
	RSLT_800X480,
	RSLT_1280X800,
	RSLT_800X600,
	RSLT_1024X768,
	
	RSLT_MAX,
}RESOLUTION;


/* �������� */
typedef enum {
   ALM_LEV_HIGH,
   ALM_LEV_MED,
   ALM_LEV_LOW
}ALM_LEVEL;

/* �����尴������ */
typedef enum {
   KB_SILENCE,
   KB_VOL_LOW,
   KB_VOL_MED,
   KB_VOL_HIGH,
   KB_VOL_MAX = 4
}KBVOLUME;

/* �����屨������ */
typedef enum {
   ALM_SILENCE,
   ALM_VOL_LOW,
   ALM_VOL_MED,
   ALM_VOL_HIGH,
   ALM_VOL_MAX = 4
}ALARM_VOLUME;

/* ��ʼ��״̬ */
typedef enum {
   INIT_NOT_DONE,
   INIT_SUCCESS,
   INIT_FAILED
}INIT_STATUS;

/* �����¼�����code */
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
/* �����¼�����code */
typedef enum
{
	TOUCH_UNDEFINED,

	TOUCH_PRESSED,
	TOUCH_RELEASE,

	TOUCH_MSG_ALL,
}TOUCH_CODE;
#endif

/* ģ������ */
#define  MID_NULL   (-1)
#define  MID_REC	(100)
typedef enum {
	MID_KB,
	MID_FHR,
	MID_RECODER,
	MID_MAX
} MODULE_ID;

/* ʱ������ */
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

/* ϵͳ�������� */
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

/* �������� */
typedef enum {
	CONFIG_TYPE_CURRENT,
	CONFIG_TYPE_USER,
	CONFIG_TYPE_DEFAULT
}CONFIG_TYPE;

/* ������������  */
typedef enum {
	WAVE_TYPE_FHR,
	WAVE_TYPE_TOCO,
	WAVE_TYPE_MAX
} WAVE_TYPE;

/* �������� */
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

/* ���������� */
typedef enum {
	PARA_BLOCK_FHR1,
	PARA_BLOCK_FHR2,
	PARA_BLOCK_TOCO,
	PARA_BLOCK_FM,
	PARA_BLOCK_MAX,
	
	// ������������ֻ�ڶ�ȡȱʡ����ʱʹ�ã�
	PARA_BLOCK_SYS, // ��ȡϵͳȱʡ����
	PARA_BLOCK_ALL  // ��ȡ����ȱʡ����

} PARABLOCKNAME;

/* ������ID */
typedef enum {
	SENSOR_FIRST,
	SENSOR_FHR_CH1 = SENSOR_FIRST,
	SENSOR_FHR_CH2,
	SENSOR_TOCO,
	SENSOR_FM,
	SENSOR_MAX
}SENSORINDEX;

/* �������� */
typedef enum {
   PARAM_MAX
}PARAM_INDEX;

/* �������� */
typedef enum {
   ALM_PARAM_MAX
}PARAM_ALARM_CODE_INDEX;


/* ʵʱ��¼�Ĳ��γ���,��λ,��. */
typedef enum {
	RT_REC_LEN_CONTINUE,   /* ���� */
	RT_REC_LEN_8s,		 /*  */
	RT_REC_LEN_16s,		/*  */
	RT_REC_LEN_32s		 /*  */
}RT_REC_LEN;

/* ʵʱ��¼ģʽ. */
typedef enum {
	RT_REC_MANUAL ,		/* �ֶ���ʽ */
	RT_REC_AUTO			/* �Զ���ʽ */
}RT_MODE;

/* ��¼�����ٶ�. mm/s */
typedef enum {
  REC_SPEED_25,
  REC_SPEED_50
} REC_SWEEPSPEED;

/* �Զ���¼��ʱ���� */
typedef enum {
  REC_PERIOD_OFF,	/* �ر��Զ���¼���� */
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

//��������
typedef enum  {
   INT_RAW,	 //������ԭʼ
   INT_X10,	 //�����Ŵ���10����
   INT_X100,	//�����Ŵ���100����
   INT_X1000	//�����Ŵ���1000����
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
