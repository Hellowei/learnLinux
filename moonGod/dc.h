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

#define TYPE_HTSK	   0x09  /* 任务对象 */
#define TYPE_HJOB	   0x0A  /* 工作对象 */

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
	RECT	  DevRC;	 //DC表示的设备矩形;它反应了在屏幕屏幕上的坐标.

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
