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
#ifndef  _DC_H
#define  _DC_H

#define TYPE_HWND	   0x01
#define TYPE_MAINWIN	0x11
#define TYPE_CONTROL	0x12
#define TYPE_HMENU	  0x02
#define TYPE_MENUBAR	0x21
#define TYPE_PPPMENU	0x22
#define TYPE_NMLMENU	0x23
#define TYPE_HACCEL	 0x03
#define TYPE_HCURSOR	0x05
#define TYPE_HICON	  0x07
#define TYPE_HDC		0x08
#define TYPE_SCRDC	  0x81
#define TYPE_GENDC	  0x82
#define TYPE_MEMDC	  0x83

#define TYPE_HTSK	   0x09  /* ������� */
#define TYPE_HJOB	   0x0A  /* �������� */

#define DCSLOTNUMBER		8

//struct tagDC;

// Device Context
typedef struct tagDC
{
	INT16 DataType;  /* the data type, always be TYPE_HDC */
	INT16 DCType;	/* the dc type */
		
	BOOL  inuse;
	HWND  hwnd;
	
	/* graphics context */
	PSD   scrdev;	//GAL_GC gc;

	/* background color and mode */
	GAL_PIXEL  bkcolor;
	INT32	  bkmode;

	/* pen attributes */
	GAL_PIXEL pencolor;
	INT32	 pentype;

	/* brush attributes */
	GAL_PIXEL brushcolor;
	INT32	 brushtype;

	/* text attibutes */
	GAL_PIXEL textcolor;
	//GAL_PIXEL textbkcolor;

	POINT	 CurPenPos;
	RECT	  DevRC;	 //DC��ʾ���豸����;����Ӧ������Ļ��Ļ�ϵ�����.

	BOOL	  bIsClient;
	PLOGFONT  pLogFont;
	void * mutex;
}DC, * PDC;

//typedef struct tagDC ;
//typedef struct tagDC * PDC;

extern DC __mg_screen_dc;

// This function convert HDC to PDC.
PDC  dc_HDC2PDC (HDC hdc);
BOOL dc_IsMemHDC (HDC hdc);
BOOL dc_IsScreenHDC (HDC hdc);
BOOL dc_IsGeneralHDC (HDC hdc);
BOOL dc_IsMemDC (PDC pdc);
BOOL dc_IsScreenDC (PDC pdc);
BOOL dc_IsGeneralDC (PDC pdc);
BOOL dc_IsVisible (PDC pdc);
VOID coor_DP2SP(PDC pdc, INT32 * x, INT32 * y);
VOID coor_SP2DP(PDC pdc, INT32 * x, INT32 * y);
VOID coor_LP2SP(PDC pdc, INT32 * x, INT32 * y);
VOID coor_SP2LP(PDC pdc, INT32 * x, INT32 * y);


#endif
