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

#define   GAL_GLOBALS 
#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "color.h"
#include "myfb.h"
#include "gal.h"

SCREENDEVICE  scrdev;

#if defined(X86) || defined(LANNRY)

int	GraphDriver;			 /* The Graphics device driver		   */
int	GraphMode;			   /* The Graphics mode value			  */
int	ErrorCode;			   /* Reports any graphics errors		  */

#define DetectVGA()	  (GraphMode = VGAHI)

int huge DetectVGA16(void)
{
  int   Vid;

  printf("Which video mode would you like to use? \n");
  printf("  0) 320x200x16\n");
  printf("  1) 640x200x16\n");
  printf("  2) 640x350x16\n");
  printf("  3) 640x480x256\n");
  printf("  4) 800x600x16\n");
  printf("  5) 1024x768x16\n");
  printf("  6) 1280x1024x16\n");
  printf("\n> ");
  scanf("%d",&Vid);
  return Vid;
}

int huge DetectVGA256(void)
{
  int Vid;

  printf("Which video mode would you like to use? \n");
  printf("  0) 320x200x256\n");
  printf("  1) 640x400x256\n");
  printf("  2) 640x480x256\n");
  printf("  3) 800x600x256\n");
  printf("  4) 1024x768x256\n");
  printf("  5) 640x480x256\n");
  printf("  6) 1280x1024x256\n");
  printf("\n> ");
  scanf("%d",&Vid);
  return Vid;
  //return  3;
}

int huge DetectVGA64k(void)
{
  int Vid;

  printf("Which video mode would you like to use? \n");
  printf("  0) 320x200x65536\n");
  printf("  1) 640x350x65536\n");
  printf("  2) 640x400x65536\n");
  printf("  3) 640x480x65536\n");
  printf("  4) 800x600x65536\n");
  printf("  5) 1024x768x65536\n");
  printf("  6) 1280x1024x65536\n");
  printf("\n> ");
  scanf("%d",&Vid);
  return Vid;
 }

int  CheckBgiDriver(void)
{
	int  driver;
	int  option;
	
	/* Find out which driver the user wants */
	printf("Which driver would you like to use?\n");
	printf("  0) Svga16\n");
	printf("  1) Svga256\n");
	printf("  2) Svga64k\n");
	printf("\n> ");
	scanf("%d",&option);

	driver = DETECT;
	
	switch(option)
	{
	case 0: installuserdriver("Svga16",DetectVGA16);
	// case 0: driver = VGA;
	//		DetectVGA();
	/*  If driver is linked with file, remove comments */
	/*		  registerfarbgidriver(Svga16_fdriver);  */
		break;

	case 1: installuserdriver("Svga256",DetectVGA256);
		   // driver = DETECT;
	/*  If driver is linked with file, remove comments */
	/*		  registerfarbgidriver(Svga256_fdriver); */
	/*   driver = installuserdriver("Svga16",DetectVGA16)*/
		break;
		   
	case 2: installuserdriver("Svga64k",DetectVGA64k);
		break;
		
	default:
		driver = DETECT;
		break;
	}

	return driver;
}

#endif


/**
*  \note 根据系统支持的color数量,计算 bits per pixel; color_num一般都是2的整数倍;
*  \return  bpp值;
**/
int  Calc_Bpp(long color_num)
{
	int bpp;

	bpp = 0;

	color_num >>= 1;
	while ( color_num ) {
		color_num >>= 1;
		bpp ++;
	}
	return bpp;
}


#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
 
VOID unblank(VOID)
{
 int f;
 f = open("/dev/tty0", O_RDWR);
 write(f, "\033[9;0]", 8);
 close(f);
}


BOOL  InitGraphDriver(VOID)
{
	int  i;
	char ch[100];
	
	fb_clear();

	unblank();

	//printf("\033[9;0]");

	scrdev.ncolors = 16777216;  /* Read maximum number of colors*/
	scrdev.xres	= 800;
	scrdev.yres	= 480;	  /* Read size of screen */
	scrdev.bpp	 = Calc_Bpp(scrdev.ncolors);
	scrdev.linelen = (scrdev.xres * scrdev.bpp) >> 3;
	scrdev.size	= scrdev.linelen * scrdev.yres;
/** /
	for (i = 0; i < 17; i++)
		SysPixelIndex [i] = MapColor (&scrdev, (GAL_COLOR*)(SysPixelColor + i));
/**/
	 return TRUE;

error_init:
	return FALSE;
}


UINT32  GUI_Color2Index_332(UINT8 r, UINT8 g, UINT8 b) 
{ 
	r = (r * 7 + 127) / 255;
	g = (g * 7 + 127) / 255;
	b = (b + 42) / 85;
	
	return ((r<<5) + (g << 2) + (b<<0));
}


/*
 * Convertion between GAL_COLOR and gal_pixel
 * borrowed  from gl lib.
 */
GAL_PIXEL GUIAPI MapColor (PSD psd, GAL_COLOR *color)
{
	UINT32 v;
	switch (psd->bpp) {
	case 1:
		if ((color->b + color->g + color->r) > 128*3)
			v = 1;
		else
			v = 0;
		return v;

	case 2:
		v = 0;
		if (color->b >= 64)
			v += 1;
		if (color->g >= 64)
			v += 2;
		if (color->r >= 64)
			v += 4;
		if (color->b >= 192 || color->g >= 192 || color->r >= 192)
			v += 8;
		v>>=2;
		return v;
	case 4:
		/* Now this is real fun. Map to standard EGA palette. */
		v = 0;
		if (color->b >= 64)
			v += 1;
		if (color->g >= 64)
			v += 2;
		if (color->r >= 64)
			v += 4;
		if (color->b >= 192 || color->g >= 192 || color->r >= 192)
			v += 8;
		return v;

	case 8:
		return RGB2PIXEL332 (color->r, color->g, color->b);
	case 15:
		return RGB2PIXEL555 (color->r, color->g, color->b);
	case 16:
		return RGB2PIXEL565 (color->r, color->g, color->b, color->reserved);
	case 24:
	case 32:
		return RGB2PIXEL888 (color->r, color->g, color->b, color->reserved);

	}
	return -1;
}

INT32 GUIAPI  UnmapPixel (PSD psd, GAL_PIXEL pixel, GAL_COLOR* color)
{
	switch (psd->bpp) {
	case 1:
		if (pixel) {
			color->r = 255;
			color->g = 255;
			color->b = 255;
		}
		else {
			color->r = 0;
			color->g = 0;
			color->b = 0;
		}
		break;

	case 2:
	case 4:
		color->r = SysPixelColor [pixel].r;
		color->g = SysPixelColor [pixel].g;
		color->b = SysPixelColor [pixel].b;
		break;

	case 8:
		color->r = PIXEL332RED (pixel) << 5;
		color->g = PIXEL332GREEN (pixel) << 5;
		color->b = PIXEL332BLUE (pixel) << 6;
		break;

	case 15:
		color->r = PIXEL555RED (pixel) << 3;
		color->g = PIXEL555GREEN (pixel) << 3;
		color->b = PIXEL555BLUE (pixel) << 3;
		break;

	case 16:
		color->r = PIXEL565RED (pixel) << 3;
		color->g = PIXEL565GREEN (pixel) << 2;
		color->b = PIXEL565BLUE (pixel) << 3;
		color->reserved = (pixel >> 24) & 0xff; //透明色支持
		break;

	case 24:
	case 32:
		color->r = PIXEL888RED (pixel);
		color->g = PIXEL888GREEN (pixel);
		color->b = PIXEL888BLUE (pixel);
		color->reserved = (pixel >> 24) & 0xff; //透明色支持
		break;
	}

	return 0;
}

/**
** \brief   根据输入的源象素值,和bits per pixel, 把它转换成当前系统识别的象素值;
**		  
** \param   psd,  当前屏幕驱动信息结构
** \param   bpp,  bits per pixel
** \param   pix,  输入的象素值
** \return  转换以后的当前格式的象素值
**
** \note  主要是因为一些bitmap文件具有不同于系统的数据格式;所以需要转换;
**/
GAL_PIXEL GUIAPI MapColorEx (PSD psd, UINT8 bpp, GAL_PIXEL pixel)
{
	GAL_COLOR color;

	switch ( bpp ) {
	case 4:
		color.r = SysPixelColor [pixel].r;
		color.g = SysPixelColor [pixel].g;
		color.b = SysPixelColor [pixel].b;
		break;

	case 8:
		color.r = PIXEL332RED (pixel) << 5;
		color.g = PIXEL332GREEN (pixel) << 5;
		color.b = PIXEL332BLUE (pixel) << 6;
		break;

	case 16:
		color.r = PIXEL565RED (pixel) << 3;
		color.g = PIXEL565GREEN (pixel) << 2;
		color.b = PIXEL565BLUE (pixel) << 3;
		break;
		
	default:
		color.r = 0xff;
		color.g = 0xff;
		color.b = 0xff;
	}

	return MapColor(psd, &color);
}


