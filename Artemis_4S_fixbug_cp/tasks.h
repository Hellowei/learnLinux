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
	窗口处理比较复杂，使用链表比较合适；
	一般功能对象服务不会变动；用一个数组就可以了。
	保存一个数组的首地址即可。funcList；
**/
typedef struct _tagTask{
	/* 下面三个项和OBJECTHEAD相同；不要改变它；*/
	CHAIN_NODE	  node;
	INT16		   type;			/* the obj type. */
	INT16		   subType;		/* the sub type. */

	/* following task special												*/
	
	CHAIN_CONTROL   winList;		/* 创建于本任务的窗口链表				*/

	/* CHAIN_CONTROL  ObjList;											   */
	JOBP		   *jobList;		/* 依赖于本任务处理的功能对象列表		*/

	MSGQ			msgQ;
	UINT32		  mbox;		   /* mail box handle					   */
	TSKPROC		 tskProc;		/* the proc of message				   */
	UINT32		  msgBuf[4];	  /* message buffer						*/
	UINT32		  extData;		/* for extend use						*/
} TASK, * PTASK;


typedef  TASK   *TSKID;
typedef  TASK   *TSKP;
typedef  UINT32  HTSK;

typedef  VOID   (*TSKENTRY)(VOID *pdata);  /* 任务处理入口函数地址				*/

typedef struct _task_info {
   CHAR	 *name;				/* 任务名称							   */
   UINT8	 prio;				/* 在ucos中，同时也是task id			  */
   VOID	 *pdata;			   /* 传递给任务处理入口的数据指针		   */
   OS_STK   *pStk;				/* 栈起始地址							 */
   UINT32	stkSize;			 /* 栈的长度； 单位: OS_STK				*/
   TSKENTRY  entry;			   /* 任务处理入口函数地址				   */
   UINT16	opt;				 /* 创建任务的选项						 */
   VOID	 *pExt;				/* 传递给任务控制块的附加数据地址		 */
   TSKID	 task;				/* 任务内部控制结构句柄；传递给任务	   */
   UINT32	msgSize;			 /* 消息队列的长度；message numbers		*/
   //VOID	**ppmsg;			   /* 任务消息队列的内存地址				 */
   UINT8	 memflag;			 /* 任务栈和消息队列是否动态分配或静态分配 */
}TASKINFO;


typedef struct _sem_info {
   CHAR	   *name;
   UINT16	  cnt;			   /* 初始值 */
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

BOOL   InitSysRes(VOID); /* 初始化全局系统资源, 信号量, 消息队列, 邮箱. */

/*   */
#ifdef TASKS_GLOBALS
#define TASKS_EXT 
#else
#define TASKS_EXT  extern
#endif

/* 系统中的信号量 */
TASKS_EXT  pthread_mutex_t SysInfoItemSem;		/* 信息栏提示信息条结构存取保护			 */
TASKS_EXT  pthread_mutex_t SysEventSem;		   /* 监护仪事件结构存取保护				   */
TASKS_EXT  pthread_mutex_t SysTimerSem;		   /* 系统定时器存取保护信号量				 */
TASKS_EXT  pthread_mutex_t DcUseSem;			  /* DC使用保护信号量						 */
TASKS_EXT  pthread_mutex_t GuiUseSem;			 /* GUI使用保护信号量						*/
TASKS_EXT  pthread_mutex_t FileAccessSem;	/* 文件操作*/

TASKS_EXT  pthread_mutex_t RecGraphReadSem;	   /*打印机图形数据读操作信号量*/
TASKS_EXT  pthread_mutex_t RecStartupSem;
TASKS_EXT  pthread_mutex_t RecDataReadSem;	/* 打印机数据信号量 */

TASKS_EXT  pthread_mutex_t NetCenterSem;
TASKS_EXT  pthread_mutex_t NetCenterRecSem;

/* 系统中的消息队列 */

/* 系统中的邮箱	 */
TASKS_EXT  sem_t *IoAckMbox;			 /* IO服务应答邮箱						   */


extern  JOB	   AlarmJob;
extern  TASKINFO  SysTaskInfo[TSK_MAX];


#define AlarmJobHdl   (HANDLE)(&AlarmJob)

void wait_for_cond_trigger();


#define MY_BUFFER_SIZE ((INT32)32768)

#define   OS_ENTER_CRITICAL()
#define   OS_EXIT_CRITICAL()

extern volatile int KillSignal;

#endif
