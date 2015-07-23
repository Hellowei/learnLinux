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

#define   CTRLBAS_GLOBALS 
#include  "includes.h"

static CTRLCLASSINFO ccitable[] = {
/*   name:			 style:  exStyle: bkcolor: proc: dwAddData*/
	{CTRL_STATIC,	  0,	  0,	   0,	   0,	0   },
	{CTRL_BUTTON,	  0,	  0,	   0,	   0,	0   },
	{CTRL_EDIT,		0,	  0,	   0,	   0,	0   },
	{CTRL_CHECKBOX,	0,	  0,	   0,	   0,	0   },
	{CTRL_LISTBOX,	 0,	  0,	   0,	   0,	0   },
	{CTRL_SPINBOX,	 0,	  0,	   0,	   0,	0   },  
	{CTRL_GROUPBOX,	0,	  0,	   0,	   0,	0   },  
	{CTRL_SCROLL,	  0,	  0,	   0,	   0,	0   },  
};

#define  NR_SYS_CCITABLE  TABLESIZE(ccitable)

PCONTROL Control (HWND hWnd)
{
	PCONTROL pCtrl;

	pCtrl = (PCONTROL) hWnd;

	if (pCtrl && pCtrl->winType == TYPE_CONTROL)
		return pCtrl;

	return NULL;
}

INT AddNewControlClass (struct _WNDCLASS * pWndClass)
{
	PCTRLCLASSINFO cciP;
	char szClassName [MAXLEN_CLASSNAME + 2];
	int i=0;

	strncpy (szClassName, pWndClass->spClassName, MAXLEN_CLASSNAME + 1);

	if (!isalpha (szClassName[0])) 
		return ERR_CTRLCLASS_INVNAME;
	
	while (szClassName[i]) {
		szClassName[i] = tolower(szClassName[i]);

		i++;
		if (i > MAXLEN_CLASSNAME)
			return ERR_CTRLCLASS_INVLEN;
	}
	for ( i = 0; i < NR_SYS_CCITABLE; i ++ ) {
		cciP = ccitable + i;
		if (strcmp (szClassName, cciP->name) == 0) 
			break; //原来已经有保存，则覆盖它；
		if (0==strlen(cciP->name) )				
			break; //空项；
	}
	
	if (i >= NR_SYS_CCITABLE) {
		 return ERR_CTRLCLASS_MEM; //没有足够内存供保存；
	}
	
	cciP = &ccitable[i];
	strcpy (cciP->name, szClassName);
	cciP->dwStyle	 = pWndClass->dwStyle;
	cciP->dwExStyle   = pWndClass->dwExStyle;
	cciP->iBkColor	= pWndClass->iBkColor;
	cciP->textColor   = pWndClass->textColor;
	cciP->proc		= pWndClass->proc;
	cciP->dwAddData   = pWndClass->dwAddData;
	
	return ERR_OK;
}


BOOL InitControlClass (VOID)
{
	// Register system controls here.
#ifdef _CTRL_STATIC
	if (!RegisterStaticControl ())
		return FALSE;
#endif

#ifdef _CTRL_BUTTON
	if (!RegisterButtonControl())
		return FALSE;
#endif

#ifdef _CTRL_EDIT
	if (!RegisterEditControl())
		return FALSE;
#endif

#ifdef _CTRL_LISTBOX
	if (!RegisterListboxControl())
		return FALSE;
#endif

#ifdef _CTRL_CHECKBOX
	if (!RegisterCheckboxControl())
		return FALSE;
#endif

#ifdef _CTRL_SPINBOX
	if (!RegisterSpinboxControl())
		return FALSE;
#endif

#if _CTRL_GROUPBOX
	if (!RegisterGroupBoxControl())
		return FALSE;   
#endif

#if _CTRL_SCROLLBAR
	if (!RegisterScrollBarControl())
		return FALSE;
#endif

  return TRUE;
}

PCTRLCLASSINFO GetControlClassInfo (const char* szClassName)
{
	PCTRLCLASSINFO  cciP;
	int			 i;
	char szName [MAXLEN_CLASSNAME + 1];

	if (szClassName == NULL) 
		return NULL;

	strncpy (szName, szClassName, MAXLEN_CLASSNAME);

	if (!isalpha (szName[0])) 
		return NULL;

	i = 0;
	while (szName[i]) {
		szName[i] = tolower(szName[i]);

		i++;
	}
	
	for (i = 0; i < NR_SYS_CCITABLE; i++) {
		cciP = ccitable + i;
		if (strcmp (szClassName, cciP->name) == 0) 
			break; 
	}
	
	if (i >= NR_SYS_CCITABLE) {
		 return NULL; 
	}
	
	cciP = &ccitable[i];
	
	return cciP;
}

INT32 NotifyParent(HWND hwnd, INT16 id, INT16 code)
{
	return PostMessage (GetParent(hwnd),
						MSG_COMMAND,
						MAKEWPARAM(id, code),
						(LPARAM)hwnd);
}

BOOL SetHelpStringID(HWND hWnd, int helpid, int strid)
{
	char txt[16];
	PCONTROL pCtrl = (PCONTROL)hWnd;
	strncpy(txt , GetClassName(hWnd), MAXLEN_CLASSNAME);
	if (0 == strcmp(txt, CTRL_BUTTON))
	{
		BUTTON_HELPID(pCtrl) = helpid;
		BUTTON_HELPSTR(pCtrl) = strid;
		return TRUE;
	}
	if (0 == strcmp(txt, CTRL_LISTBOX))
	{
		LISTBOX_HELPID(pCtrl) = helpid;
		LISTBOX_HELPSTR(pCtrl) = strid;
		return TRUE;
	}
	if (0 == strcmp(txt, CTRL_SPINBOX))
	{
		LISTBOX_HELPID(pCtrl) = helpid;
		LISTBOX_HELPSTR(pCtrl) = strid;
		return TRUE;
	}
	if (0 == strcmp(txt, CTRL_GROUPBOX))
	{
		GROUPBOX_HELPID(pCtrl) = helpid;
		GROUPBOX_HELPSTR(pCtrl) = strid;
		return TRUE;
	}
	if (0 == strcmp(txt, CTRL_SCROLL))
	{
		SCROLL_EXHID(pCtrl) = helpid;
		SCROLL_EXSTR(pCtrl) = strid;
		return TRUE;
	}
	return FALSE;
}


INT32 ShowHelpString(PCONTROL pCtrl, int id, int str)
{
	HWND hWnd;
//	if (pCtrl)
//	{
//		if (pCtrl->pMainWin)
//		{
//			if (hWnd = GetDlgItem((HWND)(pCtrl->pMainWin), id))
//			{
//				SetWindowText(hWnd, str);
//				return ERR_OK;
//			}
//		}
//	}
	if (MonitorConfig.showHelp == FALSE)
	{
		return ERR_OK;
	}
	hWnd = GetDlgItem(MainScnHWnd, id);
	if (hWnd)
	{
		SetWindowText(hWnd, str);
		return ERR_OK;
	}
	return ERR_CTRLID_NOT_EXIST;
}


