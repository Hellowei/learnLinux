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

#define   EDIT_GLOBALS 
#include  "includes.h"

static void editPaintFocus(HWND hWnd, EDITDATAP pedit)
{
	HDC	 hdc;
	INT32   x0;
	INT32   y0;
	INT32   x1;
	INT32   y1;
	INT32   i;
	hdc	 = GetDC(hWnd);
	SetPenColor(hdc, PIXEL_blue);
	x0 = pedit->rcVis.left + 1;
	y0 = pedit->rcVis.top  + 1;
	x1 = pedit->rcVis.right - 2;
	y1 = pedit->rcVis.bottom - 1;
	Rect(hdc,x0,y0,x1,y1);
	if (pedit->leftMargin > 1)
	{
		x0 = pedit->rcVis.left   + pedit->leftMargin	- 1;
	}
	if (pedit->topMargin > 1)
	{
		y0 = pedit->rcVis.top	+ pedit->topMargin	 - 1;
	}
	if (pedit->rightMargin > 2)
	{
		x1 = pedit->rcVis.right  - pedit->rightMargin   + 1;
	}
	if (pedit->bottomMargin > 1)
	{
		y1 = pedit->rcVis.bottom - pedit->bottomMargin  + 1;
	}
	Rect(hdc,x0,y0,x1,y1);
	ReleaseDC(hdc);
}

static void editCtrlPrint(HWND hWnd, long message, WPARAM wParam, LPARAM lParam)
{
	long		drawStyle;
	int		 x, y, w, h;
	int		 show_len;
	HDC		 hdc;
//	PDC		 pdc;
	PCONTROL	pCtrl;
	EDITDATAP   pEdit;
	RECT		rc;
	char		*txt;
	drawStyle   = GetWindowStyle(hWnd);
	pCtrl	   = Control(hWnd);
	pEdit	   = (EDITDATAP)pCtrl->dwAddData2;
	x = pEdit->leftMargin;
	y = pEdit->topMargin;
	w = RECTW(pEdit->rcVis) - pEdit->leftMargin - pEdit->rightMargin;
	h = RECTH(pEdit->rcVis) - pEdit->topMargin - pEdit->bottomMargin;
	SetRect(&rc, x, y, x + w, y + h);
	txt = pEdit->content.string;
	hdc = GetClientDC (hWnd);
//	pdc = dc_HDC2PDC(hdc);
//	pdc->pLogFont = pCtrl->pLogFont;
	if (pCtrl->dwStyle & WS_DISABLED) {
		SetBkColor(hdc, PIXEL_darkgray);
		SetBrushColor(hdc, PIXEL_darkgray);
	} else {
		SetBkColor(hdc, GetWindowBkColor(hWnd));
		SetBrushColor(hdc, GetWindowBkColor(hWnd));
	}
//	SetBkColor(hdc, GetWindowBkColor(hWnd));
	SetTextColor(hdc,GetWindowTextColor(hWnd));
	FillRect(hdc, x, y, w, h);
	SetPenColor(hdc, PIXEL_black);
	Rect(hdc, rc.left, rc.top, rc.right, rc.bottom);
	
	switch (drawStyle & ES_TYPEMASK)
	{
		case ES_LEFT:
		{
			if (strlen(txt) > 0)
			{
				show_len = GetTextOutLenExtent(hdc, w - 4, txt);
				y += (h - GetFontHeight(hdc)) / 2;
				TextOutLen(hdc, x + 2, y, txt, show_len);
			}
			ReleaseDC(hdc);
			return;
		}
		
		case ES_CENTER:
		{
			if (strlen(txt) > 0)
			{
				SIZE  size;
				show_len = GetTextOutLenExtent(hdc, w - 1, txt);
				GetTextExtent(hdc, txt, show_len, &size);
				x += (w - size.cx) / 2;
				y += (h - size.cy) / 2;
				y += (h - GetFontHeight(hdc)) / 2;
				TextOutLen(hdc, x, y, txt, show_len);
			}
			ReleaseDC(hdc);
			return;
		}
		
		case ES_RIGHT:
		{
			if (strlen(txt) > 0)
			{
				SIZE  size;
				show_len = GetTextOutLenExtent(hdc, w - 1, txt);
				GetTextExtent(hdc, txt, show_len, &size);
				x += (w - size.cx);
				y += (h - GetFontHeight(hdc)) / 2;
				TextOutLen(hdc, x, y, txt, show_len);
			}
			break;
		}
		
		case ES_MULTILINE:
			break;
		
		/* not use * /		
		case ES_UPPERCASE:
			break;
		
		case ES_LOWERCASE:
			break;
		
		case ES_PASSWORD:
			break;
		
		case ES_AUTOVSCROLL:
			break;
		
		case ES_AUTOHSCROLL:
			break;
		
		case ES_NOHIDESEL:
			break;
		
		case ES_AUTOSELECT:
			break;
		
		case ES_READONLY:
			break;
		
		case ES_BASELINE:
			break;
		/ * not use */

		case ES_AUTOWRAP:
		{
			if (strlen(pEdit->content.string) > 0)
			{
				TextOutWrap(hdc, &rc, pEdit->content.string, -1);
			}
			break;
		}

		case ES_TITLE:
			break;
		
		case ES_TIP:
			break;

		default:
			printf("error edit drawStyle...%p\n", drawStyle);
			break;
	}
	ReleaseDC(hdc);
}

static void PaintEdit(HWND hWnd, EDITDATAP pEdit)
{
	long		drawStyle;
	int 	 x, y, w, h;
	int 	 show_len;
	HDC 	 hdc;
//	PDC 	 pdc;
	PCONTROL	pCtrl;
	RECT		rc;
	char		*txt;
	drawStyle	= GetWindowStyle(hWnd);
	pCtrl	   = Control(hWnd);
	x = pEdit->leftMargin;
	y = pEdit->topMargin;
	w = RECTW(pEdit->rcVis) - pEdit->leftMargin - pEdit->rightMargin;
	h = RECTH(pEdit->rcVis) - pEdit->topMargin - pEdit->bottomMargin;
	SetRect(&rc, x, y, x + w, y + h);
	txt = pEdit->content.string;
	hdc = GetClientDC (hWnd);

	if (pCtrl->dwStyle & WS_DISABLED)
	{
		SetBkColor(hdc, PIXEL_darkgray);
		SetBrushColor(hdc, PIXEL_darkgray);
		SetTextColor(hdc, GetWindowTextColor(hWnd));
	}
	else if (pEdit->status & EN_SETFOCUS)
	{
		SetBkColor(hdc, PIXEL_blue);
		SetBrushColor(hdc, PIXEL_blue);
		SetTextColor(hdc, PIXEL_white);
	}
	else
	{
		SetBkColor(hdc, GetWindowBkColor(hWnd));
		SetBrushColor(hdc, GetWindowBkColor(hWnd));
		SetTextColor(hdc, GetWindowTextColor(hWnd));
	}
	FillRect(hdc, x, y, w, h);
	SetPenColor(hdc, PIXEL_black);
	Rect(hdc, rc.left, rc.top, rc.right, rc.bottom);
	
	switch (drawStyle & ES_TYPEMASK)
	{
		case ES_LEFT:
		{
			if (strlen(txt) > 0)
			{
				show_len = GetTextOutLenExtent(hdc, w - 4, txt);
				y += (h - GetFontHeight(hdc)) / 2;
				TextOutLen(hdc, x + 2, y, txt, show_len);
			}
			ReleaseDC(hdc);
			return;
		}
		
		case ES_CENTER:
		{
			if (strlen(txt) > 0)
			{
				SIZE  size;
				show_len = GetTextOutLenExtent(hdc, w - 1, txt);
				GetTextExtent(hdc, txt, show_len, &size);
				x += (w - size.cx) / 2;
				y += (h - size.cy) / 2;
				y += (h - GetFontHeight(hdc)) / 2;
				TextOutLen(hdc, x, y, txt, show_len);
			}
			ReleaseDC(hdc);
			return;
		}
		
		case ES_RIGHT:
		{
			if (strlen(txt) > 0)
			{
				SIZE  size;
				show_len = GetTextOutLenExtent(hdc, w - 1, txt);
				GetTextExtent(hdc, txt, show_len, &size);
				x += (w - size.cx);
				y += (h - GetFontHeight(hdc)) / 2;
				TextOutLen(hdc, x, y, txt, show_len);
			}
			break;
		}
		
		case ES_MULTILINE:
			break;

		case ES_AUTOWRAP:
		{
			if (strlen(pEdit->content.string) > 0)
			{
    			rc.left += 1;
    			rc.top  += 1;
				TextOutWrap(hdc, &rc, pEdit->content.string, -1);
			}
			break;
		}

		default:
			break;
	}
	ReleaseDC(hdc);
}

static void editInit(HWND hWnd, EDITDATAP pEdit)
{
	INT32 len;
	pEdit->status = 0;

	GetClientRect(hWnd, &(pEdit->rcVis));

	pEdit->nVisW = RECTW(pEdit->rcVis);

	if (pEdit->leftMargin <= 0)
	{
		pEdit->leftMargin  = MARGIN_EDIT_LEFT;
	}

	if (pEdit->topMargin <= 0)
	{
		pEdit->topMargin  = MARGIN_EDIT_TOP;
	}

	if (pEdit->rightMargin <= 0)
	{
		pEdit->rightMargin  = MARGIN_EDIT_RIGHT;
	}

	if (pEdit->bottomMargin <= 0)
	{
		pEdit->bottomMargin  = MARGIN_EDIT_BOTTOM;
	}

	len = pEdit->content.maxlen;

	if (len < 1)
	{
		len = EDIT_STRLEN_MAX;
	}

	if (pEdit->content.string == NULL)
	{
		NewStrBuffer(&(pEdit->content), len);
	}
	
	if (pEdit->tiptext == NULL)
	{
		pEdit->tiptext = LoadString(STR_NULL);
	}

	if (pEdit->titletext == NULL)
	{
		pEdit->titletext = LoadString(STR_NULL);
	}
	
	if (pEdit->hardLimit <= 1)
	{
		pEdit->hardLimit = EDIT_STRLEN_MAX;
	}
	
	pEdit->changed   = FALSE;

}

static void editDestroy(HWND hWnd, EDITDATAP pEdit)
{
	if (pEdit->content.string != NULL)
	{
		TextDel(pEdit->content.string);
	}
}

static EDITDATAP GetEditItem(PCONTROL pCtrl)
{
	return ((EDITDATAP)(pCtrl->dwAddData2));
}

static long EditCtrlProc (HWND hWnd, long message, WPARAM wParam, LPARAM lParam)
{
	DWORD	   dwStyle;
	PCONTROL	pCtrl;
	EDITDATAP   pEdit;
	RECT		rc;
	char		*txt;
	pCtrl	   = Control(hWnd);
	dwStyle	 = pCtrl->dwStyle;
	pEdit	   = (EDITDATAP)pCtrl->dwAddData2;
	
	switch( message ) {
		case MSG_CREATE:
		{
			if (!pEdit)
				return -1;
			editInit(hWnd, pEdit);
			return 0;
		}

		case MSG_DESTROY:
			editDestroy(hWnd, pEdit);
			return 0;

		case MSG_PAINT:
//			editCtrlPrint(hWnd, message, wParam, lParam);
//			if (pEdit->status & EN_SETFOCUS)
//			{
//				editPaintFocus(hWnd, pEdit);
//			}
			PaintEdit(hWnd, pEdit);
			return 0;

		case MSG_NCPAINT:
			return 0;

		//case MSG_CHAR:
#if _ENB_TOUCH
		case MSG_TOUCHENCODER:
			if (lParam)
				SendMessage(hWnd, MSG_SETFOCUS, wParam, lParam);
			else
				NotifyParent(hWnd, pCtrl->id, EN_CLICKED);
			return 0;
#endif

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

		case MSG_SETTEXT:
			pCtrl->caption = (STRINGID)lParam;
			InvalidateRect (hWnd, NULL, TRUE);
			return 0;

		case MSG_FONTCHANGED:
			InvalidateRect (hWnd, NULL, TRUE);
			return 0;

		case MSG_SETFOCUS:
			pEdit->status = EN_SETFOCUS;
			InvalidateRect (hWnd, NULL, TRUE);
			return 0;

		case MSG_KILLFOCUS:
			if (pEdit->status & EN_SETFOCUS)
			{
				pEdit->status = EN_KILLFOCUS;
				InvalidateRect (hWnd, NULL, TRUE);
				return 0;
			}
			else
			{
				return (pEdit->status = 0);
			}

		case MSG_KEYENCODER:
			NotifyParent(hWnd, pCtrl->id, EN_CLICKED);
			return 0;

		case MSG_ERASEBKGND:
			return 0;

		default :
			break;
	}
	
	return DefaultDialogProc(hWnd, message, wParam, lParam);
}


BOOL RegisterEditControl (void)
{
	WNDCLASS WndClass;

	WndClass.spClassName = "edit";
	WndClass.dwStyle	 = WS_NONE;
	WndClass.dwExStyle   = WS_EX_NONE;
	WndClass.iBkColor	= PIXEL_lightwhite;
	WndClass.textColor   = GetWindowElementColor (FGC_CONTROL_DEF);
	WndClass.proc		= EditCtrlProc;

	return (AddNewControlClass (&WndClass) == ERR_OK);
}

CHAR *GetEditText(RESID parent, RESID child)
{
	PCONTROL pCtrl;
	pCtrl = GetSubCtrlItem(parent, child);
	return (((EDITDATAP)(pCtrl->dwAddData2))->content.string);
}

VOID SetEditboxText(PCONTROL pCtrl)
{
	EDITDATAP pEdit;
	CHAR	 *txt;
	pEdit   = GetEditItem(pCtrl);
	if (strlen(LoadString(pCtrl->caption)) > 0)
	{
		txt = pEdit->content.string;
		memset(txt, '\0', pEdit->hardLimit);
		strncpy(txt, LoadString(pCtrl->caption), pEdit->hardLimit-1);
	}
	else
	{
		if (strlen(pEdit->tiptext) > 0)
		{
			txt = pEdit->content.string;
			memset(txt, '\0', pEdit->hardLimit);
			strncpy(txt, pEdit->tiptext, pEdit->hardLimit-1);
		}
		else
		{
			txt = pEdit->content.string;
			memset(txt, '\0', pEdit->hardLimit);
		}
	}
	InvalidateRect ((HWND)pCtrl, NULL, TRUE);
}

VOID SetEditText(RESID parent, RESID child, UCHAR *txt)
{
	PCONTROL  pCtrl;
	pCtrl   = GetSubCtrlItem(parent, child);
	if (!pCtrl) return;
	//strncpy(LoadString(pCtrl->caption), txt, GetEditItem(pCtrl)->hardLimit-1);
	sprintf(LoadString(pCtrl->caption), "%s", txt);
	
//	prinfo("LoadString(pCtrl->caption)...%s, 0x%x\r\n", LoadString(pCtrl->caption), LoadString(pCtrl->caption));
	SetEditboxText(pCtrl);
}

INT32 SetEditboxIntValue(RESID parent, RESID child, INT32 value)
{
	PCONTROL  pCtrl;
	pCtrl   = GetSubCtrlItem(parent, child);
	if (!pCtrl) return;
	sprintf(LoadString(pCtrl->caption), "%d", value);
	SetEditboxText(pCtrl);
}

VOID SetEditboxHardLimit(RESID parent, RESID child, UINT32 limit)
{
	PCONTROL  pCtrl;
	EDITDATAP pEdit;

	pCtrl = GetSubCtrlItem(parent, child);

	if (!pCtrl)
		return;

	pEdit = GetEditItem(pCtrl);

	if (!pEdit)
		return;

	pEdit->hardLimit = limit;
}

