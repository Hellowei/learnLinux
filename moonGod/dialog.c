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

#define   DIALOG_GLOBALS 
#include  "includes.h"



void GUIAPI DestroyAllControls (HWND hDlg)
{
	PMAINWIN pDlg = (PMAINWIN)hDlg;
	PCONTROL pCtrl = (PCONTROL)(pDlg->subWinList.first);
	PCONTROL pNext;

	while (!_Addresses_Equal(pCtrl, _Chain_Tail(&pDlg->subWinList))) {
		pNext = (PCONTROL)pCtrl->node.next;
		DestroyWindow ((HWND)pCtrl);
		pCtrl = pNext;
	}
}

#define dlgDestroyAllControls   DestroyAllControls


INT32 GUIAPI GetDlgCtrlID (HWND hwndCtl)
{
	PCONTROL pCtrl = (PCONTROL)hwndCtl;

	if (pCtrl) {
		return pCtrl->id;
	}

	return -1;
}

HWND GUIAPI GetDlgItem (HWND hDlg, INT32 nIDDlgItem)
{
	PCONTROL pCtrl;
	PMAINWIN pMainWin = (PMAINWIN)hDlg;

	pCtrl = (PCONTROL)pMainWin->subWinList.first;

	while (!_Addresses_Equal(pCtrl, _Chain_Tail(&pMainWin->subWinList))) {
		if (pCtrl->id == nIDDlgItem)
			return (HWND)pCtrl;

		pCtrl = (PCONTROL)pCtrl->node.next;
	}
   
	return 0;
}

HWND GUIAPI GetNextDlgGroupItem (HWND hDlg, HWND hCtl, BOOL bPrevious)
{
	PCONTROL pStartCtrl, pCtrl;
	PMAINWIN pMainWin = (PMAINWIN)hDlg;

	if (hCtl)
		pStartCtrl = (PCONTROL)hCtl;
	else {
		pStartCtrl = (PCONTROL)(pMainWin->subWinList.first);
		if (bPrevious) {
			pStartCtrl = (PCONTROL)pMainWin->subWinList.last;
		}
	}

	if (bPrevious) {
		if (pStartCtrl->dwStyle & WS_GROUP) {
			if (_Addresses_Equal(pStartCtrl, pMainWin->subWinList.last)) {
				/*pStartCtrl不但是最后一个单元,还有WS_GROUP 标志, 那么就返回它. */
				return  (HWND)pStartCtrl; 
			}

			/* 从pStartCtrl开始查找下一个WS_GROUP标志的控件 */
			pCtrl = (PCONTROL)pStartCtrl->node.next;
			while (!_Addresses_Equal(pCtrl,_Chain_Tail(&pMainWin->subWinList))) {
				if (pCtrl->dwStyle & WS_GROUP)
					break;
				pCtrl = (PCONTROL)pCtrl->node.next;
			}
		}
		else {
			pCtrl = pStartCtrl;
		}
		
		if ((pCtrl->dwStyle & WS_GROUP) || _Addresses_Equal(pCtrl, pStartCtrl))
			pCtrl = (PCONTROL)pCtrl->node.previous; 

		while (!_Addresses_Equal(pCtrl, _Chain_Head(&pMainWin->subWinList))) {
			if ((pCtrl->dwStyle & WS_VISIBLE)
				&& !(pCtrl->dwStyle & WS_DISABLED))
				return (HWND)pCtrl;

			pCtrl = (PCONTROL)pCtrl->node.previous;
		}
	}
	else {
		/* 向后找下一个WS_GROUP标志的控件 */
		pCtrl = (PCONTROL)pStartCtrl->node.next;
		while (!_Addresses_Equal(pCtrl, _Chain_Tail(&pMainWin->subWinList))) {
			if (!(pCtrl->dwStyle & WS_GROUP)) {
				if ((pCtrl->dwStyle & WS_VISIBLE)
					  && !(pCtrl->dwStyle & WS_DISABLED))
					return (HWND)pCtrl;
			}
			else
				break;

			pCtrl = (PCONTROL)pCtrl->node.next;
		}
		
		pCtrl = (PCONTROL)pStartCtrl->node.previous;
		while (!_Addresses_Equal(pCtrl, _Chain_Head(&pMainWin->subWinList))) {
			if (pCtrl->dwStyle & WS_GROUP) {
				if ((pCtrl->dwStyle & WS_VISIBLE)
					  && !(pCtrl->dwStyle & WS_DISABLED))
					return (HWND)pCtrl;
				else
					break;
			}

			pCtrl = (PCONTROL)pCtrl->node.previous;
		}
		
		if (!_Addresses_Equal(pCtrl, _Chain_Tail(&pMainWin->subWinList))) {// pCtrl is the first control in group.
			pCtrl = (PCONTROL)pCtrl->node.next;
			while (!_Addresses_Equal(pCtrl, _Chain_Tail(&pMainWin->subWinList))) {
				if ( !(pCtrl->dwStyle & WS_GROUP) ) {
					if ( (pCtrl->dwStyle & WS_VISIBLE)
						  && !(pCtrl->dwStyle & WS_DISABLED) )
						return (HWND)pCtrl;
				}
				else
					break;

				pCtrl = (PCONTROL)pCtrl->node.next;
			}
		}
	}

	return hCtl;
}


HWND GUIAPI GetNextDlgTabItem (HWND hDlg, HWND hCtl, BOOL bPrevious)
{
	PCONTROL pFirstCtrl, pLastCtrl, pCtrl;
	PMAINWIN pMainWin;

	pMainWin = (PMAINWIN)hDlg;
	if (_Chain_Is_empty(&pMainWin->subWinList)) 
		return hCtl;

	/* 首先取得第一个子控件.*/
	pFirstCtrl = pCtrl = (PCONTROL)pMainWin->subWinList.first;

	/* 然后取得最后一个子控件.*/
	while (!_Addresses_Equal(pCtrl->node.next, _Chain_Tail(&pMainWin->subWinList))) {
		pCtrl = (PCONTROL)pCtrl->node.next;
	}
	pLastCtrl = pCtrl;
	
	if (hCtl) {
		pCtrl = (PCONTROL)hCtl;
		if (bPrevious)
			pCtrl = (PCONTROL)pCtrl->node.previous;
		else
			pCtrl = (PCONTROL)pCtrl->node.next;
	}
	else if (bPrevious)
		pCtrl = pLastCtrl;
	else
		pCtrl = pFirstCtrl;

	if (bPrevious) {
		while (!_Addresses_Equal(pCtrl, _Chain_Head(&pMainWin->subWinList))) {
			if ((pCtrl->dwStyle & WS_TABSTOP)
				 && (pCtrl->dwStyle & WS_VISIBLE)
				 && !(pCtrl->dwStyle & WS_DISABLED))
			{
				return (HWND)pCtrl;
			}

			pCtrl = (PCONTROL)pCtrl->node.previous;
		}
		
		pCtrl = pLastCtrl;
		while (!_Addresses_Equal(pCtrl, _Chain_Head(&pMainWin->subWinList))) {
			if ((pCtrl->dwStyle & WS_TABSTOP)
				  && (pCtrl->dwStyle & WS_VISIBLE)
				  && !(pCtrl->dwStyle & WS_DISABLED))
				{
					return (HWND)pCtrl;
				}

			pCtrl = (PCONTROL)pCtrl->node.previous;
		}
	}
	else {
		while (!_Addresses_Equal(pCtrl, _Chain_Tail(&pMainWin->subWinList))) 
		{
			if ((pCtrl->dwStyle & WS_TABSTOP)
				 && (pCtrl->dwStyle & WS_VISIBLE)
				 && !(pCtrl->dwStyle & WS_DISABLED))
				{
					return (HWND)pCtrl;
				}

			pCtrl = (PCONTROL)pCtrl->node.next;
		}

		pCtrl = pFirstCtrl;
		while (!_Addresses_Equal(pCtrl, _Chain_Tail(&pMainWin->subWinList))) {
			if ((pCtrl->dwStyle & WS_TABSTOP)
				 && (pCtrl->dwStyle & WS_VISIBLE)
				 && !(pCtrl->dwStyle & WS_DISABLED))
				{
					return (HWND)pCtrl;
				}

			pCtrl = (PCONTROL)pCtrl->node.next;
		}
	}

	return hCtl;
}

INT32 GUIAPI SendDlgItemMessage (HWND hDlg, INT16 nIDDlgItem, INT16 msg_id,
								 WPARAM wParam, LPARAM lParam)
{
	HWND hCtrl;
	
	hCtrl = GetDlgItem (hDlg, nIDDlgItem);

	if (hCtrl) {
		return SendMessage (hCtrl, msg_id, wParam, lParam);
	}

	return -1;
}

/**
	nFormat, 组成:	 
**/
BOOL GUIAPI SetDlgItemInt (HWND hDlg, long nIDDlgItem, UINT32 uValue, DWORD nFormat)
{
	HWND  hCtrl;
	char  buffer [20];
	char *text;
	BOOL  bSigned;
	UINT8 align;
	UINT8 form;
	
	if (!(hCtrl = GetDlgItem (hDlg, nIDDlgItem)))
		return FALSE;

	bSigned = (nFormat & DT_SIGNED) == DT_SIGNED;
	bSigned = bSigned;
	align   = LOBYTE((nFormat & DT_ALIGN_MASK) >> 8);
	form	= LOBYTE(nFormat);

	switch (form) {
		case  FORM_2D:
			if (align&DT_ALIGN_LEFT) {
				sprintf (buffer, "%-2d", (long)uValue);
			} else {
				sprintf (buffer, "%2d", (long)uValue);
			}
			break;
			
		case  FORM_3D:
			if (align&DT_ALIGN_LEFT) {
				sprintf (buffer, "%-3d", (long)uValue);
			} else {
				sprintf (buffer, "%3d", (long)uValue);
			}
			break;
			
		case  FORM_4D:
			if (align&DT_ALIGN_LEFT) {
				sprintf (buffer, "%-4d", (long)uValue);
			} else {
				sprintf (buffer, "%4d", (long)uValue);
			}

			break;
			
		case  FORM_41F:
			if (align&DT_ALIGN_LEFT) {
				sprintf (buffer, "%-4.1f", (FLOAT)uValue);
			} else {
				sprintf (buffer, "%4.1f", (FLOAT)uValue);
			}

			break;
			
		case  FORM_51F:
			if (align&DT_ALIGN_LEFT) {
				sprintf (buffer, "%-5.1f", (FLOAT)uValue);
			} else {
				sprintf (buffer, "%5.1f", (FLOAT)uValue);
			}
			break;
			
		case  FORM_52F:
			if (align&DT_ALIGN_LEFT) {
				sprintf (buffer, "%-5.2f", (FLOAT)uValue);
			} else {
				sprintf (buffer, "%5.2f", (FLOAT)uValue);
			}
			break;
			
		case  FORM_53F:
			if (align&DT_ALIGN_LEFT) {
				sprintf (buffer, "%-5.3f", (FLOAT)uValue);
			} else {
				sprintf (buffer, "%5.3f", (FLOAT)uValue);
			}
			break;
			
		case  FORM_72F:
			if (align&DT_ALIGN_LEFT) {
				sprintf (buffer, "%-7.2f", (FLOAT)uValue);
			} else {
				sprintf (buffer, "%7.2f", (FLOAT)uValue);
			}
			break;

		default :
			return (-1);
	}

	text = LoadString(((PCONTROL)hCtrl)->caption);
	strcpy(text, buffer);

	return  SendMessage( hCtrl, MSG_SETTEXT, 0, (LPARAM)(((PCONTROL)hCtrl)->caption) ) == 0;
}


BOOL GUIAPI SetDlgItemText (HWND hDlg, int nIDDlgItem, const char *lpString)
{
	HWND hCtrl;
	char *text;
	
	if (!(hCtrl = GetDlgItem (hDlg, nIDDlgItem)))
		return FALSE;

	text = LoadString( Control(hCtrl)->caption );
	strcpy(text, lpString);	
	return SendMessage (hCtrl, MSG_SETTEXT, 0, Control(hCtrl)->caption) == 0;
}

BOOL GUIAPI SetDlgItemTextEx(UINT16 dlg_idd, UINT16 dlg_idc, const char *str)
{
	HWND hDlg, hCtrl;
	char *text;

	if (!(hDlg = (HWND)GetMainWndMem(dlg_idd)))
		return FALSE;

	if (!(hCtrl = GetDlgItem (hDlg, dlg_idc)))
		return FALSE;

	text = LoadString(Control(hCtrl)->caption);
	strcpy(text, str);
	
	return SendMessage (hCtrl, MSG_SETTEXT, 0, Control(hCtrl)->caption) == 0;
}

BOOL GUIAPI DestroyMainWindowIndirect (HWND hMainWin)
{
	dlgDestroyAllControls (hMainWin);
	DestroyMainWindow (hMainWin);
	//ThrowAwayMessages (hMainWin);

	return TRUE;
}

BOOL GUIAPI DestroyDialogControl(HWND hDlg, INT32 ctrl_id)
{
	PMAINWIN pDlg = (PMAINWIN)hDlg;
	PCONTROL pCtrl = (PCONTROL)(pDlg->subWinList.first);
	PCONTROL pNext;

	while (!_Addresses_Equal(pCtrl, _Chain_Tail(&pDlg->subWinList))) {
		pNext = (PCONTROL)pCtrl->node.next;
		if (pCtrl->id == ctrl_id)
		{
			DestroyWindow ((HWND)pCtrl);
			return TRUE;
		}
		pCtrl = pNext;
	}
	return FALSE;
}


/**
 \note  目前系统软件不支持动态内存分配和销毁;所以,必须静态分配窗口内存;
		\a pNewCtrl,就是内存分配的起始地址; \ctrlNum, 就是分配控件的数量.
**/
HWND GUIAPI CreateMainWindowIndirectParam (PDLGTEMPLATE pDlgTemplate,HWND hOwner, INT16 id,
										   WNDPROC WndProc, LPARAM lParam, PWNDMEM pMem )
{
	MAINWINCREATE CreateInfo;
	HWND		  hMainWin;
	int		   i;
	PCTRLDATA	 pCtrlData;
	HWND		  hCtrl;
	HWND		  hFocus;
	PCONTROL	  pCtrl;
	
	HANDLE		hTsk;
	PMAINWIN	  pWin;
	PCONTROL	  pNewCtrl;
	
	if (!pDlgTemplate->controls || !pMem)
		return HWND_INVALID;

	if (!pMem->pMainWin || !pMem->pControl || !pMem->task) {
		return HWND_INVALID;
	}
	ASSERT_REPORT(pDlgTemplate->controlnr <= pMem->ctrlNum);

	hTsk	 = pMem->task;
	pWin	 = pMem->pMainWin;
	pNewCtrl = pMem->pControl;
	
	hOwner = GetMainWindowHandle (hOwner);

	CreateInfo.dwReserved	 = pDlgTemplate->dwAddData;
	CreateInfo.dwStyle		= pDlgTemplate->dwStyle & ~WS_VISIBLE;
	CreateInfo.dwExStyle	  = pDlgTemplate->dwExStyle;
	CreateInfo.caption		= pDlgTemplate->caption;
	CreateInfo.proc		   = WndProc ? WndProc : DefaultMainWinProc;
	CreateInfo.lx			 = pDlgTemplate->x;
	CreateInfo.ty			 = pDlgTemplate->y;
	CreateInfo.rx			 = pDlgTemplate->x + pDlgTemplate->w;
	CreateInfo.by			 = pDlgTemplate->y + pDlgTemplate->h;
	CreateInfo.id			 = id;
	CreateInfo.iBkColor	   = GetWindowElementColor (BKC_CONTROL_DEF);
	CreateInfo.textColor	  = GetWindowElementColor (FGC_CONTROL_DEF);
	CreateInfo.dwAddData	  = pDlgTemplate->dwAddData;
	
	hMainWin = CreateMainWindow (&CreateInfo, pWin, hTsk);
	if (hMainWin == HWND_INVALID)
		return HWND_INVALID;

	for (i = 0; i < pDlgTemplate->controlnr; i++) {
		pCtrlData = pDlgTemplate->controls + i;
		pCtrl	 = pNewCtrl + i;
		hCtrl = CreateWindowEx(pCtrlData->class_name,
							   pCtrlData->caption,
							   pCtrlData->dwStyle | WS_CHILD,
							   pCtrlData->dwExStyle,
							   pCtrlData->id,
							   pCtrlData->x,
							   pCtrlData->y,
							   pCtrlData->w,
							   pCtrlData->h,
							   hMainWin,
							   pCtrlData->dwAddData,
							   pCtrlData->dwAddData2,
							   pCtrl);
							  
		if (hCtrl == HWND_INVALID) {
			return HWND_INVALID;
		}
	}

	/*  找焦点控件，一般都是定义的第一个控件；	*/
	hFocus = GetNextDlgTabItem (hMainWin, (HWND)0, FALSE);
	if (SendMessage (hMainWin, MSG_INITDIALOG, (WPARAM)hFocus, (LPARAM)lParam)) 
	{
		dlgDestroyAllControls (hMainWin);
		DestroyMainWindow (hMainWin);
		if (hFocus)
			SetFocus (hFocus);
	}
	
	ShowWindow (hMainWin, SW_SHOWNORMAL);
	return hMainWin;
}

VOID  test_gui_task(VOID)
{
	extern UINT32  gui_data;
	extern UINT32 *gui_stkP;
	UINT32  data;
	
	data = *gui_stkP;
	if (data != gui_data)
		ASSERT_REPORT(data == gui_data);
}

INT32 GUIAPI DialogBoxIndirectParam (PDLGTEMPLATE pDlgTemplate, HWND hOwner,
	INT16 id, WNDPROC DlgProc, LPARAM lParam, PWNDMEM pMem)
{
	MAINWINCREATE CreateInfo;
	HWND		  hDlg;
	HWND		  hCtrl;
	long		  retCode = IDCANCEL;
	HWND		  hFocus;
	MSG		   msg;
	INT		   i;
	PCONTROL	  pCtrl;
	PCTRLDATA	 pCtrlData;
	HANDLE		htsk;

	INT16		 top_lev_dlg_wave_ndx; // 上级对话框覆盖的波形索引号
	INT16		 wave_ndx;			 // 本地对话框覆盖的波形索引号.
	INT16		 last_hide_dyn_trend_ndx, cur_hide_dyn_trend_ndx;
	INT16		 face_type = MonitorConfig.faceType;

	if (!pDlgTemplate->controls || !pMem)
		return  -1;

	top_lev_dlg_wave_ndx = LastHideWaveBlockNdx;
	
	if (pDlgTemplate->x && pDlgTemplate->y)
	{   // modified by gjl 2013-4-19 if set x and y, use it!
		wave_ndx = 0;
		CreateInfo.lx= pDlgTemplate->x;
		CreateInfo.ty= pDlgTemplate->y;
	}
	else
	{
		wave_ndx = GetDialogPos(pDlgTemplate, &CreateInfo.lx, &CreateInfo.ty);
	}
	LastHideWaveBlockNdx = wave_ndx;


	hOwner = GetMainWindowHandle (hOwner);

	CreateInfo.dwReserved	 = pDlgTemplate->dwAddData;
	pDlgTemplate->dwAddData   = (DWORD)(&retCode);

	CreateInfo.dwStyle		= pDlgTemplate->dwStyle & ~WS_VISIBLE;
	CreateInfo.dwExStyle	  = pDlgTemplate->dwExStyle;
	CreateInfo.caption		= pDlgTemplate->caption;
	CreateInfo.proc		   = DlgProc;
	CreateInfo.rx			 = CreateInfo.lx + pDlgTemplate->w;
	CreateInfo.by			 = CreateInfo.ty + pDlgTemplate->h;
	CreateInfo.id			 = id;
	CreateInfo.iBkColor	   = GetWindowElementColor (WEC_EXCOLOR_LAVENDER);
	CreateInfo.textColor	  = GetWindowElementColor (FGC_CONTROL_DEF);
	CreateInfo.dwAddData	  = (DWORD)pDlgTemplate;
	
	pMem->pMainWin->fblayer   = DIALOG_FB_LAYER; //add by empty 2011/01/14
	hDlg = CreateMainWindow (&CreateInfo, pMem->pMainWin, pMem->task);
	if (hDlg == HWND_INVALID)
		return  -1;

	for (i = 0; i < pDlgTemplate->controlnr; i++) 
	{
		pCtrlData = pDlgTemplate->controls + i;
		pCtrl	 = pMem->pControl + i;
		pCtrl->fblayer = DIALOG_FB_LAYER;
		hCtrl	 = CreateWindowEx(pCtrlData->class_name,
		pCtrlData->caption,
		pCtrlData->dwStyle | WS_CHILD,
		pCtrlData->dwExStyle,
		pCtrlData->id,
		pCtrlData->x,
		pCtrlData->y,
		pCtrlData->w,
		pCtrlData->h,
		hDlg,
		pCtrlData->dwAddData,
		pCtrlData->dwAddData2,
		pCtrl);
		if (hCtrl == HWND_INVALID)
			return  retCode;
		SetWindowBkColor(hCtrl, GetWindowElementColor (WEC_EXCOLOR_LAVENDER));
	}

	if (hOwner)
	{
		EnableWindow (hOwner, FALSE);
		ShowWindow (hOwner, SW_HIDE);
		myfb_close_window(hOwner);  
	}

	if (MonitorInfo.inFrozen)	// 进入菜单前，也退出冻结状态
		ExitFrozen();

	EnterDialogLayout(top_lev_dlg_wave_ndx, wave_ndx);
	myfb_open_window(hDlg);
	if (SendMessage (hDlg, MSG_INITDIALOG, (HWND)hFocus, lParam))
	{
		if (hFocus)
			SetFocus (hFocus);
	}

	hFocus = GetNextDlgTabItem (hDlg, (HWND)0, FALSE); //modified by empty 2011/04/13
	ShowWindow (hDlg, SW_SHOWNORMAL);
	if (hFocus)	 
		SetFocus (hFocus);

	htsk = GetMainWindow(hDlg)->task;
	while (GetMessage (&msg, htsk))
		DispatchMessage (&msg);

	dlgDestroyAllControls (hDlg);
	DestroyMainWindow (hDlg);
	myfb_close_window(hDlg);
	LastHideWaveBlockNdx = top_lev_dlg_wave_ndx;
	ExitDialogLayout(top_lev_dlg_wave_ndx, wave_ndx);	// 恢复可以显示的波形区.


	if (hOwner)
	{
		myfb_open_window(hOwner);	
		EnableWindow (hOwner, TRUE);
		ShowWindow (hOwner, SW_SHOWNORMAL);
	} 

	if (MonitorInfo.inFrozen)	// 退出菜单前，也退出冻结状态
		ExitFrozen();

	return  retCode;
}

BOOL GUIAPI EndDialog (HWND hDlg, long endCode)
{
	DWORD		dwAddData;
	PDLGTEMPLATE pDlgTmpl; 

	dwAddData = GetWindowAdditionalData (hDlg);

	if (dwAddData == 0)
		return FALSE;

	pDlgTmpl = (PDLGTEMPLATE)dwAddData;

	*((long *)(pDlgTmpl->dwAddData)) = endCode;

	PostQuitMessage (hDlg);

	return TRUE;
}

INT32 GUIAPI DefaultDialogProc (HWND hWnd, INT32 message, WPARAM wParam, LPARAM lParam)
{
	HWND hCurFocus;
	
	switch (message)
	{
		case MSG_CREATE:
			return 0;
						
		case MSG_COMMAND:
			if (wParam == IDCANCEL)
			{
				HWND hCancel;
				
				hCancel = GetDlgItem (hWnd, IDCANCEL);
				if (hCancel && IsWindowEnabled (hCancel) && IsWindowVisible (hCancel))
					EndDialog (hWnd, IDCANCEL);
			}
			break;
		
		case MSG_CLOSE:
			
			EndDialog (hWnd, IDCANCEL);//收到close消息,立刻结束对话框.
			return 0;
			
		default :
			break;
	}
	
	return  DefaultMainWinProc (hWnd, message, wParam, lParam);
}

#ifdef _CTRL_BUTTON
VOID GUIAPI CheckDlgButton (HWND hDlg, INT32 nIDDlgItem, INT32 nCheck)
{
	HWND hCtrl;
	long DlgCode;

	if (!(hCtrl = GetDlgItem (hDlg, nIDDlgItem)))
		return;

	DlgCode = SendMessage (hCtrl, MSG_GETDLGCODE, 0, 0);

	if (DlgCode & DLGC_BUTTON) {
		SendMessage (hCtrl, BM_SETCHECK, nCheck?BST_CHECKED:BST_UNCHECKED, 0);
	}
	else if (DlgCode & DLGC_3STATE) {
		SendMessage (hCtrl, BM_SETCHECK, nCheck, 0);
	}
}

VOID GUIAPI CheckRadioButton (HWND hDlg, INT32 idFirstButton, 
							  INT32 idLastButton, INT32 idCheckButton)
{
	HWND hCtrl;

	idFirstButton = idFirstButton;
	idLastButton  = idLastButton;
	
	if (!(hCtrl = GetDlgItem (hDlg, idCheckButton)))
		return;
		
	SendMessage (hCtrl, BM_SETCHECK, BST_CHECKED, 0);
}

INT32 GUIAPI IsDlgButtonChecked (HWND hDlg, INT32 idButton)
{
	HWND hCtrl;

	if (!(hCtrl = GetDlgItem (hDlg, idButton)))
		return -1;
	
	return SendMessage (hCtrl, BM_GETCHECK, 0, 0);
}

#ifdef _CTRL_STATIC

static INT32 MsgBoxProc (HWND hWnd, INT32 message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case MSG_INITDIALOG:
			break;

		case MSG_COMMAND:
		{
			switch (wParam)
			{
				case IDOK:
				case IDCANCEL:
				case IDABORT:
				case IDRETRY:
				case IDIGNORE:
				case IDYES:
				case IDNO:
					 if (GetDlgItem (hWnd, wParam))
						EndDialog (hWnd, wParam);
						
					break;
			}
			break;
		}	

		default:
			break;
	}

	return  DefaultDialogProc (hWnd, message, wParam, lParam);
}

//static  MAINWIN  Msgbox_Dlg;
//static  CONTROL  Msgbox_Ctrl[5];  /* 最多五个控件. */

/* message box 的常量 */
#define MB_MARGIN	10	  /* 空白边距		   */
#define MB_BUTTONW   80	  /* 按钮的宽度		 */
#define MB_TEXTSPACE 10	  /* 字符串的行距	   */
#define MB_BUTTONH   26	  /* 按钮的高度		 */
#define MB_TEXTW	 120	 /* 按钮的字串的长度   */

/* 计算MESSAGE BOX的大小尺寸; 注意, hParentWnd 不能为空; MB_BASEDONPARENT 必须有.
   否则, 坐标是以桌面为参考的.将会绘制到波形区之内.
*/
static void get_box_xy (HWND hParentWnd, DWORD dwStyle, DLGTEMPLATE* MsgBoxData)
{
	RECT rcTemp;

	if (dwStyle & MB_BASEDONPARENT)
		GetWindowRect (hParentWnd, &rcTemp);
	else
		rcTemp = g_rcScr;

	switch (dwStyle & MB_ALIGNMASK)
	{
		case MB_ALIGNCENTER:
			 MsgBoxData->x = rcTemp.left + (RECTW(rcTemp) - MsgBoxData->w) / 2;
			 MsgBoxData->y = rcTemp.top + (RECTH(rcTemp) - MsgBoxData->h) / 2;
			 break;

		case MB_ALIGNTOPLEFT:
			 MsgBoxData->x = rcTemp.left;
			 MsgBoxData->y = rcTemp.top;
			 break;

		case MB_ALIGNBTMLEFT:
			 MsgBoxData->x = rcTemp.left;
			 MsgBoxData->y = rcTemp.bottom - MsgBoxData->h;
			 break;

		case MB_ALIGNTOPRIGHT:
			 MsgBoxData->x = rcTemp.right - MsgBoxData->w;
			 MsgBoxData->y = rcTemp.top;
			 break;

		case MB_ALIGNBTMRIGHT:
			 MsgBoxData->x = rcTemp.right - MsgBoxData->w;
			 MsgBoxData->y = rcTemp.bottom - MsgBoxData->h;
			 break;
	}
}

static BUTTONDATA  Mb_BtnData[5];


/**
   \note 消息对话框不要单独出现; 必须有父窗口.因为系统中所有对话框有一个规定的
		 区域显示; 如果没有父窗口,消息对话框将以桌面为参考,画到波形区上面.
		 暂时不支持图标.
**/
long GUIAPI MessageBox (HWND hParentWnd,  STRINGID text1, STRINGID text2,
						STRINGID caption, DWORD dwStyle, HANDLE tsk)
{
	DLGTEMPLATE MsgBoxData =
	{
	/*					dwStyle,					   dwExStyle,   */
	WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG,	 0,
	/* x, y, w, h, caption, controlnr, controls, dwAddData */
	   0, 0, 0, 0,	 0,	   0,	   NULL,	  0L,
	};

	CTRLDATA CtrlData[5] = 
	{
	/* class_name */
	{   "button", 
	/* dwStyle,											 dwExStyle,  */
	BS_PUSHBUTTON | WS_TABSTOP | WS_VISIBLE | WS_GROUP, WS_EX_NONE,
	/*  x, y, w, h, id, caption, dwAddData, dwAddData2 */
	0, 0, 0, 0, 0,  0,	   0L,		0L},

	/* class_name */
	{   "button", 
	/* dwStyle,								  dwExStyle,  */
	BS_PUSHBUTTON | WS_TABSTOP | WS_VISIBLE, 0,
	/*  x, y, w, h, id, caption, dwAddData, dwAddData2 */
	0, 0, 0, 0, 0,  0,	   0L,		0L},

	/* class_name */
	{   "button",
	/* dwStyle,								  dwExStyle,  */
	BS_PUSHBUTTON | WS_TABSTOP | WS_VISIBLE, 0,
	/*  x, y, w, h, id, caption, dwAddData, dwAddData2 */
	0, 0, 0, 0, 0,  0,	   0L,		0L}
	};

	int	  i, nButtons, buttonx, buttony;
	RECT	 rcText, rcButtons, rcIcon;
	int	  width, height;
	SIZE	 text1_size = {0, 0};
	SIZE	 text2_size = {0, 0};
	int	  max;
	WNDMEM   wndMem;

	ZeroMemory(&Mb_BtnData[0], sizeof(Mb_BtnData));

	if (caption)
		MsgBoxData.caption  = caption;
	else
		MsgBoxData.caption  = STR_MSGBOX_COMPANY; 

	switch (dwStyle & MB_TYPEMASK)
	{
		case MB_OK:
			 MsgBoxData.controlnr	= 1;
			 CtrlData [0].caption	= STR_MSGBOX_OK;
			 CtrlData [0].id		 = IDOK;
			 CtrlData [0].dwAddData2 = (UINT32)&Mb_BtnData[0];
			 break;

		case MB_OKCANCEL:
			 MsgBoxData.controlnr	= 2;
			 CtrlData [1].caption	= STR_MSGBOX_OK;
			 CtrlData [1].id		 = IDOK;
			 CtrlData [1].dwAddData2 = (UINT32)&Mb_BtnData[0];
			 CtrlData [0].caption	= (dwStyle & MB_CANCELASBACK) ? 
				STR_MSGBOX_PREVIOUS : STR_MSGBOX_CANCEL;
			 CtrlData [0].id		 = IDCANCEL;
			 CtrlData [0].dwAddData2 = (UINT32)&Mb_BtnData[1];
			 break;

		case MB_YESNO:
			 MsgBoxData.controlnr	= 2;
			 CtrlData [1].caption	= STR_MSGBOX_CONFIRM_YES;
			 CtrlData [1].id		 = IDYES;
			 CtrlData [1].dwAddData2 = (UINT32)&Mb_BtnData[0];
			 CtrlData [0].caption	= STR_MSGBOX_CONFIRM_NO;
			 CtrlData [0].id		 = IDNO;
			 CtrlData [0].dwAddData2 = (UINT32)&Mb_BtnData[1];
			 break;

		case MB_RETRYCANCEL:
			 MsgBoxData.controlnr	= 2;
			 CtrlData [1].caption	= STR_MSGBOX_RETRY;
			 CtrlData [1].id		 = IDRETRY;
			 CtrlData [1].dwAddData2 = (UINT32)&Mb_BtnData[0];
			 CtrlData [0].caption	= (dwStyle & MB_CANCELASBACK) ? 
				STR_MSGBOX_PREVIOUS : STR_MSGBOX_CANCEL;
			 CtrlData [0].id		 = IDCANCEL;
			 CtrlData [0].dwAddData2 = (UINT32)&Mb_BtnData[1];
			 break;

		case MB_ABORTRETRYIGNORE:
			 MsgBoxData.controlnr	= 3;
			 CtrlData [0].caption	= STR_MSGBOX_ABORT;
			 CtrlData [0].id		 = IDABORT;
			 CtrlData [0].dwAddData2 = (UINT32)&Mb_BtnData[0];
			 CtrlData [1].caption	= STR_MSGBOX_RETRY;
			 CtrlData [1].id		 = IDRETRY;
			 CtrlData [1].dwAddData2 = (UINT32)&Mb_BtnData[1];
			 CtrlData [2].caption	= STR_MSGBOX_IGNORE;
			 CtrlData [2].id		 = IDIGNORE;
			 CtrlData [2].dwAddData2 = (UINT32)&Mb_BtnData[2];
			 break;

		case MB_YESNOCANCEL:
			 MsgBoxData.controlnr = 3;
			 CtrlData [1].caption = STR_MSGBOX_CONFIRM_YES;
			 CtrlData [1].id	  = IDYES;
			 CtrlData [1].dwAddData2 = (UINT32)&Mb_BtnData[0];
			 CtrlData [2].caption = STR_MSGBOX_CONFIRM_NO;
			 CtrlData [2].id	  = IDNO;
			 CtrlData [2].dwAddData2 = (UINT32)&Mb_BtnData[1];
			 CtrlData [0].caption = (dwStyle & MB_CANCELASBACK) ?
				 STR_MSGBOX_PREVIOUS : STR_MSGBOX_CANCEL;
			 CtrlData [0].id	  = IDCANCEL;
			 CtrlData [0].dwAddData2 = (UINT32)&Mb_BtnData[2];
			 break;
	}
	
	nButtons		 = MsgBoxData.controlnr;
	rcButtons.left   = 0;
	rcButtons.top	= 0;
	rcButtons.bottom = MB_BUTTONH;
	rcButtons.right  = MsgBoxData.controlnr * MB_BUTTONW
		+ (MsgBoxData.controlnr - 1) * (MB_MARGIN << 1);

	rcIcon.left   = 0;
	rcIcon.top	= 0;
	rcIcon.right  = 0;
	rcIcon.bottom = 0;
	if (text1)
	{
	
		

		GetTextExtentEx(GetSystemFont(SYSLOGFONT_SMAFONT), 
		LoadString(text1), -1, &text1_size);
	}

	if (text2)
	{
			
		GetTextExtentEx(GetSystemFont(SYSLOGFONT_SMAFONT), 
		LoadString(text2), -1, &text2_size);
	}
	//计算文本所占的空间
	rcText.left   = 0;
	rcText.top	= 0;
	rcText.right  = rcButtons.right + (MB_MARGIN << 1);
	rcText.right  = MAX(rcText.right, MB_TEXTW);//取默认文本区与button区的大者.
	max		   = MAX(text1_size.cx, text2_size.cx);// 文本的长度的大者.
	rcText.right  = MAX(rcText.right, max); // 最终的长度
	rcText.bottom = GetSystemFont(SYSLOGFONT_SMAFONT)->size;
	if (text2)
		rcText.bottom = rcText.bottom + MB_TEXTSPACE; //有第二个文本需要加行距.

	i					  = MsgBoxData.controlnr;
	CtrlData [i].class_name= "static";
	CtrlData [i].dwStyle   = WS_VISIBLE | SS_SIMPLE | WS_GROUP;
	CtrlData [i].x		 = RECTW (rcIcon) + (MB_MARGIN << 1) 
		+ (RECTW(rcText) - text1_size.cx) / 2;
	CtrlData [i].y		 = MB_MARGIN;
	CtrlData [i].w		 = text1_size.cx + 1;
	CtrlData [i].h		 = text1_size.cy + 1;
	CtrlData [i].id		= IDC_TEXT1;
	CtrlData [i].caption   = text1;
	CtrlData [i].dwAddData = 0;
	MsgBoxData.controlnr++;

	if (text2)
	{
		i					  = MsgBoxData.controlnr;
		CtrlData [i].class_name= "static";
		CtrlData [i].dwStyle   = WS_VISIBLE | SS_SIMPLE | WS_GROUP;
		CtrlData [i].x		 = RECTW (rcIcon) + (MB_MARGIN << 1)
			+ (RECTW(rcText) - text2_size.cx) / 2;
		CtrlData [i].y		 = MB_MARGIN + text2_size.cy + MB_TEXTSPACE;
		CtrlData [i].w		 = text2_size.cx + 1;
		CtrlData [i].h		 = text2_size.cy + 1;
		CtrlData [i].id		= IDC_TEXT2;
		CtrlData [i].caption   = text2;
		CtrlData [i].dwAddData = 0;
		MsgBoxData.controlnr++;
	}

	width = MAX (RECTW (rcText), RECTW (rcButtons)) + RECTW (rcIcon)
		+ (MB_MARGIN << 2) + (GetMainWinMetrics(MWM_BORDER) << 1);
	height = MAX (RECTH (rcText), RECTH (rcIcon)) 
		+ RECTH (rcButtons) + MB_TEXTSPACE + (MB_TEXTSPACE << 1)
		+ 10 + (GetMainWinMetrics (MWM_BORDER) << 1)  // 文本和button行距再加10
		+ GetMainWinMetrics (MWM_CAPTIONY);
	if (text2)
		height += MB_TEXTSPACE;

	buttonx = (width - RECTW (rcButtons)) >> 1;

	// 文本和button行距再加10
	buttony = MAX (RECTH (rcIcon), RECTH (rcText)) + (MB_MARGIN << 1) + 10;
	if (text2)
		buttony += MB_TEXTSPACE;

	for (i = 0; i < nButtons; i++)
	{
		CtrlData[i].x = buttonx + i * (MB_BUTTONW + MB_MARGIN);
		CtrlData[i].y = buttony;
		CtrlData[i].w = MB_BUTTONW;
		CtrlData[i].h = MB_BUTTONH;
	}

	MsgBoxData.w = width;
	MsgBoxData.h = height;
	get_box_xy (hParentWnd, dwStyle, &MsgBoxData);

	MsgBoxData.controls = CtrlData;

	wndMem.pMainWin = GetMainWndMem(IDMB);
	wndMem.pControl = GetCtrlWndMem(IDOK);
	wndMem.ctrlNum  = MsgBoxData.controlnr;
	wndMem.task	 = tsk;

	return  DialogBoxIndirectParam (&MsgBoxData, hParentWnd, IDMB, MsgBoxProc,  
		(LPARAM)dwStyle, &wndMem);
}

#endif /* _CTRL_STATIC */

#endif


#ifdef  _DIALOG_DEBUG
MAINWIN   MsgBox;
CONTROL   MsgBoxCtrl[4];

INT32 MsgBoxProc (HWND hWnd, INT32 message, WPARAM wParam, LPARAM lParam)
{

}


void  test_dialog(void)
{
	DLGTEMPLATE MsgBoxData	=  {
	/*  dwStyle,		dwExStyle, x, y, w, h, caption, controlnr, controls, dwAddData */
		WS_ABSSCRPOS | WS_CAPTION | WS_BORDER, WS_EX_NONE, 0, 0, 200, 200, 0, 0, 0, 0L
	};
	CTRLDATA	 CtrlData [3] =  {
	/* class_name, dwStyle, dwExStyle, x, y, w, h, id, caption, dwAddData, dwAddData2 */
		{   "button", 
			BS_PUSHBUTTON | WS_TABSTOP | WS_VISIBLE | WS_GROUP, WS_EX_NONE,
			0, 0, 0, 0, 0, 0, 0, 0L},
		{   "button", 
			BS_PUSHBUTTON | WS_TABSTOP | WS_VISIBLE, WS_EX_NONE,
			0, 0, 0, 0, 0, 0, 0, 0L},
		{   "button",
			BS_PUSHBUTTON | WS_TABSTOP | WS_VISIBLE, WS_EX_NONE,
			0, 0, 0, 0, 0, 0, 0, 0L}
	};

	MsgBoxData.caption   = STR_SWITCH_OFF;
	MsgBoxData.controlnr = 3;
	MsgBoxData.controls  = CtrlData;
	MsgBoxData.dwAddData = 0;


	CreateMainWindowIndirectParam(&MsgBoxData, 0, MsgBoxProc, 0, SysGui_HTSK, MsgBox, 
								  MsgBoxCtrl, 4 );
	
}

#endif

#if _ENB_PASSWORD_DIALOG > 0
static INT32 sCurr_Password;

INT32 PasswdProc (HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	switch (message)
	{
		case MSG_INITDIALOG:
			{
				INT32 i;
				HWND hCtrl;
				for (i = IDC_PASSWD_FIRST; i <= IDC_PASSWD_CANCEL_B; i++)
				{
					if (hCtrl = GetDlgItem(hWnd, i))
						SetWindowBkColor(hCtrl, ((PCONTROL)hWnd)->iBkColor);
				}
			}
			break;

		case MSG_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDC_PASSWD_WORD_SB:
					if (HIWORD(wParam) == SBN_ENTER) 
					{
						INT32 value;
						value = GetSpinBoxIntCurValue(
										IDD_PASSWORD, IDC_PASSWD_WORD_SB);
						SelectKeyboardType(0,
										LoadString(STR_DLG_PASSWD_CAPTION), 
										LoadString(((PWIN)hWnd)->caption));
						UseKeyboard(hWnd, IDC_PASSWD_WORD_SB, (LPARAM)&value);
						SetSpinBoxIntCurValue(IDD_PASSWORD,
										IDC_PASSWD_WORD_SB, (INT16)value);
						HWND hCtrl = GetDlgItem(hWnd, IDC_PASSWD_TIPS_L);
						SetWindowText(hCtrl, 0);
					}
					return 0;

				case IDC_PASSWD_OK_B:
					{
						if (sCurr_Password == GetSpinBoxIntCurValue(
										IDD_PASSWORD, IDC_PASSWD_WORD_SB))
						{
							sCurr_Password = IDOK;
							EndDialog(hWnd, IDOK);
						}
						else
						{
							HWND hCtrl = GetDlgItem(hWnd, IDC_PASSWD_TIPS_L);
							SetWindowTextColor(hCtrl, COLOR_red);
							SetWindowText(hCtrl, STR_DLG_PASSWD_ERROR);
						}
					}
					return 0;

				case IDC_PASSWD_CANCEL_B:
					{
						sCurr_Password = IDCANCEL;
						EndDialog(hWnd, IDOK);
					}
					return 0;
			}
			break;

		default:
			break;
	}
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}

long GUIAPI PasswordDialog(HANDLE hOwner, INT32 owner, INT32 tipsID)
{
	SIZE  size;
	UCHAR *tips;
	SPINBOXDATA sb_pw = 
		{ FORM_4D, SBTXT_NUM, 0, 0, 0, 0, 0, 9999, 0, 1, 0, 0 , 0, 0};

	BUTTONDATA  btn_ok	  = {0};
	BUTTONDATA  btn_cancle  = {0};

	if (tipsID <= STR_NULL)
	{
		tipsID  = STR_NULL;
	}
	
	tips = LoadString(tipsID);
	if (strlen(tips) > 0)
	{
		GetTextExtentEx(GetSystemFont(SYSLOGFONT_SMAFONT), tips, -1, &size);
	}
	else
	{
		memset(&size, 0, sizeof(size));
	}

	sCurr_Password = IDCANCEL;
	switch (owner)
	{
		case 0:
			return TRUE;

		case 1:
			sCurr_Password = DEMO_PASSWORD;
			break;

		case 2:
			sCurr_Password = USER_PASSWORD;
			break;

		case 3:
			sCurr_Password = FACTORY_PASSWORD;
			break;

		case 4:
			sCurr_Password = ANALYSIS_PASSWORD;
			break;

		default:
			return FALSE;
	}

	DLGTEMPLATE DialogData =
	{
		WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG,	 0,
		0, 0, 160, 170,	 0,	   0,	   NULL,	  0L,
	};
	CTRLDATA ctrl_data[4]={
		{   CTRL_STATIC,	WS_VISIBLE, WS_NONE,
			15 , 15 , 130, 20 , IDC_PASSWD_TIPS_L,  0, 0L, 0L },

		{   CTRL_SPINBOX,   WS_VISIBLE | WS_TABSTOP, WS_NONE,
			15 , 45 , 130, 30 , IDC_PASSWD_WORD_SB, 0, 0L, 0L },

		{   CTRL_BUTTON,	WS_VISIBLE | WS_TABSTOP, WS_NONE,
			15 , 80 , 60 , 30 , IDC_PASSWD_OK_B,	STR_DLG_PASSWD_OK, 0L, 0L },

		{   CTRL_BUTTON,	WS_VISIBLE | WS_TABSTOP, WS_NONE,
			85 , 80 , 60 , 30 , IDC_PASSWD_CANCEL_B,STR_DLG_PASSWD_CANCEL, 0L, 0L }
	};

	DialogData.caption = STR_DLG_PASSWD_CAPTION + owner;
	
	INT16 offset = 0;
	
	if (size.cx > ctrl_data[0].w)
	{
		offset = (size.cy + 2) * (size.cx + ctrl_data[0].w - 1) / ctrl_data[0].w
				+ 2; // SS_LEFTNOWORDWRAP 起始 y 坐标是 2, 行距是 2
		ctrl_data[0].dwStyle |= SS_LEFTNOWORDWRAP;
	}
	else
	{
		ctrl_data[0].dwStyle |= SS_CENTER;
	}
	
	ctrl_data[0].h += offset;
	ctrl_data[1].y += offset;
	ctrl_data[1].dwAddData2 = (DWORD)&sb_pw;
	ctrl_data[2].y += offset;
	ctrl_data[2].dwAddData2 = (DWORD)&btn_ok;
	ctrl_data[3].y += offset;
	ctrl_data[3].dwAddData2 = (DWORD)&btn_cancle;
	DialogData.h   += offset;

	WNDMEM   wndMem;
	
	wndMem.pMainWin = GetMainWndMem(IDD_PASSWORD);
	wndMem.pControl = GetCtrlWndMem(IDC_PASSWD_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;
	
	DialogData.controlnr = 4;
	DialogData.controls  = ctrl_data;
	DialogBoxIndirectParam(&DialogData, hOwner, IDD_PASSWORD, PasswdProc, 0, &wndMem);
	return (sCurr_Password == IDOK);
}
#endif


