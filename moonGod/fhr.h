
#ifndef _FHR_H
#define _FHR_H

#if 1
typedef struct _fhr_config {
	INT8	enbFhr1;
	INT8	enbFhr2;
	INT8	enbToco;
	INT8	enbAfm;

	INT8	alarm;	  //
	INT8	alarmRec;   //
	INT8	alarmLevel; //

	INT8	mode;
	INT8	volume;	 // 胎声音量
	INT8	source;	 // 胎声通道
	INT8	sweep;	  // 波形速度
	INT8	detach;	 // 曲线分离值
	INT8	zero;	   // 宫压归零值
	INT8	type;	   // 胎动类型
	INT8	threshold;  // 自动胎动阀值
	INT8	movement_calc;

	INT16   FhrAlarmLimitHi;
	INT16   FhrAlarmLimitLo;
	INT8	recChroma;
	INT8	fastPrint;
	INT8	autoPrint;
	INT8	printMode;
	INT8	printLength;
	INT8    defaultAnalyType;//用户保存的评分设置默认值
}FHR_CONFIG;

typedef struct _fhr_params {
	INT16   fhr1;
	INT16   fhr2;
	INT8	toco;
	INT8	fm;
	INT8	afm;
	INT8	signal;
	INT16   mark;
}FHR_PARAMS;

typedef struct _fhr_status {
	INT8	selfTest;			// 自检结果; OK, OR , FAULT;
	INT8	commStoped;		   // 通讯是否已经停止
	UINT8   status;
	
	INIT_STATUS initStatus;	// 初始化的状态
}FHR_STATUS;

#if 0
#define  MAX_PACKET_LEN   11
typedef union {  
	struct {
		UINT8 id;
		UINT8 data[MAX_PACKET_LEN + MAX_PACKET_LEN - 1];
	} __attribute__ ((packed, aligned(1))) frame;
	UINT8 buffer[MAX_PACKET_LEN + MAX_PACKET_LEN];
}   __attribute__ ((packed, aligned(1))) PACKETFRAME;

#define FHR_REC_LINE_BYTES					150	   //印象打印每行需要的字节数
#define FHR_REC_LINES						1		  //印象打印的行数
typedef union
{
	struct
	{  
		UINT8 mask1;
		UINT8 mask2;
		UINT8 id;
		UINT8 data[FHR_REC_LINE_BYTES * FHR_REC_LINES];
		UINT8 checksum;
	} __attribute__ ((packed, aligned(1))) packet;
	UINT8 buff[FHR_REC_LINE_BYTES * FHR_REC_LINES + 4];
}   __attribute__ ((packed, aligned(1))) FHRRECPACKETFRAME;
#endif

typedef enum
{
	FHR_PACKET_DATA	 = 0x01,
	FHR_PACKET_REC	  = 0x03,
	FHR_PACKET_COMMAND	 = 0x0a,	
}FHRPACKETTYPES;

typedef enum  _fhr_packet_id 
{
	FHR_PARAMER_CTRL_CMD = 0x0a,
	FHR_RECODER_CTRL_CMD = 0x01,
	FHR_PARAMER_DATA_CMD = 0x03,

	FHR_MAX
} FHR_PACKET_ID;

#define FHR_ASK_PACKET_LEN					6
#define FHRDATA_FLAG						0x55AA

#ifdef  FHR_GLOBALS
#define   FHR_EXTERN
#else
#define   FHR_EXTERN   extern
#endif

FHR_EXTERN  FHR_CONFIG  FhrConfig;
FHR_EXTERN  FHR_STATUS  FhrStatus;
FHR_EXTERN  FHR_PARAMS  FhrParams;


//FHR_EXTERN  ACKINFO  FhrIoAckInfo;
#define  FHR_NOTIFY_ACK()		   1//OSMboxPost(IoAckMbox,(void*)1)
#define  FHR_WAIT_ACK()			 //OSMboxPend(IoAckMbox,0,&err)

#define  FHRACKINFO_ENTER_CRITICAL()	 // OSSemPend(FhrAckSem,0,&err)
#define  FHRACKINFO_EXIT_CRITICAL()	  // OSSemPost(FhrAckSem)

#define  FHR_PARAM_RATE  4
#define  FM_INTERVAL_LIMIT 10    // 胎监包每秒2个,10 = 5秒内胎动无效
#define FHR_FACE_CTRL_NUM  6
enum
{
	FHR_CTRL_FACE,
	FHR_CTRL_WAVR_FHR,
	FHR_CTRL_WAVE_TOCO,
	FHR_CTRL_HOTKEY_RECALL,
	FHR_CTRL_HOTKEY_RESETTOCO,
	FHR_CTRL_HOTKEY_REC
};

typedef enum _tagFetalMarkType
{
	FETAL_MARK_NONE,
	FETAL_MARK_ANALY,
	FETAL_MARK_EVENT,
	FETAL_MARK_ZERO,
	FETAL_MARK_FM,
	FETAL_MARK_MAX
}FETAL_MARK_TYPE;

BOOL  InitFhr(VOID);
VOID  FhrInitStatus(VOID);
VOID  FhrInitParams(VOID);
VOID  FhrInitWaveInfo(VOID);
VOID  FhrInitModuleInfo(VOID);
VOID  FhrUpdateStatus(UINT8 status);
VOID  FhrProcInSecond(VOID);
VOID  FhrDataCorrection (VOID);


VOID  PutFhrValue(FHR_PARAMS *params);
VOID  PutFhrStatusByte (UINT8 status1, UINT8 status2);

typedef struct _fhr_real_bufinfo {
	FETALWAVEDATA *   trendBufHead;
	FETALWAVEDATA *   trendBufTail;
	FETALWAVEDATA *   trendBufCurrPtr;
	DATETIME	dateTimeOfCurrPtr;
}FHR_REAL_BUF_INFO;

typedef struct _fhr_packet_buf
{
	INT		readIndex;
	INT		prereadIndex;
	INT		writeIndex;
}FHRPACKETBUF;

typedef struct _tagMarkEvent
{
	UCHAR   zerobits  :1;
	UCHAR   fmbits	:1;
	UCHAR   afmbits   :1;
	UCHAR   eventbits :1;
	UCHAR   analybits :1;
	UCHAR			 :0;//reserve
	UCHAR   event;
	UCHAR   analy;
	UCHAR   reserve;
}MARKEVENT;


FHR_EXTERN UINT8	  FhrRedrawFace;
FHR_EXTERN UINT8	  FhrSelectedPage;
FHR_EXTERN DATETIME   FhrStartTime;

#define FETAL_SAMPLE_RATE	4
#define FETAL_REAL_DATALEN  (WAVE_DIMENSIONS_W * FETAL_SAMPLE_RATE * 60 / 100)
#define FETAL_REAL_LENGTH   WAVE_WIDTH
#define REC_FHR_CURVE_POINTS	12
#define   FHR_MAX_OFFSET	35

typedef struct _fhr_wave
{
	HWND		hFhrGph;
	HWND		hTocoGph;
	BUTTONDATA  btnleft;
	BUTTONDATA  btnrignt;
	SCROLLDATA  scrdata;
	PBITMAPMEM  fhr_back;
	PBITMAPMEM  toco_back;
	INT16	   PgNdx;
	INT16	   PgCnt;
	FETALWAVEDATA *pHead;
	FETALWAVEDATA *pTail;
	FETALWAVEDATA *pPage;
	FETALWAVEDATA *pCurr;
	DATETIME	currTime;
	INT16	   xPos;
	INT16	   yPos[WAVE_MAX][WAVE_WIDTH];
	MARKEVENT   marks[WAVE_WIDTH];
	UINT8	   drawFlag;
	UINT8	   redrawFlag;
}FHRWAVE, *PFHRWAVE;

FHR_EXTERN UINT16		   FhrLastCtrlCmd;
FHR_EXTERN UINT16		   FhrRecLastCmd;
// 波形数据保存、当前页
FHR_EXTERN INT16	RecFhr1RealSave [REC_FHR_CURVE_POINTS];
FHR_EXTERN INT16	RecFhr2RealSave [REC_FHR_CURVE_POINTS];
FHR_EXTERN INT16	RecTocoRealSave [REC_FHR_CURVE_POINTS];
FHR_EXTERN INT16	RecAutoRealSave [REC_FHR_CURVE_POINTS];
FHR_EXTERN UINT8	RecEventRealSave[REC_FHR_CURVE_POINTS];
FHR_EXTERN UINT8	RecMarkRealSave [REC_FHR_CURVE_POINTS];
FHR_EXTERN PFHRWAVE FetalWavePrint;

#define FetalGetDemoPacket FetalIndemoPacket()

VOID InitFhrRealData();
VOID SaveFhrRealData();
INT16 GetPageOfCurPtr(INT16 speed, INT16 * offset);
INT16 GetStep(INT16 speed);
VOID GetFhrRect(INT16 *left, INT16 *top, INT16 * width, INT16 * height);

VOID UpdateRealWave(INT16 speed);
VOID RecFhrTestFunction(VOID);
FHR_EXTERN VOID ReDrawFetalWave(PFHRWAVE this);
FHR_EXTERN VOID FhrDrawWave(VOID);
FHR_EXTERN VOID WavePageUp(VOID);
FHR_EXTERN VOID WavePageDown(VOID);
FHR_EXTERN VOID SetFetalDetach(BOOL detach);
FHR_EXTERN VOID SetFetalMonitorDemoStyle(BOOL isDemo);

#endif
#endif

