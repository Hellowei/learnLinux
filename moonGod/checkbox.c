/*****************************************************************************************
��Ȩ����:			�����ص�
�汾��:				1.0.0
��������:			2011.04.15
�ļ���:				
����:				�����ص�
����˵��:			
����˵��:			��
�����ļ���ϵ:		���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
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


