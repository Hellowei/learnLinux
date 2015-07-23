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

#define TYPE_HTSK		   0x09  /* ������� */

#define TYPE_HJOB		   0x0A  /* �������� */

/* ��֤ GDI ���� �ǻ����;  */
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
