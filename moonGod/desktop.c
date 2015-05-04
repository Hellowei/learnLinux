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

#define   DESKTOP_GLOBALS 
#include  "includes.h"

INT		_menu_lev;
INT		_backMainScn_lev;  //已打开的对话框层数,这里的层数是相对主窗口来说的 -- empty 2011/04/20
INT		_pressed_num_key;
INT		_pressed_num_hot;
PMAINWIN   _curr_active_mainwnd;



/* 本函数在InitGui中调用.此时, OS还没有初始化. */
BOOL  InitDesktop(VOID)
{
	_menu_lev			 = 0;
	_backMainScn_lev	  = 0;
	_pressed_num_key	  = 0;
	_pressed_num_hot	  = 0;
	_curr_active_mainwnd  = 0; // HWND_DESKTOP;
	
	return TRUE;

error:
	return FALSE;
}


BOOL  InitDesktopMem(VOID)
{
	long   buf_size;
	
	buf_size = imagesize(0, 0, LB_DROPREC_W, LB_DROPREC_H);
	ListboxDropBuff = my_malloc(buf_size);
	if (!ListboxDropBuff){
		goto error;
	}
	return TRUE;
	
error:
	return FALSE;
}

VOID  TermDesktopMem(VOID)
{
	if (ListboxDropBuff)  
		my_free(ListboxDropBuff);
}

VOID  InitDesktopTopWinList(VOID)
{
	CHAIN_CONTROL  *pWinList;
	TSKP			ptsk;
	
	ptsk	 = (TSKP)SysGui_HTSK;
	pWinList = &ptsk->winList;
	_Chain_Initialize_empty(pWinList);
}

#define DesktopSetActiveWindow(pWin)   _curr_active_mainwnd = pWin


static PMAINWIN dskGetNextVisibleMainWindow (PMAINWIN pWin)
{
	PMAINWIN		pMainWin;
	CHAIN_CONTROL  *pWinList;
	TSKP			ptsk;
	
	pMainWin = (PMAINWIN)pWin->node.next;
	ptsk	 = (TSKP)(pWin->task);
	pWinList = &ptsk->winList;
	if (!_Addresses_Equal(pMainWin, _Chain_Tail(pWinList))) {
		return pMainWin;
	} else {
		return 0;
	}
}

static PMAINWIN dskGetPreviousVisibleMainWindow (PMAINWIN pWin)
{
	PMAINWIN		pMainWin;
	CHAIN_CONTROL  *pWinList;
	TSKP			ptsk;
	
	pMainWin = (PMAINWIN)pWin->node.previous;
	ptsk	 = (TSKP)(pWin->task);
	pWinList = &ptsk->winList;
	if (!_Addresses_Equal(pMainWin, _Chain_Head(pWinList))) {
		return pMainWin;
	} else {
		return 0;
	}
}

/**
   改变了当前激活的主窗口. 目前系统不考虑非客户区的问题.
   发消息通知前面的主窗口失去焦点, 同时通知当前的主窗口获得焦点.
**/
static PMAINWIN dskChangeActiveWindow (PMAINWIN pWin)
{
	PMAINWIN pOldActive;

	pOldActive = _curr_active_mainwnd;

	if (_Addresses_Equal(pWin, _curr_active_mainwnd))
		return	_curr_active_mainwnd;
	
	DesktopSetActiveWindow(pWin);
	
	if (pWin) {
		//SendMessage ((HWND)pWin, MSG_NCACTIVATE, TRUE, 0);
		//PostMessage ((HWND)pWin, MSG_ACTIVE, TRUE, 0);

		//PostMessage ((HWND)pWin, MSG_SETFOCUS, 0, 0);
		SendMessage ((HWND)pWin, MSG_SETFOCUS, 0, 0);
	}

	//if (pOldActive != HWND_DESKTOP  && (pOldActive->dwStyle & WS_VISIBLE)) {
	if (pOldActive 
		&& (pOldActive->dwStyle & WS_VISIBLE)) {
		//SendMessage ((HWND)pOldActive, MSG_NCACTIVATE, FALSE, 0);
		//PostMessage ((HWND)pWin, MSG_ACTIVE, FALSE, 0);
		
		//PostMessage ((HWND)pOldActive, MSG_KILLFOCUS, 0, 0);
		SendMessage ((HWND)pOldActive, MSG_KILLFOCUS, 0, 0);
	}

	return pOldActive;
}

static PMAINWIN dskHideMainWindow (PMAINWIN pWin)
{
	if (!(pWin->dwStyle & WS_VISIBLE))
		return NULL;

	// Update 
	pWin->dwStyle &= ~WS_VISIBLE;
	DesktopProc (HWND_DESKTOP, MSG_ERASEDESKTOP, 0, (LPARAM)&pWin->left);
	
	// if this is the avtive window,
	// must choose another window as the active one. 
	if (_Addresses_Equal(_curr_active_mainwnd, pWin))
		dskChangeActiveWindow (dskGetPreviousVisibleMainWindow (pWin));

	return _curr_active_mainwnd;
}



// this funciton add the new main window to the main window list.
// if new main window is a visible window,
// this new main window becomes the active window and this function
// return the old main window.
// otherwise, return NULL.
// 直接对消息 MSG_ADDNEWMAINWIN 的处理.
static PMAINWIN dskAddNewMainWindow (PMAINWIN pWin, VOID * pNode)
{
	TSKP   ptsk;
	
	pNode = pNode;
	ptsk  = (TSKP)pWin->task;
	_Chain_Append_unprotected(&ptsk->winList, &pWin->node);
	
	if (pWin->dwStyle & WS_MODALDLG) {
		_menu_lev ++;
		// 检查当前的对话框,是否和波形区重叠,如果重叠,需要把位于下方的波形块
		// 销毁;
	}
	
	if (pWin->dwStyle & WS_VISIBLE) {
		SendMessage ((HWND)pWin, MSG_NCPAINT, 0, 0);
		SendMessage ((HWND)pWin, MSG_SHOWWINDOW, SW_SHOWNORMAL, 0);
		InvalidateRect((HWND)pWin, NULL, TRUE);/* 绘制客户区*/
		return dskChangeActiveWindow(pWin);
	}

	return NULL;
}

// When destroy a main win, all main win which is covered by
// this destroying main win will be redraw.
//
// Functions which lead to call this function:
//  DestroyWindow: destroy a visible window.
//
// return: the new active window.
static PMAINWIN dskRemoveMainWindow (PMAINWIN pWin)
{
	if (pWin->dwStyle & WS_MODALDLG)
	{
		_menu_lev --;
		if (_menu_lev <= 0)
		{
			_menu_lev = 0;
			//if ( _dsk_action == SM_BACKMAIN )  _dsk_action = 0;
		}
	}
	if (pWin->dwStyle & WS_VISIBLE)
	{
		if (_Addresses_Equal(_curr_active_mainwnd, pWin))
			//dskChangeActiveWindow (dskGetFirstVisibleWindow ());
			dskChangeActiveWindow (dskGetPreviousVisibleMainWindow (pWin));

		if (_Addresses_Equal(_curr_active_mainwnd, pWin))
			//_curr_active_mainwnd = HWND_DESKTOP;
			_curr_active_mainwnd = 0;
	}

	SendMessage(HWND_DESKTOP, MSG_ERASEDESKTOP, 0, (LPARAM)&pWin->left);
	_Chain_Extract_unprotected(&pWin->node);

	return  _curr_active_mainwnd;
}

/* 通知 波形和参数主窗口, 把最下方的两个波形区空出来.也就是把WS_VISIBLE
   属性去掉.重绘背景.
   send messag : MSG_ERASEBKGND
static  void  EraseDlgRegion(void)
{
	GAL_PIXEL old_color;

	old_color = SetBrushColor(HDC_SCREEN, PIXEL_black);
	FillRect(HDC_SCREEN, DlgRect.left, DlgRect.top , RECTW(DlgRect), RECTH(DlgRect) );
	SetBrushColor(HDC_SCREEN, old_color);
}
*/

// This function called when a window was shown.
// return: the new active window.
// when return value is NULL, the active window not changed.
// 目前系统不支持对非客户区的操作.所以,屏蔽掉了MSG_NCPAINT的处理.
static PMAINWIN dskShowMainWindow(PMAINWIN pWin, BOOL bActive)
{ 
	pWin->dwStyle |= WS_VISIBLE;
	SendMessage((HWND)pWin, MSG_NCPAINT, 0, 0);
	
	InvalidateRect((HWND)pWin, NULL, TRUE);

	if (bActive)
		return dskChangeActiveWindow(pWin); 

	return NULL; 
}

/* 在父窗口中增加一个子窗口对象 */
static void dskOnNewCtrlInstance (PCONTROL pParent, PCONTROL pNewCtrl)
{
	_Chain_Append_unprotected(&pParent->subWinList, &pNewCtrl->node);

}

/* 在父窗口中删除一个子窗口对象 */
static BOOL dskOnRemoveCtrlInstance (PCONTROL pParent, PCONTROL pCtrl)
{
	CHAIN_NODE  *pNode;
	
	if ( _Chain_Is_empty(&pParent->subWinList))  
		return FALSE;

	 pNode = pParent->subWinList.first;

	 /* 确认pCtrl在pParent中的子窗口链表中. */
	 while (!_Addresses_Equal(pNode, _Chain_Tail(&pParent->subWinList))) {
		 if (_Addresses_Equal(pNode, pCtrl)) 
			break;
		 pNode = pNode->next;
	 }

	 if (!_Addresses_Equal(pNode, _Chain_Tail(&pParent->subWinList))) {
		 _Chain_Extract_unprotected(pNode); /*属于parent,则从链表中解出.*/
		 return TRUE;
	 } else {
		 return FALSE;
	 }
}

static INT32 WindowMessageHandler(INT32 message, PMAINWIN pWin, LPARAM lParam)
{
	INT32  iRet;
	MSG	msg;
	
	switch( message) {
		case MSG_ADDNEWMAINWIN:
			iRet = (INT32)dskAddNewMainWindow(pWin, 0);
			break;;
			
		case MSG_REMOVEMAINWIN:
			iRet = (INT32)dskRemoveMainWindow(pWin);
			break;
				   
		case MSG_HIDEMAINWIN:
			iRet = (INT32)dskHideMainWindow(pWin);
			break;
		
		case MSG_SHOWMAINWIN:
			iRet = (INT32)dskShowMainWindow(pWin, TRUE);
			break;
			
		case MSG_GETACTIVEMAIN:
			return (INT32)_curr_active_mainwnd;
		
		case MSG_SETACTIVEMAIN:
			return (INT32)dskChangeActiveWindow (pWin);
			
		case MSG_ENABLEMAINWIN:
			iRet = !(pWin->dwStyle & WS_DISABLED);

			if ((!(pWin->dwStyle & WS_DISABLED) && !lParam)
				|| ((pWin->dwStyle & WS_DISABLED) && lParam)) {
				if (lParam)
					pWin->dwStyle &= ~WS_DISABLED;
				else
					pWin->dwStyle |=  WS_DISABLED;

				if (pWin->dwStyle & WS_DISABLED) {
				
					//if (__mg_capture_wnd && GetMainWindow (__mg_capture_wnd) == pWin) 
					//	__mg_capture_wnd = HWND_DESKTOP;

					if (_Addresses_Equal(_curr_active_mainwnd, pWin)) {
						dskChangeActiveWindow (NULL);
						break;
					}
				}

				SendMessage ((HWND)pWin, MSG_NCPAINT, 0, 0);
			}
			break;
		
		case MSG_ISENABLED:
			return !(pWin->dwStyle & WS_DISABLED);
	}
	return iRet;
}


/// 在触摸屏上按下，切换当前焦点控件
/// 1 循环所有子控件
/// 2 如果坐标在子控件范围之内，设为焦点控件
/// 3 发送按下消息
static VOID WndClientRect(HWND hWnd, PRECT prc)
{
	PCONTROL pCtrl;
	PCONTROL pParent;
	pParent = pCtrl = (PCONTROL) hWnd;

	if (hWnd == HWND_DESKTOP) {
		*prc = g_rcScr;
		return;
	}

	prc->left   = pCtrl->cl;
	prc->top	= pCtrl->ct;
	prc->right  = pCtrl->cr;
	prc->bottom = pCtrl->cb;
	
	pParent = pParent->pParent;
	while (pParent) {
		prc->left   += pParent->cl;
		prc->top	+= pParent->ct;
		prc->right  += pParent->cl;
		prc->bottom += pParent->ct;
		pParent	  = pParent->pParent;
	}
}

#if _ENB_TOUCH
static BOOL IsMainScreenControls(INT32 x, INT32 y)
{
    PMAINWIN  	   pStart;
    CHAIN_CONTROL *pWinList;

	if (MainScnHWnd == 0)
	{
		return FALSE;
	}
	if (_menu_lev > 0)
	{
		// 获取当前窗口区域
		RECT rc;
		SetRect(&rc,	_curr_active_mainwnd->left,
						_curr_active_mainwnd->top,
						_curr_active_mainwnd->right,
						_curr_active_mainwnd->bottom);
		if (PtInRect(&rc, x, y))
			return FALSE;
	}
	pStart = (PMAINWIN)MainScnHWnd;
	pWinList = &(pStart->subWinList);
    if (_Chain_Is_empty(pWinList))
    {
        return FALSE;
    }   
    pStart = (PMAINWIN)pWinList->first;
    while (!_Addresses_Equal(pStart, _Chain_Tail(pWinList)))
    {
        RECT rc;
        WndClientRect ((HWND)pStart, &rc);
		if (PtInRect(&rc, x, y))
		{
			if (pStart->dwStyle & WS_DISABLED)
			{
				pStart = (PMAINWIN) pStart->node.next;
				continue;
			}
			else
			{
				if (_menu_lev > 0)
				{
					BacktoMainScreen();
				}
				return TRUE;
			}
		}
        pStart = (PMAINWIN) pStart->node.next;
    }
    return FALSE;
}
#endif

static INT32 KeyMessageHandler ( INT32 message, INT32 scancode, DWORD status)
{
	switch ( message ) {
		case MSG_KEYENCODER:
//			if (KEY_KNOB_PRESSED == LOBYTE(scancode))
//			{
//				PostMessage(SysApp_HTSK, MSG_APP_SOUND_CMD,
//					CMD_SOUND_SET_KNOB_VOLUME, 0);
//			}
			return SendMessage((HWND)_curr_active_mainwnd, MSG_KEYENCODER,
								scancode, status);			

#if _ENB_TOUCH
		case MSG_TOUCHENCODER:
			{
				INT32 x, y;
				TOUCHPOINT *pt = (TOUCHPOINT*)scancode;
//				if (pt->pressed == TRUE)
//					break;
				x = pt->X;
				y = pt->Y;
//				printf("MSG_TOUCHENCODER:x, y %d, %d\n", x, y);
				if (FramFoucs(_curr_active_mainwnd, x, y))
				{
					if (pt->pressed == FALSE)
					{
						PostMessage(SysApp_HTSK, MSG_APP_SOUND_CMD,
									CMD_SOUND_SET_KNOB_VOLUME, 0);
					}
					return SendMessage((HWND)_curr_active_mainwnd,
									MSG_TOUCHENCODER, KEY_TOUCH, pt->pressed);
				}
			#if 0
				else
				{
				    printf("MSG_TOUCHENCODER2:x, y %d, %d\n", x, y);
					if (pt->pressed == FALSE)
					{
						if (!IsMainScreenControls(x, y))
							break;
						PostMessage(SysApp_HTSK, MSG_APP_SOUND_CMD,
									CMD_SOUND_SET_KNOB_VOLUME, 0);
						return SendMessage((HWND)_curr_active_mainwnd,
									MSG_TOUCHENCODER, KEY_TOUCH, pt->pressed);
					}
				}
			#endif
			}
#endif

		default:
			break;
	}

	return 0;
}

// 从链表的最后先前扫描, 关闭所有对话框.
static  void  dskCloseAllDlg(void)
{
	CHAIN_NODE	*pLast;
	CHAIN_CONTROL *pWinList;
	PMAINWIN	   pMainWin;

	pWinList = &(SysGui_TSKID->winList);
	pLast = pWinList->last;

	if (!_Addresses_Equal(pLast, Chain_Tail(pWinList))) {
		pMainWin = (PMAINWIN)pLast;
		_backMainScn_lev = _menu_lev;
		while (!_Addresses_Equal(pLast, Chain_Head(pWinList))) {
			if (pMainWin->dwStyle & WS_MODALDLG) {
			   PostMessage((HWND)pMainWin, MSG_CLOSE, 0, 0);
			}
			pLast	= pLast->previous;
			pMainWin = (PMAINWIN)pLast;
		}
	}
}


/**
  负责窗口管理.
  所有窗口的创建和销毁,包括主窗口, 控件窗口.
  系统的事件(硬件)首先在这里处理以后,再传递到焦点窗口.

  本系统暂时没有鼠标设备;
  同时,也没有PC键盘;只有编码器; 可以把编码器按键码转化为PC扫描码,然后再处理.

**/
INT32 DesktopProc (HWND hWnd, long message, WPARAM wParam, LPARAM lParam)
{
	PMAINWIN pTemp;
	INT32	iRet = 0;

	if (message >= MSG_FIRSTWINDOWMSG && message <= MSG_LASTWINDOWMSG)
		return  WindowMessageHandler (message, (PMAINWIN)wParam, lParam);

	if (message >= MSG_FIRSTKEYMSG && message <= MSG_LASTKEYMSG)
	{
		return  KeyMessageHandler(message, (INT32)wParam, lParam);
	}

#if _ENB_TOUCH
	if (message == MSG_TOUCHENCODER)
		return  KeyMessageHandler(message, (INT32)wParam, lParam);
#endif

	switch(message)
	{
		case MSG_GETCTRLCLASSINFO:
			 return (long)GetControlClassInfo ((const char*)lParam);

		case MSG_NEWCTRLINSTANCE:
			 dskOnNewCtrlInstance ((PCONTROL)wParam, (PCONTROL)lParam);
			 break;

		case MSG_REMOVECTRLINSTANCE:
			 if (!dskOnRemoveCtrlInstance ((PCONTROL)wParam, (PCONTROL)lParam))
				return  -1;
			
			 break;

		case MSG_SCRMAN:
			 if (wParam == SM_BACKMAIN)
			 {
				dskCloseAllDlg();
			 }
			 else if (wParam == SM_RESET)
			 {
				InitDesktop();
				InitDesktopTopWinList();
			 }

			 break;

		case MSG_ERASEDESKTOP:
			 if (lParam)
			 {
				RECT  *prc = (RECT*)lParam;
				SetBrushColor(HDC_SCREEN, PIXEL_black);
			 }
			 break;

		default:
			 break;
	}

	return  iRet;
}


