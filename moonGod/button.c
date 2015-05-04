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

#define   BUTTON_GLOBALS 
#include  "includes.h"

// 内部定义的图形元素的常量, 单位, 象素.
#define BTN_WIDTH_BORDER	1			  //内部的边框厚度
#define BTN_WIDTH_BMP	   10			 //内部图标的宽度
#define BTN_HEIGHT_BMP	  10			 //内部图标的高度
#define BTN_INTER_BMPTEXT   4			  //内部图标和文本的间距

BUTTONDATA  gBtn_Exit  = {IDI_EXIT, 0, 0, 0 };

/* 用于显示checkbox类型的button, 这是checked状态下的图标. */// 8x8
static UINT8  ButtonHook_Data[] = {   
	0x00,
	_______X,
	______XX,
	XX___XX_,
	XXX_XX__,
	_XXXX___,
	__XX____,
	0x00,
};
static BITMAP ButtonHook_Bmp = {
   0, 1, 8, 8, 1, (void *)ButtonHook_Data
};

/**
 **  说明:  显示对号;
 **  不会重绘背景；前景色可以在代码中改变；但是还不能由调用者改变。
 **/
VOID   ShowHook (HDC hdc, INT32 x, INT32 y)
{
	INT16 i, j;
	UINT8 data;
	for (i = 0; i < 8; i++) 
	{
		data = ButtonHook_Data[i];
		for (j = 0; j < 8; j++) 
		{
			if (data & 0x80) 
			{
				PutPixel(hdc, x + j, y + i, BLACK );
			}
			data <<= 1;
		}
	}
	return;
}

/**
   确定文本,bmp,和客户区的大小.
**/
static void btnGetRects (HWND hWnd, DWORD dwStyle,
									RECT* prcClient, 
									RECT* prcText, 
									RECT* prcBitmap)
{
	GetClientRect (hWnd, prcClient);
	prcClient->right --;
	prcClient->bottom --;

	SetRect (prcText, (prcClient->left   + BTN_WIDTH_BORDER),
					  (prcClient->top	+ BTN_WIDTH_BORDER),
					  (prcClient->right  - BTN_WIDTH_BORDER),
					  (prcClient->bottom - BTN_WIDTH_BORDER));

	SetRectEmpty (prcBitmap);

	if (((dwStyle & BS_TYPEMASK) < BS_CHECKBOX)
		 || (dwStyle & BS_PUSHLIKE))
		return; //如果是pushbutton, 或者是pushlik类型的check but或radio but,无须图标

	if (dwStyle & BS_LEFTTEXT) {
		SetRect (prcText, prcClient->left + 1,
						  prcClient->top + 1,
						  prcClient->right - BTN_WIDTH_BMP - BTN_INTER_BMPTEXT,
						  prcClient->bottom - 1);
		SetRect (prcBitmap, prcClient->right - BTN_WIDTH_BMP,
							prcClient->top + 1,
							prcClient->right - 1,
							prcClient->bottom - 1);
	}
	else {
		SetRect (prcText, prcClient->left + BTN_WIDTH_BMP + BTN_INTER_BMPTEXT,
						  prcClient->top + 1,
						  prcClient->right - 1,
						  prcClient->bottom - 1);
		SetRect (prcBitmap, prcClient->left + 1,
							prcClient->top + 1,
							prcClient->left + BTN_WIDTH_BMP,
							prcClient->bottom - 1);
	}

}

/**
   通知其它同组的ckeck或radio button, 它们的状态都被设置成了UNCHECKED状态,并重绘.
**/
static int btnUncheckOthers (PCONTROL pCtrl)
{
	PCONTROL pGroupLeader = pCtrl;
	PCONTROL pOthers;
	DWORD	dwType = pCtrl->dwStyle & BS_TYPEMASK;
	PMAINWIN pParent;
	CHAIN_CONTROL *pWinList;
	
	pParent = (PMAINWIN)GetParent((HWND)pCtrl);
	pWinList = &pParent->subWinList;
	while (!_Addresses_Equal(pGroupLeader, _Chain_Head(pWinList))) {
		if (pGroupLeader->dwStyle & WS_GROUP)
			break;

		pGroupLeader = (PCONTROL)pGroupLeader->node.previous;
	}

	pOthers = pGroupLeader;
	while (!_Addresses_Equal(pOthers, _Chain_Tail(pWinList))) {
		if ((pOthers->dwStyle & BS_TYPEMASK) != dwType)
			break;

		if (!_Addresses_Equal(pOthers,pCtrl) 
			&& (BUTTON_STATUS (pOthers) | BST_CHECKED)) {
			BUTTON_STATUS (pOthers) &= ~BST_CHECKED;
			InvalidateRect ((HWND)pOthers, NULL, FALSE);
		}

		pOthers = (PCONTROL)pOthers->node.next;
	}

	return pCtrl->id;
}

static void btnPaintFrame (PCONTROL pCtrl, HDC hdc, BOOL mark_flag,
						   DWORD dwStyle, RECT *prcClient)
{
	dwStyle = dwStyle;
	pCtrl   = pCtrl;
	
	if (mark_flag) {
		// 画选中框, 焦点状态.
		SetPenColor(hdc, GetWindowElementColor(BKC_CONTROL_FOCUS));
		Rect(hdc, prcClient->left, prcClient->top, prcClient->right,
			 prcClient->bottom);
		Rect(hdc, prcClient->left + 1, prcClient->top + 1, prcClient->right - 1,
			 prcClient->bottom - 1);
		Rect3D(hdc, prcClient->left + 2 , prcClient->top + 2, prcClient->right - 2,
			   prcClient->bottom - 2, PIXEL_white, PIXEL_black);
		Rect3D(hdc, prcClient->left + 1, prcClient->top + 1, prcClient->right - 1,
			   prcClient->bottom - 1, PIXEL_white, PIXEL_black);
	} else {
		// 恢复, 正常情况
		SetPenColor(hdc, PIXEL_black);
		Rect(hdc, prcClient->left, prcClient->top, prcClient->right,
		prcClient->bottom);
		SetPenColor(hdc, GetWindowElementColor(BKC_DLG));
		Rect(hdc, prcClient->left + 1, prcClient->top + 1, prcClient->right - 1,
			prcClient->bottom - 1);
	}
}

static void btnPaintIcon (PCONTROL pCtrl, HDC hdc, DWORD dwStyle, RECT *prcBmp)
{
	RECT  rc;
	BOOL  marked  = (BUTTON_STATUS(pCtrl) & BST_MARKED) == BST_MARKED;
	GAL_PIXEL oldBKcolor,oldBrushcolor; 
	INT32 y;
	rc = *prcBmp;
	y = (RECTH(rc) - 14) / 2;
	switch (dwStyle & BS_TYPEMASK) {
		case BS_AUTORADIOBUTTON:
		case BS_RADIOBUTTON:
			if (BUTTON_STATUS(pCtrl) & BST_CHECKED) {
				PutImage(hdc, rc.left + 1, rc.top + 1, &ButtonHook_Bmp);
			} 
			break;

		case BS_3STATE:
		case BS_AUTO3STATE:
		case BS_AUTOCHECKBOX:
		case BS_CHECKBOX:

		if (BUTTON_STATUS(pCtrl) & BST_CHECKED) 
		{
				if (! marked)
					SetPenColor(hdc, PIXEL_black);
				else
					SetPenColor(hdc, PIXEL_blue);

				if (dwStyle & WS_DISABLED)
					SetPenColor(hdc, PIXEL_lightgray);  
				
				//Rect(hdc, rc.left + 2, rc.top + 2, rc.left + 16, rc.top + 16);		  
				//Rect(hdc, rc.left + 3, rc.top + 3, rc.left + 15, rc.top + 15);
				Rect(hdc, rc.left+1, rc.top+y, rc.left+15, rc.top+y+15);
				Rect(hdc, rc.left+2, rc.top+y+1, rc.left+14, rc.top+y+14);
				
				oldBKcolor = SetBkColor(hdc, pCtrl->iBkColor);
				if (dwStyle & WS_DISABLED)
					oldBrushcolor = SetBrushColor(hdc, COLOR_lightgray);
				else
				  oldBrushcolor = SetBrushColor(hdc, PIXEL_black);
				PutImage(hdc, rc.left + 4, rc.top + y + 4, &ButtonHook_Bmp);
				SetBkColor(hdc, oldBKcolor);
				SetBrushColor(hdc, oldBrushcolor);
			}
			else
			{
				if (! marked)
					SetPenColor(hdc, PIXEL_black);
				else
					SetPenColor(hdc, PIXEL_blue);

				if (dwStyle & WS_DISABLED)
					SetPenColor(hdc, PIXEL_lightgray);

				Rect(hdc, rc.left+1, rc.top+y, rc.left+15, rc.top+y+15);
				Rect(hdc, rc.left+2, rc.top+y+1, rc.left+14, rc.top+y+14);
				//Rect(hdc, rc.left + 2, rc.top + 2, rc.left + 16, rc.top + 16);	 //modified by empty 2011/02/22			
				//Rect(hdc, rc.left + 3, rc.top + 3, rc.left + 15, rc.top + 15);   //modified by empty 2011/02/22

			}
			break;

		default:
			break;
	}
}

static void btnPaintNormalButton (PCONTROL pCtrl, HDC hdc, DWORD dwStyle,RECT* prcClient, RECT* prcText, RECT* prcBitmap)
{
	RECT  client_rc;
	int   i, x, y;
	SIZE  size;
	PDC   pdc;
	
	ShowHelpString(pCtrl, BUTTON_HELPID(pCtrl), 0);
	if (dwStyle & BS_BITMAP)
	{
		BUTTONDATAP pBtnData = (BUTTONDATAP)(pCtrl->dwAddData2);
		if (!pBtnData)
			return;
		PBUTTONBMP pBtnBmp = (PBUTTONBMP)pBtnData->data;
		if (!pBtnBmp)
			return;
		UCHAR * bitmap = pBtnBmp->release;
		if (bitmap)
		   {	 
			   int x = prcClient->left;
			   int y = prcClient->top;
			 // 一般而言，位图会覆盖整个客户区
			// 这里没有做什么处理，所以需要用户保证位图的大小
			   Put24Bitmap(hdc, x, y, 0,  bitmap);
		  }
		  return;
	}	
	if(dwStyle & BS_ICON)
	{
		if (!pCtrl->dwAddData2)
			return;
		
		ICONID hIcon = ((BUTTONDATAP)(pCtrl->dwAddData2))->data;
		
		if ((int)hIcon >= 0)
		{
			//SetBkColor(hdc, GetWindowElementColor(FGC_CAPTION_NORMAL));
			//SetBrushColor(hdc, GetWindowElementColor(BKC_CAPTION_NORMAL));
			SetBkColor(hdc, pCtrl->iBkColor);
			SetBrushColor(hdc, pCtrl->textColor);
			DrawIcon (hdc, 0, 0, hIcon); //DrawIcon (hdc, 0, 0, 0, 0, hIcon);
		}
		return;
	}

	pdc	   = dc_HDC2PDC(hdc);
	client_rc = *prcClient;
	pdc->pLogFont = GetSystemFont(SYSLOGFONT_SMAFONT);
	SetBrushColor(hdc, pCtrl->iBkColor);
	FillRect(hdc, client_rc.left, client_rc.top, RECTW(client_rc), RECTH(client_rc));
	if ((dwStyle & BS_CHECKBOX) == 0)
		btnPaintFrame(pCtrl, hdc, FALSE, dwStyle, prcClient);
	TestWinStrLen(strlen(LoadString(pCtrl->caption)), pCtrl->caption);
	
	// 居中处理
	GetTextExtent(hdc, LoadString(pCtrl->caption), -1, &size);
	x = prcText->left + (RECTW((*prcText)) - size.cx) / 2;
	y = prcText->top  + (RECTH((*prcText)) - size.cy) / 2;
	switch (dwStyle & BS_TYPEMASK)
	{
		case BS_PUSHBUTTON:
			if (dwStyle & WS_DISABLED)
			{
				SetTextColor(hdc, PIXEL_darkgray);
				SetBkColor(hdc, pCtrl->iBkColor);
				TextOut(hdc,x, y, LoadString(pCtrl->caption));
			}
			else
			{
				SetTextColor(hdc, pCtrl->textColor);
				SetBkColor(hdc, pCtrl->iBkColor);
				TextOut(hdc, x, y, LoadString(pCtrl->caption));
			}
			break;

		case BS_AUTORADIOBUTTON:// for  radiobox,  draw icon and text;
		case BS_RADIOBUTTON:
		case BS_3STATE:		 // for  checkbox,  draw icon and text
		case BS_AUTO3STATE:
		case BS_AUTOCHECKBOX:
		case BS_CHECKBOX:
			if (dwStyle & WS_DISABLED) 
			{
				btnPaintIcon(pCtrl, hdc, dwStyle, prcBitmap);
				SetTextColor(hdc, pCtrl->iBkColor);
				SetBkColor(hdc, pCtrl->iBkColor);
				TextOut(hdc, x, y, LoadString(pCtrl->caption));
			} 
			else 
			{
				btnPaintIcon(pCtrl, hdc, dwStyle, prcBitmap);
				SetTextColor(hdc, pCtrl->textColor);
				SetBkColor(hdc, pCtrl->iBkColor);
				TextOut(hdc, x, y, LoadString(pCtrl->caption));
			}
			break;

		
		default:
			break;			
	}

}

 static void btnPaintFocusButton (PCONTROL pCtrl, HDC hdc, DWORD dwStyle, RECT* prcClient, RECT* prcText, RECT* prcBitmap)
{
	SIZE	size;
	int		x,	y;
	ShowHelpString(pCtrl, BUTTON_HELPID(pCtrl), BUTTON_HELPSTR(pCtrl));
	if (dwStyle & BS_BITMAP)
	{
		BUTTONDATAP pBtnData = (BUTTONDATAP)(pCtrl->dwAddData2);
		if (!pBtnData)
			return;
		PBUTTONBMP pBtnBmp = (PBUTTONBMP)pBtnData->data;
		if (!pBtnBmp)
			return;
		UCHAR * bitmap = pBtnBmp->pass;
		if (bitmap)
		   {	 
			   int x = prcClient->left;
			   int y = prcClient->top;
			 // 一般而言，位图会覆盖整个客户区
			// 这里没有做什么处理，所以需要用户保证位图的大小
			   Put24Bitmap(hdc, x, y, 0,  bitmap);
		  }
		  return;
	}	
	if(dwStyle & BS_ICON)
	{
		if (!pCtrl->dwAddData2)
			return;
		
		ICONID hIcon = ((BUTTONDATAP)(pCtrl->dwAddData2))->data;
		
		if ((int)hIcon >= 0)
		{
			//SetBkColor(hdc, GetWindowElementColor(FGC_CAPTION_NORMAL));
			SetBkColor(hdc, pCtrl->iBkColor);
			SetBrushColor(hdc, GetWindowElementColor(WEC_CONTROL_FOCUSFRAME));
			DrawIcon (hdc, 0, 0, hIcon); //DrawIcon (hdc, 0, 0, 0, 0, hIcon);
		}
		return;
	}
	
	PDC pdc;
	GAL_PIXEL color = GetWindowElementColor(WEC_CONTROL_FOCUSFRAME);//(WEC_EXCOLOR_LAVENDER);

	pdc		  = dc_HDC2PDC(hdc);
	prcText   = prcText;
	prcBitmap = prcBitmap;

	pdc->pLogFont = GetSystemFont(SYSLOGFONT_BIGFONT);
	SetBrushColor(hdc, color);
	FillRect(hdc, prcClient->left, prcClient->top,
				RECTW((*prcClient)), RECTH((*prcClient)));

	if ((dwStyle & BS_CHECKBOX) == 0)
		btnPaintFrame(pCtrl, hdc, TRUE, dwStyle, prcClient);
	TestWinStrLen(strlen(LoadString(pCtrl->caption)), pCtrl->caption);

	GetTextExtent(hdc, LoadString(pCtrl->caption), -1, &size);//居中处理
	x = prcText->left + (RECTW((*prcText)) - size.cx) / 2;
	y = prcText->top  + (RECTH((*prcText)) - size.cy) / 2;

	switch ( dwStyle & BS_TYPEMASK ) 
	{
		case BS_PUSHBUTTON:// for pushbutton, only draw textout;
			if (dwStyle & WS_DISABLED) 
			{
				SetTextColor(hdc, pCtrl->iBkColor);
				SetBkColor(hdc, color);
				TextOut(hdc,x, y, LoadString(pCtrl->caption));
			} 
			else
			{
				/**
				if (LOBYTE(pCtrl->textColor) > 0xE0
					&& HIBYTE(pCtrl->textColor)  > 0xE0
					&& LOBYTE(HIWORD(pCtrl->textColor)) > 0xE0)
				{
					SetTextColor(hdc, pCtrl->textColor ^ color);
				}
				else
				{
					SetTextColor(hdc, pCtrl->textColor);
				}
				**/
				SetTextColor(hdc, PIXEL_white);
				SetBkColor(hdc, color);
				TextOut(hdc, x, y, LoadString(pCtrl->caption));
			}
			break;

		case BS_AUTORADIOBUTTON:// for  radiobox,  draw icon and text;
		case BS_RADIOBUTTON:
		case BS_3STATE:		 // for  checkbox,  draw icon and text
		case BS_AUTO3STATE:
		case BS_AUTOCHECKBOX:
		case BS_CHECKBOX:
			if (dwStyle & WS_DISABLED) 
			{
				btnPaintIcon(pCtrl, hdc, dwStyle, prcBitmap);
				SetTextColor(hdc, color);
				SetBkColor(hdc, color);
				TextOut(hdc, x, y, LoadString(pCtrl->caption));
			}
			else
			{
				btnPaintIcon(pCtrl, hdc, dwStyle, prcBitmap);
				SetTextColor(hdc, pCtrl->textColor);
				SetBkColor(hdc, color);
				TextOut(hdc, x, y, LoadString(pCtrl->caption));
			}
			break;

		default:
			break;
	}   

}


static void btnPaintInProcessButton (PCONTROL pCtrl, HDC hdc, DWORD dwStyle, 
									 RECT* prcClient, RECT* prcText, RECT* prcBitmap)
{
	prcText = prcText;
	
	if (dwStyle & WS_DISABLED)  
		goto exit;

	switch (dwStyle & BS_TYPEMASK) {
		case BS_3STATE:
		case BS_AUTO3STATE:
		case BS_AUTOCHECKBOX:
		case BS_CHECKBOX:
			if (dwStyle & BS_PUSHLIKE) {
				if (BUTTON_STATUS(pCtrl) & BST_CHECKED) {
					// 按钮显示为凹的
					Rect3D(hdc, prcClient->left, prcClient->top, prcClient->right,
						   prcClient->bottom, PIXEL_black, PIXEL_white);
					Rect3D(hdc, prcClient->left + 1, prcClient->top + 1, prcClient->right - 1,
						   prcClient->bottom - 1, PIXEL_black, PIXEL_white);
				}
				else {
					// 按钮显示为凸的
					Rect3D(hdc, prcClient->left, prcClient->top, prcClient->right,
						   prcClient->bottom, PIXEL_white, PIXEL_black);

				}

				return ; // 不用把GEN_PRESSED标志清除.
			} else {
				btnPaintIcon(pCtrl, hdc, dwStyle, prcBitmap);
			}
			break;

		case BS_PUSHBUTTON:
			if (dwStyle & BS_PUSHLIKE) {
				// 按钮显示为凹的
				Rect3D(hdc, prcClient->left + 2, prcClient->top + 2, prcClient->right - 2,
					   prcClient->bottom - 2, PIXEL_black, PIXEL_white);
				Rect3D(hdc, prcClient->left + 1, prcClient->top + 1, prcClient->right - 1,
					   prcClient->bottom - 1, PIXEL_black, PIXEL_white);
				return;
			}
			break;

		case BS_AUTORADIOBUTTON:
		case BS_RADIOBUTTON:
			btnPaintIcon(pCtrl, hdc, dwStyle, prcBitmap);
			break;// for  radiobox,  draw icon and text;
			
		default:
			break;
	}

exit:
	BUTTON_STATUS(pCtrl) &= ~GEN_PRESSED;//一般情况下不在pressed状态下停留,直接退出InProcess状态.
}


static void btnPaint(PCONTROL pCtrl, DWORD dwStyle)
{
	HDC		  hdc;
	RECT		 client_rc;
	RECT		 text_rc;
	RECT		 bmp_rc;
	BOOL		 marked;
	BOOL		 pressed;

	marked  = (BUTTON_STATUS(pCtrl) & BST_MARKED)   == BST_MARKED;
	pressed = (BUTTON_STATUS(pCtrl) & GEN_PRESSED)  == GEN_PRESSED;
	hdc	 = GetClientDC((HWND)pCtrl);

	btnGetRects((HWND)pCtrl, dwStyle, &client_rc, &text_rc, &bmp_rc);

	if (!pressed && !marked) {	// 正常显示; 没有成为焦点.
		btnPaintNormalButton(pCtrl, hdc, dwStyle, &client_rc, &text_rc, &bmp_rc );
	}
	else if (marked && !pressed) { // 焦点显示; 标记;
		btnPaintFocusButton(pCtrl, hdc, dwStyle, &client_rc, &text_rc, &bmp_rc);
	} 
	else if (marked && pressed) {  // 按键按下进入处理; 左右旋钮可以改变数据项.
		btnPaintInProcessButton(pCtrl, hdc, dwStyle, &client_rc, &text_rc, &bmp_rc);
	}

	ReleaseDC(hdc);
}


static long ButtonCtrlProc (HWND hWnd, long message, WPARAM wParam, LPARAM lParam)
{
	HDC		 hdc;
	PCONTROL	pCtrl;
	DWORD	   dwStyle;
	RECT		rcClient;
	RECT		rcText;
	RECT		rcBitmap;
	
	pCtrl   = Control(hWnd);
	dwStyle = pCtrl->dwStyle;
	
	switch (message) {
		case MSG_CREATE:
			return 0;
			
		case BM_CLICK:
			{
				DWORD dwState;
				BOOL  enb_notify;

				enb_notify = TRUE;

				switch (pCtrl->dwStyle & BS_TYPEMASK) {
					case BS_PUSHBUTTON:
						if ((pCtrl->dwStyle & BS_PUSHLIKE)
							 && (BUTTON_STATUS (pCtrl) & GEN_PRESSED))
							enb_notify= FALSE;//第一次按下,不通知主窗口;
							
						break;
					
					case BS_AUTORADIOBUTTON:
						if (!(BUTTON_STATUS (pCtrl) & BST_CHECKED)) {
							SendMessage (hWnd, BM_SETCHECK, BST_CHECKED, 0);
						}
						break;
						
					case BS_AUTOCHECKBOX:
						if (BUTTON_STATUS (pCtrl) & BST_CHECKED)
							dwState = BST_UNCHECKED;
						else
							dwState = BST_CHECKED;

						SendMessage (hWnd, BM_SETCHECK, (WPARAM)dwState, 0);
						break;
						
					case BS_AUTO3STATE:
						dwState = (BUTTON_STATUS (pCtrl) & 0x00000003L);
						dwState = BST_INDETERMINATE - dwState;
						SendMessage (hWnd, BM_SETCHECK, (WPARAM)dwState, 0);
						break;
		
					default:
						break;
				}
					
				InvalidateRect (hWnd, NULL, FALSE);
				if (enb_notify)
					NotifyParent (hWnd, pCtrl->id, BN_CLICKED);
				return 0;
			}			
		
		case MSG_KEYENCODER:
			if (wParam == KEY_KNOB_PRESSED) { //只要是点击, 就通知主窗口.
				if  (BUTTON_STATUS (pCtrl) & GEN_PRESSED) {
					BUTTON_STATUS (pCtrl) &= ~GEN_PRESSED;
				} else {
					BUTTON_STATUS (pCtrl) |= GEN_PRESSED;
				}
				SendMessage(hWnd, BM_CLICK, 0, 0);
			} else if (BUTTON_STATUS (pCtrl) & GEN_PRESSED) {
				if (wParam == KEY_KNOB_ROTATE_LEFT)
					NotifyParent(hWnd, pCtrl->id, BN_ANTICLOCK_ACT);

				if (wParam == KEY_KNOB_ROTATE_RIGHT)
					NotifyParent(hWnd, pCtrl->id, BN_CLOCK_ACT);
			}
			return 0;

#if _ENB_TOUCH
		case MSG_TOUCHENCODER:
			if (lParam)
				SendMessage(hWnd, MSG_SETFOCUS, wParam, lParam);
			else
				SendMessage(hWnd, BM_CLICK, wParam, lParam);
			return;
#endif
			
		case BM_GETCHECK:
			switch (dwStyle & BS_TYPEMASK) {
				case BS_AUTOCHECKBOX:
				case BS_AUTORADIOBUTTON:
				case BS_CHECKBOX:
				case BS_RADIOBUTTON:
					return (BUTTON_STATUS (pCtrl) & BST_CHECKED);
				
				case BS_3STATE:
				case BS_AUTO3STATE:
					if (BUTTON_STATUS (pCtrl) & BST_INDETERMINATE)
						return (BST_INDETERMINATE);
					return (BUTTON_STATUS (pCtrl) & BST_CHECKED);
				
				default:
					return 0;
			}
			
		case BM_GETSTATE:
			return (long)(BUTTON_STATUS (pCtrl));
			
		case BM_GETIMAGE:
			if ((wParam == BM_IMAGE_BITMAP) && (dwStyle & BS_BITMAP))
				return (long)(BUTTON_DATA (pCtrl));
				
			if ((wParam == BM_IMAGE_ICON) && (dwStyle & BS_ICON))
				return (long)(BUTTON_DATA (pCtrl));
			break;
		
		case BM_SETIMAGE:
			if (((wParam == BM_IMAGE_BITMAP) && (dwStyle & BS_BITMAP))
				 || ((wParam == BM_IMAGE_ICON) && (dwStyle & BS_ICON))) {
				 long oldImage = (long)BUTTON_DATA (pCtrl);
				 BUTTON_DATA (pCtrl) = (DWORD)lParam;
				 InvalidateRect (hWnd, NULL, TRUE);
				 return oldImage;
			}
			break;
		
		case MSG_SETTEXT:
			{
				pCtrl->caption = (STRINGID)lParam;
				InvalidateRect (hWnd, NULL, TRUE);
				return 0;
			}
			
		case BM_SETCHECK:
			{
				DWORD dwOldState = BUTTON_STATUS (pCtrl);

				switch (dwStyle & BS_TYPEMASK) {
					case BS_CHECKBOX:
					case BS_AUTOCHECKBOX:
						if (wParam & BST_CHECKED)
						{
							BUTTON_STATUS(pCtrl) |= BST_CHECKED;
												}
						else
						{
							BUTTON_STATUS(pCtrl) &= ~BST_CHECKED;
												}
						break;
				
					case BS_AUTORADIOBUTTON:
					case BS_RADIOBUTTON:
						if (((BUTTON_STATUS(pCtrl) & BST_CHECKED) == 0)
							 && (wParam & BST_CHECKED)) {
							BUTTON_STATUS(pCtrl) |= BST_CHECKED;
							
							btnUncheckOthers (pCtrl);
						}
						else if ((BUTTON_STATUS(pCtrl) & BST_CHECKED)
								  && (!(wParam & BST_CHECKED))) {
							BUTTON_STATUS(pCtrl) &= ~BST_CHECKED;
						}
						break;
				
					case BS_3STATE:
					case BS_AUTO3STATE:
						switch (wParam) { 
							case BST_INDETERMINATE:
							case BST_CHECKED:
							case BST_UNCHECKED:
								BUTTON_STATUS(pCtrl) &= 0xFFFFFFFC;
								BUTTON_STATUS(pCtrl) += (wParam & 0x00000003);
						}
						break;
				}
					
				if (dwOldState != BUTTON_STATUS(pCtrl))
					InvalidateRect (hWnd, NULL, TRUE);
					
				return 0;
			}
			
		case BM_SETSTATE:
			{
				DWORD dwOldState = BUTTON_STATUS(pCtrl) & BST_PUSHED;
				
				if (wParam)
					BUTTON_STATUS(pCtrl) |= BST_PUSHED;
				else
					BUTTON_STATUS(pCtrl) &= ~BST_PUSHED;
				
				if (dwOldState != (BUTTON_STATUS(pCtrl) & BST_PUSHED))
					InvalidateRect (hWnd, NULL, TRUE);
			}
			return 0;

		case BM_SETSTYLE:
			pCtrl->dwStyle &= 0xFFFF0000;  //高16位是属于窗口管理器的.全局的.
			pCtrl->dwStyle |= (DWORD)(wParam & 0x0000FFFF);//低16位是控件私有的.
			if (LOWORD (lParam))
				InvalidateRect (hWnd, NULL, TRUE);
			return 0;
			
		case MSG_GETDLGCODE:
			switch (dwStyle & BS_TYPEMASK) {
				case BS_CHECKBOX:
				case BS_AUTOCHECKBOX:
					return DLGC_WANTCHARS | DLGC_BUTTON;
				
				case BS_RADIOBUTTON:
				case BS_AUTORADIOBUTTON:
					return DLGC_RADIOBUTTON | DLGC_BUTTON;
				
				case BS_DEFPUSHBUTTON:
					return DLGC_DEFPUSHBUTTON;
				
				case BS_PUSHBUTTON:
					return DLGC_PUSHBUTTON;
				
				case BS_3STATE:
				case BS_AUTO3STATE:
					return DLGC_3STATE;

				default:
					return 0;
			}
			
		case MSG_KILLFOCUS:
			{
			   if (BUTTON_STATUS(pCtrl) & BST_CHECKED)   //add by empty 2011/02/18
							  BUTTON_STATUS(pCtrl) = BST_CHECKED;
					   else
				  BUTTON_STATUS(pCtrl) = 0;
				InvalidateRect(hWnd, 0, TRUE);
				
				if (dwStyle & BS_NOTIFY)
					NotifyParent (hWnd, pCtrl->id, BN_KILLFOCUS);
			}
			return 0;

		case MSG_SETFOCUS:
			{
				BUTTON_STATUS(pCtrl) |= BST_FOCUS;
				BUTTON_STATUS(pCtrl) |= BST_MARKED;
				InvalidateRect(hWnd, 0, TRUE);
				if (((dwStyle & BS_TYPEMASK) == BS_RADIOBUTTON)
					|| ((dwStyle & BS_TYPEMASK) == BS_AUTORADIOBUTTON))
					NotifyParent (hWnd, pCtrl->id, BN_SETFOCUS);
			}
			return 0;
			
		case MSG_PAINT:
		
			btnPaint(pCtrl, dwStyle);
			return 0;
			
		case MSG_ERASEBKGND:
			if ((dwStyle & BS_TYPEMASK) != BS_OWNERDRAW)
				return 0;
			break;
			
		case MSG_ENABLE:
			if (wParam && (dwStyle & WS_DISABLED)){
				pCtrl->dwStyle &= ~WS_DISABLED;
			}
			else if (!wParam && !(dwStyle & WS_DISABLED)){
				pCtrl->dwStyle |= WS_DISABLED;
			}
			else {
				return 0;
			}
			InvalidateRect (hWnd, NULL, TRUE);
			return 0;
		
		default :
			break;
	}
	
	return DefaultDialogProc(hWnd, message, wParam, lParam);
}

BOOL RegisterButtonControl (VOID)
{
	WNDCLASS WndClass;

	WndClass.spClassName = "button";
	WndClass.dwStyle	 = WS_NONE;
	WndClass.dwExStyle   = WS_EX_NONE;
	WndClass.iBkColor	= GetWindowElementColor (BKC_DLG); // change by gjl
	WndClass.textColor   = GetWindowElementColor (FGC_CONTROL_DEF);
	WndClass.proc		= ButtonCtrlProc;

	return AddNewControlClass (&WndClass) == ERR_OK;
}


INT16  GetButtonStatus(UINT16 parent_id, UINT16 ctrl_id, UINT32 * pStatus)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_BUTTON) == 0) {
		*pStatus = BUTTON_STATUS(pCtrl);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}


