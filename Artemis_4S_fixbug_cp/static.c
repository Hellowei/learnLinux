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

#define   STATIC_GLOBALS 
#include  "includes.h"

static long StaticControlProc (HWND hWnd, long message, WPARAM wParam, LPARAM lParam)
{
	PCONTROL	pCtrl;
	DWORD	   dwStyle;		 
	HDC		 hdc;
	RECT		rcClient;
	HICON	   hIcon;
	
	pCtrl = Control (hWnd);	
    
	switch (message) {
		case MSG_CREATE:
			pCtrl->dwAddData2 = pCtrl->dwAddData;
			return 0;
			
		case STM_GETIMAGE:
			return (long)(pCtrl->dwAddData2); 
		
		case MSG_GETDLGCODE:
			return DLGC_STATIC;
			
		case STM_SETIMAGE: {
				long pOldValue;
				
				pOldValue  = (long)(pCtrl->dwAddData2);
				if (pOldValue != (long)lParam) {
					pCtrl->dwAddData2 = (DWORD)lParam;
					InvalidateRect (hWnd, NULL, (GetWindowStyle (hWnd) & SS_TYPEMASK) == SS_ICON);
				}
				return pOldValue;
			}

		case MSG_SETITEM:
			pCtrl->dwAddData2 = lParam;
			InvalidateRect(hWnd, 0, TRUE);
			return 0;
		
		case MSG_FONTCHANGED:
			InvalidateRect (hWnd, NULL, TRUE);
			return 0;
			
		case MSG_SETTEXT:
			//if ( pCtrl->caption != (STRINGID)lParam ) {
			{
				SetWindowCaption (hWnd, (INT16)lParam);
				InvalidateRect (hWnd, NULL, TRUE);
			}
			break;

		case MSG_PAINT:
			hdc = GetClientDC (hWnd);
			GetClientRect (hWnd, &rcClient);
			dwStyle = GetWindowStyle (hWnd);
			SetBrushColor (hdc, GetWindowBkColor (hWnd));
			if ((dwStyle & SS_TYPEMASK) != SS_LEFTNOWORDWRAP)
			  FillBox (hdc, 0, 0, rcClient.right, rcClient.bottom);
			switch (dwStyle & SS_TYPEMASK) {
				case SS_BITMAP:
					if ((int)pCtrl->dwAddData2 > 0) {
						Put24Bitmap(hdc, 0, 0, 0, pCtrl->dwAddData2);
						//DrawBitmap(hdc, 0, 0, (pCtrl->dwAddData2));
					 }
					 break;
				
				case SS_ICON:
					if ((int)pCtrl->dwAddData2 >= 0) {
						hIcon = (HICON)(pCtrl->dwAddData2);
						DrawIcon (hdc, 0, 0, hIcon); //DrawIcon (hdc, 0, 0, 0, 0, hIcon);
					}
					break;
	  
				case SS_SIMPLE:
					{						
						if (dwStyle & WS_DISABLED)
							SetTextColor (hdc, PIXEL_darkgray);
						else
							SetTextColor (hdc, Control(hWnd)->textColor);

						SetBkColor (hdc, GetWindowBkColor (hWnd));
						if (pCtrl->caption) {
							TestWinStrLen(strlen(LoadString(pCtrl->caption)), pCtrl->caption);
							TextOut (hdc, 0, 0, LoadString(pCtrl->caption)); 
						}
					}
					break; 

				case SS_LEFTNOWORDWRAP:
					{
					  // 这里只是用来显示对话框的帮助信息，首先清除帮助信息区域
					  //SetBrushColor(hdc, PIXEL_darkgray);
					  FillRect(hdc, rcClient.left, rcClient.top, RECTW(rcClient), RECTH(rcClient));						
					}
					if (pCtrl->caption)
					{
					  INT16 show_len = 0;
					  INT16 show_height = 2;
					  INT16 font_height = GetFontHeight(hdc);
					  CHAR * text = LoadString(pCtrl->caption);
					  INT16 len = strlen(text);
					  CHAR str[512];
					  
					  SetTextColor (hdc, Control(hWnd)->textColor);
					  SetBkColor (hdc, GetWindowBkColor (hWnd));
					  //SetBkColor (hdc, PIXEL_darkgray);
					  while (TRUE)
					  {
						show_len = GetTextOutLenExtent
						(hdc, RECTW(rcClient) - 1, text);
						if (CHINESE == MonitorConfig.language)
						{
							strncpy(str, text, show_len);
						}
						else
						{
//							strncpy(str, text, show_len);
							show_len = CopyWords(str, text, show_len);
						}
						if (len < show_len)
							str[len] = 0;
						else
							str[show_len] = 0;
						TextOut(hdc, 2, show_height, str);

						len -= show_len;
						if (len <= 0)
							break;

						text += show_len;

						show_height += font_height + 2;
						if (show_height > RECTH(rcClient))
							break;
					  }
					}
					break;

				case SS_CENTER:
					if (pCtrl->caption)
					{
						RECT   rc;
						SIZE   size;
						CHAR  *str;

						str = LoadString(pCtrl->caption);
						GetTextExtent(hdc, str, strlen(str), &size);
						GetClientRect(hWnd, &rc);

						// 控件的客户区必须是可以容纳字符串的.调用者保证.
						if (size.cx < RECTW(rc))
							rc.left = rc.left + (RECTW(rc) - size.cx) / 2;
						if (size.cy < RECTH(rc))
							rc.top  = rc.top + (RECTH(rc) - size.cy) / 2;
						SetTextColor (hdc, Control(hWnd)->textColor);
						SetBkColor (hdc, GetWindowBkColor (hWnd));
						
						TestWinStrLen(strlen(str), pCtrl->caption);
						TextOut (hdc, rc.left, rc.top, str); 
					}
					break;

				case SS_RIGHT:
				{
					RECT   rc;
					SIZE   size;
					CHAR  *str;
					str = LoadString(pCtrl->caption);
					GetTextExtent(hdc, str, strlen(str), &size);
					GetClientRect(hWnd, &rc);
					
					// 控件的客户区必须是可以容纳字符串的.调用者保证.
					if (size.cx < RECTW(rc))
						rc.left = rc.left + (RECTW(rc) - size.cx) - 1;
					if (size.cy < RECTH(rc))
						rc.top	= rc.top + (RECTH(rc) - size.cy) / 2;
					SetTextColor (hdc, Control(hWnd)->textColor);
					SetBkColor (hdc, GetWindowBkColor (hWnd));
					
					TestWinStrLen(strlen(str), pCtrl->caption);
					TextOut (hdc, rc.left, rc.top, str); 
				}
					break;
			}
			ReleaseDC(hdc);
			break;
			
		case MSG_KEYENCODER:
			if (wParam == KEY_KNOB_PRESSED) {
				NotifyParent(hWnd, pCtrl->id, STN_CLICKED);
			}
			return 0;

#if _ENB_TOUCH
		case MSG_TOUCHENCODER:
			return 0;
#endif
			
		default :
			break;
	}
	
	return DefaultDialogProc(hWnd, message, wParam, lParam);
}

BOOL RegisterStaticControl (void)
{
	WNDCLASS WndClass;

	WndClass.spClassName = "static";
	WndClass.dwStyle	 = WS_NONE;
	WndClass.dwExStyle   = WS_EX_NONE;
	WndClass.iBkColor	= GetWindowElementColor (BKC_CONTROL_DEF);
	WndClass.textColor   = GetWindowElementColor (FGC_CONTROL_DEF);
	WndClass.proc		= StaticControlProc;

	return AddNewControlClass (&WndClass) == ERR_OK;
}


