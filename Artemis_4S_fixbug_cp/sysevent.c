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
#define   SYSEVENT_GLOBALS 
#include  "includes.h"

#define  NR_DISP_ONEPAGE   (10)  //一页显示的事件数量

static MONITOR_EVENT  Event_OnePage[NR_DISP_ONEPAGE];
static INT16		  Curr_EventNum;
static INT16		  Curr_EventPageNum;
static INT16		  Total_EventNum;

BOOL  InitSysEvent (VOID)
{
	MonitorEventInfo.current	= -1;
	MonitorEventInfo.numOfEvent = 0;
	MonitorEventInfo.handle	 = 0;

	MonitorEventInfo.handle	 = (HANDLE)(&SysEventSem);
	
	return TRUE;
}

/**
 **  注册 监护仪 发生的重要时间.可以看成是系统的日志.
 **/
VOID  RegisterSysEvent (INT16 string_id )
{
	INT16	 i;
	pthread_mutex_t	*mutex;
	UINT8	 err;

	mutex = (pthread_mutex_t *)MonitorEventInfo.handle;
	if (mutex) {
		//OSSemPend(pSem, 0, &err);
	  pthread_mutex_lock(mutex);
	}
#if 0	
	if (string_id == STR_EVE_BOOTUP) {  //第一次进入;
		MonitorEventInfo.events[0].infoId = STR_EVE_BOOTUP;
		MonitorEventInfo.events[0].time   = DateTime;
		MonitorEventInfo.numOfEvent = 1;
		MonitorEventInfo.current	= 0;
	}
	else {
		if (MonitorEventInfo.numOfEvent < MAX_ITEMS_OF_MONITOR_EVENT) {
			MonitorEventInfo.events[MonitorEventInfo.numOfEvent].infoId   = string_id;
			MonitorEventInfo.events[MonitorEventInfo.numOfEvent].time	 = DateTime;
			MonitorEventInfo.numOfEvent ++;
			MonitorEventInfo.current ++;
		}
		else {
			for (i = 1; i < MAX_ITEMS_OF_MONITOR_EVENT - 1; i++) {
				MonitorEventInfo.events[i].infoId = MonitorEventInfo.events[i+1].infoId;
				MonitorEventInfo.events[i].time   = MonitorEventInfo.events[i+1].time;
			}
			MonitorEventInfo.events[MAX_ITEMS_OF_MONITOR_EVENT - 1].infoId = string_id;
			MonitorEventInfo.events[MAX_ITEMS_OF_MONITOR_EVENT - 1].time   = DateTime;
			MonitorEventInfo.current = MAX_ITEMS_OF_MONITOR_EVENT - 1;		 
		}			   
	}
#endif
	if (mutex) {
		//OSSemPost(pSem);
	  pthread_mutex_unlock(mutex);
	}
	return;
}

/**
 **  负责具体显示工作.
**/
static  VOID  Disp_OnePageEvent(VOID)
{}

/**
 ** 第一次进入"监护仪信息"对话框, 显示系统事件.
**/
VOID  ShowSysEvent (VOID)
{}

/**
 ** 在菜单中向上翻页;
 ** 这里使用信号量保护的是MonitorEventInfo中的内容; 本地的变量,比如Total_EventNum等
 ** 不用保护;这是因为,这些本地变量只是在菜单进入时才使用.完全取决于用户动作.不存在
 ** 多任务存取的情况.
**/
VOID  PageUpSysEvent (VOID)
{}

VOID  PageDownSysEvent (VOID)
{}

/* following is System Maintain Dialog */
static INT16   SysEveDlg_OnCommand(HWND hWnd, DWORD wParam, LPARAM lParam)
{}

static  VOID  SysEveDlgInit (HWND hWnd, DWORD wParam, LPARAM lParam)
{}

/**
	系统维护菜单窗口过程.
**/
static  INT32  SysEveDlgProc (HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{}


/**
	System Event 菜单.										//Change by Latrom_07-08-2011
**/
VOID  SysEventDialog (HANDLE hOwner)
{}


