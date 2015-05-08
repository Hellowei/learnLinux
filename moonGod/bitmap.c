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

#define   BITMAP_GLOBALS 

#include "includes.h"

static BITMAP  Sys_Bmp[] = {
	{ 0, 0, 0, 0, 0, 0 },
};

#define  SYS_BMP_NR   TABLESIZE(Sys_Bmp)

/**
  \note ����ϵͳ��bmp�ļ�,�����浽RAM������;
		����֯��һ��������;ʹ��id��������.
**/
BOOL  InitSysBmp (VOID)
{
	return TRUE;
}

/**
*  \note  Ŀǰ�Ե�ɫ��bitmap,ʹ��DC��brush��ɫ;����ʹ��DC��bkcolor;
   ������Ϊ��0Ϊ����
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
	nr_bytes = w>>3;		   // һ��ͼ���ȶ�Ӧ�ֽڵ�����; һ���ֽ�8��pixel;
	remained = w%8 ;		   // ���һ��ͼ��Ŀ���8��������,���Ƕ����pixel��;

	for (i = 0; i < h; i++) { // i ��ʾ�е�����,Ҳ��ʾy��Ĳ�����;
		
		for (j = 0; j < nr_bytes; j++) { // j ��ʾһ��pixel��Ҫ�����ֽ�����
			for (m = 0; m < 8; m++) {	// ÿ�λ�8����
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
		for (j = 0; j < remained; j++) { // �������8��������,��ô��Ҫ����
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
			dataP ++;  // �������Ļ�, ����ָ��Ҫ���һ��

		coor_x = x;	// x�������;
		coor_y ++;	 // ��ʼ��һ�еĵ�
	}
}

/**
** \note  һ���ֽ����ݴ���2������; ��ߵ����ص�λ�ڸ�λ, �����������0�������;
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
		
			pixel = (*dataP)>>4;	//bitmap�����е�����ֵ;
			pixel = MapColorEx(pdc->scrdev, 4, pixel);
			SetPixel(hdc, coor_x, coor_y, pixel);
			coor_x++;
			
			pixel = *dataP;		//bitmap�����е�����ֵ;
			pixel = MapColorEx(pdc->scrdev, 4, pixel);
			SetPixel(hdc, coor_x, coor_y, pixel);
			coor_x++;
			
			dataP ++;
		}

		if (w & 0x1) {
			pixel = (*dataP)>>4;   //bitmap�����е�����ֵ;
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
		
			pixel = *dataP;	//bitmap�����е�����ֵ;
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
		
			pixel = (UINT32)(*(UINT16 *)dataP);	//bitmap�����е�����ֵ;
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
		
			pixel = (UINT32)(*(UINT32 *)dataP);	//bitmap�����е�����ֵ;
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
**  \note  Ŀǰ�Ե�ɫ��bitmap,ʹ��DC��brush��ɫ;����ʹ��DC��bkcolor;
**/
VOID GUIAPI PutImage (HDC hdc, INT32 x, INT32 y, PBITMAP imgP)
{
	PDC	 pdc	 = dc_HDC2PDC(hdc);
	RECT	effRect;
	
	coor_LP2SP(pdc, &x, &y);
	SetRect(&effRect, x, y, x + imgP->width, y + imgP->height);
	NormalizeRect(&effRect);
	
	if (IntersectRect(&effRect, &(pdc->DevRC), &effRect)) {
	
		//fixed bug: �ں����ĵ���set_pixel,��Ҫ�����߼�����.
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
** \note  �����߸����bitmap�ṹ,�����㹻���ڴ�
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
* \note ������BITMAP���ݽṹ����Ĵ�С;
**/
INT32  ImageSize(HDC hdc, INT32 w, INT32 h)
{
	PDC	 pdc;
	
	pdc = dc_HDC2PDC(hdc);
	return ((w * h * pdc->scrdev->bpp + 7) >> 3);
}

/**
**  \brief  �������ͷ�Χ������DC�ľ���, ��ô���Ƶ�ͼ�λ�����dc�ľ�����;����ͼ���ǲ���ȷ��;
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
