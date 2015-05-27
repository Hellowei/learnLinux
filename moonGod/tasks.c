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
#define   TASKS_GLOBALS
#include "includes.h"
#include "netcenter.h"
#include "netsrv.h"
void   key_simulate(void);			/**	Debug	**/
void   test_put_wavedata(void);

#define   _TASKS_DEBUG	0  /* debug switch */

extern  INT8  EnterOs;
/*  Local Variable Definition  */

/* 系统的信号量*/
static SEMINFO   Sys_SemInfo[] = {
	 { "SysTimerSem",		1, (sem_t*)&SysTimerSem		}
	,{ "SysInfoItemSem",	1, (sem_t*)&SysInfoItemSem	}
	,{ "SysEventSem",		1, (sem_t*)&SysEventSem		}
	,{ "DcUseSem",			1, (sem_t*)&DcUseSem		}
	,{ "GuiUseSem",			1, (sem_t*)&GuiUseSem		}
	,{ "FileAccessSem",		1, (sem_t*)&FileAccessSem	}
	,{ "NetCenterSem",		1, (sem_t*)&NetCenterSem	}
	,{ "NetCenterSemRec",	1, (sem_t*)&NetCenterRecSem	}
};

#define NR_SYS_SEM  TABLESIZE(Sys_SemInfo)

/* 系统的消息队列 */

//static QINFO  Sys_QInfo[] = { };
#define NR_SYS_QUEUE   0 // TABLESIZE(Sys_QInfo)

/* 系统的邮箱 */
static MBOXINFO  Sys_MboxInfo[] = {
	{ "IOAckMbox",	0,	(sem_t*)&IoAckMbox	},
};
#define NR_SYS_MBOX   TABLESIZE(Sys_MboxInfo)

/* 系统任务链表 */
static CHAIN_CONTROL  _TaskList;

UINT8  OSTimeDlyHMSM (UINT8 hours, UINT8 minutes, UINT8 seconds, UINT16 milli)
{
#if 1
  UINT32 ticks;
  UINT16 loops;
  fd_set rfds;
  int fd = 1;
  struct timeval tv;
  
  FD_ZERO (&rfds);
  FD_SET (fd, &rfds);
  tv.tv_sec = 0;
  tv.tv_usec = milli * 1000;
  select (0, NULL, NULL, NULL, &tv);  
#endif
  return -4;
}

VOID ms_sleep(INT32 ms)
{
	OSTimeDlyHMSM(0, 0, 0, ms);
}
UINT8  OSTaskCreateExt (void   (*task)(void *pd),  
						void	*pdata,
						OS_STK  *ptos,
						UINT8	prio,
						UINT16   id,
						OS_STK  *pbos,
						UINT32   stk_size,
						void	*pext,
						UINT16   opt)
{
  pthread_t		  thread_id;
  pthread_attr_t	 thread_attributes;
  struct sched_param thread_parameters;

  pthread_attr_init(&thread_attributes);
  pthread_attr_setschedpolicy(&thread_attributes, SCHED_RR);  //线程的调度策略为 "轮转法"
  pthread_attr_setinheritsched(&thread_attributes, PTHREAD_EXPLICIT_SCHED);

  // set priority
  pthread_attr_getschedparam (&thread_attributes, &thread_parameters); //取得优先级
  thread_parameters.sched_priority = prio;							   //修改优先级
  pthread_attr_setschedparam(&thread_attributes, &thread_parameters);  //设置优先级

  pthread_create(&thread_id, &thread_attributes, (void*)task, pdata);		   //创建线程，如第二个参数默认为NULL,则此线程为默认属性

  return OS_NO_ERR;
}

static INT32 sUsedSize = 0;
UINT8 sContiBuff[327680L]; // 32 * 1024

VOID* malloc_conti(INT32 size)
{
  INT32 total_size	= 327680L;
  INT32 old_used_size = sUsedSize;
  
  if (size > (total_size - old_used_size))
  {
	printf( "任务堆栈溢出 !!\r\n" ); 
	return NULL; 
  }
  sUsedSize += size;
  return sContiBuff + old_used_size;
}

// 触发任务
pthread_mutex_t task_mutex;
pthread_cond_t  task_cond;

void init_cond_mutex()
{
  pthread_mutex_init(&task_mutex, NULL);
  pthread_cond_init(&task_cond, NULL);
}

void wait_for_cond_trigger()
{
  pthread_mutex_lock(&task_mutex);  
  pthread_cond_wait(&task_cond, &task_mutex); // 这里正在等待信号，此时条件变量必须与一个互斥锁关联，
  pthread_mutex_unlock(&task_mutex);
}

void cond_trigger()
{
  pthread_cond_broadcast(&task_cond);
}


BOOL  InitSysRes (VOID)
{
  UINT8	 err;
  int	   i;
  SEMINFO  *semP;
  MBOXINFO *mbP;
  int	   rtn;
  
  semP = Sys_SemInfo;
  for (i = 0; i < NR_SYS_SEM; i++)
  {
	semP = Sys_SemInfo + i;
	rtn = pthread_mutex_init((pthread_mutex_t*)semP->sem, NULL);
	if (rtn != 0) 
	{
	  goto err;
	}
  }
  
  mbP = Sys_MboxInfo;
  for (i = 0; i < NR_SYS_MBOX; i++) {
	mbP = Sys_MboxInfo + i;
	rtn = sem_init(mbP->mbox, 0, 0);
	if (rtn != 0) {
	  goto err;
	}
  }
  
  return TRUE;
  
err:
  return FALSE;
}


TASK *FirstTask(VOID)
{
  TASK * first;
  
  if (_Chain_Is_empty(&_TaskList))
  {
	return NULL;
  }
  
  first = (TASK *)_TaskList.first;
  
  return first;
}

#define  DYN_ALLOC_STK   0x01	/* dynamic alloc memory for Task Stack		 */
#define  DYN_ALLOC_MSG   0x02	/* dynamic alloc memory for Task message Os queue */
#define  DYN_ALLOC_MSGQ  0x03	/* dynamic alloc memory for Task message queue */

UINT32   gui_data = 0;
UINT32 * gui_stkP = 0;

sem_t * CreateSemaphore()
{
  static int index = 0;
  static sem_t sem[10];

  if (index >= 10)
	return NULL;

  sem_init(&sem[index], 0, 0);
  return &sem[index ++];
}

pthread_mutex_t * CreateMutex()
{
  static int index = 0;
  static pthread_mutex_t mutex[16];

  if (index >= 15)
	return NULL;

  pthread_mutex_init(&mutex[index], NULL);
  return &mutex[index ++];
}

/**
* \brief  创建任务
**/
TASK * CreateTask(TASKINFO *pinfo)
{
  OS_STK	  *ptos;
  OS_STK	  *pbos;
  UINT32	   stksize;
  TASK		*ptsk;
  VOID		*pdata;
  UINT8		err;
  UINT8		flag;
  VOID		*p;
  JOBP		*ppjob;
  int		  i;
  sem_t	   *sem;
  
  ptsk	= pinfo->task;	   //任务ID号，在也是任务的句柄，即本任务结构体的地址 -- empty 2011/04/19
  pdata   = ptsk;			  //初始化任务处理函数的传入参数 -- empty 2011/04/19
  flag	= 0;				 //任务栈和消息队列是否动态分配或静态分配，这里为静态分配的 -- empty 2011/04/19
  stksize = pinfo->stkSize;	//任务堆栈的长度 -- empty 2011/04/19
  pbos	= pinfo->pStk;	   //任务堆栈的起始地址,这里均为0 -- empty 2011/04/19
  
  if (pbos)					//默认为0，为静态分配内存准备 -- empty 2011/04/19
  {  
	ptos = pbos + stksize - 1; //已分配内存，此在pinfo中定义 -- empty 2011/04/19
  } 
  else 
  {	   
	pbos = (OS_STK*)malloc_conti(stksize * sizeof(OS_STK)); //静态分配任务堆栈 -- empty 2011/04/19
	if (pbos) 
	{
	  ptos = pbos + stksize - 1;  //任务堆栈的结尾地址 -- empty 2011/04/19
	  pinfo->pStk = pbos;		 //任务堆栈分配的静态起始地址 -- empty 2011/04/19
	} 
	else 
	{
	  goto error;
	}
  }
  
  sem = NULL;					 //信号量指针 -- empty 2011/04/19
  if (pinfo->msgSize)
  {
	sem = CreateSemaphore();	  //为任务消息创建信号量，最多为10个 -- empty 2011/04/19
	ASSERT_REPORT(sem);
	
	p = malloc_conti(sizeof(MSG) * pinfo->msgSize);  //为任务消息静态分配内存 -- empty 2011/04/19
	if (p)
	{
	  ptsk->msgQ.msg	   = (MSGP)p;
	  ptsk->msgQ.total	 = pinfo->msgSize;
	  ptsk->msgQ.writepos  = 0;
	  ptsk->msgQ.readpos   = 0;
	  ptsk->msgQ.usedNum   = 0;
	  ptsk->msgQ.mutex = (pthread_mutex_t *)CreateMutex();	  //为此任务消息创建互斥锁，最多为15个 -- empty 2011/04/19
	  ASSERT_REPORT(ptsk->msgQ.mutex);
	}
  }
  ptsk->mbox = (HANDLE)sem;
 
  // create Task
  err = OSTaskCreateExt(pinfo->entry,
	pdata,
	ptos,
	pinfo->prio,
	pinfo->prio,
	pbos,
	stksize,
	pinfo->pExt,
	pinfo->opt);
  
  if (err != OS_NO_ERR) 
	goto error;
  
  _Chain_Initialize_empty(&ptsk->winList); 
  _Chain_Prepend_unprotected( &_TaskList, &ptsk->node );  //初始化系统任务链表 -- empty 2011/04/20
  

  if (ptsk->jobList)
  {
	ppjob = ptsk->jobList;
	for ( ; ; ) 
	{
	  (*ppjob)->task = (HANDLE)ptsk;

	  ppjob ++;
	  if (0 == *ppjob) 
		break;
	}
  }
  
  pinfo->memflag = flag; //任务栈和消息队列是否动态分配或静态分配,由于窗口必须由连续内存组成，故静态分配内存 -- empty 2011/04/20
  
  return ptsk;
  
error:
  if (flag & DYN_ALLOC_STK)   
	my_free(pinfo->pStk);
  if (flag & DYN_ALLOC_MSGQ)  
	my_free((void *)(ptsk->msgQ.msg));
  
  return NULL;
}

extern UINT8 KB_Volume;
extern UINT8 Alarm_Volume;
extern UINT8 Heart_Volume;
extern UINT8 Kb_Soundflag ;
extern UINT8 Alarm_Soundflag ;
extern UINT8 Heart_Soundflag ;

static UINT16 KbSCount = 0;
static UINT16 AlarmSCount = 0;
static UINT16 HeartSCount = 0;
static UINT8 Sound_doing = 0;
static UINT32 SoundCount = 0;
static UINT8 Alarm_doing = 0; 

//buaazy debug
int seccount = 0;
#define ReadAD  0x25
#define VBAT	0x01
#define V50	 0x00
#define V12	 0x02
#define V33	 0x03

#define BatCal  100
#define NoBat   50
#define BatCharge 20
#define HaveAC  2

#define SET_RED_LED	 0x22
#define SET_GRN_LED	 0x24
#define PWM_EN		  0x26

#define SET_VOL_1	  0x27
#define SET_VOL_2	  0x28

#define LED_ON	   1//0
#define LED_OFF	  0//1

//#define LiBAT

extern UINT8 AlarmFlash;
 
UINT32 BatTotal[3];
INT32 BatDiff[3];
UINT16 BatTemp[3];

UINT16 BatVolume[3][60];
UINT8 BatMin = 0;
UINT8 BatSec = 0;

int BatOnetime = 0;

UINT16 Alarm_Count = 0;

volatile int KillSignal = TRUE;

#if 1
static char *shmn_wd = NULL;
#include <sys/shm.h>
_open_ctrl()
{   
	int shmid;
	key_t key;
	key = ftok(FILEPATH, 1);
	shmid = shmget(key, 8, 0666 | IPC_CREAT);

	shmn_wd = (char *)shmat (shmid, 0, 0);
	
	if ((int)shmn_wd == -1)
		shmn_wd = NULL;
	else
		prinfo("_open_ctrl succeed, shmid %d\n", shmid);
}

_on_ctrl()
{
	if (!shmn_wd)
		return;
	char key = *shmn_wd;
	int  keycode;
	switch (key)
	{
			case '6':
				keycode = KEY_SILENCE;
				break;

			case '5':
				keycode = KEY_MENU;
				break;

			case '4':
				keycode = KEY_EVENT;
				break;

			case '9':
				keycode = KEY_REC_START_STOP;
				break;

			case '8':
				keycode = KEY_MAIN;
				break;

			case '1':
				keycode = KEY_KNOB_ROTATE_LEFT;
				break;

			case '2':
				keycode = KEY_KNOB_PRESSED;
				break;

			case '3':
				keycode = KEY_KNOB_ROTATE_RIGHT;
				break;

			case '*':
				keycode = KEY_FREEZE;
				break;

			case '/':
				keycode = KEY_SOS_POWER;
				return;

			case '+':
				keycode = KEY_VOL_PLUS;
				break;

			case '-':
				keycode = KEY_VOL_MINUS;
				break;

			case '7':
				keycode = KEY_NEW_PATIENT;
				break;

			case '0':
				keycode = KEY_TOCO;
				break;

			case '.':
				keycode = KEY_EXIT;
				break;

			default:
				return;
		}
	*shmn_wd = 0;
	PostMessage(SysGui_HTSK, MSG_USER_SYS_KEYMSG, keycode, 0);
}
#endif

void LedControl(int count)
{
	if ((count == 50) || (count == 98) || (count == 147) || (count == 192))
	{
		extern INT8  Sound_Alm_Lev;
		extern INT8  Alm_Lev;
		static INT16 light_timer = 0;
		UINT8 led_ctrl;
		light_timer ++;
		if (light_timer >= 8)
		{
			light_timer = 0;
		}
		if (Sound_Alm_Lev == 0)
		{
			led_ctrl = 0;
		}
		else
		{
			led_ctrl = Alm_Lev;
		}
		switch (led_ctrl)
		{
			case 0:					
				Red_led_gpio_value(LED_OFF);
				Yellow_led_gpio_value(LED_OFF);
				break;

			case 1: 
//				if (AlmGlbCtlr.AlmSilent)
//				{
//					Red_led_gpio_value(LED_OFF);
//				}
//				else
				{
					Red_led_gpio_value(light_timer % 2);
				}
				Yellow_led_gpio_value(LED_OFF); 
				break;

			case 2:
				Red_led_gpio_value(LED_OFF);
//				if (AlmGlbCtlr.AlmSilent)
//				{
//					Yellow_led_gpio_value(LED_OFF);
//				}
//				else
				{
					Yellow_led_gpio_value(light_timer / 4);
				}
				break;

			case 3:
				Red_led_gpio_value(LED_OFF);
//				if (AlmGlbCtlr.AlmSilent)
//				{
//					Yellow_led_gpio_value(LED_OFF);
//				}
//				else
				{
					Yellow_led_gpio_value(LED_ON);
				}
				break;
				
			default:
				break;
		}
		if (Sound_Alm_Lev == 0)
		{
			led_ctrl = 0;
		}
		else
		{
			led_ctrl = Alm_Lev;
		}
		switch (led_ctrl)
		{
			case 0:
				Blue_led_gpio_value(LED_OFF);
				break;

			case 1:
				Blue_led_gpio_value(light_timer % 2);
				break;

			case 2: 
				Blue_led_gpio_value(light_timer / 4);
				break;

			case 3:		 
				Blue_led_gpio_value(LED_ON);
				break;

			default:
				break;
		}
	}
}

#if _ENB_VIRTUAL_FB
extern BOOL gGphRotate;
#endif
/**
** \brief  系统定时器服务函数；每5ms调用一次；
** \note   time_count, 用作定时触发消息;5ms的解包;20ms定时查询指令返回状态.1秒钟的定时处理.
**		 blink_count, 为了实现闪烁.在一秒钟内, 约500ms时显示背景,再过500ms显示字符和图标.
**		 blink操作的间隔虽然也是1秒钟,但是和前面的定时处理时间上却有500ms的间隔.
**/
VOID  TskSysTimer (VOID *pdata)
{
	int   time_count;
	int   blink_count;
	UINT8 sleep_time		 = 5;

	pdata	   = pdata;
	time_count  = 0;
	EnterOs	 = TRUE;
	blink_count = 0;
	KillSignal  = FALSE;
	MonitorInfo.SystemRunTime = 3;
	init_cond_mutex();

	if (InitSysTask())			//创建其他所有的线程 -- empty 2011/04/19
	{
		EXIT_PROC(TermSysTask);
	} 
	else 
	{
		;
	}

	ms_sleep(10);
	_open_ctrl();
	ProcAfterCreateTasks();
	// 启动其他线程
	usleep(1000);
	cond_trigger();
#if _ENB_WATCHDOG > 0

#endif
	int spo2count	= 0;
	int mblink_count = 0;
	UINT8  PrinterBusyDelay = 0;
	int cnt = 0;
	int second = 0;
	for ( ; ; ) 
	{
		time_count++;  
		Alarm_Count++;
		sleep_time = 5;
		if (MonitorInfo.standby)
		{
		}
		else
		{
		}
		
		if(Alarm_Count >= 1200)
			Alarm_Count = 0; 

		if (time_count >= 200) // 1s
		{ 
			time_count = 0;

			MonitorInfo.battVolume = ((BatTemp[0]) - 490) / 4;
			
			PostMessage(SysGui_HTSK, MSG_SYS_DATA_CORRECTION, 0, 0);		
		}


		if (time_count % 10 == 0) 
		{
			_on_ctrl();
		}
		if (time_count % 10 == 1)
		{			
			FhrDrawWave();
		}
		if (time_count % 100 == 0)
		{
			if (MonitorInfo.inDemo == TRUE)
			{
				FetalPacketFound((PACKETFRAME *)FetalGetDemoPacket);
			}
		}
		if (time_count % 200 == 0)
		{
			PostMessage(SysGui_HTSK, MSG_GUI_BLINK, 0, 0);
			if (MonitorInfo.SystemRunTime < 36000000)
				MonitorInfo.SystemRunTime++;
		#if _ENB_REC_FUNC
			if (RecFHRControl.isBegin)
			{
				RecFhrElapseOneSec ();
				if (RecFHRControl.isBegin)
				{
					PostMessage(SysRec_HTSK, MSG_PRTCL_PRINTER,
								REC_FETAL_TIMING, 0);
				}
			}
		#endif
			// net server
			PostMessage(SysUdpT_HTSK, MSG_NET_UDP_QUERY, 0, 0);
		}

#if 1
		if (time_count % 25 == 0)
		{
			FetalMdlUnPackProc();
		}
		SysBoardUnPackProc();
		PrinterUnPackProc(MonitorConfig.RecorderType);
		// 先解包,如果有打印机忙消息,则暂停发送数据
		if (IsPrinterBusy())
		{
			prinfo("Printer In Busy!\r\n");
			// 消除忙状态,在无解除忙状态信号'0x22'时使用
			if (++PrinterBusyDelay >= 20)
			{
				PrinterBusyDelay = 0;
				RecConfig.recstatus &= 0xFF;
			}
		}
		else
		{
			if (PrinterBusyDelay)
				PrinterBusyDelay = 0;
		}
		LedControl(time_count);
#endif
#if _ENB_VIRTUAL_FB

#if QVFB_DEBUG < 1
		
		if ((time_count & 0x7) == 0)
			update_fb_ex(gGphRotate);
#endif
		
#endif
		OSTimeDlyHMSM(0, 0, 0, sleep_time); //内核调度最小时间片
		if (KillSignal == TRUE)
		{
			break;
		}
	}
}


VOID  TskGuiServer (VOID *pdata)
{
	MSG	 msg;

	wait_for_cond_trigger(); //等待主任务中条件变量开启 -- empty 2011/04/20

	while (GetMessage(&msg, (HANDLE)pdata)) 
	{
		DispatchMessage(&msg);
	}

	/* TODO: clean up task in Terminate process  */
}

VOID  TskAppServer (VOID *pdata)
{
	MSG	 msg;

	wait_for_cond_trigger();
	while (GetMessage(&msg, (HANDLE)pdata)) 
	{
		DispatchMessage(&msg);
	}
	/* TODO: clean up task in Terminate process  */
}

#if _ENB_REC_FUNC

VOID  TskRecServer (VOID *pdata)
{
	MSG	 msg;

	wait_for_cond_trigger();

	while (GetMessage(&msg, (HANDLE)pdata)) 
	{
		DispatchMessage(&msg);
	}
}

#endif

#if _ENB_TOUCH

VOID  TskTchServer (VOID *pdata)
{
	MSG	 msg;

	wait_for_cond_trigger();
	while (GetMessage(&msg, (HANDLE)pdata)) 
	{
		DispatchMessage(&msg);
	}
}

#endif

#if _ENB_NET_THREAD
/* net work transport */
VOID  TskNetTServer (VOID *pdata)
{
	MSG	 msg;

	wait_for_cond_trigger();

	while (GetMessage(&msg, (HANDLE)pdata)) 
	{
		DispatchMessage(&msg);
	}
}

#endif



/* 和 enum TASK_ID 次序一致 */
TASK   SysTask[TSK_MAX] = 
{
	/*   node: type:	 subType: winList: jobList:		 msgQ  mailbox  taskProc:	msgBuf[]: extData */
	 { {0}, TYPE_HTSK, 0, {0}, 0, {0}, 0, 0,				{0}, 0 }
	,{ {0}, TYPE_HTSK, 0, {0}, 0, {0}, 0, GuiTskProc,		{0}, 0 }
	,{ {0}, TYPE_HTSK, 0, {0}, 0, {0}, 0, AppTskProc,		{0}, 0 }


#if _ENB_REC_FUNC > 0
	,{ {0}, TYPE_HTSK, 0, {0}, 0, {0}, 0, RecTskProc,		{0}, 0 }
	,{ {0}, TYPE_HTSK, 0, {0}, 0, {0}, 0, DefaultTskProc,	{0}, 0 }
#endif

#if _ENB_TOUCH
	,{ {0}, TYPE_HTSK, 0, {0}, 0, {0}, 0, DefaultTskProc,	{0}, 0 }
#endif
#if _ENB_AUTOUSB
	,{ {0}, TYPE_HTSK, 0, {0}, 0, {0}, 0, DefaultTskProc,	{0}, 0 }
#endif
#if _ENB_NET_THREAD
	,{ {0}, TYPE_HTSK, 0, {0}, 0, {0}, 0, NetTranTskProc,{0}, 0 }
	,{ {0}, TYPE_HTSK, 0, {0}, 0, {0}, 0, DefaultTskProc,	{0}, 0 }
#endif
};

/* 和 enum TASK_ID 次序一致 */
TASKINFO  SysTaskInfo[TSK_MAX] = 
{
	/*  name:		priority: pdata:						pStk:   stkSize:			   entry:		 opt:									 pExt: task:			  msgSzie:	*/
	 {"SYS TIMER",	40, &SysTask[TSK_SYSTIMER],	0, TSK_SYSTIMER_STKSIZE,TskSysTimer,	OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR, 0, SysTimer_TSKID,		TSK_SYSTIMER_MSGSIZE}
	,{"SYS GUI",	35, &SysTask[TSK_GUI],		0, TSK_GUI_STKSIZE,		TskGuiServer,	OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR, 0, SysGui_TSKID,		TSK_GUI_MSGSIZE		}
	,{"SYS APP",	30, &SysTask[TSK_APP],		0, TSK_APP_STKSIZE,		TskAppServer,	OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR, 0, SysApp_TSKID,		TSK_APP_MSGSIZE		}
#if _ENB_REC_FUNC > 0
	,{"SYS REC",	25, &SysTask[TSK_REC],		0, TSK_REC_STKSIZE,		TskRecServer,	OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR, 0, SysRec_TSKID,		TSK_REC_MSGSIZE		}
	,{"PRINT SEND",	20, &SysTask[TSK_RECSEND],	0, TSK_REC_SENDDATA,	TskPrintComSend,OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR, 0, SysPrintSend_TSKID,	0					}
#endif
#if _ENB_TOUCH
	,{"SYS TOUCH",	15, &SysTask[TSK_TOUCH],	0, TSK_TCH_STKSIZE,		TouchServer,	OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR, 0, SysTch_TSKID,		0					}
#endif
#if _ENB_AUTOUSB
	,{"AUTOUSB",	10, &SysTask[TSK_AUSB],		0, TSK_AUSB_STKSIZE,	AutoUsbTask,	OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR, 0, SysAusb_TSKID,		0					}
#endif
#if _ENB_NET_THREAD
	,{"UDP TRAN",	10, &SysTask[TSK_NET_TRAN],	0, TSK_NET_STKSIZE,		TskNetTServer,	OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR, 0, SysTcpT_TSKID,		TSK_NET_MSGSIZE		}
	,{"UDP RECE",	10, &SysTask[TSK_NET_RECE], 0, TSK_NET_STKSIZE, 	TskNetRece,	OS_TASK_OPT_STK_CHK|OS_TASK_OPT_STK_CLR, 0, SysTcpR_TSKID,		0					}
#endif
};

#define NR_SYSTASKS	TABLESIZE(SysTask)

VOID  TermSysTask (VOID)
{
  TASKINFO  *pinfo;
  TSKP	   ptsk;
  int		i;
  
  for (i = 0; i < NR_SYSTASKS; i++) 
  {
	pinfo = SysTaskInfo + i;
	ptsk  = SysTask	 + i;
	
	if ((pinfo->memflag & DYN_ALLOC_STK) && pinfo->pStk)	
		  my_free(pinfo->pStk);
	if ((pinfo->memflag & DYN_ALLOC_MSGQ) && ptsk->msgQ.msg)  
		  my_free((void *)(ptsk->msgQ.msg));
  }
}

BOOL  InitSysTask(VOID)
{
  TASKINFO  *pinfo;
  TASK	  *ptsk;
  int		i;

  for (i = 1; i < NR_SYSTASKS; i++)
  {
	pinfo = SysTaskInfo + i;
	ptsk = CreateTask(pinfo); 
	if (ptsk == NULL)  
		  goto error;
  }
  return TRUE;
  
error:
  TermSysTask();
  return FALSE;
}

VOID  _sys_main (VOID)
{

	_Chain_Initialize_empty(&_TaskList);

	//初始化系统对象，信号量，队列，邮箱，事件组；
	if (!InitSysRes())  
	{
		return;
	}
	/* 首先创建系统中优先级最高的任务 */
	if (CreateTask(SysTaskInfo))
	{
		;
	} 
	else 
	{
		;
	}
}


#define NoAC   1 

