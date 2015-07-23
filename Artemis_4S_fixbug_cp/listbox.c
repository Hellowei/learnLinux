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

#define   LISTBOX_GLOBALS 
#include  "includes.h"

#define  LISTBOX_BMP_W		14   // '增多减小'的图形的宽度
#define  LISTBOX_TEXT_INDENT   5   // 内部文本缩进的象素点.
#define  LISTBOX_INNER_BORDER  3   // 内部边框的宽度.
#define  LISTBOX_ROW_H		20   // 下拉框一行的高度.

// ListDropBuff; 窗口不会在系统中交叠,同时只显示一个焦点控件. 所以用一个buffer即可.
static RECT  RcListboxDropSave; // 被listbox控件遮住的矩形.

static  void  GetListboxRect (PCONTROL pctrl, RECT *pClient, RECT *pText, 
							  RECT *pTextClient, RECT *pBmp, HDC hdc)
{
	long		 font_height;
	int		  top;

	GetClientRect((HWND)pctrl, pClient);

	font_height = GetFontHeight(hdc);

	*pBmp  = *pClient;
	*pText = *pClient;

	pBmp->left   = pClient->right - LISTBOX_BMP_W + 1;
	pText->right = pClient->right - LISTBOX_BMP_W;
	*pTextClient = *pText;
	
	// 文本Y坐标居中对齐.
	top = pClient->top + (pClient->bottom - pClient->top - font_height) / 2;
	pText->top = top;
	pText->left += LISTBOX_TEXT_INDENT; // 缩进
}

static  void  PaintListboxFrame (HDC hdc, BOOL mark_flag, RECT *clientRc, RECT *bmpRc)
{
	 if (mark_flag) { //焦点状态
		 SetPenColor(hdc, GetWindowElementColor(BKC_CONTROL_FOCUS));
		 Rect(hdc, clientRc->left - 2, clientRc->top - 2, clientRc->right + 2,
			  clientRc->bottom + 2);
		 Rect(hdc, clientRc->left - 1, clientRc->top - 1, clientRc->right + 1,
			  clientRc->bottom + 1);
		 Rect3D(hdc, clientRc->left, clientRc->top, clientRc->right,
				clientRc->bottom, PIXEL_black, PIXEL_white);
		 Rect3D(hdc, bmpRc->left, bmpRc->top + 1,
				bmpRc->right - 1, bmpRc->bottom - 1,
				PIXEL_white, PIXEL_black );
	 }
	 else  { // 正常状态		 
		 SetPenColor(hdc, PIXEL_black);
		 Rect(hdc, clientRc->left, clientRc->top, clientRc->right + 1, 
			  clientRc->bottom + 1);
	 }
}


//绘制表示列表的下拉图形//绘制表示'增多减小'的图形.
static  void  PaintListboxBmp (PCONTROL pctrl, RECT * BmpRc, HDC hdc)
{
	int  mid;
	RECT rc;
	int  i;
	
	rc = *BmpRc;

	//SetPenColor(hdc, PIXEL_white);
	//Rect(hdc, rc.left, rc.top, rc.right, rc.bottom);
	
	if (pctrl->dwStyle & LBS_DROPDOWN) {
		mid = rc.top + RECTH(rc) / 2;
		SetPenColor(hdc, PIXEL_black);
		for (i = 0; i < 4; i++) {
			Line(hdc, rc.right - 10 + i, mid - 2 - i, rc.right - 4 - i, mid - 2 - i); 
		}
	}
	else {
		mid = rc.top + RECTH(rc)/2;
		SetPenColor(hdc, PIXEL_black);
		Line(hdc, rc.left, mid, rc.right -1, mid);

		for ( i = 0; i < 4; i ++ ) {
			//Line(hdc, rc.right - 10 + i, mid - 2 - i, rc.right - 4 - i, mid - 2 - i); 
			Line(hdc, rc.right - 10 + i, mid + 2 + i, rc.right - 4 - i, mid + 2 + i); 
		}
	}
}

/**
	 listbox demonstration:  示例图.
	 
	 ++++++++++++++++++++++++++++++++++
	 +   +++++++++			+	   +
	 +   + text  +  textclient+  icon +  client rect;客户区矩形;里面包含了文本区和
	 +   +++++++++			+	   +  图标区.图标是绘制'下拉'的图形区.宽17pixel.
	 ++++++++++++++++++++++++++++++++++  由于文本需要缩进5个象素(x方向); 上下居中对
	 +						+  icon +  齐.所以,又分为文本区和文本客户区.其中文本
	 +						+  down +  客户区包含'文本区'.
	 +						+++++++++
	 +	 dropdown		   +	   +
	 +						+	   +
	 +////////////////////////+///////+
	 +/// current item	 ///+//   //+
	 +////////////////////////+///////+  dropdown rect; 下来矩形根据需要显示的项数
	 +						+ scroll+  以及可以显示的项数来决定.下拉区包括一个滚
	 +						+	   +  动条区.它的颜色和下拉区其它部分不同.
	 +						+	   +
	 +						+	   +
	 +						+	   +
	 +						+	   +
	 +						+	   +
	 +						+++++++++
	 +						+  up   +
	 +						+  icon +
	 ++++++++++++++++++++++++++++++++++
	 

**/
static void  PaintListboxDropdown (PCONTROL pctrl, RECT *clientRc, 
								   RECT *textClientRc,RECT *textRc, HDC hdc)
{
	char		*text;
	int		  item_num;
	int		  top,bottom;
	RECT		 saveRc;
	RECT		 dropRc;
	int		  i, no;
	int		  unit;
	static char  flag = FALSE;
	
	ReleaseDC(hdc);
	
	HWND hWnd = (HWND)pctrl->pParent;
	hdc = GetClientDC(hWnd);
	PDC pdc = dc_HDC2PDC(hdc);

	if (LISTBOX_STATUS(pctrl) & LBST_1CLICK)
	{
		// 计算下拉框中显示的项数
		item_num = (LISTBOX_ITEMNUM(pctrl) <= LISTBOX_DISPNUM(pctrl))  
				   ? LISTBOX_ITEMNUM(pctrl) : LISTBOX_DISPNUM(pctrl);

		// 计算下拉框底边的纵坐标
		bottom = clientRc->bottom + item_num * LISTBOX_ROW_H + 1;
		{
			// 第一次进入, 保存被遮住的部分.
			saveRc.left   = clientRc->left;
			saveRc.top	= clientRc->bottom + 1;
			saveRc.right  = clientRc->right;
			saveRc.bottom = bottom;
			dropRc = saveRc;  // 被覆盖的矩形区就是下拉框矩形.
			SetBrushColor(hdc, GetWindowElementColor(WEC_CONTROL_FOCUSFRAME));
			FillRect(hdc, saveRc.left, saveRc.top, RECTW(saveRc), RECTH(saveRc));
			
			SetPenColor(hdc, PIXEL_black);
			Rect(hdc, saveRc.left, saveRc.top, saveRc.right, saveRc.bottom);

			// 必须转换成屏幕坐标才能保存
			ClientToScreen((HWND)pctrl, &saveRc.left, &saveRc.top);
			ClientToScreen((HWND)pctrl, &saveRc.right, &saveRc.bottom);
			RcListboxDropSave = saveRc;
			SetBrushColor(hdc, GetWindowElementColor(BKC_DLG));
			FillRect(hdc, dropRc.left + 1, dropRc.top + 1, 
					 dropRc.right - dropRc.left - 2, 
					 dropRc.bottom - dropRc.top - 2);
			getimage(saveRc.left, saveRc.top, saveRc.right, saveRc.bottom, 
					 ListboxDropBuff);
			// 反色显示当前的选择项
			SetBrushColor(hdc, GetWindowElementColor(WEC_CONTROL_FOCUSFRAME));
			FillRect(hdc, textRc->left + 1, textRc->top + 1, 
					 textRc->right - textRc->left - 2, 
					 textRc->bottom - textRc->top - 2);

			SetTextColor(hdc, PIXEL_white);
			SetBkColor(hdc, GetWindowElementColor(WEC_CONTROL_FOCUSFRAME));
			text = LoadString(LISTBOX_INFO(pctrl)[LISTBOX_CURRITEM(pctrl)]);;
			TextOut(hdc, textRc->left, textRc->top, text);	  
			// 计算下拉框中最上一项和最下一项的序号
			if (LISTBOX_ITEMNUM(pctrl) <= LISTBOX_DISPNUM(pctrl)) {
				LISTBOX_TOPNDX(pctrl) = 0;
				LISTBOX_BOTNDX(pctrl) = LISTBOX_ITEMNUM(pctrl) - 1;
			}
			else  {
				if ((LISTBOX_CURRITEM(pctrl) < LISTBOX_DISPNUM(pctrl))
					 && (LISTBOX_CURRITEM(pctrl) >= 0)) {
					LISTBOX_TOPNDX(pctrl) = 0;
					LISTBOX_BOTNDX(pctrl) = LISTBOX_DISPNUM(pctrl) - 1;
				}
				else if ((LISTBOX_CURRITEM(pctrl) > LISTBOX_ITEMNUM(pctrl) - LISTBOX_DISPNUM(pctrl))
					&& (LISTBOX_CURRITEM(pctrl) < LISTBOX_ITEMNUM(pctrl))) {
					LISTBOX_TOPNDX(pctrl) = LISTBOX_ITEMNUM(pctrl) - LISTBOX_DISPNUM(pctrl);
					LISTBOX_BOTNDX(pctrl) = LISTBOX_ITEMNUM(pctrl) - 1;
				}
				else {
					LISTBOX_TOPNDX(pctrl) = LISTBOX_CURRITEM(pctrl) - LISTBOX_DISPNUM(pctrl) / 2;
					LISTBOX_BOTNDX(pctrl) = LISTBOX_TOPNDX(pctrl) + LISTBOX_DISPNUM(pctrl) - 1;
				}
			}

			// 显示下拉列表框的内容
			for (i = LISTBOX_TOPNDX(pctrl); i <= LISTBOX_BOTNDX(pctrl); i++) {
				no = i - LISTBOX_TOPNDX(pctrl);

				if (i == LISTBOX_CURRITEM(pctrl)) {
					// 点亮当前的选择项
					SetBrushColor(hdc, GetWindowElementColor(WEC_CONTROL_FOCUSFRAME));
					FillRect(hdc, dropRc.left + 1,
							 dropRc.top + no * LISTBOX_ROW_H, dropRc.right - 1,
							 dropRc.top + ( no + 1 ) * LISTBOX_ROW_H);

					SetTextColor(hdc, PIXEL_white);
					SetBkColor(hdc, GetWindowElementColor(WEC_CONTROL_FOCUSFRAME));
					text = LoadString(LISTBOX_INFO(pctrl)[i]);
					TextOut(hdc, textRc->left, textRc->top + LISTBOX_ROW_H * no, text);
				}
				else {
					SetTextColor(hdc, pctrl->textColor);
					SetBkColor(hdc, GetWindowElementColor(WEC_CONTROL_FOCUSFRAME));
					text = LoadString(LISTBOX_INFO(pctrl)[i]);
					TextOut(hdc, textRc->left, textRc->top + LISTBOX_ROW_H * no, text);
				}
			}

			// 显示滚动条
			if (LISTBOX_ITEMNUM(pctrl) > LISTBOX_DISPNUM(pctrl)) {
				SetBrushColor(hdc, GetWindowElementColor(BKC_DLG));
				FillRect(hdc, dropRc.right - LISTBOX_BMP_W, dropRc.top , 
						 dropRc.right - 1, dropRc.bottom - 1);
				SetPenColor(hdc, PIXEL_black);
				Line(hdc, dropRc.right - LISTBOX_BMP_W, dropRc.top , 
					 dropRc.right - LISTBOX_BMP_W, dropRc.bottom - 1);

				// 显示下拉框的上、下按钮
				Rect3D( hdc, dropRc.right - LISTBOX_BMP_W + 1, dropRc.top, 
						dropRc.right - 1, dropRc.top + LISTBOX_BMP_W - 1, 
						PIXEL_white, PIXEL_black );
				Rect3D(hdc, dropRc.right - LISTBOX_BMP_W + 1, 
					   dropRc.bottom - LISTBOX_BMP_W, 
					   dropRc.right - 1, dropRc.bottom - 1,
					   PIXEL_white, PIXEL_black);
				
				SetPenColor(hdc, PIXEL_black);
				for (i = 0; i < 4; i++) {
					Line(hdc, dropRc.right - 10 + i, dropRc.top + 8 - i,
						 dropRc.right - 4 - i,  dropRc.top + 8 - i);
					Line(hdc, dropRc.right - 10 + i, dropRc.bottom - 9 + i,
						 dropRc.right - 4 - i,
						 dropRc.bottom - 9 + i );
				}

				// 在滚动条区域反色显示当前项.
				unit = ( bottom - dropRc.top - LISTBOX_ROW_H * 2 + 1 ) 
					   / LISTBOX_ITEMNUM(pctrl);
				top  = dropRc.top + LISTBOX_BMP_W + unit * LISTBOX_TOPNDX(pctrl);
				if (LISTBOX_BOTNDX(pctrl) == LISTBOX_ITEMNUM(pctrl) - 1)
					bottom = bottom - LISTBOX_BMP_W - 1;
				else
					bottom = top + unit * LISTBOX_DISPNUM(pctrl);

				SetBrushColor(hdc, GetWindowElementColor(WEC_CONTROL_FOCUSFRAME));
				FillRect(hdc, dropRc.right - LISTBOX_BMP_W + 1, top, 
						 dropRc.right - 1, bottom );
				Rect3D(hdc, dropRc.right - LISTBOX_BMP_W + 1, top, 
					   dropRc.right - 1, bottom,
					   PIXEL_white, PIXEL_black);
			}
		}
	}

	if (LISTBOX_STATUS(pctrl) & LBST_2CLICK) {
		// 恢复被遮住的部分.
		putimage(RcListboxDropSave.left, RcListboxDropSave.top, ListboxDropBuff, 0);
		// 改变当前选择项
		SetBrushColor( hdc, pctrl->iBkColor);
		FillRect(hdc, textClientRc->left - 1, textClientRc->top - 1,
				 textClientRc->right - textClientRc->left - 2, 
				 textClientRc->bottom - textClientRc->top - 2);

		SetTextColor(hdc, pctrl->textColor);
		SetBkColor(hdc, pctrl->iBkColor);
		text = LoadString(LISTBOX_INFO(pctrl)[LISTBOX_CURRITEM(pctrl)]);;
		TextOut(hdc, textRc->left, textRc->top, text);
	}
	ReleaseDC(hdc);
	hdc = GetClientDC((HWND)pctrl);
}

/**
   绘制处于焦点状态的listbox; 不用再绘制icon了.
**/
static  void  PaintFocusListbox (PCONTROL pctrl, HDC hdc )
{
	RECT		 client_rc;
	RECT		 text_rc;
	RECT		 textClient_rc;
	RECT		 bmp_rc;
	char		*text;
	ShowHelpString(pctrl, LISTBOX_HELPID(pctrl), LISTBOX_HELPSTR(pctrl));
	PDC pdc = dc_HDC2PDC(hdc);
	pdc->pLogFont = GetSystemFont(SYSLOGFONT_BIGFONT);

	//panhonghui
//    if (MonitorConfig.language == RUSSIAN)
//    {
//         pdc->pLogFont = GetSystemFont(SYSLOGFONT_NOR_RUS);	
//    }
//    else
//    {
//        pdc->pLogFont = GetSystemFont(SYSLOGFONT_FIXED);

//    }

	GetListboxRect(pctrl, &client_rc, &text_rc, &textClient_rc, &bmp_rc, hdc);

	PaintListboxBmp(pctrl, &bmp_rc, hdc);
	
	SetBrushColor(hdc, GetWindowElementColor(WEC_CONTROL_FOCUSFRAME));
	FillRect(hdc, textClient_rc.left + 1, textClient_rc.top + 1,
			 RECTW(textClient_rc) - 2, RECTH(textClient_rc) - 1);

	PaintListboxFrame(hdc, TRUE, &client_rc, &bmp_rc);
	
	if (-1 == LISTBOX_CURRITEM(pctrl)) {
		return; // LISTBOX_CURRITEM(pctrl) = 0;
	}
	SetBkColor(hdc, GetWindowElementColor(WEC_CONTROL_FOCUSFRAME));
	SetTextColor(hdc, PIXEL_white);
	text = LoadString(LISTBOX_INFO(pctrl)[LISTBOX_CURRITEM(pctrl)]);;
	TextOut(hdc, text_rc.left, text_rc.top, text);
}

/**
   用户有按键动作以后的显示.
**/
static  void  PaintListboxInProcess (PCONTROL pctrl, HDC hdc)
{
	RECT		 client_rc;
	RECT		 text_rc;
	RECT		 textClient_rc;
	RECT		 bmp_rc;
	char		 text[20];
	
	if (LISTBOX_CURRITEM(pctrl) > LISTBOX_ITEMNUM(pctrl)) {
		LISTBOX_STATUS(pctrl) &= ~GEN_PRESSED;
		return;
	}
	
	PDC pdc = dc_HDC2PDC(hdc);
	pdc->pLogFont = GetSystemFont(SYSLOGFONT_SMAFONT);
	
	GetListboxRect(pctrl, &client_rc, &text_rc, &textClient_rc, &bmp_rc, hdc);
	PaintListboxFrame(hdc, TRUE, &client_rc, &bmp_rc);
	PaintListboxBmp(pctrl, &bmp_rc, hdc);
	if (-1 == LISTBOX_CURRITEM(pctrl)) {
		LISTBOX_CURRITEM(pctrl) = 0;
	}

	if (pctrl->dwStyle & LBS_DROPDOWN) {
		PaintListboxDropdown(pctrl, &client_rc, &textClient_rc, &text_rc, hdc);
	} else {
		SetBrushColor(hdc, pctrl->iBkColor);
		FillRect(hdc, textClient_rc.left + 1, textClient_rc.top + 1, 
				 RECTW(textClient_rc) - 2, RECTH(textClient_rc) - 2);

		SetBkColor(hdc, pctrl->iBkColor);
		SetTextColor(hdc, pctrl->textColor);
		strcpy(text, LoadString(LISTBOX_INFO(pctrl)[LISTBOX_CURRITEM(pctrl)]));
		TextOut(hdc, text_rc.left, text_rc.top, text);
	}
}

/**
   没有成为焦点,也没有用户动作.正常显示.
**/
static  void  PaintNormalListbox (PCONTROL pctrl, HDC hdc)
{
	RECT		 client_rc;
	RECT		 text_rc;
	RECT		 textClient_rc;
	RECT		 bmp_rc;
	char		 text[20];

	ShowHelpString(pctrl, LISTBOX_HELPID(pctrl), 0);
	PDC pdc = dc_HDC2PDC(hdc);
	pdc->pLogFont = GetSystemFont(SYSLOGFONT_SMAFONT);
//    if (MonitorConfig.language == RUSSIAN)
//    {
//         pdc->pLogFont = GetSystemFont(SYSLOGFONT_DEF_RUS);	
//    }
//    else
//    {
//        pdc->pLogFont = GetSystemFont(SYSLOGFONT_WCHAR_DEF);

//    }

	GetListboxRect(pctrl, &client_rc, &text_rc, &textClient_rc, &bmp_rc, hdc);

	//需要留出bmp区吗?
	//SetBrushColor(hdc, pctrl->iBkColor);
	SetBrushColor(hdc, GetWindowElementColor(WEC_EXCOLOR_WHITESMOKE));
	FillRect(hdc, client_rc.left, client_rc.top, 
			 RECTW(client_rc), RECTH(client_rc));
			 
	PaintListboxBmp(pctrl, &bmp_rc, hdc);
	
	PaintListboxFrame(hdc, FALSE, &client_rc, &bmp_rc);

	if (pctrl->dwStyle & WS_DISABLED) {
		SetTextColor(hdc, PIXEL_darkgray);
	} else {
		SetTextColor(hdc, pctrl->textColor);
	}
	//SetBkColor(hdc, pctrl->iBkColor);
	SetBkColor(hdc, GetWindowElementColor(WEC_EXCOLOR_WHITESMOKE));
	if (LISTBOX_CURRITEM(pctrl) == -1)
		return;
	
	if (LISTBOX_CURRITEM(pctrl) < LISTBOX_ITEMNUM(pctrl)
		|| LISTBOX_ITEMNUM(pctrl) == -1 )
		strcpy(text, LoadString(LISTBOX_INFO(pctrl)[LISTBOX_CURRITEM(pctrl)]));
	else
		strcpy(text, "---");
	TextOut(hdc, text_rc.left, text_rc.top, text);
}

/**
   Listbox显示的主函数
**/
static  void  PaintListbox (PCONTROL pctrl)
{
	HDC		  hdc;
	BOOL		 marked;
	BOOL		 pressed;
	
	hdc	  =  GetClientDC((HWND)pctrl);
	
	marked   =  (LISTBOX_STATUS(pctrl) & LBST_MARKED)   == LBST_MARKED;
	pressed  =  (LISTBOX_STATUS(pctrl) & GEN_PRESSED)   == GEN_PRESSED;
	
	if (!pressed && !marked) {	// 正常显示; 没有成为焦点.
		PaintNormalListbox(pctrl, hdc);
	}
	else if (marked && !pressed) { // 焦点显示; 标记;
		PaintFocusListbox(pctrl, hdc);
	} 
	else if (marked && pressed) {  // 按键按下进入处理; 左右旋钮可以改变数据项.
		PaintListboxInProcess(pctrl, hdc);
	}
	
	ReleaseDC(hdc);
}


static  void  SetListboxCode (PCONTROL pctrl, WPARAM wParam, LPARAM lParam)
{
	switch ((LBCODE)wParam) {
		case  LBC_CURRITEM:
			LISTBOX_CURRITEM(pctrl) = (INT16)lParam;
			break;
	
		case LBC_ITEMNUM:
			LISTBOX_ITEMNUM(pctrl) = (INT16)lParam;
			break;
			
		case LBC_ITEM:
			LISTBOX_INFO(pctrl)[LOBYTE(lParam)] = (STRINGID)HIWORD(lParam);
			break;

		case LBC_ITEMLIST:
			LISTBOX_INFO(pctrl) = (STRINGID *)lParam;
			break;
			
		default:
			break;
	}
}

static  long  GetListboxCode (PCONTROL pctrl, WPARAM wParam, LPARAM lParam)
{
	switch ((LBCODE)wParam) {
		case  LBC_CURRITEM:
			*(INT16*)lParam = LISTBOX_CURRITEM(pctrl);
			break;
	
		case LBC_ITEMNUM:
			*(INT16*)lParam = LISTBOX_ITEMNUM(pctrl);
			break;
			
		case LBC_ITEM:
			*(STRINGID*)(lParam) = LISTBOX_INFO(pctrl)[LISTBOX_CURRITEM(pctrl)];
			break;

		case LBC_ITEMLIST:
			*(LPARAM *)lParam = (LPARAM)LISTBOX_INFO(pctrl);
			break;
			
		default:
			break;
	}

	return  *(long *)lParam;
}

static void GetNextListboxItem (PCONTROL pctrl)
{
	if (pctrl->dwStyle & LBS_DROPDOWN)
	{
		if ((LISTBOX_CURRITEM(pctrl) >= LISTBOX_TOPNDX(pctrl)) 
			&& (LISTBOX_CURRITEM(pctrl) < LISTBOX_BOTNDX(pctrl)))
		{
			LISTBOX_CURRITEM(pctrl) ++;
		}
		else
		{
			if (LISTBOX_BOTNDX(pctrl) < LISTBOX_ITEMNUM(pctrl) - 1)
			{
				LISTBOX_TOPNDX(pctrl) ++;
				LISTBOX_BOTNDX(pctrl) ++;
				LISTBOX_CURRITEM(pctrl) ++;
			}
		}
	}
	else
	{
		if (LISTBOX_CURRITEM(pctrl) < LISTBOX_ITEMNUM(pctrl) - 1)
		{
			LISTBOX_CURRITEM(pctrl) ++;
		}
		else
		{
			LISTBOX_CURRITEM(pctrl) = 0;
		}
	}

}

static void GetPreviousListboxItem(PCONTROL pctrl)
{
	if (pctrl->dwStyle & LBS_DROPDOWN)
	{
		if ((LISTBOX_CURRITEM(pctrl) > LISTBOX_TOPNDX(pctrl)) 
			&& (LISTBOX_CURRITEM(pctrl) <= LISTBOX_BOTNDX(pctrl)))
		{
			LISTBOX_CURRITEM(pctrl)--;
		}
		else
		{
			if (LISTBOX_TOPNDX(pctrl) > 0)
			{
				LISTBOX_TOPNDX(pctrl)--;
				LISTBOX_BOTNDX(pctrl)--;
				LISTBOX_CURRITEM(pctrl)--;
			}
		}
	}
	else
	{
		if (LISTBOX_CURRITEM(pctrl) > 0)
		{
			LISTBOX_CURRITEM(pctrl)--;
		}
		else
		{
			LISTBOX_CURRITEM(pctrl) = LISTBOX_ITEMNUM(pctrl) - 1;
		}
	}
}


static long ListboxCtrlProc (HWND hWnd, long message, WPARAM wParam, LPARAM lParam)
{
	PCONTROL	  pctrl;

	pctrl = (PCONTROL)hWnd;
	switch ( message) {
		case MSG_CREATE:
			LISTBOX_STATUS(pctrl) = 0;
			break; 

		case MSG_KEYENCODER:
			switch (wParam) {
				case  KEY_KNOB_PRESSED:
					if (LISTBOX_STATUS(pctrl) & GEN_PRESSED) {
						LISTBOX_STATUS(pctrl) &= ~GEN_PRESSED;
						LISTBOX_STATUS(pctrl) |= LBST_2CLICK;
						LISTBOX_STATUS(pctrl) &= ~LBST_1CLICK;
						NotifyParent(hWnd, pctrl->id, LBN_CHANGED);
					} else {
						LISTBOX_STATUS(pctrl) |= GEN_PRESSED;
						LISTBOX_STATUS(pctrl) |= LBST_1CLICK;
					}
					break;

				case  KEY_KNOB_ROTATE_LEFT:  /* 逆时针 */
					if (LISTBOX_STATUS(pctrl) & GEN_PRESSED) {
						LISTBOX_STATUS(pctrl) |= LBST_TOP;
						LISTBOX_STATUS(pctrl) &= ~LBST_BOTTOM;
						GetPreviousListboxItem(pctrl);
					}
					break;

				case  KEY_KNOB_ROTATE_RIGHT: /* 顺时针 */
					if (LISTBOX_STATUS(pctrl) & GEN_PRESSED) {
						LISTBOX_STATUS(pctrl) |= LBST_BOTTOM;
						LISTBOX_STATUS(pctrl) &= ~LBST_TOP;
						GetNextListboxItem(pctrl);
					}
					break;

				default:
					break;
			}
			InvalidateRect(hWnd, 0, TRUE);
			return 0;

#if _ENB_TOUCH
		case MSG_TOUCHENCODER:
			if (lParam)
				SendMessage(hWnd, MSG_SETFOCUS, wParam, lParam);
			else
				NotifyParent(hWnd, pctrl->id, LBN_ENTER);
			return 0;
#endif
			
		case MSG_PAINT:
			PaintListbox(pctrl);
			return 0;

		case MSG_SETFOCUS:
			LISTBOX_STATUS(pctrl) |= LBST_MARKED;
			InvalidateRect(hWnd, 0, TRUE);
			NotifyParent(hWnd, pctrl->id, LBN_SETFOCUS);
			return 0;
			
		case MSG_KILLFOCUS:
			LISTBOX_STATUS(pctrl) = 0;
			InvalidateRect(hWnd, 0, TRUE);
			NotifyParent(hWnd, pctrl->id, LBN_KILLFOCUS);
			return 0;

		case MSG_SETITEM:
			SetListboxCode(pctrl, wParam, lParam);
			InvalidateRect(hWnd, 0, TRUE);
			return 0;

		case MSG_GETITEM:
			return GetListboxCode(pctrl, wParam, lParam);

		case MSG_GETDLGCODE:
			return 0;
			
		case MSG_ENABLE:
			if (wParam && (pctrl->dwStyle & WS_DISABLED)){
				pctrl->dwStyle &= ~WS_DISABLED;
			}
			else if (!wParam && !(pctrl->dwStyle & WS_DISABLED)){
				pctrl->dwStyle |= WS_DISABLED;
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

BOOL RegisterListboxControl (void)
{
	WNDCLASS WndClass;

	WndClass.spClassName = "listbox";
	WndClass.dwStyle	 = WS_NONE;
	WndClass.dwExStyle   = WS_EX_NONE;
	WndClass.iBkColor	= GetWindowElementColor (BKC_CONTROL_DEF); //PIXEL_lightwhite;
	WndClass.textColor   = GetWindowElementColor (FGC_CONTROL_DEF);
	WndClass.proc		= ListboxCtrlProc;

	return AddNewControlClass (&WndClass) == ERR_OK;
}

INT16  SetListBoxString(UINT16 parent_id, UINT16 ctrl_id, STRINGID *list_string_id,  INT16 string_count)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_LISTBOX) == 0) {
		LISTBOX_INFO(pCtrl)	= list_string_id;
		LISTBOX_ITEMNUM(pCtrl) = string_count;
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}


INT16  SetListBoxCurChoi(UINT16 parent_id, UINT16 ctrl_id, INT16 cur_choice) 
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_LISTBOX) == 0) {
		LISTBOX_CURRITEM(pCtrl) = cur_choice;
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  SetListBoxChoiNum(UINT16 parent_id, UINT16 ctrl_id, INT16 choi_num)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_LISTBOX) == 0) {
		LISTBOX_ITEMNUM(pCtrl) = choi_num;
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  GetListBoxCurChoi(UINT16 parent_id, UINT16 ctrl_id)
{
	PCONTROL   pCtrl;
	char	   name[30 + 1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_LISTBOX) == 0)
	{
		return  LISTBOX_CURRITEM(pCtrl);
	}
	else
	{
		return  ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  GetListBoxChoiNum(UINT16 parent_id, UINT16 ctrl_id)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_LISTBOX) == 0) {
		return LISTBOX_ITEMNUM(pCtrl);
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}
INT16  GetListBoxString(UINT16 parent_id, UINT16 ctrl_id, STRINGID **list_string_id,  INT16 *string_count)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_LISTBOX) == 0) {
		*list_string_id = LISTBOX_INFO(pCtrl);
		*string_count = LISTBOX_ITEMNUM(pCtrl);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}

}

INT16 GetListBoxInProcess(UINT16 parent_id, UINT16 ctrl_id)
{
	PCONTROL   pCtrl;
	BOOL	   marked;
	BOOL	   pressed;	

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  FALSE;

	marked	 =	(LISTBOX_STATUS(pCtrl) & LBST_MARKED)	== LBST_MARKED;
	pressed  =	(LISTBOX_STATUS(pCtrl) & GEN_PRESSED)	== GEN_PRESSED;
		
	if (marked && pressed) 
	{  
		// 按键按下进入处理; 左右旋钮可以改变数据项.
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

VOID SetListInfo(LISTBOXDATAP pList, GLOBAL_STRING_RES *pItem)
{
	INT16   i;
	char	*text;
	UINT32  strId;
	for (i = 0; i < pList->dispNum; i++)
	{
		strId = *(pList->infoList + i);// + pList->topNdx);//字符串ID一样
		if (strId >= STR_MAXNUM)
		{
			break;
		}
		text = LoadString(*(pList->infoList + i));
		if ((i < pItem->maxLen) && (i + pList->topNdx < pList->itemNum))
		{
			strncpy(text, (pItem + i)->text, sizeof((pItem + i)->text) - 1);
			// 系统字符串最大长度
		}
		else
		{
			*text = '\0';
		}
	}
}

VOID DispList(HWND hWnd, LISTBOXDATAP pList)
{
	INT16   i;
	HWND	hCtrl;
	INT16   iItem_id;
	STRINGID *pStrid;
	for (i = 0; i < pList->dispNum; i++)
	{
		// id = id-start(sroll) + id-pageup + 1
		iItem_id = pList->sroll_id + 3 + i;
		hCtrl = GetDlgItem(hWnd, iItem_id);
		if (!hCtrl)
			break;
		if (pList->topNdx + i <= pList->botNdx)
		{
			pStrid = pList->infoList;
			pStrid += pList->topNdx + i;
			SetWindowText(hCtrl, *pStrid);
			EnableWindow(hCtrl, TRUE);
		}
		else
		{
			SetWindowText(hCtrl, 0);
			EnableWindow(hCtrl, FALSE);
		}
	}
	hCtrl = GetDlgItem(hWnd, pList->sroll_id + 1);
	if (!hCtrl)
		return;
	EnableWindow(hCtrl, (pList->topNdx > 0));
	hCtrl = GetDlgItem(hWnd, pList->sroll_id + 2);
	if (!hCtrl)
		return;
	EnableWindow(hCtrl, (pList->botNdx < pList->itemNum - 1));
}

VOID PageUpList(HWND hWnd, LISTBOXDATAP pList)
{
	HWND   hCtrl;
	INT16 topNdx = pList->topNdx;
	if (topNdx > 0)
	{
		topNdx -= pList->dispNum;
		if (topNdx < 0)
			topNdx = 0;
		pList->topNdx = topNdx;
	}
	else
	{
		pList->topNdx = 0;
	}
	if (pList->dispNum > pList->itemNum - pList->topNdx)
	{
		pList->botNdx = pList->itemNum - 1;
	}
	else
	{
		pList->botNdx = pList->topNdx + pList->dispNum - 1;
	}
	hCtrl = GetDlgItem(hWnd, pList->sroll_id);
	if (!hCtrl)
		return;
	DrawScrollV(hCtrl, 
		pList->topNdx, pList->itemNum, pList->dispNum);
}

VOID PageDownList(HWND hWnd, LISTBOXDATAP pList)
{
	HWND   hCtrl;
	if (pList->botNdx < pList->itemNum - 1)
	{
		pList->topNdx = pList->botNdx + 1;
	}
	if (pList->dispNum > pList->itemNum - pList->topNdx)
	{
		pList->botNdx = pList->itemNum - 1;
	}
	else
	{
		pList->botNdx = pList->topNdx + pList->dispNum - 1;
	}
	hCtrl = GetDlgItem(hWnd, pList->sroll_id);
	if (!hCtrl)
		return;
	DrawScrollV(hCtrl, 
		pList->topNdx, pList->itemNum, pList->dispNum);
}


INT16 GetListClick(INT16 id, LISTBOXDATAP pList)
{
	return (id - (pList->sroll_id + 2) + pList->topNdx);
}


