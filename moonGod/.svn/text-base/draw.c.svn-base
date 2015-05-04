/******************************************************************************
***********
版权所有:			和心重典
版本号:				1.0.0
生成日期:			2010.05.11
文件名:				
作者:				ZONDAN
功能说明:			应用层主文件
其它说明:			
*	   GDI draw function. 
所属文件关系:		本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*******************************************************************************
**********/
#define   DRAW_GLOBALS 

#include "includes.h"
#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "gal.h"
#include "gdi.h"
#include "dc.h"
#include "myfb.h"


#define DRAW_TEST   0

//#define  GRAPH_FILL_COLOR(c)	 /*设置填充色*/
//#define  GRAPH_PEN_COLOR(c)
//#define  GRAPH_TEXT_COLOR(c)


/**
**
**/
VOID GUIAPI SetPixel(HDC hdc, INT32 x, INT32 y, GAL_PIXEL c)
{
	PDC	 pdc   = dc_HDC2PDC(hdc);
	GAL_COLOR  color;
	PMAINWIN pWin = (PMAINWIN)(pdc->hwnd);
	int fb_level = 0;
	if (pWin != NULL)
		fb_level = pWin->fblayer;
	
	coor_LP2SP(pdc, &x, &y);
	if (PtInRect(&(pdc->DevRC), x, y)) 
	{
		UnmapPixel(pdc->scrdev, c, &color);
		fb_setpixel(fb_level, x, y, color.r, color.g, color.b);
	}
}

/**
**
**/
GAL_PIXEL GUIAPI GetPixel(HDC hdc, INT32 x, INT32 y)
{
	PDC	 pdc   = dc_HDC2PDC(hdc);
	
	coor_LP2SP(pdc, &x, &y);
	
	if (PtInRect(&(pdc->DevRC), x, y)) {
		GAL_COLOR  c;
		fb_getpixel(x, y, &(c.r), &(c.g), &(c.b));
		return MapColor(pdc->scrdev, &c);
	}
	else {
		return (-1);
	}
}

/**
**
**/
GAL_PIXEL GUIAPI SetPixelRGB(HDC hdc, INT32 x, INT32 y, UINT8 r, UINT8 g, UINT8 b)
{
	GAL_COLOR c;
	PDC		pdc   = dc_HDC2PDC(hdc);
	PMAINWIN pWin = (PMAINWIN)(pdc->hwnd);
	int fb_level = 0;
	if (pWin != NULL)
		fb_level = pWin->fblayer;
	
	coor_LP2SP(pdc, &x, &y);
	if (PtInRect(&(pdc->DevRC), x, y )) {
	fb_setpixel(fb_level, x, y, r, g, b);
	}

	c.r = r;
	c.g = g;
	c.b = b;
	return MapColor(pdc->scrdev, &c);
}

/**
**
**/
GAL_PIXEL GUIAPI GetPixelRGB(HDC hdc, INT32 x, INT32 y, UINT8* r, UINT8* g, UINT8* b)
{
	PDC		pdc   = dc_HDC2PDC(hdc);
	GAL_COLOR  c;
	GAL_PIXEL  pixel = GetPixel(hdc, x, y);

	UnmapPixel(pdc->scrdev, pixel, &c);

	*r = c.r;
	*g = c.g;
	*b = c.b;

	return  pixel;
}


VOID GUIAPI MoveTo (HDC hdc, INT32 x, INT32 y)
{
	PDC	 pdc   = dc_HDC2PDC(hdc);
	
	coor_LP2SP(pdc, &x, &y);
	if (PtInRect(&(pdc->DevRC), x, y)) {
		pdc->CurPenPos.x = x;
		pdc->CurPenPos.y = y;
	}
}

/**
** \note  线条的颜色是当前DC的pencolor
**/
VOID GUIAPI LineTo (HDC hdc, INT32 x, INT32 y)
{
	PDC	 pdc   = dc_HDC2PDC(hdc);
	long	startx, starty;
	GAL_COLOR  c;
	PMAINWIN pWin = (PMAINWIN)(pdc->hwnd);
	int fb_level = 0;
	if (pWin != NULL)
		fb_level = pWin->fblayer;
	
	startx = startx;
	starty = starty;
	
	startx = pdc->CurPenPos.x;
	starty = pdc->CurPenPos.y;

	UnmapPixel(pdc->scrdev, pdc->pencolor, &c);	
	
	coor_LP2SP(pdc, &x, &y);
	if (PtInRect(&(pdc->DevRC), x, y)) {
		pdc->CurPenPos.x = x;
		pdc->CurPenPos.y = y;

		//GRAPH_TEXT_COLOR(pdc->pencolor);
	 UnmapPixel(pdc->scrdev, pdc->pencolor, &c);
	 fb_line(fb_level, startx, starty, x, y, c.r, c.g, c.b);
	}
}

/**
** \note  线条的颜色是当前DC的pencolor
**/
VOID GUIAPI Line (HDC hdc, INT32 x0, INT32 y0, INT32 x1, INT32 y1)
{
	PDC	 pdc   = dc_HDC2PDC(hdc);
	GAL_COLOR  c;
	PMAINWIN pWin = (PMAINWIN)(pdc->hwnd);
	int fb_level = 0;
	if (pWin != NULL)
		fb_level = pWin->fblayer;
	
	UnmapPixel(pdc->scrdev, pdc->pencolor, &c);	
	
	coor_LP2SP(pdc, &x0, &y0);
	coor_LP2SP(pdc, &x1, &y1);
	if (PtInRect(&(pdc->DevRC), x0, y0) && (PtInRect(&(pdc->DevRC), x1, y1 - 2) || PtInRect(&(pdc->DevRC), x1, y1))) 
	{
		//GRAPH_PEN_COLOR(pdc->pencolor);
	 UnmapPixel(pdc->scrdev, pdc->pencolor, &c);
	 fb_line(fb_level, x0, y0, x1, y1, c.r, c.g, c.b);
	}
}

/**
** \note  线条的颜色是当前DC的pencolor
**/
VOID GUIAPI LineXorVs (HDC hdc, INT32 y0, INT32 y1, INT32 x)
{
	GAL_PIXEL  color;
	PDC		pdc   = dc_HDC2PDC(hdc);
	INT32	  start_y, end_y;
	INT32	  x1 = x;
	
	coor_LP2SP(pdc, &x, &y0);
	coor_LP2SP(pdc, &x1, &y1);
	if (PtInRect(&(pdc->DevRC), x, y0) && PtInRect(&(pdc->DevRC), x1, y1)) {

		coor_SP2LP(pdc, &x, &y0);
		coor_SP2LP(pdc, &x1, &y1);
		if (y0 > y1) {
			start_y = y1;
			end_y   = y0;
		} else {
			start_y = y0;
			end_y   = y1;
		}
		for (; start_y <= end_y; start_y++) {
			color = GetPixel(hdc, x, start_y);
			color ^= pdc->pencolor;
			PutPixel(hdc, x, start_y, color);
		}
	}

}

#define Mixer(a, b, cent) ((a * cent / 100) + (b * (100 - cent) / 100))
	
#define ALPHA_MIXER(fore, back, cent) \
	(((Mixer((fore >> 16) & 0xff, ((back >> 16) & 0xff) , cent)) << 16) \
	|((Mixer((fore >>  8) & 0xff, ((back >>  8) & 0xff) , cent)) <<  8) \
	| (Mixer((fore & 0xff)	  , (back & 0xff)		 , cent))	   )
	
/* 函数说明:Bresenham快速画直线算法
 * 代码来源:
 * http://www.cnblogs.com/pheye/archive/2010/08/14/1799803.html
 * 移入时间: 2013-5-14 9:50:43
 */
void GUIAPI DrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
	GAL_PIXEL   c;
	PDC		 pdc = dc_HDC2PDC(hdc);
	int dx = x2 - x1;
	int dy = y2 - y1;
	int ux = ((dx > 0) << 1) - 1;   //x的增量方向，取或-1
	int uy = ((dy > 0) << 1) - 1;   //y的增量方向，取或-1
	int x  = x1, y = y1, eps;	   //eps为累加误差

	c   = pdc->pencolor;
	eps = 0;
	dx  = ABS(dx);
	dy  = ABS(dy); 
	if (dx > dy) 
	{
		for (x = x1; x != x2; x += ux)
		{
			SetPixel(hdc, x, y, c);
			eps += dy;
			if ((eps << 1) >= dx)
			{
				y += uy;
				eps -= dx;
			}
		}
	}
	else
	{
		for (y = y1; y != y2; y += uy)
		{
			SetPixel(hdc, x, y, c);
			eps += dx;
			if ((eps << 1) >= dy)
			{
				x += ux;
				eps -= dy;
			}
		}
	}			 
}

//对称得到整个圆
static void 
	CirPot(HDC hdc, int cx, int cy, int x, int y, char r, char g, char b)
{
	fb_set_pixel_ex(hdc, (cx+x),(cy+y), r, g, b);
	fb_set_pixel_ex(hdc, (cx+y),(cy+x), r, g, b);
	fb_set_pixel_ex(hdc, (cx+y),(cy-x), r, g, b);
	fb_set_pixel_ex(hdc, (cx+x),(cy-y), r, g, b);
	fb_set_pixel_ex(hdc, (cx-x),(cy-y), r, g, b);
	fb_set_pixel_ex(hdc, (cx-y),(cy-x), r, g, b);
	fb_set_pixel_ex(hdc, (cx-y),(cy+x), r, g, b);
	fb_set_pixel_ex(hdc, (cx-x),(cy+y), r, g, b);
}

//Bresenham法画圆
void GUIAPI DrewCircle(HDC hdc, int cx, int cy, int r, GAL_COLOR *c)
{
	int x=0,y=r,F=3-2*r;
	while(x < y)
	{
		CirPot(hdc, cx,cy,x,y, c->r, c->g, c->b);
		if(F<0)
			F += 4*x+6;
		else
		{
			F += 4*(x-y)+10;
			y--;
		}
		x++;
	}
	if (x == y)
		CirPot(hdc, cx,cy,x,y, c->r, c->g, c->b);
}

/*******************************************************************************
Name	:D3DLine
Function:
使用限制: 线长度必须大于线宽，否则可能导致曲线不连续
Input   : width:line width
Require : dc_HDC2PDC GetPixel SetPixel
*******************************************************************************/
VOID GUIAPI D3DLine(HDC hdc, int width, int x1, int y1, int x2, int y2)
{
	if (width < 1)
		return;
	GAL_PIXEL forecolor, backcolor;
	PDC pdc = dc_HDC2PDC(hdc);
	int dx  = x2 - x1;
	int dy  = y2 - y1;
	int x;
	int y;
	
	forecolor = pdc->pencolor;
	dx  = ABS(dx);
	dy  = ABS(dy);
	
	if (dx == 0)
	{
		x = x1 - (width >> 1);
		y = (y1  < y2) ? y1 : y2;
		GAL_PIXEL color = SetBrushColor(hdc, forecolor);
		FillRect(hdc, x, y, width, dx);
		SetBrushColor( hdc, color);
		return;
	}
	
	if (dy == 0)
	{
		x = (x1 < x2) ? x1 : x2;
		y = y1 - (width >> 1);
		GAL_PIXEL color = SetBrushColor(hdc, forecolor);
		FillRect(hdc, x, y, dx, width);
		SetBrushColor( hdc, color);
		return;
	}
	
	int dw = (width + 1) / 2;
	int ux = (x1 < x2) ? 1 : -1;   //x的增量方向，取1或-1
	int uy = (y1 < y2) ? 1 : -1;   //y的增量方向，取1或-1
	int i;
	int dec;
	int pos;
	if (dx > dy) 
	{
		for (x = x1; x != x2; x += ux) //以x为变量，计算y值
		{
			pos = y1 * 100 +  (x - x1) * uy * dy * 100 / (ux * dx);
			y = pos / 100;
			dec = pos % 100;
			backcolor = GetPixel(hdc, x, y - dw);
			SetPixel(hdc, x, y - dw, ALPHA_MIXER(backcolor, forecolor, dec));
			backcolor = GetPixel(hdc, x, y + dw);
			SetPixel(hdc, x, y + dw, ALPHA_MIXER(forecolor, backcolor, dec));
			SetPixel(hdc, x, y, forecolor);
			for (i = 1; i < dw; i++)
			{
				SetPixel(hdc, x, y - i, forecolor);
				SetPixel(hdc, x, y + i, forecolor);
			}
		}
		return;
	}
	
	if (dx < dy) 
	{
		for (y = y1; y != y2; y += uy)
		{
			pos = x1 * 100 +  (y - y1) * ux * dx * 100 / (uy * dy);
			x = pos / 100;
			dec = pos % 100;
			backcolor = GetPixel(hdc, x - dw, y);
			SetPixel(hdc, x - dw, y, ALPHA_MIXER(backcolor, forecolor, dec));
			backcolor = GetPixel(hdc, x + dw, y);
			SetPixel(hdc, x + dw, y, ALPHA_MIXER(forecolor, backcolor, dec));
			SetPixel(hdc, x, y, forecolor);
			for (i = 1; i < dw; i++)
			{
				SetPixel(hdc, x - i, y, forecolor);
				SetPixel(hdc, x + i, y, forecolor);
			}
		}
		return;
	}	
}

VOID GUIAPI Brush(HDC hdc, INT32 X1, INT32 X2, INT32 Y1, INT32 Y2, INT32 width)
{
	if (width < 1) width = 2;
	D3DLine (hdc, width, X1, Y1, X2, Y1);
}

/**
** \note  线条的颜色是当前DC的pencolor
**/
VOID GUIAPI Rectangle(HDC hdc, INT32 x0, INT32 y0, INT32 x1, INT32 y1)
{
	PDC	 pdc   = dc_HDC2PDC(hdc);
	RECT	srcRect;
	RECT	effRect;
	GAL_COLOR  c;
	PMAINWIN pWin = (PMAINWIN)(pdc->hwnd);
	int fb_level = 0;
	if (pWin != NULL)
		fb_level = pWin->fblayer;
	
	coor_LP2SP(pdc, &x0, &y0);
	coor_LP2SP(pdc, &x1, &y1);
	SetRect(&srcRect, x0, y0, x1, y1);
	
	NormalizeRect(&srcRect);

	srcRect.right -= 1;
	srcRect.bottom -= 1;

	if (IntersectRect(&effRect, &(pdc->DevRC), &srcRect)) {
	   // GRAPH_PEN_COLOR(pdc->pencolor);
	UnmapPixel(pdc->scrdev, pdc->pencolor, &c);
	   
	fb_line(fb_level, effRect.left,  effRect.top,	effRect.left,  effRect.bottom, c.r, c.g, c.b);
	fb_line(fb_level, effRect.left,  effRect.top,	effRect.right, effRect.top, c.r, c.g, c.b);
	fb_line(fb_level, effRect.left,  effRect.bottom, effRect.right, effRect.bottom, c.r, c.g, c.b);
	fb_line(fb_level, effRect.right, effRect.top,	effRect.right, effRect.bottom+1, c.r, c.g, c.b);	
	}
}

/**
画立体矩形框函数Rect3D( int x1, int y1, int x2, int y2, CHAR lt_color, CHAR rb_color )
描述：
	从字符屏屏幕以x1坐标，y1坐标为左上角，x2、y2为右上角，以颜色值lt_color和rb_color
	画一立体矩形框。此函数对矩形左上角、右上角的位置无限制。
输入参数：
	x1：矩形左上角x坐标；
	y1：矩形左上角y坐标；
	x2：矩形右上角x坐标；
	y2：矩形右上角y坐标；
	lt_color：左边框和上边框的颜色，
	rb_color：右边框和下边框的颜色，
输出：
	在屏幕上画一立体矩形框。
调用：
	画点函数
被调用：
	无
返回值：
	无
**/
VOID GUIAPI Rect3D (HDC hdc, INT32 x0, INT32 y0, INT32 x1, INT32 y1, 
				   GAL_PIXEL lt_color, GAL_PIXEL rb_color)
{
	SetPenColor(hdc, lt_color);
	Line(hdc, x0, y0, x1, y0);
	Line(hdc, x0, y0, x0, y1);
	
	SetPenColor(hdc, rb_color);
	Line(hdc, x0 + 1, y1, x1, y1);
	Line(hdc, x1, y0 + 1, x1, y1);
}

/**
**
**/

		  
GAL_PIXEL GUIAPI RGB2Pixel (HDC hdc, UINT8 r, UINT8 g, UINT8 b)
{
	PDC		pdc   = dc_HDC2PDC(hdc);
	GAL_COLOR  color;
	color.r = r;
	color.g = g;
	color.b = b;
	
	return MapColor(pdc->scrdev, &color);
}

VOID GUIAPI FillBox (HDC hdc, INT32 x1, INT32 y1, INT32 x2, INT32 y2)
{
	FillRect(hdc, x1, y1, x2 - x1 + 1, y2 - y1 + 1);
}

VOID GUIAPI FillRect(HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h)
{
	PDC	 pdc	 = dc_HDC2PDC(hdc);
	RECT	srcRect;
	RECT	effRect;
	GAL_COLOR  c;
	PMAINWIN pWin = (PMAINWIN)(pdc->hwnd);
	int fb_level = 0;
	if (pWin != NULL)
		fb_level = pWin->fblayer;
   
	coor_LP2SP(pdc, &x, &y);
	SetRect(&srcRect, x, y, x+w, y+h);
	NormalizeRect(&srcRect);

	if (IntersectRect(&effRect, &(pdc->DevRC), &srcRect)) 
	{
		UnmapPixel(pdc->scrdev, pdc->brushcolor, &c);
		fb_fillrect(fb_level, effRect.left, effRect.top, effRect.right, effRect.bottom, c.r, c.g, c.b);
	}
}

/*
**  如果background为NULL
**  填充的颜色是当前DC的brushcolor
**  否则直接将background当显存贴到对应的位置
**  background的起始位置为当前DC表示的设备矩形的起始位置(左上角)
**  iLine为background的每行长度(像素)
**  如果prc的范围超过background将不刷新
**  如果prc的范围超过当前DC的设备矩形也不刷新
*/
VOID GUIAPI FillRectEx (HDC hdc, PRECT prc, INT32 iLine, UCHAR *background)
{
	if (!background) 
	{
		FillRect(hdc, prc->left, prc->top, RECTWP(prc), RECTHP(prc));
	}
	else
	{
		UCHAR	   *pp;
		UCHAR	   *offset;
		PMAINWIN	pWin;
		PDC		 pdc;
		RECT		rc;
		RECT		rc1;
		INT32	   x, y, w, h;
		INT32	   i;
		INT16	   fb_level;
		pdc  = dc_HDC2PDC(hdc);
		pWin = (PMAINWIN)(pdc->hwnd);
		fb_level = BASE_FB_LAYER;
		if (pWin != NULL)
			fb_level = pWin->fblayer;
		w = (RECTW(pdc->DevRC) < iLine) ? RECTW(pdc->DevRC) : iLine;
		SetRect(&rc1, 0, 0, w, RECTH(pdc->DevRC));
		IntersectRect(&rc, &rc1, prc);
		x = rc.left;
		y = rc.top;
		w = RECTW(rc);
		h = RECTH(rc);
		#if PIXEL_BIT_24
		offset = background + (y * iLine + x) * 3;
		iLine  = iLine * 3;
		#endif
		
		#if PIXEL_BIT_16
		offset = background + (y * iLine + x) * 2;
		iLine  = iLine * 2;
		#endif
		
		#if PIXEL_BIT_8
		offset = background + (y * iLine + x);
		iLine  = iLine;
		#endif
		
		coor_LP2SP(pdc, &x, &y);
		for (i = 0; i < h; i++)
		{
			pp = offset + i * iLine;
			fb_putlinemem(fb_level, x, y+i, w, pp);
		}
	}
}

void GUIAPI DrawHVDotLine (HDC hdc, long x, long y, int w_h, BOOL H_V)
{
	PDC  pdc;
	long i;
	long dx, dy, x1, y1, x2,y2;
	GAL_COLOR  c, bc;
	
	if (w_h < 1)
		return;

	x1 = x;
	y1 = y;
	if (H_V) {  // hor
		y2 = y;
		x2 = x + w_h;
	} else {  // ver
		y2 = y + w_h;
		x2 = x ;

	}
	pdc = dc_HDC2PDC (hdc);
	PMAINWIN pWin = (PMAINWIN)(pdc->hwnd);
	int fb_level = 0;
	if (pWin != NULL)
		fb_level = pWin->fblayer;
	
	coor_LP2SP(pdc, &x1, &y1);
	coor_LP2SP(pdc, &x2, &y2);

	dx = (x2 - x1 > 0) ? (x2 - x1) : (x1 - x2);
	dy = (y2 - y1 > 0) ? (y2 - y1) : (y1 - y2);
	x  = (x2 > x1) ? x1 : x2;
	y  = (y2 > y1) ? y1 : y2;


	if ( dy == 0 ) {
		dx -= 3 - ( x % 4);
		x += 3 - ( x % 4);
		
	}
	if (dx == 0) {
		dy -= 3 - (y % 4);
		y  += 3 - (y % 4);		
	}

	UnmapPixel(pdc->scrdev, pdc->pencolor, &c);	
	UnmapPixel(pdc->scrdev, pdc->bkcolor, &bc);	

	if (H_V) { // hor
		for (i = 0; i <= dx / 4; i ++) {
			fb_setpixel(fb_level, x++, y, c.r, c.g, c.b);
			fb_setpixel(fb_level, x++ ,y, bc.r, bc.g, bc.b);
			fb_setpixel(fb_level, x++ ,y, bc.r, bc.g, bc.b);
			fb_setpixel(fb_level, x++ ,y, bc.r, bc.g, bc.b);
		}
	} else { // ver
		for (i = 0; i <= dy / 4; i ++) {
			fb_setpixel(fb_level, x, y++, c.r, c.g, c.b);
			fb_setpixel(fb_level, x ,y++, bc.r, bc.g, bc.b);
			fb_setpixel(fb_level, x ,y++, bc.r, bc.g, bc.b);
			fb_setpixel(fb_level, x ,y++, bc.r, bc.g, bc.b);
		}

	}
}

/*******************************************************************************
Name	:   void putFbCache(HDC hdc, PRECT prc, void *cache)

Date	:   2013-4-26
Function:   将指定屏幕缓存放入当前dc所在的fblayer,支持24，16，8位
Input   :   hdc:dc句柄  prc:cache所在的矩形屏幕坐标 cache:屏幕缓存
*******************************************************************************/
void putFbCache(HDC hdc, PRECT prc, unsigned char *cache)
{
	long x, y, w, h;
	long i;
	int  fb_level;
	int  offset;
	PDC  pdc;
	PMAINWIN pWin;
	unsigned char *pp;
	pdc = dc_HDC2PDC (hdc);
	pWin = (PMAINWIN)(pdc->hwnd);
	fb_level = 0;
	if (pWin != NULL)
		fb_level = pWin->fblayer;
	x = prc->left;
	y = prc->top;
	w = RECTWP(prc);
	h = RECTHP(prc);
	pp = cache;
	offset = w * fb_getBpp();
	printf("h...%d\n", h);
	for (i = 0; i < h; i++)
	{
		fb_putlinemem(fb_level, x, y+i, w, pp);
		pp += offset;
	}
	if (fb_level)//非底层窗口需要重绘背景
	{
		RECT rc_dlg = pdc->DevRC;
		if(!IsCovered(&rc_dlg, prc))
		{
			myfb_updateRect(fb_level, prc, &rc_dlg);
		}
	}
}

/*******************************************************************************
Name	:void putFbCache(HDC hdc, PRECT prc, void *cache)

Date	:2013-4-26
Function:将指定屏幕缓存存入cache,支持24，16，8位
Input   :   hdc:dc句柄  prc:cache所在的矩形屏幕坐标
Output  :   cache:屏幕缓存地址
*******************************************************************************/
unsigned char *getFbCache(HDC hdc, PRECT prc)
{
	unsigned char *cache;
	long buffsize = 0;
	long x, y, w, h;
	PDC  pdc;
	PMAINWIN pWin;
	x = prc->left;
	y = prc->top;
	w = RECTWP(prc);
	h = RECTHP(prc);
	buffsize = w * h * fb_getBpp();
	cache = NULL;
	if (buffsize > 0)
	{
		cache = malloc(buffsize);
		if (cache != NULL)
		{
			fb_getmem(x, y, w, h, cache);
		}
	}
	return cache;
}


void getimage(int left, int top, int right, int bottom, void *bitmap)
{

}

void putimage(int x, int y, const void *fpbitmap, int op)
{

}

VOID image_out(int fb_level, int x, int y, int w, int h, UCHAR *img_ptr)
{
#if PIXEL_BIT_16
	fb_putmem(fb_level, x, y, w, h, img_ptr, w * 2, 0);
#endif
#if PIXEL_BIT_24
	fb_putmem(fb_level, x, y, w, h, img_ptr, w * 3, 0);
#endif
}

VOID DrawArrow(HDC hdc, INT32 x, INT32 y, INT32 cx, INT32 cy, ARROW_TYPE type,
	GAL_PIXEL forecolor, GAL_PIXEL backcolor)
{
	GAL_PIXEL pencolor;
	POINT vertex[3];
	if (backcolor != PIXEL_transparent)
	{
		GAL_PIXEL brushcolor = SetBrushColor(hdc, backcolor);
		FillRect(hdc, x, y, cx, cy);
		SetBrushColor(hdc, brushcolor);
	}
	if (forecolor == backcolor)
	{
		return;
	}
	if (forecolor == PIXEL_transparent)
	{
		return;
	}
	switch (type)
	{
		case ARROW_LEFT:
			vertex[0].x = x + cx;
			vertex[0].y = y;
			vertex[1].x = x;
			vertex[1].y = y + (cy >> 1);
			vertex[2].x = x + cx;
			vertex[2].y = y + (cy & ~1L);
			break;

		case ARROW_RIGHT:
			vertex[0].x = x;
			vertex[0].y = y;
			vertex[1].x = x + cx;
			vertex[1].y = y + (cy >> 1);
			vertex[2].x = x;
			vertex[2].y = y + (cy & ~1L);
			break;

		case ARROW_UP:
			vertex[0].x = x;
			vertex[0].y = y + cy;
			vertex[1].x = x + (cx >> 1);
			vertex[1].y = y;
			vertex[2].x = x + (cx & ~1L);
			vertex[2].y = y + cy;
			break;

		case ARROW_DOWN:
			vertex[0].x = x;
			vertex[0].y = y;
			vertex[1].x = x + (cx >> 1);
			vertex[1].y = y + cy;
			vertex[2].x = x + (cx & ~1L);
			vertex[2].y = y;
			break;

		default:
			return;
	}
	pencolor = SetPenColor(hdc, forecolor);
	//DrawLine(hdc, vertex[0].x, vertex[0].y, vertex[1].x, vertex[1].y);
	//DrawLine(hdc, vertex[2].x, vertex[2].y, vertex[1].x, vertex[1].y);
	D3DLine(hdc, 2, vertex[0].x, vertex[0].y, vertex[1].x, vertex[1].y);
	D3DLine(hdc, 2, vertex[2].x, vertex[2].y, vertex[1].x, vertex[1].y);
	SetPenColor(hdc, pencolor);
}



VOID DrawScrollRect(HWND hWnd, UINT16 iCur, UINT16 iCount, UINT16 iItems,
					INT8 mode, GAL_PIXEL color)
{
	HDC	 hdc;
	RECT	rc;
	RECT	frc;
	INT16   headPos;
	INT16   tailPos;
	INT16   thick;
	GAL_PIXEL tmpcolor;
	if (!hWnd)
		return;
	if (iCount <= iItems)
		return;
	GetClientRect(hWnd, &rc);
	color ^= GetWindowBkColor(hWnd);
	hdc = GetDC(hWnd);
	if (mode)// =
	{
//		thick = RECTH(rc) * iItems / iCount;
		thick = RECTH(rc) / ((iCount + iItems - 1) / iItems);
		if (thick > 2)
		{
			thick -= 2;// 1 + 1
		}
		else
		{
			thick = 1;
		}
		headPos = rc.top + RECTH(rc) * iCur / iCount + 1;
		tailPos = headPos + thick;
		if (tailPos >= rc.bottom)
		{
			tailPos = rc.bottom - 1;
			headPos = tailPos - thick;
		}
		SetRect(&frc, rc.left + 1, headPos, rc.right - 1, tailPos);
	}
	else// [	|| ]
	{
		if (RECTH(rc) > DLG_OFFSET)
		{
			DrawArrow(hdc, rc.left, rc.top, RECTH(rc) - 1, RECTH(rc) - 1,
						ARROW_LEFT, color, GetWindowBkColor(hWnd));
			DrawArrow(hdc, rc.right - RECTH(rc), rc.top, RECTH(rc) - 1,
				RECTH(rc) - 1, ARROW_RIGHT, color, GetWindowBkColor(hWnd));
			rc.left  += RECTH(rc);
			rc.right -= RECTH(rc) + 1;
		}
//		thick = RECTW(rc) * iItems / iCount;
		thick = RECTW(rc) / ((iCount + iItems - 1) / iItems);
		if (thick > 2)
		{
			thick -= 2;// 1 + 1
		}
		else
		{
			thick = 1;
		}
		headPos = rc.left + RECTW(rc) * iCur / iCount + 1;
		tailPos = headPos + thick;
		if (tailPos >= rc.right)
		{
			tailPos = rc.right - 1;
			headPos = tailPos - thick;
		}
		SetRect(&frc, headPos , rc.top + 1, tailPos, rc.bottom - 1);
	}
	tmpcolor = SetBrushColor(hdc, color);
	FillRect(hdc, frc.left, frc.top, RECTW(frc), RECTH(frc));
	SetBrushColor(hdc, tmpcolor);
	ReleaseDC(hdc);
}

VOID DrawScrollH(HWND hWnd, UINT16 iCur, UINT16 iCount, UINT16 iItems)
{
	SetWindowText(hWnd, 0);
	DrawScrollRect(hWnd, iCur, iCount, iItems, 0, 
					GetWindowElementColor(BKC_CAPTION_NORMAL));
}

VOID DrawScrollV(HWND hWnd, UINT16 iCur, UINT16 iCount, UINT16 iItems)
{
	SetWindowText(hWnd, 0);
	DrawScrollRect(hWnd, iCur, iCount, iItems, 1, 
					GetWindowElementColor(BKC_CAPTION_NORMAL));
}

