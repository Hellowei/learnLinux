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
#if !defined(_COLOR_H)
#define	  _COLOR_H

/* Truecolor color conversion and extraction macros*/
/*
 * Conversion from RGB to gal_pixel
 */
/* create 24 bit 8/8/8 format pixel (0x00RRGGBB) from RGB triplet*/
#define RGB2PIXEL888(r,g,b,reserved) \
	(((reserved) << 24) | ((r) << 16) | ((g) << 8) | (b))

/* create 16 bit 5/6/5 format pixel from RGB triplet */
#define RGB2PIXEL565(r,g,b,reserved) \
	(((reserved) << 24) | (((r) & 0xf8) << 8) | (((g) & 0xfc) << 3) | (((b) & 0xf8) >> 3))

/* create 15 bit 5/5/5 format pixel from RGB triplet */
#define RGB2PIXEL555(r,g,b) \
	((((r) & 0xf8) << 7) | (((g) & 0xf8) << 2) | (((b) & 0xf8) >> 3))

/* create 8 bit 3/3/2 format pixel from RGB triplet*/
#define RGB2PIXEL332(r,g,b) \
	(((r) & 0xe0) | (((g) & 0xe0) >> 3) | (((b) & 0xc0) >> 6))

/*
 * Conversion from COLORVAL to gal_pixel
 */
/* create 24 bit 8/8/8 format pixel from RGB colorval (0x00BBGGRR)*/
#define COLOR2PIXEL888(c)   \
	((((c) & 0xff) << 16) | ((c) & 0xff00) | (((c) & 0xff0000) >> 16))

/* create 16 bit 5/6/5 format pixel from RGB colorval (0x00BBGGRR)*/
#define COLOR2PIXEL565(c)   \
	((((c) & 0xf8) << 8) | (((c) & 0xfc00) >> 5) | (((c) & 0xf80000) >> 19))

/* create 15 bit 5/5/5 format pixel from RGB colorval (0x00BBGGRR)*/
#define COLOR2PIXEL555(c)   \
	((((c) & 0xf8) << 7) | (((c) & 0xf800) >> 6) | (((c) & 0xf80000) >> 19))

/* create 8 bit 3/3/2 format pixel from RGB colorval (0x00BBGGRR)*/
#define COLOR2PIXEL332(c)   \
	(((c) & 0xe0) | (((c) & 0xe000) >> 11) | (((c) & 0xc00000) >> 22))

/*
 * Conversion from gal_pixel to red, green or blue components
 */
/* return 8/8/8 bit r, g or b component of 24 bit gal_pixel*/
#define PIXEL888RED(gal_pixel)	  (((gal_pixel) >> 16) & 0xff)
#define PIXEL888GREEN(gal_pixel)	(((gal_pixel) >> 8) & 0xff)
#define PIXEL888BLUE(gal_pixel)	 ((gal_pixel) & 0xff)

/* return 5/6/5 bit r, g or b component of 16 bit gal_pixel*/
#define PIXEL565RED(gal_pixel)	  (((gal_pixel) >> 11) & 0x1f)
#define PIXEL565GREEN(gal_pixel)	(((gal_pixel) >> 5) & 0x3f)
#define PIXEL565BLUE(gal_pixel)	 ((gal_pixel) & 0x1f)

/* return 5/5/5 bit r, g or b component of 16 bit gal_pixel*/
#define PIXEL555RED(gal_pixel)	  (((gal_pixel) >> 10) & 0x1f)
#define PIXEL555GREEN(gal_pixel)	(((gal_pixel) >> 5) & 0x1f)
#define PIXEL555BLUE(gal_pixel)	 ((gal_pixel) & 0x1f)

/* return 3/3/2 bit r, g or b component of 8 bit gal_pixel*/
#define PIXEL332RED(gal_pixel)	  (((gal_pixel) >> 5) & 0x07)
#define PIXEL332GREEN(gal_pixel)	(((gal_pixel) >> 2) & 0x07)
#define PIXEL332BLUE(gal_pixel)	 ((gal_pixel) & 0x03)

/**
**
** static INT32 get_light (INT32 fg, INT32 bg)
** {
**	return ( bg + (fg - bg) / 4 );
** }
**/
#define  GET_LIGHT(fg, bg)	( bg + (fg - bg) / 4 )

/**
** 
** static INT32 get_medium (INT32 fg, INT32 bg)
** {
**	 return ( bg + (fg - bg) * 2 / 4 );
** }
**/
#define GET_MEDIUM(fg, bg)	( bg + (fg - bg) * 2 / 4 )

/**
**
** static INT32 get_dark (INT32 fg, INT32 bg)
** {
**	 return ( bg + (fg - bg) * 3 / 4 );
** }
**/
#define GET_DARK(fg, bg)	  ( bg + (fg - bg) * 3 / 4 )


enum COLORS {
	BLACK,				/* dark colors */
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,		   /* light colors */
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE
};


#endif
