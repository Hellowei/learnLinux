#define  MYFB_GLOBALS
#include "includes.h"

#include "config.h"
#include "basetypes.h"
#include "mycommon.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "myfb.h"

#ifdef QVFB_DEBUG
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#endif

#define traceout printf

#if !defined( TRUE ) || ( TRUE != 1 )
#undef  TRUE
#define TRUE	1
#endif

#if !defined( FALSE ) || ( FALSE != 0 )
#undef  FALSE
#define FALSE   0
#endif

/* a framebuffer device structure */
typedef struct fbdev
{
	int fb;
	unsigned long fb_mem_offset;
	unsigned long fb_mem;
	struct fb_fix_screeninfo fb_fix;
	struct fb_var_screeninfo fb_var;
	char dev[20];
} FBDEV, *PFBDEV;

#ifdef QVFB_DEBUG
unsigned char	 *shmrgn;
struct _fb		 fb;
struct QVFbHeader *hdr;
RECT			   fbrect;
#endif

static FBDEV sfbdev;

static unsigned int sfbxpos[SCREEN_WIDTH];
static unsigned int sfbypos[SCREEN_HIGH];

// 分成3层，每层每次可以记住4个区域
static int fb_rect_num[MAX_FB_LAYER];
static RECT fb_rect_list[MAX_FB_LAYER][MAX_RECT_AREA_NUM];

#if _ENB_VIRTUAL_FB
static unsigned char virtual_fb[SCREEN_WIDTH * SCREEN_HIGH * 2];
static unsigned char *pVFB = virtual_fb;
#endif
#if PIXEL_BIT_16
static unsigned char fb_buff_level[MAX_FB_LAYER][SCREEN_WIDTH * SCREEN_HIGH * 2];
static unsigned char fb_tmp[SCREEN_WIDTH * SCREEN_HIGH * 2];
#endif

#define PAGE_MASK 0xfffff000


#if  PIXEL_BIT_16
unsigned short fb_color(unsigned char r, unsigned char g, unsigned char b)
{
	unsigned short color = 0;
	color |= (b >> 3);
	color |= (g >> 2) << 5;
	color |= (r >> 3) << 11;
#if QVFB_DEBUG
	hdr->update = fbrect;
	hdr->dirty = 1;
#endif
	return color;
}
#endif

#if QVFB_DEBUG
#include <stdio.h>
#include <fcntl.h>
#include <sys/select.h>
int   mouse_fd = -1;
int fb_open()
{
	int i = 0;
	char file [50];
	key_t key;
	int shmid;

	sprintf (file, QT_VFB_MOUSE_PIPE);
	key = ftok (file, 'b');
	shmid = shmget (key, 0, 0);

	if (shmid != -1)
		shmrgn = (unsigned char *)shmat (shmid, 0, 0);
	else {
		printf("[luther.gliethttp] shmid=-1\n");
		return -1;
	}

	fb.hdr   = hdr  = (struct QVFbHeader *) shmrgn;
	fb.data		 = (char *)hdr + hdr->dataoffset;
	fb.linesize	 = hdr->linestep;
	fb.BitsPerPixel = hdr->depth;
	
	switch (fb.BitsPerPixel) {
		case 8:
			fb.BytesPerPixel = 1;
			hdr->numcols = 256;
			break;
		case 12:
			fb.BitsPerPixel = 16;
			fb.BytesPerPixel = 2;
			fb.Rmask = 0x00000F00;
			fb.Gmask = 0x000000F0;
			fb.Bmask = 0x0000000F;
			break;
		case 16:
			fb.BytesPerPixel = 2;
			fb.Rmask = 0x0000F800; // R:G:B=5:6:5模式
			fb.Gmask = 0x000007E0;
			fb.Bmask = 0x0000001F;
			break;
		case 32:
			fb.BytesPerPixel = 4;
			fb.Rmask = 0x00FF0000;
			fb.Gmask = 0x0000FF00;
			fb.Bmask = 0x000000FF;
			break;
		default:
			printf("[luther.gliethttp] bits error!\n");
			return -1;
	}

	fbrect.left   = 0;
	fbrect.top	= 0;
	fbrect.right  = fb.hdr->width; 
	fbrect.bottom = fb.hdr->height;
	hdr->update   = fbrect;

	sfbdev.fb_var.bits_per_pixel = fb.BitsPerPixel;
	sfbdev.fb_fix.line_length	= fb.linesize;
	printf("width	 = %d\n"
		   "height	= %d\n"
		   "depth	 = %d\n"
		   "linestep  = %d\n"
		   "dataoffs  = %d\n"
		   "dirty	 = %d\n"
		   "numcols   = %d\n"
		   "left	  = %d\n"
		   "top	   = %d\n"
		   "right	 = %d\n"
		   "bottom	= %d\n",
		   hdr->width,
		   hdr->height,
		   hdr->depth,
		   hdr->linestep,
		   hdr->dataoffset,
		   hdr->dirty,
		   hdr->numcols,
		   hdr->update.left,
		   hdr->update.top,
		   hdr->update.right,
		   hdr->update.bottom);

	//为了减少计算量
	for (i = 0; i < SCREEN_WIDTH; ++i)
		sfbxpos[i] = i * (sfbdev.fb_var.bits_per_pixel / 8);

	for (i = 0; i < SCREEN_HIGH; ++i)
		sfbypos[i] = i * sfbdev.fb_fix.line_length;

	for (i = 0; i < MAX_FB_LAYER; ++i)
		fb_rect_num[i] = 0;

	if(( mouse_fd = open("/tmp/.qtvfb_mouse-0", O_RDONLY))<0)
	{
		printf("Failed to open \"/tmp/.qtvfb_mouse-0\".\n");
		return;
	}
	else
	{
		printf("open \"/tmp/.qtvfb_mouse-0\" successfuly.\n");
	}

	return TRUE;
}
#define NOBUTTON			  0x0000
#define LEFTBUTTON			0x0001
#define RIGHTBUTTON		   0x0002
#define MIDBUTTON			 0x0004
#define MOUSEBUTTONMASK	   0x00FF

static POINT mouse_pt;
static int   mouse_buttons;


static int mouse_update (void)
{
	int ret1;
	int ret2;

	POINT l_mouse_pt;
	int   l_mouse_buttons;

	lseek(mouse_fd, 0, SEEK_SET);
	ret1 = read(mouse_fd, &l_mouse_pt,	  sizeof(POINT));
	ret2 = read(mouse_fd, &l_mouse_buttons, sizeof(int));

	if (ret1 == sizeof(POINT)
	 && ret2
	 && sizeof(int)
	 && l_mouse_buttons < 0x08) {

		mouse_pt	  = l_mouse_pt;
		mouse_buttons = l_mouse_buttons;
	}
	else {
		return 0;
	}

	return 1;
}

static void mouse_getxy (int *x, int *y)
{
	*x = mouse_pt.x;
	*y = mouse_pt.y;
}

static int mouse_getbutton (void)
{
	int buttons = 0;

	if (mouse_buttons & LEFTBUTTON)
		buttons |= 1;

	if (mouse_buttons & RIGHTBUTTON)
		buttons |= 4;

	if (mouse_buttons & MIDBUTTON)
		buttons |= 2;

	return buttons;
}

int QvfbServer (void)
{
	char   file[50];
	int	display = 0;

	sprintf(file, QT_VFB_MOUSE_PIPE, display); /* open mouse pipe */

	if ((mouse_fd = open(file, O_RDONLY)) < 0) {
		fprintf(stderr, "QVFB IAL engine: can not open mouse pipe.\n");

		return -1;
	}
#if 0
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(mouse_fd, &rfds);
	for (;;) {
		if (select(FD_SETSIZE, &rfds, 0, 0, 0) > 0)
		{
			if (FD_ISSET(mouse_fd, &rfds))
			{
				if (mouse_update()) {
					int x;
					int y;
					int buttons;
					mouse_getxy(&x, &y);

					buttons = mouse_getbutton();

					//if (LEFTBUTTON == buttons)
						printf("[mouse] [%04d,%04d,%01d]\n", x, y, buttons);
/*
					if (LEFTBUTTON == buttons)
						PostMessage(SysGui_HTSK, MSG_USER_SYS_TOUCHMSG,
									TOUCH_PRESSED,
									(x << 16) | y);
*/
				}
			}
		}
	}
#endif
	
	int fd, retval;
	short buf[3];
	short release;
	short xpos,ypos;
	unsigned char output[5];
	fd_set readfds;
	struct timeval tv;
	release = 0;
	fd = mouse_fd;
	printf("fd,,,%d\r\n", fd);
	while(1)
	{
		tv.tv_sec = 50;
		tv.tv_usec = 0;

		FD_ZERO(&readfds);
		FD_SET(fd, &readfds);

		retval = select(1, &readfds, NULL, NULL, &tv);
		if(FD_ISSET(fd,&readfds))
		{
			if(read(fd, buf, 6) <= 0)//终端设备，一次只能读取一行
			{
				continue;
			}
			if (buf[0] || buf[2])
			{
				xpos = buf[0];
				ypos = buf[2];
			}

			if(release == 1 && buf[1] == 0)
			{
				output[0] = 0x80;
			}
			else if (buf[1] == 1)
			{
				output[0] = 0x81;
			}
			else
			{
				output[0] = 0;
			}
			if (output[0])
			{
				printf("post x:%4d, y:%4d, btn:%d\n", xpos, ypos, release);
				output[1] = ((xpos >> 7) & 0x7f);
				output[2] = (xpos & 0x7f);
				output[3] = ((ypos >> 7) & 0x7f);
				output[4] = (ypos & 0x7f);
				//printf("send: 0x%02x, 0x%02x, 0x%02x, 0x%02x, 0x%02x\r\n", output[0], output[1], output[2], output[3], output[4]);
			}
			release = buf[1];
		}
	}
	close(fd);
}

#else
// Initialize frame buffer
int fb_open()
{
	int i = 0;
	memset(&sfbdev, 0, sizeof(FBDEV));
	strcpy(sfbdev.dev, "/dev/fb0");

	sfbdev.fb = open(sfbdev.dev, O_RDWR);
	if(sfbdev.fb < 0)
	{
		traceout("Error opening %s: %m. Check kernel config\n", sfbdev.dev);
		return FALSE;
	}

	if (-1 == ioctl(sfbdev.fb, FBIOGET_VSCREENINFO, &(sfbdev.fb_var)))
	{
		traceout("ioctl FBIOGET_VSCREENINFO\n");
		return FALSE;
	}

	if (-1 == ioctl(sfbdev.fb, FBIOGET_FSCREENINFO, &(sfbdev.fb_fix)))
	{
		traceout("ioctl FBIOGET_FSCREENINFO\n");
		return FALSE;
	}
	
	/* map physics address to virtual address */
	sfbdev.fb_mem_offset = (unsigned long)(sfbdev.fb_fix.smem_start) & (~PAGE_MASK);
	sfbdev.fb_mem = (unsigned long int)mmap(NULL, sfbdev.fb_fix.smem_len + sfbdev.fb_mem_offset,
		PROT_READ | PROT_WRITE, MAP_SHARED, sfbdev.fb, 0);

	if (-1L == (long)sfbdev.fb_mem)
	{
		traceout("mmap error! mem:%d offset:%d\n", sfbdev.fb_mem, sfbdev.fb_mem_offset);
		return FALSE;
	}
	//为了减少计算量
	for (i = 0; i < SCREEN_WIDTH; ++ i)
	{
		sfbxpos[i] = i * (sfbdev.fb_var.bits_per_pixel / 8);
	}
	for (i = 0; i < SCREEN_HIGH; ++ i)
	{
		sfbypos[i] = i * sfbdev.fb_fix.line_length;
	}

	for (i = 0; i < MAX_FB_LAYER; ++ i)
	{
		fb_rect_num[i] = 0;
	}
	return TRUE;
}
#endif
// 预处理位图数据
void fb_bitmap_conv(unsigned char * bitmap)
{
	INT32 w, h, line_bytes;
	BITMAPFILEHEADER BitHeader;			 //BMP文件结构的头
	BITMAPINFOHEADER BitInfoHeader;		 //BMP位图信息头	
	unsigned char * data, * bits;

	memcpy(&BitHeader, bitmap, sizeof(BITMAPFILEHEADER));
	bits = bitmap + BitHeader.bfOffBits; // 保存图象数据的开始地址
	
	// 打开BMP位图信息头
	memcpy(&BitInfoHeader, bitmap + sizeof(BITMAPFILEHEADER), sizeof(BITMAPINFOHEADER));

	line_bytes = (((BitInfoHeader.biWidth * BitInfoHeader.biBitCount + 31) >> 5) << 2);
	int mem_line_len = BitInfoHeader.biWidth * sfbdev.fb_var.bits_per_pixel / 8;

	for (h = 0; h < BitInfoHeader.biHeight; h++) 
	{
		data = bits;
		for (w = 0; w < BitInfoHeader.biWidth; w++) 
		{
			unsigned char tmp = data[2];
			data[2] = data[0];
			data[0] = tmp;
			data = data + 3;
		}
		bits = bits + line_bytes;		
	 }
}


#if _ENB_VIRTUAL_FB
BOOL gGphRotate = FALSE;
void rotate_fb_setpixel(int x, int y)
{
	if (gGphRotate == FALSE)
		return;
	unsigned char *pReal = 
		(unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
	unsigned char *p = pReal + sfbxpos[SCREEN_WIDTH - x - 1]
		+ sfbypos[SCREEN_HIGH - y - 1];
#if PIXEL_BIT_16
	*p++ = *(pVFB + sfbxpos[x] + sfbypos[y]);
	*p = *(pVFB + sfbxpos[x] + sfbypos[y] + 1);
#endif
}

void rotate_fb_rect(PRECT prc)
{
	if (prc->left < 0)
	{
		prc->left = 0;
	}
	if (prc->right > SCREEN_WIDTH - 1)
	{
		prc->right = SCREEN_WIDTH - 1;
	}
	if (prc->top < 0)
	{
		prc->top = 0;
	}
	if (prc->bottom > SCREEN_HIGH - 1)
	{
		prc->bottom = SCREEN_HIGH - 1;
	}
	int i, j;
	for (i = prc->top; i < prc->bottom + 1; i++)
	{
		for (j = prc->left; j < prc->right + 1; j++)
		{
			rotate_fb_setpixel(j, i);
		}
	}
}
#endif

// Set pixel
void fb_setpixel(int fb_level, int x, int y, unsigned char red, unsigned char green, unsigned char blue)
{
	  if (MonitorInfo.standby)
		  return;
		  
#if QVFB_DEBUG
	unsigned char *p = fb.data;
#else
	unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif
#if _ENB_VIRTUAL_FB
	p = pVFB;
#endif
	if (fb_level != DIALOG_FB_LAYER)
	{
		int i = 0, num = fb_rect_num[DIALOG_FB_LAYER];
		for (i = 0; i < num; ++ i)
		{
			if (PtInRect(&(fb_rect_list[DIALOG_FB_LAYER][i]), x, y))
			{
				p = fb_buff_level[fb_level];
				break;
			}
		}
	}

	p += sfbypos[y] + sfbxpos[x];

#if PIXEL_BIT_16
	unsigned short * pp = (unsigned short *)p;
	*pp = fb_color(red, green, blue);
#endif
#if _ENB_VIRTUAL_FB
	rotate_fb_setpixel(x, y);
#endif

}

// Get pixel
void fb_getpixel(int x, int y, unsigned char *red, unsigned char *green, unsigned char *blue)
{
#if QVFB_DEBUG
	unsigned char *p = fb.data;
#else
	unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif
	p += sfbypos[y] + sfbxpos[x];  

#if PIXEL_BIT_16
	unsigned short color = *((unsigned short *)p);
	*red = ((color >> 11) & 0x1f) << 3;
	*green = ((color >> 5) & 0x3f) << 2;
	*blue = ((color >> 0) & 0x1f) << 3;
#endif
}


// 目前只处理只有一个矩形的情况
void fb_hline(int fb_level, int x0, int x1, int y, unsigned char red, unsigned char green, unsigned char blue)
{
	int i;
	  if (x0 > x1)
	  {
		int tmp = x1;
		x1 = x0;
		x0 = tmp;
	}

	int width = x1 - x0;
  
	unsigned char buff[SCREEN_WIDTH* 2];
	unsigned char * p = buff;

	for (i = 0; i < width; ++ i)
	{	 
#if PIXEL_BIT_16
		unsigned short * pp = (unsigned short *)p;
		*pp ++= fb_color(red, green, blue);
		p = (unsigned char *)pp;
#endif
	}

	fb_putlinemem(fb_level, x0, y, width, buff);
}


// 目前只处理只有一个矩形的情况
void fb_vline(int fb_level, int y0, int y1, int x, unsigned char red, unsigned char green, unsigned char blue)
{
	
	if (MonitorInfo.standby)
		return;
		
	int y;
	
	if (y0 > y1)
	{
		int tmp = y1;
		y1 = y0;
		y0 = tmp;
	}
	
	int num = fb_rect_num[DIALOG_FB_LAYER];
	RECT rc = fb_rect_list[DIALOG_FB_LAYER][0];

	// 在对话框图层上面，或者线与矩形没有交点。
	// 这种情况是最多的，所以先处理，提高执行效率
	if ((fb_level == DIALOG_FB_LAYER) || (num <= 0) || (x < rc.left) || (x >= rc.right) || (y1 < rc.top) || (y0 >= rc.bottom))
	{
#if QVFB_DEBUG
		unsigned char *p = fb.data;
#else
		unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif	
#if _ENB_VIRTUAL_FB
		p = pVFB;
#endif
		p += sfbypos[y0] + sfbxpos[x];
		for (y = y0; y < y1; ++ y)
		{
			
	#if PIXEL_BIT_16
			unsigned short * pp = (unsigned short *)p;
			*pp = fb_color(red, green, blue);
	#endif	
			p += sfbdev.fb_fix.line_length;
		}
		  return;
	}

  
	// 线全部在矩形内部
	if ((y0 >= rc.top) && (y1 < rc.bottom))
	{
		unsigned char *p = fb_buff_level[fb_level];
		p += sfbypos[y0] + sfbxpos[x];
		for (y = y0; y < y1; ++ y)
		{
			
	#if PIXEL_BIT_16
			unsigned short * pp = (unsigned short *)p;
			*pp = fb_color(red, green, blue);
	#endif	
			p += sfbdev.fb_fix.line_length;
		}
		  return;
	}

	// 剩下的那些情况很少发生，所以直接调用打点函数，简化程序
	for (y = y0; y < y1; ++ y)
	{
		fb_setpixel(fb_level, x, y, red, green, blue);
	}
}

// The soame point, no pixel out
void fb_line(int fb_level, int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b)
{
	int dx, dy, h, x, y, t; 
	 
	if(x1 > x2)
	{
		int tmp;
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	
		tmp = y1;
		y1 = y2;
		y2 = tmp;
	}
  
	dx = x2-x1; 
	dy = y2-y1; 
	x = x1;
	y = y1; 

  // for oxyCRG parameters 
  fb_setpixel(fb_level, x, y, r, g, b);
  
  if (dx == 0) 
  { 
	fb_vline(fb_level, y1, y2, x, r, g, b);
	return;
  }
  
  if(dy == 0) 
  {
	fb_hline(fb_level, x1, x2, y1, r, g, b);
	return;
  }

  if (dy > 0)
  {
	if (dy <= dx) 
	{ 
	  h = 2 * dy - dx; 
	  while (x != x2) 
	  { 
		if (h < 0) 
		{
		  h += 2 * dy; 
		}
		else 
		{ 
		  y ++; 
		  h += 2 * (dy - dx); 
		} 
		fb_setpixel(fb_level, x, y, r, g, b);
		x ++; 
	  } 
	} 
	else 
	{ 
	  h = 2 * dx - dy; 
	  while (y != y2) 
	  { 
		if(h < 0) 
		{
		  h += 2 * dx; 
		}
		else 
		{ 
		  ++ x; 
		  h += 2 * (dx - dy); 
		} 
		fb_setpixel(fb_level, x, y, r, g, b);
		y ++; 
	  } 
	} 
  }
  else 
  { 
	t = -dy; 
	if (t <= dx) 
	{ 
	  h = 2 * dy + dx; 
	  while (x != x2) 
	  { 
		if (h < 0) 
		{ 
		  h += 2 * (dy + dx); 
		  y --; 
		} 
		else 
		{
		  h += 2 * dy; 
		}
		fb_setpixel(fb_level, x, y, r, g, b);
		x ++; 
	  } 
	} 
	else 
	{ 
	  h = -(2 * dx * dy) - (dy * dy); 
	  while (y != y2) 
	  { 
		if (h < 0) 
		{
		  h += -(2 * dx * dy); 
		}
		else 
		{ 
		  h += -(2 * dx * dy) - (2 * dy * dy); 
		  x ++; 
		} 
		fb_setpixel(fb_level, x, y, r, g, b);
		y --; 
	  } 
	} 
  } 
}
 


void fb_fillrect(int fb_level, int left, int top, int right, int bottom, unsigned char red, unsigned char green, unsigned char blue)
{
	int i = 0;
	int width = right - left;
	int x = left, y;

	unsigned char buff[SCREEN_WIDTH * 3];
	unsigned char * p = buff;
	for (i = 0; i < width; ++ i)
	{
	  
#if PIXEL_BIT_16
		unsigned short * pp = (unsigned short *)p;
		*pp ++= fb_color(red, green, blue);
		p = (unsigned char *)pp;
#endif

	}

	for (y = top; y < bottom; ++ y)
	{
		fb_putlinemem(fb_level, x, y, width, buff);
	}
}

// 这里给出的数据是根据FB特性，已经格式化好的数据。
// 只需要直接memcpy就可以了。
// 所以，这个函数支持24跟16位色
void fb_putlinemem(int fb_level, int x, int y, int width, void * mem)
{
	if (MonitorInfo.standby)
		return;
	int i;
	int j;
	int num = fb_rect_num[DIALOG_FB_LAYER];
	RECT rc = fb_rect_list[DIALOG_FB_LAYER][0];

	int x0 = x, x1 = x + width;

	unsigned char * tmp_mem = mem;
	int mem_len = width * sfbdev.fb_var.bits_per_pixel / 8;
	i = 0;
	//for (i = 0; i < num; i++)
	{
		rc = fb_rect_list[DIALOG_FB_LAYER][i];
		// 在对话框图层上面，或者水平线与矩形没有交点。这种情况是最多的，所以先处理，提高执行效率
		if ((fb_level == DIALOG_FB_LAYER) || (num <= 0) || (x1 < rc.left) || (x0 >= rc.right) || (y < rc.top) || (y >= rc.bottom))
		  {
#if QVFB_DEBUG
			  unsigned char *p = fb.data;
#else
			  unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif  
#if _ENB_VIRTUAL_FB
			  p = pVFB;
#endif
			  p += sfbypos[y] + sfbxpos[x0];
			memcpy(p, tmp_mem, mem_len);
			  return;
		}

		// 水平线全部在矩形内部
		if ((x0 >= rc.left) && (x1 < rc.right)) 
		{
			  unsigned char *p = fb_buff_level[fb_level];
			  p += sfbypos[y] + sfbxpos[x0];
			  
			  memcpy(p, tmp_mem, mem_len);
			  return;
		}

		// 左半部分在矩形内部
		if ((x0 >= rc.left) && (x1 >= rc.right))
		{
			  unsigned char *p = fb_buff_level[fb_level];
			  p += sfbypos[y] + sfbxpos[x0];
			  mem_len = (rc.right - x0) * sfbdev.fb_var.bits_per_pixel / 8;
			  memcpy(p, tmp_mem, mem_len);
			  tmp_mem += mem_len;

#if QVFB_DEBUG
			p = fb.data;
#else
			p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif  
#if _ENB_VIRTUAL_FB
			p = pVFB;
#endif
			p += sfbypos[y] + sfbxpos[rc.right];
			mem_len = (x1 - rc.right) * sfbdev.fb_var.bits_per_pixel / 8;
			
			  memcpy(p, tmp_mem, mem_len);
			  return;
		}

		// 水平线的右半部分在矩形内部
		if ((x0 < rc.left) && (x1 < rc.right))
		{
#if QVFB_DEBUG
			unsigned char *p = fb.data;
#else
			unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif  
#if _ENB_VIRTUAL_FB
			  p = pVFB;
#endif
			  p += sfbypos[y] + sfbxpos[x0];

			  mem_len = (rc.left - x0) * sfbdev.fb_var.bits_per_pixel / 8;
			  memcpy(p, tmp_mem, mem_len);	  
			  tmp_mem += mem_len;

			  p = fb_buff_level[fb_level];
			  p += sfbypos[y] + sfbxpos[rc.left];
			  mem_len = (x1 - rc.left ) * sfbdev.fb_var.bits_per_pixel / 8;

			  memcpy(p, tmp_mem, mem_len);	  
			  tmp_mem += mem_len;
			  return;
		}	

		// 水平线中间部分被矩形覆盖
		if ((x0 < rc.left) && (x1 >= rc.right))
		{
#if QVFB_DEBUG
			unsigned char *p = fb.data;
#else
			unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif  
#if _ENB_VIRTUAL_FB
			p = pVFB;
#endif
			p += sfbypos[y] + sfbxpos[x0];

			  mem_len = (rc.left - x0) * sfbdev.fb_var.bits_per_pixel / 8;
			  memcpy(p, tmp_mem, mem_len);	  
			  tmp_mem += mem_len;
			
			  p = fb_buff_level[fb_level];
			  p += sfbypos[y] + sfbxpos[rc.left];
			  mem_len = (rc.right - rc.left) * sfbdev.fb_var.bits_per_pixel / 8;
			  memcpy(p, tmp_mem, mem_len);	  
			  tmp_mem += mem_len;

			p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#if _ENB_VIRTUAL_FB
			p = pVFB;
#endif
			p += sfbypos[y] + sfbxpos[rc.right];
			  mem_len = (x1 - rc.right) * sfbdev.fb_var.bits_per_pixel / 8;
			  memcpy(p, tmp_mem, mem_len);	  
			  tmp_mem += mem_len;
			  return;
		}
	}
}

#if 1
//扩展的fb_getlinemen
void fb_getlinemem2(int fb_level,int x, int y, int width, void * mem)
{
	int num;
	static unsigned char * tmp_mem;
	static unsigned char * pbase;
	static unsigned char * pdlg;
	static unsigned char *p;
	
	num = fb_rect_num[DIALOG_FB_LAYER];
	if(num > 0 && fb_level == BASE_FB_LAYER)
	{
		int x0;
		int x1;
		int i;
		x0 = x;
		x1 = x + width;
		for (i = 0; i < num; i++)
		{
			RECT			rc;
			rc = fb_rect_list[DIALOG_FB_LAYER][i];
			if ((PtInRect(&rc, x0, y)) && (PtInRect(&rc, x1, y)))
			{
				int mem_len;
				mem_len = width * sfbdev.fb_var.bits_per_pixel / 8;
				p = &fb_buff_level[BASE_FB_LAYER][0];
				p += sfbypos[y] + sfbxpos[x];
				memcpy(mem, p, mem_len);
			}
			else
				if (PtInRect(&rc, x0, y))
			{
				int mem_len1, mem_len2, offset;
				tmp_mem = (unsigned char *)mem;
				mem_len1 = (rc.right - x0) * sfbdev.fb_var.bits_per_pixel / 8;
				mem_len2 = (x1 - rc.right) * sfbdev.fb_var.bits_per_pixel / 8;
				pbase = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#if _ENB_VIRTUAL_FB
				pbase = pVFB;
#endif
				pdlg  = &fb_buff_level[BASE_FB_LAYER][0];
				offset = sfbypos[y] + sfbxpos[x];
				pdlg += offset;
				memcpy(tmp_mem, pdlg, mem_len1);
				tmp_mem += mem_len1;
				pbase += offset + mem_len1;
				memcpy(tmp_mem, pbase, mem_len2);
			}
			else 
				if (PtInRect(&rc, x1, y))
			{
				int mem_len1, mem_len2, offset;
				tmp_mem = (unsigned char *)mem;
				mem_len1 = (rc.left - x0) * sfbdev.fb_var.bits_per_pixel / 8;
				mem_len2 = (x1 - rc.left) * sfbdev.fb_var.bits_per_pixel / 8;
				pbase = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#if _ENB_VIRTUAL_FB
				pbase = pVFB;
#endif
				pdlg  = &fb_buff_level[BASE_FB_LAYER][0];
				offset = sfbypos[y] + sfbxpos[x];
				pbase += offset;
				memcpy(tmp_mem, pbase, mem_len1);
				tmp_mem += mem_len1;
				pdlg += offset + mem_len1;
				memcpy(tmp_mem, pdlg, mem_len2);
			}
			else
			{
				fb_getlinemem(x, y, width, mem);
			}
		}
	}
	else
	{
		fb_getlinemem(x, y, width, mem);
	}
}
#endif

void fb_getlinemem(int x, int y, int width, void * mem)
{
	int mem_len = width * sfbdev.fb_var.bits_per_pixel / 8;
#if QVFB_DEBUG
	unsigned char *p = fb.data;
#else
	unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif  
#if _ENB_VIRTUAL_FB
	p = pVFB;
#endif
	p += sfbypos[y] + sfbxpos[x];
	memcpy(mem, p, mem_len);
}

// 也是支持24，16位
void fb_putmem(int fb_level, int x, int y, int width, int height, void * mem, int mem_line_len, int reverse)
{
	int i = 0;	
	unsigned char * p = (unsigned char *)mem;
#if PIXEL_BIT_16
	int j = 0;
	unsigned char red, green, blue;
	unsigned short * pp = malloc(width * height * 2);
#endif
	
	if (reverse != 0)
	{
		for (i = 0; i < height; ++ i)
		{
		#if PIXEL_BIT_24
			fb_putlinemem(fb_level, x, y + height - i - 1, width, p);
			p += mem_line_len;
		#endif
		#if PIXEL_BIT_16
			for(j = 0;j < width; j++)
			{
				red = *p;
				p++;
				green = *p;
				p++;
				blue = *p;
				p++;
				*(pp+j) = fb_color(red, green, blue);
			}		   
			fb_putlinemem(fb_level, x, y + height - i - 1, width, pp);
			p += (mem_line_len - width * 3);			
		#endif
		}
	}
	else
	{
		for (i = 0; i < height; ++ i)
		{
		#if PIXEL_BIT_24
			fb_putlinemem(fb_level, x, y + i, width, p);
			p += mem_line_len;
		#endif
		#if PIXEL_BIT_16
			for(j = 0; j < width; j++)
			{
				red = *p;
				p++;
				green = *p;
				p++;
				blue = *p;
				p++;
				*(pp+j) = fb_color(red, green, blue);
			}	
			
			fb_putlinemem(fb_level, x, y + i, width, pp);
			p += (mem_line_len - width * 3);			
		#endif
		}
	}
#if PIXEL_BIT_16
	free(pp);
#endif
}

void fb_getmem(int x, int y, int width, int height, void * mem)
{
	int i = 0;
	unsigned char * tmp_mem = mem;
	int mem_line_len = width * sfbdev.fb_var.bits_per_pixel / 8;
#if QVFB_DEBUG
	unsigned char *p = fb.data;
#else
	unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif  
#if _ENB_VIRTUAL_FB
	p = pVFB;
#endif
	p += sfbypos[y] + sfbxpos[x];

	for (i = 0; i < height; ++ i)
	{
		memcpy(tmp_mem, p, mem_line_len);
		p += sfbdev.fb_fix.line_length;
		tmp_mem += mem_line_len;
	}
}

void fb_clear()
{
#if QVFB_DEBUG
	unsigned char *p = fb.data;
#else
	unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif  
	memset(p, 0, sfbdev.fb_fix.smem_len);
#if _ENB_VIRTUAL_FB
	p = pVFB;
	memset(p, 0, sfbdev.fb_fix.smem_len);
#endif
}

void fb_close()
{
  close(sfbdev.fb);
  sfbdev.fb = -1;  
}



void fb_memcpy(unsigned char * dst, unsigned char * src, RECT rc)
{
	int x, y;
	int line_len = (rc.right - rc.left) * sfbdev.fb_var.bits_per_pixel / 8;

	x = rc.left;
	for (y = rc.top; y < rc.bottom; ++ y)
	{
		unsigned char *pdst = dst + sfbypos[y] + sfbxpos[x];	
		unsigned char *psrc = src + sfbypos[y] + sfbxpos[x];
		memcpy(pdst, psrc, line_len);
	}
}

void fb_putlinemem_ex(int fb_level, int x, int y, int width, void * mem)
{
	
	int j;
	int num = fb_rect_num[DIALOG_FB_LAYER];
	RECT rc = fb_rect_list[DIALOG_FB_LAYER][0];
	int x0 = x, x1 = x + width;

	unsigned char * tmp_mem = mem;
	int mem_len = width * sfbdev.fb_var.bits_per_pixel / 8;
	// 在对话框图层上面，或者水平线与矩形没有交点。这种情况是最多的，所以先处理，提高执行效率
	if ((fb_level == DIALOG_FB_LAYER) || (num <= 0) || (x1 < rc.left) || (x0 >= rc.right) || (y < rc.top) || (y >= rc.bottom))
	  {
#if QVFB_DEBUG
		  unsigned char *p = fb.data;
#else
		  unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif  
#if _ENB_VIRTUAL_FB
		  p = pVFB;
#endif
		  p += sfbypos[y] + sfbxpos[x0];
		  memcpy(p, tmp_mem, mem_len);
#if QVFB_DEBUG
		  hdr->update = fbrect;
		  hdr->dirty = 1;
#endif
		  return;
	}

	// 水平线全部在矩形内部
	if ((x0 >= rc.left) && (x1 < rc.right))
	{
		  unsigned char *p = fb_buff_level[fb_level];
		  p += sfbypos[y] + sfbxpos[x0];
		  memcpy(p, tmp_mem, mem_len);
#if QVFB_DEBUG
		  hdr->update = fbrect;
		  hdr->dirty = 1;
#endif
		  return;
	}

	// 左半部分在矩形内部
	if ((x0 >= rc.left) && (x1 >= rc.right))
	{
		  unsigned char *p = fb_buff_level[fb_level];
		  p += sfbypos[y] + sfbxpos[x0];
		  mem_len = (rc.right - x0) * sfbdev.fb_var.bits_per_pixel / 8;

		  memcpy(p, tmp_mem, mem_len);
		  tmp_mem += mem_len;

#if QVFB_DEBUG
		  p = fb.data;
#else
		  p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif  
#if _ENB_VIRTUAL_FB
		  p = pVFB;
#endif
		  p += sfbypos[y] + sfbxpos[rc.right];
		  mem_len = (x1 - rc.right) * sfbdev.fb_var.bits_per_pixel / 8;
		
		  memcpy(p, tmp_mem, mem_len);
#if QVFB_DEBUG
		  hdr->update = fbrect;
		  hdr->dirty = 1;
#endif
	  return;
	}

	// 水平线的右半部分在矩形内部
	if ((x0 < rc.left) && (x1 < rc.right))
	{
#if QVFB_DEBUG
		unsigned char *p = fb.data;
#else
		unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif  
#if _ENB_VIRTUAL_FB
		  p = pVFB;
#endif
		  p += sfbypos[y] + sfbxpos[x0];

		  mem_len = (rc.left - x0) * sfbdev.fb_var.bits_per_pixel / 8;
		  memcpy(p, tmp_mem, mem_len);	  
		  tmp_mem += mem_len;

		  p = fb_buff_level[fb_level];
		  p += sfbypos[y] + sfbxpos[rc.left];
		  mem_len = (x1 - rc.left ) * sfbdev.fb_var.bits_per_pixel / 8;
		  memcpy(p, tmp_mem, mem_len);	  
		  tmp_mem += mem_len;
#if QVFB_DEBUG
		  hdr->update = fbrect;
		  hdr->dirty = 1;
#endif
		  return;
	}	

	// 水平线中间部分被矩形覆盖
	if ((x0 < rc.left) && (x1 >= rc.right))
	{
#if QVFB_DEBUG
		unsigned char *p = fb.data;
#else
		unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif  
#if _ENB_VIRTUAL_FB
		p = pVFB;
#endif
		p += sfbypos[y] + sfbxpos[x0];

		  mem_len = (rc.left - x0) * sfbdev.fb_var.bits_per_pixel / 8;
		  memcpy(p, tmp_mem, mem_len);	  
		  tmp_mem += mem_len;
		
		  p = fb_buff_level[fb_level];
		  p += sfbypos[y] + sfbxpos[rc.left];
		  mem_len = (rc.right - rc.left) * sfbdev.fb_var.bits_per_pixel / 8;
		  memcpy(p, tmp_mem, mem_len);	  
		  tmp_mem += mem_len;

#if QVFB_DEBUG
		p = fb.data;
#else
		p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif  
#if _ENB_VIRTUAL_FB
		p = pVFB;
#endif
		p += sfbypos[y] + sfbxpos[rc.right];
		  mem_len = (x1 - rc.right) * sfbdev.fb_var.bits_per_pixel / 8;
		  memcpy(p, tmp_mem, mem_len);	  
		  tmp_mem += mem_len;
	  
#if QVFB_DEBUG
		hdr->update = fbrect;
		hdr->dirty = 1;
#endif
		  return;
	}
}

void fb_set_pixel_ex(HDC hdc, int x, int y, char r, char g, char b)
{
	if (MonitorInfo.standby == FALSE)
	{
		return SetPixel(hdc, x, y, MakeRGB(r,g,b));
	}
	char *p = (char *)sfbdev.fb_mem;
#if _ENB_VIRTUAL_FB
	p = pVFB;
#endif
#if PIXEL_BIT_16
	unsigned short * pp = (unsigned short *)(p + sfbypos[y] + sfbxpos[x]);
	*pp = fb_color(r, g, b);
#endif
#if _ENB_VIRTUAL_FB
	rotate_fb_setpixel(x, y);
#endif
}

void fb_fillrect_ex(int fb_level, int left, int top, int right, int bottom, unsigned char red, unsigned char green, unsigned char blue)
{
	int i	 = 0;
	int width = right - left;
	int x	 = left, y;

	unsigned char   buff[SCREEN_WIDTH * 3];	// 最多支持24位色
	unsigned char * p = buff;

	for (i = 0; i < width; ++i)
	{
#if PIXEL_BIT_16
		unsigned short * pp = (unsigned short *)p;
		*pp ++= fb_color(red, green, blue);
		p = (unsigned char *)pp;
#endif
	}

	for (y = top; y < bottom; ++y)
	{
		fb_putlinemem_ex(fb_level, x, y, width, buff);
	}
}

// 也是支持24，16位
void fb_putmem_ex(int fb_level, int x, int y, int width, int height, void * mem, int mem_line_len, int reverse)
{
	int i = 0;
#if PIXEL_BIT_24
	unsigned char * p = (unsigned char *)mem;
	
	if (reverse != 0)
	{
		for (i = 0; i < height; ++ i)
		{
			fb_putlinemem_ex(fb_level, x, y + height - i - 1, width, p);
			p += mem_line_len;
		}
	}
	else
	{
		for (i = 0; i < height; ++ i)
		{
			fb_putlinemem_ex(fb_level, x, y + i, width, p);
			p += mem_line_len;
		}
	}
#endif

#if PIXEL_BIT_16
	int j;
	
	unsigned char red,green,blue;
	unsigned char * p = (unsigned char *)mem;
	 unsigned short * pp = malloc(width*height*2);

		 
	if (reverse != 0)
	{
		for (i = 0; i < height; ++ i)
		{
			 for(j=0;j<width;j++)
			{
				red = *p;
				p++;
				green = *p;
				p++;
				blue = *p;
				p++;
				*(pp+j) = fb_color(red, green, blue);
			}
	
			fb_putlinemem_ex(fb_level, x, y + height - i - 1, width, pp);
			p += (mem_line_len-width*3);
		}
	}
	else
	{
		for (i = 0; i < height; ++ i)
		{
		
			 for(j=0;j<width;j++)
			{
				red = *p;
				p++;
				green = *p;
				p++;
				blue = *p;
				p++;
				*(pp+j) = fb_color(red, green, blue);
			}	
		fb_putlinemem_ex(fb_level, x, y + i, width, pp);
		p += (mem_line_len-width*3);		
		}
	}
	 free(pp);
#endif
}


void fb_open_window(int fb_level, RECT rc)
{
	int num = fb_rect_num[fb_level];
	if (num >= MAX_RECT_AREA_NUM )
	{
		return;
	}
	fb_rect_list[fb_level][num] = rc;
	++ fb_rect_num[fb_level];
	// 保存被覆盖区域的图像
#if QVFB_DEBUG
	unsigned char *p = fb.data;
#else
	unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif	
#if _ENB_VIRTUAL_FB
	p = pVFB;
#endif
	fb_memcpy(fb_buff_level[BASE_FB_LAYER], p, rc);
}


void fb_close_window(int fb_level, RECT rc)
{
	int num = fb_rect_num[fb_level];
	if (num <= 0)
	{
		return;
	}
	int i = num - 1;
	for (; i >= 0; -- i)
	{
		if (memcmp(&(fb_rect_list[fb_level][i]), &rc, sizeof(RECT)) == 0)
		{
			break;
		}
	}

	// 恢复被覆盖区域的图像
	if (i >= 0)
	{
#if QVFB_DEBUG
		unsigned char *p = fb.data;
#else
		unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif	
#if _ENB_VIRTUAL_FB
		p = pVFB;
#endif
		fb_memcpy(p, fb_buff_level[BASE_FB_LAYER], rc);
	
		int k = i;
		for (; k < num - 1; ++ k)
		{
			fb_rect_list[fb_level][k] = fb_rect_list[fb_level][k + 1];
		}
		-- fb_rect_num[fb_level];
	}
}


void fb_clear_window(int fb_level)
{
	fb_rect_num[fb_level] = 0;
}

// Bpp not bpp, Bpp means byte per pixel
int fb_getBpp(void)
{
	return (sfbdev.fb_var.bits_per_pixel / 8);
}

// 由于屏幕不是自动更新的，提供区域刷新
void fb_updateLayerRect(int fb_level, PRECT prc)
{
	int fb_size = sfbdev.fb_fix.line_length * SCREEN_HIGH;
	unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#if _ENB_VIRTUAL_FB
	p = pVFB;
#endif
	memcpy(fb_tmp, fb_buff_level[0], fb_size);
	fb_memcpy(fb_tmp, fb_buff_level[fb_level], *prc);
	memcpy(p, fb_tmp, fb_size);
}

// 每5ms更新一次
void update_fb(void)
{
	int i;
	int fb_size = sfbdev.fb_fix.line_length * SCREEN_HIGH;
	
	memcpy(fb_tmp, fb_buff_level[0], fb_size);
	for (i = 1; i < MAX_FB_LAYER; ++ i)
	{
		int k = 0;
		for (k = 0; k < fb_rect_num[i]; ++ k)
		{
			fb_memcpy(fb_tmp, fb_buff_level[i], fb_rect_list[i][k]);
		}
	}

	// 更新到framebuffer
	unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
	memcpy(p, fb_tmp, fb_size);
}

#if _ENB_VIRTUAL_FB
void update_fb_ex(char rotate)
{
	if (rotate)
	{
		RECT rc = {0, 0, SCREEN_WIDTH - 1, SCREEN_HIGH - 1};
	#if PIXEL_BIT_8
		
	#endif
	#if PIXEL_BIT_16
		rotate_fb_rect(&rc);
	#endif
	#if PIXEL_BIT_24
		
	#endif
	}
	else
	{
		unsigned char *pReal = 
			(unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
	#if PIXEL_BIT_8
		
	#endif
	#if PIXEL_BIT_16
		memcpy(pReal, virtual_fb, sizeof(virtual_fb));
	#endif
	#if PIXEL_BIT_24
		
	#endif
	}
}
#endif

void myfb_updateRect(int fb_level, PRECT prc, PRECT pHiRc)
{
	RECT rc_tb, rc_lr, rc, rc_dlg;
	if(fb_level <= BASE_FB_LAYER)
	{
		fb_updateLayerRect(BASE_FB_LAYER, prc);
		fb_updateLayerRect(BASE_FB_LAYER, pHiRc);
		return;
	}
	fb_level--;
	rc		  = *prc;
	rc_dlg	  = *pHiRc;
	rc_tb.left  = rc.left;
	rc_tb.right = rc.right;
	rc_lr.top   = (rc.top > rc_dlg.top) ? rc.top : rc_dlg.top;
	rc_lr.bottom= (rc.bottom < rc_dlg.bottom) ? rc.bottom : rc_dlg.bottom;
	if (rc_dlg.top > rc.top)
	{
		rc_tb.top = rc.top;
		rc_tb.bottom = rc_dlg.top - 1;
		if (RECTH(rc_tb) > 0)
		{
			fb_updateLayerRect(fb_level, &rc_tb);
		}
	}
	if (rc_dlg.bottom < rc.bottom)
	{
		rc_tb.top = rc_dlg.bottom + 1;
		rc_tb.bottom = rc.bottom;
		if (RECTH(rc_tb) > 0)
		{
			fb_updateLayerRect(fb_level, &rc_tb);
		}
	}
	if (rc_dlg.left > rc.left)
	{
		rc_lr.left = rc.left;
		rc_lr.right = rc_dlg.left - 1;
		if (RECTW(rc_lr) > 0)
		{
			fb_updateLayerRect(fb_level, &rc_lr);
		}
	}
	if (rc_dlg.right < rc.right)
	{
		rc_lr.left = rc_dlg.right + 1;
		rc_lr.right = rc.right;
		if (RECTW(rc_lr) > 0)
		{
			fb_updateLayerRect(fb_level, &rc_lr);
		}
	}
}

void myfb_open_window(PMAINWIN pWin)
{
	RECT rc;
	int fb_level = pWin->fblayer;

	GetWindowRect((HWND)pWin, &rc);
	fb_open_window(fb_level, rc);
}


void myfb_close_window(PMAINWIN pWin)
{
	RECT rc;
	int fb_level = pWin->fblayer;	
	GetWindowRect((HWND)pWin, &rc);
	fb_close_window(fb_level, rc);
}

#if _ENB_MYFB_RECORD_DEBUG_FUNC
const UINT8 fb_mask[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

void myfb_debug_pixel (UINT8 *pbmp, INT32 index)
{
	INT32  i;
	INT32  j;
	UINT8  bmp;
	UINT16 offset_x;
	GAL_PIXEL color;
	RGB	   rgb;
	unsigned char * pp;
	
#if QVFB_DEBUG
	unsigned char *p = fb.data;
#else
	unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif  

	color  = PIXEL_white;
	rgb.r  = GetRValue(color);
	rgb.g  = GetGValue(color);
	rgb.b  = GetBValue(color);
	offset_x = 400; 
	for (i = 0; i < RECPAPERWIDTH; i++)
	{
		bmp = pbmp[i + index * RECPAPERWIDTH];
		for (j = 0; j < 8; j++)
		{
			if (bmp & fb_mask[j])
			{
				pp = p;
				pp += sfbypos[i * 8 + j] + sfbxpos[offset_x + index];
#if PIXEL_BIT_24				
				*pp ++ = rgb.r;
				*pp ++ = rgb.g;
				*pp ++ = rgb.b;
#endif
#if PIXEL_BIT_16
				UINT16 *p1 = (UINT16 *)pp;
				*p1 = fb_color(rgb.r, rgb.g, rgb.b);		
#endif
			}
		}
	}
}


void myfb_debug_line (UINT8 *pbmp, INT32 start_x, INT32 end_x)
{
	INT32  i;
	INT32  j;
	INT32  k;
	UINT8  bmp;
	UINT32 offset_x;
	GAL_PIXEL color;
	RGB	   rgb;	
	unsigned char *pp;
	unsigned char *buff;

#if QVFB_DEBUG
	unsigned char *p = fb.data;
#else
	unsigned char *p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);
#endif  
	color  = PIXEL_white;
	rgb.r  = GetRValue(color);
	rgb.g  = GetGValue(color);
	rgb.b  = GetBValue(color);
	offset_x = 0;

	for (i = start_x; i <= end_x; i++)
	{
		for (j = 0; j < RECPAPERWIDTH; j++)
		{
			bmp = pbmp[j + i * RECPAPERWIDTH];
			
			for (k = 0; k < 8; k++)
			{
				if (bmp & fb_mask[k])
				{
					pp = p;
					pp += sfbypos[j * 8 + k] + sfbxpos[offset_x + i];
#if PIXEL_BIT_24					
					*pp ++ = rgb.r;
					*pp ++ = rgb.g;
					*pp ++ = rgb.b;
#endif
#if PIXEL_BIT_16
					UINT16 *p1 = (UINT16 *)pp;
					*p1 = fb_color(rgb.r, rgb.g, rgb.b);
#endif
				}
			}
		}
	}
#if 0 //在整幅图一起显示的时候可以提高效率,目前这种显示方式效果不明显 -- empty 2011/11/10
	p = (unsigned char *)(sfbdev.fb_mem + sfbdev.fb_mem_offset);	
	for (i = 0; i < RECPAPERWIDTH_150 * 8; i++)
	{
		pp = p;
		pp += sfbypos[i] + sfbxpos[offset_x + start_x];
		memcpy (pp, (sMyFbDebugBuff + sfbypos[i] + sfbxpos[offset_x + start_x]), (end_x - start_x + 1) * 3);
	}
#endif	
}
#endif

