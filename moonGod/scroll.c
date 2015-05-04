/*******************************************************************************
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
*******************************************************************************/
#define  SCROLLBAR_GLOBALS 
#include "includes.h"

#define DEF_BORDER_WIDTH 1

static void DrawBorder(HDC hdc, INT32 border, PRECT prc)
{
	int i;
	
	if (border <= 0) 
	{
		return;
	}
	SetPenColor(hdc, PIXEL_darkgray);
	for (i = 0; i < border; i++)
	{
		Rect(hdc, prc->left + i, prc->top + i, prc->right - i, prc->bottom - i);
	}
}


static void DrawScrollBar(PCONTROL pctrl, HDC hdc)
{
	PDC pdc = dc_HDC2PDC(hdc);
	INT32 x, y, w, h, border;
	INT32 body, start;
	RECT rc;
	HWND hWnd = (HWND)pctrl;
	GetClientRect(hWnd, &rc);
	border = SCROLL_BORDER(pctrl);
	if (SCROLL_EX(pctrl) == NULL)
	{
		SetPenColor(hdc, PIXEL_black);
	}
	else
	{
		SetPenColor(hdc, SCROLL_EXBRC(pctrl));
	}
	DrawBorder(hdc, border, &rc);
	SetBrushColor(hdc, GetWindowBkColor(hWnd));
	FillRect(hdc, rc.left + border, rc.top + border, rc.right - border - 2,
		rc.bottom - border - 2);
	if (0 == SCROLL_COUNT(pctrl) || 0 == SCROLL_STEP(pctrl))
	{
		SetBrushColor(hdc, GetWindowTextColor(hWnd));
		x = rc.left + border;
		y = rc.top + border;
		w = rc.right - border - 2;
		h = rc.bottom - border - 2;
		FillRect(hdc, x, y, w, h);
		return;
	}
	if (pctrl->dwStyle & WS_VSCROLL)//垂直滚动条
	{
		x = rc.left + border;
		y = RECTH(rc) * (SCROLL_VALUE(pctrl) - SCROLL_MINNUM(pctrl))
			/ SCROLL_COUNT(pctrl);
		w = rc.right - border - 2;
		h = RECTH(rc) * SCROLL_STEP(pctrl) / SCROLL_COUNT(pctrl);
		if (h < SCROLL_MINVS(pctrl))
		{
			h = SCROLL_MINVS(pctrl);
		}
		if (h < 1)
		{
			h = 1;
		}
		if (h + y > rc.bottom - border)
		{
			y = rc.bottom - border - h;
			if (SCROLL_VALUE(pctrl) != SCROLL_MAXNUM(pctrl))
			{
				y -= 1;
			}
		}
		if (y < border + 1)
		{
			y = border + 1;
			if (SCROLL_VALUE(pctrl) == SCROLL_MINNUM(pctrl))
			{
				y = border;
			}
		}
	}
	else if (pctrl->dwStyle & WS_HSCROLL)
	{
		x = RECTW(rc) * (SCROLL_VALUE(pctrl) - SCROLL_MINNUM(pctrl))
			/ SCROLL_COUNT(pctrl);
		y = rc.top + border;
		w = RECTW(rc) * SCROLL_STEP(pctrl) / SCROLL_COUNT(pctrl);
		h = rc.bottom - border - 2;
		if (w < SCROLL_MINVS(pctrl))
		{
			w = SCROLL_MINVS(pctrl);
		}
		if (w < 1) //太小以至于不可见
		{
			w = 1;
		}
		if (w + x > rc.right - border)
		{
			x = rc.right - border - w;
			if (SCROLL_VALUE(pctrl) != SCROLL_MAXNUM(pctrl))
				x -= 1;
		}
		if (x < border + 1)
		{
			x = border + 1;
			if (SCROLL_VALUE(pctrl) == SCROLL_MINNUM(pctrl))
			{
				x = border;
			}
		}
	}
	else
	{
		return;
	}
	SetBrushColor(hdc, GetWindowTextColor(hWnd));
	FillRect(hdc, x, y, w, h);
}


static void PaintNormalScrollBar(PCONTROL pctrl, HDC hdc)
{
	if (SCROLL_EX(pctrl) == NULL)
	{
		SetWindowTextColor((HWND)pctrl, GetWindowElementColor(WEC_EXCOLOR_WHEAT));
	}
	else
	{
		SetWindowTextColor((HWND)pctrl, SCROLL_EXNFC(pctrl));
		ShowHelpString(pctrl, SCROLL_EXHID(pctrl), 0);
	}
	DrawScrollBar(pctrl, hdc);
	return;
}


static void PaintFocusScrollBar(PCONTROL pctrl, HDC hdc)
{
	if (SCROLL_EX(pctrl) == NULL)
	{
		SetWindowTextColor((HWND)pctrl, PIXEL_white);
	}
	else
	{
		SetWindowTextColor((HWND)pctrl, SCROLL_EXFFC(pctrl));
		ShowHelpString(pctrl, SCROLL_EXHID(pctrl), SCROLL_EXSTR(pctrl));
	}
	DrawScrollBar(pctrl, hdc);
	return;
}


static void PaintScrollBarInProcess(PCONTROL pctrl, HDC hdc)
{
	if (SCROLL_EX(pctrl) == NULL)
	{
		SetWindowTextColor((HWND)pctrl, PIXEL_blue);
	}
	else
	{
		SetWindowTextColor((HWND)pctrl, SCROLL_EXPFC(pctrl));
	}
	DrawScrollBar(pctrl, hdc);
	return;
}


static void PaintScrollBar(PCONTROL pctrl)
{
	HDC		  hdc;
	BOOL		 marked;
	BOOL		 pressed;
	
	hdc	  =  GetClientDC((HWND)pctrl);
	
	marked   =  (SCROLL_STATUS(pctrl) & SCR_MARKED)	== SCR_MARKED;
	pressed  =  (SCROLL_STATUS(pctrl) & GEN_PRESSED)   == GEN_PRESSED;
	if (!pressed && !marked) 
	{   
		//正常显示; 没有成为焦点.
		PaintNormalScrollBar(pctrl, hdc);
	}
	else if (marked && !pressed) 
	{ 
		//焦点显示; 标记;
		PaintFocusScrollBar(pctrl, hdc);
	} 
	else if (marked && pressed) 
	{  
		//按键按下进入处理; 左右旋钮可以改变数据项.
		PaintScrollBarInProcess(pctrl, hdc);
	}
	ReleaseDC(hdc);
}


static long 
	ScrollBarCtrlProc(HWND hWnd, long message, WPARAM wParam, LPARAM lParam)
{
	PCONTROL pCtrl = Control (hWnd);						
	
	switch (message)
	{
		case MSG_CREATE:
			if (! pCtrl->dwAddData2)
			{
				printf("SCROLLDATA is needful .\r\n");
				return 0;
			}
			SCROLL_STATUS(pCtrl) = 0;
			if (SCROLL_MINVS(pCtrl) < 2)
			{
				SCROLL_MINVS(pCtrl) = 2;
			}
			return 0;

		case MSG_KEYENCODER:
			switch (wParam) 
			{
				case KEY_KNOB_PRESSED:
					if (SCROLL_STATUS(pCtrl) & GEN_PRESSED)
					{
						SCROLL_STATUS(pCtrl) &= ~GEN_PRESSED;
					}
					else
					{
						SCROLL_STATUS(pCtrl) |= GEN_PRESSED;
					}
					if (SCROLL_EX(pCtrl))
					{
						if (SCROLL_EXPRC(pCtrl))
						{
							SCROLL_EXPRC(pCtrl)(hWnd, message, wParam, lParam);
						}
					}
					break;

				case KEY_KNOB_ROTATE_LEFT:  /* 逆时针 */
					if (SCROLL_STATUS(pCtrl) & GEN_PRESSED)
					{
						if ((SCROLL_VALUE(pCtrl) - SCROLL_STEP(pCtrl))
							< SCROLL_MINNUM(pCtrl))
						{
							SCROLL_VALUE(pCtrl) = SCROLL_MINNUM(pCtrl);
						}
						else
						{
							SCROLL_VALUE(pCtrl) -= SCROLL_STEP(pCtrl);
						}
						NotifyParent(hWnd, pCtrl->id, SCR_LEFT);
						NotifyParent(hWnd, pCtrl->id, SCR_CHANGE);
					}
					break;

				case KEY_KNOB_ROTATE_RIGHT: /* 顺时针 */
					if (SCROLL_STATUS(pCtrl) & GEN_PRESSED)
					{
						if (SCROLL_VALUE(pCtrl) + SCROLL_STEP(pCtrl)
							> SCROLL_MAXNUM(pCtrl))
						{
							SCROLL_VALUE(pCtrl) = SCROLL_MAXNUM(pCtrl);
						}
						else
						{
							SCROLL_VALUE(pCtrl) += SCROLL_STEP(pCtrl);
						}
						NotifyParent(hWnd, pCtrl->id, SCR_RIGHT);
						NotifyParent(hWnd, pCtrl->id, SCR_CHANGE);
					}
					break;

				default:
					break;
			}
			InvalidateRect(hWnd, 0, TRUE);
			return 0;

		
	#if _ENB_TOUCH
		case MSG_TOUCHENCODER:
			NotifyParent(hWnd, pCtrl->id, SCR_CHANGE);
			return 0;
	#endif

		case MSG_PAINT:
			PaintScrollBar(pCtrl);
			return 0;

		case MSG_SETFOCUS:
			SCROLL_STATUS(pCtrl) |= SCR_MARKED;
			InvalidateRect(hWnd, 0, FALSE);
			NotifyParent(hWnd, pCtrl->id, SCR_SETFOCUS);
			return 0;

		case MSG_KILLFOCUS:
			SCROLL_STATUS(pCtrl) = 0;
			InvalidateRect(hWnd, 0, TRUE);
			NotifyParent(hWnd, pCtrl->id, SCR_KILLFOCUS);
			return 0;

		case MSG_ENABLE:
			if (wParam && (pCtrl->dwStyle & WS_DISABLED))
			{
				pCtrl->dwStyle &= ~WS_DISABLED;
			}
			else if (!wParam && !(pCtrl->dwStyle & WS_DISABLED))
			{
				pCtrl->dwStyle |= WS_DISABLED;
			}
			else 
			{
				return 0;
			}
			InvalidateRect (hWnd, NULL, TRUE);
			return 0;

		default:
			break;
	}
	return DefaultDialogProc(hWnd, message, wParam, lParam);
}


BOOL RegisterScrollBarControl(VOID)
{
	WNDCLASS WndClass;

	WndClass.spClassName = "scroll";
	WndClass.dwStyle	 = WS_NONE;
	WndClass.dwExStyle   = WS_EX_NONE;
	WndClass.iBkColor	= GetWindowElementColor (BKC_CONTROL_DEF);
	WndClass.textColor   = GetWindowElementColor (FGC_CONTROL_DEF);
	WndClass.proc		= ScrollBarCtrlProc;

	return AddNewControlClass (&WndClass) == ERR_OK;
}


INT16 SetScrollBarValue(UINT16 parent_id, UINT16 ctrl_id, long  value)
{
	INT16	  ret;
	PCONTROL   pCtrl;
	if (ret = GetControlPtr(parent_id, ctrl_id, CTRL_SCROLL, &pCtrl))
	{
		return ret;
	}
	ret = (INT16)SCROLL_VALUE(pCtrl);
	if (value > SCROLL_MAXNUM(pCtrl))
	{
		value = SCROLL_MAXNUM(pCtrl);
	}
	if (value < SCROLL_MINNUM(pCtrl))
	{
		value = SCROLL_MINNUM(pCtrl);
	}
	SCROLL_VALUE(pCtrl) = value;
	InvalidateRect((HWND)pCtrl, NULL, 0);
	return ret;
}


INT16 SetScrollBarMaxNum(UINT16 parent_id, UINT16 ctrl_id, long  max)
{
	INT16	  ret;
	PCONTROL   pCtrl;
	
	if (ret = GetControlPtr(parent_id, ctrl_id, CTRL_SCROLL, &pCtrl))
	{
		return ret;
	}
	ret = (INT16)SCROLL_MAXNUM(pCtrl);
	if (max < SCROLL_MINNUM(pCtrl))
	{
		max = SCROLL_MINNUM(pCtrl);
	}
	if (max < SCROLL_VALUE(pCtrl))
	{
		SCROLL_VALUE(pCtrl) = max;
	}
	SCROLL_MAXNUM(pCtrl) = max;
	InvalidateRect((HWND)pCtrl, NULL, TRUE);
	return ret;
}


INT16 SetScrollBarMinNum(UINT16 parent_id, UINT16 ctrl_id, long  min)
{
	INT16	  ret;
	PCONTROL   pCtrl;
	
	if (ret = GetControlPtr(parent_id, ctrl_id, CTRL_SCROLL, &pCtrl))
	{
		return ret;
	}
	ret = (INT16)SCROLL_MINNUM(pCtrl);
	if (min > SCROLL_MAXNUM(pCtrl))
	{
		min = SCROLL_MAXNUM(pCtrl);
	}
	if (min > SCROLL_VALUE(pCtrl))
	{
		SCROLL_VALUE(pCtrl) = min;
	}
	SCROLL_MINNUM(pCtrl) = min;
	InvalidateRect((HWND)pCtrl, NULL, TRUE);
	return ret;
}


INT16 SetScrollBarStep(UINT16 parent_id, UINT16 ctrl_id, DWORD step)
{
	INT16	  ret;
	PCONTROL   pCtrl;
	
	if (ret = GetControlPtr(parent_id, ctrl_id, CTRL_SCROLL, &pCtrl))
	{
		return ret;
	}
	ret = (INT16)SCROLL_STEP(pCtrl);
	if (step < 1)
	{
		step = 1;
	}
	SCROLL_STEP(pCtrl) = step;
	InvalidateRect((HWND)pCtrl, NULL, TRUE);
	return ret;
}


INT16 SetScrollBarBorder(UINT16 parent_id, UINT16 ctrl_id, WORD border)
{
	INT16	  ret;
	PCONTROL   pCtrl;
	
	if (ret = GetControlPtr(parent_id, ctrl_id, CTRL_SCROLL, &pCtrl))
	{
		return ret;
	}
	ret = (INT16)SCROLL_BORDER(pCtrl);
	SCROLL_BORDER(pCtrl) = border;
	InvalidateRect((HWND)pCtrl, NULL, TRUE);
	return ret;
}


INT16 SetScrollBarMinVisual(UINT16 parent_id, UINT16 ctrl_id, WORD minVisual)
{
	INT16	  ret;
	PCONTROL   pCtrl;
	
	if (ret = GetControlPtr(parent_id, ctrl_id, CTRL_SCROLL, &pCtrl))
	{
		return ret;
	}
	ret = (INT16)SCROLL_MINVS(pCtrl);
	if (minVisual < 1)
	{
		minVisual = 1;
	}
	SCROLL_MINVS(pCtrl) = minVisual;
	InvalidateRect((HWND)pCtrl, NULL, TRUE);
	return ret;
}


long GetScrollBarValue(UINT16 parent_id, UINT16 ctrl_id)
{
	INT16	  ret;
	PCONTROL   pCtrl;
	
	if (ret = GetControlPtr(parent_id, ctrl_id, CTRL_SCROLL, &pCtrl))
	{
		return ret;
	}
	return SCROLL_VALUE(pCtrl);
}


long GetScrollBarMaxNum(UINT16 parent_id, UINT16 ctrl_id)
{
	INT16	  ret;
	PCONTROL   pCtrl;
	
	if (ret = GetControlPtr(parent_id, ctrl_id, CTRL_SCROLL, &pCtrl))
	{
		return ret;
	}
	return SCROLL_MAXNUM(pCtrl);
}


long GetScrollBarMinNum(UINT16 parent_id, UINT16 ctrl_id)
{
	INT16	  ret;
	PCONTROL   pCtrl;
	
	if (ret = GetControlPtr(parent_id, ctrl_id, CTRL_SCROLL, &pCtrl))
	{
		return ret;
	}
	return SCROLL_MINNUM(pCtrl);
}


DWORD GetScrollBarStep(UINT16 parent_id, UINT16 ctrl_id)
{
	INT16	  ret;
	PCONTROL   pCtrl;
	
	if (ret = GetControlPtr(parent_id, ctrl_id, CTRL_SCROLL, &pCtrl))
	{
		return ret;
	}
	return SCROLL_STEP(pCtrl);
}


WORD GetScrollBarBorder(UINT16 parent_id, UINT16 ctrl_id)
{
	INT16	  ret;
	PCONTROL   pCtrl;
	
	if (ret = GetControlPtr(parent_id, ctrl_id, CTRL_SCROLL, &pCtrl))
	{
		return ret;
	}
	return SCROLL_BORDER(pCtrl);
}


WORD GetScrollBarMinVisual(UINT16 parent_id, UINT16 ctrl_id)
{
	INT16	  ret;
	PCONTROL   pCtrl;
	
	if (ret = GetControlPtr(parent_id, ctrl_id, CTRL_SCROLL, &pCtrl))
	{
		return ret;
	}
	return SCROLL_MINVS(pCtrl);
}

