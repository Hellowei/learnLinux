
#include "includes.h"

static void fbmem_set_mem(int width, int height, int pixelbits, PBITMAPMEM mem)
{
	mem->cx = width;
	mem->cy = height;
	mem->bits = pixelbits;
	if (mem->data == NULL)
	{
		mem->data = (unsigned char *)malloc
			(((width * height * pixelbits + 31) >> 5) << 2);
		if (mem->data)
			mem->free = TRUE;
	}
}

static void fbmem_fill_rect(PBITMAPMEM mem, 
					INT32 left, INT32 top, INT32 right, INT32 bottom, 
					UCHAR red, UCHAR green, UCHAR blue)
{
	INT32 width;
	INT32 height;
	INT32 byte;
	INT32 w;
	INT32 h;
#if PIXEL_BIT_16
	UINT16 *pp;
	UINT16 color;
	color = fb_color(red, green, blue);
#endif
	byte = mem->bits / 8;
	width = mem->cx;
	height = mem->cy;
	for (h = top; h < bottom; h++)
	{
#if PIXEL_BIT_16
		pp = (UINT16 *)(mem->data + ((h * width + left) * byte));
#endif
		for (w = left; w < right; w++)
		{
			*pp++ = color;
		}
	}
}

static void fbmem_setpixel(PBITMAPMEM mem, int x, int y, GAL_PIXEL pixel)
{
#if PIXEL_BIT_16
	UINT16 color = fb_color(PIXEL888RED (pixel), PIXEL888GREEN (pixel),
							PIXEL888BLUE (pixel));
	unsigned short *pp;
	if (x < 0 || y < 0 || x >= mem->cx || y >= mem->cy)
		return;
	pp = (unsigned short *)(mem->data + (((x + y * mem->cx) * mem->bits) >> 3));
#endif
	
}

// 目前只处理只有一个矩形的情况
static void 
fbmem_hline(PBITMAPMEM mem, INT32 x0, INT32 x1, INT32 y, GAL_PIXEL pixel)
{
	INT32 x;
	INT32 iLineBytes;
	unsigned char *p = mem->data;
#if PIXEL_BIT_16
	UINT16 color = fb_color(PIXEL888RED (pixel), PIXEL888GREEN (pixel),
							PIXEL888BLUE (pixel));
	unsigned short *pp = (unsigned short *)(mem->data);
#endif	
	iLineBytes = (mem->cx * mem->bits) >> 3;
	p += iLineBytes * y;
	p += (x0 * mem->bits) >> 3;
#if PIXEL_BIT_16
	for (x = x0; x < x1; x++)
	{
		*pp++ = color;
	}
#endif	
	return;
}



// 画竖线
static void 
fbmem_vline(PBITMAPMEM mem, INT32 y0, INT32 y1, INT32 x, GAL_PIXEL pixel)
{
	INT32 y;
	INT32 iLineBytes;
	unsigned char *p = mem->data;
#if PIXEL_BIT_16
	UINT16 color = fb_color(PIXEL888RED (pixel), PIXEL888GREEN (pixel),
							PIXEL888BLUE (pixel));
	unsigned short *pp = (unsigned short *)(mem->data);
#endif	
	iLineBytes = (mem->cx * mem->bits) >> 3;
	p += iLineBytes * y0;
	p += (x * mem->bits) >> 3;
	for (y = y0; y < y1; y++)
	{
#if PIXEL_BIT_16
		*pp = color;
#endif	
		p += iLineBytes;
	}
	  return;
}

// The soame point, no pixel out
void fbmem_line(PBITMAPMEM mem, INT32 x0, INT32 y0, INT32 x1, INT32 y1,
				GAL_PIXEL pixel)
{
	INT32 tmp; 
	if (x0 == x1)
	{ 
		if (x1 < 0 || x0 > mem->cx)
			return;
		if (y0 > y1)
		{
			tmp = y0;
			y0 = y1;
			y1 = tmp;
		}
		if (y1 < 0 || y0 > mem->cy)
			return;
		fbmem_vline(mem, y0, y1, x0, pixel);
		return;
	}
	if (y0 == y1)
	{
		if (y1 < 0 || y0 > mem->cy)
			return;
		if (x0 > x1)
		{
			tmp = x0;
			x0 = x1;
			x1 = tmp;
		}
		if (x1 < 0 || x0 > mem->cx)
			return;
		fbmem_hline(mem, x0, x1, y0, pixel);
		return;
	}
}

static void fbmem_put_bmchar(PBITMAPMEM mem, UCHAR * imgP,
	INT32 x, INT32 y, INT32 w, INT32 h, GAL_PIXEL bgpixel, GAL_PIXEL fgpixel)
{//DCB2HEX_TAB[8]
#if PIXEL_BIT_16
	UINT16 backColor = fb_color(PIXEL888RED (bgpixel), PIXEL888GREEN (bgpixel),
								PIXEL888BLUE (bgpixel));
	UINT16 foreColor = fb_color(PIXEL888RED (fgpixel), PIXEL888GREEN (fgpixel),
								PIXEL888BLUE (fgpixel));
#endif
	UCHAR *buff, *p;
	INT32 index;
	INT8  transparent = FALSE;
	INT16 i, j, k;
	INT16 width;
	INT16 height;
	INT16 nr_bytes;
	INT8  remained;
	if (bgpixel == PIXEL_transparent)
		transparent = TRUE;

	if (mem->cx < x || x + w < 0 || mem->cy < y || y + h < 0)//不在men内
		return;
	if (x < 0 || y < 0)//起始位置不在mem内
		return;
	if (x + w > mem->cx || y + h > mem->cy)//超界
		return;
	
	nr_bytes = w >> 3;   // 字符的宽对几个字节的数据
	remained = (w & 0x07); // w % 8; 如果字符的宽不是8的整数倍,这是额外的pixel数;
	p = imgP;
	for (i = y; i < y + h; i++)
	{
		index = 0;
		buff = mem->data + (x + i * mem->cx) * mem->bits / 8;
		for (j = 0; j < nr_bytes; j++)
		{
			for (k = 0; k < 8; k++)
			{
#if PIXEL_BIT_16
				unsigned short * pp = (unsigned short *)(buff + index);
				if (((*p) & DCB2HEX_TAB[k]) == 0)
				{
					if (! transparent)
						*pp = backColor;
				}
				else
				{
					*pp = foreColor;
				}
				index += 2;
#endif
			}
			p++;
		}
		for ( j = 0; j < remained; j ++ ) 
		{
#if PIXEL_BIT_16
			unsigned short * pp = (unsigned short *)(buff + index);
			if (((*p) & DCB2HEX_TAB[j]) == 0)
			{
				if (! transparent)
					*pp = backColor;
			}
			else
			{
				*pp = foreColor;
			}
			index += 2;
#endif	  
		}
		if ( remained )  
			p ++;  // 有余数的话, 数据指针要多加一次
	}
}


static INT32 fbmem_put_strn (PBITMAPMEM mem, PLOGFONT pLogfont,
							 GAL_PIXEL bgpixel, GAL_PIXEL fgpixel,
							 INT32 x, INT32 y, const CHAR* text, INT32 len)
{
	DEVFONT  * sbc_devfont   = pLogfont->sbc_devfont;
	DEVFONT  * mbc_devfont   = pLogfont->mbc_devfont;
	long	   len_cur_char;
	long	   left_bytes = len; // 有待处理的字符字节数量
	long	   origx = x;
	long	   sbc_height;
	long	   mbc_height = 0;
	long	   sbc_width  = 0;
	long	   mbc_width  = 0;
	UCHAR	* imgP;
	UINT8	  err;
	
	sbc_height =
		(*sbc_devfont->font_ops->get_font_height)(pLogfont, sbc_devfont);

	if (mbc_devfont)
	{
		mbc_height =
			(*mbc_devfont->font_ops->get_font_height)(pLogfont, mbc_devfont);
	}

	while (left_bytes) 
	{
		if (mbc_devfont != NULL)	 // 存在多字节字符集字体
		{   
			len_cur_char = (*mbc_devfont->charset_ops->len_first_char)
				(text, left_bytes);
			if (len_cur_char != 0)  // 当前字符属于这个设备字体
			{
				mbc_width = (*mbc_devfont->font_ops->get_char_width)
					(pLogfont,mbc_devfont, text, len_cur_char);
				imgP = (UCHAR *)(*mbc_devfont->font_ops->get_char_bitmap)
					(pLogfont,mbc_devfont, text, len_cur_char);
				fbmem_put_bmchar(mem, imgP, x, y, mbc_width, mbc_height,
					bgpixel, fgpixel);
				
				x += mbc_width; // 更新x坐标,待处理的字节递减,文本指针向后移动;
				left_bytes -= len_cur_char;
				text += len_cur_char;
				continue;
			}
		}

		// 单字节字符集字体处理
		len_cur_char = (*sbc_devfont->charset_ops->len_first_char)
		(text, left_bytes);
		if (len_cur_char != 0) 
		{
			sbc_width = (*sbc_devfont->font_ops->get_char_width)
				(pLogfont,sbc_devfont, text, len_cur_char);
			imgP = (UCHAR *)(*sbc_devfont->font_ops->get_char_bitmap)
				(pLogfont,sbc_devfont, text, len_cur_char);
			fbmem_put_bmchar(mem, imgP, x, y, sbc_width, sbc_height,
				bgpixel, fgpixel);
		}
		else 
		{
			break; // 不属于该字符集; 退出函数
		}
		// 更新x坐标, 代处理的字节递减, 文本指针向后移动;
		x += sbc_width;
		left_bytes -= len_cur_char;
		text += len_cur_char;
	}
	
	return x - origx;
}



static INT32 fbmem_textout(PBITMAPMEM mem, PLOGFONT pLogfont,
					GAL_PIXEL bgpixel, GAL_PIXEL fgpixel,
					INT32 x, INT32 y, const CHAR* text, INT32 len)
{
	RECT   rcOutput;
	RECT   rcMem;
	SIZE   size;

	if (len == 0) return 0;
	if (len < 0)  len = strlen (text); 

	if (mem->cx < x || mem->cy < y)
		 return 0;//如果字符的起始点不在显存内,立即推迟;不必继续后面的过程;
	SetRect(&rcMem, 0, 0, mem->cx - 1, mem->cy - 1);
	while (len)
	{  // 必须保证整个字符输出都在显存内,否则减少输出的字符;
	
		gdi_get_TextOut_extent (NULL, pLogfont, text, len, &size);

		rcOutput.left   = x;
		rcOutput.top	= y;
		rcOutput.right  = x + size.cx ; 
		rcOutput.bottom = y + size.cy ; 
		NormalizeRect(&rcOutput);

		if (IsCovered(&rcMem, &rcOutput))  
			break;//输出范围在在显存内,出循环;
			
		len --;
	}
	if (len > 0)
	{
		fbmem_put_strn(mem, pLogfont, bgpixel, fgpixel, x, y,
						text + strlen(text) - len, len);
	}
	else 
	{
		size.cx = 0;
	}
	return size.cx;
}

static long Build24BitmapMem(UCHAR *pBitmap, INT8 pixel_bits, PBITMAPMEM pMem)
{
	INT32			line_bytes;
	INT32			size = 0;			  //累加数据指针的长度
	BITMAPFILEHEADER BitHeader;			 //BMP文件结构的头
	BITMAPINFOHEADER BitInfoHeader;		 //BMP位图信息头
	INT16			w, h;					 //行循环计数变量
	UINT8			err;
	UCHAR			*bits, *pp;

	memcpy(&BitHeader, pBitmap, sizeof(BITMAPFILEHEADER));

	// 判断文件的合法性。
	if(BitHeader.bfType != 'M' * 256 + 'B')
	{
		printf("This Is Not A Bmp File.\n");
		return -1;
	}

	bits = pBitmap + BitHeader.bfOffBits; // 保存图象数据的开始地址
	
	// 打开BMP位图信息头
	memcpy(&BitInfoHeader, pBitmap + sizeof(BITMAPFILEHEADER),
			sizeof(BITMAPINFOHEADER));
	
	// 24位色限定(只能识别真彩24位)
	if (BitInfoHeader.biBitCount != 24) 
   {
		printf("This Programme Only For 24bit Colors Bitmap.\n");
		return -1;
	}
	
	// 压缩限定（识别无压缩格式）
	if (BitInfoHeader.biCompress != 0) 
	{
		printf("This Programme Only For no rar Bitmap.\n");
		return -1;
	}

	//图片大小限定最大1024*768
	if (BitInfoHeader.biWidth > 1024 || BitInfoHeader.biHeight > 768) 
	{
		printf("Bitmap is too big.\n");
		return -1;
	}
	pMem->bits = BitInfoHeader.biBitCount;
	pMem->cx = BitInfoHeader.biWidth;
	pMem->cy = BitInfoHeader.biHeight;
	//算出图片的每行数据的字节数
	line_bytes = 
		(((BitInfoHeader.biWidth * BitInfoHeader.biBitCount + 31) >> 5 ) << 2);
	if (pixel_bits == 24)
	{
		pMem->data = bits;
	}
	if (pixel_bits == 16)
	{
		UINT16 *data;
		UINT16 color = 0;
		UINT8 r, g, b;
		size = ((pMem->cx * 16) >> 3) * pMem->cy;
		data = (UINT16 *)malloc(size);
		if (data == NULL)
		{
			errprintf("Can not malloc.\n");
			return -1;
		}
		pMem->data = PTR2FLAT(data);
		pMem->free = TRUE;
		pp = bits;
		for  (h = 0; h < pMem->cy; h++)
		{
			for (w = 0; w < pMem->cx; w++)
			{
				r = *pp++;
				g = *pp++;
				b = *pp++;
				color |= (b >> 3);
				color |= (g >> 2) << 5;
				color |= (r >> 3) << 11;
				*data++ = color;
			}
		}
	}
	return 0;   
}

static void NewFbMemory(PFBMEM this, int width, int height, int pixelbits)
{
	fbmem_set_mem(width, height, pixelbits, this->mem);
}

static void 
BuildBitmapMemory(PFBMEM this, unsigned char *pBitmap, char pixel_bits)
{
	Build24BitmapMem(pBitmap, pixel_bits, this->mem);
}

static void DestroyMemory(PFBMEM this)
{
	if (!this->mem->data)
		free(this->mem->data);
	this->mem->data = NULL;
}

static void OutputFbMemory(PFBMEM this, HDC hdc, long x, long y)
{
	RECT rc;
	SetRect(&rc, x, y, x + this->mem->cx, y + this->mem->cy);
	FillRectEx(hdc, &rc, this->mem->cx, this->mem->data);
}

static void FbMemFillRect(PFBMEM this, PRECT prc)
{
	GAL_PIXEL color = this->brushColor;
	fbmem_fill_rect(this->mem, prc->left, prc->top, prc->right, prc->bottom,
	PIXEL888RED (color), PIXEL888GREEN (color), PIXEL888BLUE (color));
}

static void FbMemLine(PFBMEM this, long x0, long x1, long y0, long y1)
{
	fbmem_line(this->mem, x0, y0, x1, y1, this->foreColor);
}

static void 
FbMemPutIcon(PFBMEM this, unsigned char * imgP, long x, long y, long w, long h)
{
	fbmem_put_bmchar(this->mem, imgP, x, y, w, h,
					 this->backColor, this->foreColor);
}

static void 
FbMemTextOutLen(PFBMEM this, long x, long y, const char* text, long len)
{
	fbmem_textout(this->mem, this->pLogfont, this->backColor,
					this->foreColor, x, y, text, len);
}

static void FbMemTextOut(PFBMEM this, long x, long y, const char* text)
{
	this->TextOutLen(this, x, y, text, strlen(text));
}

static void FbMemSetPixel(PFBMEM this, long x, long y, GAL_PIXEL pixel)
{
	fbmem_setpixel(this->mem, x, y, pixel);
}

static PBITMAPMEM SetFbMemory(PFBMEM this, BITMAPMEM * mem)
{
	UINT32 tmp = (UINT32)this->mem;
	this->mem = mem;
	return (PBITMAPMEM)tmp;
}

static PBITMAPMEM GetFbMemory(PFBMEM this)
{
	return this->mem;
}

static PLOGFONT FbMemSetFont(PFBMEM this, PLOGFONT pLogfont)
{
	PLOGFONT pfont = this->pLogfont;
	this->pLogfont = pLogfont;
	return pfont;
}

static PLOGFONT FbMemGetFont(PFBMEM this)
{
	return this->pLogfont;
}

static GAL_PIXEL FbMemSetBackColor(PFBMEM this, GAL_PIXEL color)
{
	GAL_PIXEL c = this->backColor;
	this->backColor = color;
	return c;
}

static GAL_PIXEL FbMemGetBackColor(PFBMEM this)
{
	return this->backColor;
}

static GAL_PIXEL FbMemSetForeColor(PFBMEM this, GAL_PIXEL color)
{
	GAL_PIXEL c = this->foreColor;
	this->foreColor = color;
	return c;
}

static GAL_PIXEL FbMemGetForeColor(PFBMEM this)
{
	return this->foreColor;
}

static GAL_PIXEL FbMemSetBrushColor(PFBMEM this, GAL_PIXEL color)
{
	GAL_PIXEL c = this->brushColor;
	this->brushColor = color;
	return c;
}

static GAL_PIXEL FbMemGetBrushColor(PFBMEM this)
{
	return this->brushColor;
}

struct _fb_mem_func FbMem = {
	0,  0,  0,		  NULL,				   NULL,
	NewFbMemory,		BuildBitmapMemory,	  DestroyMemory,  
	OutputFbMemory,	 FbMemFillRect,		  FbMemLine,
	FbMemPutIcon,	   FbMemTextOut,		   FbMemTextOutLen,
	FbMemSetPixel,	  SetFbMemory,			GetFbMemory,
	FbMemSetFont,	   FbMemGetFont,		   FbMemSetBackColor,
	FbMemGetBackColor,  FbMemSetForeColor,	  FbMemGetForeColor,
	FbMemSetBrushColor, FbMemGetBrushColor						  };

