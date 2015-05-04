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

#define   GDI_GLOBALS 
#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "gal.h"
#include "gdi.h"
#include "dc.h"
#include "devfont.h"
#include "includes.h"

DC __mg_screen_dc;

// General DC
static DC DCSlot [DCSLOTNUMBER];

// mutex ensuring exclusive access to DC slot. 
// 由于绘制波形和一般的gui处理过程不在一个任务;所以,必须保护DC.

#define  DC_ENTER_CRITICAL()   pthread_mutex_lock(&DcUseSem)
#define  DC_EXIT_CRITICAL()	  pthread_mutex_unlock(&DcUseSem)


// mutex ensuring exclusive access to gdi. 
// pthread_mutex_t __mg_gdilock;

GAL_PIXEL SysPixelIndex [17];

// This should be the standard EGA palette.
const RGB SysPixelColor [] = {
	// r,  g,	b
	{0x00, 0x00, 0x00, 0xEA},	 // transparent   --0
	{0x00, 0x00, 0x80},	 // dark blue	 --1
	{0x00, 0x80, 0x00},	 // dark green	--2
	{0x00, 0x80, 0x80},	 // dark cyan	 --3
	{0x80, 0x00, 0x00},	 // dark red	  --4
	{0x80, 0x00, 0x80},	 // dark magenta  --5
	{0x80, 0x80, 0x00},	 // dark yellow   --6
	{0x80, 0x80, 0x80},	 // dark gray	 --7
	{0xC0, 0xC0, 0xC0},	 // light gray	--8
	{0x00, 0x00, 0xFF},	 // blue		  --9
	{0x00, 0xFF, 0x00},	 // green		 --10
	{0x00, 0xFF, 0xFF},	 // cyan		  --11
	{0xFF, 0x00, 0x00},	 // red		   --12
	{0xFF, 0x00, 0xFF},	 // magenta	   --13
	{0xFF, 0xFF, 0x00},	 // yellow		--14
	{0xFF, 0xFF, 0xFF},	 // light white   --15
	{0x00, 0x00, 0x00}	  // black		 --16
};

// This function convert HDC to PDC.
PDC dc_HDC2PDC (HDC hdc)
{
	if (hdc == HDC_SCREEN) 
		return &__mg_screen_dc;
		
	return (PDC) hdc;
}

BOOL dc_IsMemHDC (HDC hdc)
{
	if (hdc == HDC_SCREEN) 
		return FALSE;
		
	return (((PDC)hdc)->DCType == TYPE_MEMDC);
}

BOOL dc_IsGeneralHDC (HDC hdc)
{
	if (hdc == HDC_SCREEN) 
		return FALSE;
		
	return (((PDC)hdc)->DCType == TYPE_GENDC);
}

BOOL dc_IsVisible (PDC pdc)
{
	PCONTROL pCtrl;
	
	if (pdc->DCType != TYPE_GENDC)
		return TRUE;
	
	if (pdc->hwnd == HWND_DESKTOP)
		return TRUE;
 
	pCtrl = (PCONTROL)(pdc->hwnd);

	do {
		if (!(pCtrl->dwStyle & WS_VISIBLE))
			return FALSE;

		pCtrl = pCtrl->pParent;
	} while (pCtrl);
	return TRUE;
}

/**
** \brief  设备坐标 转 屏幕坐标
**/
VOID coor_DP2SP(PDC pdc, INT32* x, INT32* y)
{
	if (pdc->DCType != TYPE_GENDC)
		return;

	*x += pdc->DevRC.left;
	*y += pdc->DevRC.top;
}

/**
**  \brief  屏幕坐标 转 设备坐标 
**/
VOID coor_SP2DP(PDC pdc, INT32* x, INT32* y)
{
	if (pdc->DCType != TYPE_GENDC)
		return;

	*x -= pdc->DevRC.left;
	*y -= pdc->DevRC.top;
}

/**
** \brief  逻辑坐标 转 屏幕坐标
**/
VOID coor_LP2SP(PDC pdc, INT32* x, INT32* y)
{
	if (pdc == &__mg_screen_dc)
		return;

	*x += pdc->DevRC.left;
	*y += pdc->DevRC.top;
}

/**
**
**/
VOID coor_SP2LP(PDC pdc, INT32* x, INT32* y)
{
	if (pdc == &__mg_screen_dc)
		return;

	*x -= pdc->DevRC.left;
	*y -= pdc->DevRC.top;
}

/* 取得指定窗口在所属底层窗口客户区的坐标矩形 */
static VOID WndRect(HWND hWnd, PRECT prc)
{
	PCONTROL pParent;
	PCONTROL pCtrl;

	pParent = pCtrl = (PCONTROL) hWnd;

	if (hWnd == HWND_DESKTOP) {
		*prc = g_rcScr;
		return;
	}

	prc->left   = pCtrl->left;
	prc->top	= pCtrl->top;
	prc->right  = pCtrl->right;
	prc->bottom = pCtrl->bottom;

	pParent = pParent->pParent;
	while (pParent) {
		prc->left   += pParent->cl;
		prc->top	+= pParent->ct;
		prc->right  += pParent->cl;
		prc->bottom += pParent->ct;
		pParent	  = pParent->pParent;
	}
}

/* 取得指定窗口客户区在所属底层窗口客户区的坐标矩形 */
static VOID WndClientRect(HWND hWnd, PRECT prc)
{
	PCONTROL pCtrl;
	PCONTROL pParent;
	pParent = pCtrl = (PCONTROL) hWnd;

	if (hWnd == HWND_DESKTOP) {
		*prc = g_rcScr;
		return;
	}

	prc->left   = pCtrl->cl;
	prc->top	= pCtrl->ct;
	prc->right  = pCtrl->cr;
	prc->bottom = pCtrl->cb;
	
	pParent = pParent->pParent;
	while (pParent) {
		prc->left   += pParent->cl;
		prc->top	+= pParent->ct;
		prc->right  += pParent->cl;
		prc->bottom += pParent->ct;
		pParent	  = pParent->pParent;
	}
}
 
// This function init DC.
// set the default parameters.
static VOID dc_InitDC(PDC pdc, HWND hWnd, BOOL bIsClient)
{
	UINT8 err;

	pdc->hwnd	= hWnd;
	pdc->scrdev  = &scrdev;

	pdc->bkcolor = PIXEL_black;
	pdc->bkmode  = 0;

	pdc->brushtype  = BT_SOLID;
	pdc->brushcolor = PIXEL_lightwhite;

	pdc->pentype  = PT_SOLID;
	pdc->pencolor = PIXEL_lightwhite;
	pdc->CurPenPos.x = pdc->CurPenPos.y = 0;

	pdc->textcolor   = PIXEL_lightwhite;
	//pdc->textbkcolor = PIXEL_black;
	pdc->pLogFont = GetWindowFont (hWnd);
	if (!(pdc->pLogFont))
		pdc->pLogFont = GetSystemFont (SYSLOGFONT_SMAFONT);

	/* todo: 保护, 原子操作 ;互斥量加锁 */
	DC_ENTER_CRITICAL();
	
	pdc->bIsClient = bIsClient;
	if (bIsClient)
		WndClientRect (pdc->hwnd, &pdc->DevRC);
	else
		WndRect (pdc->hwnd, &pdc->DevRC);
	
	/* todo: 保护, 原子操作   ;互斥量解锁*/
	DC_EXIT_CRITICAL();

}

static VOID dc_Init_ScreenDC (VOID)
{
	int i;
	__mg_screen_dc.DataType = TYPE_HDC;
	__mg_screen_dc.DCType   = TYPE_SCRDC;
	__mg_screen_dc.hwnd	 = 0;
	__mg_screen_dc.scrdev   = &scrdev;

	__mg_screen_dc.bkcolor = PIXEL_black;
	__mg_screen_dc.bkmode  = 0;

	__mg_screen_dc.brushtype  = BT_SOLID;
	__mg_screen_dc.brushcolor = PIXEL_yellow;

	__mg_screen_dc.pentype  = PT_SOLID;
	__mg_screen_dc.pencolor = PIXEL_cyan;
	__mg_screen_dc.CurPenPos.x = __mg_screen_dc.CurPenPos.y = 0;

	__mg_screen_dc.textcolor  = PIXEL_lightwhite;
	__mg_screen_dc.pLogFont  = GetSystemFont (SYSLOGFONT_SMAFONT);

	__mg_screen_dc.bIsClient = FALSE;

	__mg_screen_dc.DevRC.left   = 0;
	__mg_screen_dc.DevRC.top	= 0;
	__mg_screen_dc.DevRC.right  = WIDTHOFPHYGC - 1;
	__mg_screen_dc.DevRC.bottom = HEIGHTOFPHYGC - 1;

	for (i = 0; i < DCSLOTNUMBER; ++ i)
	{
		DCSlot[i].mutex = (void*)CreateMutex();
	}

}

BOOL InitGDI (void)
{   
	if (!InitDeviceFonts ()) 
	{
		errprintf ("GDI: Can not initialize device fonts!\n");
		goto error;
	}
	EXIT_PROC(TermDeviceFonts);

	/* TODO: add other font support here */
	if (!InitSysFont ()) 
	{
		errprintf ("GDI: Can not create system fonts!\n");
		goto error;
	}

	dc_Init_ScreenDC ();

	return TRUE;

error:
	return FALSE;
}


/*
 * Function: HDC GUIAPI GetClientDC(HWND hWnd)
 *	 This function get the specified window client's DC.
 * Parameter:
 *	 HWND hWnd: The window, 0 for screen.
 * Return:
 *	 The handle of wanted DC.
 */

HDC GUIAPI GetClientDC(HWND hWnd)
{
	INT32 i;
	UINT8 err;

	DC_ENTER_CRITICAL();//会阻塞任务
	for (i = 0; i < DCSLOTNUMBER; i++) {
		if (!DCSlot[i].inuse) {
			DCSlot[i].inuse = TRUE;
			DCSlot[i].DataType = TYPE_HDC;
			DCSlot[i].DCType   = TYPE_GENDC;
			break;
		}
	}
	DC_EXIT_CRITICAL();

	if (i >= DCSLOTNUMBER)
		return HDC_SCREEN;

	dc_InitDC (DCSlot + i, hWnd, TRUE);

	//GET_GUI_PERMIT();
	pthread_mutex_lock(DCSlot[i].mutex);

	return (HDC) (DCSlot + i);
}

/*
 * Function: HDC GUIAPI GetDC(HWND hWnd)
 *	 This function get the specified window's DC.
 * Parameter:
 *	 HWND hWnd: The window, 0 for screen.
 * Return:
 *	 The handle of wanted DC.
 */

HDC GUIAPI GetDC(HWND hWnd)
{
	INT32 i;
	UINT8 err;

	// allocate an empty dc slot exclusively   
	DC_ENTER_CRITICAL();//会阻塞任务
	for(i = 0; i < DCSLOTNUMBER; i++) {
		if(!DCSlot[i].inuse) {
			DCSlot[i].inuse = TRUE;
			DCSlot[i].DataType = TYPE_HDC;
			DCSlot[i].DCType   = TYPE_GENDC;
			break;
		}
	}
	DC_EXIT_CRITICAL();

	if (i >= DCSLOTNUMBER) {
		return HDC_SCREEN;
	}
	dc_InitDC(DCSlot + i, hWnd, FALSE);

	//GET_GUI_PERMIT();
	pthread_mutex_lock(DCSlot[i].mutex);	
	
	return (HDC)(DCSlot + i);
}

/*
 * Function: VOID GUIAPI ReleaseDC(HDC hDC)
 *	 This function release the specified DC.
 * Parameter:
 *	 HDC hDC: The DC handle want to release.
 * Return:
 *	 None. 
 */
VOID GUIAPI ReleaseDC (HDC hDC)
{
	PDC	pdc;
	UINT8  err;

	pdc = dc_HDC2PDC(hDC);

	//RELEASE_GUI_PERMIT();
	pthread_mutex_unlock(pdc->mutex);


	DC_ENTER_CRITICAL();
	pdc->inuse = FALSE;
	DC_EXIT_CRITICAL();// 会释放任务
}
