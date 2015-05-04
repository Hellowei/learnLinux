/*****************************************************************************************
°æÈ¨ËùÓÐ:			ºÍÐÄÖØµä
°æ±¾ºÅ:				1.0.0
Éú³ÉÈÕÆÚ:			2011.04.15
ÎÄ¼þÃû:				
×÷Õß:				ºÍÐÄÖØµä
¹¦ÄÜËµÃ÷:			
ÆäËüËµÃ÷:			ÎÞ
ËùÊôÎÄ¼þ¹ØÏµ:		±¾ÎÄ¼þÎª¹¤³Ì¹æÔ¼´úÂëÎÄ¼þ

ÐÞ¸Ä¼ÇÂ¼:
¼ÇÂ¼1:
ÐÞ¸ÄÕß:
ÐÞ¸ÄÈÕÆÚ:
ÐÞ¸ÄÄÚÈÝ:
ÐÞ¸ÄÔ­Òò:
*****************************************************************************************/
#if !defined(_CONTROL_H)
#define	  _CONTROL_H

#define  STATIC_HEIGHT  20  // ±ê×¼ Static ¿Ø¼þµÄ¸ß¶È


// ¶¨ÒåÊýÖµ¸ñÊ½ÀàÐÍ, formatÀàÐÍ
typedef enum _format_type
{
	FORM_0D,
	FORM_2D,
	FORM_3D,
	FORM_4D,
	FORM_41F,
	FORM_51F,
	FORM_52F,
	FORM_53F,
	FORM_72F
} FORMAT_TYPE;

// ²Ëµ¥ÖÐ¿Ø¼þµÄ¸ß¶È
//#define  KEY_HEIGHT	   22
// ÎÞÐ§Öµ
#define  UNAVAIL		  2

#define  GEN_UNPRESSED	 0x00000000L
	 
#define  GEN_PRESSED	   0x01000000L


/************************** Control Helpers **********************************/
	/**
	 * \addtogroup fns Functions
	 * @{
	 */

	/**
	 * \addtogroup global_fns Global/general functions
	 * @{
	 */

	/**
	 * \addtogroup misc_fns Miscellaneous functions
	 * @{
	 */
/**
 * \fn Draw3DControlFrame (HDC hdc, long x0, long y0, long x1, long y1, GAL_PIXEL fillc, BOOL updown)
 * \brief Draws a 3D style frame control.		   
 *
 * \param hdc The handle to Drawing context.
 * \param x0  Specifies the x-coordinate of the upper-left corner.
 * \param yo  Specifies the y-coordinate of the upper-left corner.
 * \param x1  Specifies the x-coordinate of the lower-right corner.  
 * \param y1  Specifies the y-coordinate of the lower-right corner.
 * \param fillc Specifies the color to fill the frame.
 * \param updown Specifies the state of the frame control, ie. up or down. 
 *
 * \sa Draw3DControlFrame
 */
void GUIAPI Draw3DControlFrame (HDC hdc, long x0, long y0, long x1, long y1, 
								GAL_PIXEL fillc, BOOL updown);

/**
 * \fn DrawFlatControlFrameEx(HDC hdc, long x0, long y0, long x1, long y1, GAL_PIXEL fillc, long corner, BOOL updown)
 * \brief Draws a flat frame control with triangle corner.
 *
 * \param hdc The handle to Drawing context.
 * \param x0  Specifies the x-coordinate of the upper-left corner.
 * \param yo  Specifies the y-coordinate of the upper-left corner.
 * \param x1  Specifies the x-coordinate of the lower-right corner.
 * \param y1  Specifies the y-coordinate of the lower-right corner.
 * \param fillc Specifies the color to fill the frame.
 * \param corner Specifies the length of the edge of the triangle corner.
 * \param updown Specifies the state of the frame control, ie. up or down.
 *
 * \sa Draw3DControlFrame
 */
void GUIAPI DrawFlatControlFrameEx (HDC hdc, long x0, long y0, long x1, long y1, 
									GAL_PIXEL fillc, long corner, BOOL updown);

/**
 * \def DrawFlatControlFrame(HDC hdc, long x0, long y0, long x1, long y1, GAL_PIXEL fillc, BOOL updown)
 * \brief Draws a flat frame control.		   
 *
 * \param hdc The handle to drawing context.
 * \param x0  Specifies the x-coordinate of the upper-left corner.
 * \param yo  Specifies the y-coordinate of the upper-left corner.
 * \param x1  Specifies the x-coordinate of the lower-right corner.  
 * \param y1  Specifies the y-coordinate of the lower-right corner.
 * \param fillc Specifies the color to fill the frame.
 * \param updown Specifies the state of the frame control, ie. up or down. 
 *
 * \note This function is actually a macro of DrawFlatControlFrameEx.
 *
 * \sa DrawFlatControlFrameEx
 */
#define DrawFlatControlFrame(hdc, x0, y0, x1, y1, fillc, updown) \
				 DrawFlatControlFrameEx(hdc, x0, y0, x1, y1, fillc, 3, updown);

/**
 * \def NotifyParent(hwnd, id, code)
 * \brief Sends a notification message to the parent.
 *
 * This function send a notification message to the parent.
 *
 * \param hwnd The handle to current control window.
 * \param id the id of current control .
 * \param code the Notification code.
 *
 * \note This Function is actually a macro of SendNotifyMessage.
 *
 * \sa SendNotifyMessage
 */
INT32 NotifyParent(HWND hwnd, INT16 id, INT16 code);
				 
	/** @} end of misc_fns */

	/** @} end of global_fns */

	/** @} end of fns */


	/**
	 * \defgroup controls Standard controls
	 * @{
	 */

/****** control messages *****************************************************/

/* NOTE: control messages start from 0xF000 to 0xFFFF */
#define MSG_FIRSTCTRLMSG	0xF000
#define MSG_LASTCTRLMSG	 0xFFFF

/****** Static Control ******************************************************/
#ifdef _CTRL_STATIC

	/**
	 * \defgroup ctrl_static Static control
	 * @{
	 */

/**
 * \def CTRL_STATIC
 * \brief The class name of static control.
 */
#define CTRL_STATIC		 "static"

	/**
	 * \defgroup ctrl_static_styles Styles of static control
	 * @{
	 */

/**
 * \def SS_LEFT
 * \brief Displays the given text flush-left.
 */
#define SS_LEFT			 0x00000000L

/**
 * \def SS_CENTER 
 * \brief Displays the given text centered in the rectangle. 
 */
#define SS_CENTER		   0x00000001L

/**
 * \def SS_RIGHT
 * \brief Displays the given text flush-right.
 */
#define SS_RIGHT			0x00000002L

/**
 * \def SS_ICON 
 * \brief Designates an icon displayed in the static control.
 */
#define SS_ICON			 0x00000003L

#define SS_BLACKRECT		0x00000004L

/**
 * \def SS_GRAYRECT
 * \brief Specifies a rectangle filled with the color used to 
 *		fill the screen background. The default is gray.
 */
#define SS_GRAYRECT		 0x00000005L

#define SS_WHITERECT		0x00000006L
#define SS_BLACKFRAME	   0x00000007L

/**
 * \def SS_GRAYFRAME
 * \brief Specifies a box with a frame drawn with the same color as 
 *		window frames. The default is gray.
 */
#define SS_GRAYFRAME		0x00000008L

#define SS_WHITEFRAME	   0x00000009L

/**
 * \def SS_GROUPBOX
 * \brief Creates a rectangle in which other controls can be grouped.
 */
#define SS_GROUPBOX		 0x0000000AL

/**
 * \def SS_SIMPLE 
 * \brief Designates a simple rectangle and displays a single line 
 *		of text flush-left in the rectangle.
 */
#define SS_SIMPLE		   0x0000000BL

/**
 * \def SS_LEFTNOWORDWRAP
 * \brief Designates a simple rectangle and displays the given text 
 *		flush-left in the rectangle. 
 *
 * Tabs are expanded, but words are not wrapped. 
 * Text that extends past the end of a line is clipped.
 */
#define SS_LEFTNOWORDWRAP   0x0000000CL

#define SS_OWNERDRAW		0x0000000DL

/**
 * \def SS_BITMAP
 * \brief Specifies that a bitmap will be displayed in the static control.
 */
#define SS_BITMAP		   0x0000000EL

#define SS_ENHMETAFILE	  0x0000000FL
#define SS_TYPEMASK		 0x0000000FL

/**
 * \def SS_NOPREFIX
 * \brief Prevents interpretation of any ampersand (&) characters in 
 *		the control's text as accelerator prefix characters.
 *
 * \note Not implemented so far.
 */
#define SS_NOPREFIX		 0x00000080L

#define SS_ETCHEDHORZ	   0x00000010L
#define SS_ETCHEDVERT	   0x00000011L
#define SS_ETCHEDFRAME	  0x00000012L
#define SS_ETCTYPEMAKS	  0x0000001FL

/**
 * \def SS_NOTIFY
 * \brief Sends the parent window notification messages when the user 
 *		clicks or double-clicks the control.
 */
#define SS_NOTIFY		   0x00000100L

#define SS_CENTERIMAGE	  0x00000200L
#define SS_RIGHTJUST		0x00000400L
#define SS_REALSIZEIMAGE	0x00000800L

/*
 * #define SS_SUNKEN		   0x00001000L
 * #define SS_ENDELLIPSIS	  0x00004000L
 * #define SS_PATHELLIPSIS	 0x00008000L
 * #define SS_WORDELLIPSIS	 0x0000C000L
 * #define SS_ELLIPSISMASK	 0x0000C000L
 */

	/** @} end of ctrl_static_styles */
	
	/**
	 * \defgroup ctrl_static_msgs Messages of static control
	 * @{
	 */

#define STM_SETICON		 0xF170
#define STM_GETICON		 0xF171

/**
 * \def STM_SETIMAGE
 * \brief Associate a new image (icon or bitmap) with a static control.
 *
 * An application sends an STM_SETIMAGE message to 
 * associate a new image (icon or bitmap) with a static control.
 *
 * \code
 * STM_SETIMAGE
 * HICON image;
 *  or 
 * BITMAP* image;
 *
 * wParam = (WPARAM)image;
 * lParam = 0;
 * \endcode
 * 
 * \param image The handle to an icon if the type of static control type 
 * is SS_ICON, or the pointer to a BITMAP object if the type is SS_BITMAP.
 * \return The old image (handle or pointer).
 */
#define STM_SETIMAGE		0xF172

/**
 * \def STM_GETIMAGE
 * \brief Retrieves a handle to the image.
 *
 * An application sends an STM_GETIMAGE message to retrieve a handle 
 * to the image associated with a static control.
 *
 * \code
 * STM_GETIMAGE
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The handle to the icon if the type of static control type is SS_ICON, 
 * or the pointer to the BITMAP object if the type is SS_BITMAP.
 */
#define STM_GETIMAGE		0xF173

/* Not supported */
#define STM_MSGMAX		  0xF174

	/** @} end of ctrl_static_msgs */

	/**
	 * \defgroup ctrl_static_ncs Notification codes of static control
	 * @{
	 */

/**
 * \def STN_DBLCLK
 * \brief Notifies a double-click.
 *
 * The STN_DBLCLK notification message is sent when 
 * the user double-clicks a static control that has the SS_NOTIFY style.
 */
#define STN_DBLCLK		  1

#define STN_ENABLE		  2
#define STN_DISABLE		 3

/**
 * \def STN_CLICKED
 * \brief Notifies that a static control is clicked.
 *
 * The STN_CLICKED notification message is sent 
 * when the user clicks a static control that has the SS_NOTIFY style.
 */
#define STN_CLICKED		 4

	/** @} end of ctrl_static_ncs */

	/** @} end of ctrl_static */

#endif /* _CTRL_STATIC */

/****** Button Control ******************************************************/
#ifdef _CTRL_BUTTON

	/**
	 * \defgroup ctrl_button Button control
	 * @{
	 */

/**
 * \def CTRL_BUTTON
 * \brief The class name of button control.
 */
#define CTRL_BUTTON		 "button"

	/**
	 * \defgroup ctrl_button_styles Styles of button control
	 * @{
	 */

/**
 * \def BS_PUSHBUTTON
 * \brief Creates a push button.
 */
#define BS_PUSHBUTTON	   0x00000000L

/**
 * \def BS_DEFPUSHBUTTON
 * \brief Creates a push button that behaves like a BS_PUSHBUTTON style button.
 
 * Creates a push button that behaves like a BS_PUSHBUTTON style button, 
 * but also has a heavy black border.  If the button is in a dialog box, 
 * the user can select the button by pressing the enter key, 
 * even when the button does not have the input focus. 
 * This style is useful for enabling the user to quickly select 
 * the most likely (default) option.
 */
#define BS_DEFPUSHBUTTON	0x00000001L

/**
 * \def BS_CHECKBOX
 * \brief Creates a small, empty check box with text.
 *
 * By default, the text is displayed to the right of the check box. 
 * To display the text to the left of the check box, combine this flag 
 * with the BS_LEFTTEXT style (or with the equivalent BS_RIGHTBUTTON style).
 */
#define BS_CHECKBOX		 0x00000002L

/**
 * \def BS_AUTOCHECKBOX
 * \brief Creates a button that is almost the same as a check box.
 *
 * Creates a button that is the same as a check box, 
 * except that the check state automatically toggles between 
 * checked and unchecked each time the user selects the check box.
 */
#define BS_AUTOCHECKBOX	 0x00000003L

/**
 * \def BS_RADIOBUTTON
 * \brief Creates a small circle with text.
 *
 * By default, the text is displayed to the right of the circle. 
 * To display the text to the left of the circle, combine this flag 
 * with the BS_LEFTTEXT style (or with the equivalent BS_RIGHTBUTTON style). 
 * Use radio buttons for groups of related, but mutually exclusive choices.
 */
#define BS_RADIOBUTTON	  0x00000004L

/**
 * \def BS_3STATE
 * \brief Creates a button that is almost the same as a check box.
 * 
 * Creates a button that is the same as a check box, except 
 * that the box can be grayed as well as checked or unchecked.
 * Use the grayed state to show that the state of the check box 
 * is not determined.
 */
#define BS_3STATE		   0x00000005L

/**
 * \def BS_AUTO3STATE
 * \brief Creates a button that is almost the same as a three-state check box.
 *
 * Creates a button that is the same as a three-state check box, 
 * except that the box changes its state when the user selects it.
 * The state cycles through checked, grayed, and unchecked.
 */
#define BS_AUTO3STATE	   0x00000006L

#define BS_GROUPBOX		 0x00000007L
#define BS_USERBUTTON	   0x00000008L

/**
 * \def BS_AUTORADIOBUTTON
 * \brief Creates a button that is almost the same as a radio button.
 * 
 * Creates a button that is the same as a radio button, 
 * except that when the user selects it, The system automatically 
 * sets the button's check state to checked
 * and automatically sets the check state for all other buttons 
 * in the same group to unchecked.
 */
#define BS_AUTORADIOBUTTON  0x00000009L

/**
 * \def BS_OWNERDRAW
 * \brief Creates an owner-drawn button.
 *
 * \note Not implemented so far.
 */
#define BS_OWNERDRAW		0x0000000BL

#define BS_TYPEMASK		 0x0000000FL

/**
 * \def BS_TEXT
 * \brief Specifies that the button displays text.
 */
#define BS_TEXT			 0x00000000L

/**
 * \def BS_LEFTTEXT
 * \brief Places text on the left side.
 *
 * Places text on the left side of the radio button 
 * or check box when combined with a radio button or check box style.
 */
#define BS_LEFTTEXT		 0x00000020L

/**
 * \def BS_ICON
 * \brief Specifies that the button displays an icon.
 */
#define BS_ICON			 0x00000040L

/**
 * \def BS_BITMAP
 * \brief Specifies that the button displays a bitmap.
 */
#define BS_BITMAP		   0x00000080L

#define BS_CONTENTMASK	  0x000000F0L

/**
 * \def BS_LEFT
 * \brief Left-justifies the text in the button rectangle.
 *
 * However, if the button is a check box or radio button that 
 * does not have the BS_RIGHTBUTTON style, the text is left 
 * justified on the right side of the check box or radio button.
 */
#define BS_LEFT			 0x00000100L

/**
 * \def BS_RIGHT
 * \brief Right-justifies text in the button rectangle.
 * 
 * However, if the button is a check box or radio button that 
 * does not have the BS_RIGHTBUTTON style, the text is 
 * right justified on the right side of the check box or radio button.
 */
#define BS_RIGHT			0x00000200L

/**
 * \def BS_CENTER
 * \brief Centers text horizontally in the button rectangle.
 */
#define BS_CENTER		   0x00000300L

/**
 * \def BS_TOP
 * \brief Places text at the top of the button rectangle.
 */
#define BS_TOP			  0x00000400L

/**
 * \def BS_BOTTOM
 * \brief Places text at the bottom of the button rectangle.
 */
#define BS_BOTTOM		   0x00000800L

/**
 * \def BS_VCENTER
 * \brief Places text in the middle (vertically) of the button rectangle.
 */
#define BS_VCENTER		  0x00000C00L

#define BS_ALIGNMASK		0x00000F00L

/**
 * \def BS_PUSHLIKE
 * \brief Makes a button look and act like a push button.
 *
 * Makes a button (such as a check box, three-state check box, or radio button) 
 * look and act like a push button. The button looks raised when it isn't 
 * pushed or checked, and sunken when it is pushed or checked.
 */
#define BS_PUSHLIKE		 0x00001000L

/**
 * \def BS_MULTLINE
 * \brief Wraps the button text to multiple lines.
 *
 * Wraps the button text to multiple lines if the text string is 
 * too long to fit on a single line in the button rectangle.
 */
#define BS_MULTLINE		 0x00002000L

/**
 * \def BS_NOTIFY
 * \brief Enables a button to send notification messages to its parent window.
 */
#define BS_NOTIFY		   0x00004000L

#define BS_FLAT			 0x00008000L
#define BS_RIGHTBUTTON	  BS_LEFTTEXT

	/** @} end of ctrl_button_styles */

	/**
	 * \defgroup ctrl_button_states States of button control
	 * @{
	 */

/**
 * \def BST_UNCHECKED
 * \brief Indicates the button is unchecked.
 */
#define BST_UNCHECKED	   0x0000

/**
 * \def BST_CHECKED
 * \brief Indicates the button is checked.
 */
#define BST_CHECKED		 0x0001

/**
 * \def BST_INDETERMINATE
 * \brief Indicates the button is grayed because 
 * the state of the button is indeterminate.
 */
#define BST_INDETERMINATE   0x0002

/**
 * \def BST_PUSHED
 * \brief Specifies the highlight state.
 */
#define BST_PUSHED		  0x0004

/**
 * \def BST_FOCUS
 * \brief Specifies the focus state.
 */
#define BST_FOCUS		   0x0008

#define BST_MARKED		  0x0010

	/** @} end of ctrl_button_states */

	/**
	 * \defgroup ctrl_button_msgs Messages of button control
	 * @{
	 */

/**
 * \def BM_GETCHECK
 * \brief Retrieves the check state of a radio button or check box.
 *
 * An application sends a BM_GETCHECK message to retrieve 
 * the check state of a radio button or check box.
 *
 * \code
 * BM_GETCHECK
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return An integer indicates whether the button is checked.
 *
 * \retval BST_UNCHECKED The button is not checked.
 * \retval BST_CHECKED The button is checked.
 * \retval BST_INDETERMINATE The button is grayed because the state of the button is indeterminate.
 *
 * \sa ctrl_button_states
 */
#define BM_GETCHECK			 0xF0F0

/**
 * \def BM_SETCHECK
 * \brief Sets the check state of a radio button or check box.
 *
 * An application sends a BM_SETCHECK message to set 
 * the check state of a radio button or check box.
 *
 * \code
 * BM_SETCHECK
 * int check_state;
 *
 * wParam = (WPARAM)check_state;
 * lParam = 0;
 * \endcode
 *
 * \param check_state The check state of button, can be one of the following values:
 *	  - BST_UNCHECKED\n
 *		Want the button to be unchecked.
 *	  - BST_CHECKED\n
 *		Want the button to be checked.
 *	  - BST_INDETERMINATE\n
 *		Want the button to be grayed if it is a three states button.
 */
#define BM_SETCHECK			 0xF0F1

/**
 * \def BM_GETSTATE
 * \brief Gets the state of a button or check box.
 *
 * An application sends a BM_GETSTATE message to 
 * determine the state of a button or check box.
 *
 * \code
 * BM_GETSTATE
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return An integer indicates the button state.
 *
 * \sa ctrl_button_states
 */
#define BM_GETSTATE			 0xF0F2

/**
 * \def BM_SETSTATE
 * \brief Sets the state of a button.
 *
 * An application sends a BM_GETSTATE message to set the state of a 
 * button.
 *
 * \code
 * BM_SETSTATE
 * int push_state;
 *
 * wParam = (WPARAM)push_state;
 * lParam = 0;
 * \endcode
 *
 * \param push_state The push state of a button, can be one of the following values:
 *	  - Zero\n
 *		Want the button to be unpushed.
 *	  - Non zero\n
 *		Want the button to be pushed.
 */
#define BM_SETSTATE			 0xF0F3

/**
 * \def BM_SETSTYLE
 * \brief Changes the style of a button.
 *
 * An application sends a BM_SETSTYLE message to change the style of a button.
 *
 * \code
 * BM_SETSTYLE
 * int button_style;
 *
 * wParam = (WPARAM)button_style;
 * lParam = 0;
 * \endcode
 *
 * \param button_style The styles of a button:
 *
 * \sa ctrl_button_styles
 */
#define BM_SETSTYLE			 0xF0F4

/**
 * \def BM_CLICK
 * \brief Simulates the user clicking a button.
 *
 * An application sends a BM_CLICK message to simulate the user clicking a button.
 *
 * \code
 * BM_CLICK
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 */
#define BM_CLICK				0xF0F5

/**
 * \def BM_GETIMAGE
 * \brief Retrieves the handle to the image.
 *
 * An application sends a BM_GETIMAGE message to 
 * retrieve a handle to the image (icon or bitmap) associated with the button.
 *
 * \code
 * BM_GETIMAGE
 * int image_type;
 *
 * wParam = (WPARAM)image_type;
 * lParam = 0;
 * \endcode
 *
 * \param image_type The type of a button image, can be one of the following values:
 *	  - BM_IMAGE_BITMAP\n
 *		Bitmap of a button.
 *	  - BM_IMAGE_ICON\n
 *		Icon of a button.
 *
 * \return A handle of the bitmap or icon of a button.
 */
#define BM_GETIMAGE			 0xF0F6

#define BM_IMAGE_BITMAP		 1
#define BM_IMAGE_ICON		   2
	
/**
 * \def BM_SETIMAGE
 * \brief Associates a new image (icon or bitmap) with the button.
 *
 * An application sends a BM_SETIMAGE message to 
 * associate a new image (icon or bitmap) with the button.
 *
 * Please use BM_IMAGE_BITMAP or BM_IMAGE_ICON as the first parameter of the message 
 * to indicate the type of button control image:
 *  - BM_IMAGE_BITMAP\n
 *		  Specifies the type of image to associate with the button to be a bitmap.
 *  - BM_IMAGE_ICON\n
 *		  Specifies the type of image to associate with the button to be an icon.
 */
#define BM_SETIMAGE			 0xF0F7

	/** @} end of ctrl_button_msgs */
	
	/**
	 * \defgroup ctrl_button_ncs Notification codes of button control
	 * @{
	 */

/**
 * \def BN_CLICKED
 * \brief The BN_CLICKED notification message is sent when the user clicks a button.
 */
#define BN_CLICKED		  0

#define BN_PAINT			1
#define BN_HILITE		   2
#define BN_UNHILITE		 3
#define BN_DISABLE		  4
#define BN_DOUBLECLICKED	5

#define BN_ANTICLOCK_ACT	10
#define BN_CLOCK_ACT		11

/**
 * \def BN_PUSHED
 * \brief The BN_PUSHED notification message is sent when the user pushes a button.
 */
#define BN_PUSHED		   BN_HILITE

/**
 * \def BN_UNPUSHED
 * \brief The BN_UNPUSHED notification message is sent when the user unpushes a button.
 */
#define BN_UNPUSHED		 BN_UNHILITE

/**
 * \def BN_DBLCLK
 * \brief The BN_DBLCLK notification message is sent when the user double-clicks a button.
 */
#define BN_DBLCLK		   BN_DOUBLECLICKED

/**
 * \def BN_SETFOCUS
 * \brief The BN_SETFOCUS notification message is sent when a button receives the keyboard focus.
 */
#define BN_SETFOCUS		 6

/**
 * \def BN_KILLFOCUS
 * \brief The BN_KILLFOCUS notification message is sent when a button loses the keyboard focus.
 */
#define BN_KILLFOCUS		7

	/** @} end of ctrl_button_ncs */

	/** @} end of ctrl_button */

#endif /* _CTRL_BUTTON */

/****** Edit Control ******************************************************/
#if 0
//#ifdef _CTRL_EDIT
	/**
	 * \defgroup ctrl_edit Edit/MEdit control
	 *
	 * \bug You can not pass caption argument for multi-line edit control
	 *	  when you create it, just use null string:
	 *
	 * \code
	 *  CreateWindowEx (CTRL_MEDIT, ..., "", ...);
	 * \endcode
	 *
	 * @{
	 */

/**
 * \def CTRL_SLEDIT
 * \brief The class name of single-line editor box.
 */
#define CTRL_SLEDIT		 ("sledit")
#define CTRL_EDIT		   "edit"

/**
 * \def CTRL_MLEDIT
 * \brief The class name of multiple-line editor box.
 */
#define CTRL_MLEDIT		 ("mledit")
#define CTRL_MEDIT		  ("medit")

	/**
	 * \defgroup ctrl_edit_styles Styles of edit control
	 * @{
	 */

/**
 * \def ES_LEFT
 * \brief Left-aligns text.
 */
#define ES_LEFT			 0x00000000L

#define ES_CENTER		   0x00000001L
#define ES_RIGHT			0x00000002L
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

#define ES_AUTOVSCROLL	  0x00000040L
#define ES_AUTOHSCROLL	  0x00000080L
#define ES_NOHIDESEL		0x00000100L
#define ES_OEMCONVERT	   0x00000400L

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
#define ES_AUTOWRAP			0x00002000L

	/** @} end of ctrl_edit_styles */

	/**
	 * \defgroup ctrl_edit_msgs Messages of edit control
	 * @{
	 */

#define EM_GETSEL			   0xF0B0
#define EM_SETSEL			   0xF0B1
#define EM_GETRECT			  0xF0B2
#define EM_SETRECT			  0xF0B3
#define EM_SETRECTNP			0xF0B4
#define EM_SCROLL			   0xF0B5
#define EM_LINESCROLL		   0xF0B6
#define EM_SCROLLCARET		  0xF0B7
#define EM_GETMODIFY			0xF0B8
#define EM_SETMODIFY			0xF0B9
#define EM_GETLINECOUNT		 0xF0BA
#define EM_LINEINDEX			0xF0BB
#define EM_SETHANDLE			0xF0BC
#define EM_GETHANDLE			0xF0BD
#define EM_GETTHUMB			 0xF0BE
#define EM_LINELENGTH		   0xF0C1
#define EM_REPLACESEL		   0xF0C2
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
 * \param newLimit The new text limit of an edit control:
 */
#define EM_LIMITTEXT			0xF0C5

#define EM_CANUNDO			  0xF0C6
#define EM_UNDO				 0xF0C7
#define EM_FMTLINES			 0xF0C8
#define EM_LINEFROMCHAR		 0xF0C9
#define EM_SETTABSTOPS		  0xF0CB

/**
 * \def EM_SETPASSWORDCHAR
 * \brief Defines the character that edit control uses in conjunction with 
 * the ES_PASSWORD style.
 *
 * \code
 * EM_SETPASSWORDCHAR
 * int passwdChar;
 *
 * wParam = (WPARAM)passwdChar;
 * lParam = 0;
 * \endcode
 */
#define EM_SETPASSWORDCHAR	  0xF0CC

#define EM_EMPTYUNDOBUFFER	  0xF0CD
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

#define EM_SETWORDBREAKPROC	 0xF0D0
#define EM_GETWORDBREAKPROC	 0xF0D1

/**
 * \def EM_GETPASSWORDCHAR
 * \brief Returns the character that edit controls uses in conjunction with 
 * the ES_PASSWORD style.
 *
 * \code
 * EM_GETPASSWORDCHAR
 * int *passwdchar;
 *
 * wParam = 0;
 * lParam = (LPARAM)passwdchar;
 * \endcode
 *
 */
#define EM_GETPASSWORDCHAR	  0xF0D2

#define EM_SETMARGINS		   0xF0D3
#define EM_GETMARGINS		   0xF0D4
#define EM_SETLIMITTEXT		 EM_LIMITTEXT
#define EM_GETMARGINS		   0xF0D4
#define EM_GETLIMITTEXT		 0xF0D5
#define EM_POSFROMCHAR		  0xF0D6
#define EM_CHARFROMPOS		  0xF0D7
#define EM_SETIMESTATUS		 0xF0D8
#define EM_GETIMESTATUS		 0xF0D9
#define MEM_SCROLLCHANGE		0xF0DB
#define MED_STATE_YES		   0x0
#define MED_STATE_NOUP		  0x1
#define MED_STATE_NODN		  0x2
#define MED_STATE_NO			0x3

	/** @} end of ctrl_edit_msgs */

	/**
	 * \defgroup ctrl_edit_ncs Notification codes of edit control
	 * @{
	 */

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
 * \brief Notifies that the text is altered.
 *
 * An edit control sends the EN_CHANGE notification code when the user takes 
 * an action that may have altered text in an edit control.
 */
#define EN_CHANGE		   0x0300

#define EN_UPDATE		   0x0400
#define EN_ERRSPACE		 0x0500

/**
 * \def EN_MAXTEXT
 * \brief Notifies reach of maximum text limitation.
 *
 * The EN_MAXTEXT notification message is sent when the current text 
 * insertion has exceeded the specified number of characters for the edit control.
 */
#define EN_MAXTEXT		  0x0501

#define EN_HSCROLL		  0x0601
#define EN_VSCROLL		  0x0602

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

#endif /* _CTRL_EDIT */

/****** Listbox Control ******************************************************/
#ifdef _CTRL_LISTBOX

	/**
	 * \defgroup ctrl_listbox ListBox control
	 * @{
	 */

/**
 * \def CTRL_LISTBOX
 * \brief The class name of listbox control.
 */
#define CTRL_LISTBOX		"listbox"

/* ÎªÁË±£´æ±»ÏÂÀ´¿òÕÚ×¡µÄÇøÓò,±ØÐë¶¨ÒåÒ»¸öbuffer;  */
#define LB_DROPREC_W	  1 // (16*10)  // µ¥Î», ÏóËØ; 10¸ö16x16µÄ×Ö·û;
#define LB_DROPREC_H	  1 // (20*10)  // µ¥Î», ÏóËØ; 10ÐÐ×Ö·û; Ã¿ÐÐ20¸öÏóËØ.

/* Listbox return value */
#define LB_OKAY				 0
#define LB_ERR				  (-1)
#define LB_ERRSPACE			 (-2)

#define CMFLAG_BLANK		0
#define CMFLAG_CHECKED	  1
#define CMFLAG_PARTCHECKED  2

/** Structrue of the listbox item info */
typedef struct _LISTBOXITEMINFO
{
	/** Insert position of the item */
	int	 insPos;		 /* insert position */
	/** Item string */
	char   *string;		 /* item string */
	/** 
	 * Check mark flag, can be one of the followings:
	 * - CMFLAG_BLANK
	 *   The item is blank.
	 * - CMFLAG_CHECKED
	 *   The item is checked.
	 * - CMFLAG_PARTCHECKED
	 *   The item is partly checked.
	 */
	int	 cmFlag;		 /* check mark flag */
	/** Handle to the icon of the item */
	HICON   hIcon;		  /* handle to icon */
} LISTBOXITEMINFO;
/** 
 * \var typedef LISTBOXITEMINFO* PLISTBOXITEMINFO;
 * \brief Data type of the pointer to a LISTBOXITEMINFO.
 */
typedef LISTBOXITEMINFO* PLISTBOXITEMINFO;

	/**
	 * \defgroup ctrl_listbox_styles Styles of listbox control
	 * @{
	 */

/**
 * \def LBS_NOTIFY
 * \brief Notifies the parent window.
 *
 * Causes the list box to notify the list box parent window 
 * with a notification message when the user clicks or doubleclicks an item.
 */
#define LBS_NOTIFY			  0x0001L

/**
 * \def LBS_SORT
 * \brief Sorts strings alphabetically.
 *
 * Causes the list box to sort strings alphabetically that are 
 * added to the list box with an LB_ADDSTRING message.
 */
#define LBS_SORT				0x0002L

#define LBS_DROPDOWN			0x0004L

/**
 * \def LBS_MULTIPLESEL
 * \brief Causes the list box to allow the user to select multiple items.
 */
#define LBS_MULTIPLESEL		 0x0008L

/**
 * \def LBS_CHECKBOX
 * \brief Displays a check box in an item.
 */
#define LBS_CHECKBOX			0x1000L

/**
 * \def LBS_USEICON
 * \brief Displays an icon in an item.
 */
#define LBS_USEICON			 0x2000L

/**
 * \def LBS_AUTOCHECK
 * \brief
 */
#define LBS_AUTOCHECK		   0x4000L

#define LBS_AUTOCHECKBOX		0x5000L

#define LBS_OWNERDRAWFIXED	  0x0010L
#define LBS_OWNERDRAWVARIABLE   0x0020L
#define LBS_USETABSTOPS		 0x0080L
#define LBS_MULTICOLUMN		 0x0200L
#define LBS_WANTKEYBOARDINPUT   0x0400L
#define LBS_NOREDRAW			0x0004L
#define LBS_HASSTRINGS		  0x0040L
#define LBS_NOINTEGRALHEIGHT	0x0100L
#define LBS_EXTENDEDSEL		 0x0800L

	/** @} end of ctrl_listbox_styles */

	/**
	 * \defgroup ctrl_listbox_msgs Messages of listbox control
	 * @{
	 */

/**
 * \def LB_ADDSTRING
 * \brief Appends the specified string.
 *
 * An application sends an LB_ADDSTRING message to add the string 
 * specified in the lParam parameter to a list box.
 *
 * \code
 * LB_ADDSTRING
 * PLISTBOXITEMINFO plbii;
 *
 * wParam = 0;
 * lParam = (LPARAM)plbii;
 * \endcode
 *
 * \param plbii Pointer to the listbox item info to be added.
 */
#define LB_ADDSTRING			0xF180

/**
 * \def LB_INSERTSTRING
 * \brief Inserts an item to the list box.
 *
 * An application sends an LB_INSERTSTRING message to insert an item 
 * into a list box. Unlike LB_ADDSTRING message, the LB_INSERTSTRING
 * message do not cause the list to be sorted.
 *
 * \code
 * LB_INSERTSTRING
 * int index;
 * PLISTBOXITEMINFO plbii;
 * char* string;
 *
 * wParam = (WPARAM)index;
 * lParam = (LPARAM)plbii;
 * or lParam = (LPARAM)string;
 * \endcode
 * 
 * \param index Specifies the index of the position at which to insert the item.
 * \param plbii Pointer to the listbox item info to be inserted.
 * \param string Pointer to the string to be inserted.
 */
#define LB_INSERTSTRING		 0xF181

/**
 * \def LB_DELETESTRING
 * \brief Removes from the list box a specified string or data item.
 *
 * An application sends an LB_DELETESTRING message to a list box 
 * to remove from the list box a string or data item specified in 
 * the wParam parameter.
 *
 * \code
 * LB_DELETESTRING
 * int delete;
 *
 * wParam = (WPARAM)delete;
 * lParam = 0;
 * \endcode
 *
 * \param delete The index of the listbox item to be deleted.
 */
#define LB_DELETESTRING		 0xF182

#define LB_SELITEMRANGEEX	   0xF183

/**
 * \def LB_RESETCONTENT
 * \brief Removes the contents of a list box.
 *
 * An application sends an LB_RESETCONTENT message to remove the contents 
 * of a list box.
 *
 * \code
 * LB_RESETCONTENT
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 */
#define LB_RESETCONTENT		 0xF184

/**
 * \def LB_SETSEL
 * \brief Selects an item in a multiple-selection list box.
 *
 * An application sends an LB_SETSEL message to select an item 
 * in a multiple-selection list box and scroll it into view if necessary.
 *
 * \code
 * LB_SETSEL
 * int index, sel
 *
 * wParam = (WPARAM)sel;
 * lParam = (LPARAM)index;
 * \endcode
 *
 * \param sel Indicates the changes to be made to the listbox item, can be one of the followings.
 *	 - -1\n
 *	 If the item has been selected, makes it unselected, vice versa.
 *	 - 0\n
 *	 Makes the item unselected. 
 *	 - other\n
 *	 Makes the item selected. 
 * \param index The index of the item.
 */
#define LB_SETSEL			   0xF185

/**
 * \def LB_SETCURSEL
 * \brief Selects an item.
 *
 * An application sends an LB_SETCURSEL message to a list box to 
 * select an item and scroll it into view, if necessary.
 *
 * \code
 * LB_SETCURSEL
 * int cursel;
 *
 * wParam = (WPARAM)cursel;
 * lParam = 0;
 * \endcode
 *
 * \param cursel The index of the item to be selected and hilighted.
 *
 * \return The old index of the item selected.
 */
#define LB_SETCURSEL			0xF186

/**
 * \def LB_GETSEL
 * \brief Gets the selected state for an specified item.
 *
 * An application sends an LB_GETSEL message to a list box to get the selected 
 * state for an item specified in the wParam parameter.
 *
 * \code
 * LB_GETSEL
 * int index;
 *
 * wParam = (WPARAM)index;
 * lParam = 0;
 * \endcode
 *
 * \param index The index of the specified item.
 *
 * \return The state of the specified item.
 */
#define LB_GETSEL			   0xF187

/**
 * \def LB_GETCURSEL
 * \brief Gets the index of the currently selected item.
 *
 * An application sends an LB_GETCURSEL message to a list box to get the index of 
 * the currently selected item, if there is one, in a single-selection list box.
 *
 * \code
 * LB_GETCURSEL
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The index of the currently selected item.
 */
#define LB_GETCURSEL			0xF188

/**
 * \def LB_GETTEXT
 * \brief Retrieves a string.
 *
 * An application sends an LB_GETTEXT message to a list box to retrieve a string 
 * from it.
 *
 * \code
 * LB_GETTEXT
 * int index;
 * char *string;
 *
 * wParam = (WPARAM)index;
 * lParam = (LPARAM)string;
 * \endcode
 *
 * \param index The index of the selected item.
 * \param string Pointer to the string buffer.
 */
#define LB_GETTEXT			  0xF189

/**
 * \def LB_GETTEXTLEN
 * \brief Gets the length of a string specified.
 *
 * An application sends an LB_GETTEXTLEN message to a list box to get the length 
 * of a string specified in the wParam parameter.
 *
 * \code
 * LB_GETTEXTLEN
 * int index;
 *
 * wParam = (WPARAM)index;
 * lParam = 0;
 * \endcode
 *
 * \param index The index of the specified item.
 *
 * \return The length of the string.
 */
#define LB_GETTEXTLEN		   0xF18A

/**
 * \def LB_GETCOUNT
 * \brief Gets the number of items in the list box.
 *
 * An application sends an LB_GETCOUNT message to a list box to get the number 
 * of items in the list box.
 *
 * \code
 * LB_GETCOUNT
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The number of items in the listbox.
 */
#define LB_GETCOUNT			 0xF18B

#define LB_SELECTSTRING		 0xF18C

#define LB_DIR				  0xF18D

/**
 * \def LB_GETTOPINDEX
 * \brief Gets the index to the first visible item in the list box.
 *
 * An application sends an LB_GETTOPINDEX message to get the index to the first 
 * visible item in the list box.Initially, the first visible item is item 0, but 
 * this changes as the list box is scrolled. For multiple-column list boxes, the 
 * first visible item is the top-left item.
 *
 * \code
 * LB_GETTOPINDEX
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The index of the first visible item in the listbox.
 */
#define LB_GETTOPINDEX		  0xF18E

/**
 * \def LB_FINDSTRING
 * \brief Searchs a specified string.
 *
 * An application sends an LB_FINDSTRING message to search a list box for an item 
 * that begins with the characters specified in the lParam parameter. The wParam 
 * parameter specifies the zero-based index of the item before the first item to 
 * be searched; The lParam parameter specifies a pointer to a null-terminated 
 * string that contains the prefix to search for.
 *
 * \code
 * LB_FINDSTRING
 * int index;
 * char *string;
 *
 * wParam = (WPARAM)index;
 * lParam = (LPARAM)string;
 * \endcode
 *
 * \param index The index of the item to be searched.
 * \param string The string of the item to be searched.
 *
 * \return The index of the matched item.
 */
#define LB_FINDSTRING		   0xF18F

/**
 * \def LB_GETSELCOUNT
 * \brief Gets the number of selected items in a multiple-selection list box.
 *
 * An application sends an LB_GETSELCOUNT message to a list box to get the number 
 * of selected items in a multiple-selection list box.
 *
 * \code
 * LB_GETSELCOUNT
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The number of selected items in the listbox.
 */
#define LB_GETSELCOUNT		  0xF190

/**
 * \def LB_GETSELITEMS
 * \brief Gets the numbers of selected items.
 *
 * An application sends an LB_GETSELITEMS message to a list box to fill a buffer 
 * with an array of integers that specify the item numbers of selected items in 
 * a multiple-selection list box.
 *
 * \code
 * LB_GETSELITEMS
 * int nItem;
 * int *pInt;
 *
 * wParam = (WPARAM)nItem;
 * lParam = (LPARAM)pInt;
 * \endcode
 *
 * \param nItem The maximum integer numbers wanted.
 * \param pInt The buffer of an array of integers.
 *
 * \return The number of selected items.
 */
#define LB_GETSELITEMS		  0xF191

#define LB_SETTABSTOPS		  0xF192
#define LB_GETHORIZONTALEXTENT  0xF193
#define LB_SETHORIZONTALEXTENT  0xF194
#define LB_SETCOLUMNWIDTH	   0xF195
#define LB_ADDFILE			  0xF196

/**
 * \def LB_SETTOPINDEX
 * \brief Ensures that a particular item in it is visible.
 *
 * An application sends an LB_SETTOPINDEX message to a list box to ensure that a 
 * particular item in it is visible. The item is specified in the wParam parameter. 
 * The list box scrolls so that either the specified item appears at the top of 
 * the list box or the maximum scroll range has been reached.
 * 
 * \code
 * LB_SETTOPINDEX
 * int index;
 *
 * wParam = (WPARAM)index;
 * lParam = 0;
 * \endcode
 *
 * \param index The index of the particular item to be set.
 */
#define LB_SETTOPINDEX		  0xF197

/**
 * \def LB_GETITEMRECT
 * \brief Retrieves the dimensions of the rectangle.
 *
 * An application sends an LB_GETITEMRECT message to a list box to retrieve 
 * the dimensions of the rectangle that bounds an item as it is currently 
 * displayed in the list box window. The item is specified in the wParam 
 * parameter, and a pointer to a RECT structure is given in the lParam parameter.
 *
 * \code
 * LB_GETITEMRECT
 * int index;
 * RECT *rcItem;
 *
 * wParam = (WPARAM)index;
 * lParam = (LPARAM)rcItem;
 * \endcode
 *
 * \param index The index of the specified item.
 * \param rcItem Pointer to the buffer used for storing the item rect;
 */
#define LB_GETITEMRECT		  0xF198

/**
 * \def LB_GETITEMDATA
 * \brief Gets the 32-bit data value the list box has stored.
 * 
 * An application sends an LB_GETITEMDATA message to a list box to get the 
 * 32-bit data value the list box has stored for the item specified in the 
 * wParam parameter; By default this is zero. An application must set the 
 * item data value by sending an LB_SETITEMDATA message to the list box for 
 * this value to have meaning.
 *
 * \code
 * LB_GETITEMDATA
 * int index;
 * PLISTBOXITEMINFO plbii;
 *
 * wParam = (WPARAM)index;
 * lParam = (LPARAM)plbii;
 * \endcode
 *
 * \param index The index of the specified item.
 * \param plbii Pointer to the buffer used for storing the item info of the 
 *		 specified item;
 */
#define LB_GETITEMDATA		  0xF199

/**
 * \def LB_SETITEMDATA
 * \brief Associates a 32-bit data value with an item.
 * 
 * An application sends an LB_SETITEMDATA message to associate a 32-bit data 
 * value specified in the lParam parameter with an item in the list box that 
 * is specified in the wParam parameter.
 *
 * \code
 * LB_SETITEMDATA
 * int index;
 * PLISTBOXITEMINFO plbii;
 *
 * wParam = (WPARAM)index;
 * lParam = (LPARAM)plbii;
 * \endcode
 *
 * \param index The index of the specified item.
 * \param plbii Pointer to the buffer used for setting the item info of the 
 *		 specified item;
 */
#define LB_SETITEMDATA		  0xF19A

#define LB_SELITEMRANGE		 0xF19B
#define LB_SETANCHORINDEX	   0xF19C
#define LB_GETANCHORINDEX	   0xF19D

/**
 * \def LB_SETCARETINDEX
 * \brief Sets the focus rectangle to the item at the specified index.
 * 
 * An application sends an LB_SETCARETINDEX message to set the focus rectangle 
 * to the item at the specified index in a multiple-selection list box.
 *
 * \code
 * LB_SETCARETINDEX
 * int index;
 *
 * wParam = (WPARAM)index;
 * lParam = 0;
 * \endcode
 */
#define LB_SETCARETINDEX		0xF19E

/**
 * \def LB_GETCARETINDEX
 * \brief Determines the index of the item that has the focus rectangle.
 * 
 * An application sends an LB_GETCARETINDEX message to a list box to determine 
 * the index of the item that has the focus rectangle in a multiple-selection 
 * list box.
 *
 * \code
 * LB_GETCARETINDEX
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The index of the item that has the focus rectangle.
 */
#define LB_GETCARETINDEX		0xF19F

/**
 * \def LB_SETITEMHEIGHT
 * \brief Sets the height of an item or all the items.
 * 
 * An application sends an LB_SETITEMHEIGHT message to set the height of an 
 * item or all the items in a list box.
 *
 * \code
 * LB_SETITEMHEIGHT
 * int itemHeight;
 *
 * wParam = 0;
 * lParam = (LPARAM)itemHeight;
 * \endcode
 *
 * \param itemHeight New height of an item or all the items.
 */
#define LB_SETITEMHEIGHT		0xF1A0

/**
 * \def LB_GETITEMHEIGHT
 * \brief Gets the height in pixels of an item specified in the wParam parameter.
 * 
 * An application sends an LB_GETITEMHEIGHT message to a list box to get the 
 * height in pixels of an item specified in the wParam parameter.
 *
 * \code
 * LB_GETITEMHEIGHT
 *
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The height of an item of the listbox.
 */
#define LB_GETITEMHEIGHT		0xF1A1

/**
 * \def LB_FINDSTRINGEXACT
 * \brief Searchs for an item that matches the characters specified.
 * 
 * An application sends an LB_FINDSTRINGEXACT message to a list box to search 
 * it for an item that matches the characters specified in the lParam parameter.
 *
 * \code
 * LB_FINDSTRINGEXACT
 * int index;
 * char *string;
 *
 * wParam = (WPARAM)index;
 * lParam = (LPARAM)string;
 * \endcode
 *
 * \param index The index of the specified item.
 * \param string The string of the item to be searched for.
 *
 * \return The index of the found item.
 */
#define LB_FINDSTRINGEXACT	  0xF1A2

#define LB_SETLOCALE			0xF1A5
#define LB_GETLOCALE			0xF1A6
#define LB_SETCOUNT			 0xF1A7
#define LB_INITSTORAGE		  0xF1A8
#define LB_ITEMFROMPOINT		0xF1A9

/**
 * \def LB_SETTEXT
 * \brief Sets text of the specified item.
 *
 * \code
 * LB_SETTEXT
 * int index;
 * char *string;
 *
 * wParam = (WPARAM)index;
 * lParam = (LPARAM)string;
 * \endcode
 *
 * \param index The index of the specified item.
 * \param string The string of the item to be set.
 */
#define LB_SETTEXT			  0xF1AA

/**
 * \def LB_GETCHECKMARK
 * \brief Gets check mark status of an item.
 *
 * \code
 * LB_GETCHECKMARK
 * int index;
 *
 * wParam = (WPARAM)index;
 * lParam = 0;
 * \endcode
 *
 * \param index The index of the specified item.
 *
 * \return The check mark status of specified item.
 */
#define LB_GETCHECKMARK		 0xF1AB

/**
 * \def LB_SETCHECKMARK
 * \brief Sets check mark status of an item.
 *
 * \code
 * LB_SETCHECKMARK
 * int index, status;
 *
 * wParam = (WPARAM)index;
 * lParam = (LPARAM)status;
 * \endcode
 *
 * \param index The index of the specified item.
 * \param status The new check mark status, can be one of the followings.
 *	 - CMFLAG_CHECKED\n
 *	 The item is checked.
 *	 - CMFLAG_PARTCHECKED\n
 *	 The item is partly checked.
 *
 * \return The check mark status of specified item.
 */
#define LB_SETCHECKMARK		 0xF1AC

/**
 * \def LB_GETITEMADDDATA
 * \brief Gets additional data stored in an item.
 *
 * \code
 * LB_GETITEMADDDATA
 * int index;
 *
 * wParam = (WPARAM)index;
 * lParam = 0;
 * \endcode
 *
 * \param index The index of the specified item.
 *
 * \return Pointer to the buffer storing the additional data.
 */
#define LB_GETITEMADDDATA	   0xF1AD

/**
 * \def LB_SETITEMADDDATA
 * \brief Stores additional data into an item.
 *
 * \code
 * LB_SETITEMADDDATA
 * int index;
 * DWORD addData;
 *
 * wParam = (WPARAM)index;
 * lParam = (LPARAM)addData;
 * \endcode
 *
 * \param index The index of the specified item.
 * \param addData Pointer to the buffer storing the additional data.
 *
 */
#define LB_SETITEMADDDATA	   0xF1AE

#define LB_MSGMAX			   0xF1B0

	/** @} end of ctrl_listbox_msgs */

	/**
	 * \defgroup ctrl_listbox_ncs Notification codes of listbox control
	 * @{
	 */

/**
 * \def LBN_ERRSPACE
 * \brief Indicates that memory is not enough.
 * 
 * A list box sends an LBN_ERRSPACE notification message to its parent window 
 * when it cannot allocate enough memory to complete the current operation.
 */
#define LBN_ERRSPACE			(-2)

/**
 * \def LBN_SELCHANGE
 * \brief Indicates change due to mouse or keyboard user input.
 * 
 * A list box created with the LBS_NOTIFY style sends an LBN_SELCHANGE 
 * notification message to its parent window when the selection is about to 
 * change due to mouse or keyboard user input.
 */
#define LBN_SELCHANGE		   1

/**
 * \def LBN_DBLCLK
 * \brief Indicates double click on an item.
 * 
 * A list box created with the LBS_NOTIFY style sends an LBN_DBLCLK notification 
 * message to its parent window when the user double-clicks a string in it.
 */
#define LBN_DBLCLK			  2

/**
 * \def LBN_SELCANCEL
 * \brief Indicates cancel of the selection in the list box.
 * 
 * A list box created with the LBS_NOTIFY style sends an LBN_SELCANCEL 
 * notification message to its parent window when the user cancels the selection 
 * in the list box.
 */
#define LBN_SELCANCEL		   3

/**
 * \def LBN_SETFOCUS
 * \brief Indicates gain of input focus.
 * 
 * A list box sends an LBN_SETFOCUS notification message to its parent window 
 * when the list box gains the input focus.
 */
#define LBN_SETFOCUS			4

/**
 * \def LBN_KILLFOCUS
 * \brief Indicates loss of input focus.
 * 
 * A list box sends an LBN_KILLFOCUS notification message to its parent window 
 * when the list box loses the input focus.
 */
#define LBN_KILLFOCUS		   5

/**
 * \def LBN_CLICKCHECKMARK
 * \brief Indicates click on the check mark.
 */
#define LBN_CLICKCHECKMARK	  6

/**
 * \def LBN_CLICKED
 * \brief Indicates click on the string.
 */
#define LBN_CLICKED			 7

/**
 * \def LBN_ENTER
 * \brief
 */
#define LBN_ENTER			   8

#define LBN_CHANGED			 9

	/** @} end of ctrl_listbox_ncs */

	/**
	 * \defgroup ctrl_listbox_states States of listbox control
	 * @{
	 */
	#define LBST_MARKED	 0x0001	 /* ¿Ø¼þ±»±ê¼Ç; ½¹µã¿Ø¼þ	   */
	#define LBST_1CLICK	 0x0002	 /* ÓÃ»§°´ÏÂ1´Î,¿ÉÒÔ½øÐÐ²Ù×÷.  */
	#define LBST_2CLICK	 0x0004	 /* ÓÃ»§°´ÏÂ2´Î,ÍË³ö²Ù×÷.	  */
	#define LBST_TOP		0x0010	 /* ÓÃ»§²Ù×÷, ÏòÉÏ·­¶¯.		*/
	#define LBST_BOTTOM	 0x0020	 /* ÓÃ»§²Ù×÷, ÏòÏÂ·­¶¯.		*/

	/** @} end of ctrl_listbox_states */


	/** @} end of ctrl_listbox */

#endif /* _CTRL_LISTBOX */

/****** Spinbox Control ******************************************************/
#ifdef _CTRL_SPINBOX
	/**
	 * \defgroup ctrl_spinbox Spinbox control
	 * @{
	 */

/**
 * \def CTRL_SPINBOX
 * \brief The class name of spinbox control.
 */
#define CTRL_SPINBOX		 "spinbox"

	/**
	 * \defgroup ctrl_spinbox_styles Styles of spinbox control
	 * @{
	 */

	 
	/** @} end of ctrl_spinbox_styles */
	
	/**
	 * \defgroup ctrl_spinbox_states States of spinbox control
	 * @{
	 */
	#define SBST_MARKED	 0x0001

	/** @} end of ctrl_spinbox_states */
	
	/**
	 * \defgroup ctrl_spinbox_msgs Messages of spinbox control
	 * @{
	 */
	 
	/** @} end of ctrl_spinbox_msgs */

	/**
	 * \defgroup ctrl_spinbox_ncs Notification codes of spinbox control
	 * @{
	 */
	#define SBN_CHANGED	   1	// Êý¾ÝÏî¸Ä±äÁË.
	#define SBN_SETFOCUS	  2	// »ñµÃ½¹µã
	#define SBN_KILLFOCUS	 3	// Ê§È¥½¹µã.
	#define SBN_DATACHANGING  4	// Êý¾Ý·¢ÉúÁË¸Ä±ä£

	#define SBN_ENTER		 5	// ¸Õ¸Õ½øÈë¿Ø¼þ´¦Àí£»Ò²¾ÍÊÇµÚÒ»´Î¡®°´¼ü¶¯×÷¡¯£»
	/** @} end of ctrl_spinbox_ncs */
	
	/** @} end of ctrl_spinbox */

#endif /* _CTRL_SPINBOX */

/****** Checkbox Control ******************************************************/
#ifdef _CTRL_CHECKBOX
	/**
	 * \defgroup ctrl_checkbox Checkbox control
	 * @{
	 */

/**
 * \def CTRL_CHECKBOX
 * \brief The class name of checkbox control.
 */
#define CTRL_CHECKBOX		 "checkbox"

	/**
	 * \defgroup ctrl_checkbox_styles Styles of checkbox control
	 * @{
	 */

	 
	/** @} end of ctrl_checkbox_styles */
	
	/**
	 * \defgroup ctrl_checkbox_msgs Messages of checkbox control
	 * @{
	 */
	 
	/** @} end of ctrl_checkbox_msgs */

	/**
	 * \defgroup ctrl_checkbox_ncs Notification codes of checkbox control
	 * @{
	 */
	 
	/** @} end of ctrl_checkbox_ncs */
	
	/** @} end of ctrl_checkbox */

#endif /* _CTRL_CHECKBOX */

#ifdef _CTRL_HOTKEY
/**
 * \def CTRL_HOTKEY
 * \brief The class name of hotkey control.
 */
#define CTRL_HOTKEY		 "hotkey"

	/**
	 * \defgroup ctrl_hotkey_styles Styles of hotkey control
	 * @{
	 */
	#define HKS_CENTER	  0x00000001L
	 
	/** @} end of ctrl_hotkey_styles */
	
	/**
	 * \defgroup ctrl_hotkey_states States of button control
	 * @{
	 */
	#define HKST_MARKED	 0x0001
	#define HKST_CHANGING   0x0002

	/** @} end of ctrl_hotkey_states */
	 
	/**
	 * \defgroup ctrl_hotkey_msgs Messages of hotkey control
	 * @{
	 */
	 
	/** @} end of ctrl_hotkey_msgs */

	/**
	 * \defgroup ctrl_hotkey_ncs Notification codes of hotkey control
	 * @{
	 */
	#define HKN_CHANGED	 1	// Ñ¡Ïî¸Ä±äÁË.
	#define HKN_SETFOCUS	2	// »ñµÃ½¹µã
	#define HKN_KILLFOCUS   3	// Ê§È¥½¹µã.
	#define HKN_CLICKED	 4	// Ñ¡Ïî¸Ä±äÁË.
	/** @} end of ctrl_hotkey_ncs */
	
	/** @} end of ctrl_hotkey */

#endif /* _CTRL_HOTKEY */

#ifdef _CTRL_GROUPBOX
#define CTRL_GROUPBOX		"groupbox"
#define GRB_BORDER			0x00000001L
#define GRB_TYPEMASK		0x0000000FL
	
#define GRBT_MARKED		 0x0001
#define GRBT_PRESSED	 0x0002
	
#define GRBN_CLICKED	1
#define GRBN_KEY_LEFT	2
#define GRBN_KEY_RIGHT	3
#define GRBN_PRESSED	4

#define	GRB_SCROLL		0x00000010L
#endif

#ifdef _CTRL_SCROLLBAR

#define CTRL_SCROLL	 "scroll"
#define SCR_MARKED	  0x00000100L // key paused
#define SCR_HOLD		0x00010000L // touch hold
#define SCR_SETFOCUS	1 // 
#define SCR_KILLFOCUS   2 //
#define SCR_LEFT		3 //
#define SCR_RIGHT	   4 //
#define SCR_CHANGE	  5 // change

#endif

	/** @} end of controls */

#endif
