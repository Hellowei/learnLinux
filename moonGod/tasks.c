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
#define   TASKS_GLOBALS
#include "includes.h"
#include "netcenter.h"
#include "netsrv.h"
void   key_simulate(void);			/**	Debug	**/
void   test_put_wavedata(void);

#define   _TASKS_DEBUG	0  /* debug switch */

extern  INT8  EnterOs;
/*  Local Variable Definition  */

/* ϵͳ���ź���*/
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

/* ϵͳ����Ϣ���� */

//static QINFO  Sys_QInfo[] = { };
#define NR_SYS_QUEUE   0 // TABLESIZE(Sys_QInfo)

/* ϵͳ������ */
static MBOXINFO  Sys_MboxInfo[] = {
	{ "IOAckMbox",	0,	(sem_t*)&IoAckMbox	},
};
#define NR_SYS_MBOX   TABLESIZE(Sys_MboxInfo)

/* ϵͳ�������� */
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
  pthread_attr_setschedpolicy(&thread_attributes, SCHED_RR);  //�̵߳ĵ��Ȳ���Ϊ "��ת��"
  pthread_attr_setinheritsched(&thread_attributes, PTHREAD_EXPLICIT_SCHED);

  // set priority
  pthread_attr_getschedparam (&thread_attributes, &thread_parameters); //ȡ�����ȼ�
  thread_parameters.sched_priority = prio;							   //�޸����ȼ�
  pthread_attr_setschedparam(&thread_attributes, &thread_parameters);  //�������ȼ�

  pthread_create(&thread_id, &thread_attributes, (void*)task, pdata);		   //�����̣߳���ڶ�������Ĭ��ΪNULL,����߳�ΪĬ������

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
	printf( "�����ջ��� !!\r\n" ); 
	return NULL; 
  }
  sUsedSize += size;
  return sContiBuff + old_used_size;
}

// ��������
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
  pthread_cond_wait(&task_cond, &task_mutex); // �������ڵȴ��źţ���ʱ��������������һ��������������
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
* \brief  ��������
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
  
  ptsk	= pinfo->task;	   //����ID�ţ���Ҳ������ľ������������ṹ��ĵ�ַ -- empty 2011/04/19
  pdata   = ptsk;			  //��ʼ�����������Ĵ������ -- empty 2011/04/19
  flag	= 0;				 //����ջ����Ϣ�����Ƿ�̬�����̬���䣬����Ϊ��̬����� -- empty 2011/04/19
  stksize = pinfo->stkSize;	//�����ջ�ĳ��� -- empty 2011/04/19
  pbos	= pinfo->pStk;	   //�����ջ����ʼ��ַ,�����Ϊ0 -- empty 2011/04/19
  
  if (pbos)					//Ĭ��Ϊ0��Ϊ��̬�����ڴ�׼�� -- empty 2011/04/19
  {  
	ptos = pbos + stksize - 1; //�ѷ����ڴ棬����pinfo�ж��� -- empty 2011/04/19
  } 
  else 
  {	   
	pbos = (OS_STK*)malloc_conti(stksize * sizeof(OS_STK)); //��̬���������ջ -- empty 2011/04/19
	if (pbos) 
	{
	  ptos = pbos + stksize - 1;  //�����ջ�Ľ�β��ַ -- empty 2011/04/19
	  pinfo->pStk = pbos;		 //�����ջ����ľ�̬��ʼ��ַ -- empty 2011/04/19
	} 
	else 
	{
	  goto error;
	}
  }
  
  sem = NULL;					 //�ź���ָ�� -- empty 2011/04/19
  if (pinfo->msgSize)
  {
	sem = CreateSemaphore();	  //Ϊ������Ϣ�����ź��������Ϊ10�� -- empty 2011/04/19
	ASSERT_REPORT(sem);
	
	p = malloc_conti(sizeof(MSG) * pinfo->msgSize);  //Ϊ������Ϣ��̬�����ڴ� -- empty 2011/04/19
	if (p)
	{
	  ptsk->msgQ.msg	   = (MSGP)p;
	  ptsk->msgQ.total	 = pinfo->msgSize;
	  ptsk->msgQ.writepos  = 0;
	  ptsk->msgQ.readpos   = 0;
	  ptsk->msgQ.usedNum   = 0;
	  ptsk->msgQ.mutex = (pthread_mutex_t *)CreateMutex();	  //Ϊ��������Ϣ���������������Ϊ15�� -- empty 2011/04/19
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
  _Chain_Prepend_unprotected( &_TaskList, &ptsk->node );  //��ʼ��ϵͳ�������� -- empty 2011/04/20
  

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
  
  pinfo->memflag = flag; //����ջ����Ϣ�����Ƿ�̬�����̬����,���ڴ��ڱ����������ڴ���ɣ��ʾ�̬�����ڴ� -- empty 2011/04/20
  
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
** \brief  ϵͳ��ʱ����������ÿ5ms����һ�Σ�
** \note   time_count, ������ʱ������Ϣ;5ms�Ľ��;20ms��ʱ��ѯָ���״̬.1���ӵĶ�ʱ����.
**		 blink_count, Ϊ��ʵ����˸.��һ������, Լ500msʱ��ʾ����,�ٹ�500ms��ʾ�ַ���ͼ��.
**		 blink�����ļ����ȻҲ��1����,���Ǻ�ǰ��Ķ�ʱ����ʱ����ȴ��500ms�ļ��.
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

	if (InitSysTask())			//�����������е��߳� -- empty 2011/04/19
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
	// ���������߳�
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
		// �Ƚ��,����д�ӡ��æ��Ϣ,����ͣ��������
		if (IsPrinterBusy())
		{
			prinfo("Printer In Busy!\r\n");
			// ����æ״̬,���޽��æ״̬�ź�'0x22'ʱʹ��
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
		OSTimeDlyHMSM(0, 0, 0, sleep_time); //�ں˵�����Сʱ��Ƭ
		if (KillSignal == TRUE)
		{
			break;
		}
	}
}


VOID  TskGuiServer (VOID *pdata)
{
	MSG	 msg;

	wait_for_cond_trigger(); //�ȴ��������������������� -- empty 2011/04/20

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



/* �� enum TASK_ID ����һ�� */
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

/* �� enum TASK_ID ����һ�� */
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

	//��ʼ��ϵͳ�����ź��������У����䣬�¼��飻
	if (!InitSysRes())  
	{
		return;
	}
	/* ���ȴ���ϵͳ�����ȼ���ߵ����� */
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

