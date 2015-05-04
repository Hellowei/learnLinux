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
#define MSG_GLOBALS

#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "chain.h"
#include "object.h"
#include "msg.h"
#include "tasks.h"
#include "winstr.h"
#include "gdi.h"
#include "window.h"
#include "internal.h"
#include "system.h"

extern  INT  _backMainScn_lev; 

void test_msg_block(HANDLE  hdl);

/**
 ** ���������ϵͳ������,ȡ��������������ָ��.
 **/
PTASK   GetTaskData(HANDLE  hdl)
{
	OBJHEADP	p;
	PTASK	   ptsk;
	PMAINWIN	pMainWin;

	if (hdl == 0) {  // �������HWND_DESKTOP, ����gui������.
		return  SysGui_TSKID;
	}
	
	p	= (OBJHEADP)hdl;
	ptsk = 0;
	switch (p->type ) {
		case TYPE_HWND :
			pMainWin = GetMainWindow((HWND)hdl);
			if (pMainWin) {
				ptsk = (PTASK)pMainWin->task;
			}
			break;
			
		case TYPE_HJOB:
			ptsk = (TSKP)((JOBP)p)->task;
			break;

		case TYPE_HTSK:
			ptsk = (TSKP)hdl;
			break;
			
		default:
			break;
	}
	return ptsk;
}

PMSGQ   GetMsgQueue(HANDLE hdl)
{
	PTASK   ptsk;

	ptsk = GetTaskData(hdl);

	if (ptsk) {
		return &(ptsk->msgQ);
	} else {
		return 0;
	}
}

static WNDPROC GetWndProc (HWND hWnd)
{
	 PMAINWIN  pMainWin = (PMAINWIN)hWnd;

	 if (hWnd == HWND_DESKTOP)
		 return (WNDPROC)DesktopProc;

	 return pMainWin->winProc;
}

//��鴰�ڵĺϷ���; �Ƿ���ϵͳ����������;
BOOL   WndIsValid(HWND  win) 
{
	 PCONTROL   pCtrl;
	 PMAINWIN   pMainWin;
	 BOOL	   valid;
	  
	 valid = FALSE;

	 pMainWin = GetMainWindow(win);
	 if (IsMainWindow(win)) {
		 pMainWin =  GetTopWndItem(pMainWin->id);
		 valid = ((HWND)pMainWin != HWND_INVALID);
	 } else 
	 if (IsControl(win)) {
		 pMainWin =  GetTopWndItem(pMainWin->id);  //���ؼ��������������Ƿ���Ч
		 if ((HWND)pMainWin!= HWND_INVALID) {
			 pCtrl = (PCONTROL)win;
			 pCtrl = (PCONTROL)GetDlgItem((HWND)pMainWin, pCtrl->id);
			 valid = (pCtrl != 0);
		 }
	 }

	 return valid;
}

VOID test_gui_task(VOID);

/**
** \brief   ������Ϣ��ֱ����������Ժ�ŷ��أ�
** \note	����ֱ�ӵ����˴��ڹ��̣����ǵ��ڲ�ͬ�߳��е��û����ͬ������Դ��������⡣
**		  ����һ�㲻�����ڱ����߳�֮����úͱ����߳��޹ص���Ϣ���̣�
**/
INT32  SendMessage (HANDLE hdl, INT32 iMsg, WPARAM wParam, LPARAM lParam)
{
	OBJHEADP	p;
	WNDPROC	 winProc;
	TSKP		ptsk;
	INT32	   ret;
	
	if (hdl == HWND_INVALID) {
		return (-1);
	}
	
	if (hdl == HWND_DESKTOP) {
		ret = DesktopProc(hdl, iMsg, wParam, lParam);
		return  ret;
	}

	p = (OBJHEADP)hdl;
	
	switch (p->type) {
	
		case TYPE_HWND :
			winProc = GetWndProc((HWND)hdl);
			ret = winProc(hdl, iMsg, wParam, lParam);
			return  ret;
			
		case TYPE_HTSK:
			ret = (*((TSKP)p)->tskProc)(hdl, iMsg, wParam, lParam);
			return  ret;

		case TYPE_HJOB:
			ret = (*((JOBP)p)->proc)(hdl, iMsg, wParam, lParam);
			return  ret;

		default:
			break;
	}

	return (-1);
}

INT32  PostMessage (HANDLE hdl, INT32 iMsg, WPARAM wParam, LPARAM lParam)
{
	PMSGQ	 pMsgQ;
	MSGP	  pMsg;
	pthread_mutex_t *mutex;
	sem_t	*sem;
	UINT8	 err;
	PTASK	 ptsk;
	BOOL	  post_mail; // TRUE, post mail box; FALSE, no post;

	post_mail = FALSE; 
	pMsgQ = GetMsgQueue(hdl);
	ptsk  = GetTaskData(hdl);

	if (!pMsgQ ||!ptsk) {
		return  ERR_INV_HWND;
	}
	
	mutex = (pthread_mutex_t *)(pMsgQ->mutex);
	if (mutex) 
	{ // enter critical block
		pthread_mutex_lock(mutex);
	} else {
		ASSERT_REPORT(0);
	}
	
	if (((pMsgQ->writepos + 1) % pMsgQ->total) == pMsgQ->readpos) 
	{
		if (mutex)
		{  // exit critical block
			err = pthread_mutex_unlock(mutex);
		}
		return ERR_QUEUE_FULL;
	}
	pMsg = pMsgQ->msg + pMsgQ->writepos;

	post_mail = (pMsgQ->usedNum <= 0);
		
	pMsgQ->writepos++;
	pMsgQ->usedNum ++;

	if (pMsgQ->writepos >= pMsgQ->total)  
		pMsgQ->writepos = 0;	

	pMsg->handle = hdl;
	pMsg->id	 = iMsg;
	pMsg->wParam = wParam;
	pMsg->lParam = lParam;
	
	if (mutex) { // exit critical block
		pthread_mutex_unlock(mutex);
	} else {
		ASSERT_REPORT(0);
	}
	
	err = OS_NO_ERR;
	sem = (sem_t *)(ptsk->mbox);
	if (sem && post_mail) {
		err = sem_post(sem); 
	}

	if (err != OS_NO_ERR)
		ASSERT_REPORT(err==OS_NO_ERR);
	
	return  ((err == OS_NO_ERR) ? ERR_OK : ERR_Q_POSTFAIL);

}

/**
  ��ģʽ�Ի������˳���Ϣѭ��; 
**/
INT32 GUIAPI PostQuitMessage (HWND hWnd)
{
	TSKP	 ptsk;
	PMAINWIN pMainWin;
	
	pMainWin = GetMainWindow(hWnd);
	ptsk = (TSKP)pMainWin->task;
	ptsk->extData |= QS_QUIT; /*  ��Ϣѭ���˳���־ */
	
	return PostMessage(hWnd, MSG_QUIT, 0, 0);
}


/**
*   \brief  ���������Ķ�����ȡ��һ����Ϣ�� 
*   \note  �������������������ľ����ͬʱ��ȡ����Ϣ�򷵻�1�����󷵻�0���������������ͬ��
**/
INT32 GUIAPI GetMessage (MSGP pMsg, HANDLE hdl)
{
	pthread_mutex_t *mutex;
	sem_t	  *sem;
	OBJHEADP	p;
	TSKID	   ptsk;
	UINT8	   err;
	PCONTROL	pWin;
	PMSGQ	   pMsgQ;
	BOOL		post_mail;  //TRUE, post mailbox; FALSE, NO;
   
	p = (OBJHEADP)hdl;

	if (TYPE_HTSK != p->type) {
	   p->type = TYPE_HTSK;
	}
	if (p->type != TYPE_HTSK)
		ASSERT_REPORT(TYPE_HTSK == p->type);

	if (TYPE_HTSK == p->type) {
		
		ptsk  = (TSKP)p;
		err = OS_NO_ERR;
		sem = (sem_t *)(ptsk->mbox);
		sem_wait(sem);					//�ȴ��ź�������ȡӵ��Ȩ -- empty 2011/04/20
		if (err != OS_NO_ERR) {
			ASSERT_REPORT(err==OS_NO_ERR);
		}

		if (ptsk->extData & QS_QUIT) {
			if (ptsk == SysGui_TSKID) {
				if (_backMainScn_lev > 0) {
					_backMainScn_lev --;
				} 

				if (_backMainScn_lev <= 0){
					ptsk->extData &= ~(QS_QUIT);/* �����־;��ֹ�´ν����ٴη���QUIT��Ϣ. */
				}
			} else {
					ptsk->extData &= ~(QS_QUIT);/* �����־;��ֹ�´ν����ٴη���QUIT��Ϣ. */
			}

			sem_post(sem);			//�ͷ��ź�������UCOS�м����ź�����ʹ��λ��1 -- empty 2011/04/20
			return 0; /* �˳���Ϣѭ��. */
		}

		pMsgQ = &(ptsk->msgQ);
		mutex = (pthread_mutex_t *)(pMsgQ->mutex);
		if (mutex) 
		{
			pthread_mutex_lock(mutex);   //�����ȡ��Ϣ���� -- empty 2011/04/20
		} 
		else 
		{
			ASSERT_REPORT(0);
		}

		if (pMsgQ->usedNum > 0) 
		{
		
			*pMsg = pMsgQ->msg[pMsgQ->readpos]; //��ʼ������Ϣ -- empty 2011/04/20
			pMsgQ->usedNum --;
			if (pMsgQ->usedNum < 0)
				pMsgQ->usedNum = 0;
				
			pMsgQ->readpos++;
			if (pMsgQ->readpos >= pMsgQ->total)  
				pMsgQ->readpos = 0;
		} 
		else 
		{
			pMsg->handle = HWND_INVALID;	   //������Ч��Ϣ -- empty 2011/04/20
		}
		post_mail = (pMsgQ->usedNum > 0); 
		
		if (mutex) 
		{ 
			pthread_mutex_unlock(mutex);	   //�ͷŻ����������������߳�д����Ϣ -- empty 2011/04/20
		} 
		else 
		{
			ASSERT_REPORT(0);
		}

		if (post_mail)
			sem_post(sem);					 //������Ϣ�ź�������ʱ��Ϣ��ΪQS_QUIT -- empty 2011/04/20

		if (pMsg->id == MSG_QUIT)
			pMsg->handle = HWND_INVALID;
		  
		if (pMsg->handle == HWND_INVALID)
			return 1;
				 
		//����Ǵ�����Ϣ,��鴰�ںϷ���;�Ƿ����ڰѴ��ھ����ֵΪ��Чֵ.
		p = (OBJHEADP)pMsg->handle;
		if (p->type == TYPE_HWND)
		{
			if (!WndIsValid(pMsg->handle) 
				 || !IsWindowVisible(pMsg->handle)) 
			{
				pMsg->handle = HWND_INVALID;//��������Ѿ�����,���߲�����ʾ;��������Ϣ
			}
		}
		
		return  (err==OS_NO_ERR);
		
	} else {
		return 0;
	}
}


/**
 ** ����������������������Ϣ;
 ** �������ڴ��ھ��,Ҳ������������ϵͳ����,����task,job�ȵ�.
**/
long GUIAPI ThrowAwayMessages (HANDLE handle)
{
	MSGP		pMsg;
	PMSGQ	   pMsgQ;
	long		nCount = 0;
	long		readpos;

	pMsgQ = GetMsgQueue(handle);
	if (!pMsgQ) 
		return ERR_INV_HWND;

	readpos = pMsgQ->readpos;
	while (readpos != pMsgQ->writepos) {
		pMsg = pMsgQ->msg + readpos;

		if (pMsg->handle == handle
			 || GetMainWindow (pMsg->handle) == (PMAINWIN)handle) {
			pMsg->handle = HWND_INVALID;
			nCount ++;
		}
		
		readpos++;
		if (readpos >= pMsgQ->total) 
			readpos = 0;
	}

	return nCount;
}

INT32  GUIAPI  ThrowAwayTaskMessages (HANDLE htsk)
{
	PMSGQ	 pMsgQ;
	PTASK	 ptsk = (PTASK)htsk;
	
	pMsgQ = &ptsk->msgQ;
	pMsgQ->readpos  = 0;
	pMsgQ->writepos = 0;
	pMsgQ->usedNum  = 0;
	return 0;
}




