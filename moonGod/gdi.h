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
#if !defined(_GDI_H)
#define	  _GDI_H

	/**
	 * \addtogroup global_vars Global variables
	 * @{
	 */

	/**
	 * \defgroup color_vars System colors and pixel values.
	 * @{
	 */

/**
 * \var GAL_PIXEL SysPixelIndex []
 * \brief The pre-defined system pixel values.
 *
 * MiniGUI defines some system pixel values when initializing 
 * graphics sub-system. You can access the arrary to get the
 * system pixel values, or just use the following macros:
 *
 *  - PIXEL_black\n
 *	black
 *  - PIXEL_darkred\n
 *	dark red
 *  - PIXEL_darkgreen\n
 *	dark green
 *  - PIXEL_darkyellow\n
 *	dark yellow
 *  - PIXEL_darkblue\n
 *	dark blue
 *  - PIXEL_darkmagenta\n
 *	dark magenta
 *  - PIXEL_darkcyan\n
 *	dark cyan
 *  - PIXEL_lightgray\n
 *	light gray
 *  - PIXEL_darkgray\n
 *	dark gray
 *  - PIXEL_red\n
 *	red
 *  - PIXEL_green\n
 *	green
 *  - PIXEL_yellow\n
 *	yellow
 *  - PIXEL_blue\n
 *	blue
 *  - PIXEL_magenta\n
 *	magenta
 *  - PIXEL_cyan\n
 *	cyan
 *  - PIXEL_lightwhite\n
 *	light white
 */
extern GAL_PIXEL SysPixelIndex [];

/**
 * \var RGB SysPixelColor []
 * \brief The pre-defined system RGB colors.
 *
 * The elements in this array are system colors in RGB triples.
 */
extern const RGB SysPixelColor [];
#define USE_ELEMENTCOLOR_EXTERN 1
#define PIXEL_invalid		   0

#if USE_ELEMENTCOLOR_EXTERN
#define PIXEL_transparent   GetWindowElementColor(WEC_EXCOLOR_TRANSPARENT)
#define PIXEL_darkblue	  GetWindowElementColor(WEC_EXCOLOR_NAVY)
#define PIXEL_darkgreen	 GetWindowElementColor(WEC_EXCOLOR_GREEN)
#define PIXEL_darkcyan	  GetWindowElementColor(WEC_EXCOLOR_TEAL)
#define PIXEL_darkred	   GetWindowElementColor(WEC_EXCOLOR_MAROON) 
#define PIXEL_darkmagenta   GetWindowElementColor(WEC_EXCOLOR_PURPLE)
#define PIXEL_darkyellow	GetWindowElementColor(WEC_EXCOLOR_OLIVE) 
#define PIXEL_darkgray	  GetWindowElementColor(WEC_EXCOLOR_GRAY) 
#define PIXEL_lightgray	 GetWindowElementColor(WEC_EXCOLOR_SILVER)
#define PIXEL_blue		  GetWindowElementColor(WEC_EXCOLOR_BLUE)
#define PIXEL_green		 GetWindowElementColor(WEC_EXCOLOR_LIME)
#define PIXEL_cyan		  GetWindowElementColor(WEC_EXCOLOR_CYAN)
#define PIXEL_red		   GetWindowElementColor(WEC_EXCOLOR_RED)
#define PIXEL_magenta	   GetWindowElementColor(WEC_EXCOLOR_MAGENTA)
#define PIXEL_yellow		GetWindowElementColor(WEC_EXCOLOR_YELLOW)
#define PIXEL_lightwhite	GetWindowElementColor(WEC_EXCOLOR_WHITE)
#define PIXEL_black		 GetWindowElementColor(WEC_EXCOLOR_BLACK)
#define PIXEL_white		 GetWindowElementColor(WEC_EXCOLOR_WHITE)
#else
#define PIXEL_transparent   SysPixelIndex[0]
#define PIXEL_darkblue	  SysPixelIndex[1]  //GetWindowElementColor(WEC_EXCOLOR_NAVY)
#define PIXEL_darkgreen	 SysPixelIndex[2]  //GetWindowElementColor(WEC_EXCOLOR_GREEN)
#define PIXEL_darkcyan	  SysPixelIndex[3]  //GetWindowElementColor(WEC_EXCOLOR_TEAL)
#define PIXEL_darkred	   SysPixelIndex[4]  //GetWindowElementColor(WEC_EXCOLOR_MAROON) 
#define PIXEL_darkmagenta   SysPixelIndex[5]  //GetWindowElementColor(WEC_EXCOLOR_PURPLE)
#define PIXEL_darkyellow	SysPixelIndex[6]  //GetWindowElementColor(WEC_EXCOLOR_OLIVE) 
#define PIXEL_darkgray	  SysPixelIndex[7]  //GetWindowElementColor(WEC_EXCOLOR_GRAY) 
#define PIXEL_lightgray	 SysPixelIndex[8]  //GetWindowElementColor(WEC_EXCOLOR_SILVER)
#define PIXEL_blue		  SysPixelIndex[9]  //GetWindowElementColor(WEC_EXCOLOR_BLUE)
#define PIXEL_green		 SysPixelIndex[10] //GetWindowElementColor(WEC_EXCOLOR_LIME)
#define PIXEL_cyan		  SysPixelIndex[11] //GetWindowElementColor(WEC_EXCOLOR_CYAN)
#define PIXEL_red		   SysPixelIndex[12] //GetWindowElementColor(WEC_EXCOLOR_RED)
#define PIXEL_magenta	   SysPixelIndex[13] //GetWindowElementColor(WEC_EXCOLOR_MAGENTA)
#define PIXEL_yellow		SysPixelIndex[14] //GetWindowElementColor(WEC_EXCOLOR_YELLOW)
#define PIXEL_lightwhite	SysPixelIndex[15] //GetWindowElementColor(WEC_EXCOLOR_WHITE)
#define PIXEL_black		 SysPixelIndex[16] //GetWindowElementColor(WEC_EXCOLOR_BLACK)
#define PIXEL_white		 SysPixelIndex[15] //GetWindowElementColor(WEC_EXCOLOR_WHITE)
#endif

/* Compatiblity definitions */
#define COLOR_invalid	   PIXEL_invalid
#define COLOR_transparent   PIXEL_transparent
#define COLOR_darkred	   PIXEL_darkred
#define COLOR_darkgreen	 PIXEL_darkgreen
#define COLOR_darkyellow	PIXEL_darkyellow
#define COLOR_darkblue	  PIXEL_darkblue
#define COLOR_darkmagenta   PIXEL_darkmagenta
#define COLOR_darkcyan	  PIXEL_darkcyan
#define COLOR_lightgray	 PIXEL_lightgray
#define COLOR_darkgray	  PIXEL_darkgray
#define COLOR_red		   PIXEL_red
#define COLOR_green		 PIXEL_green
#define COLOR_yellow		PIXEL_yellow
#define COLOR_blue		  PIXEL_blue
#define COLOR_magenta	   PIXEL_magenta
#define COLOR_cyan		  PIXEL_cyan
#define COLOR_lightwhite	PIXEL_lightwhite
#define COLOR_black		 PIXEL_black
#define COLOR_white		 PIXEL_lightwhite

#define SysColorIndex	   SysPixelIndex

	/** @} end of color_vars */

	/** @} end of global_vars */
	
	/**
	 * \defgroup dc_fns General DC operations
	 *
	 * DC means Device Context, just like Graphics Context (GC) of X Lib.
	 * DC represents a rectangle area on the actual screen or a virtual screen
	 * created in memory. We call the rectangle area as "surface" of the DC.
	 *
	 * You can call a GDI function and pass a DC to the function to 
	 * draw lines, circles, or text. Commonly, you should call a function
	 * like \a GetClientDC or \a CreateCompatibleDC to get or create a
	 * DC, then call GDI functions to draw objects, e.g. \a MoveTo and \a LineTo.
	 * After finishing drawing, you should call \a ReleaseDC or \a DestroyMemDC function
	 * to release or destroy the DC.
	 *
	 * MiniGUI reserved an global DC called \a HDC_SCREEN. You can
	 * use this DC directly without getting/creating or releasing/destroying.
	 *
	 * For main windows or controls, MiniGUI will send a MSG_PAINT message to
	 * the window when the whole or part of window area have been invalidated. 
	 * You should call \a BegainPaint function to get the DC, then repaint the window, 
	 * and call \a EndPaint function to release the DC at the last.
	 *
	 * Example:
	 *
	 * \include msg_paint.c
	 *
	 * @{
	 */

/**
 * \def HDC_SCREEN
 * \brief Handle to the device context of the whole screen.
 *
 * This DC is a special one. MiniGUI uses it to draw popup menus and other global
 * objects. You can also use this DC to draw lines or text on the screen 
 * directly, and there is no need to get or release it.
 *
 * If you do not want to create any main window, but you want to draw on
 * the screen, you can use this DC.
 *
 * \note MiniGUI does not do any clipping operation for this DC, so use this DC 
 * may make a mess of other windows. 
 */
#define HDC_SCREEN		  0

/**
 * \def HDC_INVALID
 * \brief Indicates an invalid handle to device context.
 */
#define HDC_INVALID		 0

#define GDCAP_COLORNUM	  0
#define GDCAP_HPIXEL		1
#define GDCAP_VPIXEL		2
#define GDCAP_MAXX		  3
#define GDCAP_MAXY		  4
#define GDCAP_DEPTH		 5
#define GDCAP_BPP		   6

/**
 * \fn unsigned INT32 GUIAPI GetGDCapability (HDC hdc, INT32 iItem)
 * \brief Returns a capability of a DC.
 *
 * This function returns the capability of the specified item \a iItem of the DC \a hdc.
 *
 * \param hdc The handle to the DC.
 * \param iItem An integer presents the capablity, can be one of the following values:
 *
 *  - GDCAP_COLORNUM\n
 *	Tell \a GetGDCapability to return the colors number of the DC. Note the for a DC
 *	with 32-bit depth, the function will return 0xFFFFFFFF, not 0x100000000.
 *  - GDCAP_HPIXEL\n
 *	Tell \a GetGCapability to return the horizontal resolution of the DC.
 *  - GDCAP_VPIXEL\n
 *	Tell \a GetGDCapability to return the vertical resolution of the DC.
 *  - GDCAP_MAXX\n
 *	Tell \a GetGDCapability to return the maximal visible x value of the DC.
 *  - GDCAP_MAXY\n
 *	Tell \a GetGDCapability to return the maximal visible y value of the DC.
 *  - GDCAP_DEPTH\n
 *	Tell \a GetGDCapability to return the color depth of the DC. The returned value can be 
 *	1, 4, 8, 15, 16, 24, or 32.
 *  - GDCAP_BPP\n
 *	Tell \a GetGDCapability to return the bytes number for storing a pixle in the DC.
 *
 * \return The capbility.
 */
UINT32 GUIAPI GetGDCapability (HDC hdc, INT32 iItem);

/**
 * \fn HDC GUIAPI GetDC (HWND hwnd)
 * \brief Gets a window DC of a window.
 *
 * This function gets a window DC of the specified \a hwnd, and returns the handle to the DC.
 * MiniGUI will try to return an unused DC from the internal DC pool, rather than
 * allocate a new one from the system heap. Thus, you should release the DC when
 * you finish drawing as soon as possible.
 *
 * \param hwnd The handle to the window.
 * \return The handle to the DC, HDC_INVALID indicates an error.
 *
 * \note You should call \a ReleaseDC to release the DC when you are done.
 *
 * \sa GetClientDC, ReleaseDC
 */
HDC GUIAPI GetDC (HWND hwnd);

/**
 * \fn HDC GUIAPI GetClientDC (HWND hwnd)
 * \brief Gets a client DC of a window.
 *
 * This function gets a client DC of the specified \a hwnd, and returns the handle to the DC.
 * MiniGUI will try to return an unused DC from the internal DC pool, rather than
 * allocate a new one from the system heap. Thus, you should release the DC when
 * you finish drawing as soon as possible.
 *
 * \param hwnd The handle to the window.
 * \return The handle to the DC, HDC_INVALID indicates an error.
 *
 * \note You should call \a ReleaseDC to release the DC when you are done.
 *
 * \sa GetDC, ReleaseDC
 */
HDC GUIAPI GetClientDC (HWND hwnd);

/**
 * \fn VOID GUIAPI ReleaseDC (HDC hdc)
 * \brief Releases a DC from DC pool.
 *
 * This function releases the DC returned by \a GetDC or \a GetClientDC.
 *
 * \param hdc The handle to the DC.
 *
 * \sa GetDC, GetClientDC 
 */
VOID GUIAPI ReleaseDC (HDC hdc);

	/** @} end of dc_fns */

	/**
	 * \defgroup dc_attrs DC attribute operations
	 * @{
	 */

#define BM_TRANSPARENT		  1
#define BM_OPAQUE			   0

#define PT_SOLID				0
#define BT_SOLID				0

/**
 * \fn GetBkColor(hdc)
 * \brief Gets the background color of a DC.
 *
 * \param hdc The device context.
 * \return The background pixel value of the DC \a hdc.
 *
 * \note Defined as a macro calling \a GetDCAttr for _USE_NEWGAL. 
 *	   If _USE_NEWGAL is not defined, \a GetBkColor is defined as 
 *	   a function, and have the same semantics as this macro.
 *
 * \sa GetDCAttr, SetBkColor
 */
GAL_PIXEL GUIAPI GetBkColor (HDC hdc);

/**
 * \fn GetBkMode(hdc)
 * \brief Gets the background mode of a DC.
 *
 * \param hdc The device context.
 * \return The background mode of the DC \a hdc.
 *
 * \retval BM_TRANSPARENT   Indicate that reserve the background untouched when draw text. 
 * \retval BM_OPAQUE		Indicate that erase the background with background color when draw text.
 *
 * \note Defined as a macro calling \a GetDCAttr for _USE_NEWGAL. 
 *	   If _USE_NEWGAL is not defined, \a GetBkMode is defined as 
 *	   a function, and have the same semantics as this macro.
 *
 * \sa GetDCAttr, SetBkMode
 */
INT32 GUIAPI GetBkMode (HDC hdc);

/**
 * \fn GetTextColor(hdc)
 * \brief Gets the text color of a DC.
 *
 * \param hdc The device context.
 * \return The text color (pixel value) of the DC \a hdc.
 *
 * \note Defined as a macro calling \a GetDCAttr for _USE_NEWGAL. 
 *	   If _USE_NEWGAL is not defined, \a GetTextColor is defined as 
 *	   a function, and have the same semantics as this macro.
 *
 * \sa GetDCAttr, SetTextColor
 */
GAL_PIXEL GUIAPI GetTextColor (HDC hdc);

/**
 * \fn SetBkColor(hdc, color)
 * \brief Sets the background color of a DC to a new value.
 *
 * \param hdc The device context.
 * \param color The new background color (pixel value).
 * \return The old background pixel value of the DC \a hdc.
 *
 * \note Defined as a macro calling \a SetDCAttr for _USE_NEWGAL. 
 *	   If _USE_NEWGAL is not defined, \a SetBkColor is defined as 
 *	   a function, and have the same semantics as this macro.
 *
 * \sa SetDCAttr, GetBkColor
 */
GAL_PIXEL GUIAPI SetBkColor (HDC hdc, GAL_PIXEL color);

/**
 * \fn SetBkMode(hdc, mode)
 * \brief Sets the background color of a DC to a new mode.
 *
 * \param hdc The device context.
 * \param mode The new background mode, be can one of the following values:
 *
 *	  - BM_TRANSPARENT\n
 *		Indicate that reserve the background untouched when draw text. 
 *	  - BM_OPAQUE\n
 *		Indicate that erase the background with background color when draw text.
 *
 * \return The old background mode of the DC \a hdc.
 *
 * \note Defined as a macro calling \a SetDCAttr for _USE_NEWGAL. 
 *	   If _USE_NEWGAL is not defined, \a SetBkMode is defined as 
 *	   a function, and have the same semantics as this macro.
 *
 * \sa SetDCAttr, GetBkMode
 */
INT32 GUIAPI SetBkMode (HDC hdc, INT32 bkmode);

/**
 * \fn SetTextColor(hdc, color)
 * \brief Sets the text color of a DC to a new value.
 *
 * \param hdc The device context.
 * \param color The new text color (pixel value).
 * \return The old text color (pixel value) of the DC \a hdc.
 *
 * \note Defined as a macro calling \a SetDCAttr for _USE_NEWGAL. 
 *	   If _USE_NEWGAL is not defined, \a SetTextColor is defined as 
 *	   a function, and have the same semantics as this macro.
 *
 * \sa SetDCAttr, GetTextColor
 */
GAL_PIXEL GUIAPI SetTextColor (HDC hdc, GAL_PIXEL color);

/* Pen and brush support */

/**
 * \fn GetPenColor(hdc)
 * \brief Gets the pen color of a DC.
 *
 * \param hdc The device context.
 * \return The pen color (pixel value) of the DC \a hdc.
 *
 * \note Defined as a macro calling \a GetDCAttr for _USE_NEWGAL. 
 *	   If _USE_NEWGAL is not defined, \a GetPenColor is defined as 
 *	   a function, and have the same semantics as this macro.
 *
 * \sa GetDCAttr, SetPenColor
 */
GAL_PIXEL GUIAPI GetPenColor (HDC hdc);

/**
 * \fn GetBrushColor(hdc)
 * \brief Gets the brush color of a DC.
 *
 * \param hdc The device context.
 * \return The brush color (pixel value) of the DC \a hdc.
 *
 * \note Defined as a macro calling \a GetDCAttr for _USE_NEWGAL. 
 *	   If _USE_NEWGAL is not defined, \a GetBrushColor is defined as 
 *	   a function, and have the same semantics as this macro.
 *
 * \sa GetDCAttr, SetBrushColor
 */
GAL_PIXEL GUIAPI GetBrushColor (HDC hdc);

/**
 * \fn GetPenType(hdc)
 * \brief Gets the pen type of a DC.
 *
 * \param hdc The device context.
 * \return The pen type of the DC \a hdc.
 *
 * \retval PT_SOLID	 Only solid pen type supported so far.
 *
 * \note Defined as a macro calling \a GetDCAttr for _USE_NEWGAL. 
 *	   If _USE_NEWGAL is not defined, \a GetPenType is defined as 
 *	   a function, and have the same semantics as this macro.
 *
 * \sa GetDCAttr, SetPenType
 */
INT32 GUIAPI GetPenType (HDC hdc);

/**
 * \fn GetBrushType(hdc)
 * \brief Gets the brush type of a DC.
 *
 * \param hdc The device context.
 * \return The brush type of the DC \a hdc.
 *
 * \retval BT_SOLID Only solid brush type supported so far.
 *
 * \note Defined as a macro calling \a GetDCAttr for _USE_NEWGAL. 
 *	   If _USE_NEWGAL is not defined, \a GetBrushType is defined as 
 *	   a function, and have the same semantics as this macro.
 *
 * \sa GetDCAttr, SetBrushType
 */
INT32 GUIAPI GetBrushType (HDC hdc);

/**
 * \fn SetPenColor(hdc, color)
 * \brief Sets the pen color of a DC to a new value.
 *
 * \param hdc The device context.
 * \param color The new pen color (pixel value).
 * \return The old pen pixel value of the DC \a hdc.
 *
 * \note Defined as a macro calling \a SetDCAttr for _USE_NEWGAL. 
 *	   If _USE_NEWGAL is not defined, \a SetPenColor is defined as 
 *	   a function, and have the same semantics as this macro.
 *
 * \sa SetDCAttr, GetPenColor
 */
GAL_PIXEL GUIAPI SetPenColor (HDC hdc, GAL_PIXEL color);

/**
 * \fn SetBrushColor(hdc, color)
 * \brief Sets the brush color of a DC to a new value.
 *
 * \param hdc The device context.
 * \param color The new brush color (pixel value).
 * \return The old brush pixel value of the DC \a hdc.
 *
 * \note Defined as a macro calling \a SetDCAttr for _USE_NEWGAL. 
 *	   If _USE_NEWGAL is not defined, \a SetBrushColor is defined as 
 *	   a function, and have the same semantics as this macro.
 *
 * \sa SetDCAttr, GetBrushColor
 */
GAL_PIXEL GUIAPI SetBrushColor (HDC hdc, GAL_PIXEL color);

/**
 * \fn SetPenType(hdc, type)
 * \brief Sets the pen type of a DC to a new type.
 *
 * \param hdc The device context.
 * \param mode The new pen type. Only \a PT_SOLID is supported so far.
 * \return The old pen type of the DC \a hdc.
 *
 * \note Defined as a macro calling \a SetDCAttr for _USE_NEWGAL. 
 *	   If _USE_NEWGAL is not defined, \a SetPenType is defined as 
 *	   a function, and have the same semantics as this macro.
 *
 * \sa SetDCAttr, GetPenType
 */
INT32 GUIAPI SetPenType (HDC hdc, INT32 pentype);

/**
 * \fn SetBrushType(hdc, type)
 * \brief Sets the brush type of a DC to a new type.
 *
 * \param hdc The device context.
 * \param mode The new brush type. Only \a BT_SOLID is supported so far.
 * \return The old brush type of the DC \a hdc.
 *
 * \note Defined as a macro calling \a SetDCAttr for _USE_NEWGAL. 
 *	   If _USE_NEWGAL is not defined, \a SetBrushType is defined as 
 *	   a function, and have the same semantics as this macro.
 *
 * \sa SetDCAttr, GetBrushType
 */
INT32 GUIAPI SetBrushType (HDC hdc, INT32 brushtype);

/**
 * \fn VOID GUIAPI SetPixel (HDC hdc, INT32 x, INT32 y, GAL_PIXEL pixel)
 * \brief Sets the pixel with a new pixel value at the specified position on a DC.
 *
 * This function sets the pixel with a pixel value \a pixel at the specified position \a (x,y) 
 * on the DC \a hdc. You can the pre-defined standard system pixel values.
 *
 * \param hdc The device context.
 * \param x,y The pixel position.
 * \param pixel The pixel value.
 *
 * \sa GetPixel, color_vars
 */
VOID GUIAPI SetPixel (HDC hdc, INT32 x, INT32 y, GAL_PIXEL pixel);

#define  PutPixel(hdc, x, y, pixel)	 SetPixel(hdc, x, y, pixel)

/**
 * \fn GAL_PIXEL GUIAPI SetPixelRGB (HDC hdc, INT32 x, INT32 y, UINT8 r, UINT8 g, UINT8 b)
 * \brief Sets the pixel by a RGB triple at the specified position on a DC.
 *
 * This function sets the pixel with a RGB triple \a (r,g,b) at the specified position \a (x,y) 
 * on the DC \a hdc.
 *
 * \param hdc The device context.
 * \param x,y The pixel position.
 * \param r,g,b The red, green, and blue components of the color.
 * \return The pixel value of the RGB triple.
 *
 * \sa GetPixel, RGB2Pixel
 */
GAL_PIXEL GUIAPI SetPixelRGB (HDC hdc, INT32 x, INT32 y, UINT8 r, UINT8 g, UINT8 b);

/**
 * \fn GAL_PIXEL GUIAPI GetPixel (HDC hdc, INT32 x, INT32 y)
 * \brief Gets the pixel value at the specified position on a DC.
 *
 * This function gets the pixel value at the specified position \a (x,y) on the DC \a hdc.
 *
 * \param hdc The device context.
 * \param x,y The pixel position.
 * \return The pixel value.
 *
 * \sa SetPixel
 */
GAL_PIXEL GUIAPI GetPixel (HDC hdc, INT32 x, INT32 y);

/**
 * \fn GAL_PIXEL GUIAPI GetPixelRGB (HDC hdc, INT32 x, INT32 y, UINT8* r, UINT8* g, UINT8* b)
 * \brief Gets the pixel value at the specified position on a DC in RGB triple.
 *
 * This function gets the pixel value at the specified position \a (x,y) 
 * on the DC \a hdc in RGB triple.
 *
 * \param hdc The device context.
 * \param x,y The pixel position.
 * \param r,g,b The red, green, and red components of the pixel will be returned through
 *		these pointers.
 * \return The pixel value.
 *
 * \sa SetPixelRGB
 */
GAL_PIXEL GUIAPI GetPixelRGB (HDC hdc, INT32 x, INT32 y, UINT8 * r, UINT8 * g, UINT8 * b);

/**
 * \fn GAL_PIXEL GUIAPI RGB2Pixel (HDC hdc, UINT8 r, UINT8 g, UINT8 b)
 * \brief Gets the pixel value from a color in RGB triple under a DC.
 *
 * This function gets the pixel value from the RGB triple \a (r,g,b) under the DC \a hdc.
 *
 * \param hdc The device context.
 * \param r,g,b,a The red, green, and red components of a color.
 * \return The pixel value.
 *
 * \sa Pixel2RGB
 */
GAL_PIXEL GUIAPI RGB2Pixel (HDC hdc, UINT8 r, UINT8 g, UINT8 b);

/**
 * \fn VOID GUIAPI Pixel2RGB (HDC hdc, GAL_PIXEL pixel, UINT8* r, UINT8* g, UINT8* b)
 * \brief Gets the color in RGB triple from a pixel value under a DC.
 *
 * This function gets the color in RGB triple from the pixel value \a pixel under the DC \a hdc.
 *
 * \param hdc The device context.
 * \param r,g,b The red, green, and red components of the pixel will be returned 
 *		through these pointers.
 * \return The pixel value.
 *
 * \note Only defined for _USE_NEWGAL. 
 *
 * \sa RGB2Pixel
 */
VOID GUIAPI Pixel2RGB (HDC hdc, GAL_PIXEL pixel, UINT8* r, UINT8* g, UINT8* b);


/**
 * \fn VOID GUIAPI MoveTo (HDC hdc, INT32 x, INT32 y)
 * \brief Moves the current pen position.
 *
 * This function moves the current pen position of the DC \a hdc to \a (x,y).
 * The next line or other pen drawing operation will start from the position.
 *
 * \param hdc The device context.
 * \param x,y The new pen position.
 *
 * \sa LineTo
 */
VOID GUIAPI MoveTo (HDC hdc, INT32 x, INT32 y);

/**
 * \fn VOID GUIAPI LineTo (HDC hdc, INT32 x, INT32 y)
 * \brief Draws a line to a position.
 *
 * This function draws a line from the current pen position to \a (x,y),
 * and then moves the pen position to \a (x,y).
 * The next line or other pen drawing operation will start from the position.
 *
 * \param hdc The device context.
 * \param x,y The end point of the line.
 *
 * \sa MoveTo, LineGenerator, dc_attrs
 */
VOID GUIAPI LineTo (HDC hdc, INT32 x, INT32 y);

VOID GUIAPI Line (HDC hdc, INT32 x0, INT32 y0, INT32 x1, INT32 y1);
VOID GUIAPI LineXorVs (HDC hdc, INT32 y0, INT32 y1, INT32 x);

void GUIAPI DrewCircle(HDC hdc, int cx, int cy, int r, GAL_COLOR *c);

void GUIAPI DrawLine(HDC hdc, int x1, int y1, int x2, int y2);
VOID GUIAPI D3DLine(HDC hdc, int width, int x1, int y1, int x2, int y2);

typedef enum{
	ARROW_LEFT,
	ARROW_RIGHT,
	ARROW_UP,
	ARROW_DOWN,
}ARROW_TYPE;
VOID GUIAPI DrawArrow(HDC hdc, INT32 x, INT32 y, INT32 cx, INT32 cy,
					ARROW_TYPE type, GAL_PIXEL forecolor, GAL_PIXEL backcolor);

VOID GUIAPI DrawScrollRect
(HWND hWnd,UINT16 iCur,UINT16 iCount,UINT16 iItems,INT8 mode,GAL_PIXEL color);

VOID GUIAPI DrawScrollH(HWND hWnd, UINT16 iCur, UINT16 iCount, UINT16 iItems);
VOID GUIAPI DrawScrollV(HWND hWnd, UINT16 iCur, UINT16 iCount, UINT16 iItems);
/**
 * \fn VOID GUIAPI Rectangle (HDC hdc, INT32 x0, INT32 y0, INT32 x1, INT32 y1)
 * \brief Draws a rectangle.
 *
 * This function draws a rectangle by using \a MoveTo and \a LineTo.
 * The current pen position after calling this function will be \a (x1,y1).
 *
 * \param hdc The device context.
 * \param x0,y0 The coordinates of the upper-left corner of the rectangle.
 * \param x1,y1 The coordinates of the lower-right corner of the rectangle.
 *
 * \sa MoveTo, LineTo
 */
VOID GUIAPI Rectangle (HDC hdc, INT32 x0, INT32 y0, INT32 x1, INT32 y1);

#define Rect(hdc, x0, y0, x1, y1)   Rectangle(hdc, x0, y0, x1, y1)

VOID GUIAPI Rect3D(HDC hdc, INT32 x0, INT32 y0, INT32 x1, INT32 y1, 
				   GAL_PIXEL lt_color, GAL_PIXEL rb_color );

/** 
 * \fn VOID GUIAPI PolylineTo (HDC hdc, const POINT* pts, INT32 vertices)
 * \brief Draws a polyline.
 *
 * This function draws a polyline by using \a MoveTo and \a LineTo.
 * The current pen position after calling this function will be the
 * last vertex of the polyline.
 *
 * \param hdc The device context.
 * \param pts The pointer to the vertex array of the polyline.
 * \param vertices The number of the vertices.
 *
 * \sa MoveTo, LineTo
 */
VOID GUIAPI PolylineTo (HDC hdc, const POINT* pts, INT32 vertices);


/**
 * \fn VOID GUIAPI Circle (HDC hdc, INT32 sx, INT32 sy, INT32 r)
 * \brief Draws a circle.
 *
 * This function draws a circle with current pen color on the DC \a hdc.
 * The center of the circle is at \a (sx, sy), and the radius is \a r.
 * 
 * \param hdc The device context.
 * \param sx,sy The center of the circle.
 * \param r The radius of the circle.
 *
 * \sa CircleGenerator
 */
VOID GUIAPI Circle (HDC hdc, INT32 sx, INT32 sy, INT32 r);

/**
 * \fn VOID GUIAPI FillBox (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h)
 * \brief Fills a rectangle box.
 *
 * This function fills a box with the current brush in the DC \a hdc. 
 * Note that MiniGUI only defined the color property for the brush objects so far.
 *
 * \param hdc The device context.
 * \param x,y The coorinates of the upper-left corner of the box.
 * \param w,h The width and height of the box.
 *
 * \sa dc_attrs
 */
VOID GUIAPI FillBox (HDC hdc, INT32 x1, INT32 y1, INT32 x2, INT32 y2);

	/** @} end of draw_fns */
	
	/**
	 * \defgroup map_fns Mapping Operations
	 *
	 * The mapping mode defines the unit of measure used to transform 
	 * page-space units into device-space units, and also defines 
	 * the orientation of the device's x and y axes. 
	 *
	 * So far, MiniGUI support only two mapping mode: 
	 *
	 *	  - MM_TEXT\n
	 *		Each logical unit is mapped to on device pixel. 
	 *		Positive x is to the right; positive y is down.
	 *	  - MM_ANISOTROPIC\n
	 *		Logical units are mapped to arbitrary units with arbitrarily scaled axes; 
	 *		Use \a SetWindowExt and \a SetViewportExt functions to specify the units, 
	 *		orientation, and scaling required.
	 *
	 * The following formula shows the math involved in converting a point 
	 * from page space to device space:
	 *
	 * \code
	 *	  Dx = ((Lx - WOx) * VEx / WEx) + VOx
	 * \endcode
	 *
	 * The following variables are involved:
	 *
	 *	  - Dx	x value in device units
	 *	  - Lx	x value in logical units (also known as page space units)
	 *	  - WO	window x origin
	 *	  - VO	viewport x origin
	 *	  - WE	window x-extent
	 *	  - VE	viewport x-extent
	 *
	 * The same equation with y replacing x transforms the y component of a point.
	 * The formula first offsets the point from its coordinate origin. 
	 * This value, no longer biased by the  origin, is then scaled into 
	 * the destination coordinate system by the ratio of the extents. 
	 * Finally, the scaled value is offset by the destination origin to 
	 * its final mapping.
	 *
	 * @{
	 */

#define MM_TEXT			   0
#define MM_ANISOTROPIC		1

/**
 * \fn GetMapMode(hdc)
 * \brief Retrives the current mapping mode of a DC.
 *
 * This function retrives the current mapping mode of the DC \a hdc. 
 *
 * So far, MiniGUI support two mapping modes: MM_TEXT and MM_ANISOTROPIC.
 *
 * \param hdc The device context.
 * \return The current mapping mode, can be either \a MM_TEXT or \a MM_ANISOTROPIC.
 *
 * \note Defined as a macro calling \a GetDCAttr for _USE_NEWGAL. 
 *	   If _USE_NEWGAL is not defined, \a GetMapMode is defined as 
 *	   a function, and have the same semantics as this macro.
 *
 * \sa SetWindowExt, SetViewportExt, SetMapMode
 */
INT32 GUIAPI GetMapMode (HDC hdc);

/**
 * \fn SetMapMode(hdc, mapmode)
 * \brief Sets the mapping mode of a display context.
 *
 * This function sets the mapping mode of the specified display context \a hdc.
 *
 * So far, MiniGUI support two mapping modes: MM_TEXT and MM_ANISOTROPIC.
 *
 * \param hdc The device context.
 * \param mapmode The new mapping mode, should be either \a MM_TEXT or \a MM_ANISOTROPIC.
 * \return The old mapping mode, either \a MM_TEXT or \a MM_ANISOTROPIC.
 *
 * \note Defined as a macro calling \a SetDCAttr for _USE_NEWGAL. 
 *	   If _USE_NEWGAL is not defined, \a SetMapMode is defined as 
 *	   a function, and have the same semantics as this macro.
 *
 * \sa SetWindowExt, SetViewportExt, SetMapMode
 */
VOID GUIAPI SetMapMode (HDC hdc, INT32 mapmode);

/**
 * \fn VOID GUIAPI DPtoLP (HDC hdc, POINT* pPt)
 * \brief Converts device coordinates into logical coordinates.
 * 
 * This function converts device coordinates into logical coordinates 
 * in the device context \a hdc.
 *
 * The conversion depends on the mapping mode of the display context, 
 * the settings of the origins and extents for the window and viewport. 
 * The x-coordinate and y-coordinate contained in struct \a pPt will be 
 * transformed.
 * 
 * \param hdc The device context.
 * \param pPt The coordinates to be converted, and the transformed coordinates
 *		will be contained in this buffer after the function returns.
 *
 * \sa LPtoDP
 */
VOID GUIAPI DPtoLP (HDC hdc, POINT* pPt);

/**
 * \fn VOID GUIAPI LPtoDP (HDC hdc, POINT* pPt)
 * \brief Converts logical coordinates into device coordinates.
 * 
 * This function converts logical coordinates into device coordinates 
 * in the device context \a hdc.
 *
 * The conversion depends on the mapping mode of the display context, 
 * the settings of the origins and extents for the window and viewport.
 * The x-coordinate and y-coordinate contained in struct \a pPt will be 
 * transformed.
 * 
 * \param hdc The device context.
 * \param pPt The coordinates to be converted, and the transformed coordinates
 *		will be contained in this buffer after the function returns.
 *
 * \sa DPtoLP
 */
VOID GUIAPI LPtoDP (HDC hdc, POINT* pPt);

	/** @} end of map_fns */

/**
 * \fn VOID SetRect (RECT* prc, INT32 left, INT32 top, INT32 right, INT32 bottom)
 * \brief Sets a rectangle.
 *
 * This function sets the rectangle with specified values.
 *
 * \param prc The pointer to the rectangle.
 * \param left,top The coordinates of the upper-left corner of the rectangle.
 * \param right,bottom The coordinates of the lower-right corner of the rectangle.
 *
 * \note Defined as an inline function for _USE_NEWGAL. 
 *
 * \sa SetRectEmpty
 */
 VOID SetRect (RECT* prc, INT32 left, INT32 top, INT32 right, INT32 bottom);

/**
 * \fn VOID SetRectEmpty (RECT* prc)
 * \brief Empties a rectangle.
 *
 * This function empties the rectangle pointed to by \a prc. 
 * An empty rectangle in MiniGUI is a rectangle whose width and height both are zero. 
 * This function will sets all coordinates of the rectangle to be zero.
 *
 * \param prc The pointer to the rectangle.
 *
 * \note Defined as an inline function for _USE_NEWGAL. 
 *
 * \sa SetRect
 */
VOID SetRectEmpty (RECT* prc);

	/**
	 * \defgroup rect_fns Rectangle operations
	 * @{
	 */
/**
 * \fn VOID CopyRect (RECT* pdrc, const RECT* psrc)
 * \brief Copies one rectangle to another.
 *
 * This function copies the coordinates of the source rectangle 
 * pointed to by \a psrc to the destination rectangle pointed to by \a pdrc.
 *
 * \param pdrc The pointer to the destination rectangle.
 * \param psrc The pointer to the source rectangle.
 *
 * \note Defined as an inline function for _USE_NEWGAL. 
 *
 * \sa SetRect
 */
VOID CopyRect (RECT* pdrc, const RECT* psrc);

/**
 * \fn VOID OffsetRect (RECT* prc, INT32 x, INT32 y)
 * \brief Moves a rectangle by offsets.
 *
 * This function moves the specified rectangle by the specified offsets. 
 * \a x and \a y specify the amount to move the rectangle left/right or up/down 
 * respectively. \a x must be a negative value to move the rectangle to
 * the left, and \a y must be a negative value to move the rectangle up.
 *
 * \param prc The pointer to the rectangle.
 * \param x,y The offsets.
 *
 * \note Defined as an inline function for _USE_NEWGAL. 
 *
 * \sa InflateRect
 */
VOID OffsetRect (RECT* prc, INT32 x, INT32 y);

/**
 * \fn VOID InflateRect (RECT* prc, INT32 cx, INT32 cy)
 * \brief Increases or decreases the width and height of an rectangle.
 *
 * This function increases or decreases the width and height of 
 * the specified rectangle \a prc. This function adds \a cx units 
 * to the left and right ends of the rectangle and \a cy units to the 
 * top and bottom. the \cx and \cy are signed values; positive values 
 * increases the width and height, and negative values decreases them.
 *
 * \param prc The pointer to the rectangle.
 * \param cx,cy The inflating values.
 *
 * \note Defined as an inline function for _USE_NEWGAL. 
 *
 * \sa InflateRectToPt
 */
VOID InflateRect (RECT* prc, INT32 cx, INT32 cy);

/**
 * \fn VOID InflateRectToPt (RECT* prc, INT32 x, INT32 y)
 * \brief Inflates a rectangle to contain a point.
 *
 * This function inflates the rectangle \a prc to contain the specified point \a (x,y).
 *
 * \param prc The pointer to the rectangle.
 * \param x,y The point.
 *
 * \note Defined as an inline function for _USE_NEWGAL. 
 *
 * \sa InflateRect
 */
VOID InflateRectToPt (RECT* prc, INT32 x, INT32 y);

/**
 * \fn BOOL PtInRect(const RECT* prc, INT32 x, INT32 y)
 * \brief Determines whether a point lies within an rectangle.
 *
 * This function determines whether the specified point \a (x,y) lies within 
 * the specified rectangle \a prc.
 *
 * A point is within a rectangle if it lies on the left or top side or is 
 * within all four sides. A point on the right or bottom side is considered 
 * outside the rectangle.
 *
 * \param prc The pointer to the rectangle.
 * \param x,y The point.
 *
 * \note Defined as an inline function for _USE_NEWGAL. 
 */
BOOL PtInRect(const RECT* prc, INT32 x, INT32 y);

/**
 * \fn BOOL GUIAPI IsRectEmpty (const RECT* prc)
 * \brief Determines whether an rectangle is empty.
 *
 * This function determines whether the specified rectangle \a prc is empty. 
 * An empty rectangle is one that has no area; that is, the coordinates 
 * of the right side is equal to the coordinate of the left side, or the
 * coordinates of the bottom side is equal to the coordinate of the top side.
 *
 * \param prc The pointer to the rectangle.
 * \return TRUE for empty, otherwise FALSE.
 */
BOOL GUIAPI IsRectEmpty (const RECT* prc);

/**
 * \fn BOOL GUIAPI EqualRect (const RECT* prc1, const RECT* prc2)
 * \brief Determines whether two rectangles are equal.
 *
 * This function determines whether the two specified rectangles 
 * (\a prc1 and \a prc2) are equal by comparing the coordinates of 
 * the upper-left and lower-right corners.
 *
 * \param prc1,prc2 The pointers to the two rectangles.
 * \return TRUE for equal, otherwise FALSE.
 */
BOOL GUIAPI EqualRect (const RECT* prc1, const RECT* prc2);

/**
 * \fn VOID GUIAPI NormalizeRect (RECT* pRect)
 * \brief Normalizes a rectangle.
 *
 * This function normalizes the rectangle pointed to by \a prc 
 * so that both the height and width are positive.
 *
 * \param pRect The pointer to the rectangle.
 */
VOID GUIAPI NormalizeRect (RECT* pRect);

/**
 * \fn BOOL GUIAPI IntersectRect (RECT* pdrc, const RECT* psrc1, const RECT* psrc2)
 * \brief Calculates the intersection of two rectangles.
 *
 * This function calculates the intersection of two source rectangles (\a psrc1 and \a psrc2) 
 * and places the coordinates of the intersection rectangle into the destination rectangle
 * pointed to by \a pdrc. If the source rectangles do not intersect, and empty rectangle 
 * (in which all coordinates are set to zero) is placed into the destination rectangle.
 *
 * \param pdrc The pointer to the destination rectangle.
 * \param psrc1,psrc2 Two source rectangles.
 * \return TRUE if the source rectangles intersect, otherwise FALSE.
 *
 * \sa DoesIntersect, IsCovered
 */
BOOL GUIAPI IntersectRect (RECT* pdrc, const RECT* psrc1, const RECT* psrc2);

/**
 * \fn BOOL GUIAPI IsCovered (const RECT* prc1, const RECT* prc2)
 * \brief Determines whether one rectangle covers another.
 *
 * This function determines whether one rectangle (\a prc1) 
 * covers another rectangle (\a prc2).
 *
 * \param prc1,prc2 Two rectangles.
 * \return TRUE if the first rectangle covers the second, otherwise FALSE.
 *
 * \sa DoesIntersect
 */
BOOL GUIAPI IsCovered (const RECT* prc1, const RECT* prc2);

/**
 * \fn BOOL GUIAPI DoesIntersect (const RECT* psrc1, const RECT* psrc2)
 * \brief Determines whether two rectangles intersect.
 *
 * This function determines whether two rectangles (\a psrc1 and \a psrc2) intersect.
 *
 * \param psrc1,psrc2 Two source rectangles.
 * \return TRUE if the source rectangles intersect, otherwise FALSE.
 *
 * \sa IntersectRect
 */
BOOL GUIAPI DoesIntersect (const RECT* psrc1, const RECT* psrc2);

/**
 * \fn BOOL GUIAPI UnionRect (RECT* pdrc, const RECT* psrc1, const RECT* psrc2)
 * \brief Unions two source rectangles.
 *
 * This function creates the union (\a pdrc) of two rectangles (\a psrc1 and \a psrc2),
 * if the source rectangles are border upon and not stagger.
 *
 * \param pdrc The unioned rectangle.
 * \param psrc1,psrc2 Two source rectangles.
 * \return TRUE if the source rectangles are border upon and not stagger, otherwise FALSE.
 *
 * \sa GetBoundRect
 */
BOOL GUIAPI UnionRect (RECT* pdrc, const RECT* psrc1, const RECT* psrc2);

/**
 * \fn VOID GUIAPI GetBoundRect (PRECT pdrc,  const RECT* psrc1, const RECT* psrc2)
 * \brief Gets the bound rectangle of two source rectangles.
 *
 * This function creates the bound rect (\a pdrc) of two rectangles (\a psrc1 and \a prsrc2). 
 * The bound rect is the smallest rectangle that contains both source rectangles.
 *
 * \param pdrc The destination rectangle.
 * \param psrc1,psrc2 Two source rectangle.
 *
 * \sa UnionRect
 */
VOID GUIAPI GetBoundRect (PRECT pdrc,  const RECT* psrc1, const RECT* psrc2);

/**
 * \fn INT32 GUIAPI SubtractRect (RECT* rc, const RECT* psrc1, const RECT* psrc2)
 * \brief Obtains the rectangles when substracting one rectangle from another.
 *
 * This function obtains the rectangles substracting the rectangle \a psrc1 
 * from the other \a psrc2. \a rc should be an array of RECT struct, and 
 * may contain at most four rectangles. This function returns 
 * the number of result rectangles.
 *
 * \param rc The pointer to the resule rectangle array.
 * \param psrc1 The pointer to the minuend rectangle.
 * \param psrc2 The pointer to the subtrahend rectangle.
 * \return The number of result rectangles.
 *
 * \sa UnionRect
 */
INT32 GUIAPI SubtractRect (RECT* rc, const RECT* psrc1, const RECT* psrc2);

/**
 * \def RECTWP(prc)
 * \brief Gets the width of a RECT object by using the pointer to it.
 */
#define RECTWP(prc)  (prc->right - prc->left)
/**
 * \def RECTHP(prc)
 * \brief Gets the height of a RECT object by using the pointer to it.
 */
#define RECTHP(prc)  (prc->bottom - prc->top)
/**
 * \def RECTW(rc)
 * \brief Gets the width of a RECT object.
 */
#define RECTW(rc)	(rc.right - rc.left)
/**
 * \def RECTH(rc)
 * \brief Gets the height of a RECT object.
 */
#define RECTH(rc)	(rc.bottom - rc.top)

	/** @} end of rect_fns */

	/**
	 * \defgroup font_fns Logical font operations
	 *
	 * MiniGUI uses logical font to render text in a DC. You can create a logical
	 * font by using \a CreateLogFont and select it into a DC by using \a SelectFont,
	 * then you can use this logical font to render text by using \a TextOutLen or \a DrawTextEx.
	 *
	 * @{
	 */

/* Font-related structures */
/** Font name format:
*   type-family-style-width-height-charset-encoding
*   5	15	   6	 3	 3	  15  
*   description:
*   type		:  vaf,  rbf, tty, type1, etc
*   family	  :  system, courier, times, Helvetica, song, ming, etc
*   style	   :  weight, slant, setwidth , spacing, underline, strokeout
*   charset	 :  BIG8859, GB2312, BIG5, GB18030
*
*   目前, 字体名字:
*	 type-family-width-height-charset-encoding
*	 5	15	 3	 3	  15	   
**/

//#define LEN_DEVFONT_NAME			79
#define LEN_DEVFONT_NAME			46
#define LEN_FONT_NAME			   15

#define FONT_WEIGHT_NIL			 '\0'
#define FONT_WEIGHT_ALL			 '*'
#define FONT_WEIGHT_BLACK		   'c'
#define FONT_WEIGHT_BOLD			'b'
#define FONT_WEIGHT_BOOK			'k'
#define FONT_WEIGHT_DEMIBOLD		'd'
#define FONT_WEIGHT_LIGHT		   'l'
#define FONT_WEIGHT_MEDIUM		  'm'
#define FONT_WEIGHT_REGULAR		 'r'

#define FS_WEIGHT_MASK			  0x000000FF
#define FS_WEIGHT_BLACK			 0x00000001
#define FS_WEIGHT_BOLD			  0x00000002
#define FS_WEIGHT_BOOK			  0x00000004
#define FS_WEIGHT_DEMIBOLD		  0x00000006 /* BOOK | BOLD */
#define FS_WEIGHT_LIGHT			 0x00000010
#define FS_WEIGHT_MEDIUM			0x00000020
#define FS_WEIGHT_REGULAR		   0x00000000

#define FONT_SLANT_NIL			  '\0'
#define FONT_SLANT_ALL			  '*'
#define FONT_SLANT_ITALIC		   'i'
#define FONT_SLANT_OBLIQUE		  'o'
#define FONT_SLANT_ROMAN			'r'

#define FS_SLANT_MASK			   0x00000F00
#define FS_SLANT_ITALIC			 0x00000100
#define FS_SLANT_OBLIQUE			0x00000200
#define FS_SLANT_ROMAN			  0x00000000

#define FONT_SETWIDTH_NIL		   '\0'
#define FONT_SETWIDTH_ALL		   '*'
#define FONT_SETWIDTH_BOLD		  'b'
#define FONT_SETWIDTH_CONDENSED	 'c'
#define FONT_SETWIDTH_SEMICONDENSED 's'
#define FONT_SETWIDTH_NORMAL		'n'

#define FS_SETWIDTH_MASK			0x0000F000
#define FS_SETWIDTH_BOLD			0x00001000
#define FS_SETWIDTH_CONDENSED	   0x00002000
#define FS_SETWIDTH_SEMICONDENSED   0x00004000
#define FS_SETWIDTH_NORMAL		  0x00000000

#define FONT_SPACING_NIL			'\0'
#define FONT_SPACING_ALL			'*'
#define FONT_SPACING_MONOSPACING	'm'
#define FONT_SPACING_PROPORTIONAL   'p'
#define FONT_SPACING_CHARCELL	   'c'

#define FS_SPACING_MASK			 0x000F0000
#define FS_SPACING_MONOSPACING	  0x00010000
#define FS_SPACING_PROPORTIONAL	 0x00020000
#define FS_SPACING_CHARCELL		 0x00000000

#define FONT_UNDERLINE_NIL		  '\0'
#define FONT_UNDERLINE_ALL		  '*'
#define FONT_UNDERLINE_LINE		 'u'
#define FONT_UNDERLINE_NONE		 'n'

#define FS_UNDERLINE_MASK		   0x00F00000
#define FS_UNDERLINE_LINE		   0x00100000
#define FS_UNDERLINE_NONE		   0x00000000

#define FONT_STRUCKOUT_NIL		  '\0'
#define FONT_STRUCKOUT_ALL		  '*'
#define FONT_STRUCKOUT_LINE		 's'
#define FONT_STRUCKOUT_NONE		 'n'

#define FS_STRUCKOUT_MASK		   0x0F000000
#define FS_STRUCKOUT_LINE		   0x01000000
#define FS_STRUCKOUT_NONE		   0x00000000

/* 字体类型 */
#define FONT_TYPE_NAME_BITMAP_RAW   "RBF"  /* "rbf", 定宽光栅字体 */
#define FONT_TYPE_NAME_BITMAP_VAR   "VBF"  /* "vbf", 变宽光栅字体 */
#define FONT_TYPE_NAME_SCALE_TTF	"TTF"  /* "ttf", 矢量字体	 */
#define FONT_TYPE_NAME_SCALE_T1F	"T1F"  /* "t1f", PDF 字体	 */
#define FONT_TYPE_NAME_ALL		  "*"

#define FONT_TYPE_BITMAP_RAW		0x0001  /* "rbf" */
#define FONT_TYPE_BITMAP_VAR		0x0002  /* "vbf" */
#define FONT_TYPE_SCALE_TTF		 0x0010  /* "ttf" */
#define FONT_TYPE_SCALE_T1F		 0x0010  /* "t1f" */
#define FONT_TYPE_ALL			   0xFFFF  /* "all" */

/* 字符集的名字 */
#define FONT_CHARSET_ISO8859_1	  "ISO8859-1"
#define FONT_CHARSET_ISO8859_2	  "ISO8859-2"
#define FONT_CHARSET_ISO8859_3	  "ISO8859-3"
#define FONT_CHARSET_ISO8859_4	  "ISO8859-4"
#define FONT_CHARSET_ISO8859_5	  "ISO8859-5"
#define FONT_CHARSET_ISO8859_6	  "ISO8859-6"
#define FONT_CHARSET_ISO8859_7	  "ISO8859-7"
#define FONT_CHARSET_ISO8859_8	  "ISO8859-8"
#define FONT_CHARSET_ISO8859_9	  "ISO8859-9"
#define FONT_CHARSET_ISO8859_10	 "ISO8859-10"
#define FONT_CHARSET_ISO8859_11	 "ISO8859-11"
#define FONT_CHARSET_ISO8859_12	 "ISO8859-12"
#define FONT_CHARSET_ISO8859_13	 "ISO8859-13"
#define FONT_CHARSET_ISO8859_14	 "ISO8859-14"
#define FONT_CHARSET_ISO8859_15	 "ISO8859-15"
#define FONT_CHARSET_GB2312_1980_0  "GB2312.1980-0"
#define FONT_CHARSET_GB18030		"GB18030"
#define FONT_CHARSET_BIG5		   "BIG5"
#define FONT_CHARSET_EUCKR		  "EUCKR"
#define FONT_CHARSET_UJIS		   "UJIS"

#define FONT_MAX_SIZE			   256
#define FONT_MIN_SIZE			   4

/* 字形的名字 */
#define FONT_FAMILY_ROM			 "ROM"
#define FONT_FAMILY_SYSTEM		  "SYSTEM"
#define FONT_FAMILY_SONG			"SONG"
#define FONT_FAMILY_TIMES		   "TIMES"
#define FONT_FAMILY_ARIAL		   "ARIAL"
#define FONT_FAMILY_FIXEDSYS		"FIXEDSYS"
#define FONT_FAMILY_COURIER		 "COURIER"
#define FONT_FAMILY_VERDANA		 "VERDANA"
#define FONT_FAMILY_SANSSERIF	   "SANSSERIF"

/* 完整的字体名字; 目前系统中实现的全部字体. */
#define FONT_VBF_ROM_5X7_ISO8859_1			"VBF-ROM-5-7-ISO8859-1"
#define FONT_VBF_ROM_8X8_ISO8859_1			"VBF-ROM-8-8-ISO8859-1"
#define FONT_VBF_ROM_8X12_ISO8859_1		   "VBF-ROM-8-12-ISO8859-1"
#define FONT_VBF_ROM_8X16_ISO8859_1		   "VBF-ROM-8-16-ISO8859-1" 
#define FONT_VBF_ROM_16X20_ISO8859_1		  "VBF-ROM-16-20-ISO8859-1"
#define FONT_VBF_ROM_24X32_ISO8859_1		  "VBF-ROM-24-32-ISO8859-1"
#define FONT_VBF_ROM_32X48_ISO8859_1		  "VBF-ROM-32-48-ISO8859-1"
#define FONT_VBF_ROM_40X60_ISO8859_1		  "VBF-ROM-40-60-ISO8859-1"
#define FONT_VBF_ROM_48X72_ISO8859_1		  "VBF-ROM-48-72-ISO8859-1"
#define FONT_VBF_ROM_56X84_ISO8859_1		  "VBF-ROM-56-84-ISO8859-1"
#define FONT_VBF_ROM_80X120_ISO8859_1		 "VBF-ROM-80-120-ISO8859-1"

#if _ENB_PRT16X18_FONT > 0	// Add for 16X18
#define FONT_VBF_ROM_16X18_ISO8859_1		  "VBF-ROM-16-18-ISO8859-1"
#endif

#define FONT_RBF_ROM_8X16_ISO8859_1		   "RBF-ROM-8-16-ISO8859-1"		 // 暂时没有用到
#define FONT_RBF_ROM_12X12_GB2312			 "RBF-ROM-12-12-GB2312.1980-0"
#define FONT_RBF_ROM_16X16_GB2312			 "RBF-ROM-16-16-GB2312.1980-0"

#if _RUS_SUPPORT
#define FONT_CHARSET_RUSSIAN_1980_0			"RUSSIA.1980-0"				  //Change by Latrom_06-21-2011
#endif

#if _ENB_RUS8X12_FONT
#define FONT_RBF_ROM_8X12_RUSSIAN			 "RBF-ROM-8-12-RUSSIA.1980-0"	 //Change by Latrom_06-21-2011
#endif

#if _ENB_RUS8X16_FONT
#define FONT_RBF_ROM_8X16_RUSSIAN			 "RBF-ROM-8-16-RUSSIA.1980-0"	 //Change by Latrom_06-21-2011
#endif

#if _ENB_PRT16X18_FONT > 0
#define FONT_RBF_ROM_16X18_GB2312			 "RBF-ROM-16-18-GB2312.1980-0"
#endif

#if _ENB_YAHEI17_FONT > 0
#define FONT_RBF_ROM_23X30_GB2312			 "RBF-ROM-23-30-GB2312.1980-0"
#endif

struct _DEVFONT;
typedef struct _DEVFONT DEVFONT;

/** The logical font structure. */
typedef struct _LOGFONT {
	/** The type of the logical font. */
	CHAR type [LEN_FONT_NAME + 1];
	/** The family name of the logical font. */
	CHAR family [LEN_FONT_NAME + 1];
	/** The charset of the logical font. */
	CHAR charset [LEN_FONT_NAME + 1];
	/** The size of the logical font. */
	INT32	 size;
	DEVFONT * sbc_devfont;
	DEVFONT * mbc_devfont;
} LOGFONT;
typedef LOGFONT*	PLOGFONT;

struct _WORDINFO;
typedef struct _WORDINFO WORDINFO;

#define MAX_LEN_MCHAR			   4

typedef struct _CHARSETOPS
{
	INT32 nr_chars;
	INT32 bytes_per_char;
	INT32 bytes_maxlen_char;
	const CHAR * name;
	CHAR  def_char [MAX_LEN_MCHAR];

	INT32 (*len_first_char) (const UCHAR* mstr, INT32 mstrlen);
	INT32 (*char_offset) (const UCHAR* mchar);

	INT32 (*nr_chars_in_str) (const UCHAR* mstr, INT32 mstrlen);

	INT32 (*is_this_charset) (const UCHAR* charset);

	INT32 (*len_first_substr) (const UCHAR* mstr, INT32 mstrlen);
	const UCHAR* (*get_next_word) (const UCHAR* mstr, 
								   INT32 strlen, WORDINFO* word_info);

	INT32 (*pos_first_char) (const UCHAR* mstr, INT32 mstrlen);
} CHARSETOPS;

typedef struct _FONTOPS
{
	INT32 (*get_char_width) (LOGFONT* logfont, DEVFONT* devfont, 
							 const UCHAR* mchar, INT32 len);
	INT32 (*get_str_width) (LOGFONT* logfont, DEVFONT* devfont, 
							const UCHAR* mstr, INT32 n);
	INT32 (*get_ave_width) (LOGFONT* logfont, DEVFONT* devfont);
	INT32 (*get_max_width) (LOGFONT* logfont, DEVFONT* devfont);
	INT32 (*get_font_height) (LOGFONT* logfont, DEVFONT* devfont);
	INT32 (*get_font_size) (LOGFONT* logfont, DEVFONT* devfont, INT32 expect);
	INT32 (*get_font_ascent) (LOGFONT* logfont, DEVFONT* devfont);
	INT32 (*get_font_descent) (LOGFONT* logfont, DEVFONT* devfont);	
	INT32 (*char_bitmap_size) (LOGFONT* logfont, DEVFONT* devfont, 
							   const UCHAR* mchar, INT32 len);
	INT32 (*max_bitmap_size) (LOGFONT* logfont, DEVFONT* devfont);
	const VOID* (*get_char_bitmap) (LOGFONT* logfont, DEVFONT* devfont, 
									const UCHAR* mchar, INT32 len);
} FONTOPS;

struct _DEVFONT
{
	CHAR			 name [LEN_DEVFONT_NAME + 1];
	FONTOPS*		 font_ops;
	CHARSETOPS*	  charset_ops;
	VOID*			data;
};

#define SBC_DEVFONT_INFO(logfont) (logfont.sbc_devfont)
#define MBC_DEVFONT_INFO(logfont) (logfont.mbc_devfont)

#define SBC_DEVFONT_INFO_P(logfont) (logfont->sbc_devfont)
#define MBC_DEVFONT_INFO_P(logfont) (logfont->mbc_devfont)

#define INV_LOGFONT	 0

/**
 * \fn PLOGFONT GUIAPI CreateLogFont (const CHAR* type, const CHAR* family, const CHAR* charset, CHAR weight, CHAR slant, CHAR set_width, CHAR spacing, CHAR underline, CHAR struckout, INT32 size, INT32 rotation)
 * \brief Creates a logical font.
 *
 * This function creates a logical font. 
 *
 * \param type The type of the logical font, can be one of the values:
 *	  - FONT_TYPE_NAME_BITMAP_RAW\n
 *		Creates a logical font by using raw bitmap device font, i.e. mono-space bitmap font.
 *	  - FONT_TYPE_NAME_BITMAP_VAR\n
 *		Creates a logical font by using var-width bitmap device font.
 *	  - FONT_TYPE_NAME_SCALE_TTF\n
 *		Creates a logical font by using scalable TrueType device font.
 *	  - FONT_TYPE_NAME_SCALE_T1F\n
 *		Creates a logical font by using scalable Adobe Type1 device font.
 *	  - FONT_TYPE_NAME_ALL\n
 *		Creates a logical font by using any type device font.
 * \param family The family of the logical font, such as "Courier", "Helvetica", and so on.
 * \param charset The charset of the logical font. You can specify a sigle-byte charset
 *		like "ISO8859-1", or a multi-byte charset like "GB2312.1980-0".
 * \param weight The weight of the logical font, can be one of the values:
 *	  - FONT_WEIGHT_ALL\n
 *		Any one.
 *	  - FONT_WEIGHT_REGULAR\n
 *		Regular font.
 *	  - FONT_WEIGHT_BOLD\n
 *		Bold font.
 * \param slant The slant of the logical font, can be one of the values:
 *	  - FONT_SLANT_ALL\n
 *		Any one.
 *	  - FONT_SLANT_ROMAN\n
 *		Regular font.
 *	  - FONT_SLANT_ITALIC\n
 *		Italic font.
 * \param set_width Not used so far.
 * \param spacing Not used so far.
 * \param underline The underline of the logical font, can be one of the values:
 *	  - FONT_UNDERLINE_ALL\n
 *		Any one.
 *	  - FONT_UNDERLINE_LINE\n
 *		With underline.
 *	  - FONT_UNDERLINE_NONE\n
 *		Without underline.
 * \param struckout The struckout line of the logical font, can be one of the values:
 *	  - FONT_STRUCKOUT_ALL\n
 *		Any one.
 *	  - FONT_STRUCKOUT_LINE\n
 *		With struckout line.
 *	  - FONT_STRUCKOUT_NONE\n
 *		Without struckout line.
 * \param size The size, i.e. the height, of the logical font. Note that the size of 
 *		the logical font may be different from the size expected.
 * \param rotation The rotation of the logical font, it is in units of tenth degrees.
 *		Note that can specify rotation only for TrueType and Adobe Type1 fonts.
 * \return The pointer to the logical font created, NULL on error.
 *
 * \sa CreateLogFontIndirect, SelectFont
 *
 * Example:
 *
 * \include createlogfont.c
 *
 */
PLOGFONT GUIAPI CreateLogFont (const CHAR* type, const CHAR* family, 
							   const CHAR* charset, INT32 size);

/**
 * \fn PLOGFONT GUIAPI CreateLogFontIndirect (LOGFONT* logfont)
 * \brief Creates a logical font indirectly from a LOGFONT structure.
 *
 * \param logfont The pointer to the reference logical font structure.
 * \return The pointer to the logical font created, NULL on error.
 *
 * \sa CreateLogFont, SelectFont
 */
PLOGFONT GUIAPI CreateLogFontIndirect (LOGFONT* logfont);

/**
 * \fn VOID GUIAPI DestroyLogFont (PLOGFONT log_font)
 * \brief Destroies a logical font.
 *
 * This function destroies the specified logical font \a log_font.
 *
 * \param log_font The logical font what to destroy.
 *
 * \sa CreateLogFont, CreateLogFontIndirect
 */
VOID GUIAPI DestroyLogFont (PLOGFONT log_font);

/**
 * \fn VOID GUIAPI GetLogFontInfo (HDC hdc, LOGFONT* log_font)
 * \brief Gets logical font information of a DC.
 *
 * This function gets the logical font information of the specified DC \a hdc,
 * and copies to the LOGFONT structure pointed to by \a log_font.
 *
 * \param hdc The device context.
 * \param log_font The pointer to the LOGFONT structure to save the logical font info.
 *
 * \sa GetCurFont
 */
VOID GUIAPI GetLogFontInfo (HDC hdc, LOGFONT* log_font);

/**
 * \fn PLOGFONT GUIAPI GetCurFont (HDC hdc)
 * \brief Gets the pointer to the current logical font of a DC.
 *
 * This function returns the pointer to the current logical font selected to the DC \a hdc.
 *
 * \param hdc The device context.
 * \return The pointer to the current logical font.
 *
 * \sa GetLogFontInfo, SelectFont
 */
PLOGFONT GUIAPI GetCurFont (HDC hdc);

/**
 * \fn PLOGFONT GUIAPI SelectFont (HDC hdc, PLOGFONT log_font)
 * \brief Selects a logical font into a DC.
 *
 * This function selects the specified logical font \a log_font into the device context \a hdc.
 *
 * \param hdc The device context.
 * \param log_font The pointer to the logical font to be selected into the DC.
 * \return The old logical font of the DC.
 *
 * \sa GetCurFont
 *
 * Example:
 *
 * \include drawtext.c
 *
 */
PLOGFONT GUIAPI SelectFont (HDC hdc, PLOGFONT log_font);

	/** @} end of font_fns */

	/**
	 * \defgroup system_font System charset and font operations
	 *
	 * MiniGUI creates a few system fonts to draw menu text, window caption, or
	 * other general items. MiniGUI at least creates two system fonts: one mono-space
	 * logical font for single-byte charset, and one mono-space logical font for
	 * multi-byte charset. For the multi-byte charset, 
	 * the width of one multi-byte character should be equal to the width of 
	 * two single-byte characters.
	 *
	 * @{
	 */

#define SYSLOGFONT_DEFAULT		  0  // 8x8(ASCII)
#define SYSLOGFONT_WCHAR_DEF		1  // 12x12(HZK), 8x12(ASCII)
#define SYSLOGFONT_MINI			 2  // 5x7(ASCII)
#define SYSLOGFONT_MICRO_PARAM	  3  // 16x20 (ASCII)
#define SYSLOGFONT_SMALL_PARAM	  4  // 24x32 (ASCII)
#define SYSLOGFONT_MID_PARAM		5  // 32x48 (ASCII)
#define SYSLOGFONT_BIG_PARAM		6  // 40x60 (ASCII)
#define SYSLOGFONT_FIXED			7  // 16x16(HZK), 8x16(ASCII)
#define SYSLOGFONT_DEF_ASC		  8  // default english , 8x12. ASCII.
#define SYSLOGFONT_NOR_ASC		  9  // rormal  english , 8x16. ASCII.
#define SYSLOGFONT_HUGE_PARAM	   10 // 80x120

#if _ENB_RUS8X12_FONT
#define SYSLOGFONT_DEF_RUS		  11 // small, 8x12 Russian
#endif

#if _ENB_RUS8X16_FONT
#define SYSLOGFONT_NOR_RUS		  12 // normal, 8x16 Russian
#endif

#if 0								  //Change by Latrom_06-27-2011
#define SYSLOGFONT_SMAFONT		  SYSLOGFONT_WCHAR_DEF  // 控件默认字体
#define SYSLOGFONT_BIGFONT		  SYSLOGFONT_FIXED	  // 大号字体
#endif
#if _ENB_PRT16X18_FONT > 0 // Add for 16X18
#define SYSLOGFONT_PRINT_FONT	   13  // 16 x 18 (ASCII)
#define SYSLOGFONT_REC_FONT		 14  //16x18(HZK), 16x18(ASCII)
#endif
#if _ENB_YAHEI17_FONT > 0 // Add by gjl
#define SYSLOGFONT_YAHEI17_FONT	 15  // 24X30
#endif

#if _ENB_YAHEI17_FONT > 0
#define NR_SYSLOGFONTS			   (SYSLOGFONT_YAHEI17_FONT + 1)
#else
#define NR_SYSLOGFONTS			   15
#endif

extern PLOGFONT g_SysLogFont [];

/**
 * \fn PLOGFONT GUIAPI GetSystemFont (INT32 font_id)
 * \brief Gets the system logical font through an font identifier.
 *
 * This function returns the system logical font through the font identifier \a font_id.
 *
 * \param font_id The identifier of a system font, can be one of the following values:
 *	  - SYSLOGFONT_DEFAULT\n
 *		The default system logical font in single-byte charset, must be rbf.
 *	  - SYSLOGFONT_WCHAR_DEF\n
 *		The default system logical font in multi-byte charset, must be rbf.
 *	  - SYSLOGFONT_FIXED\n
 *		The fixed space system logical font.
 *	  - SYSLOGFONT_CAPTION\n
 *		The system logical font used to draw caption text.
 *	  - SYSLOGFONT_MENU\n
 *		The system logical font used to draw menu items.
 *	  - SYSLOGFONT_CONTROL\n
 *		The system logical font used to draw controls.
 * \return The pointer to the system logical font. NULL on error.
 */
PLOGFONT GUIAPI GetSystemFont (INT32 font_id);

/**
 * \fn const CHAR* GUIAPI GetSysCharset (BOOL wchar)
 * \brief Gets the current system charset.
 *
 * This function gets the current system charset and returns the charset name.
 * By default, the system charset is ISO8859-1 (for single-byte charset) or 
 * GB2312.1980-0 (for wide charset), but you can change it by modifying \a MiniGUI.cfg. 
 *
 * \param wchar Whether to retrive the wide charset supported currently.
 * \return The read-only buffer of charset name. If you pass \a wchar TRUE,
 *		 This function may return NULL, if there is not any wide charset supported.
 */
const CHAR* GUIAPI GetSysCharset (BOOL wchar);

/**
 * \fn INT32 GUIAPI GetSysCharHeight (VOID)
 * \brief Gets the height of a character of the default system font.
 *
 * This function returns the height of a character of 
 * the system default font. MiniGUI uses mono-space font as the default system font.
 *
 * Normally, the width of one multi-byte character is equal to 
 * the width of two single-byte character when using the default system font.
 *
 * \return The character height of the default system font.
 *
 * \sa GetSysCharWidth, GetSysCCharWidth
 */
INT32 GUIAPI GetSysCharHeight (VOID);

/**
 * \fn INT32 GUIAPI GetSysCharWidth (VOID)
 * \brief Gets the width of a single-byte character of the default system font.
 *
 * This function returns the width of a single-byte character of the default system font.
 * MiniGUI uses mono-space font as the default system font, but you can specify a 
 * different font to output text in windows of MiniGUI.
 *
 * \return The width of single-byte character of the default system font.
 *
 * \sa GetSysCharHeight, GetSysCCharWidth, SelectFont, CreateLogFont
 */
INT32 GUIAPI GetSysCharWidth (VOID);

/**
 * \fn INT32 GUIAPI GetSysCCharWidth (VOID)
 * \brief Gets the width of a multi-byte character of the default system font.
 *
 * This function returns the width of a multi-byte character of 
 * the default system font. MiniGUI uses mono-space font as the system default font.
 *
 * \return The width of multi-byte character of the default system font.
 *
 * \sa GetSysCharHeight, GetSysCharWidth
 */
INT32 GUIAPI GetSysCCharWidth (VOID);

	/** @} end of system_font */

	/**
	 * \defgroup text_parse_fns Text parsing functions
	 *
	 * MiniGUI uses logical font to output text, also uses
	 * logical font to parsing the multi-byte characters and
	 * words in the text.
	 *
	 * @{
	 */

/** Word information structure */
struct _WORDINFO
{
	/** the length of the word. */
	INT32 len;
	/** the delimiter after the word. */
	UCHAR delimiter;
	/** the number of delimiters after the word. */
	INT32 nr_delimiters;
};

/**
 * \fn INT32 GUIAPI GetTextMCharInfo (PLOGFONT log_font, const CHAR* mstr, INT32 len, INT32* pos_chars)
 * \brief Retrives positions of multi-byte characters in a string.
 *
 * This function retrives position of multi-byte characters in 
 * the string \a mstr which is \len bytes long. It returns the positions 
 * of characters in the string in an integer array pointed to by \a pos_chars.
 *
 * \param log_font The logical font used to parse the multi-byte string.
 * \param mstr The multi-byte string.
 * \param len The length of the string.
 * \param pos_chars The position of characters will be returned through this array if it is not NULL.
 * \return The number of characters in the multi-byte string.
 *
 * \sa GetTextWordInfo
 */
INT32 GUIAPI GetTextMCharInfo (PLOGFONT log_font, const CHAR* mstr, INT32 len, 
				INT32* pos_chars);

/**
 * \fn INT32 GUIAPI GetTextWordInfo (PLOGFONT log_font, const CHAR* mstr, INT32 len, INT32* pos_words, WORDINFO* info_words)
 * \brief Retrives information of multi-byte words in a string.
 *
 * This function retrives information of multi-byte words in the string \a mstr which is 
 * \a len bytes long. It returns the positions of words in the string in an integer 
 * array pointed to by \a pos_words if the pointer is not NULL. This function also 
 * returns the information of words in a WORDINFO struct array pointed to by \a info_words 
 * when the pointer is not NULL.
 *
 * \param log_font The logical font used to parse the multi-byte string.
 * \param mstr The multi-byte string.
 * \param len The length of the string.
 * \param pos_words The position of words will be returned through this array if it is not NULL.
 * \param word_info The words' information will be returned through this array if it is not NULL.
 * \return The number of words in the multi-byte string.
 *
 * \sa GetTextMCharInfo, WORDINFO
 */
INT32 GUIAPI GetTextWordInfo (PLOGFONT log_font, const CHAR* mstr, INT32 len, 
				INT32* pos_words, WORDINFO* info_words);

/**
 * \fn INT32 GUIAPI GetFirstMCharLen (PLOGFONT log_font, const CHAR* mstr, INT32 len)
 * \brief Retrives the length of the first multi-byte character in a string.
 *
 * This function retrives and returns the length of the first multi-byte 
 * character in the string \a mstr which is \a len bytes long.
 *
 * \param log_font The logical font used to parse the multi-byte string.
 * \param mstr The multi-byte string.
 * \param len The length of the string.
 * \return The length of the first multi-byte character.
 *
 * \sa GetFirstWord
 */
INT32 GUIAPI GetFirstMCharLen (PLOGFONT log_font, const CHAR* mstr, INT32 len);

/**
 * \fn INT32 GUIAPI GetFirstWord (PLOGFONT log_font, const CHAR* mstr, INT32 len, WORDINFO* word_info)
 * \brief Retrives the length and info of the first multi-byte word in a string.
 *
 * This function retrives the information of the first multi-byte character in the string \a mstr
 * which is \a len bytes long, and returns it through \a word_info. 
 * It also returns the full length of the word including the delimiters after the word.
 *
 * \param log_font The logical font used to parse the multi-byte string.
 * \param mstr The multi-byte string.
 * \param len The length of the string.
 * \param word_info The pointer to a WORDINFO structure used to return the word information.
 * \return The length of the first multi-byte word.
 *
 * \sa GetFirstMCharLen, WORDINFO
 */
INT32 GUIAPI GetFirstWord (PLOGFONT log_font, const CHAR* mstr, INT32 len,
							WORDINFO* word_info);

/**
 * \fn INT32 GUIAPI GetTextExtentPoint (HDC hdc, const CHAR* text, INT32 len, INT32 max_extent, INT32* fit_chars, INT32* pos_chars, INT32* dx_chars, SIZE* size)
 * \brief Computes the extent of a string when output the string in a limited space.
 *
 * This function computes the extent of the specified string of text \a text which is 
 * \a len bytes long when output the text in a limited space (\a max_extent wide). 
 * If \a pos_chars and \a dx_chars are not NULL, this function will return the 
 * positions of each character in the text, and the output position of each character.
 * This function returns the text extent in a SIZE struct pointed to by \a size, and 
 * the width of text as return value.
 * 
 * \param hdc The device context.
 * \param text The multi-byte string.
 * \param len The length of the string.
 * \param max_extent The width of the limited space.
 * \param fit_chars The number of the characters actually outputed.
 * \param pos_chars The positions of each character in the text will be returned through this pointer.
 * \param dx_chars The output positions of each character in the text will be returned through this pointer.
 * \param size The output extent of the text in the limited space will be returned through this pointer.
 * \return The actual output width of the text in the limited space.
 *
 * \sa GetFirstMCharLen, GetFirstWord
 */
INT32 GUIAPI GetTextExtentPoint (HDC hdc, const CHAR* text, INT32 len, INT32 max_extent, 
				INT32* fit_chars, INT32* pos_chars, INT32* dx_chars, SIZE* size);

	/** @} end of text_parse_fns */

	/**
	 * \defgroup text_output_fns Text output functions
	 * @{
	 */

/**
 * \fn INT32 GUIAPI GetFontHeight (HDC hdc)
 * \brief Retrives the height of the current logical font in a DC.
 *
 * This function retrives the height of the current logical font in the DC \a hdc.
 *
 * \param hdc The device context.
 * \return The height of the current logical font.
 *
 * \sa GetMaxFontWidth
 */
INT32 GUIAPI GetFontHeight (HDC hdc);

/**
 * \fn INT32 GUIAPI GetMaxFontWidth (HDC hdc)
 * \brief Retrives the maximal character width of the current logical font in a DC.
 *
 * This function retrives the maximal character width of the current logical font 
 * in the DC \a hdc.
 *
 * \param hdc The device context.
 * \return The maximal character width of the current logical font.
 *
 * \sa GetFontHeight
 */
INT32 GUIAPI GetMaxFontWidth (HDC hdc);

/**
 * \fn VOID GUIAPI GetTextExtent (HDC hdc, const CHAR* spText, INT32 len, SIZE* pSize)
 * \brief Computes the output extent of a string of text.
 *
 * This function computes the output extent of the text (\a spText) with length of \a len. 
 * This function returns the extent in a SIZE struct pointed to by \a pSize and the width 
 * of text as the return value.
 *
 * \param hdc The device context.
 * \param spText The pointer to the string of text.
 * \param len The length of the text.
 * \param pSize The output extent will be returned through this buffer.
 *
 * \sa GetTabbedTextExtent
 */
VOID GUIAPI GetTextExtent (HDC hdc, const CHAR* spText, INT32 len, SIZE* pSize);
VOID GUIAPI GetTextExtentEx (PLOGFONT pLogfont, const CHAR* spText, INT32 len, SIZE *pSize);
INT16 GUIAPI GetTextOutLenExtent (HDC hdc, INT16 width, const CHAR* text);
char *GetTextInLen(PLOGFONT pFont, int width, char *text);

/**
 * \fn VOID GUIAPI GetTabbedTextExtent (HDC hdc, const CHAR* spText, INT32 len, SIZE* pSize)
 * \brief Computes the output extent of a formatted text.
 *
 * This function computes the output extent of the formatted text (\a spText) with length of \a len.
 * This function returns the extent in a SIZE struct pointed to by \a pSize and the width of text as 
 * the return value. The output extent will be affected by the default tab size if there are some 
 * TAB characters in the text.
 *
 * \param hdc The device context.
 * \param spText The pointer to the string of text.
 * \param len The length of the text.
 * \param pSize The output extent will be returned through this buffer.
 *
 * \sa GetTextExtent
 */
VOID GUIAPI GetTabbedTextExtent (HDC hdc, const CHAR* spText, INT32 len, SIZE* pSize);

/**
 * \fn GetTextCharacterExtra(hdc)
 * \brief Retrives the current intercharacter spacing for the DC.
 * 
 * \note Defined as a macro calling \a GetDCAttr for _USE_NEWGAL.
 *	   If _USE_NEWGAL is not defined, \a GetTextCharacterExtra is defined as
 *	   a function, and have the same semantics as this macro.
 *
 * \sa SetTextCharacterExtra
 */
INT32 GUIAPI GetTextCharacterExtra (HDC hdc);

/**
 * \fn GetTextAboveLineExtra(hdc)
 * \brief Retrives the current spacing above line for the DC.
 *
 * \note Defined as a macro calling \a GetDCAttr for _USE_NEWGAL.
 *	   If _USE_NEWGAL is not defined, \a GetTextAboveLineExtra is defined as
 *	   a function, and have the same semantics as this macro.
 *
 * \sa SetTextAboveLineExtra
 */
INT32 GUIAPI GetTextAboveLineExtra (HDC hdc);

/**
 * \fn GetTextBellowLineExtra(hdc)
 * \brief Retrives the current spacing bellow line for the DC.
 *
 * \note Defined as a macro calling \a GetDCAttr for _USE_NEWGAL.
 *	   If _USE_NEWGAL is not defined, \a GetTextBellowLineExtra is defined as
 *	   a function, and have the same semantics as this macro.
 *
 * \sa SetTextBellowLineExtra
 */
INT32 GUIAPI GetTextBellowLineExtra (HDC hdc);

/**
 * \fn SetTextCharacterExtra(hdc, extra)
 * \brief Sets the intercharacter spacing for the DC and returns the old spacing value.
 * 
 * \note Defined as a macro calling \a SetDCAttr for _USE_NEWGAL.
 *	   If _USE_NEWGAL is not defined, \a SetTextCharacterExtra is defined as
 *	   a function, and have the same semantics as this macro.
 *
 * \sa GetTextCharacterExtra
 */
INT32 GUIAPI SetTextCharacterExtra (HDC hdc, INT32 extra);

/**
 * \fn SetTextAboveLineExtra(hdc, extra)
 * \brief Sets the spacing above line for the DC and returns the old value.
 *
 * \note Defined as a macro calling \a SetDCAttr for _USE_NEWGAL.
 *	   If _USE_NEWGAL is not defined, \a SetTextAboveLineExtra is defined as
 *	   a function, and have the same semantics as this macro.
 *
 * \sa GetTextAboveLineExtra
 */
INT32 GUIAPI SetTextAboveLineExtra (HDC hdc, INT32 extra);

/**
 * \fn SetTextBellowLineExtra(hdc, extra)
 * \brief Sets the spacing bellow line for the DC and returns the old value.
 *
 * \note Defined as a macro calling \a SetDCAttr for _USE_NEWGAL.
 *	   If _USE_NEWGAL is not defined, \a SetTextBellowLineExtra is defined as
 *	   a function, and have the same semantics as this macro.
 *
 * \sa GetTextBellowLineExtra
 */
INT32 GUIAPI SetTextBellowLineExtra (HDC hdc, INT32 extra);

/**
 * \fn INT32 GUIAPI TextOutLen (HDC hdc, INT32 x, INT32 y, const CHAR* text, INT32 len)
 * \brief Outputs a string of text.
 *
 * This function outputs the text \a text with length of \a len at a (x,y). 
 * This function returns the width of text.
 *
 * \param hdc The device context.
 * \param x,y The output position.
 * \param text The string of the text.
 * \param len The length of the text. If it is less than 0, MiniGUI will treat it as 
 *		a null-terminated string.
 * \return The output width of the text.
 *
 * \sa TabbedTextOutLen
 */
INT32 GUIAPI TextOutLen (HDC hdc, INT32 x, INT32 y, const CHAR* text, INT32 len);

/**
 * \fn INT32 GUIAPI TabbedTextOutLen (HDC hdc, INT32 x, INT32 y, const CHAR* spText, INT32 len)
 * \brief Outputs a formatted text.
 *
 * This function outputs the formatted text \a spText with length of \a len at \a (x,y).
 * This function returns the width of text. The output will be affected by 
 * the default tab size if there are some TAB characters in the text.
 *
 * \param hdc The device context.
 * \param x,y The output position.
 * \param spText The formatted text.
 * \param len The length of the text. If it is less than 0, MiniGUI will treat it as 
 *		a null-terminated string.
 * \return The output width of the text.
 *
 * \sa TextOutLen
 */
INT32 GUIAPI TabbedTextOutLen (HDC hdc, INT32 x, INT32 y, const CHAR* spText, INT32 len); 

/**
 * \fn INT32 GUIAPI TabbedTextOutEx (HDC hdc, INT32 x, INT32 y, const CHAR* spText, INT32 nCount, INT32 nTabPositions, INT32 *pTabPositions, INT32 nTabOrigin)
 * \brief Writes a character string at a specified location, expanding tabs to the values
 *		specified in an anrry of tab-stop positions.
 *
 * This function writes the string \a spText with length of \a nCount at a specified locations, 
 * expanding tabs to the value spcified in the array \a pTabPositions of tab-stop positions.
 *
 * \param hdc The device context.
 * \param x,y The output position.
 * \param spText The formatted text.
 * \param nCount The length of the text. If it is less than 0, MiniGUI will treat it as 
 *		a null-terminated string.
 * \param nTabPositions The length of the array of the tab-stop positions.
 * \param nTabOrigin The origin of the tab-stops.
 * \return The output width of the text.
 *
 * \sa TabbedTextOutLen
 */
INT32 GUIAPI TabbedTextOutEx (HDC hdc, INT32 x, INT32 y, const CHAR* spText, INT32 nCount,
			INT32 nTabPositions, INT32 *pTabPositions, INT32 nTabOrigin);

/**
 * \fn VOID GUIAPI GetLastTextOutPos (HDC hdc, POINT* pt)
 * \brief Retrives the last text output position.
 *
 * \param hdc The device context.
 * \param pt The last text output position will be returned through this pointer.
 *
 */
VOID GUIAPI GetLastTextOutPos (HDC hdc, POINT* pt);

/**
 * \def TextOut(hdc, x, y, text)
 * \brief Outputs text.
 *
 * Defined as a macro calling \a TextOutLen passing \a len as -1.
 *
 * \sa TextOutLen
 */
#define TextOut(hdc, x, y, text)	TextOutLen (hdc, x, y, text, -1)
#define TextOutEx(hdc, x, y, text, mode) TextOutLenEx(hdc, x, y, text, -1, mode)

extern INT32 GUIAPI ScreenTextOut (HDC hdc, INT32 x, INT32 y, const CHAR* text, INT32 len);
/**
 * \def TabbedTextOut(hdc, x, y, text)
 * \brief Outputs formatted text.
 *
 * Defined as a macro calling \a TabbedTextOutLen passing \a len as -1.
 *
 * \sa TextOutLen
 */
#define TabbedTextOut(hdc, x, y, text)  TabbedTextOutLen (hdc, x, y, text, -1)

#define DT_TOP			  0x00000000
#define DT_LEFT			 0x00000000
#define DT_CENTER		   0x00000001
#define DT_RIGHT			0x00000002
#define DT_VCENTER		  0x00000004
#define DT_BOTTOM		   0x00000008
#define DT_WORDBREAK		0x00000010
#define DT_SINGLELINE	   0x00000020
#define DT_EXPANDTABS	   0x00000040
#define DT_TABSTOP		  0x00000080
#define DT_NOCLIP		   0x00000100
#define DT_EXTERNALLPADING  0x00000200
#define DT_CALCRECT		 0x00000400
#define DT_NOPREFIX		 0x00000800
#define DT_INTERNAL		 0x00001000

/**
 * \fn INT32 GUIAPI DrawTextEx (HDC hdc, const CHAR* pText, INT32 nCount, RECT* pRect, INT32 nIndent, UINT nFormat)
 * \brief Draws a formatted text in a rectangle.
 *
 * This function draws formatted text (\a pText) in the specified rectangle (\a pRect).
 * It formats the text according to the specified method (through \a nFormat, 
 * including expanding tabs, justifying characters, breaking lines, and so forth). 
 *
 * \param hdc The device context.
 * \param pText The formatted text.
 * \param nCount The length of the text. If it is less than 0, MiniGUI will treat it as 
 *		a null-terminated string.
 * \param pRect The output rectangle.
 * \param nIndent The indent value of the first line.
 * \param nFormat The methods used to format the text. MiniGUI support 
 *		the following method to format text so far:
 *
 *  - DT_TOP\n
 *	Top-justifies text (single line only).
 *  - DT_LEFT\n
 *	Aligns text to the left.
 *  - DT_CENTER\n
 *	Centers text horizontally in the rectangle.
 *  - DT_RIGHT\n
 *	Aligns text to the right.
 *  - DT_VCENTER\n
 *	Centers text vertically (single line only).
 *  - DT_BOTTOM\n
 *	Justify the text to the bottom of the rectangle. This value must be combined with DT_SINGLELINE.
 *  - DT_WORDBREAK\n
 *	Break words. Lines are automatically broken beteween words if a word would extend past 
 *	the edge of the rectangle specified by the the pRect parameter. 
 *	A carriage return or linefeed also breaks the line.
 *  - DT_SINGLELINE\n
 *	Display text ont the single line only. Carriage returns and linefeeds do not break the line.
 *  - DT_EXPANDTABS\n
 *	Expands tab characters. The default number of character per tab is eight.
 *  - DT_TABSTOP\n
 *	Set tab stops. Bits 15-8 (hight-order byte of the low-order word) of the \a uForma parameter specify 
 *	the number of characters for each tab. The default number of characters per tab is eight.
 *  - DT_NOCLIP\n
 *	Draws without clipping. \a DrawText is somewhat faster when DT_NOCLIP is used.
 *  - DT_CALCRECT\n
 *	Determines the width and the height of the rectangle. If there are multiple lines of text,  
 *	\a DrawText uses the width of the rectangle pointed to by the \a lpRect parameter and extends 
 *	the base of the rectangle to bound the last line of text. If there is only one line of text, 
 *	\a DrawText modifies the right side of the rectangle so that it bounds 
 *	the last character in the line. In either case, \a DrawText returns the height of 
 *	the formatted text but does not draw the text.
 *
 * \return The output height of the formatted text.
 *
 * \sa DrawText
 *
 * Example:
 *
 * \include drawtext.c
 */
INT32 GUIAPI DrawTextEx (HDC hdc, const CHAR* pText, INT32 nCount, 
					   RECT* pRect, INT32 nIndent, UINT nFormat);

/**
 * \def DrawText(hdc, text, n, rc, format)
 * \brief Draws a formatted text in a rectangle.
 *
 * Defined as a macro calling \a DrawTextEx passing \a nIndent as 0.
 *
 * \sa DrawTextEx
 */
#define DrawText(hdc, text, n, rc, format)	  DrawTextEx (hdc, text, n, rc, 0, format)

	/** @} end of text_output_fns */

#define BMP_TYPE_NORMAL		 0x00
#define BMP_TYPE_RLE			0x01
#define BMP_TYPE_ALPHA		  0x02
#define BMP_TYPE_ALPHACHANNEL   0x04
#define BMP_TYPE_COLORKEY	   0x10
#define BMP_TYPE_PRIV_PIXEL	 0x20

	/**
	 * Bitmap types, can be OR'ed by the following values:
	 *  - BMP_TYPE_NORMAL\n
	 *	A nomal bitmap, without alpha and color key.
	 *  - BMP_TYPE_RLE\n
	 *	A RLE encoded bitmap, not used so far.
	 *  - BMP_TYPE_ALPHA\n
	 *	Per-pixel alpha in the bitmap.
	 *  - BMP_TYPE_ALPHACHANNEL\n
	 *	The \a bmAlpha is a valid alpha channel value.
	 *  - BMP_TYPE_COLORKEY\n
	 *	The \a bmColorKey is a valid color key value.
	 *  - BMP_TYPE_PRIV_PIXEL\n
	 *	The bitmap have a private pixel format.
	 */
typedef struct _tag_bitmap {
	UCHAR   type;			 /* bitmap type			 */
	UCHAR   bitsPixel;		/* bits per pixel		  */
	INT16   width;			/* pixels of width		 */
	INT16   height;		   /* pixels of height		*/
	INT16   bytesWidth;	   /* bytes of width		  */
	VOID  * bits;			 /* address of bitmap data  */
} BITMAP;

typedef BITMAP* PBITMAP;


/**
 * \fn void GUIAPI DrawHVDotLine (HDC hdc, int x, int y, int w_h, BOOL H_V)
 * \brief Draws a horizontal or vertical dot line.
 *
 * This function draws a horizontal or vertical dot line.
 *
 * \param hdc The device context.
 * \param x,y The start point of the line.
 * \param w_h The width of the line or horizontal dot line, or the height
 *			if you want to draw a vertical dot line.
 * \param H_V Specify whether you want to draw a horizontal or vertical line.
 *			TRUE for horizontal, FALSE for vertical.
 *
 * \sa FocusRect
 */
void GUIAPI DrawHVDotLine (HDC hdc, long x, long y, int w_h, BOOL H_V);

/**
 * \def DrawHDotLine(hdc, x, y, w)
 * \brief Draws a horizontal dot line.
 *
 * \param hdc The device context.
 * \param x,y The start point of the line.
 * \param w The width of the horizontal dot line.
 *
 * \note Defined as a macro calling DrawHVDotLine.
 *
 * \sa DrawVDotLine, DrawHVDotLine
 */
#define DrawHDotLine(hdc, x, y, w) DrawHVDotLine (hdc, x, y, w, TRUE);

/**
 * \def DrawVDotLine(hdc, x, y, h)
 * \brief Draws a vertical dot line.
 *
 * \param hdc The device context.
 * \param x,y The start point of the line.
 * \param h The height of the horizontal dot line.
 *
 * \note Defined as a macro calling DrawHVDotLine.
 *
 * \sa DrawHDotLine, DrawHVDotLine
 */
#define DrawVDotLine(hdc, x, y, h) DrawHVDotLine (hdc, x, y, h, FALSE);


#define  ClearScreen(c)  SetBrushColor(HDC_SCREEN, c); \
						 FillRect(HDC_SCREEN, g_rcScr.left,g_rcScr.top, RECTW(g_rcScr),RECTH(g_rcScr))

GAL_PIXEL GUIAPI SetTextBkColor (HDC hdc, GAL_PIXEL color);
GAL_PIXEL GUIAPI GetTextBkColor(HDC hdc);

VOID GUIAPI GetBox (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h, VOID * bufP);
VOID GUIAPI PutBox (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h, VOID * imgP);
VOID GUIAPI FillRect (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h);
VOID GUIAPI PutImage (HDC hdc, INT32 x, INT32 y, PBITMAP imgP);
VOID GUIAPI GetImage (HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h, PBITMAP imgP);

extern UINT8 const  DCB2HEX_TAB[];

VOID   DrawBitmap( HDC hdc, INT32 x,INT32 y, INT bmp_id );

int  Put24BmpFile(HDC hdc, long x, long y, int mode, char *fpath);
int  Put256PcxFile (HDC hdc, int x, int y, int mode, const char *name);


#define myprintf()   printf("File :%s  Function :%s  Line :%d\r\n",__FILE__,__FUNCTION__,__LINE__); //add by empty for debug 2011/01/19

#endif
