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

#define   CHECKBOX_GLOBALS 
#include  "includes.h"


static long CheckboxControlProc (HWND hWnd, long message, WPARAM wParam, LPARAM lParam)
{
	hWnd	= hWnd;
	message = message;
	wParam  = wParam;
	lParam  = lParam;
	
	switch( message ) {
		case  MSG_CREATE:
			break;

		default :
			break;
	}
	
	return DefaultDialogProc(hWnd, message, wParam, lParam);
}

BOOL RegisterCheckboxControl (void)
{
	WNDCLASS WndClass;

	WndClass.spClassName = "checkbox";
	WndClass.dwStyle	 = WS_NONE;
	WndClass.dwExStyle   = WS_EX_NONE;
	WndClass.iBkColor	= GetWindowElementColor (BKC_CONTROL_DEF);
	WndClass.textColor   = GetWindowElementColor (FGC_CONTROL_DEF);
	WndClass.proc		= CheckboxControlProc;

	return AddNewControlClass (&WndClass) == ERR_OK;
}


