/******************************************************************************
***********
��Ȩ����:			�����ص�
�汾��:				1.0.0
��������:			2010.05.11
�ļ���:				
����:				ZONDAN
����˵��:			Ӧ�ò����ļ�
����˵��:			
�����ļ���ϵ:		���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
*******************************************************************************
**********/
#ifndef	 _RECMAIN_H
#define	 _RECMAIN_H


#ifdef  RECMAIN_GLOBALS
#define   RECMAIN_EXTERN
#else
#define   RECMAIN_EXTERN   extern
#endif

#define  MAX_RECPARAMROWS		   14
#define  MAX_RECPARAMLINES		  40
#define  MAX_RECSTRBUFFERLEN		100
#define  MAX_REC_NIBPLIST_NUM	   11
#define  MAX_REC_NIBPLIST_CHAR	  100
#define  GET_RECGRAPH_PERMIT()	  pthread_mutex_lock (&RecGraphReadSem);
#define  RELEASE_RECGRAPH_PERMIT()  pthread_mutex_unlock (&RecGraphReadSem);
#define  GET_RECSTARTUP_PERMIT()	pthread_mutex_lock (&RecStartupSem)
#define  RELEASE_STARTUP_PERMIT()   pthread_mutex_unlock (&RecStartupSem)

#define  GET_RECDATA_PERMIT()	   pthread_mutex_lock(&RecDataReadSem)
#define  RELEASE_RECDATA_PERMIT()   pthread_mutex_unlock(&RecDataReadSem)

#define  PRINT_MODULE_ID			0x79

#define  PRINT_RTN_CMD_ID		0x99
#define  PRINT_RTN_DATA_ID		0x31
#define  PRINT_RTN_STATUS		0x32
#define  PRINT_RTN_BUSY			0xEE
#define  PRINT_RTN_NOBUSY		0x22
#define  PRINT_RTN_HOT			0x60
#define  PRINT_RTN_PAPER		0x61
#define  PRINT_RTN_OPEN			0x62

#define REC_REGION_FHR210_MIN		1
#define REC_REGION_FHR210_MAX		199
#define REC_REGION_FHR60_MIN		400
#define REC_REGION_FHR60_MAX		640
#define REC_REGION_TOCO100_MIN		440
#define REC_REGION_TOCO100_MAX		800
#define REC_REGION_TOCO0_MIN		700
#define REC_REGION_TOCO0_MAX		1200

#define REC_REGION_FHR210_112		100
#define REC_REGION_FHR60_112		520
#define REC_REGION_TOCO100_112		548
#define REC_REGION_TOCO0_112		828

#define REC_REGION_FHR210_1561		134
#define REC_REGION_FHR60_1561		535
#define REC_REGION_TOCO100_1561		758
#define REC_REGION_TOCO0_1561		1078
enum
{
	REC_NON_REALTIME,
	REC_REALTIME
};

typedef enum 
{
   REC_FEED_DOWN,
   REC_WAIT_ONLINE,   
   REC_HALT,
   REC_HALT_ERROR,
   REC_HALT_NOPAPER,
   REC_HEAD_UP,
   REC_ERROR_RESUMABLE,
   REC_ERROR_NORESUMABLE,
   REC_ERROR_CUTTER,
   REC_ERROR_HARDWARE,
   REC_SENSOR_NOPAPER,
   REC_SENSOR_LESSPAPER,

   RECERR_MAX

} RECERROR_ID;

typedef enum {
   RECGETSTA_REAL,
   RECGETSTA_HALT,
   RECGETSTA_ERROR,
   RECGETSTA_SENSOR,

   RECGETSTA_MAX

} RECGETSTATUS_ID;

typedef enum  _record_type
{
	REC_TYPE_BASE = 0,

	REC_RT_SLICE,
	REC_RT_CONTI,
	REC_RT_AUTO,
	REC_FREEZE,
	REC_PARA_ALARM,
	REC_ARR_ALARM,
	REC_ST_ALARM,
	REC_TREND_GRAPH,
	REC_TREND_TAB,
	REC_ALARM_RECALL,
	REC_NIBP_RETRO,
	REC_PARA_ALARM_RETRO,
	REC_ARR_ALARM_RETRO,
	REC_ST_ALARM_RETRO,
	REC_TITRATION_TAB,
	REC_OXYCRG_RECORD,
	REC_WAVE_RECALL,
	REC_FETAL_RECALL,
	REC_FETAL_TIMING,
	REC_RECALL_PAGE,
	REC_RECALL_ALL,
	REC_SELF_TEST,
	REC_SETUP_PRINTER,
	REC_STOP,
	REC_TYPE_MAX
} RECORD_TYPE;

//�����ӡֽ��������,������ص�
enum _paper_region_index{
	PAPER_REG_FHR,
	PAPER_REG_TOCO,
	PAPER_REGION_MAX
}PAPER_REGION;

typedef struct _RECCONFIG
{
	UINT8  rectime;			 // ��¼������
	UINT8  speed;			   // ��ֽ�ٶ�1-25, 50 mm/s
	UINT8  recoveredSeconds;	// �����������ʱ���ڲ����� -- empty 2011/09/22
	UINT8  firstConnect;		//
	UINT8  chroma;			  // ��ӡŨ��
	UINT8  isScale;			 // �Ƿ���ÿ�δ�ӡǰ��ӡ���
	UINT8  fhrMax;			  // 240 / 210 ��Բ�ͬ����ӡֽ
	UINT8  fhrMin;			  // 30  /  60 ��Բ�ͬ����ӡֽ
	INT32  recstatus;		   // ��ӡ��״̬��,�����ʾ�쳣,Ӧ��ֹͣ���ʹ�ӡ����
	INT32  regStar[PAPER_REGION_MAX];   // regStar < regEnd, �����ӡ
	INT32  regEnd[PAPER_REGION_MAX];	// regStar > regEnd, �����ӡ
} RECCONFIG;


typedef struct _RECFHRCONTROL
{		
	FETALWAVEDATA *pFHRStart;   // ��ӡ��ʼ����ָ��
	FETALWAVEDATA *pFHREnd;	 // ��ӡ��������ָ��,ÿ�δ�ӡ�����λ��
	FETALWAVEDATA *pFHRHead;	// ����ָ��ͷ
	FETALWAVEDATA *pFHRTail;	// ����ָ��β
	UINT16  recRate;			// 3cm/min:12 2cm/min:8 1cm/min:4
	UINT16  rec_type;			// ��ӡ����
	UINT32  isBegin;			// �Ƿ�ʼ��ӡ
	UINT32  timeover;		   // ��������ָ���Ƿ�ֹͣ����ӡ������Ϣ
	UINT32  elapseSec;		  // �ѹ�ȥʱ��
	UINT32  periodTime;		 // ��ʱʱ��
	INT32   recStatus;		  // ��ӡ��״̬
} RECFHRCONTROL, *PRECFHRCONTROL;

RECMAIN_EXTERN RECFHRCONTROL RecFHRControl;


typedef enum _rec_event_type
{
	REC_EVENT_NOTHING,
	REC_EVENT_MONITOR,
	REC_EVENT_TRENDGRAPH,
	REC_EVENT_TRENDTABLE,
	REC_EVENT_OXYCRT,
	REC_EVENT_ALM_RECALL,
	REC_EVENT_NIBPLIST,
	REC_EVENT_WAVERECALL,
	REC_EVENT_FREEZE,
	REC_EVENT_SELFTEST,
	REC_EVENT_FETAL,
	REC_EVENT_RECALLPAGE,
	REC_EVENT_RECALLALL,

	REC_EVENT_MAX
}RECEVNTTYPE;


typedef enum _rec_working_type
{
	REC_WORKING_TYPE_RY,
	REC_WORKING_TYPE_ON,
	REC_WORKING_TYPE_OFF,
	REC_WORKING_TYPE_CHANGE,

	REC_WORKING_TYPE_MAX
}RECWORKINGTYPE;

typedef enum _print_rtn_data_index
{
	PRINT_RTN_DATA_INDEX_CMD,
	PRINT_RTN_DATA_INDEX_DATA,
	PRINT_RTN_DATA_INDEX_STATUS,
	PRINT_RTN_DATA_INDEX_BUSY,
	PRINT_RTN_DATA_INDEX_MAX
}PRINT_RTN_DATA_INDEX;

typedef struct _tagRECRECALL
{
	PTRPARIENT  file;
	UCHAR	   PrintType;
	UCHAR	   page;
	DATETIME	CurrTime;
	DATETIME	StartTime;
	DATETIME	EndTime;
}RECRECALL, *PRECRECALL;

RECMAIN_EXTERN RECRECALL RecRecall;

typedef struct _rec_event_class
{
	BOOL			isUartSending;	  // 
	INT32		   semaphore;		  // 1:��ӡ�����ڹ��� 0:��ӡ��δ�ڹ���״̬
	INT32		   source;			 // 
	INT32		   lastSource;			// �ź���Դ������ӡ����
	PRECFHRCONTROL  fetalAddData;	   // ̥��ʵʱ���δ�ӡ
//	PRECRECALL	  recallAddData;	  // ̥���¼��ӡ��������ָ��
	PTRPARIENT	  prntFileAddData;	// ̥�൵����ӡ��������ָ��
	PRECDRVCLASS	pRecClass;			// ָ���ӡ�����Ͷ����ָ��

	VOID (*func[REC_EVENT_MAX])(struct _rec_event_class *this);
	VOID (*RecPutGutter)(struct _rec_event_class *this);
	VOID (*RecPutScale)(struct _rec_event_class *this, BOOL isScale);
	VOID (*RecPutEndLine)(struct _rec_event_class *this);
}RECEVENTCLASS, *PRECEVENTCLASS;


RECMAIN_EXTERN RECEVENTCLASS	RecEventClass;
RECMAIN_EXTERN RECCONFIG		RecConfig;


RECMAIN_EXTERN INT32  RecordService(INT32 rec_type);
RECMAIN_EXTERN BOOL   RecInit (VOID);
RECMAIN_EXTERN BOOL   RecClassInitOps (VOID);
RECMAIN_EXTERN BOOL   RecEventClassInitOps (VOID);
RECMAIN_EXTERN VOID   RecScaleWave(INT32 top, INT32 bottom, INT32 mindata, INT32 maxdata, INT32 *data, INT32 len);
RECMAIN_EXTERN VOID   TskPrintComSend (VOID *pdata);
RECMAIN_EXTERN VOID   RecDealWithEvents (INT32 source);
RECMAIN_EXTERN VOID   RecPreStartup (PRECEVENTCLASS this);
RECMAIN_EXTERN VOID   RecTestWave (PRECEVENTCLASS this);
RECMAIN_EXTERN BOOL   InitRecModule(VOID);
RECMAIN_EXTERN INT32  mybiosprint(UINT8 byte);
RECMAIN_EXTERN VOID   uartputbuff(UINT8 *buff, INT16 len);
RECMAIN_EXTERN VOID   uartputchar(UINT8 d);
RECMAIN_EXTERN VOID   InitPrinter_110(VOID);
RECMAIN_EXTERN VOID   RecCheckAckPacks(VOID);
RECMAIN_EXTERN BOOL   RecUnpackProc (UINT8 *recdata, INT32 len);
RECMAIN_EXTERN BOOL   RecUnpackProc_110 (UINT8 *recdata, INT32 len);
RECMAIN_EXTERN VOID   RecProcInSecond (VOID);
RECMAIN_EXTERN VOID   RecRequestStatus(UINT8 type);
RECMAIN_EXTERN VOID   RecGetRealStatus_110 (VOID);
RECMAIN_EXTERN VOID   RecGetHaltStatus_110 (VOID);
RECMAIN_EXTERN VOID   RecGetErrorStatus_110(VOID);
RECMAIN_EXTERN VOID   RecGetSensorStatus_110(VOID);
RECMAIN_EXTERN INT32  RecBuildStringRegion(PRECEVENTCLASS this, INT32 x_start, INT32 y_start, INT32 y_end, UCHAR *str, INT32 sumIndex, INT32 memWidth);
RECMAIN_EXTERN VOID   Save_Record_Config(INT16 info_ndx , INT8 type);
RECMAIN_EXTERN STATUS Load_Record_Config(INT8 type);

RECMAIN_EXTERN VOID InitRceRegion(VOID);
RECMAIN_EXTERN VOID PrinterTestFunc(VOID);
RECMAIN_EXTERN VOID PrinterInitFunc(PRECDRVCLASS this);
RECMAIN_EXTERN VOID PrinterSetChroma(PRECDRVCLASS this);
RECMAIN_EXTERN VOID PrintLine_112mm(PRECDRVCLASS this);
extern VOID RecFetalStart (PRECEVENTCLASS this);
extern VOID RecRecallPageStart (PRECEVENTCLASS this);
extern VOID RecRecallAllStart (PRECEVENTCLASS this);
extern VOID UpdatePrinterStatus(VOID);
RECMAIN_EXTERN void SetPt1561pVersion(char *ver);
RECMAIN_EXTERN void Pt1561pAlarmPacket(char *alarm);
RECMAIN_EXTERN void Pt1561DebugProc(void);
#endif

