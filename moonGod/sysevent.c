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
#define   SYSEVENT_GLOBALS 
#include  "includes.h"

#define  NR_DISP_ONEPAGE   (10)  //һҳ��ʾ���¼�����

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
 **  ע�� �໤�� ��������Ҫʱ��.���Կ�����ϵͳ����־.
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
	if (string_id == STR_EVE_BOOTUP) {  //��һ�ν���;
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
 **  ���������ʾ����.
**/
static  VOID  Disp_OnePageEvent(VOID)
{}

/**
 ** ��һ�ν���"�໤����Ϣ"�Ի���, ��ʾϵͳ�¼�.
**/
VOID  ShowSysEvent (VOID)
{}

/**
 ** �ڲ˵������Ϸ�ҳ;
 ** ����ʹ���ź�����������MonitorEventInfo�е�����; ���صı���,����Total_EventNum��
 ** ���ñ���;������Ϊ,��Щ���ر���ֻ���ڲ˵�����ʱ��ʹ��.��ȫȡ�����û�����.������
 ** �������ȡ�����.
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
	ϵͳά���˵����ڹ���.
**/
static  INT32  SysEveDlgProc (HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{}


/**
	System Event �˵�.										//Change by Latrom_07-08-2011
**/
VOID  SysEventDialog (HANDLE hOwner)
{}


