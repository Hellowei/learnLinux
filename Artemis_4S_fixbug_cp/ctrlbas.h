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
#if !defined(_CTRLBAS_H)
#define	  _CTRLBAS_H


#define MAXLEN_CLASSNAME	15
typedef struct _CTRLCLASSINFO {
	char	  name[MAXLEN_CLASSNAME]; // class name
	/*
	 * common properties of this class
	 */
	DWORD	 dwStyle;		  // Default control styles.
	DWORD	 dwExStyle;		// Default control extended styles.

	GAL_PIXEL iBkColor;		 // control background color.
	GAL_PIXEL textColor;
	WNDPROC   proc;			 // control procedure.
	DWORD	 dwAddData;		// the additional data.
}CTRLCLASSINFO;
typedef CTRLCLASSINFO* PCTRLCLASSINFO;

struct  _window;
struct  _CONTROL;

typedef struct _CONTROL
{
	/*
	 * These fields are similiar with MAINWIN struct.
	 */
	CHAIN_NODE	  node;
	INT16		   dataType;		   // the data type
	INT16		   winType;			// the window type

	INT32		   left, top;		  // the position of control in main window's
	INT32		   right, bottom;	  // client area.
	INT32		   cl, ct;			 // the positio of control client in main window's
	INT32		   cr, cb;			 // client area.
	
	CHAIN_CONTROL   subWinList;
	WNDPROC		 ctrlProc;

	DWORD		   dwStyle;			// the styles of child window.
	DWORD		   dwExStyle;		  // the extended styles of child window.

	GAL_PIXEL	   iBkColor;			// the background color.
	GAL_PIXEL	   textColor;
	PLOGFONT		pLogFont;		   // pointer to logical font.

	DWORD		   dwAddData;		  // the additional data.
	DWORD		   dwAddData2;		 // the second addtional data.

	STRINGID		caption;			// the caption of control.
	INT16		   id;				 // the identifier of child window.
	STRINGID		helpid;
	INT16		   fblayer;
	struct _window  * pMainWin;		 // the main window that contains this control.
	struct _CONTROL * pParent;		  // the parent of this control.

	struct _CONTROL * active;		   // the active child control.

	/*
	 * The following members are only implemented for control.
	 */
	PCTRLCLASSINFO  pcci;	 // pointer to Control Class Info struct.
}CONTROL, * PCONTROL;

struct _WNDCLASS;

BOOL  InitControlClass (VOID);
VOID  TerminateControlClass (VOID);

PCTRLCLASSINFO GetControlClassInfo (const char* szClassName);
INT			AddNewControlClass (struct _WNDCLASS *pWndClass);
PCONTROL Control (HWND hWnd);   // check whether hWnd is control
								// and return pointer to control hWnd.

BOOL RegisterStaticControl (void);
BOOL RegisterButtonControl (void);
BOOL RegisterEditControl (void);
BOOL RegisterListboxControl (void);
BOOL RegisterCheckboxControl (void);
INT32 ShowHelpString(PCONTROL pCtrl, int id, int str);
BOOL SetHelpStringID(HWND hWnd, int helpid, int strid);

#endif

