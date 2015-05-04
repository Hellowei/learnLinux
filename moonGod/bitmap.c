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

#define   BITMAP_GLOBALS 

#include "includes.h"

static BITMAP  Sys_Bmp[] = {
	{ 0, 0, 0, 0, 0, 0 },
};

#define  SYS_BMP_NR   TABLESIZE(Sys_Bmp)

/**
  \note 加载系统的bmp文件,并保存到RAM对象中;
		并组织到一个数组中;使用id号来引用.
**/
BOOL  InitSysBmp (VOID)
{
	return TRUE;
}

/**
*  \note  目前对单色的bitmap,使用DC的brush颜色;背景使用DC的bkcolor;
   这里认为，0为背景
**/
static  void  bm_put_1bppImg (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h,  PBITMAP imgP)
{
	UINT8	  *dataP;
	GAL_PIXEL   color, bk_color, brush_color;
	int		 coor_x, coor_y;
	int		 i, j , m;
	int		 nr_bytes;
	int		 remained;
	INT8		transparent = FALSE;
	bk_color = GetBkColor(hdc);
	brush_color = GetBrushColor(hdc);
	if (bk_color == PIXEL_transparent)
	{
		transparent = TRUE;
	}
	dataP	= imgP->bits;
	coor_x   = x;
	coor_y   = y;
	nr_bytes = w>>3;		   // 一行图像宽度对应字节的数量; 一个字节8个pixel;
	remained = w%8 ;		   // 如果一行图像的宽不是8的整数倍,这是额外的pixel数;

	for (i = 0; i < h; i++) { // i 表示行的数量,也表示y轴的步进量;
		
		for (j = 0; j < nr_bytes; j++) { // j 表示一行pixel需要几个字节数据
			for (m = 0; m < 8; m++) {	// 每次划8个点
				if ((*dataP) & DCB2HEX_TAB[m])
				{
					color = brush_color;
					SetPixel(hdc, coor_x, coor_y, color);
				}
				else if (!transparent)
				{
					color = bk_color;
					SetPixel(hdc, coor_x, coor_y, color);
				}
				coor_x ++;
			}
			dataP++;
		}
		for (j = 0; j < remained; j++) { // 如果宽不是8的整数倍,那么还要画点
			if ((*dataP) & DCB2HEX_TAB[j])
			{
				color = brush_color;
				SetPixel(hdc, coor_x, coor_y, color);
			}
			else if (!transparent)
			{
				color = bk_color;
				SetPixel(hdc, coor_x, coor_y, color);
			}
			coor_x ++;
		}
		if (remained)  
			dataP ++;  // 有余数的话, 数据指针要多加一次

		coor_x = x;	// x坐标回退;
		coor_y ++;	 // 开始划一行的点
	}
}

/**
** \note  一个字节数据代表2个象素; 左边的象素点位于高位, 不足的数据以0做右填充;
** \format  bit 7  6  5  4  3  2  1  0
**			 | pixel 0   | pixel 1  |
**/
static  void  bm_put_4bppImg (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h,  PBITMAP imgP)
{
	PDC		 pdc;
	UINT8	  *dataP;
	GAL_PIXEL   pixel;
	int		 coor_x, coor_y;
	int		 i, j;
	
	pdc	  = dc_HDC2PDC(hdc);
	dataP	= imgP->bits;
	coor_x   = x;
	coor_y   = y;
	
	for (i= 0; i < h; i++) {

		for (j = 0; j < w/2; j++) {
		
			pixel = (*dataP)>>4;	//bitmap数据中的象素值;
			pixel = MapColorEx(pdc->scrdev, 4, pixel);
			SetPixel(hdc, coor_x, coor_y, pixel);
			coor_x++;
			
			pixel = *dataP;		//bitmap数据中的象素值;
			pixel = MapColorEx(pdc->scrdev, 4, pixel);
			SetPixel(hdc, coor_x, coor_y, pixel);
			coor_x++;
			
			dataP ++;
		}

		if (w & 0x1) {
			pixel = (*dataP)>>4;   //bitmap数据中的象素值;
			pixel = MapColorEx(pdc->scrdev, 4, pixel);
			SetPixel(hdc, coor_x, coor_y, pixel);
			coor_x++;
			
			dataP ++;
		}
		
		coor_x -= w;
		coor_y ++;
	}
}

static  void  bm_put_8bppImg (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h,  PBITMAP imgP)
{
#if defined(LANNRY)
	PDC		 pdc;
	UINT8	  *dataP;

	pdc	  = dc_HDC2PDC(hdc);
	dataP	= imgP->bits;

	coor_LP2SP(pdc, &x, &y);

	GuiBmp(x, y, x + w - 1, y + h - 1, (int far *)dataP);	
#else
	PDC		 pdc;
	UINT8	  *dataP;
	GAL_PIXEL   pixel;
	int		 coor_x, coor_y;
	int		 i, j;

	pdc	  = dc_HDC2PDC(hdc);
	dataP	= imgP->bits;
	coor_x   = x;
	coor_y   = y;
	
	for (i= 0; i < h; i++) {

		for (j = 0; j < w; j++) {
		
			pixel = *dataP;	//bitmap数据中的象素值;
			pixel = MapColorEx(pdc->scrdev, 8, pixel);
			SetPixel(hdc, coor_x, coor_y, pixel);
			dataP ++;
			coor_x++;
		}
		
		coor_x -= w;
		coor_y ++;
	}
#endif
}

static  void  bm_put_16bppImg (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h,  PBITMAP imgP)
{
	PDC		 pdc;
	UINT8	  *dataP;
	GAL_PIXEL   pixel;
	int		 coor_x, coor_y;
	int		 i, j;

	pdc	  = dc_HDC2PDC(hdc);
	dataP	= imgP->bits;
	coor_x   = x;
	coor_y   = y;

	for (i= 0; i < h; i++) {

		for (j = 0; j < w; j++) {
		
			pixel = (UINT32)(*(UINT16 *)dataP);	//bitmap数据中的象素值;
			pixel = MapColorEx(pdc->scrdev, 16, pixel);
			SetPixel(hdc, coor_x, coor_y, pixel);
			dataP += 2;
			coor_x++;
		}
		
		coor_x -= w;
		coor_y ++;
	}
}

static  void  bm_put_24bppImg (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h,  PBITMAP imgP)
{
	PDC		 pdc;
	UINT8	  *dataP;
	GAL_PIXEL   pixel;
	int		 coor_x, coor_y;
	int		 i, j;

	pdc	  = dc_HDC2PDC(hdc);
	dataP	= imgP->bits;
	coor_x   = x;
	coor_y   = y;

	for (i= 0; i < h; i++) {

		for (j = 0; j < w; j++) {
		
			pixel = (UINT32)(*(UINT32 *)dataP);	//bitmap数据中的象素值;
			pixel = MapColorEx(pdc->scrdev, 24, pixel);
			SetPixel(hdc, coor_x, coor_y, pixel);
			dataP += 4;
			coor_x++;
		}
		
		coor_x -= w;
		coor_y ++;
	}
}


/**
**  \note  目前对单色的bitmap,使用DC的brush颜色;背景使用DC的bkcolor;
**/
VOID GUIAPI PutImage (HDC hdc, INT32 x, INT32 y, PBITMAP imgP)
{
	PDC	 pdc	 = dc_HDC2PDC(hdc);
	RECT	effRect;
	
	coor_LP2SP(pdc, &x, &y);
	SetRect(&effRect, x, y, x + imgP->width, y + imgP->height);
	NormalizeRect(&effRect);
	
	if (IntersectRect(&effRect, &(pdc->DevRC), &effRect)) {
	
		//fixed bug: 在后续的调用set_pixel,需要输入逻辑坐标.
		coor_SP2LP(pdc, &effRect.left, &effRect.top);
		coor_SP2LP(pdc, &effRect.right, &effRect.bottom);
		
		switch (imgP->bitsPixel) {
			case 1:
				bm_put_1bppImg(hdc, effRect.left, effRect.top, RECTW(effRect), 
							   RECTH(effRect), imgP);
				break;
				
			case 4:
				bm_put_4bppImg(hdc,effRect.left, effRect.top, RECTW(effRect), 
							   RECTH(effRect), imgP);
				break;

			case 8:
				bm_put_8bppImg(hdc,effRect.left, effRect.top, RECTW(effRect), 
							   RECTH(effRect), imgP);
				break;

			case 16:
				bm_put_16bppImg(hdc,effRect.left, effRect.top, RECTW(effRect), 
								RECTH(effRect), imgP);
				break;

			case 24:
				bm_put_24bppImg(hdc,effRect.left, effRect.top, RECTW(effRect), 
								RECTH(effRect), imgP);
				break;
			
			default: 
				break;
		}
	}
}

static  void  bm_get_4bppImg (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h,  PBITMAP imgP)
{
	UINT8	*bitsP;
	GAL_PIXEL pix_h, pix_l;
	int	   i, j;
	int	   coor_x, coor_y;
	
	bitsP  = imgP->bits;
	coor_x = x;
	coor_y = y;
	
	for (i = 0; i < h; i++) {
		for (j = 0; j < w/2; j++) {
			pix_h  = GetPixel(hdc, coor_x++, coor_y);
			pix_l  = GetPixel(hdc, coor_x++, coor_y);
			*bitsP = ((pix_h<<4) + pix_l)&0xff;
			bitsP ++;
		}

		if (w & 0x1) {
			pix_h  = GetPixel(hdc, coor_x++, coor_y);
			*bitsP = (pix_h<<4);
			bitsP ++;
		}
		coor_x -= w;
		coor_y ++;
	}
}

static  void  bm_get_8bppImg (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h,  PBITMAP imgP)
{
	UINT8	*bitsP;
	GAL_PIXEL pixel;
	int	   i, j;
	int	   coor_x, coor_y;
	
	bitsP  = imgP->bits;
	coor_x = x;
	coor_y = y;
	
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			pixel  = GetPixel(hdc, coor_x++, coor_y );
			*bitsP = pixel&0xff;
			bitsP ++;
		}

		coor_x -= w;
		coor_y ++;
	}
}

static  void  bm_get_16bppImg (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h,  PBITMAP imgP)
{
	UINT8	*bitsP;
	GAL_PIXEL pixel;
	int	   i, j;
	int	   coor_x, coor_y;
	
	bitsP  = imgP->bits;
	coor_x = x;
	coor_y = y;
	
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			pixel  = GetPixel(hdc, coor_x++, coor_y);
			*((UINT16 *)bitsP) = pixel&0xffff;
			bitsP += 2;
		}

		coor_x -= w;
		coor_y ++;
	}
}

static  void  bm_get_24bppImg (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h,  PBITMAP imgP)
{
	UINT8	*bitsP;
	GAL_PIXEL pixel;
	int	   i, j;
	int	   coor_x, coor_y;
	
	bitsP  = imgP->bits;
	coor_x = x;
	coor_y = y;
	
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			pixel  = GetPixel(hdc, coor_x++, coor_y);
			*((UINT32 *)bitsP) = pixel&0xffffff;
			bitsP += 4;
		}

		coor_x -= w;
		coor_y ++;
	}
}


/**
** \note  调用者负责对bitmap结构,分配足够的内存
**/
VOID  GUIAPI  GetImage (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h, PBITMAP imgP)
{
	PDC	 pdc;
	
	pdc = dc_HDC2PDC(hdc);

	imgP->type	   = 0;
	imgP->bitsPixel  = pdc->scrdev->bpp;
	imgP->width	  = w;
	imgP->height	 = h;
	imgP->bytesWidth = (w * imgP->bitsPixel + 7)>>3;
	
	switch (pdc->scrdev->bpp) {
		case 4:
			bm_get_4bppImg(hdc, x, y, w, h, imgP);
			break;

		case 8:
			bm_get_8bppImg(hdc, x, y, w, h, imgP);
			break;

		case 16:
			bm_get_16bppImg(hdc, x, y, w, h, imgP);
			break;
		case 24:
			bm_get_24bppImg(hdc, x, y, w, h, imgP);			
			break;

		default:
			break;
	}
}

/**
* \note 不包括BITMAP数据结构本身的大小;
**/
INT32  ImageSize(HDC hdc, INT32 w, INT32 h)
{
	PDC	 pdc;
	
	pdc = dc_HDC2PDC(hdc);
	return ((w * h * pdc->scrdev->bpp + 7) >> 3);
}

/**
**  \brief  如果坐标和范围超过了DC的矩形, 那么绘制的图形还是在dc的矩形内;但是图形是不正确的;
**/
VOID GUIAPI PutBox (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h, VOID * imgP)
{
	PDC	 pdc	 = dc_HDC2PDC(hdc);
	RECT	srcRect;
	RECT	effRect;
	
	coor_LP2SP(pdc, &x, &y);
	SetRect( &srcRect, x, y, x+w, y+h );
	NormalizeRect(&srcRect);
	
	if (IntersectRect(&effRect, &(pdc->DevRC), &srcRect)) {
	  putimage(effRect.left, effRect.top, imgP, 0);
	}
}

/**
**
**/
VOID GUIAPI GetBox (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h, VOID * bufP)
{
	PDC	 pdc	 = dc_HDC2PDC(hdc);
	RECT	srcRect;
	RECT	effRect;
	
	coor_LP2SP(pdc, &x, &y);
	SetRect( &srcRect, x, y, x+w, y+h );
	NormalizeRect(&srcRect);
	
	if ( IntersectRect( &effRect, &(pdc->DevRC), &srcRect ) ) {
		getimage(effRect.left, effRect.top, effRect.left + RECTW(effRect), 
				 effRect.top + RECTH(effRect), bufP);
	}
}

VOID   DrawBitmap(HDC hdc, INT32 x,INT32 y, INT bmp_id)
{
	if (bmp_id >= 0)   
		PutImage(hdc, x, y,  Sys_Bmp + bmp_id);
}
