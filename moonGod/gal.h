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

#ifndef  _GAL_H
#define  _GAL_H

typedef struct  _screendevice {
	INT32   xres;		/* X screen res (real) */
	INT32   yres;		/* Y screen res (real) */
	INT32   bpp;		/* # bits per pixel	*/
	INT32   linelen;	/* line length in bytes for bpp  1,2,4,8	*/
						/* line length in pixels for bpp 16, 24, 32 */
						
	INT32   size;		/* size of memory allocated */

	INT32   ncolors;	/* # screen colors*/
//	VOID  * addr;		/* address of video memory */
} SCREENDEVICE;

typedef struct _screendevice * PSD;


#define WIDTHOFPHYGC			(scrdev.xres)
#define HEIGHTOFPHYGC		   (scrdev.yres)

extern GAL_PIXEL SysPixelIndex [];
extern const RGB SysPixelColor [];
extern SCREENDEVICE  scrdev;

BOOL	  InitGraphDriver(VOID);
GAL_PIXEL GUIAPI MapColor (PSD psd, GAL_COLOR *color);
INT32	 GUIAPI UnmapPixel (PSD psd, GAL_PIXEL pixel, GAL_COLOR* color);
GAL_PIXEL GUIAPI MapColorEx (PSD psd, UINT8 bpp, GAL_PIXEL pixel);


#endif
