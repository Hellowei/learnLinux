
#ifndef MYFB_H
#define MYFB_H


#define MAX_FB_LAYER		2
#define MAX_RECT_AREA_NUM  32

#define BASE_FB_LAYER	   0
#define DIALOG_FB_LAYER	 1


#ifdef  MYFB_GLOBALS
#define MYFB_EXT 
#else 
#define MYFB_EXT extern 
#endif

#ifdef QVFB_DEBUG
#define QT_VFB_MOUSE_PIPE	"/tmp/.qtvfb_mouse-0"
#define QT_VFB_KEYBOARD_PIPE "/tmp/.qtvfb_keyboard-0"

struct QVFbHeader
{
	int width;
	int height;
	int depth;
	int linestep;
	int dataoffset;
	RECT update;
	unsigned char dirty;
	int numcols;
	unsigned int clut[256];
};

struct _fb {
	struct QVFbHeader *hdr;
	unsigned char *data;
	int size;
	int BitsPerPixel;
	int BytesPerPixel;
	int linesize;
	int Rmask;
	int Gmask;
	int Bmask;
	int Amask;
};

extern struct QVFbHeader *hdr;

extern RECT fbrect;

#endif


MYFB_EXT INT  fb_open();
MYFB_EXT VOID fb_bitmap_conv(UINT8 * bitmap);
MYFB_EXT VOID fb_setpixel(INT fb_level, INT x, INT y, UINT8 red, UINT8 green, UINT8 blue);
MYFB_EXT VOID fb_getpixel(INT x, INT y, UINT8 *red, UINT8 *green, UINT8 *blue);
MYFB_EXT VOID fb_fillrect(INT fb_level, INT left, INT top, INT right, INT bottom, UINT8 red, UINT8 green, UINT8 blue);
MYFB_EXT VOID fb_clear();
MYFB_EXT VOID fb_close();
MYFB_EXT VOID fb_putlinemem(INT fb_level, INT x, INT y, INT width, VOID * mem);
MYFB_EXT VOID fb_putmem_ex(INT fb_level, INT x, INT y, int width, INT height, VOID * mem, INT mem_line_len, INT reverse);
MYFB_EXT VOID fb_getmem(INT x, INT y, INT width, INT height, VOID * mem);
MYFB_EXT void fb_getlinemem(int x, int y, int width, void * mem);
MYFB_EXT int  fb_getBpp(void);

MYFB_EXT void fb_set_pixel_ex(HDC hdc, int x, int y, char r, char g, char b);

#if MYFB_RECORD_DEBUG
MYFB_EXT VOID myfb_debug_pixel (UINT8 *pbmp, INT32 offset);
MYFB_EXT VOID myfb_debug_line (UINT8 *pbmp, INT32 start_x, INT32 end_x);
#endif

#if _ENB_VIRTUAL_FB
MYFB_EXT void update_fb_ex(char rotate);
#endif

#endif

