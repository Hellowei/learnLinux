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
修改者:		 gjl
修改日期:	   2013-4-22
修改内容:
修改原因:
*****************************************************************************************/

// 此处引用MiniGui中EDIT的宏定义	
#ifndef _MGUI_CTRL_EDIT_H
#define _MGUI_CTRL_EDIT_H
	 
   
		/**
		 * \addtogroup controls
		 * @{
		 */
	
		/**
		 * \defgroup ctrl_edit Edit/MEdit control
		 *
		 * @{
		 */
	
	/**
	 * \def CTRL_EDIT
	 * \brief The class name of simple single-line editor box.
	 *
	 * This edit control uses the system default fixed logical font.
	 */
#define CTRL_EDIT		   ("edit")
	
		/**
		 * \defgroup ctrl_edit_styles Styles of edit control
		 * @{
		 */
	
	/**
	 * \def ES_LEFT
	 * \brief Left-aligned text.
	 */
#define ES_LEFT			 0x00000000L
	
	/**
	 * \def ES_CENTER
	 * \brief Center-aligned text.
	 */
#define ES_CENTER		   0x00000001L
	
	/**
	 * \def ES_RIGHT
	 * \brief Right-aligned text.
	 */
#define ES_RIGHT			0x00000002L
	
	/**
	 * \def ES_MULTILINE
	 * \brief Multi-line text.
	 */
#define ES_MULTILINE		0x00000004L
	
	/**
	 * \def ES_UPPERCASE
	 * \brief Converts all characters to uppercase as they are typed into the edit control.
	 */
#define ES_UPPERCASE		0x00000008L
	
	/**
	 * \def ES_LOWERCASE
	 * \brief Converts all characters to lowercase as they are typed into the edit control.
	 */
#define ES_LOWERCASE		0x00000010L
	
	/**
	 * \def ES_PASSWORD
	 * \brief Displays an asterisk (*) for each character typed into the edit control.
	 */
#define ES_PASSWORD		 0x00000020L
	
	/* Not use */
#define ES_AUTOVSCROLL	  0x00000040L
	/* Not use */
#define ES_AUTOHSCROLL	  0x00000080L
	
	/**
	 * \def ES_NOHIDESEL
	 * \brief Edit control with this style will remain selected when focus is lost
	 */
#define ES_NOHIDESEL		0x00000100L
	
	/**
	 * \def ES_AUTOSELECT
	 * \brief Selects all text when getting focus
	 */
#define ES_AUTOSELECT	   0x00000400L
	//#define ES_OEMCONVERT	   0x00000400L
	
	/**
	 * \def ES_READONLY
	 * \brief Prevents the user from typing or editing text in the edit control.
	 */
#define ES_READONLY		 0x00000800L
	
	/**
	 * \def ES_BASELINE
	 * \brief Draws base line under input area instead of frame border.
	 */
#define ES_BASELINE		 0x00001000L
	
	/**
	 * \def ES_AUTOWRAP
	 * \brief Automatically wraps against border when inputting.
	 */
#define ES_AUTOWRAP		 0x00002000L
	
	/**
	 * \def ES_TITLE
	 * \brief Shows specified title texts.
	 */
#define ES_TITLE			0x00004000L
	
	/**
	 * \def ES_TIP
	 * \brief Shows specified tip texts.
	 */
#define ES_TIP			  0x00008000L
	
		/** @} end of ctrl_edit_styles */
	
		/**
		 * \defgroup ctrl_edit_msgs Messages of edit control
		 * @{
		 */

#define ES_TYPEMASK		 0x0000FFFFL
	
	/**
	 * \def EM_GETSEL
	 * \brief Gets the selected string in the edit control.
	 *
	 * \code
	 * EM_GETSEL
	 *
	 * char *buffer;
	 * int len;
	 *
	 * wParam = (WPARAM)len;
	 * lParam = (LPARAM)buffer;
	 * \endcode
	 *
	 * \param len Length of buffer.
	 * \param buffer Pointer to the string buffer
	 *
	 * \return Length of the selected string
	 */
#define EM_GETSEL			   0xF0B0
	
	/**
	 * \def EM_SETSEL
	 * \brief Sets the selected point in the edit control and makes
	 *		the text between insertion point and selection point selected.
	 *
	 *		Generally, you should send EM_SETCARETPOS first to set insertion
	 *		point before you use EM_SETSEL to select text.
	 *
	 * \code
	 * EM_SETSEL
	 *
	 * int line_pos;
	 * int char_pos;
	 *
	 * wParam = (WPARAM)line_pos;
	 * lParam = (LPARAM)char_pos;
	 * \endcode
	 *
	 * \param line_pos Line position of the selection point.
	 *				 For single line editor, it is always zero.
	 *				 Note : For multi-line editor, "line" means a text string ended with a line
	 *				 seperator, not a single text line in wrap mode. So, char_pos
	 *				 means the character position in a text string.
	 * \param char_pos Character(wide character) position of the selection point.
	 *
	 * \return Length of the selected string
	 */
#define EM_SETSEL			   0xF0B1
	
	/**
	 * \def EM_SETSELECTION
	 * \sa EM_SETSEL
	 */
#define EM_SETSELECTION		 EM_SETSEL
	
	/**
	 * \def EM_SELECTALL
	 * \brief Selects all the texts, the same meaning as ctrl+a
	 *		
	 * \code
	 * EM_SELECTALL
	 *
	 * wParam = 0;
	 * lParam = 0;
	 * \endcode
	 */
#define EM_SELECTALL			  0xF0B2
	
	/**
	 * \def EM_GETSELPOS
	 * \brief Gets the position of the selection point.
	 *
	 * \code
	 * EM_GETSELPOS
	 * int* line_pos;
	 * int* char_pos;
	 *
	 * wParam = (WPARAM)line_pos;
	 * lParam = (LPARAM)char_pos;
	 * \endcode
	 *
	 * \param line_pos Pointer to a integer buffer to save the selection line position.
	 *				 For single line editor, it is always zero.
	 *				 Note : Here "line" means a text string ended with a line
	 *				 seperator, not a single text line in wrap mode. So, char_pos
	 *				 means the character position in a text string.
	 * \param char_pos Pointer to a integer buffer to save the selection character position.
	 *
	 * \return The string length of the text from the beginning to the selection point.
	 */
#define EM_GETSELPOS			  0xF0B3
	
	/**
	 * \def EM_INSERTCBTEXT
	 * \brief Inserts the text in the clipboard to the current caret position
	 *
	 * \code
	 * EM_INSERTCBTEXT
	 * int len;
	 * const char *string;
	 *
	 * wParam = (WPARAM)len;
	 * lParam = (LPARAM)string;
	 * \endcode
	 *
	 * \param len Length of string
	 * \param string Pointer to the text string
	 */
#define EM_INSERTCBTEXT		   0xF0B4
	
	/**
	 * \def EM_COPYTOCB
	 * \brief Copies the currently selected text to the clipboard
	 *
	 * \code
	 * EM_COPYTOCB
	 *
	 * wParam = 0;
	 * lParam = 0
	 * \endcode
	 *
	 * \return Length of the text which is really copied to clipboard.
	 */
#define EM_COPYTOCB			   0xF0B5
	
	/**
	 * \def EM_CUTTOCB
	 * \brief Cuts the currently selected text to the clipboard
	 *
	 * \code
	 * EM_CUTTOCB
	 *
	 * wParam = 0;
	 * lParam = 0
	 * \endcode
	 *
	 * \return Length of the text which is really copied to clipboard.
	 */
#define EM_CUTTOCB			   0xF0B6
	
	/**
	 * \def EM_SETLFDISPCHAR
	 * \brief Sets the char used to represent the line seperator.
	 *		
	 * In default case, the line sperator will not be shown.
	 * If the char used to represent the line seperator is not zero,
	 *	this char will be shown in place of line seperator.
	 *
	 * \code
	 * EM_SETLFDISPCHAR
	 * unsigned char ch;
	 *
	 * wParam = 0;
	 * lParam = ch;
	 * \endcode
	 *
	 * \param ch The char used to represent the line seperator
	 */
#define EM_SETLFDISPCHAR		  0xF0B7
	
	/**
	 * \def EM_SETLINESEP
	 * \brief Sets the line seperator.
	 *		
	 * In default case, the line sperator is '\n'.
	 *
	 * \code
	 * EM_SETLINESEP
	 * unsigned char ch;
	 *
	 * wParam = 0;
	 * lParam = ch;
	 * \endcode
	 *
	 * \param ch The new line seperator
	 */
#define EM_SETLINESEP			 0xF0B8
	
	/* #define EM_GETRECT			  0xF0B2 */
	/* #define EM_SETRECT			  0xF0B3 */
	/* #define EM_SETRECTNP			0xF0B4 */
	/* #define EM_SCROLL			   0xF0B5 */
	
	/**
	 * \def EM_GETCARETPOS
	 * \brief Gets the position of the caret.
	 *
	 * \code
	 * EM_GETCARETPOS
	 * int* line_pos;
	 * int* char_pos;
	 *
	 * wParam = (WPARAM)line_pos;
	 * lParam = (LPARAM)char_pos;
	 * \endcode
	 *
	 * \param line_pos Pointer to a integer buffer to save the caret line position.
	 *				 For single line editor, it is always zero.
	 *				 Note : Here "line" means a text string ended with a line
	 *				 seperator, not a single text line in wrap mode. So, char_pos
	 *				 means the character position in a text string.
	 * \param char_pos Pointer to a integer buffer to save the caret character position.
	 *
	 * \return The string length of the text from the beginning to the caret pos.
	 */
#define EM_GETCARETPOS		  0xF0B9
	
	/**
	 * \def EM_SETCARETPOS
	 * \brief Sets the position of the caret.
	 *
	 * \code
	 * EM_SETCARETPOS
	 * int line_pos;
	 * int char_pos;
	 *
	 * wParam = (WPARAM)line_pos;
	 * lParam = (LPARAM)char_pos;
	 * \endcode
	 *
	 * \param line_pos The new caret line position. For single line editor, it will be ignored.
	 *				 Note : Here "line" means a text string ended with a line
	 *				 seperator, not a single text line in wrap mode. So, char_pos
	 *				 means the character position in a text string.
	 * \param char_pos The new caret character position.
	 *
	 * \return Length of the string from the beginning to the caret position 
	 *		 on success, otherwise -1.
	 */
#define EM_SETCARETPOS		  0xF0BA
	
	/**
	 * \def EM_SETINSERTION
	 * \sa EM_SETCARETPOS
	 */
#define EM_SETINSERTION		 EM_SETCARETPOS
	
	/* #define EM_SCROLLCARET		  0xF0B9 */
	/* #define EM_GETMODIFY			0xF0BA */
	/* #define EM_SETMODIFY			0xF0BB */
	
	/**
	 * \def EM_GETLINECOUNT
	 * \brief Gets the line number.
	 *
	 * \code
	 * EM_GETLINECOUNT
	 *
	 * wParam = 0;
	 * lParam = 0;
	 * \endcode
	 *
	 * \return Line number on success, otherwise -1.
	 * \note Implemented for TextEdit control.
	 */
#define EM_GETLINECOUNT		 0xF0BC
	
	/**
	 * \def EM_GETLINEHEIGHT
	 * \brief Gets the height of a line.
	 *
	 * \code
	 * EM_GETLINEHEIGHT
	 *
	 * wParam = 0;
	 * lParam = 0;
	 * \endcode
	 *
	 * \return Height value.
	 * \note Implemented for TextEdit control.
	 */
#define EM_GETLINEHEIGHT		0xF0BD
	
	/**
	 * \def EM_SETLINEHEIGHT
	 * \brief Sets the height of a line.
	 *
	 * \code
	 * EM_SETLINEHEIGHT
	 *
	 * wParam = (WPARAM)height;
	 * lParam = 0;
	 * \endcode
	 *
	 * \return The old height value.
	 * \note Implemented for TextEdit control.
	 */
#define EM_SETLINEHEIGHT		0xF0BE
	
	
	/*#define EM_LINEINDEX			0xF0BD */
	/*#define EM_GETTHUMB			 0xF0BE */
	
	/* internal used now */
#define EM_LINESCROLL		   0xF0BF
	 
	/**
	 * \def EM_INSERTTEXT
	 * \brief Inserts the specified text to the current caret position
	 *
	 * Normally used to input a long string.
	 *
	 * \code
	 * EM_INSERTTEXT
	 * int len;
	 * const char *string;
	 *
	 * wParam = (WPARAM)len;
	 * lParam = (LPARAM)string;
	 * \endcode
	 *
	 * \param len Length of string
	 * \param string Pointer to the text string
	 */
#define EM_INSERTTEXT		   0xF0C0
	
	/* Not use */
#define EM_LINELENGTH		   0xF0C1
	/* Not use */
#define EM_REPLACESEL		   0xF0C2
	
	/**
	 * \def EM_GETMAXLIMIT
	 * \brief Get text limit of a single-line edit control.
	 */
#define EM_GETMAXLIMIT			0xF0C3
	
	/* Not use */
#define EM_GETLINE			  0xF0C4
	
	/**
	 * \def EM_LIMITTEXT
	 * \brief Set text limit of an edit control.
	 *
	 * \code
	 * EM_LIMITTEXT
	 * int newLimit;
	 *
	 * wParam = (WPARAM)newLimit;
	 * lParam = 0;
	 * \endcode
	 *
	 * \param newLimit The new text limit of an edit control.
	 */
#define EM_LIMITTEXT			0xF0C5
	
	/**
	 * \def EM_REDO
	 * \brief Redo operation.
	 *
	 * \code
	 *
	 * wParam = 0;
	 * lParam = 0;
	 * \endcode
	 *
	 */
#define EM_REDO				 0xF0C6
	/*#define EM_CANUNDO			  0xF0C6 */
	 
	/**
	 * \def EM_UNDO
	 * \brief Undo operation.
	 *
	 * \code
	 *
	 * wParam = 0;
	 * lParam = 0;
	 * \endcode
	 *
	 */
#define EM_UNDO				 0xF0C7
	
	/* Not use */
#define EM_FMTLINES			 0xF0C8
	/* Not use */
#define EM_LINEFROMCHAR		 0xF0C9
	/* Not use */
#define EM_SETTABSTOPS		  0xF0CB
	
	/**
	 * \def EM_SETPASSWORDCHAR
	 * \brief Defines the character that edit control uses in conjunction with 
	 * the ES_PASSWORD style.
	 *
	 * \code
	 * EM_SETPASSWORDCHAR
	 * char passwdChar;
	 *
	 * wParam = (WPARAM)passwdChar;
	 * lParam = 0;
	 * \endcode
	 */
#define EM_SETPASSWORDCHAR	  0xF0CC
	
	/* Not use */
#define EM_EMPTYUNDOBUFFER	  0xF0CD
	/* Not use */
#define EM_GETFIRSTVISIBLELINE  0xF0CE
	
	/**
	 * \def EM_SETREADONLY
	 * \brief Sets or removes the read-only style (ES_READONLY) in an edit control.
	 *
	 * \code
	 * EM_SETREADONLY
	 * int readonly;
	 *
	 * wParam = (WPARAM)readonly;
	 * lParam = 0;
	 * \endcode
	 *
	 * \param readonly Indicates whether the edit control is read-only:
	 *	  - Zero\n
	 *		Not read-only.
	 *	  - Non zero\n
	 *		Read-only.
	 */
#define EM_SETREADONLY		  0xF0CF
	
	/**
	 * \def EM_SETDRAWSELECTFUNC
	 * \brief Sets the callback function on drawing selected chars
	 *
	 * \code
	 * EM_SETDRAWSELECTFUNC
	 * ED_DRAWSEL_FUNC drawsel;
	 *
	 * wParam = 0;
	 * lParam = (LPARAM)drawsel;
	 * \endcode
	 *
	 * \param drawsel The callback function used to draw selected strings.
	 */
#define EM_SETDRAWSELECTFUNC	0xF0D0
	
	/**
	 * \def EM_SETGETCARETWIDTHFUNC
	 * \brief Sets the callback function on getting caret width
	 *
	 * \code
	 * EM_SETGETCARETWIDTHFUNC
	 * int (*get_caret_width) (HWND, int);
	 *
	 * wParam = 0;
	 * lParam = (LPARAM)get_caret_width;
	 * \endcode
	 *
	 * \param get_caret_width The callback function used to get caret width.
	 *						The window handle and the maximum caret width are passed as arguments.
	 *
	 * \return The desired caret width.
	 */
#define EM_SETGETCARETWIDTHFUNC 0xF0D1
	
	/*
#define EM_SETWORDBREAKPROC	 0xF0D0
#define EM_GETWORDBREAKPROC	 0xF0D1
	*/
	
	/**
	 * \def EM_GETPASSWORDCHAR
	 * \brief Returns the character that edit controls uses in conjunction with 
	 * the ES_PASSWORD style.
	 *
	 * \code
	 * EM_GETPASSWORDCHAR
	 *
	 * wParam = 0;
	 * lParam = 0;
	 * \endcode
	 *
	 * \return The currently used password character
	 */
#define EM_GETPASSWORDCHAR	  0xF0D2
	
	/**
	 * \def EM_SETLIMITTEXT
	 * \sa EM_LIMITTEXT
	 */
#define EM_SETLIMITTEXT		 EM_LIMITTEXT
	
	/**
	 * \def ED_CARETSHAPE_LINE
	 * \brief Line-shaped caret
	 */
#define ED_CARETSHAPE_LINE	  0
	
	/**
	 * \def ED_CARETSHAPE_BLOCK
	 * \brief Block-shaped caret
	 */
#define ED_CARETSHAPE_BLOCK	 1
	
	/**
	 * \def EM_CHANGECARETSHAPE
	 * \brief Changes the shape of the caret
	 *
	 * \code
	 * EM_CHANGECARETSHAPE
	 *
	 * int caret_shape;
	 * 
	 * wParam = (WPARAM)caret_shape;
	 * lParam = 0;
	 * \endcode
	 *
	 * \param caret_shape Shape index of the caret, can be ED_CARETSHAPE_LINE or ED_CARETSHAPE_BLOCK.
	 *
	 * \return The old create shape
	 */
#define EM_CHANGECARETSHAPE	 0xF0D3
	
	/**
	 * \def EM_REFRESHCARET
	 * \brief Refresh caret of the edit control
	 */
#define EM_REFRESHCARET		 0xF0D4
	
	/**
	 * \def EM_ENABLECARET
	 * \brief To enable or disable the input caret
	 *
	 * \code
	 * EM_ENABLECARET
	 *
	 * BOOL bEnable;
	 *
	 * wParam = (WPARAM)bEnable;
	 * lParam = 0;
	 * \endcode
	 *
	 * \param bEnable TRUE to enable caret.
	 *
	 * \return The previous caret enabled status.
	 */
#define EM_ENABLECARET		  0xF0D5
	
	/**
	 * \def EM_GETLIMITTEXT
	 * \brief Get text limit value of the edit control. 
	 *
	 * \return -1 when user doesn't set limit value, otherwise return current 
	 * limit value. 
	 */
#define EM_GETLIMITTEXT		 0xF0D6
	/* Not use */
#define MED_STATE_YES		   0x0
	/* Not use */
#define MED_STATE_NOUP		  0x1
	/* Not use */
#define MED_STATE_NODN		  0x2
	/* Not use */
#define MED_STATE_NO			0x3
	
	/**
	 * \def EM_SETTITLETEXT
	 * \brief Sets the title text displayed before content text. 
	 *
	 * \code
	 * EM_SETTITLETEXT
	 * const char *title;
	 * int len;
	 *
	 * wParam = (WPARAM)len;
	 * lParam = (LPARAM)title;
	 * \endcode
	 *
	 * \note Implemented for TextEdit control.
	 */
#define EM_SETTITLETEXT		 0xF0DC
	
	/**
	 * \def EM_GETTITLETEXT
	 * \brief Gets the title text displayed before content text. 
	 *
	 * \code
	 * EM_GETTITLETEXT
	 * const char *buffer;
	 * int len;
	 *
	 * wParam = (WPARAM)len;
	 * lParam = (LPARAM)buffer;
	 * \endcode
	 *
	 * \param len Should be length of buffer minus 1, left space for '\\0'
	 * \param buffer String buffer
	 *
	 *
	 * \return Length of title
	 * \note Implemented for TextEdit control.
	 */
#define EM_GETTITLETEXT		 0xF0DD
	
	/**
	 * \def EM_SETTIPTEXT
	 * \brief Sets the tip text displayed when content is empty. 
	 *
	 * \code
	 * EM_SETTIPTEXT
	 * const char *buffer;
	 * int len;
	 *
	 * wParam = (WPARAM)len;
	 * lParam = (LPARAM)buffer;
	 * \endcode
	 *
	 */
#define EM_SETTIPTEXT		   0xF0DE
	
	/**
	 * \def EM_GETTIPTEXT
	 * \brief Gets the tip text displayed when content is empty. 
	 *
	 * \code
	 * EM_GETTIPTEXT
	 * const char *buffer;
	 * int len;
	 *
	 * wParam = (WPARAM)len;
	 * lParam = (LPARAM)buffer;
	 * \endcode
	 *
	 * \param len Should be length of buffer minus 1, left space for '\\0'
	 * \param buffer String buffer
	 *
	 * \return Length of tip text
	 */
#define EM_GETTIPTEXT		   0xF0DF
	
	/**
	 * \def EM_GETNUMOFPARAGRAPHS
	 * \brief Gets the number of paragraphs in textedit control. 
	 *
	 * \return The number of paragraphs.
	 */
#define EM_GETNUMOFPARAGRAPHS   0xF0E0
	/**
	 * \def EM_GETPARAGRAPHLENGTH
	 * \brief Gets the specified paragraph length in textedit control. 
	 *
	 * \code
	 * EM_GETPARAGRAPHLENGTH
	 * wParam = (WPARAM) index;
	 * \endcode
	 *
	 * \return The length of text.
	 */
#define EM_GETPARAGRAPHLENGTH  0xF0E1
	/**
	 * \def EM_GETPARAGRAPHTEXT
	 * \brief Gets the specified paragraph text from textedit control. 
	 *
	 * \code
	 * EM_GETPARAGRAPHTEXT
	 * const char buffer[BUF_SIZE];
	 * TEXTPOSINFO info;
	 *
	 * info.start_pos = 0;
	 * info.copy_len = BUF_SIZE;
	 * info.buff = buffer;
	 * info.paragraph_index = -1;
	 *
	 * wParam = (WPARAM)&info;
	 * \endcode
	 *
	 * \return The copied length of text which doesn't include terminate 
	 * character '\0'.
	 */
#define EM_GETPARAGRAPHTEXT	0xF0E2
	
#define EM_MSGMAX			   0xF0EA
	
		/** @} end of ctrl_edit_msgs */
	
		/**
		 * \defgroup ctrl_edit_ncs Notification codes of edit control
		 * @{
		 */
	
#define EN_ERRSPACE		 255
	
	/**
	 * \def EN_CLICKED
	 * \brief Notifies a click in an edit control.
	 *
	 * An edit control sends the EN_CLICKED notification code when the user clicks
	 * in an edit control.
	 */
#define EN_CLICKED		  0x0001
	
	/**
	 * \def EN_DBLCLK
	 * \brief Notifies a double click in an edit control.
	 *
	 * An edit control sends the EN_CLICKED notification code when the user 
	 * double clicks in an edit control.
	 */
#define EN_DBLCLK		   0x0002
	
	/**
	 * \def EN_SETFOCUS
	 * \brief Notifies the receipt of the input focus.
	 *
	 * The EN_SETFOCUS notification code is sent when an edit control receives 
	 * the input focus.
	 */
#define EN_SETFOCUS		 0x0100
	
	/**
	 * \def EN_KILLFOCUS
	 * \brief Notifies the lost of the input focus.
	 *
	 * The EN_KILLFOCUS notification code is sent when an edit control loses 
	 * the input focus.
	 */
#define EN_KILLFOCUS		0x0200
	
	/**
	 * \def EN_CHANGE
	 * \brief Notifies that the text is altered by the user.
	 *
	 * An edit control sends the EN_CHANGE notification code when the user takes 
	 * an action that may have altered text in an edit control.
	 */
#define EN_CHANGE		   0x0300
	
	/**
	 * \def EN_UPDATE
	 * \brief Notifies that the text is altered by sending MSG_SETTEXT
	 *		TEM_RESETCONTENT, or EM_SETLINEHEIGHT message to it.
	 *
	 * An edit control sends the EN_UPDATE notification code when the control
	 * received MSG_SETTEXT, TEM_RESETCONTENT, or EM_SETLINEHEIGHT message.
	 *
	 * Note that this notification will occured when you call SetWindowText or
	 * SetDlgItemText function on the control.
	 */
#define EN_UPDATE		   0x0400
	
	/**
	 * \def EN_MAXTEXT
	 * \brief Notifies reach of maximum text limitation.
	 *
	 * The EN_MAXTEXT notification message is sent when the current text 
	 * insertion has exceeded the specified number of characters for the edit control.
	 */
#define EN_MAXTEXT		  0x0501
	
	/* Not use */
#define EN_HSCROLL		  0x0601
	/* Not use */
#define EN_VSCROLL		  0x0602
	
	
	/**
	 * \def EN_SELCHANGED
	 * \brief Notifies that the current selection is changed in the text field.
	 */
#define EN_SELCHANGED	   0x0603
	
	/**
	 * \def EN_CONTCHANGED
	 * \brief Notifies that the current content is changed in the text field
	 * when text edit losts focus.
	 */
#define EN_CONTCHANGED	 0x0604
	
	/**
	 * \def EN_ENTER
	 * \brief Notifies the user has type the ENTER key in a single-line edit control.
	 */
#define EN_ENTER			0x0700
	
		/** @} end of ctrl_edit_ncs */
	
	/* Edit control EM_SETMARGIN parameters */
	/**
	 * \def EC_LEFTMARGIN
	 * \brief Value of wParam. Specifies the margins to set.
	 */
#define EC_LEFTMARGIN	   0x0001
	/**
	 * \def EC_RIGHTMARGIN
	 * \brief Value of wParam. Specifies the margins to set.
	 */
#define EC_RIGHTMARGIN	  0x0002
	/**
	 * \def EC_USEFONTINFO
	 * \brief Value of wParam. Specifies the margins to set.
	 */
#define EC_USEFONTINFO	  0xffff
	
	/* wParam of EM_GET/SETIMESTATUS  */
	/**
	 * \def EMSIS_COMPOSITIONSTRING
	 * \brief Indicates the type of status to retrieve.
	 */
#define EMSIS_COMPOSITIONSTRING		0x0001
	
	/* lParam for EMSIS_COMPOSITIONSTRING  */
	/**
	 * \def EIMES_GETCOMPSTRATONCE
	 * \brief lParam for EMSIS_COMPOSITIONSTRING.
	 */
#define EIMES_GETCOMPSTRATONCE		 0x0001
	/**
	 * \def EIMES_CANCELCOMPSTRINFOCUS
	 * \brief lParam for EMSIS_COMPOSITIONSTRING.
	 */
#define EIMES_CANCELCOMPSTRINFOCUS	 0x0002
	/**
	 * \def EIMES_COMPLETECOMPSTRKILLFOCUS
	 * \brief lParam for EMSIS_COMPOSITIONSTRING.
	 */
#define EIMES_COMPLETECOMPSTRKILLFOCUS 0x0004
	
		/** @} end of ctrl_edit */
	
		/** @} end of controls */
	
	
#endif /* _MGUI_CTRL_EDIT_H */
	
#if !defined(_EDIT_H)
#define	  _EDIT_H

#define EST_FOCUSED	 0x00000001L
#define EST_MODIFY	  0x00000002L
#define EST_IME_MK	  0x00000080L
#define EST_IME_CN	  0x00000040L
#define EST_IME_UP	  0x00000020L
#define EST_IME_LO	  0x00000010L
#define EST_IME_MASK	0x000000F0L

#define MSG_DOESNEEDIME	 0x0150

typedef struct tagSLEDITDATA
{
	DWORD   status;		 // status of box
	/** /
	int	 editPos;		// current edit position
	int	 selStart;	   // selection start position
	int	 selEnd;		 // selection end position
	int	 nContX;		 // content x offset position
	int	 nContW;		 // content width
	/ **/ 
	RECT	rcVis;		  // content rect
	int	 nVisW;		  // visible area width
	/** /
	int	 startx;		 // text x display position
	int	 starty;		 // text y display position
	/ **/ 

	int	 leftMargin;	 // left margin
	int	 topMargin;	  // top margin
	int	 rightMargin;	// right margin
	int	 bottomMargin;   // bottom margin

//	int	 nBlockSize;	 /* string buffer block size */
	StrBuffer content;	  // string text buffer
	char	*tiptext;	   // tip text
	char	*titletext;	 // title
	int	 hardLimit;	  // hard limit

	/** /
	int	 passwdChar;	 // password character
	/ **/

	DWORD   dwAddData;		  // the additional data.
	DWORD   dwAddData2;		 // the second addtional data.

	int	 changed;		  // change flag
}EDITDATA, *EDITDATAP;

#ifndef MARGIN_EDIT_LEFT
#define MARGIN_EDIT_LEFT		1
#endif

#ifndef MARGIN_EDIT_TOP
#define MARGIN_EDIT_TOP		 1
#endif

#ifndef MARGIN_EDIT_RIGHT
#define MARGIN_EDIT_RIGHT	   2
#endif

#ifndef MARGIN_EDIT_BOTTOM
#define MARGIN_EDIT_BOTTOM	  1
#endif

#define EDIT_STRLEN_MAX		 150

#define EDIT_STATUS(pCtrl)   (((EDITDATAP)(pCtrl->dwAddData2))->status)

#ifndef EDIT_GLOBALS
#define EDIT_EXT extern
#else
#define EDIT_EXT
#endif

EDIT_EXT VOID SetEditboxText(PCONTROL pCtrl);

// 外部接口函数
BOOL RegisterEditControl(VOID);
CHAR *GetEditText(RESID parent, RESID child);
VOID SetEditText(RESID parent, RESID child, UCHAR *txt);
VOID SetEditboxHardLimit(RESID parent, RESID child, UINT32 limit);
#endif
