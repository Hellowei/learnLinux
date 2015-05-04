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
#if !defined(_GUI_H)
#define	  _GUI_H

	/**
	 * \defgroup rect_vars Rectangles
	 * @{
	 */

/**
 * \var RECT g_rcScr
 * \brief Contains the rectangle of the whole screen.
 */
extern RECT g_rcScr;		 /* The RECT of screen. */

/**
 * \defgroup ini_fns Configuration file operations
 *
 * The configuration file used by GUI have a similiar format as M$ Windows INI file,
 * i.e. the file consists of sections, and the section consists of key-value pairs, like this:
 *
 * \code
 * [system]
 * # GAL engine
 * gal_engine=fbcon
 *
 * # IAL engine
 * ial_engine=console
 *
 * mdev=/dev/mouse
 * mtype=PS2
 * 
 * [fbcon]
 * defaultmode=1024x768-16bpp
 * 
 * [qvfb]
 * defaultmode=640x480-16bpp
 * display=0
 * \endcode
 *
 * Assume that the configuration file named \a my.cfg, if you want get the value of \a mdev
 * in \a system section, you can call \a GetValueFromIniFile in the following way:
 *
 * \code
 * char buffer [51];
 *
 * GetValueFromIniFile ("my.ini", "system", "mdev", buffer, 51);
 * \endcode
 *
 * Example:
 *
 * \include cfgfile.c
 *
 * @{
 */

#define INI_MAXLINE			 256 //1024
#define INI_FILENOTFOUND		-1
#define INI_SECTIONNOTFOUND	 -2
#define INI_KEYNOTFOUND		 -3
#define INI_TMPFILEFAILED	   -4
#define INI_FILEIOFAILED		-5
#define INI_INTCONV			 -6
#define INI_OK				  0


/**
 * \var char* INIFILEPATH
 * \brief The path name of GUI configuration file.
 *
 * By default, the configuration file of GUI must be installed ,
 * the name should be "monitor.ini".
 *
 *
 * If GUI can not find any \a .ini file, or find a bad formated configure
 * file, the initialzation of GUI will be canceled.
 */
extern char INIFILEPATH [];

/**
 * \fn INT32 GUIAPI GetValueFromIniFile (const char* pIniFile, const char* pSection, const char* pKey, char* pValue, long iLen)
 * \brief Gets value from a configuration file.
 *
 * This function gets the value of the key \a pKey in the section \a pSection 
 * of the configuration file \a pIniFile, and saves the value to the buffer
 * pointed to by \a pValue. 
 *
 * \param pIniFile The path name of the configuration file.
 * \param pSection The section name in which the value located.
 * \param pKey The key name of the value.
 * \param pValue The value will be saved in this buffer.
 * \param iLen The length in bytes of the buffer.
 * \return INI_OK on success, < 0 on error.
 *
 * \retval INI_OK			   Gets value successfullly.
 * \retval INI_FILENOTFOUND	 Can not find the specified configuration file.
 * \retval INI_SECTIONNOTFOUND  Can not find the specified section in the configuration file.
 * \retval INI_KEYNOTFOUND	  Can not find the specified key in the section.
 * \retval INI_FILEIOFAILED	 File I/O operation error occurred.
 *
 * \note GUI use \a strncpy to copy actual value to \a pValue. Thus, if the length of 
 * the actual value is larger than \a iLen, the result copied to \a pValue 
 * will \em NOT be null-terminated.
 *
 * \sa GetIntValueFromIniFile, SetValueToIniFile, strncpy(3)
 */
INT32 GUIAPI GetValueFromIniFile (const char* pIniFile, const char* pSection,
								  const char* pKey, char* pValue, long iLen);

/**
 * \fn INT32 GUIAPI GetIntValueFromIniFile (const char* pIniFile, const char* pSection, const char* pKey, INT32* value)
 * \brief Gets integer value from a configuration file.
 *
 * This function gets the integer value of the key \a pKey in the section \a pSection 
 * of the configuration file \a pIniFile, and returns the integer value through the buffer
 * pointed to by \a value. 
 *
 * \param pIniFile The path name of the configuration file.
 * \param pSection The section name in which the value located.
 * \param pKey The key name of the value.
 * \param value The integer value will be saved in this buffer.
 * \return INI_OK on success, < 0 on error.
 *
 * \retval INI_OK			   Gets value successfullly.
 * \retval INI_FILENOTFOUND	 Can not find the specified configuration file.
 * \retval INI_SECTIONNOTFOUND  Can not find the specified section in the configuration file.
 * \retval INI_KEYNOTFOUND	  Can not find the specified key in the section.
 * \retval INI_FILEIOFAILED	 File I/O operation error occurred.
 * \retval INI_INTCONV		  Can not convert the value string to an integer.
 *
 * \note GUI uses \a strtol to convert the string value to an integer, and pass the base as 0.
 * Thus, the valid string value can be converted to integer should be in the following forms:
 *
 *  - [+|-]0x[0-9|A-F]*\n
 *	Will be read in base 16.
 *  - [+|-]0[0-7]*\n
 *	Will be read in base 8.
 *  - [+|-][1-9][0-9]*\n
 *	Will be read in base 10.
 *
 * \sa GetValueFromIniFile, SetValueToIniFile, strtol(3)
 */
INT32 GUIAPI GetIntValueFromIniFile (const char* pIniFile, const char* pSection,
									 const char* pKey, long* value);

/**
 * \fn INT32 GUIAPI SetValueToIniFile (const char* pIniFile, const char* pSection, const char* pKey, char* pValue)
 * \brief Sets a value in a configuration file.
 *
 * This function stes the value of the key \a pKey in the section \a pSection
 * of the configuration file \a pIniFile to be the string pointed to by \a pValue.
 *
 * \param pIniFile The path name of the configuration file.
 * \param pSection The section name in which the value located.
 * \param pKey The key name of the value.
 * \param value The null-terminated value string.
 * \return INI_OK on success, < 0 on error.
 *
 * \retval INI_OK			   Sets value successfullly.
 * \retval INI_FILEIOFAILED	 File I/O operation error occurred.
 * \retval INI_TMPFILEFAILED	Can not create temporary file.
 *
 * \note If the specified configuration file does not exist, GUI will try to
 * create this file.
 *
 * \sa GetValueFromIniFile, GetIntValueFromIniFile
 */
INT32 GUIAPI SetValueToIniFile (const char* pIniFile, const char* pSection,
							   const char* pKey, char* pValue);

	/** @} end of ini_fns */

	/**
	 * \addtogroup misc_fns Miscellaneous functions
	 * @{
	 */

/**
 * \fn void GUIAPI Ping (void)
 * \brief Makes a beep sound.
 * \sa Beep
 */
void GUIAPI Ping (void);

/**
 * \def Beep
 * \brief Alias of Ping.
 * \sa Ping
 */
#define Beep Ping

/**
 * \fn void GUIAPI Tone (INT32 frequency_hz, INT32 duration_ms)
 * \brief Makes a tone.
 *
 * This function will return after the tone. Thus, your program
 * will be blocked when the tone is being played.
 *
 * \param frequency_hz The frequency of the tone in hertz.
 * \param duration_ms The duration of the tone in millisecond.
 *
 * \bug When GUI runs on X Window, the tone can not be played correctly.
 *
 * \sa Ping
 */
void GUIAPI Tone (INT32 frequency_hz, INT32 duration_ms);

/**
 * \fn void GUIAPI Draw3DUpFrame (HDC hDC, INT32 l, INT32 t, INT32 r, INT32 b, GAL_PIXEL fillc)
 * \brief Draws a thick 3D up frame.
 *
 * This function draws a thick 3D up frame (the border is 2-pixel wide), 
 * and fills the frame if a valid filling pixel is specified.
 *
 * \param hDC The device context.
 * \param l The x-coordinate of upper-left corner of the frame.
 * \param t The y-coordinate of upper-left corner of the frame.
 * \param r The x-coordinate of lower-right corner of the frame.
 * \param b The y-coordinate of lower-right corner of the frame.
 * \param fillc The filling color.
 *
 * \note If \a fillc is zero, this function will not fill the frame.
 *
 * \sa Draw3DDownFrame, Draw3DUpThinFrame
 */
void GUIAPI Draw3DUpFrame (HDC hDC, INT32 l, INT32 t, INT32 r, INT32 b, GAL_PIXEL fillc);

/**
 * \fn void GUIAPI Draw3DDownFrame (HDC hDC, INT32 l, INT32 t, INT32 r, INT32 b, GAL_PIXEL fillc)
 * \brief Draws a thick 3D down frame.
 *
 * This function draws a thick 3D down frame (the border is 2-pixel wide), 
 * and fills the frame if a valid filling pixel is specified.
 *
 * \param hDC The device context.
 * \param l The x-coordinate of upper-left corner of the frame.
 * \param t The y-coordinate of upper-left corner of the frame.
 * \param r The x-coordinate of lower-right corner of the frame.
 * \param b The y-coordinate of lower-right corner of the frame.
 * \param fillc The filling color.
 *
 * \note If \a fillc is zero, this function will not fill the frame.
 *
 * \sa Draw3DUpFrame, Draw3DDownThinFrame
 */
void GUIAPI Draw3DDownFrame (HDC hDC, INT32 l, INT32 t, INT32 r, INT32 b, GAL_PIXEL fillc);

/**
 * \def Draw3DUpThickFrame
 * \brief Alias of Draw3DUpFrame
 */
#define Draw3DUpThickFrame	  Draw3DUpFrame

/**
 * \def Draw3DDownThickFrame
 * \brief Alias of Draw3DDownFrame
 */
#define Draw3DDownThickFrame	Draw3DDownFrame

/**
 * \fn void GUIAPI Draw3DUpThinFrame (HDC hDC, INT32 l, INT32 t, INT32 r, INT32 b, GAL_PIXEL fillc)
 * \brief Draws a thin 3D up frame.
 *
 * This function draws a thin 3D up frame (the border is 1-pixel wide), 
 * and fills the frame if a valid filling pixel is specified.
 *
 * \param hDC The device context.
 * \param l The x-coordinate of upper-left corner of the frame.
 * \param t The y-coordinate of upper-left corner of the frame.
 * \param r The x-coordinate of lower-right corner of the frame.
 * \param b The y-coordinate of lower-right corner of the frame.
 * \param fillc The filling color.
 *
 * \note If \a fillc is zero, this function will not fill the frame.
 *
 * \sa Draw3DDownThinFrame, Draw3DUpFrame
 */
void GUIAPI Draw3DUpThinFrame (HDC hDC, 
				INT32 l, INT32 t, INT32 r, INT32 b, GAL_PIXEL fillc);

/**
 * \fn void GUIAPI Draw3DDownThinFrame (HDC hDC, INT32 l, INT32 t, INT32 r, INT32 b, GAL_PIXEL fillc)
 * \brief Draws a thin 3D down frame.
 *
 * This function draws a thin 3D down frame (the border is 1-pixel wide), 
 * and fills the frame if a valid filling pixel is specified.
 *
 * \param hDC The device context.
 * \param l The x-coordinate of upper-left corner of the frame.
 * \param t The y-coordinate of upper-left corner of the frame.
 * \param r The x-coordinate of lower-right corner of the frame.
 * \param b The y-coordinate of lower-right corner of the frame.
 * \param fillc The filling color.
 *
 * \note If \a fillc is zero, this function will not fill the frame.
 *
 * \sa Draw3DUpThinFrame, Draw3DDownFrame
 */
void GUIAPI Draw3DDownThinFrame (HDC hDC, 
				INT32 l, INT32 t, INT32 r, INT32 b, GAL_PIXEL fillc);

/**
 * \fn void GUIAPI Draw3DBorder (HDC hdc, INT32 l, INT32 t, INT32 r, INT32 b)
 * \brief Draws a 3D rectangle border.
 *
 * This function draws a 3D retangle border which is 2-pixel wide.
 *
 * \param hDC The device context.
 * \param l The x-coordinate of upper-left corner of the rectangle.
 * \param t The y-coordinate of upper-left corner of the rectangle.
 * \param r The x-coordinate of lower-right corner of the rectangle.
 * \param b The y-coordinate of lower-right corner of the rectangle.
 *
 * \sa Draw3DUpThinFrame, Draw3DDownFrame
 */
void GUIAPI Draw3DBorder (HDC hdc, INT32 l, INT32 t, INT32 r, INT32 b);

/**
 * \fn void GUIAPI DisabledTextOut (HDC hDC, INT32 x, INT32 y, const char* szText)
 * \brief Outputs disabled (grayed) text.
 *
 * This function outputs a grayed text at the specified position.
 *
 * \param hDC The device context.
 * \param x The x-coordinate of start point.
 * \param y The y-coordinate of start point.
 * \param szText The null-terminated text to be outputted.
 *
 * \sa TextOut, DrawText
 */
void GUIAPI DisabledTextOut (HDC hDC, INT32 x, INT32 y, const char* szText);

	/** @} end of misc_fns */

void do_nothing (void);

	/**
	 * \defgroup str_helpers String operation helpers
	 * @{
	 */

/**
 * \fn char* strnchr (const char* s, size_t n, INT32 c);
 * \brief Locates character in the first \a n characters of string \a s.
 *
 * \param s The pointer to the string.
 * \param n The number of first characters will be searched.
 * \param c The expected character.
 * \return Returns a pointer to the first occurrence of the character \a c in the string \a s
 *
 * \sa strchr(3)
 */
char* strnchr (const char* s, INT32 n, INT32 c);

/**
 * \fn INT32 substrlen (const char* text, INT32 len, char delimiter, INT32* nr_delim)
 * \brief Locates a substring delimited by one or more delimiters in the first \a len characters of string \a text.
 *
 * \param text The pointer to the string.
 * \param len The number of first characters will be searched.
 * \param delimiter The delimiter which delimites the substring from other.
 * \param nr_delim  The number of continuous delimiters will be returned through this pointer.
 * \return The length of the substring.
 *
 * \sa strstr(3)
 */
INT32 substrlen (const char* text, INT32 len, char delimiter, INT32* nr_delim);

	/** @} end of str_helpers */


extern  INT  _menu_lev;
extern  INT  _backMainScn_lev;  //


#define  GET_GUI_PERMIT()		   pthread_mutex_lock(&GuiUseSem)
#define  RELEASE_GUI_PERMIT()   pthread_mutex_unlock(&GuiUseSem)

#endif
