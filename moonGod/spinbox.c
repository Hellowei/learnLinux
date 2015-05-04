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

#define   SPINBOX_GLOBALS 
#include  "includes.h"


#define  SPINBOX_BMP_W		13  // '增多减小'的图形的宽度
#define  SPINBOX_TEXT_INDENT   5   // 内部文本缩进的象素点.
#define  SPINBOX_INNER_BORDER  3   // 内部边框的宽度.


// 计算矩形, 为以后的显示使用.
static  void GetSpinboxRect (PCONTROL pctrl, RECT *pClient, RECT *pText, RECT *pTextClient, RECT *pBmp, HDC hdc )
{
	long		 font_height;
	int		  top;

	GetClientRect((HWND)pctrl, pClient);
	font_height = GetFontHeight(hdc);

	*pBmp  = *pClient;
	*pText = *pClient;

	pBmp->left   = pClient->right - SPINBOX_BMP_W + 1;
	pText->right = pClient->right - SPINBOX_BMP_W;
	*pTextClient = *pText;
	
	// 文本Y边标居中对齐.
	top = pClient->top + (pClient->bottom - pClient->top - font_height) / 2;
	pText->top = top;
	pText->left += SPINBOX_TEXT_INDENT;

}

static INLINE INT16 DealSpinboxIntVal(PCONTROL pctrl)
{
	if (SPINBOX_ICUR (pctrl) > SPINBOX_IMAX(pctrl))
		SPINBOX_ICUR (pctrl) = SPINBOX_IMAX(pctrl);
	if (SPINBOX_ICUR (pctrl) < SPINBOX_IMIN(pctrl))
		SPINBOX_ICUR (pctrl) = SPINBOX_IMIN(pctrl);
}

static INLINE INT16 DealSpinboxFloatVal(PCONTROL pctrl)
{
	if (SPINBOX_FCUR (pctrl) > SPINBOX_FMAX(pctrl))
		SPINBOX_FCUR (pctrl) = SPINBOX_FMAX(pctrl);
	if (SPINBOX_FCUR (pctrl) < SPINBOX_FMIN(pctrl))
		SPINBOX_FCUR (pctrl) = SPINBOX_FMIN(pctrl);
}

static  char * GetSpinboxText (PCONTROL pctrl, CHAR *str , INT str_len)
{
	str_len = str_len;
	char *p, buf[128];
	strcpy (str, "");

	switch (SPINBOX_MODE (pctrl))
	{
	case SBTXT_BLANK:
		sprintf (str, " ");
		break;
	case SBTXT_INT:
		sprintf (str, "---");
		break;
	case SBTXT_FLOAT:
		sprintf (str, "--.-");
		break;
	case SBTXT_NUM :
// 显示旋转编辑框中的数值

		switch (SPINBOX_FORM (pctrl))
		{
// 无效值
		case FORM_0D:
			sprintf (str, "---");
			break;
// 整数类型
		case FORM_2D:
			DealSpinboxIntVal(pctrl);
			sprintf (str, "%-2d", SPINBOX_ICUR (pctrl));
			break;
		case FORM_3D:
			DealSpinboxIntVal(pctrl);
			sprintf (str, "%-3d", SPINBOX_ICUR (pctrl));
			break;
		case FORM_4D:
			DealSpinboxIntVal(pctrl);
			sprintf (str, "%-4d", SPINBOX_ICUR (pctrl));
			break;
// 浮点数类型
		default:
			if ((SPINBOX_FCUR (pctrl) > SPINBOX_FMAX (pctrl))
				|| (SPINBOX_FCUR (pctrl) < SPINBOX_FMIN (pctrl)) )
			{
				if (SPINBOX_FCUR (pctrl) > SPINBOX_FMAX (pctrl))
					SPINBOX_FCUR (pctrl) = SPINBOX_FMAX (pctrl);

				if (SPINBOX_FCUR (pctrl) < SPINBOX_FMIN (pctrl))
					SPINBOX_FCUR (pctrl) = SPINBOX_FMIN (pctrl);

				GetFloatText (str, str_len, SPINBOX_FCUR (pctrl) / 10, 10, FORM_51F);
			}
			else
			{
				switch (SPINBOX_FORM (pctrl))
				{
				case FORM_41F:
					GetFloatText (str, str_len, SPINBOX_FCUR (pctrl) / 10, 10, FORM_41F);
					break;
				case FORM_51F:
					GetFloatText (str, str_len, SPINBOX_FCUR (pctrl) / 10, 10, FORM_51F);
					break;
				case FORM_52F:
					GetFloatText (str, str_len, SPINBOX_FCUR (pctrl), 100, FORM_52F);
					break;
				case FORM_53F:
					GetFloatText (str, str_len, SPINBOX_FCUR (pctrl) *10, 1000, FORM_53F);
					break;
				case FORM_72F:
					GetFloatText (str, str_len, SPINBOX_FCUR (pctrl), 100, FORM_72F);
					break;
				default:
					break;
				}
			}

			break;
		}

		break;

	default:
		break;
	}

	strcpy (buf, str);

	p = buf;

	while (*p)
	{
		if (*p != ' ')
			break;

		p ++;
	}

	strcpy (str, p);

	return  str;
}




//绘制表示'增多减小'的图形.
static  void  PaintSpinboxBmp (PCONTROL pctrl, RECT * BmpRc, HDC hdc)
{
	int  mid;
	RECT rc;
	int  i;

	pctrl = pctrl;
	rc = *BmpRc;
	mid = rc.top + RECTH(rc)/2;
	SetPenColor(hdc, PIXEL_black);
	Line(hdc, rc.left, mid, rc.right -1, mid);

	for (i = 0; i < 4; i++) {
		Line(hdc, rc.right - 10 + i, mid - 2 - i, rc.right - 4 - i, mid - 2 - i); 
		Line(hdc, rc.right - 10 + i, mid + 2 + i, rc.right - 4 - i, mid + 2 + i); 
	}
}

// 绘制spinbox的外框.
static  void  PaintSpinboxFrame (HDC hdc, BOOL marked, RECT *rcClient, RECT *rcBmp)
{
	if (marked) { //焦点状态
		SetPenColor(hdc, GetWindowElementColor(BKC_CONTROL_FOCUS));
		Rect(hdc, rcClient->left - 2, rcClient->top - 2, 
			 rcClient->right + 2, rcClient->bottom + 2);
		Rect(hdc, rcClient->left - 1, rcClient->top - 1, rcClient->right + 1,
			 rcClient->bottom + 1);
		Rect3D(hdc, rcClient->left, rcClient->top, rcClient->right,
			   rcClient->bottom, PIXEL_black, PIXEL_white);
		Rect3D(hdc, rcBmp->left, rcBmp->top + 1, 
			   rcBmp->right - 1, rcBmp->bottom - 1,
			   PIXEL_white,  PIXEL_black);
	} else  { //正常模式
		
		SetPenColor(hdc, PIXEL_black);
		Rect(hdc, rcClient->left, rcClient->top, rcClient->right + 1, rcClient->bottom + 1);
	}
}

// 绘制成为焦点的控件的标记状态. 注意, 一旦按一次键进入处理状态, 显示是不同的.虽然
// 也是处于焦点状态;
static  void  PaintFocusSpinbox (PCONTROL pctrl, HDC hdc)
{
	RECT		 client_rc;
	RECT		 text_rc;
	RECT		 textClient_rc;
	RECT		 bmp_rc;
	char		 text[10];

	ShowHelpString(pctrl, SPINBOX_HELPID(pctrl), SPINBOX_HELPSTR(pctrl));
	PDC pdc = dc_HDC2PDC(hdc);
	//pdc->pLogFont = GetSystemFont(SYSLOGFONT_FIXED);
	//panhonghui
    if (MonitorConfig.language == RUSSIAN)
    {
         pdc->pLogFont = GetSystemFont(SYSLOGFONT_NOR_RUS);	

    }
    else
    {
        pdc->pLogFont = GetSystemFont(SYSLOGFONT_FIXED);

    }

	text[0] = 0;
	
	GetSpinboxRect(pctrl, &client_rc, &text_rc, &textClient_rc,&bmp_rc, hdc);

	PaintSpinboxFrame(hdc, TRUE, &client_rc, &bmp_rc);
	
	SetBrushColor(hdc, GetWindowElementColor(WEC_CONTROL_FOCUSFRAME));
	FillRect(hdc, textClient_rc.top + 1, textClient_rc.left + 1, 
			 RECTW(textClient_rc) - 2, 
			 RECTH(textClient_rc) - 1);
			 
	PaintSpinboxBmp(pctrl, &bmp_rc, hdc);

	// 反色显示, 文本框的值.
	SetBkColor(hdc, GetWindowElementColor(WEC_CONTROL_FOCUSFRAME));
	SetTextColor(hdc, PIXEL_white);
	TextOut(hdc, text_rc.left, text_rc.top, 
			GetSpinboxText(pctrl, text, sizeof(text)));

}

static  void  PaintSpinboxInProcess (PCONTROL pctrl, HDC hdc)
{
	RECT		 client_rc;
	RECT		 text_rc;
	RECT		 textClient_rc;
	RECT		 bmp_rc;
	char		 text[10];

	text[0] = 0;
	
	PDC pdc = dc_HDC2PDC(hdc);
	pdc->pLogFont = GetSystemFont(SYSLOGFONT_WCHAR_DEF);
	
	GetSpinboxRect(pctrl, &client_rc, &text_rc, &textClient_rc, &bmp_rc, hdc);
	
	PaintSpinboxFrame(hdc, TRUE, &client_rc, &bmp_rc);
	
	SetBrushColor(hdc, pctrl->iBkColor);
	FillRect(hdc, textClient_rc.top + 1, textClient_rc.left + 1, 
			 RECTW(textClient_rc) - 2, 
			 RECTH(textClient_rc) - 2 );
			 
	PaintSpinboxBmp(pctrl, &bmp_rc, hdc);
	
	SetBkColor(hdc, pctrl->iBkColor);
	SetTextColor(hdc, pctrl->textColor);
	GetSpinboxText(pctrl, text, sizeof(text));
	TextOut(hdc, text_rc.left, text_rc.top, text);
}

static  void  PaintNormalSpinbox (PCONTROL pctrl, HDC hdc)
{
	RECT		 client_rc;
	RECT		 text_rc;
	RECT		 textClient_rc;
	RECT		 bmp_rc;
	char		 text[10];
	
	ShowHelpString(pctrl, SPINBOX_HELPID(pctrl), 0);
	PDC pdc = dc_HDC2PDC(hdc);
	pdc->pLogFont = GetSystemFont(SYSLOGFONT_WCHAR_DEF);
	
	text[0] = 0;
	
	GetSpinboxRect(pctrl, &client_rc, &text_rc, &textClient_rc, &bmp_rc, hdc);


	//SetBrushColor(hdc, pctrl->iBkColor);
	SetBrushColor(hdc, GetWindowElementColor(WEC_EXCOLOR_WHITESMOKE));
	FillRect(hdc, client_rc.left, client_rc.top, 
			 RECTW(client_rc), RECTH(client_rc));
	PaintSpinboxBmp(pctrl, &bmp_rc, hdc);
	
	PaintSpinboxFrame(hdc, FALSE, &client_rc, &bmp_rc);

	if (pctrl->dwStyle & WS_DISABLED) {
		SetTextColor(hdc, PIXEL_darkgray);
	} else {
		SetTextColor(hdc, pctrl->textColor);
	}
	//SetBkColor(hdc, pctrl->iBkColor);
	SetBkColor(hdc, GetWindowElementColor(WEC_EXCOLOR_WHITESMOKE));
	TextOut(hdc, text_rc.left, text_rc.top, 
			GetSpinboxText(pctrl, text, sizeof(text)));
}

static  void  PaintSpinbox (PCONTROL pctrl)
{
	HDC		  hdc;
	BOOL		 marked;
	BOOL		 pressed;
	
	hdc	 = GetClientDC((HWND)pctrl);
	marked  = (SPINBOX_STATUS(pctrl) & SBST_MARKED) == SBST_MARKED;
	pressed = (SPINBOX_STATUS(pctrl) & GEN_PRESSED) == GEN_PRESSED;
	
	if (!pressed && !marked) {	// 正常显示; 没有成为焦点.
		PaintNormalSpinbox(pctrl, hdc);
	}
	else if (marked && !pressed) { // 焦点显示; 标记;
		PaintFocusSpinbox(pctrl, hdc);
	} 
	else if (marked && pressed) {  // 按键按下进入处理; 左右旋钮可以改变数据项.
		PaintSpinboxInProcess(pctrl, hdc);
	}
	
	ReleaseDC(hdc);
}

// 计算下一个值, 递增;
static  void   CalcNextSpinboxValue (PCONTROL pctrl)
{
	if ((SPINBOX_FORM(pctrl) == FORM_2D)
		|| (SPINBOX_FORM(pctrl) == FORM_3D)
		|| (SPINBOX_FORM(pctrl) == FORM_4D)) {
		// 整数类型
		if (SPINBOX_ICUR(pctrl) + SPINBOX_ISTEP(pctrl) <= SPINBOX_IMAX(pctrl))  {
			SPINBOX_ICUR(pctrl) += SPINBOX_ISTEP(pctrl);

			if (SPINBOX_RATE(pctrl) != 0)
				SPINBOX_FCUR(pctrl) = (INT32)SPINBOX_ICUR(pctrl) * 1000 / SPINBOX_RATE(pctrl) ;

		}
	}
	else if (SPINBOX_FORM(pctrl) == FORM_41F) {
		if (SPINBOX_ICUR(pctrl) + SPINBOX_ISTEP(pctrl) <= SPINBOX_IMAX(pctrl)) {
			SPINBOX_ICUR(pctrl) += SPINBOX_ISTEP(pctrl);

			if (SPINBOX_RATE(pctrl) != 0)
				SPINBOX_FCUR(pctrl) = (INT32)SPINBOX_ICUR(pctrl) * 1000 / SPINBOX_RATE(pctrl) ;

		}
	}
	else  {
		// 浮点数类型
		if (SPINBOX_FCUR(pctrl) + SPINBOX_FSTEP(pctrl) <= SPINBOX_FMAX(pctrl)) {
			SPINBOX_FCUR(pctrl) += SPINBOX_FSTEP(pctrl);
		}
	}
}

// 计算前一个值, 递减.
static  void   CalcPreviousSpinboxValue(PCONTROL pctrl)
{
	if ((SPINBOX_FORM(pctrl) == FORM_2D)
		 || (SPINBOX_FORM(pctrl) == FORM_3D)
		 || (SPINBOX_FORM(pctrl) == FORM_4D)) {
		 // 整数类型
		if (SPINBOX_ICUR(pctrl) - SPINBOX_ISTEP(pctrl) >= SPINBOX_IMIN(pctrl)) {
			SPINBOX_ICUR(pctrl) -= SPINBOX_ISTEP(pctrl);

			if (SPINBOX_RATE(pctrl) != 0)
				SPINBOX_FCUR(pctrl) = (INT32)SPINBOX_ICUR(pctrl) * 1000 / SPINBOX_RATE(pctrl) ;

		}
	}
	else if (SPINBOX_FORM(pctrl) == FORM_41F) {
		if (SPINBOX_ICUR(pctrl) - SPINBOX_ISTEP(pctrl) >= SPINBOX_IMIN(pctrl)) {
			SPINBOX_ICUR(pctrl) -= SPINBOX_ISTEP(pctrl);

			if (SPINBOX_RATE(pctrl) != 0)
				SPINBOX_FCUR(pctrl) = (INT32)SPINBOX_ICUR(pctrl) * 1000 / SPINBOX_RATE(pctrl);

		}
	}
	else {
		// 浮点数类型
		if (SPINBOX_FCUR(pctrl) - SPINBOX_FSTEP(pctrl) >= SPINBOX_FMIN(pctrl)) {
			SPINBOX_FCUR(pctrl) -= SPINBOX_FSTEP(pctrl);
		}
	}
}

static  void  SetSpinboxItem (PCONTROL pctrl, WPARAM wParam, LPARAM lParam)
{
	SPINBOXDATAP  pSpinbox;

	pSpinbox = (SPINBOXDATAP)pctrl->dwAddData2;
	switch ((SBCODE)wParam) {
		case SBC_FMAX:
			pSpinbox->fMax = (INT32)lParam;
			break;

		case SBC_FMIN:
			pSpinbox->fMin = (INT32)lParam;
			break;

		case SBC_FCUR:
			pSpinbox->fCur = (INT32)lParam;
			break;

		case SBC_IMAX:
			pSpinbox->iMax = (INT16)lParam;
			break;

		case SBC_IMIN:
			pSpinbox->iMin = (INT16)lParam;
			break;

		case SBC_ICUR:
			pSpinbox->iCur = (INT16)lParam;
			break;

		case SBC_RATE:
			pSpinbox->rate = (INT16)lParam;
			break;

		case SBC_MODE:
			SPINBOX_MODE(pctrl) = (INT16)lParam;
			break;

		case SBC_FORM:
			SPINBOX_FORM(pctrl) = (INT16)lParam;
			break;

		default:
			break;

	}
	
}

static  long  GetSpinboxItem (PCONTROL pctrl, WPARAM wParam, LPARAM lParam)
{
	SPINBOXDATAP  pSpinbox;

	pSpinbox = (SPINBOXDATAP)pctrl->dwAddData2;
	switch ((SBCODE)wParam) {
		case SBC_FMAX:
			*(INT32*)lParam = pSpinbox->fMax;
			break;

		case SBC_FMIN:
			*(INT32*)lParam = pSpinbox->fMin;
			break;

		case SBC_FCUR:
			*(INT32*)lParam = pSpinbox->fCur;
			break;

		case SBC_IMAX:
			*(INT16*)lParam = pSpinbox->iMax;
			break;

		case SBC_IMIN:
			*(INT16*)lParam = pSpinbox->iMin;
			break;

		case SBC_ICUR:
			*(INT16*)lParam = pSpinbox->iCur;
			break;

		case SBC_RATE:
			*(INT16*)lParam = pSpinbox->rate;
			break;

		case SBC_MODE:
			*(INT16*)lParam = SPINBOX_MODE(pctrl);
			break;

		case SBC_FORM:
			*(INT16*)lParam = SPINBOX_FORM(pctrl);
			break;

		default:
			return (-1);

	}
	return (long)lParam;
}

static long SpinboxCtrlProc (HWND hWnd, long message, WPARAM wParam, LPARAM lParam)
{
	PCONTROL	  pctrl;

	pctrl = (PCONTROL)hWnd;
	switch (message) {
		case MSG_CREATE:
			//memset( Spinbox_Text, 0, sizeof(Spinbox_Text) );
			SPINBOX_STATUS(pctrl) = 0;
			break; 

		case MSG_KEYENCODER:
			switch (wParam) {
				case  KEY_KNOB_PRESSED:
					if (SPINBOX_STATUS(pctrl) & GEN_PRESSED) {
						SPINBOX_STATUS(pctrl) &= ~GEN_PRESSED;
						NotifyParent(hWnd, pctrl->id, SBN_CHANGED);
					} else {
						if (SPINBOX_MODE(pctrl) != SBTXT_NUM)
							SPINBOX_MODE(pctrl) = SBTXT_NUM;
							
						if (SPINBOX_FORM(pctrl) != FORM_0D) //如果是FORM_0D,不进入处理.
							SPINBOX_STATUS(pctrl) |= GEN_PRESSED;
							
						NotifyParent(hWnd, pctrl->id, SBN_ENTER);
					}
					break;

				case  KEY_KNOB_ROTATE_LEFT:
					if (SPINBOX_STATUS(pctrl) & GEN_PRESSED) {
						CalcPreviousSpinboxValue(pctrl);
						NotifyParent(hWnd, pctrl->id, SBN_DATACHANGING);
					}
					break;

				case  KEY_KNOB_ROTATE_RIGHT:
					if (SPINBOX_STATUS(pctrl) & GEN_PRESSED) {
						CalcNextSpinboxValue(pctrl);
						NotifyParent(hWnd, pctrl->id, SBN_DATACHANGING);
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
				NotifyParent(hWnd, pctrl->id, SBN_ENTER);
			return 0;
#endif

		case MSG_PAINT:
			PaintSpinbox(pctrl);
			return 0;

		case MSG_SETFOCUS:
			SPINBOX_STATUS(pctrl) |= SBST_MARKED;
			InvalidateRect(hWnd, 0, TRUE);
			NotifyParent(hWnd, pctrl->id, SBN_SETFOCUS);
			return 0;
			
		case MSG_KILLFOCUS:
			SPINBOX_STATUS(pctrl) = 0;
			InvalidateRect(hWnd, 0, TRUE);
			NotifyParent(hWnd, pctrl->id, SBN_KILLFOCUS);
			return 0;

		case MSG_SETITEM:
			SetSpinboxItem(pctrl, wParam, lParam);
			InvalidateRect(hWnd, 0, TRUE);
			return 0;

		case MSG_GETITEM:
			return GetSpinboxItem(pctrl, wParam, lParam);
		
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

BOOL RegisterSpinboxControl (void)
{
	WNDCLASS WndClass;

	WndClass.spClassName = "spinbox";
	WndClass.dwStyle	 = WS_NONE;
	WndClass.dwExStyle   = WS_EX_NONE;
	WndClass.iBkColor	= GetWindowElementColor (BKC_CONTROL_DEF);
	WndClass.textColor   = GetWindowElementColor (FGC_CONTROL_DEF);
	WndClass.proc		= SpinboxCtrlProc;

	return AddNewControlClass (&WndClass) == ERR_OK;
}

INT16  SetSpinBoxType(UINT16 parent_id, UINT16 ctrl_id, FORMAT_TYPE type)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		SPINBOX_FORM(pCtrl) = type;
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  SetSpinBoxTextMode(UINT16 parent_id, UINT16 ctrl_id, SBT_MODE mode)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		SPINBOX_MODE(pCtrl) = mode;
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  SetSpinBoxFloatValue(UINT16 parent_id, UINT16 ctrl_id, INT32 cur_val, 
							INT32 max_val, INT32 min_val)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		SPINBOX_FMAX(pCtrl) = max_val;
		SPINBOX_FMIN(pCtrl) = min_val;
		SPINBOX_FCUR(pCtrl) = cur_val;
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  SetSpinBoxFloatValueEx(UINT16 parent_id, UINT16 ctrl_id, FLOAT cur_val, 
							  FLOAT max_val, FLOAT min_val)
{
	PCONTROL   pCtrl;
	char	   name[30+1];
	INT32	  value;

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		value = (INT32)(max_val * 100);
		SPINBOX_FMAX(pCtrl) = value;
		value = (INT32)(min_val * 100);
		SPINBOX_FMIN(pCtrl) = value;
		value = (INT32)(cur_val * 100);
		SPINBOX_FCUR(pCtrl) = value;
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  SetSpinBoxFloatCurValue(UINT16 parent_id, UINT16 ctrl_id, INT32 cur_val)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		SPINBOX_FCUR(pCtrl) = cur_val;
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  SetSpinBoxFloatCurValueEx(UINT16 parent_id, UINT16 ctrl_id, FLOAT cur_val)
{
	PCONTROL   pCtrl;
	char	   name[30+1];
	INT32	  value;

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		value = (INT32)( cur_val * 100);
		SPINBOX_FCUR(pCtrl) = value;
		//InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  SetSpinBoxFloatMaxValue(UINT16 parent_id, UINT16 ctrl_id, INT32 max_val)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		SPINBOX_FMAX(pCtrl) = max_val;
	 if (SPINBOX_FCUR(pCtrl) > SPINBOX_FMAX(pCtrl))
	 {
	   SPINBOX_FCUR(pCtrl) = SPINBOX_FMAX(pCtrl);
	 }		
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  SetSpinBoxFloatMaxValueEx(UINT16 parent_id, UINT16 ctrl_id, FLOAT max_val)
{
	PCONTROL   pCtrl;
	char	   name[30+1];
	INT32	  value;

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		value = (INT32)(max_val * 100);
		SPINBOX_FMAX(pCtrl) = value;
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  SetSpinBoxFloatMinValue(UINT16 parent_id, UINT16 ctrl_id, INT32 min_val)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		SPINBOX_FMIN(pCtrl) = min_val;
	 if (SPINBOX_FCUR(pCtrl) < SPINBOX_FMIN(pCtrl))
		 SPINBOX_FCUR(pCtrl) = SPINBOX_FMIN(pCtrl);
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  SetSpinBoxFloatMinValueEx(UINT16 parent_id, UINT16 ctrl_id, FLOAT min_val)
{
	PCONTROL   pCtrl;
	char	   name[30+1];
	INT32	  value;
	
	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		value = (INT32)(min_val * 100);
		SPINBOX_FMIN(pCtrl) = value;
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}


INT16  SetSpinBoxIntValue(UINT16 parent_id, UINT16 ctrl_id, INT16 cur_val, 
						  INT16 max_val, INT16 min_val)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		SPINBOX_IMAX(pCtrl) = max_val;
		SPINBOX_IMIN(pCtrl) = min_val;
		SPINBOX_ICUR(pCtrl) = cur_val;
		if (SPINBOX_RATE(pCtrl)) {
			SPINBOX_FMAX(pCtrl) = (INT32)SPINBOX_IMAX(pCtrl) * 1000 / SPINBOX_RATE(pCtrl);
			SPINBOX_FMIN(pCtrl) = (INT32)SPINBOX_IMIN(pCtrl) * 1000 / SPINBOX_RATE(pCtrl);
			SPINBOX_FCUR(pCtrl) = (INT32)SPINBOX_ICUR(pCtrl) * 1000 / SPINBOX_RATE(pCtrl);
		}
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  SetSpinBoxIntCurValue(UINT16 parent_id, UINT16 ctrl_id, INT16 cur_val)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		SPINBOX_ICUR(pCtrl) = cur_val;
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  GetSpinBoxIntCurValue(UINT16 parent_id, UINT16 ctrl_id)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		return SPINBOX_ICUR(pCtrl);
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  GetSpinBoxIntMaxValue(UINT16 parent_id, UINT16 ctrl_id)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		return SPINBOX_IMAX(pCtrl);
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  GetSpinBoxIntMinValue(UINT16 parent_id, UINT16 ctrl_id)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		return SPINBOX_IMIN(pCtrl);
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  SetSpinBoxIntMaxValue(UINT16 parent_id, UINT16 ctrl_id, INT16 max_val)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		SPINBOX_IMAX(pCtrl) = max_val;
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  SetSpinBoxIntMinValue(UINT16 parent_id, UINT16 ctrl_id, INT16 min_val)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		SPINBOX_IMIN(pCtrl) = min_val;
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  SetSpinBoxRate(UINT16 parent_id, UINT16 ctrl_id, INT16 rate)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		SPINBOX_RATE(pCtrl) = rate;
		InvalidateRect((HWND)pCtrl, NULL, TRUE);
		return ERR_OK;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  GetSpinBoxRate(UINT16 parent_id, UINT16 ctrl_id)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		return  SPINBOX_RATE(pCtrl);
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  GetSpinBoxFloatCurValue(UINT16 parent_id, UINT16 ctrl_id, INT32 *value)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		*value = SPINBOX_FCUR(pCtrl);
		return  0;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16  GetSpinBoxFloatMaxValue(UINT16 parent_id, UINT16 ctrl_id, INT32 *value)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		*value = SPINBOX_FMAX(pCtrl);
		return  0;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}


INT16  GetSpinBoxFloatMinValue(UINT16 parent_id, UINT16 ctrl_id, INT32 *value)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		*value = SPINBOX_FMIN(pCtrl);
		return  0;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}


INT16  GetSpinBoxFloatCurValueEx(UINT16 parent_id, UINT16 ctrl_id, FLOAT *value)
{
	PCONTROL   pCtrl;
	char	   name[30+1];
	INT32	  tmp_value;

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		tmp_value = SPINBOX_FCUR(pCtrl);
		*value = tmp_value / 100.0;
		return  0;
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16 GetDpinBoxFloatFormat(UINT16 parent_id, UINT16 ctrl_id)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		return SPINBOX_FORM(pCtrl);
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT16 GetSpinBoxInProcess(UINT16 parent_id, UINT16 ctrl_id)
{
	PCONTROL   pCtrl;
	BOOL	   marked;
	BOOL	   pressed;	

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  FALSE;

	marked	 =	(SPINBOX_STATUS(pCtrl) & LBST_MARKED)	== LBST_MARKED;
	pressed  =	(SPINBOX_STATUS(pCtrl) & GEN_PRESSED)	== GEN_PRESSED;
		
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



INT16 GetSpinBoxIntValue( UINT16 parent_id, UINT16 ctrl_id, INT16 *cur_val, INT16 * max_val, INT16 *min_val )
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		*cur_val = SPINBOX_ICUR(pCtrl);
		*max_val = SPINBOX_IMAX(pCtrl);
		*min_val = SPINBOX_IMIN(pCtrl);		
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}

}

INT16 GetSpinBoxFloatFormat(UINT16 parent_id, UINT16 ctrl_id)
{
	PCONTROL   pCtrl;
	char	   name[30+1];

	pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!pCtrl)
		return  ERR_CTRLID_NOT_EXIST;

	strncpy(name, GetClassName((HWND)pCtrl), 30);
	if (strcmp(name, CTRL_SPINBOX) == 0) {
		return SPINBOX_FORM(pCtrl);
	}else {
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
}

INT32 OnClickSpinbox(HWND hWnd, UINT16 ctrl, INT16 mode)
{
	INT32 value;
	UINT16 parent = ((PWIN)hWnd)->id;
	value = GetSpinBoxIntCurValue(parent, ctrl);
	if (mode > 0)
	{
		// 如果没有预设则使用默认空的标题和提示信息
		*LoadString(STR_DLG_KB_CAPTION) = '\0';
		*LoadString(STR_DLG_KB_TIPS) = '\0';
		SelectKeyboardType(mode, LoadString(STR_DLG_KB_CAPTION), 
									LoadString(STR_DLG_KB_TIPS));
	}
	UseKeyboard(hWnd, ctrl, (LPARAM)&value);
	SetSpinBoxIntCurValue(parent, ctrl, (INT16)value);
	value = GetSpinBoxIntCurValue(parent, ctrl);
	SetSpinBoxIntCurValue(parent, ctrl, (INT16)value);
	return value;
}

