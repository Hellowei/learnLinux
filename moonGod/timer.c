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
#define   TIMER_GLOBALS
#include  "includes.h"


//������sys timer�и��¼�������sys timer��5ms�����ڣ����Գ���5��
static TIMER  Sys_Timer[MAX_TIMERS];
#define NR_SYS_TIMER  TABLESIZE(Sys_Timer)

/* ���ź������� */
#define  SYSTIMER_LOCK()	 pthread_mutex_lock(&SysTimerSem)
#define  SYSTIMER_UNLOCK()   pthread_mutex_unlock(&SysTimerSem)

BOOL  InitTimer (VOID)
{
	ZeroMemory(Sys_Timer, sizeof(Sys_Timer));	
	return TRUE;
}

static PTIMER  FindItem(HANDLE hdl, UINT8 id)
{
	int	 i;
	PTIMER  p;

	p = Sys_Timer;
	for ( i = 0; i < NR_SYS_TIMER; i ++ ) {
		  p = p + i;
		  if ( (p->hdl == hdl) && (p->id == id) ) break;
	}
	if ( i < NR_SYS_TIMER ) {
		return p;
	} else {
		return NULL;
	}
}

VOID TerminateTimer (HANDLE hdl, UINT8 id)
{
	PTIMER  p;
	p = FindItem(hdl, id);
	if (!p)
		return;

	SYSTIMER_LOCK();

	p->count = 0;
	p->status &= 0xFE;

	SYSTIMER_UNLOCK();
}

INT PauseTimer(HANDLE hdl, UINT8 id, UINT8 pause)
{
	PTIMER  p;

	SYSTIMER_LOCK();

	p = FindItem(hdl, id);
	if (!p)
		return ERR_TIMER_INVALIDITEM;
	p->status &= 0xFE;
	p->status |= !pause;

	SYSTIMER_UNLOCK();

	return ERR_OK;
}

INT AddTimer (HANDLE hdl, UINT8 id, UINT8 status, long elapsed)
{
	int	 i;
	PTIMER  p;
	INT	 rtn;
	UINT8   err;
	
	SYSTIMER_LOCK();
	
	if ( FindItem(hdl,id) )  {
		rtn = ERR_TIMER_SAME;
		goto EXIT;
	}
	
	p = Sys_Timer;
	for ( i = 0; i < NR_SYS_TIMER; i ++ ) {
		  p = p + i;
		  if ( p->hdl == 0 ) break;
	}

	if ( i < NR_SYS_TIMER ) {
		p->hdl	 = hdl;
		p->id	  = id;
		p->elapsed = elapsed;
		p->count   = 0;
		rtn = ERR_OK;
	} else {
		rtn = ERR_TIMER_NOSPACE;
	}

EXIT:

	SYSTIMER_UNLOCK();
	return rtn;
}

INT RemoveTimer (HANDLE hdl, UINT8 id)
{
	PTIMER  p;
	INT	 rtn;
	UINT8   err;
	
	SYSTIMER_LOCK();
	p = FindItem(hdl,id);
	if ( p ) {
		p->hdl = 0;
		rtn = ERR_OK;
	} else {
		rtn = ERR_TIMER_INVALIDITEM;
	}

	SYSTIMER_UNLOCK();

	return rtn; 
}

BOOL SetTimerElapsed (HANDLE hdl, UINT8 id, long elapsed)
{
	PTIMER  p;
	INT	 rtn;
	UINT8   err;
	
	SYSTIMER_LOCK();
	
	p = FindItem(hdl, id);
	if ( p ) {
		p->elapsed = elapsed;
		p->count   = 0;
		rtn = ERR_OK;
	} else {
		rtn = ERR_TIMER_INVALIDITEM;
	}
	
	SYSTIMER_UNLOCK();
	
	return rtn; 
}

VOID  SysTimerProc (VOID)
{
	int	 i;
	PTIMER  p;
	UINT8   err;
	
	SYSTIMER_LOCK();
	
	for (i = 0; i < NR_SYS_TIMER; i++) {
		p = Sys_Timer + i;
		if (p->hdl) {
			if (p->status & 0x01)
				p->count ++;
			if (p->count >= p->elapsed) {
				p->count = 0;
				p->status &= 0xFE;
				p->status |= (p->status & 0x02);
				PostMessage(p->hdl, MSG_TIMER, p->id, 0);
			}
		}
	}
	
	SYSTIMER_UNLOCK();
}

