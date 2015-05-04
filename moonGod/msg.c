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
 ** 根据输入的系统对象句柄,取得所在任务对象的指针.
 **/
PTASK   GetTaskData(HANDLE  hdl)
{
	OBJHEADP	p;
	PTASK	   ptsk;
	PMAINWIN	pMainWin;

	if (hdl == 0) {  // 如果等于HWND_DESKTOP, 返回gui任务句柄.
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

//检查窗口的合法性; 是否在系统窗口链表上;
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
		 pMainWin =  GetTopWndItem(pMainWin->id);  //检查控件所属的主窗口是否有效
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
** \brief   发送消息；直到处理完成以后才返回；
** \note	由于直接调用了窗口过程；考虑到在不同线程中调用会产生同步和资源共享的问题。
**		  所以一般不允许在本地线程之外调用和本地线程无关的消息过程；
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
  在模式对话框中退出消息循环; 
**/
INT32 GUIAPI PostQuitMessage (HWND hWnd)
{
	TSKP	 ptsk;
	PMAINWIN pMainWin;
	
	pMainWin = GetMainWindow(hWnd);
	ptsk = (TSKP)pMainWin->task;
	ptsk->extData |= QS_QUIT; /*  消息循环退出标志 */
	
	return PostMessage(hWnd, MSG_QUIT, 0, 0);
}


/**
*   \brief  从任务对象的队列中取得一个消息； 
*   \note  输入句柄必须是任务对象的句柄；同时，取得消息则返回1；错误返回0；这和其它函数不同；
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
		sem_wait(sem);					//等待信号量，获取拥有权 -- empty 2011/04/20
		if (err != OS_NO_ERR) {
			ASSERT_REPORT(err==OS_NO_ERR);
		}

		if (ptsk->extData & QS_QUIT) {
			if (ptsk == SysGui_TSKID) {
				if (_backMainScn_lev > 0) {
					_backMainScn_lev --;
				} 

				if (_backMainScn_lev <= 0){
					ptsk->extData &= ~(QS_QUIT);/* 清除标志;防止下次进来再次发送QUIT消息. */
				}
			} else {
					ptsk->extData &= ~(QS_QUIT);/* 清除标志;防止下次进来再次发送QUIT消息. */
			}

			sem_post(sem);			//释放信号量，在UCOS中即将信号量的使用位加1 -- empty 2011/04/20
			return 0; /* 退出消息循环. */
		}

		pMsgQ = &(ptsk->msgQ);
		mutex = (pthread_mutex_t *)(pMsgQ->mutex);
		if (mutex) 
		{
			pthread_mutex_lock(mutex);   //进入读取消息保护 -- empty 2011/04/20
		} 
		else 
		{
			ASSERT_REPORT(0);
		}

		if (pMsgQ->usedNum > 0) 
		{
		
			*pMsg = pMsgQ->msg[pMsgQ->readpos]; //开始读出消息 -- empty 2011/04/20
			pMsgQ->usedNum --;
			if (pMsgQ->usedNum < 0)
				pMsgQ->usedNum = 0;
				
			pMsgQ->readpos++;
			if (pMsgQ->readpos >= pMsgQ->total)  
				pMsgQ->readpos = 0;
		} 
		else 
		{
			pMsg->handle = HWND_INVALID;	   //返回无效消息 -- empty 2011/04/20
		}
		post_mail = (pMsgQ->usedNum > 0); 
		
		if (mutex) 
		{ 
			pthread_mutex_unlock(mutex);	   //释放互斥锁，允许其他线程写入消息 -- empty 2011/04/20
		} 
		else 
		{
			ASSERT_REPORT(0);
		}

		if (post_mail)
			sem_post(sem);					 //发送消息信号量，此时消息不为QS_QUIT -- empty 2011/04/20

		if (pMsg->id == MSG_QUIT)
			pMsg->handle = HWND_INVALID;
		  
		if (pMsg->handle == HWND_INVALID)
			return 1;
				 
		//如果是窗口消息,检查窗口合法性;非法窗口把窗口句柄赋值为无效值.
		p = (OBJHEADP)pMsg->handle;
		if (p->type == TYPE_HWND)
		{
			if (!WndIsValid(pMsg->handle) 
				 || !IsWindowVisible(pMsg->handle)) 
			{
				pMsg->handle = HWND_INVALID;//如果窗口已经销毁,或者不可显示;抛弃该消息
			}
		}
		
		return  (err==OS_NO_ERR);
		
	} else {
		return 0;
	}
}


/**
 ** 抛弃所有所有输入对象的消息;
 ** 可以用于窗口句柄,也可以用于其它系统对象,比如task,job等等.
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




