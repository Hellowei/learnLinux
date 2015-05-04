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
#ifndef _PARAMS_H
   #define _PARAMS_H

#define  WAVE_SECONDS		 42
#define  LONG_TREND_LENGTH	10080	//three hours
#define  SHORT_TREND_LENGTH   3600	 //one hour

#define  INVALID_PARAM_INT	   (-100)
#define  INVALID_PARAM_FLOAT	 (-100.0)
#define  INVALID_PARAM		   (-100)
#define  PARAM_MODULE_NOT_EXIST  (-200)
#define  UNKNOWN_PARAM		   (-400)
#define  NOVALUE		(-100)			//Change by Latrom_07-20-2011



/*  Event Trend; 系统事件的趋势结构  */
typedef struct _event_trend_params {
	UINT8   flag;
	UINT8   reserve;
}EVENT_TREND_PARAMS;


/*  Event Trend Buffer  */
typedef struct _event_trend_bufinfo {
   EVENT_TREND_PARAMS  * trendBufHead;
   EVENT_TREND_PARAMS  * trendBufTail;
   EVENT_TREND_PARAMS  * trendBufCurrPtr;
   DATETIME			  dateTimeOfCurrPtr;
}EVENT_TREND_BUFINFO;


typedef struct _all_params {
	INT16 fhr1;
	INT16 fhr2;
	INT16 toco;
	INT16 fm;
	INT16 afm;
	INT16 signal;
}ALL_PARAMS;


/*  Monitor status events -------------------------------------------- */
#define  MAX_ITEMS_OF_MONITOR_EVENT   50


typedef struct _monitor_event {
	INT16	   infoId;   //事件类型;其实就是string id
	DATETIME	time;	 //事件发生时间　　　　
} MONITOR_EVENT, *PMONITOR_EVENT;


typedef struct _monitor_event_info {
	MONITOR_EVENT  events[MAX_ITEMS_OF_MONITOR_EVENT];	//事件数组
	INT16		   current;							   //指向最新的事件
	INT16		   numOfEvent;							//事件的个数
	HANDLE		  handle;
}MONITOR_EVENT_INFO;


// define the max wave length(int bytes) of a second.
#define WAVE_BYTES_SECOND_MAX		   256

#define WAVE_BUF_LENGTH				 WAVE_BYTES_SECOND_MAX*32

typedef struct _fhr_real_params {
	UCHAR   fhr1;   // 胎心1曲线
	UCHAR   fhr2;   // 胎心2曲线
	UCHAR   toco;   // 宫缩压力曲线
	UCHAR   afm;	// 自动胎动曲线
	UCHAR   event;	 // 系统事件,每次最多只有一个事件
	UCHAR  fmmark  :1;	 // 打标标记
	UCHAR  afmmark :1;
	UCHAR  zero	:1;	 // 宫压归零
	UCHAR  fhr1Eff :1;
	UCHAR  fhr1Alm :1;
	UCHAR  fhr2Eff :1;
	UCHAR  fhr2Alm :1;
	UCHAR  tocoEff :1;
}__attribute__ ((packed, aligned(2)))FHR_REAL_PARAMS, *PFHRPARAM;

typedef struct{
	UCHAR fhr1;
	UCHAR fhr2;
	CHAR  toco;
	CHAR  afm;
	UCHAR event;	//占位用,两字节对齐
	CHAR  zerobits  :1;
	CHAR  fmbits	:1;
	CHAR  afmbits   :1;
	CHAR  fhr1Alm   :1;
	CHAR  fhr1Eff   :1;
	CHAR  fhr2Alm   :1;
	CHAR  fhr2Eff   :1;
	CHAR  tocoEff   :1;
}__attribute__ ((packed, aligned(2)))FETALWAVEDATA;


#define FETAL_PAGE_TIME	 (WAVE_CX_CM / 3)			// 最高速3cm/min
#define FETAL_WAVE_SAVEMIN  (24 * 60)				   //24小时常规储存
#define FETAL_WAVE_PAGE_MAX (FETAL_WAVE_SAVEMIN / FETAL_PAGE_TIME)
#define MAX_FETAL_DATA_LEN  (FETAL_SAMPLE_RATE * FETAL_WAVE_SAVEMIN * 60)
#define FETAL_DATA_BUFF_LEN (MAX_FETAL_DATA_LEN * sizeof(FETALWAVEDATA))

#ifdef  PARAMS_GLOBALS
#define PARAMS_EXTERN  
#else
#define PARAMS_EXTERN  extern
#endif

// All parameters ----------------------------------------------------
PARAMS_EXTERN  ALL_PARAMS	AllParams;


// Trend data --------------------------------------------------------


#if _ENB_MONITOREVENT_FUNC > 0
//  Monitor status events----------------------------------------------
PARAMS_EXTERN  MONITOR_EVENT_INFO   MonitorEventInfo;

#endif

PARAMS_EXTERN   FETALWAVEDATA   *FetalWaveBuffPtr;
PARAMS_EXTERN   FETALWAVEDATA   *FetalWaveBuffHeadPtr;
PARAMS_EXTERN   FETALWAVEDATA   *FetalWaveBuffTailPtr;
PARAMS_EXTERN   FETALWAVEDATA   *FetalWaveBuffWritePtr;


VOID  CollectParams( INT module_id );
BOOL  InitParam(VOID);

#endif

