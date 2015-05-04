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
#if !defined(_INTERNAL_H)
#define	  _INTERNAL_H

// handle type and child type.
#define TYPE_HWND		   0x01
	#define TYPE_MAINWIN	0x11
	#define TYPE_CONTROL	0x12
#define TYPE_HMENU		  0x02
	#define TYPE_MENUBAR	0x21
	#define TYPE_PPPMENU	0x22
	#define TYPE_NMLMENU	0x23
#define TYPE_HACCEL		 0x03
#define TYPE_HCURSOR		0x05
#define TYPE_HICON		  0x07
#define TYPE_HDC			0x08
	#define TYPE_SCRDC	  0x81
	#define TYPE_GENDC	  0x82
	#define TYPE_MEMDC	  0x83

#define TYPE_HTSK		   0x09  /* 任务对象 */

#define TYPE_HJOB		   0x0A  /* 工作对象 */

/* 保证 GDI 操作 是互斥的;  */
#define  GDI_MUTEX_LOCK()		   
#define  GDI_MUTEX_UNLOCK()		 

typedef  long (* MSG_PFN)(HWND parent, HWND crtrl, LPARAM lParam);


typedef struct _msgmap_entry {
	INT32  nMessage;   // windows message
	UINT16 nID;		  // control ID (or 0 for windows messages)
	UINT16 nCode;		// control code or WM_NOTIFY code
	//UINT nSig;		 // signature type (action) or pointer to message #
	MSG_PFN pfn;		 // routine to call (or special value)
} MSGMAP_ENTRY, *PMSGMAP_ENTRY;


BOOL InitScreenDC (VOID);
VOID TerminateScreenDC (VOID);

BOOL InitGDI (VOID);
VOID TerminateGDI (VOID);

BOOL InitWindowElementColors (VOID);

BOOL InitSysFont (VOID);
VOID TermSysFont (VOID);


#endif
