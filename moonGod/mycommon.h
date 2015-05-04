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
#ifndef  _MYCOMMON_H
#define  _MYCOMMON_H


#define GUIAPI

/* The two types of endianness */
/**
 * \def MGUI_LIL_ENDIAN
 * \brief Little endianness.
 */
#define MGUI_LIL_ENDIAN  1234

/**
 * \def MGUI_BIG_ENDIAN
 * \brief Big endianness.
 */
#define MGUI_BIG_ENDIAN  4321

/* 和目标平台有关 */
#define MGUI_BYTEORDER   MGUI_LIL_ENDIAN

	/**
	 * \defgroup handles MiniGUI handles
	 * @{
	 */

/**
 * \var typedef unsigned long GHANDLE
 * \brief General handle.
 */
typedef unsigned long GHANDLE;
/**
 * \var typedef unsigned long HWND
 * \brief Handle to main window or control.
 */
typedef unsigned long HWND;
/**
 * \var typedef unsigned long HDC
 * \brief Handle to device context.
 */
typedef unsigned long HDC;
/**
 * \var typedef unsigned INT32 HCURSOR
 * \brief Handle to cursor.
 */
typedef unsigned long HCURSOR;
/**
 * \var typedef unsigned INT32 HICON
 * \brief Handle to icon.
 */
typedef unsigned long HICON;
/**
 * \var typedef unsigned INT32 HMENU
 * \brief Handle to menu.
 */
typedef unsigned long HMENU;
/**
 * \var typedef unsigned INT32 HACCEL
 * \brief Handle to accelarator.
 */
typedef unsigned long HACCEL;
/**
 * \var typedef unsigned INT32 HDLG
 * \brief Handle to dialog box, same with HWND.
 */
typedef unsigned long HDLG;
/**
 * \var typedef unsigned INT32 HHOOK
 * \brief Handle to keyboard or mouse event hook.
 */
typedef unsigned long HHOOK;


typedef unsigned long HANDLE;
#define DECLARE_HANDLE(name) typedef HANDLE name

typedef   int		  STATUS;			/* 函数返回值的类型			 */
typedef   UINT32	   OPTION;			/* 选项字					   */

	/** @} end of handles */
/* Types use for passing & returning polymorphic values */

/**
 * \var typedef unsigned long WPARAM
 * \brief A type definition for the first message paramter.
 */
typedef unsigned long	   WPARAM;

/**
 * \var typedef DWORD WPARAM
 * \brief A type definition for the second message paramter.
 */
typedef unsigned long	   LPARAM;

typedef long				LRESULT;

typedef unsigned char	   BYTE;
typedef unsigned short	  WORD;
typedef unsigned long	   DWORD;
typedef char				SBYTE;
typedef short			   SWORD;
typedef long				SDWORD;

typedef int				 BOOL;				 /*  16 bit							   */
typedef int				 INT;				  /*  16 bit							   */
typedef unsigned int		UINT;				 /*  16 bit							   */
typedef unsigned int	  * PUINT;
typedef FLOAT			 * PFLOAT;
typedef BOOL			  * PBOOL;
typedef BOOL			  * LPBOOL;
typedef BYTE			  * PBYTE;
typedef BYTE			  * LPBYTE;
typedef int			   * PINT;
typedef int			   * LPINT;
typedef WORD			  * PWORD;
typedef WORD			  * LPWORD;
typedef long			  * LPLONG;
typedef DWORD			 * PDWORD;
typedef DWORD			 * LPDWORD;
typedef void			  * LPVOID;
typedef CONST void		* LPCVOID;
typedef char			  * PCHAR;
typedef unsigned char	 * PUCHAR;
typedef unsigned char	  bool;

/* Win32 macros */
/**
 * \def LOBYTE(w)
 * \brief Returns the low byte of the word \a w.
 *
 * \sa MAKEWORD
 */
#define LOBYTE(w)		   ((BYTE)(w))

/**
 * \def HIBYTE(w)
 * \brief Returns the high byte of the word \a w.
 *
 * \sa MAKEWORD
 */
#define HIBYTE(w)		   ((BYTE)(((WORD)(w) >> 8) & 0xFF))

/**
 * \def MAKEWORD(low, high)
 * \brief Makes a word from \a low byte and \a high byte.
 */
#define MAKEWORD(a, b)	  ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))

/**
 * \def LOWORD(l)
 * \brief Returns the low word of the double word \a l
 *
 * \sa MAKELONG
 */
#define LOWORD(l)		   ((WORD)(l))

/**
 * \def HIWORD(l)
 * \brief Returns the high word of the double word \a l
 *
 * \sa MAKELONG
 */
#define HIWORD(l)		   ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))

/**
 * \def MAKELONG(low, high)
 * \brief Makes a double word from \a low word and \a high word.
 */
#define MAKELONG(low, high) ((DWORD)(((WORD)(low)) | (((DWORD)((WORD)(high))) << 16)))

/**
 * \def LOSWORD(l)
 * \brief Returns the low signed word of the double word \a l
 *
 * \sa MAKELONG
 */
#define LOSWORD(l)		  ((SWORD)(DWORD)(l))

/**
 * \def HISWORD(l)
 * \brief Returns the high signed word of the double word \a l
 *
 * \sa MAKELONG
 */
#define HISWORD(l)		  ((SWORD)((((DWORD)(l)) >> 16) & 0xFFFF))

#define MAKESWORD(a, b)	  ((UWORD)(((UBYTE)(a)) | ((UWORD)((UBYTE)(b))) << 8))

#define MAKESLONG(a, b)	  ((ULONG)(((UWORD)(a)) | ((ULONG)((UWORD)(b))) << 16))
#define LOSBYTE(w)		   ((UBYTE)(w))
#define HISBYTE(w)		   ((UBYTE)(((UWORD)(w) >> 8) & 0xFF))

/**
 * \def GetRValue(rgb)
 * \brief Gets the red component from a RGB triple value \a rgb.
 *
 * You can make a RGB triple by using MakeRGB.
 *
 * \sa MakeRGB
 */
#define GetRValue(rgb)	  ((BYTE)(rgb))
/**
 * \def GetGValue(rgb)
 * \brief Gets the green component from a RGB triple value \a rgb.
 *
 * You can make a RGB triple by using MakeRGB.
 *
 * \sa MakeRGB
 */
#define GetGValue(rgb)	  ((BYTE)(((WORD)(rgb)) >> 8))
/**
 * \def GetBValue(rgb)
 * \brief Gets the blue component from a RGB triple value \a rgb.
 *
 * You can make a RGB triple by using MakeRGB.
 *
 * \sa MakeRGB
 */
#define GetBValue(rgb)	  ((BYTE)((rgb) >> 16))

/**
 * \def MakeRGB(r, g, b)
 * \brief Makes a RGB triple value from red \a r, green \a g, and blue \a b components.
 *
 * \note The red, green, and blue components are all ranged from 0 to 255,
 * and the returned value will be a double word.
 *
 * \sa GetRValue, GetGValue, GetBValue
 */
#define MakeRGB(r, g, b)	(((DWORD)((BYTE)(r))) | ((DWORD)((BYTE)(g)) << 8) \
				| ((DWORD)((BYTE)(b)) << 16))

/**
 * A rectangle defined by coordinates of corners.
 *
 * \note The lower-right corner does not belong to the rectangle,
 * i.e. the bottom horizontal line and the right vertical line are excluded
 * from the retangle.
 *
 * \sa PRECT, GAL_Rect
 */
typedef struct _RECT
{
	/**
	 * the x coordinate of the upper-left corner of the rectangle.
	 */
	INT32 left;
	/**
	 * the y coordinate of the upper-left corner of the rectangle.
	 */
	INT32 top;
	/**
	 * the x coordinate of the lower-right corner of the rectangle.
	 */
	INT32 right;
	/**
	 * the y coordinate of the lower-right corner of the rectangle.
	 */
	INT32 bottom;
} RECT;
/**
 * \var typedef RECT* PRECT
 * \brief Data type of the pointer to a RECT.
 *
 * \sa RECT
 */
typedef RECT* PRECT;

/**
 * Point structure.
 * \sa PPOINT
 */
typedef struct _POINT
{
	/**
	 * the x coordinate of the point.
	 */
	INT32 x;
	/**
	 * the y coordinate of the point.
	 */
	INT32 y;
} POINT;
/**
 * \var typedef POINT* PPOINT
 * \brief Data type of the pointer to a POINT.
 *
 * \sa POINT
 */
typedef POINT* PPOINT;

/**
 * Size structure of a 2-dimension object.
 * \sa PSIZE
 */
typedef struct _SIZE
{
	/**
	 * the extent in x coordinate of a 2D object.
	 */
	INT32 cx;
	/**
	 * the extent in y coordinate of a 2D object.
	 */
	INT32 cy;
} SIZE;
/**
 * \var typedef SIZE* PSIZE
 * \brief Data type of the pointer to a SIZE.
 *
 * \sa SIZE
 */
typedef SIZE* PSIZE;

/**
 * RGB triple structure.
 * \sa PRGB, GAL_Color
 */
typedef struct _RGB
{
	/**
	 * the red component of a RGB triple.
	 */
	BYTE r;
	/**
	 * the green component of a RGB triple.
	 */
	BYTE g;
	/**
	 * the blue component of a RGB triple.
	 */
	BYTE b;
	/**
	 * Reserved for alignment, maybe used for the alpha component of a RGB triple. 
	 */
	BYTE Reserved;
} RGB;
typedef RGB* PRGB;
	/** @} end of win32_types */
	
	/**
	 * \defgroup gdi_types Data types for GDI
	 * @{
	 */
/**
 * \var typedef INT8 GAL_SINT8
 * \brief Data type of 8-bit signed integer.
 *
 * \sa INT8
 */
typedef INT8	   GAL_SINT8;
/**
 * \var typedef UINT8 GAL_UINT8
 * \brief Data type of 8-bit unsigned integer.
 *
 * \sa UINT8
 */
typedef UINT8	   GAL_UINT8;

/**
 * \var typedef INT16 GAL_INT16
 * \brief Data type of 16-bit signed integer.
 *
 * \sa INT16
 */
typedef INT16	  GAL_INT16;
/**
 * \var typedef UINT16 GAL_UINT16
 * \brief Data type of 16-bit unsigned integer.
 *
 * \sa UINT16
 */
typedef UINT16	  GAL_UINT16;

/**
 * \var typedef INT32 GAL_INT32
 * \brief Data type of 32-bit signed integer.
 *
 * \sa INT32
 */
typedef INT32	  GAL_INT32;
/**
 * \var typedef UINT32 GAL_UINT32
 * \brief Data type of 32-bit unsigned integer.
 *
 * \sa UINT32
 */
typedef UINT32	  GAL_UINT32;
/**
 * \var typedef Uint32 gal_pixel 
 * \brief Data type of pixel value
 */
typedef UINT32		  GAL_PIXEL;
/**
 * \var typedef Uint32 gal_attr
 * \brief Data type of attribute value
 */
typedef UINT32		  GAL_ATTR;
/**
 * \var typedef long fixed.
 * \brief Data type of fixed point.
 */
typedef long FIXED;

/**
 * RGBA quarter structure.
 * \sa RGB
 */
typedef struct GAL_Color
{
	/**
	 * the red component of a RGBA quarter.
	 */
	UINT8 r;
	/**
	 * the green component of a RGBA quarter.
	 */
	UINT8 g;
	/**
	 * the blue component of a RGBA quarter.
	 */
	UINT8 b;
	/**
	 * the alpha component of a RGBA quarter.
	 */
	UINT8 reserved;
} GAL_COLOR;

	/** @} end of gdi_types */

	/**
	 * \defgroup err_codes Error codes
	 * @{
	 */
#define ERR_OK				   0
#define ERR_INV_HWND			-1
#define ERR_QUEUE_FULL		  -2

#define ERR_INVALID_HANDLE	  -3
#define ERR_INVALID_HMENU	   -4
#define ERR_INVALID_POS		 -5
#define ERR_INVALID_ID		  -6
#define ERR_RES_ALLOCATION	  -7

#define ERR_CTRLCLASS_INVNAME   -8
#define ERR_CTRLCLASS_INVLEN	-9
#define ERR_CTRLCLASS_MEM	   -10
#define ERR_CTRLCLASS_INUSE	 -11

#define ERR_ALREADY_EXIST	   -12
#define ERR_NO_MATCH			-13
#define ERR_BAD_OWNER		   -14

#define ERR_IME_TOOMUCHIMEWND   -15
#define ERR_IME_NOSUCHIMEWND	-16
#define ERR_IME_NOIMEWND		-17

#define ERR_CONFIG_FILE		 -18
#define ERR_FILE_IO			 -19
#define ERR_GFX_ENGINE		  -20
#define ERR_INPUT_ENGINE		-21
#define ERR_NO_ENGINE		   -22

#define ERR_CTRLID_MISMATCH_CTRLCLASS  -30	/* 控件id和控件类型不符.  */
#define ERR_CTRLID_NOT_EXIST	-31

#define ERR_TIMER_SAME		  -50	/* 增加timer已经存在			 */
#define ERR_TIMER_NOSPACE	   -51	/* 增加timer, 没有空间		   */
#define ERR_TIMER_INVALIDITEM   -52	/* 删除timer, 没有找到相应item   */

#define ERR_IO_NOENOUGH_BUFF	-60	/* IO请求队列没有空闲单元		*/

#define ERR_E2P_ADDR_INVALID	-70	/* e2prom 读写地址非法.超过范围. */

#define ERR_Q_POSTFAIL		  -80	/* call OSQPend failure */
#define ERR_IO_NOACK			-90	/* no ack */
#define ERR_IO_NOCMD			-91	/* no command */


/*
***************************************************************************
*				   错误代码
*				  返回值；一般用STATUS类型值；
***************************************************************************
*/
#define   TM_SUCCESS	0
#define   TM_FAIL	   10


	/** @} end of err_codes */

	/**
	 * \defgroup misc_macros Miscellaneous macros
	 * @{
	 */
/**
 * \def TABLESIZE(table)
 * \brief A macro returns the number of elements in a \a table.
 */
#define TABLESIZE(table)	(sizeof(table)/sizeof(table[0]))

/* MAX/MIN/ABS macors */
/**
 * \def MAX(x, y)
 * \brief A macro returns the maximum of \a x and \a y.
 */
#ifndef MAX
#define MAX(x, y)		   ((x > y)?x:y)
#endif
/**
 * \def MIN(x, y)
 * \brief A macro returns the minimum of \a x and \a y.
 */
#ifndef MIN
#define MIN(x, y)		   ((x < y)?x:y)
#endif
/**
 * \def ABS(x)
 * \brief A macro returns the absolute value of \a x.
 */
#ifndef ABS
#define ABS(x)			  (((x)<0) ? -(x) : (x))
#endif

/**
 * \def MAX_PATH
 * \brief The possible maximal length of a path name.
 * \note This definition is an alias of PATH_MAX
 */
#define MAX_PATH		32// PATH_MAX
/**
 * \def MAX_NAME
 * \brief The possible maximal length of a file name.
 * \note This definition is an alias of NAME_MAX
 */
#define MAX_NAME		16//NAME_MAX

#define   UNREFRENCED_PARAMETERS(p)		   (p)=(p)	 /* 消除编译警告 */
#define   UNREFERENCED_PARAMETER(p)		   (p)=(p)

#define HandleToUlong(h)  ((UINT32) (h) )
#define PtrToUlong(p)	 ((UINT32) (p) )
#define PtrToLong(p)	  ((LONG) (p) )
#define PtrToUshort(p)	((unsigned short) (p) )
#define PtrToShort(p)	 ((short) (p) )

#define PTR2FLAT(c) ((unsigned char *)(c))
#define FLAT2PTR(c) ((unsigned char *)(c))

#define PTR_ADD(p, off)	 FLAT2PTR(PTR2FLAT(p) + off)			/* 指针加一个偏移量 */
#define PTR_SUB(p, off)	 FLAT2PTR(PTR2FLAT(p) - off)			/* 指针减一个偏移量 */
#define PTR_EQUAL(p1, p2)   (PTR2FLAT(p1) == PTR2FLAT(p2))		 /* 指针相等		 */
#define PTR_CPR(p1, p2)	 (PTR2FLAT(p1) < PTR2FLAT(p2))		  /* 指针比较		 */

#define FIELD_OFFSET(type, field)	((UINT32)&(((type *)0)->field))

/**
* TYPE_ALIGNMENT will return the alignment requirements of a given type for
* the current platform.
*
* #pragma warning(disable:4116)
**/
#define TYPE_ALIGNMENT( t ) \
	FIELD_OFFSET( struct { char x; t test; }, test )

/**
* Calculate the address of the base of the structure given its type, and an
* address of a field within the structure.
**/
#define CONTAINING_RECORD(address, type, field) ((type *)( \
												  (PCHAR)(address) - \
												  (UINT32)(&((type *)0)->field)))
/* l,  low word(16bit);  h, high word(16bit) */
#define MAKEWPARAM(l, h)	  (WPARAM)MAKELONG(l, h)
#define MAKELPARAM(l, h)	  (LPARAM)MAKELONG(l, h)
#define MAKELRESULT(l, h)	 (LRESULT)MAKELONG(l, h)

/* b0, byte 0 (lower byte). b1, ..., ect */
#define MAKEWPARAM2(b0,b1,b2,b3)	  (WPARAM)MAKELONG(MAKEWORD(b0,b1), MAKEWORD(b2,b3))
#define MAKELPARAM2(b0,b1,b2,b3)	  (LPARAM)MAKELONG(MAKEWORD(b0,b1), MAKEWORD(b2,b3))

/* 把w(word)高低字节交换 */
#define SWAP16(w) ((w<<8)|(w>>8))

/* 把dw(DWORD)高低字节交换, 原来次序4,3,2,1, 4最高; 交换后,变成1,2,3,4 */
#define SWAP32(dw) ((dw<<24)|((dw<<8)&0x00FF0000)|((dw>>8)&0x0000FF00)|(dw>>24))

#define  MAKEWINP(h)   ((WINDOW *)h)

/* p, address;			  l, length */
#define  ZeroMemory(p,l)   memset((p), 0, (l))

	/** @} end of misc_macros */

	/** @} end of macros_types */
	
typedef  INT32  (*WNDPROC)(HWND, INT32, WPARAM, LPARAM);


#define OS_TICK_TIME	  ((UINT16)( 1000L/(UINT32)OS_TICKS_PER_SEC))	/* OS一个tick延时多少ms */ 
#define OS_TIME_1ms	   ((UINT16)((UINT32)OS_TICKS_PER_SEC * 1L / 1000L))
#define OS_TIME_10ms	  ((UINT16)((UINT32)OS_TICKS_PER_SEC * 10L / 1000L))
#define OS_TIME_100ms	 ((UINT16)((UINT32)OS_TICKS_PER_SEC * 100L / 1000L))

#define OS_NO_ERR 0
#define OS_TASK_OPT_STK_CHK  0x0001		/* Enable stack checking for the task					  */
#define OS_TASK_OPT_STK_CLR  0x0002		/* Clear the stack when the task is create				 */
#define OS_TASK_OPT_SAVE_FP  0x0004		/* Save the contents of any floating-point registers	   */

#define errprintf(c) printf(c)

#ifndef EXIT_PROC
#define EXIT_PROC(c)
#endif

#define ASSERT_REPORT(c) //(printf("assert...%s:%d:%p", __FUNCTION__,__LINE__, c))

#define mem_copy(a, b, c) memcpy(a, b, (c) * 2)
#define mem_set(a, b, c)  memset(a, b, (c) * 2)

#define EXAM_ASSERT(c)

#define COLOR_BYTES		2
#define IMAGE_SIZE(w,h)	(ulong)(w)*(ulong)(h)*(ulong)(COLOR_BYTES)
#define imagesize(x1,y1, x2, y2)	(IMAGE_SIZE(x2-x1, y2-y1) + 4)
void getimage(int left, int top, int right, int bottom, void *bitmap);
void putimage(int x, int y, const void *fpbitmap, int op);

#define traceout printf
#define _ENDL "\n"
#define prinfo (printf("%s:%d\t", __FUNCTION__,__LINE__),printf)
#endif

