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
#if !defined(_TASK_H)
#define	  _TASK_H

#include <semaphore.h>

typedef enum _task_id 
{
	TSK_SYSTIMER,
	TSK_GUI,
	TSK_APP,
#if _ENB_REC_FUNC > 0
	TSK_REC,
	TSK_RECSEND,
#endif
#if _ENB_TOUCH
	TSK_TOUCH,
#endif
#if _ENB_AUTOUSB
	TSK_AUSB,
#endif
#if _ENB_NET_THREAD
	TSK_NET_TRAN,
	TSK_NET_RECE,
#endif

	TSK_MAX,
} TASK_ID;


typedef  INT32 (* TSKPROC)(HANDLE, INT32, UINT32, UINT32);


/**
	Task Struct 
	���ڴ���Ƚϸ��ӣ�ʹ������ȽϺ��ʣ�
	һ�㹦�ܶ�����񲻻�䶯����һ������Ϳ����ˡ�
	����һ��������׵�ַ���ɡ�funcList��
**/
typedef struct _tagTask{
	/* �����������OBJECTHEAD��ͬ����Ҫ�ı�����*/
	CHAIN_NODE	  node;
	INT16		   type;			/* the obj type. */
	INT16		   subType;		/* the sub type. */

	/* following task special												*/
	
	CHAIN_CONTROL   winList;		/* �����ڱ�����Ĵ�������				*/

	/* CHAIN_CONTROL  ObjList;											   */
	JOBP		   *jobList;		/* �����ڱ�������Ĺ��ܶ����б�		*/

	MSGQ			msgQ;
	UINT32		  mbox;		   /* mail box handle					   */
	TSKPROC		 tskProc;		/* the proc of message				   */
	UINT32		  msgBuf[4];	  /* message buffer						*/
	UINT32		  extData;		/* for extend use						*/
} TASK, * PTASK;


typedef  TASK   *TSKID;
typedef  TASK   *TSKP;
typedef  UINT32  HTSK;

typedef  VOID   (*TSKENTRY)(VOID *pdata);  /* ��������ں�����ַ				*/

typedef struct _task_info {
   CHAR	 *name;				/* ��������							   */
   UINT8	 prio;				/* ��ucos�У�ͬʱҲ��task id			  */
   VOID	 *pdata;			   /* ���ݸ���������ڵ�����ָ��		   */
   OS_STK   *pStk;				/* ջ��ʼ��ַ							 */
   UINT32	stkSize;			 /* ջ�ĳ��ȣ� ��λ: OS_STK				*/
   TSKENTRY  entry;			   /* ��������ں�����ַ				   */
   UINT16	opt;				 /* ���������ѡ��						 */
   VOID	 *pExt;				/* ���ݸ�������ƿ�ĸ������ݵ�ַ		 */
   TSKID	 task;				/* �����ڲ����ƽṹ��������ݸ�����	   */
   UINT32	msgSize;			 /* ��Ϣ���еĳ��ȣ�message numbers		*/
   //VOID	**ppmsg;			   /* ������Ϣ���е��ڴ��ַ				 */
   UINT8	 memflag;			 /* ����ջ����Ϣ�����Ƿ�̬�����̬���� */
}TASKINFO;


typedef struct _sem_info {
   CHAR	   *name;
   UINT16	  cnt;			   /* ��ʼֵ */
   //OS_EVENT  **sem;
   sem_t	   *sem;

}SEMINFO;


typedef struct _mbox_info {
   CHAR	   *name;
   VOID	   *msg;
   sem_t	  *mbox;
}MBOXINFO;


extern TASK  SysTask[];

#define SysTimer_HTSK		((HTSK)&(SysTask[TSK_SYSTIMER]))
#define SysTimer_TSKID	   (&(SysTask[TSK_SYSTIMER]))

#define SysGui_HTSK		  ((HTSK)&(SysTask[TSK_GUI]))
#define SysGui_TSKID		 (&(SysTask[TSK_GUI]))

#define SysApp_HTSK		  ((HTSK)&(SysTask[TSK_APP]))
#define SysApp_TSKID		 (&(SysTask[TSK_APP]))


#if  _ENB_REC_FUNC > 0
#define SysRec_HTSK		  ((HTSK)&(SysTask[TSK_REC]))
#define SysRec_TSKID		 (&(SysTask[TSK_REC]))
#define SysPrintSend_TSKID   (&(SysTask[TSK_RECSEND]))
#endif

#if  _ENB_REC_FUNC > 0
#define Protocol_HTSK		((HTSK)&(SysTask[TSK_RECSEND]))
#define Protocol_TSKID	   (&(SysTask[TSK_RECSEND]))
#endif

#if _ENB_TOUCH
#define SysTch_HTSK		  ((HTSK)&(SysTask[TSK_TOUCH]))
#define SysTch_TSKID		 (&(SysTask[TSK_TOUCH]))
#endif

#if _ENB_AUTOUSB
#define SysAusb_HTSK	((HTSK)&(SysTask[TSK_AUSB]))
#define SysAusb_TSKID	(&(SysTask[TSK_AUSB]))
#endif

#if _ENB_NET_THREAD
#define SysTcpT_HTSK	((HTSK)&(SysTask[TSK_NET_TRAN]))
#define SysTcpT_TSKID	(&(SysTask[TSK_NET_TRAN]))
#define SysTcpR_HTSK	((HTSK)&(SysTask[TSK_NET_RECE]))
#define SysTcpR_TSKID	(&(SysTask[TSK_NET_RECE]))
#define SysUdpT_HTSK	SysTcpT_HTSK
#define SysUdpR_HTSK	SysTcpR_HTSK
#endif

BOOL  InitSysTask(VOID);
VOID  TermSysTask(VOID);


/*  API for Task */
TASK  *CreateTask( TASKINFO * tskInfo );
INT32  DefaultTskProc(HANDLE task, INT32 msg, UINT32 nParam, UINT32 lParam);

INT32  SysTskProc	(HANDLE task, INT32 msg, UINT32 lParam, UINT32 nParam);
INT32  MonitorTskProc(HANDLE task, INT32 msg, UINT32 lParam, UINT32 nParam);
INT32  GuiTskProc	(HANDLE task, INT32 msg, UINT32 lParam, UINT32 nParam);
INT32  DataTskProc   (HANDLE task, INT32 msg, UINT32 lParam, UINT32 nParam);
INT32  AppTskProc	(HANDLE task, INT32 msg, UINT32 lParam, UINT32 nParam);
INT32  IoTskProc	 (HANDLE task, INT32 msg, UINT32 lParam, UINT32 nParam);
INT32  Com1TskProc   (HANDLE task, INT32 msg, UINT32 lParam, UINT32 nParam);
INT32  Com2TskProc   (HANDLE task, INT32 msg, UINT32 lParam, UINT32 nParam);
INT32  Com3TskProc   (HANDLE task, INT32 msg, UINT32 lParam, UINT32 nParam);
INT32  Com4TskProc   (HANDLE task, INT32 msg, UINT32 lParam, UINT32 nParam);
INT32  RecTskProc	(HANDLE task, INT32 msg, UINT32 lParam, UINT32 nParam);
INT32  NetTskProc	(HANDLE task, INT32 msg, UINT32 lParam, UINT32 nParam);

BOOL   InitSysRes(VOID); /* ��ʼ��ȫ��ϵͳ��Դ, �ź���, ��Ϣ����, ����. */

/*   */
#ifdef TASKS_GLOBALS
#define TASKS_EXT 
#else
#define TASKS_EXT  extern
#endif

/* ϵͳ�е��ź��� */
TASKS_EXT  pthread_mutex_t SysInfoItemSem;		/* ��Ϣ����ʾ��Ϣ���ṹ��ȡ����			 */
TASKS_EXT  pthread_mutex_t SysEventSem;		   /* �໤���¼��ṹ��ȡ����				   */
TASKS_EXT  pthread_mutex_t SysTimerSem;		   /* ϵͳ��ʱ����ȡ�����ź���				 */
TASKS_EXT  pthread_mutex_t DcUseSem;			  /* DCʹ�ñ����ź���						 */
TASKS_EXT  pthread_mutex_t GuiUseSem;			 /* GUIʹ�ñ����ź���						*/
TASKS_EXT  pthread_mutex_t FileAccessSem;	/* �ļ�����*/

TASKS_EXT  pthread_mutex_t RecGraphReadSem;	   /*��ӡ��ͼ�����ݶ������ź���*/
TASKS_EXT  pthread_mutex_t RecStartupSem;
TASKS_EXT  pthread_mutex_t RecDataReadSem;	/* ��ӡ�������ź��� */

TASKS_EXT  pthread_mutex_t NetCenterSem;
TASKS_EXT  pthread_mutex_t NetCenterRecSem;

/* ϵͳ�е���Ϣ���� */

/* ϵͳ�е�����	 */
TASKS_EXT  sem_t *IoAckMbox;			 /* IO����Ӧ������						   */


extern  JOB	   AlarmJob;
extern  TASKINFO  SysTaskInfo[TSK_MAX];


#define AlarmJobHdl   (HANDLE)(&AlarmJob)

void wait_for_cond_trigger();


#define MY_BUFFER_SIZE ((INT32)32768)

#define   OS_ENTER_CRITICAL()
#define   OS_EXIT_CRITICAL()

extern volatile int KillSignal;

#endif
