#define  GROUPBOX_GLOBALS
#include "includes.h"


static long GroupBoxControlProc(HWND hWnd, long message, WPARAM wParam, LPARAM lParam)
{
	PCONTROL	pCtrl;
	DWORD	   dwStyle;		 
	HDC		 hdc;
	RECT		rcClient;
	HICON	   hIcon;

	pCtrl   = Control(hWnd);
	dwStyle = pCtrl->dwStyle;
	switch (message)
	{
		case MSG_CREATE:
		{
			PGROUPBOXDATA pp;
			pp = (PGROUPBOXDATA)pCtrl->dwAddData2;
		}
			GROUPBOX_STATUS(pCtrl) = 0L;
			break;
	
		case MSG_SETFOCUS:
			{
				GROUPBOX_STATUS(pCtrl) |= GRBT_MARKED;
				InvalidateRect(hWnd, 0, FALSE);
			}
			break;
			
		case MSG_KILLFOCUS:
			{
				GROUPBOX_STATUS(pCtrl) &= ~GRBT_MARKED;
				InvalidateRect(hWnd, 0, FALSE);
			}
			break;

		case MSG_PAINT:
			PaintGroupBox(pCtrl);
			break;


		case MSG_ENABLE:
			if (wParam && (dwStyle & WS_DISABLED))
			{
				pCtrl->dwStyle &= ~WS_DISABLED;
			}
			else if (!wParam && !(dwStyle & WS_DISABLED))
			{
				pCtrl->dwStyle |= WS_DISABLED;
			}
			else 
			{
				return 0;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;

		case MSG_KEYENCODER:
			if (wParam == KEY_KNOB_PRESSED)
			{
				if (pCtrl->dwStyle & GRB_SCROLL)
				{
					if (GROUPBOX_STATUS(pCtrl) & GEN_PRESSED)
					{
						GROUPBOX_STATUS(pCtrl) &= ~GEN_PRESSED;
						NotifyParent(hWnd, pCtrl->id, GRBN_CLICKED);
						SendMessage(hWnd, MSG_SETFOCUS, wParam, lParam);
					}
					else
					{
						GROUPBOX_STATUS(pCtrl) |= GEN_PRESSED;
						NotifyParent(hWnd, pCtrl->id, GRBN_PRESSED);
					}
				}
				else
				{
					NotifyParent(hWnd, pCtrl->id, GRBN_CLICKED);
				}
//				SendMessage(hWnd, GRBN_CLICKED, 0, 0);
			}
			else
			{
				if (pCtrl->dwStyle & GRB_SCROLL)
				{
					if (GROUPBOX_STATUS(pCtrl) & GEN_PRESSED)
					{
						if (wParam == KEY_KNOB_ROTATE_LEFT)
							NotifyParent(hWnd, pCtrl->id, GRBN_KEY_LEFT);
						if (wParam == KEY_KNOB_ROTATE_RIGHT)
							NotifyParent(hWnd, pCtrl->id, GRBN_KEY_RIGHT);
					}
				}
				else
				{
					if (GROUPBOX_STATUS(pCtrl) & GRBT_PRESSED)
						GROUPBOX_STATUS(pCtrl) &= ~GRBT_PRESSED;
				}
			}
			return 0;
			
#if _ENB_TOUCH
		case MSG_TOUCHENCODER:
			{
				if (lParam)
					SendMessage(hWnd, MSG_SETFOCUS, wParam, lParam);
				else
					NotifyParent(hWnd, pCtrl->id, GRBN_CLICKED);
				return;
			}
			break;
#endif

		default :
			break;
	}
	return DefaultDialogProc(hWnd, message, wParam, lParam);
}


BOOL RegisterGroupBoxControl(VOID)
{
	WNDCLASS WndClass;

	WndClass.spClassName = "groupbox";
	WndClass.dwStyle	 = WS_NONE;
	WndClass.dwExStyle   = WS_EX_NONE;
	WndClass.iBkColor	= GetWindowElementColor (BKC_CONTROL_DEF);
	WndClass.textColor   = GetWindowElementColor (FGC_CONTROL_DEF);
	WndClass.proc		= GroupBoxControlProc;

	return AddNewControlClass(&WndClass) == ERR_OK;
}


static grbPaintFocusGroupBox(PCONTROL pctrl, HDC hdc)
{
	RECT	   rc;
	GAL_PIXEL oldPenColor;

	ShowHelpString(pctrl, GROUPBOX_HELPID(pctrl), GROUPBOX_HELPSTR(pctrl));
	GetClientRect((HWND)pctrl, &rc);
	#if _ENB_3D_FRAME
	oldPenColor = SetPenColor(hdc, PIXEL_darkgray);
	Rect(hdc, rc.left + 1, rc.top + 1, rc.right - 1, rc.bottom - 1);
	SetPenColor(hdc, PIXEL_white);
	Rect(hdc, rc.left, rc.top, rc.right, rc.bottom);
	#else
	oldPenColor = SetPenColor(hdc, PIXEL_white);
	Rect(hdc, rc.left, rc.top, rc.right, rc.bottom);
	Rect(hdc, rc.left + 1, rc.top + 1, rc.right - 1, rc.bottom - 1);
	#endif
	SetPenColor(hdc, oldPenColor);
}


static grbPaintNormalGroupBox(PCONTROL pctrl, HDC hdc, BOOL border)
{
	RECT	   rc;
	GAL_PIXEL oldPenColor, oldBrushColor;

	ShowHelpString(pctrl, GROUPBOX_HELPID(pctrl), 0);
	GetClientRect((HWND)pctrl, &rc);
	oldPenColor = SetPenColor(hdc, pctrl->iBkColor);
	//oldPenColor = SetPenColor(hdc, GetWindowElementColor(WEC_EXCOLOR_WHITE));
	Rect(hdc, rc.left, rc.top, rc.right, rc.bottom);
	Rect(hdc, rc.left + 1, rc.top + 1, rc.right - 1, rc.bottom - 1);
	SetPenColor(hdc, oldPenColor);
}

VOID PaintGroupBox(PCONTROL pctrl)
{
	HDC		hdc;
	BOOL	   border, marked, pressed;
	RECT	   rc;
	GAL_PIXEL oldBrushColor;

	hdc	= GetClientDC((HWND)pctrl);
	border = (pctrl->dwStyle & GRB_BORDER)		  == GRB_BORDER;
	marked = (GROUPBOX_STATUS(pctrl) & GRBT_MARKED) == GRBT_MARKED;
	pressed = (GROUPBOX_STATUS(pctrl) & GRBT_PRESSED) == GRBT_PRESSED;
	if (marked)
	{
		grbPaintFocusGroupBox(pctrl, hdc);
	}
	else
	{
		grbPaintNormalGroupBox(pctrl, hdc, border);
	}
	ReleaseDC(hdc);
}
