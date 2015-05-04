
#ifndef FBMEM_H
#define FBMEM_H

typedef struct _bitmap_memory{
	short		   bits;   //图像每像素位数
	short		   free;   //是否需要释放内存
	long			cx;	 //图像的水平分辨率
	long			cy;	 //图象的垂直分辨率
	unsigned char   *data;  //图像显存
}BITMAPMEM, *PBITMAPMEM;

typedef struct _fb_mem_func{
	GAL_PIXEL   backColor;
	GAL_PIXEL   foreColor;
	GAL_PIXEL   brushColor;
	PLOGFONT	pLogfont;
	PBITMAPMEM  mem;
	void		(*New)		  (struct _fb_mem_func *this, int width, int height, int pixelbits);
	void		(*NewBmp)	   (struct _fb_mem_func *this, unsigned char *pBitmap, char pixel_bits);
	void		(*Destroy)	  (struct _fb_mem_func *this);
	void		(*Output)	   (struct _fb_mem_func *this, HDC hdc, long x, long y);
	void		(*FillRect)	 (struct _fb_mem_func *this, PRECT prc);
	void		(*Line)		 (struct _fb_mem_func *this, long x0, long x1, long y0, long y1);
	void		(*PutIcon)	  (struct _fb_mem_func *this, unsigned char * imgP, long x, long y, long w, long h);
	void		(*TextOut)	  (struct _fb_mem_func *this, long x, long y, const char* text);
	void		(*TextOutLen)   (struct _fb_mem_func *this, long x, long y, const char* text, long len);
	void		(*SetPixel)	 (struct _fb_mem_func *this, long x, long y, GAL_PIXEL pixel);
	PBITMAPMEM  (*SetMenory)	(struct _fb_mem_func *this, BITMAPMEM * mem);
	PBITMAPMEM  (*GetMenory)	(struct _fb_mem_func *this);
	PLOGFONT	(*SetFont)	  (struct _fb_mem_func *this, PLOGFONT pLogfont);
	PLOGFONT	(*GetFont)	  (struct _fb_mem_func *this);
	GAL_PIXEL   (*SetBackColor) (struct _fb_mem_func *this, GAL_PIXEL color);
	GAL_PIXEL   (*GetBackColor) (struct _fb_mem_func *this);
	GAL_PIXEL   (*SetForeColor) (struct _fb_mem_func *this, GAL_PIXEL color);
	GAL_PIXEL   (*GetForeColor) (struct _fb_mem_func *this);
	GAL_PIXEL   (*SetBrushColor)(struct _fb_mem_func *this, GAL_PIXEL color);
	GAL_PIXEL   (*GetBrushColor)(struct _fb_mem_func *this);
}FBMEMFUNC, *PFBMEM;

extern FBMEMFUNC FbMem;

#endif

