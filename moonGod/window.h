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
#if !defined(_WINDOW_H)
#define	  _WINDOW_H

#include "ctrlbas.h"

/* definitions of common messages. */
#define MSG_SYNCMSG		 0x0000
#define MSG_NULLMSG		 0x0000

	/**
	 * \defgroup mouse_msgs Mouse event messages
	 * @{
	 */

	/* Group 1 from 0x0001 to 0x000F, the mouse messages. */
#define MSG_FIRSTMOUSEMSG   0x0001

#define MSG_LASTMOUSEMSG	0x000F

	/** @} end of mouse_msgs */

	/**
	 * \defgroup key_msgs Key event messages
	 * @{
	 */

	/* Group 2 from 0x0010 to 0x001F, the key messages. */
#define MSG_FIRSTKEYMSG	 0x0010

#if _ENB_TOUCH
#define MSG_TOUCHENCODER	0x0011   /* 触摸屏 */
#endif

#define MSG_KEYENCODER	  0x001E   /* 编码器. eric, 2006.02.05 */

#define MSG_LASTKEYMSG	  0x001F

	/** @} end of key_msgs */
	
	/**
	 * \defgroup post_event_msgs Post mouse/key event messages
	 * @{
	 */

	/* Group 3 from 0x0020 to 0x005F, the post mouse/key event messages. */
#define MSG_FIRSTPOSTMSG	0x0020

#define MSG_CHANGESIZE	  0x0022

/**
 * \def MSG_SIZECHANGING
 * \brief Indicates the size of the window is being changed.
 *
 * This message is sent to the window when the size is being changed.
 * If you want to control the actual position and size of the window when 
 * the size is being changed (this may be caused by MoveWindow or other functions), 
 * you should handle this message, and return the actual
 * position and size of the window through the second parameter.
 *
 * \code
 * MSG_SIZECHANGING
 * const RECT* rcExpect = (const RECT*)wParam;
 * RECT* rcResult = (RECT*)lParam;
 * \endcode
 *
 * \param rcExpect The expected size of the window after changing.
 * \param rcResult The actual size of the window after changing.
 *
 * Example:
 *
 * \include msg_sizechanging.c
 */
#define MSG_SIZECHANGING	0x0025

/**
 * \def MSG_SIZECHANGED
 * \brief Indicates the size of the window has been changed.
 *
 * This message is sent to the window when the size has been changed.
 * If you want adjust the size of the client area of the window, 
 * you should handle this message, change the values of the client area,
 * and return non-zero value to indicate that the client area has been modified.
 *
 * \code
 * MSG_SIZECHANGED
 * RECT* rcClient = (RECT*)lParam;
 * \endcode
 *
 * \param rcClient The pointer to a RECT structure which contains the new client area.
 * 
 * Example:
 *
 * \include msg_sizechanged.c
 */
#define MSG_SIZECHANGED	 0x0026

/**
 * \def MSG_SETFOCUS
 * \brief Indicates that the window has gained the input focus.
 *
 * This message is sent to the window procedure 
 * after the window gains the input focus.
 */
#define MSG_SETFOCUS		0x0030

/**
 * \def MSG_KILLFOCUS
 * \brief Indicates that the window has lost the input focus.
 *
 * This message is sent to the window procedure 
 * after the window lost the input focus.
 */
#define MSG_KILLFOCUS	   0x0031

#define MSG_ACTIVE		  0x0033

#define MSG_LASTPOSTMSG	 0x005F

	/** @} end of post_event_msgs */

	/**
	 * \defgroup creation_msgs Window creation messages
	 * @{
	 */

	/* Group 4 from 0x0060 to 0x009F, the creation messages. */
#define MSG_FIRSTCREATEMSG  0x0060

/**
 * \def MSG_CREATE
 * \brief Indicates the window has been created, and gives you a chance to initialize your private objects.
 *
 * This messages is sent to the window after the window has been created and registered
 * to the system. You can initialize your own objects when you receive this message, 
 * and return zero to the system in order to indicates the success of initialization.
 * If you return non-zero to the system after handle this message, the created window
 * will be destroied immediately.
 *
 * \code
 * MSG_CREATE for main windows:
 * PMAINWINCREATE create_info = (PMAINWINCREATE)lParam;
 *
 * MSG_CREATE for controls:
 * HWND parent = (HWND)wParam;
 * DWORD add_data = (DWORD)lParam;
 * \endcode
 *
 * \param create_info The pointer to the MAINWINCREATE structure which is passed to
 *		CreateMainWindow function.
 * \param parent The handle to the parent window of the control.
 * \param add_data The first additional data passed to CreateWindow function.
 *
 * \sa CreateMainWindow, CreateWindow, MAINWINCREATE
 */
#define MSG_CREATE		  0x0060

/**
 * \def MSG_NCCREATE
 * \brief Indicates the window has been created, but has not registered to the system.
 *
 * This message is sent to the window after the window has been created, but not
 * registered the system. Like MSG_CREATE message, you can initialize your own objects
 * when you receive this message, but can not create child windows of the window, can
 * not get a device context to draw.
 *
 * If you return non-zero to the system after handle this message, the created window
 * will be destroied immediately.
 *
 * \code
 * MSG_NCCREATE for main windows:
 * PMAINWINCREATE create_info = (PMAINWINCREATE)lParam;
 *
 * MSG_NCCREATE for controls:
 * DWORD add_data = (DWORD)lParam;
 * \endcode
 *
 * \param create_info The pointer to the MAINWINCREATE structure which is passed to
 *		CreateMainWindow function.
 * \param add_data The first additional data passed to CreateWindow function.
 *
 * \sa CreateMainWindow, CreateWindow, MAINWINCREATE
 */
#define MSG_NCCREATE		0x0061

/**
 * \def MSG_DESTROY
 * \brief Indicates the window will be destroied.
 *
 * This message is sent to the window when \a DestroyMainWindow 
 * or \a DestroyWindow is calling. You can destroy your private objects
 * when receive this message.
 *
 * If you return non-zero to the system after handle this message, the process 
 * of \a DestroyMainWindow and \a DestroyWindow will return immediately.
 *
 * \sa DestroyMainWindow, DestroyWindow
 */
#define MSG_DESTROY		 0x0064

/**
 * \def MSG_CLOSE
 * \brief Indicates the user has clicked the closing box on the caption.
 *
 * This message is sent to the window when the user has clicked the closing box
 * on the caption of the window.
 */
#define MSG_CLOSE		   0x0066

#define MSG_LASTCREATEMSG   0x009F

	/** @} end of creation_msgs */

	/**
	 * \defgroup paint_msgs Window painting messages
	 * @{
	 */

	/* Group 5 from 0x00A0 to 0x00CF, the paint messages. */
#define MSG_FIRSTPAINTMSG   0x00A0


/**
 * \def MSG_SHOWWINDOW
 * \brief Indicates that the window has been shown or hidden.
 *
 * This message is sent to the window when the window has been shown
 * or hidden (due to the calling of the function ShowWindow).
 *
 * \code
 * MSG_SHOWWINDOW
 * int show_cmd = (int)wParam;
 * \endcode
 *
 * \param show_cmd The command to show or hide, can be one of 
 * the following values:
 *	  - SW_SHOW\n
 *		Shows the window.
 *	  - SW_HIDE\n
 *		Hides the window.
 *	  - SW_SHOWNORMAL\n
 *		Shows the window, and if the window is a main window 
 *		sets it to be the top most main window.
 *
 * \sa ShowWindow
 */
#define MSG_SHOWWINDOW	  0x00A0 

/**
 * \def MSG_ERASEBKGND
 * \brief Sent to the window to erase the background.
 *
 * This message is sent to the window if the whole or a part of the background
 * should be erased.
 *
 * \code
 * MSG_ERASEBKGND
 * const RECT* inv_rect = (const RECT*)lParam;
 * \endcode
 *
 * \param inv_rect The pointer to a RECT structure contains the rectangle
 * should be erase. The rectangle is in client coordinates system. If it
 * is NULL, the whole client area should be erased.
 */
#define MSG_ERASEBKGND	  0x00B0	  /* this is an async message. */

/**
 * \def MSG_PAINT
 * \brief Sent to the window if the window contains an invalid region.
 *
 * This message is sent to the window if the window contains an invalid region.
 *
 * \code
 * MSG_PAINT
 * const CLIPRGN* inv_rgn = (const CLIPRGN*) lParam;
 * \endcode
 *
 * \param inv_rgn The pointer to the invalid region of the window.
 */
#define MSG_PAINT		   0x00B1

#define MSG_NCPAINT		 0x00B2  /* 非客户区绘制消息.比如,边框. */

/**
 * \def MSG_ENABLE
 * \brief Indicates the window is disabled/enabled.
 *
 * This message is sent to the window if the window has been disabled or enabled.
 *
 * \code
 * MSG_ENABLE
 * BOOL enabled = (BOOL)wParam;
 * \endcode
 *
 * \param enabled Indicates whether the window was disabled or enabled.
 */
#define MSG_ENABLE		  0x00C0

#define MSG_LASTPAINTMSG	0x00CF

	/** @} end of paint_msgs */

	/**
	 * \defgroup desktop_msgs Internal desktop messages
	 * @{
	 */

	/* Group 6 from 0x00D0 to 0x00EF, the internal desktop messages. */
#define MSG_FIRSTSESSIONMSG 0x00D0

/* wParam, 保存窗口句柄. */
#define MSG_APPENDHOTKEY	0x00D7  /*  增加热键,  eric , 2006.02.05 */
#define MSG_PREPENDHOTKEY   0x00D8  /*  增加热键,  eric , 2006.02.05 */

/* lParam, 窗口句柄. 在其后面将要被插入热键. */
#define MSG_INSERTHOTKEY	0x00D9	/*  增加热键,  eric , 2006.02.05 */
#define MSG_REMOVEHOTKEY	0x00DA	/* 删除热键	*/
#define MSG_SCRMAN			0x00DB	/* 屏幕管理	*/
	#define SM_RESET		0x0001	/* screen managee code : reset desktop	   */
	#define SM_BACKMAIN		0x0002	/* screen managee code : back to main screen */
	#define SM_DLGRECT		0x0003	/* screen managee code : setup dialog rect   */
	#define SM_START_LAYOUT	0x0004	/* screen managee code : 启动布局调整	*/
	#define SM_FREEZE		0x0005	/* screen managee code : 进入冻结菜单	*/
	#define SM_MENU			0x0006	/* screen managee code : 进入主菜单		*/
	#define SM_LAYOUT		0x0007	/* screen managee code : 开始一次布局调整	*/
	#define SM_EVENT		0x0008	/* screen managee code : 进入医生标记菜单	*/
	#define SM_PATIENT		0x0009	/* screen managee code : 进入病人信息菜单	*/
	#define SM_STATUS		0x000A	/* screen managee code : 进入系统信息菜单	*/
	#define SM_FACTORY		0x000B	/* screen managee code : factory maintain dialog	*/

#define MSG_ERASEDESKTOP	0x00E0

#define MSG_LASTSESSIONMSG  0x00EF

	/** @} end of desktop_msgs */

	/**
	 * \defgroup window_msgs Internal window management messages
	 * @{
	 */

	/* Group 7 from 0x00F0 to 0x010F, Internal window management messages. */
#define MSG_FIRSTWINDOWMSG  0x00F0

#define MSG_ADDNEWMAINWIN   0x00F0
#define MSG_REMOVEMAINWIN   0x00F1
#define MSG_MOVETOTOPMOST   0x00F2 
#define MSG_SETACTIVEMAIN   0x00F3
#define MSG_GETACTIVEMAIN   0x00F4
#define MSG_SHOWMAINWIN	 0x00F5
#define MSG_HIDEMAINWIN	 0x00F6
#define MSG_MOVEMAINWIN	 0x00F7
#define MSG_SETCAPTURE	  0x00F8
#define MSG_GETCAPTURE	  0x00F9

#define MSG_ENABLEMAINWIN   0x0100
#define MSG_ISENABLED	   0x0101
	
#define MSG_LASTWINDOWMSG   0x010F

	/** @} end of window_msgs */

	/**
	 * \defgroup ctrl_msgs Dialog and control messages
	 * @{
	 */

	/* Group 8 from 0x0120 to 0x013F, the dialog and control messages. */
#define MSG_FIRSTCONTROLMSG 0x0120

/**
 * \def MSG_COMMAND
 * \brief The command message, indicates a notification message from child window,
 * or the user has selected a menu item.
 *
 * This message sent to the window when the user has selected a menu item, or
 * a child window has sent a notification message to the parent.
 *
 * \code
 * MSG_COMMAND
 * int id = LOWORD(wParam);
 * int code = HIWORD(wParam);
 * \endcode
 *
 * \param id The identifier of the menu item or the child window.
 * \param code The notification code.
 *
 * \sa NotifyParent
 */
#define MSG_COMMAND		 0x0120
#define MSG_SYSCOMMAND	  0x0121
#define MSG_GETDLGCODE	  0x0122

/**
 * \def MSG_INITDIALOG
 * \brief Ready to initialize the controls in a dialog box.
 *
 * This message is sent to the dialog in order that you can initialize the controls
 * in the dialog box.
 *
 * \code
 * MSG_INITDIALOG
 * HWND focus_hwnd = (HWND)wParam;
 * LPARAM lparam = (LPARAM)lParam;
 * \endcode
 *
 * \param focus_hwnd The handle to the control which will gain the input focus.
 * \param lparam The parameter passed into the dialog box through \a DialogBoxIndirectParam function.
 * \return Returns non-zero value to set the input focus to \a focus_hwnd, else do not set focus.
 *
 * \sa DialogBoxIndirectParam
 *
 * Example:
 *
 * \include msg_initdialog.c
 */
#define MSG_INITDIALOG	  0x0123

/**
 * \def MSG_FONTCHANGING
 * \brief Indicates the user is trying to change the font of the window.
 *
 * This message is sent to the window when the user is trying to change
 * the font of the window by calling \a SetWindowFont.
 * If you return non-zero after handling this message, \a SetWindowFont
 * will return immediately. Thus, the default window font will not change.
 *
 * \code
 * MSG_FONTCHANGING
 * PLOGFONT log_font = (PLOGFONT)lParam;
 * \endcode
 *
 * \param log_font The pointer to the new window logical font.
 *
 * \sa SetWindowFont
 */
#define MSG_FONTCHANGING	0x0130


/**
 * \def MSG_FONTCHANGED
 * \brief Indicates the window font has been changed.
 *
 * This message is sent to the window after the window font has changed.
 * Some window should be repainted to reflect the new window font.
 */
#define MSG_FONTCHANGED	 0x0131

/**
 * \def MSG_GETTEXTLENGTH
 * \brief Sent to the control to get the length of the text.
 *
 * This message is sent to the control when you calling \a GetWindowTextLength
 * function to get the length of the text.
 *
 * \code
 * MSG_GETTEXTLENGTH
 * wParam = 0;
 * lParam = 0;
 * \endcode
 *
 * \return The length of the text.
 *
 * \sa GetWindowTextLength
 */
#define MSG_GETTEXTLENGTH   0x0132

/**
 * \def MSG_GETTEXT
 * \brief Sent to the control to get the text.
 *
 * This message is sent to the control when you calling \a GetWindowText
 * function to get the text.
 *
 * \code
 * MSG_GETTEXT
 * int max_len;
 * char* text_buf;
 *
 * wParam = (WPARAM)max_len;
 * lParam = (LPARAM)text_buf;
 * \endcode
 *
 * \param max_len The maximal number of characters can be copied to the buffer.
 * \param text_buf The pointer to a buffer receives the text.
 * \return The length of the window text string.
 *
 * \sa GetWindowText
 */
#define MSG_GETTEXT		 0x0133

/**
 * \def MSG_SETTEXT
 * \brief Sent to the control to set the text.
 *
 * This message is sent to the control when you calling \a SetWindowText
 * function to set the text.
 *
 * \code
 * MSG_GETTEXT
 * char* text_buf;
 *
 * wParam = 0;
 * lParam = (LPARAM)text_buf;
 * \endcode
 *
 * \param text_buf The pointer to a buffer contains the text.
 * \return The length of the text string.
 *
 * \sa SetWindowText
 */
#define MSG_SETTEXT		 0x0134

#define MSG_SETITEM		 0x013A
#define MSG_GETITEM		 0x013B

#define MSG_LASTCONTROLMSG  0x013F

	/** @} end of ctrl_msgs */

	/**
	 * \defgroup system_msgs System messages
	 * @{
	 */

	/* Group 9 from 0x0140 to 0x016F, the system messages. */
#define MSG_FIRSTSYSTEMMSG  0x0140

#define MSG_QUIT			0x0140

/**
 * \def MSG_IDLE
 * \brief Indicates the system enters idle loop.
 *
 * This message is sent to the all main window when the system
 * enters idle loop.
 */
#define MSG_IDLE			0x0142

#define MSG_TIMEOUT		 0x0143

/**
 * \def MSG_TIMER
 * \brief Indicates a timer has expired.
 *
 * This message is sent to the window when a timer expired.
 *
 * \code
 * MSG_TIMER
 * int timer_id = (int)wParam;
 * \endcode
 *
 * \param timer_id The identifier of the timer has expired.
 */
#define MSG_TIMER		   0x0144

#define MSG_GETCTRLCLASSINFO	0x016B
#define MSG_CTRLCLASSDATAOP	 0x016C
	#define CCDOP_GETCCI		0x01
	#define CCDOP_SETCCI		0x02
	
#define MSG_NEWCTRLINSTANCE	 0x0169
#define MSG_REMOVECTRLINSTANCE  0x016A

#define MSG_LASTSYSTEMMSG   0x016F

	/** @} end of system_msgs */
	
	/**
	 * \defgroup user_msgs User-defined  messages
	 * @{
	 */

#define MSG_FIRSTUSERMSG	0x0800

/**
 * \def MSG_USER
 * \brief The first user-defined message.
 *
 * MiniGUI reserved the range from 0x0800 to 0xEFFF for user-defined messages.
 * MSG_USER is the first user-defined message you can use by your own.
 */
#define MSG_USER			0x0800

#define MSG_LASTUSERMSG	 0xEFFF

	/** @} end of user_msgs */

	/** @} end of msgs */
	
/*   各个界面元素的颜色.	   */
/*   BKC, backgroud color; FGC, foreground color; WEC, window element color */
/**
	 scnColor;				// 屏幕颜色
	 strColor;				// 字符颜色

	 // DIALOG颜色定义
	 menuBkColor;			// 菜单背景色
	 menuTitleColor;		// 菜单标题颜色  
	 menuTitleBkColor;		// 菜单标题背景色,
	 focusCtrlFrameColor;	// 控件被选中的边框颜色
	 focusCtrlBkColor;		// 被选中的控件的背景色(列表框、SPINBOX)
	 listDropColor;			// 下拉框的颜色
**/
enum color_define{
	BKC_CAPTION_NORMAL = 0,				 // 0,
	FGC_CAPTION_NORMAL,					 // 1,
	BKC_CAPTION_ACTIVED,					// 2,
	FGC_CAPTION_ACTIVED,					// 3,
	BKC_CAPTION_DISABLED,				   // 4,
	FGC_CAPTION_DISABLED,				   // 5,
	WEC_FRAME_NORMAL,					   // 6,
	WEC_FRAME_ACTIVED,					  // 7,
	WEC_FRAME_DISABLED,					 // 8,
	BKC_MENUBAR_NORMAL,					 // 9,
	FGC_MENUBAR_NORMAL,					 //10,
	BKC_MENUBAR_HILITE,					 //11,
	FGC_MENUBAR_HILITE,					 //12,
	FGC_MENUBAR_DISABLED,				   //13,
	BKC_MENUITEM_NORMAL,					//14,
	FGC_MENUITEM_NORMAL,					//15,
	BKC_MENUITEM_HILITE,					//16,
	FGC_MENUITEM_HILITE,					//17,
	FGC_MENUITEM_DISABLED,				  //18,
	BKC_PPPMENUTITLE,					   //19,
	FGC_PPPMENUTITLE,					   //20,
	WEC_3DFRAME_LEFT_OUTER,				 //21,
	WEC_3DFRAME_LEFT_INNER,				 //22,
	WEC_3DFRAME_TOP_OUTER,				  //23,
	WEC_3DFRAME_TOP_INNER,				  //24,
	WEC_3DFRAME_RIGHT_OUTER,				//25,
	WEC_3DFRAME_RIGHT_INNER,				//26,
	WEC_3DFRAME_BOTTOM_OUTER,			   //27,
	WEC_3DFRAME_BOTTOM_INNER,			   //28,
	WEC_3DFRAME_LEFT,					   //29,
	WEC_3DFRAME_TOP,						//30,
	WEC_3DFRAME_RIGHT,					  //31,
	WEC_3DFRAME_BOTTOM,					 //32,
	BKC_CONTROL_DEF,						//33,
	FGC_CONTROL_DEF,						//34,
	WEC_FLAT_BORDER,						//35,
	WEC_TEXT,							   //36,	   //textdefaultcolor
	BKC_DLG,								//37,	   //dialogdefaultbackgroundcolor
	BKC_CONTROL_FOCUS,					  //38,	   //backgroundcolorofFocusedcontrol
	WEC_CONTROL_FOCUSFRAME,				 //39,	   //colorofFocusedcontrolframe
	WEC_CONTROL_LIST_DROP,				  //40,	   //colorofListcontroldropdown
	WEC_EXCOLOR_LIGHTPINK,				  //41,	   ////浅粉红
	WEC_EXCOLOR_PINK,					   //42,	   ////粉红
	WEC_EXCOLOR_CRIMSON,					//43,	   ////深红/猩红
	WEC_EXCOLOR_LAVENDERBLUSH,			  //44,	   ////淡紫红
	WEC_EXCOLOR_PALEVIOLETRED,			  //45,	   ////弱紫罗兰红
	WEC_EXCOLOR_HOTPINK,					//46,	   ////热情的粉红
	WEC_EXCOLOR_DEEPPINK,				   //47,	   ////深粉红
	WEC_EXCOLOR_MEDIUMVIOLETRED,			//48,	   ////中紫罗兰红
	WEC_EXCOLOR_ORCHID,					 //49,	   ////暗紫色/兰花紫
	WEC_EXCOLOR_THISTLE,					//50,	   ////蓟色
	WEC_EXCOLOR_PLUM,					   //51,	   ////洋李色/李子紫
	WEC_EXCOLOR_VIOLET,					 //52,	   ////紫罗兰
	WEC_EXCOLOR_MAGENTA,					//53,	   ////洋红/玫瑰红
	WEC_EXCOLOR_FUCHSIA,					//54,	   ////紫红/灯笼海棠
	WEC_EXCOLOR_DARKMAGENTA,				//55,	   ////深洋红
	WEC_EXCOLOR_PURPLE,					 //56,	   ////紫色
	WEC_EXCOLOR_MDEIUMORCHID,			   //57,	   ////中兰花紫
	WEC_EXCOLOR_DARKVIOLET,				 //58,	   ////暗紫罗兰
	WEC_EXCOLOR_DARKORCHID,				 //59,	   ////暗兰花紫
	WEC_EXCOLOR_INDIGO,					 //60,	   ////靛青/紫兰色
	WEC_EXCOLOR_BLUEVIOLET,				 //61,	   ////蓝紫罗兰
	WEC_EXCOLOR_MEDIUMPURPLE,			   //62,	   ////中紫色
	WEC_EXCOLOR_MEDIUMSLATEBLUE,			//63,	   ////中暗蓝色/中板岩蓝
	WEC_EXCOLOR_SLATEBLUE,				  //64,	   ////石蓝色/板岩蓝
	WEC_EXCOLOR_DARKSLATBLUE,			   //65,	   ////暗灰蓝色/暗板岩蓝
	WEC_EXCOLOR_LAVENDER,				   //66,	   ////淡紫色/熏衣草淡紫
	WEC_EXCOLOR_GHOSTWHITE,				 //67,	   ////幽灵白
	WEC_EXCOLOR_BLUE,					   //68,	   ////纯蓝
	WEC_EXCOLOR_MEDIUMBLUE,				 //69,	   ////中蓝色
	WEC_EXCOLOR_MIDNIGHTBLUE,			   //70,	   ////午夜蓝
	WEC_EXCOLOR_DARKBLUE,				   //71,	   ////暗蓝色
	WEC_EXCOLOR_NAVY,					   //72,	   ////海军蓝
	WEC_EXCOLOR_ROYALBLUE,				  //73,	   ////皇家蓝/宝蓝
	WEC_EXCOLOR_CORNFLOWERBLUE,			 //74,	   ////矢车菊蓝
	WEC_EXCOLOR_LIGHTSTEELBLUE,			 //75,	   ////亮钢蓝
	WEC_EXCOLOR_LIGHTSLATEGRAY,			 //76,	   ////亮蓝灰/亮石板灰
	WEC_EXCOLOR_SLATEGRAY,				  //77,	   ////灰石色/石板灰
	WEC_EXCOLOR_DODGERBLUE,				 //78,	   ////闪兰色/道奇蓝
	WEC_EXCOLOR_ALICEBLUE,				  //79,	   ////爱丽丝蓝
	WEC_EXCOLOR_STEELBLUE,				  //80,	   ////钢蓝/铁青
	WEC_EXCOLOR_LIGHTSKYBLUE,			   //81,	   ////亮天蓝色
	WEC_EXCOLOR_SKYBLUE,					//82,	   ////天蓝色
	WEC_EXCOLOR_DEEPSKYBLUE,				//83,	   ////深天蓝
	WEC_EXCOLOR_LIGHTBLUE,				  //84,	   ////亮蓝
	WEC_EXCOLOR_POWDERBLUE,				 //85,	   ////粉蓝色/火药青
	WEC_EXCOLOR_CADETBLUE,				  //86,	   ////军兰色/军服蓝
	WEC_EXCOLOR_AZURE,					  //87,	   ////蔚蓝色
	WEC_EXCOLOR_LIGHTCYAN,				  //88,	   ////淡青色
	WEC_EXCOLOR_PALETURQUOISE,			  //89,	   ////弱绿宝石
	WEC_EXCOLOR_CYAN,					   //90,	   ////青色
	WEC_EXCOLOR_AQUA,					   //91,	   ////浅绿色/水色
	WEC_EXCOLOR_DARKTURQUOISE,			  //92,	   ////暗绿宝石
	WEC_EXCOLOR_DARKSLATEGRAY,			  //93,	   ////暗瓦灰色/暗石板灰
	WEC_EXCOLOR_DARKCYAN,				   //94,	   ////暗青色
	WEC_EXCOLOR_TEAL,					   //95,	   ////水鸭色
	WEC_EXCOLOR_MEDIUMTURQUOISE,			//96,	   ////中绿宝石
	WEC_EXCOLOR_LIGHTSEAGREEN,			  //97,	   ////浅海洋绿
	WEC_EXCOLOR_TURQUOISE,				  //98,	   ////绿宝石
	WEC_EXCOLOR_AQUAMARINE,				 //99,	   ////宝石碧绿
	WEC_EXCOLOR_MEDIUMAQUAMARINE,		   //100,	  ////中宝石碧绿
	WEC_EXCOLOR_MEDIUMSPRINGGREEN,		  //101	   //中春绿色
	WEC_EXCOLOR_MINTCREAM,				  //102,	  ////薄荷奶油
	WEC_EXCOLOR_SPRINGGREEN,				//103,	  ////春绿色
	WEC_EXCOLOR_MEDIUMSEAGREEN,			 //104,	  ////中海洋绿
	WEC_EXCOLOR_SEAGREEN,				   //105,	  ////海洋绿
	WEC_EXCOLOR_HONEYDEW,				   //106,	  ////蜜色/蜜瓜色
	WEC_EXCOLOR_LIGHTGREEN,				 //107,	  ////淡绿色
	WEC_EXCOLOR_PALEGREEN,				  //108,	  ////弱绿色
	WEC_EXCOLOR_DARKSEAGREEN,			   //109,	  ////暗海洋绿
	WEC_EXCOLOR_LIMEGREEN,				  //110,	  ////闪光深绿
	WEC_EXCOLOR_LIME,					   //111,	  ////闪光绿
	WEC_EXCOLOR_FORESTGREEN,				//112,	  ////森林绿
	WEC_EXCOLOR_GREEN,					  //113,	  ////纯绿
	WEC_EXCOLOR_DARKGREEN,				  //114,	  ////暗绿色
	WEC_EXCOLOR_CHARTREUSE,				 //115,	  ////黄绿色/查特酒绿
	WEC_EXCOLOR_LAWNGREEN,				  //116,	  ////草绿色/草坪绿
	WEC_EXCOLOR_GREENYELLOW,				//117,	  ////绿黄色
	WEC_EXCOLOR_DARKOLIVEGREEN,			 //118,	  ////暗橄榄绿
	WEC_EXCOLOR_YELLOWGREEN,				//119,	  ////黄绿色
	WEC_EXCOLOR_OLIVEDRAB,				  //120,	  ////橄榄褐色
	WEC_EXCOLOR_BEIGE,					  //121,	  ////米色/灰棕色
	WEC_EXCOLOR_LIGHTGOLDENRODYELLOW,	   //122,	  //亮菊黄
	WEC_EXCOLOR_IVORY,					  //123,	  ////象牙色
	WEC_EXCOLOR_LIGHTYELLOW,				//124,	  ////浅黄色
	WEC_EXCOLOR_YELLOW,					 //125,	  ////纯黄
	WEC_EXCOLOR_OLIVE,					  //126,	  ////橄榄
	WEC_EXCOLOR_DARKKHAKI,				  //127,	  ////暗黄褐色/深卡叽布
	WEC_EXCOLOR_LEMONCHIFFON,			   //128,	  ////柠檬绸
	WEC_EXCOLOR_PALEGOLDENROD,			  //129,	  ////灰菊黄/苍麒麟色
	WEC_EXCOLOR_KHAKI,					  //130,	  ////黄褐色/卡叽布
	WEC_EXCOLOR_GOLD,					   //131,	  ////金色
	WEC_EXCOLOR_CORNSILK,				   //132,	  ////玉米丝色
	WEC_EXCOLOR_GOLRENROD,				  //133,	  ////金菊黄
	WEC_EXCOLOR_DARKGOLDENROD,			  //134,	  ////暗金菊黄
	WEC_EXCOLOR_FLORALWHITE,				//135,	  //花的白色
	WEC_EXCOLOR_OLDLACE,					//136,	  ////老花色/旧蕾丝
	WEC_EXCOLOR_WHEAT,					  //137,	  ////浅黄色/小麦色
	WEC_EXCOLOR_MOCCASIN,				   //138,	  ////鹿皮色/鹿皮靴
	WEC_EXCOLOR_ORANGE,					 //139,	  ////橙色
	WEC_EXCOLOR_PAPAYAWHIP,				 //140,	  ////番木色/番木瓜
	WEC_EXCOLOR_BLANCHEDALMOND,			 //141,	  ////白杏色
	WEC_EXCOLOR_NAVAJOEWHITE,			   //142,	  ////纳瓦白/土著白
	WEC_EXCOLOR_ANTIQUEWHITE,			   //143,	  ////古董白
	WEC_EXCOLOR_TAN,						//144,	  ////茶色
	WEC_EXCOLOR_BURLYWOOD,				  //145,	  ////硬木色
	WEC_EXCOLOR_BISQUE,					 //146,	  ////陶坯黄
	WEC_EXCOLOR_DARKORANGE,				 //147,	  ////深橙色
	WEC_EXCOLOR_LINEN,					  //148,	  ////亚麻布
	WEC_EXCOLOR_PERU,					   //159,	  ////秘鲁色
	WEC_EXCOLOR_PEACHPUFF,				  //150,	  ////桃肉色
	WEC_EXCOLOR_SANDYBROWN,				 //151,	  ////沙棕色
	WEC_EXCOLOR_CHOCOLATE,				  //152,	  ////巧克力色
	WEC_EXCOLOR_SADDLEBROWN,				//153,	  ////重褐色/马鞍棕色
	WEC_EXCOLOR_SEASHELL,				   //154,	  ////海贝壳
	WEC_EXCOLOR_SIENNA,					 //155,	  ////黄土赭色
	WEC_EXCOLOR_LIGHTSALMON,				//156,	  ////浅鲑鱼肉色
	WEC_EXCOLOR_CORAL,					  //157,	  ////珊瑚
	WEC_EXCOLOR_ORANGERED,				  //158,	  ////橙红色
	WEC_EXCOLOR_DARKSALMON,				 //159,	  ////深鲜肉/鲑鱼色
	WEC_EXCOLOR_TOMATO,					 //160,	  ////番茄红
	WEC_EXCOLOR_MISTYROSE,				  //161,	  ////浅玫瑰色/薄雾玫瑰
	WEC_EXCOLOR_SALMON,					 //162,	  ////鲜肉/鲑鱼色
	WEC_EXCOLOR_SNOW,					   //163,	  ////雪白色
	WEC_EXCOLOR_LIGHTCORAL,				 //164,	  ////淡珊瑚色
	WEC_EXCOLOR_ROSYBROWN,				  //165,	  ////玫瑰棕色
	WEC_EXCOLOR_INDIANRED,				  //166,	  ////印度红
	WEC_EXCOLOR_RED,						//167,	  ////纯红
	WEC_EXCOLOR_BROWN,					  //168,	  ////棕色
	WEC_EXCOLOR_FIREBRICK,				  //169,	  ////火砖色/耐火砖
	WEC_EXCOLOR_DARKRED,					//170,	  ////深红色
	WEC_EXCOLOR_MAROON,					 //171,	  ////栗色
	WEC_EXCOLOR_WHITE,					  //172,	  ////纯白
	WEC_EXCOLOR_WHITESMOKE,				 //173,	  ////白烟
	WEC_EXCOLOR_GAINSBORO,				  //174,	  ////淡灰色
	WEC_EXCOLOR_LIGHTGREY,				  //175,	  ////浅灰色
	WEC_EXCOLOR_SILVER,					 //176,	  ////银灰色
	WEC_EXCOLOR_DARKGRAY,				   //177,	  ////深灰色
	WEC_EXCOLOR_GRAY,					   //178,	  ////灰色
	WEC_EXCOLOR_DIMGRAY,					//179,	  ////暗淡灰
		WEC_EXCOLOR_BLACK1,					  //180,	  ////暗黑1
		WEC_EXCOLOR_BLACK2,					  //181,	  ////暗黑2
		WEC_EXCOLOR_BLACK3,					  //182,	  ////暗黑3
		WEC_EXCOLOR_BLACK4,					  //183,	  ////暗黑4
		WEC_EXCOLOR_BLACK5,					  //184,	  ////暗黑5
		WEC_EXCOLOR_BLACK,					  //185,	  ////纯黑
	WEC_EXCOLOR_TRANSPARENT,				//186	   ////透明
	WEC_ITEM_NUMBER						 //182
}WEC_COLOR;

extern GAL_PIXEL WinElementColors[];
#define GetWindowElementColor(iItem)	(WinElementColors[iItem])
#define CLR_STRING(iItem)			   GetColorName(iItem)
#define DEF_BACK_COLOR				  GetWindowElementColor(WEC_EXCOLOR_BLACK1)
	/**
	 * \defgroup styles Window styles
	 * @{
	 */

/**
 * \def WS_NONE
 * \brief None style.
 */
#define WS_NONE			 0x00000000L

#define WS_OVERLAPPED	   0x00000000L

/**
 * \def WS_ABSSCRPOS
 * \brief Create a main window whose position is based on absolute screen coordinates.
 */
#define WS_ABSSCRPOS		0x80000000L

/**
 * \def WS_CHILD
 * \brief Indicates the window is a child.
 */
#define WS_CHILD			0x40000000L

/* Clipping styles -- not supported so far */

/**
 * \def WS_VISIBLE
 * \brief Creates a window initially visible.
 */
#define WS_VISIBLE		  0x08000000L

/**
 * \def WS_DISABLED
 * \brief Creates a window initially disabled.
 */
#define WS_DISABLED		 0x04000000L

/* Main window states -- not supported so far */
#define WS_MINIMIZE		 0x02000000L
#define WS_MAXIMIZE		 0x01000000L

/**
 * \def WS_CAPTION
 * \brief Creates a main window with caption.
 */
#define WS_CAPTION		  0x20000000L

/**
 * \def WS_SYSMENU
 * \brief Creates a main window with system menu.
 */
#define WS_SYSMENU		  0x10000000L

#define WS_DLGFRAME		 0x00800000L

/**
 * \def WS_BORDER
 * \brief Creates a window with border.
 */
#define WS_BORDER		   0x00400000L

/**
 * \def WS_THICKFRAME
 * \brief Creates a window with thick frame.
 */
#define WS_THICKFRAME	   0x00200000L

/**
 * \def WS_THINFRAME
 * \brief Creates a window with thin frame.
 */
#define WS_THINFRAME		0x00100000L

/**
 * \def WS_VSCROLL
 * \brief Creates a window with vertical scroll bar.
 */
#define WS_VSCROLL		  0x00080000L

//#define WS_BGLINE		   0x00080000L

/**
 * \def WS_HSCROLL
 * \brief Creates a window with horizontal scroll bar.
 */
#define WS_HSCROLL		  0x00040000L

/**
 * \def WS_MINIMIZEBOX
 * \brief Creates a window with minimizing box on caption.
 */
#define WS_MINIMIZEBOX	  0x00020000L

/**
 * \def WS_MAXIMIZEBOX
 * \brief Creates a window with maximizing box on caption.
 */
#define WS_MAXIMIZEBOX	  0x00010000L

/**
 * \def WS_GROUP
 * \brief Indicates the control is the leader of a group.
 */
#define WS_GROUP			0x00020000L

/**
 * \def WS_TABSTOP
 * \brief Indicates the user can set the input focus to the control by using Tab key.
 */
#define WS_TABSTOP		  0x00010000L

/**
	只能用于主窗口; 因为,控件窗口也使用的了低16位的值.
	
	WS_QUIT, 可以不使用了. 通过检查窗口是否还在链表上,可以鉴别窗口是否有效.
			eric, 2006.02.19;
**/
#define WS_MODALDLG		 0x00008000L		/* eric, 2006.02.06. 表示模式对话框. */
#define WS_QUIT			 0x00000001L		/* eric, 2006.02.06. 表示窗口退出.不接收任何消息.  */

/**
 * \def WS_EX_NONE
 * \brief None extended window style.
 */
#define WS_EX_NONE			  0x00000000L	 /* supported */

/**
 * \def WS_EX_USEPRIVATECDC
 * \brief The window has its own private client device context.
 *
 * \sa CreatePrivateClientDC
 */
#define WS_EX_USEPRIVATECDC	 0x00000002L	 /* supported */

#define WS_EX_NOPARENTNOTIFY	0x00000004L

/**
 * \def WS_EX_TOPMOST
 * \brief The main window is a top-most (always on top) window.
 */
#define WS_EX_TOPMOST		   0x00000008L	 /* supported */
#define WS_EX_TRANSPARENT	   0x00000020L

/**
 * \def WS_EX_TOOLWINDOW
 * \brief The main window is a tool window, which can not gain the input focus.
 */
#define WS_EX_TOOLWINDOW		0x00000080L	 /* supported */

/**
 * \def WS_EX_USEPARENTFONT
 * \brief The window uses the default font of its parent.
 */
#define WS_EX_USEPARENTFONT	 0x00000100L	 /* supported */

#define WS_EX_CONTEXTHELP	   0x00000400L

/**
 * \def WS_EX_USEPARENTCURSOR
 * \brief The window uses the default cursor of its parent.
 */
#define WS_EX_USEPARENTCURSOR   0x00000800L	 /* supported */

#define WS_EX_RIGHT			 0x00001000L
#define WS_EX_LEFT			  0x00000000L
#define WS_EX_RTLREADING		0x00002000L
#define WS_EX_LTRREADING		0x00000000L
#define WS_EX_LEFTSCROLLBAR	 0x00004000L
#define WS_EX_RIGHTSCROLLBAR	0x00000000L

#define WS_EX_CONTROLPARENT	 0x00010000L
#define WS_EX_STATICEDGE		0x00020000L
#define WS_EX_APPWINDOW		 0x00040000L

#define WS_EX_HOTKEY			0x00100000L	 /* eric, 2006.02.06;表示热键属性. */

/**
 * \def WS_EX_IMECOMPOSE
 * \brief The main window will get input from IME window.
 */
#define WS_EX_IMECOMPOSE		0x10000000L	 /* supported */

/**
 * \def WS_EX_NOCLOSEBOX
 * \brief The main window has no closing box on its caption.
 */
#define WS_EX_NOCLOSEBOX		0x20000000L	 /* supported */

/**
 * \def WS_EX_CTRLASMAINWIN
 * \brief The control can be displayed out of the main window which contains the control.
 */
#define WS_EX_CTRLASMAINWIN	 0x40000000L	 /* supported */

	/** @} end of styles */

#define HWND_DESKTOP		0			
#define HWND_INVALID		0xFFFFFFFF


/**
 * Structure defines a main window.
 */
typedef struct _MAINWINCREATE
{
	/** the style of the main window */
	DWORD dwStyle;

	/** the extended style of the main window */
	DWORD dwExStyle;

	/** the caption of the main window */
	STRINGID caption;

	/** the window callback procedure */
	WNDPROC proc;

	/** the position of the main window in the screen coordinates */
	INT32 lx, ty, rx, by;
	INT16 id;

	/** the pixel value of background color of the main window */
	GAL_PIXEL iBkColor;
	GAL_PIXEL textColor;

	/** the first private data associated with the main window */
	DWORD dwAddData;

	/** reserved, do not use */
	DWORD dwReserved;
}MAINWINCREATE;
typedef MAINWINCREATE* PMAINWINCREATE;

struct _window;

// this struct is an internal struct;它的大小必须和CONTROL相同;因为系统所有窗口
// 的内存都是静态统一分配的.
typedef struct _window
{
	/*
	 * These fields are similiar with CONTROL struct.
	 */
	CHAIN_NODE	  node;
	INT16		   dataType;	
	INT16		   winType;	  // the window type. 也就是subType
						   
	INT32		   left,  top;   // the position and size of main window.
	INT32		   right, bottom;
	INT32		   cl, ct;	   // the position and size of client area.
	INT32		   cr, cb;

	CHAIN_CONTROL   subWinList;
	WNDPROC		 winProc;// the address of main window procedure.

	DWORD		   dwStyle;	  // the styles of main window.
	DWORD		   dwExStyle;	// the extended styles of main window.
	
	GAL_PIXEL	   iBkColor;	 // the background color.
	GAL_PIXEL	   textColor;	// the text color.
	PLOGFONT		pLogFont;	 // pointer to logical font.

	DWORD		   dwAddData;	// the additional data.
	DWORD		   dwAddData2;   // the second addtional data.

	STRINGID		caption;	  // the caption of main window.
	INT16		   id;		   // the identifier of main window.
	STRINGID		helpid;
	INT16		   fblayer;
	GAL_PIXEL	  *pBkLineColor;

	INT16		   iLineBytes;		 //
	UCHAR		  *pBackground;		// 

	struct _window *pMainWin;	 // the main window that contains this control.
	HWND			hParent;	  // the parent of this window. 
								  // for main window, always be HWND_DESKTOP.
	HWND			hActiveChild; // the currently active child window.当前焦点控件句柄
	
	/* 下面是主菜单独有的 */
	HANDLE		  task;		  // the thread which creates this main window.
}WINDOW, * PMAINWIN, MAINWIN, * PWIN;

long DesktopProc (HWND hWnd, long message, WPARAM wParam, LPARAM lParam);


/**
 * \fn BOOL GUIAPI DestroyMainWindow (HWND hWnd)
 * \brief Destroies a main window.
 *
 * This function destroies the main window specified by \a hWnd.
 * It does not release all system resource used by the main window.
 * You should call \a MainWindowThreadCleanup to destroy the main window
 * actually.
 *
 * \param hWnd The handle to the main window.
 * \return TRUE on success, FALSE on error.
 *
 * \sa MainWindowThreadCleanup
 *
 * Example:
 *
 * \include destroymainwindow.c
 */
BOOL GUIAPI DestroyMainWindow (HWND hWnd);


/**
 * \fn HWND GUIAPI CreateMainWindow (PMAINWINCREATE pCreateStruct)
 * \brief Creates a main window.
 * 
 * This function creates a main window by using information in 
 * the structure pointed to by \a pCreateStruct, and returns 
 * the handle to the main window.
 *
 * \param pCreateStruct The pointer to a MAINWINCREATE structure.
 * \param pWin		  The pointer to a MAINWIN structure
 * \return The handle to the new main window; HWND_INVALID indicates an error.
 *
 * \sa MAINWINCREATE, styles
 *
 * Example:
 *
 * \include createmainwindow.c
 */
HWND GUIAPI CreateMainWindow (PMAINWINCREATE pCreateStruct, PMAINWIN pWin, HANDLE hTsk);

/**
 * \fn int DefaultMainWinProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
 * \brief Is the default main window callback procedure.
 *
 * This function is the default main window callback procedure.
 * You should call this function for all messages you do not want to handle
 * in your main window procedure.
 */
long DefaultMainWinProc (HWND hWnd, long message, WPARAM wParam, LPARAM lParam);

/**
 * \fn int DefaultControlProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
 * \brief Is the default control callback procedure.
 *
 * This function is the default control callback procedure.
 * You should call this function for all messages you do not want to handle
 * in your own control procedure.
 */
long DefaultControlProc (HWND hWnd, long message, WPARAM wParam, LPARAM lParam);

/**
 * \fn BOOL GUIAPI EndDialog (HWND hDlg, int endCode)
 * \brief Destroys a modal dialog box, causing MiniGUI to end any processing for the dialog box.
 *
 * This function destroys the modal dialog box \a hDlg created by \a DialogBoxIndirectParam
 * and ends any processing for the dialog box. The argument \a endCode will be returned
 * by \a DialogBoxIndirectParam as the return value.
 *
 * \param hDlg The handle to the dialog box.
 * \param endCode The value will be returned by \a DialogBoxIndirectParam.
 *
 * \return TRUE on success, FALSE on error.
 */
BOOL GUIAPI EndDialog (HWND hDlg, long endCode);


/* Dialog codes */
#define DLGC_WANTARROWS	 0x0001	  /* Control wants arrow keys		 */
#define DLGC_WANTTAB		0x0002	  /* Control wants tab keys		   */
#define DLGC_WANTALLKEYS	0x0004	  /* Control wants all keys		   */
#define DLGC_WANTCHARS	  0x0008	  /* Want MSG_CHAR messages		   */

#define DLGC_HASSETSEL	  0x0010	  /* Understands EM_SETSEL message	*/

#define DLGC_DEFPUSHBUTTON  0x0100	  /* Default pushbutton			   */
#define DLGC_PUSHBUTTON	 0x0200	  /* Non-default pushbutton		   */
#define DLGC_RADIOBUTTON	0x0400	  /* Radio button					 */
#define DLGC_3STATE		 0x0800	  /* 3 States button item			 */
#define DLGC_STATIC		 0x1000	  /* Static item: don't include	   */
#define DLGC_BUTTON		 0x2000	  /* Button item: can be checked	  */


/**
 * Structure which defines a control.
 */
typedef struct _CTRLDATA
{
	char*	   class_name;			 /** class name of the control */
	DWORD	   dwStyle;				/** control style */
	DWORD	   dwExStyle;			  /** control extended style */
	short	   x, y, w, h;			 /** control position in dialog */
	short	   id;					 /** control identifier */
	STRINGID	caption;				/** control caption */
	DWORD	   dwAddData;			  /** additional data */
	DWORD	   dwAddData2;			 /** additional data2 */
} CTRLDATA;
typedef CTRLDATA* PCTRLDATA;

/**
 * Structure which defines a dialogbox.
 *
 * Example:
 * 
 * \include dlgtemplate.c
 */
typedef struct _DLGTEMPLATE
{
	DWORD	   dwStyle;				/** dialog box style */
	DWORD	   dwExStyle;			  /** dialog box extended style */
	short	   x, y, w, h;			 /** dialog box position */
	STRINGID	caption;				/** dialog box caption */
	short	   controlnr;			  /** number of controls */
	PCTRLDATA   controls;			   /** poiter to control array */
	DWORD	   dwAddData;			  /** addtional data, must be zero */
} DLGTEMPLATE;
typedef DLGTEMPLATE* PDLGTEMPLATE;

/* 由于目前系统不支持内存的动态分配; 所有,在create窗口时,必须输入窗口变量的地址. */
typedef struct _wnd_mem {
	PMAINWIN   pMainWin;  /* 主窗口地址				*/
	PCONTROL   pControl;  /* 子窗口起始地址			*/
	INT16	  ctrlNum;   /* 子窗口控件的数量		  */
	HANDLE	 task;	  /* 主窗口所属的任务句柄	  */
} WNDMEM,  *PWNDMEM;


/**
 * \fn BOOL GUIAPI DestroyMainWindowIndirect (HWND hMainWin)
 * \brief Destroys a main window created by \a CreateMainWindowIndirectParam.
 *
 * This function destroys the main window which was created by 
 * \a CreateMainWindowIndirectParam function.
 *
 * \param hMainWnd The handle to the main window.
 *
 * \sa CreateMainWindowIndirectParam
 */
BOOL GUIAPI DestroyMainWindowIndirect (HWND hMainWin);


/**
 * \fn HWND GUIAPI CreateMainWindowIndirectParam (PDLGTEMPLATE pDlgTemplate, HWND hOwner, WNDPROC WndProc, LPARAM lParam) 
 * \brief Uses a dialog template to create a main window and controls in it, and pass a parameter to the window procedure.
 *
 * This function uses a dialog template pointed to by \a pDlgTemplate
 * to create a main window and controls in it. The parameter specified by
 * \a lParam will be passed to the window procedure as the second paramter
 * of MSG_INITDIALOG message.
 *
 * \param pDlgTemplate The pointer to a DLGTEMPLATE structure.
 * \param hOwner The handle to the hosting main window.
 * \param WndProc The window procedure of the new main window.
 * \param lParam The parameter will be passed to the window procedure.
 * \param hTsk   The handle of Task which Window belong to
 * \param pWin  The pointer to MAINWIN structure.
 * \param pNewCtrl  The pointer to Array of CONTROL.
 * \param ctrlNum   The Control structure numbers.
 * \return Handle to the new main window, HWND_INVALID on error.
 *
 * \sa DestroyMainWindowIndirect, DialogBoxIndirectParam, DLGTEMPLATE
 */
HWND GUIAPI CreateMainWindowIndirectParam (PDLGTEMPLATE pDlgTemplate, HWND hOwner,
						   INT16 id, WNDPROC WndProc, LPARAM lParam, PWNDMEM pMem );

/**
 * \def CreateMainWindowIndirect(pDlgTemplate, hOwner, WndProc)
 * \brief An simplified version of \a CreateMainWindowIndirectParam.
 *
 * This macro calls \a CreateMainWindowIndirectParam with \a lParam set to be 0.
#define CreateMainWindowIndirect(pDlgTemplate, hOwner, WndProc) \
			CreateMainWindowIndirectParam(pDlgTemplate, hOwner, WndProc, 0)
 */

/**
 * \fn HWND GUIAPI CreateWindowEx (const char* spClassName, const char* spCaption, DWORD dwStyle, DWORD dwExStyle, int id, int x, int y, int w, int h, HWND hParentWnd, DWORD dwAddData)
 * \brief Creates a child window with extended style.
 *
 * This function creates a child window (also known as "control") with extended style.
 * It specifies the window class, window title, window style, window extended style, 
 * and the initial position and size of the window. The function also specifies 
 * the window's parent or owner.
 *
 * \param spClassName The class name of the control.
 * \param caption The caption of the control.
 * \param dwStyle The control style.
 * \param dwExStyle The extended control style.
 * \param id The identifier of the control.
 * \param x,y The initial position of the control in the parent window.
 * \param w,h The initial size of the control.
 * \param hParentWnd The handle to the parent window.
 * \param dwAddData The first private additional data of the control.
 *		Note that some control classes use this value to initialize some properties of 
 *		the new control instance. For these control classes, you should pass a 
 *		valid value to it.
 * \param pCtrl  control struct
 * \return The handle to the new control, HWND_INVALID on error.
 *
 * \sa CreateMainWindow, CTRLDATA
 *
 * Example:
 *
 * \include createwindow.c
 */
HWND GUIAPI CreateWindowEx (const char* spClassName, STRINGID caption,
							DWORD dwStyle, DWORD dwExStyle, short id, 
							short x, short y, short w, short h, HWND hParentWnd, 
							DWORD dwAddData,DWORD dwAddData2, PCONTROL pCtrl);

/**
 * \def CreateWindow(class_name, caption, style, id, x, y, w, h, parent, add_data)
 * \brief A simplified version of \a CreateWindowEx.
 *
 * \sa CreateWindowEx
 */
#define CreateWindow(class_name, caption, style, id, x, y, w, h, parent, add_data, pCtrl ) \
		CreateWindowEx(class_name, caption, style, 0, id, x, y, w, h, parent, add_data, pCtrl)


/**
 * \fn BOOL GUIAPI DestroyWindow (HWND hWnd)
 * \brief Destroys a specified control.
 *
 * This function destroys the specified control \a hWnd, which is created
 * by \a CreateWindowEx.
 *
 * \param hWnd The handle to the control.
 * \return TRUE on success, FALSE on error.
 *
 * \sa CreateWindowEx
 */
BOOL GUIAPI DestroyWindow (HWND hWnd);

void GUIAPI DestroyAllControls (HWND hDlg);


/**
 * Structure defines a window class
 */
typedef struct _WNDCLASS
{
	/** the class name */
	char*   spClassName;

	/** window style for all instances of this window class */
	DWORD   dwStyle;

	/** extended window style for all instances of this window class */
	DWORD   dwExStyle;

	/** background color pixel value of all instances of this window class */
	GAL_PIXEL iBkColor;
	GAL_PIXEL textColor;

	/** window callback procedure of all instances of this window class */
	WNDPROC proc;

	/** the private additional data associated with this window class */
	DWORD dwAddData;
} WNDCLASS;
typedef WNDCLASS* PWNDCLASS;

#define MAINWINCLASSNAME	("MAINWINDOW")

/**
 * \fn BOOL GUIAPI RegisterWindowClass (PWNDCLASS pWndClass)
 * \brief Registers a window class. 
 *
 * This function registers a window class. 
 * Later on, you can create a window of a registered class.
 *
 * \param pWndClass The pointer to a WNDCLASS structure which specifies 
 *		the information of the window class.
 * \return TRUE on success, FALSE on error.
 * 
 * \sa UnregisterWindowClass, WNDCLASS
 *
 * Example:
 *
 * \include registerwindowclass.c
 */
BOOL GUIAPI RegisterWindowClass (PWNDCLASS pWndClass);

#define SW_HIDE			  0x0000
#define SW_SHOW			  0x0010
#define SW_SHOWNORMAL		0x0100

/**
 * \fn void GUIAPI UpdateWindow (HWND hWnd, BOOL bErase)
 * \brief Updates a window.
 *
 * This function updates the window specified by \a hWnd.
 * It will redraw the caption, the frame, and the menu bar of the window.
 * It will invalidate the client area of the window as well, and 
 * if \b bErase is TRUE, the client area will be erased by using background color.
 *
 * \param hWnd The handle to the window.
 * \param bErase Indicates whether to erase the client area of the window.
 *
 * \sa InvalidateRect
 */
void GUIAPI UpdateWindow (HWND hWnd, BOOL bErase);

/**
 * \fn BOOL GUIAPI ShowWindow (HWND hWnd, int iCmdShow)
 * \brief Shows or hides a window.
 *
 * This function shows or hides the window specified by \a hWnd.
 * 
 * \param hWnd The handle to the window.
 * \param iCmdShow The command to show or hide, can be one of 
 * the following values:
 *	  - SW_SHOW\n
 *		Shows the window.
 *	  - SW_HIDE\n
 *		Hides the window.
 *	  - SW_SHOWNORMAL\n
 *		Shows the window, and if the window is a main window 
 *		sets it to be the top most main window.
 * \return TRUE on sucess, otherwise FALSE.
 */
BOOL GUIAPI ShowWindow (HWND hWnd, int iCmdShow);

PMAINWIN GetMainWindow (HWND hWnd); // return main window contains hWnd.
PMAINWIN MainWindow (HWND hWnd);	// check whether hWnd is main window 


typedef enum _mwm_item_id {
	MWM_MINWIDTH,
	MWM_MINHEIGHT,
	MWM_BORDER,
	MWM_THICKFRAME,
	MWM_THINFRAME,
	MWM_CAPTIONY,
	
	MWM_ITEM_NUMBER
} MWM_ITEM_ID;
extern INT16 WinMainMetrics [];

#define  GetMainWinMetrics(iItem)	(WinMainMetrics[iItem])

/**
 * \fn BOOL GUIAPI EnableWindow (HWND hWnd, BOOL fEnable)
 * \brief Enables of disables a window.
 *
 * This function enables or disables mouse and keyboard input 
 * to the specified window \a hWnd. When input is disabled, the window 
 * does not receive input such as mouse clicks and key presses. 
 * When input is enabled, the window receives all input.
 *
 * \param hWnd The handle to the window.
 * \param fEnable Indicates whether to enable or disable the window, TRUE for enable.
 * \return The old enable state of the window.
 *
 * \sa IsWindowEnabled
 */
BOOL GUIAPI EnableWindow (HWND hWnd, BOOL fEnable);

/**
 * \fn BOOL GUIAPI IsWindowEnabled (HWND hWnd)
 * \brief Determines whether the specified window is enabled for mouse and keyboard input.
 *
 * This function returns the enable/disable state of the window specified by 
 * \a hWnd.
 *
 * \param hWnd The handle to the window.
 * \return The enable/disable state of the window, TRUE for enabled.
 * 
 * \sa EnableWindow
 */
BOOL GUIAPI IsWindowEnabled (HWND hWnd);

/**
 * \fn BOOL GUIAPI GetClientRect(HWND hWnd, PRECT prc)
 * \brief Retrives the client rectangle of a window.
 *
 * This function retrives the coordinates of the client area of 
 * the window specified by \a hWnd. The client coordinates specify 
 * the upper-left and lower-right corners of the client area. 
 * Because client coordinates are relative to the upper-left corner of 
 * a window's client area, the coordinates of the upper-left corner are always (0,0).
 *
 * \param hWnd The handle to the window.
 * \param prc The pointer to a RECT structure receives the client rectangle.
 * Note that the coordinates of the upper-left corner are always zero.
 *
 * \return TRUE on sucess, otherwise FALSE.
 *
 * \sa MoveWindow
 */
BOOL GUIAPI GetClientRect(HWND hWnd, PRECT prc);

/**
 * \fn int GUIAPI GetWindowBkColor (HWND hWnd)
 * \brief Returns the current background color of a window.
 *
 * This function returns the pixel value of the current background color of 
 * the window specified by \a hWnd.
 *
 * \param hWnd The handle to the window.
 * \return The pixel value of the background color.
 *
 * /sa SetWindowBkColor
 */
GAL_PIXEL GUIAPI GetWindowBkColor (HWND hWnd);

GAL_PIXEL GUIAPI GetWindowTextColor (HWND hWnd);

/**
 * \fn int GUIAPI SetWindowBkColor (HWND hWnd, int new_bkcolor)
 * \brief Sets the background color of a window.
 *
 * This function sets the background color of the specified window \a hWnd
 * to be new pixel value \a new_backcolor. You should call \a UpdateWindow
 * or \a InvalidateRect in order that the new background color run into
 * affect.
 *
 * \param hWnd The handle to the window.
 * \param new_bkcolor The pixel value of the new background color.
 * \return The pixel value of the old background color.
 *
 * /sa GetWindowBkColor
 */
GAL_PIXEL  GUIAPI  SetWindowBkColor (HWND hWnd, GAL_PIXEL new_bkcolor);

GAL_PIXEL  GUIAPI  SetWindowTextColor (HWND hWnd, GAL_PIXEL new_color);

/**
 * \fn PLOGFONT GUIAPI GetWindowFont (HWND hWnd)
 * \brief Retrives the default font of a window.
 *
 * This function retrives the default font of the specified 
 * window \a hWnd.
 *
 * \param hWnd The handle to the window.
 * \return The default logical font of the window.
 *
 * /sa SetWindowFont
 */
PLOGFONT GUIAPI GetWindowFont (HWND hWnd);

/**
 * \fn PLOGFONT GUIAPI SetWindowFont (HWND hWnd, PLOGFONT pLogFont)
 * \brief Sets the default font of a window.
 *
 * This function sets the default font of the specified window \a hWnd
 * to be the logical font \a pLogFont. This function will send an
 * MSG_FONTCHANGING message to the window. If the handler of the message
 * returns non-zero value, this function will return immediately with the 
 * unchanged default font. Or, after the new default font set, this function 
 * will send an MSG_FONTCHANGED message to the window as a notification.
 *
 * \param hWnd The handle to the window.
 * \param pLogFont The new default logical font. If it is NULL, this function
 * will set the default font to be the system wchar font.
 * \return The old default logical font of the window, NULL on error.
 *
 * \sa GetWindowFont, GetSystemFont
 */
PLOGFONT GUIAPI SetWindowFont (HWND hWnd, PLOGFONT pLogFont);

/**
 * \fn HCURSOR GUIAPI GetWindowCursor (HWND hWnd)
 * \brief Retrives the current cursor of a window.
 *
 * This function retrives the current cursor of the specified
 * window \a hWnd.
 *
 * \param hWnd The handle to the window.
 * \return The handle to the cursor.
 *
 * \sa SetWindowCursor
 */
HCURSOR GUIAPI GetWindowCursor (HWND hWnd);


/**
 * \fn DWORD GUIAPI GetWindowStyle (HWND hWnd)
 * \brief Retrives the style of a window.
 *
 * This function retrives the style of the window specified by \a hWnd.
 *
 * \param hWnd The handle to the window.
 * \return The style of the window.
 *
 * \sa GetWindowExStyle
 */
DWORD GUIAPI GetWindowStyle (HWND hWnd);

/**
 * \fn DWORD GUIAPI GetWindowExStyle (HWND hWnd)
 * \brief Retrives the extended style of a window.
 *
 * This function retrives the extended style of the window specified by \a hWnd.
 *
 * \param hWnd The handle to the window.
 * \return The extended style of the window.
 *
 * \sa GetWindowStyle
 */
DWORD GUIAPI GetWindowExStyle (HWND hWnd);

BOOL GUIAPI ExcludeWindowStyle (HWND hWnd, DWORD dwStyle);
BOOL GUIAPI IncludeWindowStyle (HWND hWnd, DWORD dwStyle);

/**
 * \fn WNDPROC GUIAPI GetWindowCallbackProc (HWND hWnd)
 * \brief Retrives the callback procedure of a window.
 *
 * This function retrives the window callback procedure of the specified window
 * \a hWnd.
 *
 * \param hWnd The handle to the window.
 * \return The callback procedure of the window.
 *
 * \sa SetWindowCallbackProc
 */
WNDPROC GUIAPI GetWindowCallbackProc (HWND hWnd);

/**
 * \fn WNDPROC GUIAPI SetWindowCallbackProc (HWND hWnd, WNDPROC newProc)
 * \brief Sets the callback procedure of a window.
 *
 * This function sets the window callback procedure of the specified window
 * \a hWnd to be the procedure \a newProc.
 *
 * \param hWnd The handle to the window.
 * \param newProc The new callback procedure of the window.
 * \return The old callback procedure of the window.
 *
 * \sa GetWindowCallbackProc
 *
 * Example:
 *
 * \include subclass.c
 */
WNDPROC GUIAPI SetWindowCallbackProc (HWND hWnd, WNDPROC newProc);

/**
 * \fn DWORD GUIAPI GetWindowAdditionalData (HWND hWnd)
 * \brief Retrives the first additional data of a window.
 *
 * This function retrives the first additional data of the specified window
 * \a hWnd.
 * 
 * \param hWnd The handle to the window.
 * \return The first additional data of the window.
 *
 * \sa SetWindowAdditionalData
 */
DWORD GUIAPI GetWindowAdditionalData (HWND hWnd);

/**
 * \fn DWORD GUIAPI SetWindowAdditionalData (HWND hWnd, DWORD newData)
 * \brief Sets the first additional data of a window.
 *
 * This function sets the first additional data of the specified window
 * \a hWnd.
 * 
 * \param hWnd The handle to the window.
 * \param newData The new first additional data of the window.
 * \return The old first additional data of the window.
 *
 * \note For a dialog box created by \a DialogBoxIndirectParam, its first additional
 * data used internally by the system to save the return value of the box.
 * So you should avoid setting the first additional data of a dialog box.
 *
 * \sa GetWindowAdditionalData
 */
DWORD GUIAPI SetWindowAdditionalData (HWND hWnd, DWORD newData);

/**
 * \fn DWORD GUIAPI GetWindowAdditionalData2 (HWND hWnd)
 * \brief Retrives the second additional data of a window.
 *
 * This function retrives the second additional data of the specified window
 * \a hWnd.
 * 
 * \param hWnd The handle to the window.
 * \return The second additional data of the window.
 *
 * \sa SetWindowAdditionalData2
 */
DWORD GUIAPI GetWindowAdditionalData2 (HWND hWnd);

/**
 * \fn DWORD GUIAPI SetWindowAdditionalData2 (HWND hWnd, DWORD newData)
 * \brief Sets the second additional data of a window.
 *
 * This function sets the second additional data of the specified window
 * \a hWnd.
 * 
 * \param hWnd The handle to the window.
 * \param newData The new second additional data of the window.
 * \return The old second additional data of the window.
 *
 * \note For a control created by \a CreateWindow, its second additional
 * data is reserved for internal use. So you should avoid setting the 
 * second additional data of a control.
 *
 * \sa GetWindowAdditionalData2
 */
DWORD GUIAPI SetWindowAdditionalData2 (HWND hWnd, DWORD newData);

/**
 * \fn DWORD GUIAPI GetWindowClassAdditionalData (HWND hWnd)
 * \brief Retrives the additional data of a control class.
 *
 * This function retrives the additional data of the control class to which
 * the specified control \a hWnd belongs.
 *
 * \param hWnd The handle to the control.
 * \return The additional data of the control class to which the control belongs.
 * Note that this function always returns zero for the main window.
 *
 * \sa SetWindowClassAdditionalData
 */
DWORD GUIAPI GetWindowClassAdditionalData (HWND hWnd);

/**
 * \fn DWORD GUIAPI SetWindowClassAdditionalData (HWND hWnd, DWORD newData)
 * \brief Sets the additional data of a control class.
 *
 * This function sets the additional data of the control class to which
 * the specified control \a hWnd belongs.
 *
 * \param hWnd The handle to the control.
 * \param newData The new additional data of the control class.
 * \return The old additional data of the control class.
 *
 * \note This function always does nothing and returns zero for the main window.
 *
 * \sa SetWindowClassAdditionalData
 */
DWORD GUIAPI SetWindowClassAdditionalData (HWND hWnd, DWORD newData);

/**
 * \fn const char* GUIAPI GetWindowCaption (HWND hWnd)
 * \brief Retrives the caption of a window.
 *
 * This function retrives the caption of the specified window \a hWnd.
 *
 * \param hWnd The handle to the window.
 * \return The pointer to the caption string of the window.
 *
 * \sa SetWindowCaption
 */
INT16  GUIAPI GetWindowCaption (HWND hWnd);

/**
 * \fn BOOL GUIAPI SetWindowCaption (HWND hWnd, const char* spCaption)
 * \brief Sets the captionn of a window.
 *
 * This function sets the caption of the specified window \a hWnd.
 *
 * \param hWnd The handle to the window.
 * \param spCaption The pointer to the new caption of the window.
 * \return TRUE on success, otherwise FALSE.
 *
 * \sa GetWindowCaption, SetWindowText
 */
BOOL GUIAPI SetWindowCaption (HWND hWnd, INT16 caption);

/**
 * \fn BOOL GUIAPI InvalidateRect(HWND hWnd, const RECT* prc, BOOL bEraseBkgnd)
 * \brief Makes a rectangle region in the client area of a window invalid.
 *
 * This function adds a rectangle pointed to by \a prc to the specified window's 
 * update region. The update region represents the portion of the window's client area 
 * that must be redrawn, and erase background if argument \a bReaseBkgnd is set.
 *
 * \param hWnd The handle to the window.
 * \param prc The pointer to a RECT structure which defines the invalid rectangle.
 * \param bEraseBkgnd Indicates whether the background should be erased.
 * \return TRUE on success, otherwise FALSE.
 *
 * \sa MSG_PAINT
 */
BOOL GUIAPI InvalidateRect(HWND hWnd, const RECT* prc, BOOL bEraseBkgnd);

/**
 * \fn HDC GUIAPI BeginPaint(HWND hWnd)
 * \brief Prepares a window for painting.
 *
 * This function prepares the specified window \a hWnd for painting.
 * This function is called in the handler of MSG_PAINT message normally.
 * It returns a device context including the update region of the window.
 * When you are done with the device context, you should call \a EndPaint
 * to finish the painting of the window.
 *
 * \param hWnd The handle to the window.
 * \return The device context.
 *
 * \sa EndPaint
 */
/* HDC GUIAPI BeginPaint(HWND hWnd);
 */
/**
 * \fn int GUIAPI DialogBoxIndirectParam (PDLGTEMPLATE pDlgTemplate, HWND hOwner, WNDPROC DlgProc, LPARAM lParam)
 * \brief Creates a modal dialog box from a dialog box template in memory.
 *
 * This function creates a modal dialog box from a dialog box template in memory. 
 * Before displaying the dialog box, the function passes an application-defined value to 
 * the dialog box procedure as the second parameter of the MSG_INITDIALOG message. 
 * An application can use this value to initialize dialog box controls.
 *
 * \param pDlgTemplate The pointer to a DLGTEMPLATE structure.
 * \param hOwner The handle to the hosting main window.
 * \param WndProc The window procedure of the new dialog box.
 * \param lParam The parameter will be passed to the window procedure.
 * \return Handle to the new main window, HWND_INVALID on error.
 *
 * \sa CreateMainWindowIndirectParam, DLGTEMPLATE
 *
 * Example:
 *
 * \include dialogbox.c
 */
INT32  GUIAPI DialogBoxIndirectParam (PDLGTEMPLATE pDlgTemplate, HWND hOwner, INT16 id,
									  WNDPROC DlgProc, LPARAM lParam, PWNDMEM pMem);

/**
 * \fn void GUIAPI EndPaint(HWND hWnd, HDC hdc)
 * \brief Marks the end of painting in a window.
 *
 * This function marks the end of painting in the specified window. 
 * This function is required for each call to the \a BeginPaint function, 
 * but only after painting is complete.
 *
 * \param hWnd The handle to the window.
 * \param hdc The device context returned by BeginPaint.
 *
 * \sa BeginPaint
 */
/**
void GUIAPI EndPaint(HWND hWnd, HDC hdc);
 */

/**
 * \fn BOOL GUIAPI GetUpdateRect (HWND hWnd, RECT* update_rect)
 * \brief Retrives the bounding box of the update region of a window.
 *
 * This function retrives the bounding box of the update region of
 * the specified window \a hWnd.
 *
 * \param hWnd The handle to the window.
 * \param update_rect The pointer to a RECT structure which will contains 
 * the bounding box of the update region.
 * \return TRUE on success, otherwise FALSE.
 *
 * \sa InvalidateRect
 */
BOOL GUIAPI GetUpdateRect (HWND hWnd, RECT* update_rect);

/**
 * \fn int GUIAPI ClientWidthToWindowWidth (DWORD dwStyle, int cw)
 * \brief Calculates main window width from the width of the client area.
 *
 * This function calculates the main window width from the width of the client area.
 *
 * \param dwStyle The style of the main window.
 * \param cw The width of the client area.
 * \return The width of the main window.
 *
 * \sa ClientHeightToWindowHeight
 */
int GUIAPI ClientWidthToWindowWidth (DWORD dwStyle, int cw);

/**
 * \fn int GUIAPI ClientHeightToWindowHeight (DWORD dwStyle, int ch, BOOL hasMenu)
 * \brief Calculates main window height from the height of the client area.
 *
 * This function calculates the main window height from the height of
 * the client area.
 *
 * \param dwStyle The style of the main window.
 * \param ch The height of the client area.
 * \param hasMenu Indicates whether the main window has menu.
 * \return The height of the main window.
 *
 * \sa ClientWidthToWindowWidth
 */
int GUIAPI ClientHeightToWindowHeight (DWORD dwStyle, int ch, BOOL hasMenu);

/**
 * \fn void GUIAPI ClientToScreen (HWND hWnd, int* x, int* y)
 * \brief Converts the client coordinates of a point to screen coordinates.
 *
 * This function converts the client coordinates of the specified point \a (*x,*y)
 * in the specified window \a hWnd to screen coordinates.
 *
 * \param hWnd The handle to the window.
 * \param x,y The pointer to the coordinates.
 * 
 * \sa ScreenToClient
 */
void GUIAPI ClientToScreen (HWND hWnd, long* x, long* y);

/**
 * \fn void GUIAPI ScreenToClient (HWND hWnd, int* x, int* y)
 * \brief Converts the screen coordinates of a point to client coordinates.
 *
 * This function converts the screen coordinates of the specified point \a (*x,*y)
 * to client coordinates of the specified window \a hWnd 
 *
 * \param hWnd The handle to the window.
 * \param x,y The pointer to the coordinates.
 * 
 * \sa ClientToScreen
 */
void GUIAPI ScreenToClient (HWND hWnd, long* x, long* y);

/**
 * \fn void GUIAPI WindowToScreen (HWND hWnd, int* x, int* y)
 * \brief Converts the window coordinates of a point to screen coordinates.
 *
 * This function converts the window coordinates of the specified point \a (*x,*y)
 * in the specified window \a hWnd to the screen coordinates.
 *
 * \param hWnd The handle to the window.
 * \param x,y The pointer to the coordinates.
 * 
 * \sa ScreenToWindow
 */
void GUIAPI WindowToScreen (HWND hWnd, long* x, long* y);

/**
 * \fn void GUIAPI ScreenToWindow (HWND hWnd, int* x, int* y)
 * \brief Converts the screen coordinates of a point to window coordinates.
 *
 * This function converts the screen coordinates of the specified point \a (*x,*y)
 * to the window coordinates of the specfied window \a hWnd.
 *
 * \param hWnd The handle to the window.
 * \param x,y The pointer to the coordinates.
 * 
 * \sa WindowToScreen
 */
void GUIAPI ScreenToWindow (HWND hWnd, long* x, long* y);

/**
 * \fn BOOL GUIAPI IsMainWindow (HWND hWnd)
 * \brief Determines whether a window is a main window.
 *
 * This function determines whether the specified window \a hWnd is a main window.
 *
 * \param hWnd The handle to the window.
 * \return TRUE for main window, otherwise FALSE.
 *
 * \sa IsControl, IsWindow
 */
BOOL GUIAPI IsMainWindow (HWND hWnd);

/**
 * \fn BOOL GUIAPI IsControl (HWND hWnd)
 * \brief Determines whether a window is a control.
 *
 * This function determines whether the specified window \a hWnd is a control.
 *
 * \param hWnd The handle to the window.
 * \return TRUE for control, otherwise FALSE.
 *
 * \sa IsMainWindow, IsWindow
 */
BOOL GUIAPI IsControl (HWND hWnd);

/**
 * \fn BOOL GUIAPI IsWindow (HWND hWnd)
 * \brief Determines whether a window handle identifies an existing window.
 *
 * This function determines whether the specified window handle \a hWnd 
 * identifies an existing window.
 *
 * \param hWnd The window handle.
 * \return TRUE for window, otherwise FALSE.
 *
 * \sa IsMainWindow, IsControl
 */
BOOL GUIAPI IsWindow (HWND hWnd);

/**
 * \fn HWND GUIAPI GetParent (HWND hWnd)
 * \brief Retrieves the handle to a child window's parent window.
 *
 * This function retrieves the handle to the specified child window's parent window.
 *
 * \param hWnd The handle to the child window.
 * \return The handle to the parent, HWND_INVALID indicates an error.
 *
 * \note For a main window, this function always returns HWND_DESKTOP.
 *
 * \sa GetMainWindowHandle
 */
HWND GUIAPI GetParent (HWND hWnd);

/**
 * \fn HWND GUIAPI GetMainWindowHandle (HWND hWnd)
 * \brief Retrives the handle to the main window contains a window.
 *
 * This function retrives the handle to the main window which contains the
 * specified window \a hWnd.
 *
 * \param hWnd The handle to the window.
 * \return The handle to the main window, HWND_DEKSTOP indicates an error.
 *
 * \note For a main window, this function always returns the handle to itself.
 *
 * \sa GetParent
 */
HWND GUIAPI GetMainWindowHandle (HWND hWnd);

/**
 * \fn BOOL GUIAPI IsWindowVisible (HWND hWnd)
 * \brief Retrieves the visibility state of a window.
 *
 * This function retrives the visibility state of the specified window \a hWnd.
 *
 * \param hWnd The handle to the window.
 * \return TRUE if visible, otherwise FALSE.
 *
 * \sa ShowWindow
 */
BOOL GUIAPI IsWindowVisible (HWND hWnd);

/**
 * \fn BOOL GUIAPI GetWindowRect (HWND hWnd, PRECT prc)
 * \brief Retrives the dimensions of the bounding rectangle of a window. 
 *
 * This function retrives the dimension of the bounding rectangle of
 * the specified window \a hWnd. The dimensions are given in screen coordinates 
 * that are relative to the upper-left corner of the screen.
 *
 * \param hWnd The handle to the window.
 * \param prc The pointer to a RECT structure which will contains the window rectangle.
 * \return TRUE on success, otherwise FALSE.
 *
 * \sa GetClientRect
 */
BOOL GUIAPI GetWindowRect (HWND hWnd, PRECT prc);


/**
 * \fn int GUIAPI GetWindowTextLength (HWND hWnd)
 * \brief Retrieves the length of a window's text.
 *
 * This function retrieves the length, in characters, of the specified window's text.
 * The function retrieves the length of the text by sending an MSG_GETTEXTLENGTH message
 * to the window.
 *
 * \param hWnd The handle to the window.
 * \return The length of the window's text.
 *
 * \sa GetWindowText
 */
long  GUIAPI GetWindowTextLength (HWND hWnd);

/**
 * \fn int GUIAPI GetWindowText (HWND hWnd, char* spString, int nMaxLen)
 * \brief Copies the text of a window's into a buffer.
 *
 * This function copies the text of the specified window \a hWnd into the buffer
 * pointed to by \a spString. The function gets the window text by sending
 * an MSG_GETTEXT message to the window.
 *
 * \param hWnd The handle to the window.
 * \param stringP The pointer to a string ID.
 * \return The length of the window text string.
 *
 * \sa GetWindowCaption, SetWindowText
 */
long  GUIAPI GetWindowText (HWND hWnd, INT16 *stringP);

/**
 * \fn BOOL GUIAPI SetWindowText (HWND hWnd, const char* spString)
 * \brief Sets the text of a window.
 *
 * This function copies the string in the buffer pointed to by \a spString
 * to be the text of the specified window \a hWnd. The function sets
 * the window text by sending an MSG_SETTEXT message to the window.
 *
 * \param hWnd   The handle to the window.
 * \param str_Id The sting ID.
 * \return TRUE on success, otherwise FALSE.
 *
 * \sa SetWindowCaption, GetWindowText
 */
BOOL GUIAPI SetWindowText (HWND hWnd,  INT16 str_id);

BOOL GUIAPI SetWindowItem (HWND hWnd,DWORD addData2);

/**
 * \fn HWND GUIAPI GetFocusChild (HWND hWnd)
 * \brief Retrieves the handle to the window's active child that has the keyboard focus.
 *
 * This function retrives the handle to the window's active child that has
 * the keyboard focus.
 *
 * \param hWnd The handle to the window.
 * \return The handle to the active child.
 *
 * \sa SetFocusChild
 */
HWND GUIAPI GetFocusChild (HWND hWnd);

/**
 * \fn HWND GUIAPI SetFocusChild (HWND hWnd)
 * \brief Sets the active child of a window.
 *
 * This function sets the specified window \a hWnd as the active child of its parent.
 *
 * \param hWnd The handle to the window.
 * \return The handle to the old active child of its parent.
 *
 * \sa GetFocusChild
 */
HWND GUIAPI SetFocusChild (HWND hWnd);

#define SetFocus SetFocusChild
#define GetFocus GetFocusChild

/**
 * \fn HWND GUIAPI GetActiveWindow (void)
 * \brief Retrieves the main window handle to the active main window.
 *
 * This function retrives the main window handle to the active main window which
 * receives the input.
 *
 * \return The handle to the active main window.
 *
 * \sa SetActiveWindow, GetFocusChild
 */
HWND GUIAPI GetActiveWindow (void);

/**
 * \fn HWND GUIAPI SetActiveWindow (HWND hMainWnd)
 * \brief Sets a main window to be the active main window.
 *
 * This function sets the specified main window \a hMainWnd to be the 
 * active main window which receives the input.
 *
 * \param hMainWnd The handle to the new active main window.
 * \return The handle to the old active main window.
 *
 * \sa GetActiveWindow, SetFocusChild
 */
HWND GUIAPI SetActiveWindow (HWND hMainWnd);

#define GetForegroundWindow GetActiveWindow
#define SetForegroundWindow SetActiveWindow

/**
 * \fn const char* GUIAPI GetClassName (HWND hWnd)
 * \brief Retrieves the name of the class to which the specified window belongs.
 *
 * This function retrieves the name of the class to which 
 * the specified window \a hWnd belongs.
 *
 * \param hWnd The handle to the window.
 * \return The pointer to a const class name string, NULL on error.
 *
 * \sa RegisterWindowClass
 */
const char* GUIAPI GetClassName (HWND hWnd);


/**
 * \fn int GUIAPI DefaultDialogProc (HWND hWnd, int message, WPARAM wParam, LPARAM lParam)
 * \brief The default dialog box procedure.
 *
 * This function is the default dialog box procedure. 
 * You should call this function in your dialog box procedure 
 * to process the unhandled messages.
 *
 * \param hWnd The handle to the window.
 * \param message The message identifier.
 * \param wParam The first message parameter.
 * \param lParam The second message parameter.
 * \return The return value of the message handler.
 */
INT32  GUIAPI DefaultDialogProc (HWND hWnd, INT32 message, 
								 WPARAM wParam, LPARAM lParam);

/**
 * \fn int GUIAPI GetDlgCtrlID (HWND hwndCtl)
 * \brief Gets the integer identifier of a control.
 *
 * This function gets the integer identifier of the control \a hwndCtl.
 *
 * \param hwndCtl The handle to the control.
 * \return The identifier of the control, -1 for error.
 *
 * \sa GetDlgItem
 */
INT32  GUIAPI GetDlgCtrlID (HWND hwndCtl);

/**
 * \fn HWND GUIAPI GetDlgItem (HWND hDlg, int nIDDlgItem)
 * \brief Retrives the handle to a control in a dialog box.
 *
 * This function retrives the handle to a control, whose identifier is \a nIDDlgItem,
 * in the specified dialog box \a hDlg.
 *
 * \param hDlg The handle to the dialog box.
 * \param nIDDlgItem The identifier of the control.
 * \return The handle to the control, zero for not found.
 */
HWND GUIAPI GetDlgItem (HWND hDlg, INT32 nIDDlgItem);

/**
 * \fn UINT GUIAPI GetDlgItemInt (HWND hDlg, int nIDDlgItem, BOOL *lpTranslated, BOOL bSigned)
 * \brief Translates the text of a control in a dialog box into an integer value.
 *
 * This function translates the text of the control, whose identifier is \a nIDDlgItem
 * in the dialog box \a hDlg into an integer value.
 *
 * \param hDlg The handle to the dialog box.
 * \param nIDDlgItem The identifier of the control.
 * \param lpTranslated The pointer to a boolean value, which indicates whether
 *		translated successfully.
 * \param bSigned Indicates whether handle the text as a signed integer.
 * \return The translated 32-bit integer.
 *
 * \note MiniGUI uses \a strtol or \a strtoul to convert the string value 
 * to a 32-bit integer, and pass the base as 0. Thus, the valid string value 
 * should be in the following forms:
 *
 *  - [+|-]0x[0-9|A-F]*\n
 *	Will be read in base 16.
 *  - [+|-]0[0-7]*\n
 *	Will be read in base 8.
 *  - [+|-][1-9][0-9]*\n
 *	Will be read in base 10.
 *
 * \sa GetDlgItemText, SetDlgItemInt
 */
UINT32 GUIAPI GetDlgItemInt (HWND hDlg, int nIDDlgItem, BOOL *lpTranslated, BOOL bSigned);

/**
 * \fn int GUIAPI GetDlgItemText (HWND hDlg, int nIDDlgItem, char* lpString, int nMaxCount)
 * \brief Retrieves the title or text associated with a control in a dialog box.
 *
 * This function retrives the title or text associated with a control, whose
 * identifier is \a nIDDlgItem in the dialog box \a hDlg.
 *
 * \param hDlg The handle to the dialog box.
 * \param nIDDlgItem The identifier of the control.
 * \param lpString The pointer to a buffer which receives the text.
 * \param nMaxCount The maximal length of the string, not including the null character.
 * \return The length of the null-terminated text.
 *
 * \note The buffer should at least have size of (\a nMaxCount + 1).
 *
 * \sa GetDlgItemInt, GetDlgItemText2
 */
INT32  GUIAPI GetDlgItemText (HWND hDlg, INT32 nIDDlgItem, CHAR* lpString, INT32 nMaxCount);

/**
 * \fn char* GUIAPI GetDlgItemText2 (HWND hDlg, int id, int* lenPtr)
 * \brief Retrieves the title or text associated with a control in a dialog box.
 *
 * This function is similiar as \a GetDlgItemText function,
 * but it allocates memory for the text and returns the pointer 
 * to the allocated buffer. You should free the buffer when done by using
 * \a free function.
 *
 * \param hDlg The handle to the dialog box.
 * \param id The identifier of the control.
 * \param lenPtr The pointer to an integer which receives the length of the text
 *		if it is not NULL.
 * \return The pointer to the allocated buffer.
 *
 * \sa GetDlgItemText
 */
CHAR* GUIAPI GetDlgItemText2 (HWND hDlg, INT32 id, INT32* lenPtr);

/**
 * \fn HWND GUIAPI GetNextDlgGroupItem (HWND hDlg, HWND hCtl, BOOL bPrevious)
 * \brief Retrieves the handle to the first control in a group of controls that precedes
 *		(or follows) the specified control in a dialog box.
 *
 * This function retrieves the handle to the first control in 
 * a group of controls that precedes (or follows) the specified control \a hCtl 
 * in the dialog box \a hDlg.
 *
 * \param hDlg The handle to the dialog box.
 * \param hCtl The handle to the control.
 * \param bPrevious A boolean value indicates to retrive the preceding or following control.
 *		TRUE for preceding control.
 * \return The handle to the preceding or following control.
 *
 * \sa GetNextDlgTabItem
 */
HWND GUIAPI GetNextDlgGroupItem (HWND hDlg, HWND hCtl, BOOL bPrevious);

/**
 * \fn HWND GUIAPI GetNextDlgTabItem (HWND hDlg, HWND hCtl, BOOL bPrevious)
 * \brief Retrieves the handle to the first control that has the WS_TABSTOP style 
 *		that precedes (or follows) the specified control.
 *
 * This function retrieves the handle to the first control that has 
 * the WS_TABSTOP style that precedes (or follows) the specified control \a hCtl
 * in the dialog box \a hDlg.
 *
 * \param hDlg The handle to the dialog box.
 * \param hCtl The handle to the control.
 * \param bPrevious A boolean value indicates to retrive the preceding or following control.
 *		TRUE for preceding control.
 * \return The handle to the preceding or following control.
 *
 * \sa GetNextDlgGroupItem
 */
HWND GUIAPI GetNextDlgTabItem (HWND hDlg, HWND hCtl, BOOL bPrevious);

/**
 * \fn int GUIAPI SendDlgItemMessage (HWND hDlg, int nIDDlgItem, int message, WPARAM wParam, LPARAM lParam)
 * \brief Sends a message to the specified control in a dialog box.
 *
 * This function sends a message specified by (\a message, \a wParam, \a lParam)
 * to the specified control whose identifier is \a nIDDlgItem in the dialog box \a hDlg.
 *
 * \param hDlg The handle to the dialog box.
 * \param nIDDlgItem The identifier of the control.
 * \param message The message identifier.
 * \param wParam The first message parameter.
 * \param lParam The second message parameter.
 * \return The return value of the message handler.
 *
 * \sa SendMessage, GetDlgItem
 */
INT32  GUIAPI SendDlgItemMessage ( HWND hDlg, INT16 nIDDlgItem, 
								   INT16 message, WPARAM wParam, LPARAM lParam);

//格式见enum FORMAT_TYPE, control.h;
#define  DT_FORM_MASK		 0x0000000FL  //格式, 3位整数, 还是7.2位浮点

#define  DT_SIGNED			0x00000010L  //有符号.
#define  DT_SIGNED_MASK	   0x000000F0L  //符号, 有符号,还是没有符号.

#define  DT_ALIGN_RIGHT	   0x00000000L  //右对齐.
#define  DT_ALIGN_LEFT		0x00000100L  //左对齐
#define  DT_ALIGN_MASK		0x00000F00L  //对齐方式.


/**
 * \fn BOOL GUIAPI SetDlgItemInt (HWND hDlg, int nIDDlgItem, UINT uValue, BOOL bSigned)
 * \brief Sets the text of a control in a dialog box to the string 
 *		representation of a specified integer value.
 *
 * This function sets the text of the control whose identifier is \a nIDDlgItem 
 * in the dialog box \a hDlg to the string representation of 
 * the specified integer value \a nValue.
 *
 * \param hDlg The handle to the dialog box.
 * \param nIDDlgItem The identifier of the control.
 * \param uValue The 32-bit integer value.
 * \param nFormat , spefify the format of string maked.
 * \return TRUE on success, FALSE on error.
 *
 * \sa GetDlgItemInt, SetDlgItemText
 */
BOOL GUIAPI SetDlgItemInt (HWND hDlg, long nIDDlgItem, UINT32 uValue, DWORD nFormat);

	 /**
	  * \defgroup msgbox_fns Message box operations
	  * @{
	  */
#ifdef _CTRL_BUTTON

/**
 * \fn void GUIAPI CheckDlgButton (HWND hDlg, int nIDDlgItem, int nCheck)
 * \brief Changes the check status of a button control.
 *
 * This function changes the check status of the button control whose 
 * identifier is \a nIDDlgItem in the dialog box \a hDlg.
 *
 * \param hDlg The handle to the dialog box.
 * \param nIDDlgItem The identifier of the control.
 * \param nCheck The state of the button. If the button is a normal button,
 *		the value being zero means the button is checked, otherwise unchecked.
 *		If the button is a special button with three states, the value 
 *		can be one of the following values:
 *		  - BST_UNCHECKED\n
 *			The button is unchecked.
 *		  - BST_CHECKED\n
 *			The button is checked.
 *		  - BST_INDETERMINATE\n
 *			The button is in indeterminate state.
 *
 * \sa CheckRadioButton, IsDlgButtonChecked
 */
VOID GUIAPI CheckDlgButton (HWND hDlg, INT32 nIDDlgItem, INT32 nCheck);

/**
 * \fn void GUIAPI CheckRadioButton (HWND hDlg, int idFirstButton, int idLastButton, int idCheckButton)
 * \brief Adds a check mark to (checks) a specified radio button in a group 
 *		and removes a check mark from (clears) all other radio buttons in the group.
 *
 * This function adds a check mark to (checks) the specified radio button \a idCheckButton
 * in a group between \a idFirstButton and \a idLastButton, and removes 
 * a check mark from (clears) all other radio buttons in the group.
 *
 * \param hDlg The handle to the dialog box.
 * \param idFirstButton The identifier of the first control in the group.
 * \param idLastButton The identifier of the last control in the group.
 * \param idCheckButton The identifier of the control to be checked.
 *
 * \sa CheckDlgButton
 */
VOID GUIAPI CheckRadioButton (HWND hDlg, 
				INT32 idFirstButton, INT32 idLastButton, INT32 idCheckButton);

/**
 * \fn int GUIAPI IsDlgButtonChecked (HWND hDlg, int idButton)
 * \brief Determines whether a button control has a check mark next to it or 
 *		whether a three-state button control is grayed, checked, or neither.
 *
 * This function determines whether the button control whose identifier is \a idButton
 * has a check mark next to it or whether a three-state button control is grayed, 
 * checked, or neither.
 *
 * \param hDlg The handle to the dialog box.
 * \param idButton The identifier of the button.
 * \return The check state of the button. If the button is a normal button,
 *		the value being zero means the button is checked, otherwise unchecked.
 *		If the button is a special button with three states, the value 
 *		can be one of the following values:
 *		  - BST_UNCHECKED\n
 *			The button is unchecked.
 *		  - BST_CHECKED\n
 *			The button is checked.
 *		  - BST_INDETERMINATE\n
 *			The button is in indeterminate state.
 *
 * \sa CheckDlgButton
 */
INT32  GUIAPI IsDlgButtonChecked (HWND hDlg, INT32 idButton); 
#endif

	 /** @} end of dialog_fns */

#if defined(_CTRL_STATIC) && defined (_CTRL_BUTTON)


/* 系统控件触发的命令id, 的范围.最大最小值. */
#define MINID_RESERVED	  0xF001
#define MAXID_RESERVED	  0xFFFF

/* for Message box use, 定义消息对话框的类型,行为.  eric */
#define MB_OK				   0x00000000L
#define MB_OKCANCEL			 0x00000001L
#define MB_YESNO				0x00000002L
#define MB_RETRYCANCEL		  0x00000003L
#define MB_ABORTRETRYIGNORE	 0x00000004L
#define MB_YESNOCANCEL		  0x00000005L
#define MB_CANCELASBACK		 0x00000008L  /* customized style */
#define MB_TYPEMASK			 0x00000007L

#define MB_ICONHAND			 0x00000010L
#define MB_ICONQUESTION		 0x00000020L
#define MB_ICONEXCLAMATION	  0x00000030L
#define MB_ICONASTERISK		 0x00000040L
#define MB_ICONMASK			 0x000000F0L

#define MB_ICONINFORMATION	  MB_ICONASTERISK
#define MB_ICONSTOP			 MB_ICONHAND

#define MB_DEFBUTTON1		   0x00000000L
#define MB_DEFBUTTON2		   0x00000100L
#define MB_DEFBUTTON3		   0x00000200L
#define MB_DEFMASK			  0x00000F00L

/* #define MB_APPLMODAL			0x00000000 */
/* #define MB_SYSTEMMODAL		  0x00001000 */
/* #define MB_TASKMODAL			0x00002000 */

#define MB_NOFOCUS			  0x00008000L

#define MB_ALIGNCENTER		  0x00000000L
#define MB_ALIGNTOPLEFT		 0x00010000L
#define MB_ALIGNBTMLEFT		 0x00020000L
#define MB_ALIGNTOPRIGHT		0x00030000L
#define MB_ALIGNBTMRIGHT		0x00040000L
#define MB_ALIGNMASK			0x00070000L

#define MB_BASEDONPARENT		0x00080000L  /* default is desktop. */

/**
 * \fn int GUIAPI MessageBox (HWND hParentWnd, const char* pszText, const char* pszCaption, DWORD dwStyle)
 * \brief Displays a message box within one, two, or three push buttons.
 *
 * This function displays a message box within one, two, or three buttons, and returns
 * the identifier of the button clicked by the user. You can pass \a dwStyle argument 
 * with different values to control the number of buttons, the button titles, and so on.
 *
 * \param hParentWnd The handle to the hosting main window.
 * \param pszText The message text will be displayed in the message box.
 * \param pszCaption The caption of the message box.
 * \param dwStyle The style of the message box, can be one or'ed value of the following styles:
 *		  - MB_OK\n
 *			Create a message box within only one button whose title is "OK".
 *		  - MB_OKCANCEL\n
 *			Create a message box within two buttons whose title are "OK" and "Cancel" respectively.
 *		  - MB_YESNO\n
 *			Create a message box within two buttons whose title are "Yes" and "No" respectively.
 *		  - MB_RETRYCANCEL\n
 *			Create a message box within two buttons whose title are "Retry" and "Cancel" respectively.
 *		  - MB_ABORTRETRYIGNORE\n
 *			Create a message box within three buttons whose title are "Abort", "Retry" and "Ignore" respectively.
 *		  - MB_YESNOCANCEL\n
 *			Create a message box within three buttons whose title are "Yes", "No" and "Cancel" respectively.
 *		  - MB_CANCELASBACK\n
 *			Title "Cancel" replaced with title "Previous".
 *		  - MB_ICONHAND\n
 *			Display a hand/stop icon in the message box.
 *		  - MB_ICONQUESTION\n
 *			Display a question mark icon in the message box.
 *		  - MB_ICONEXCLAMATION\n
 *			Display a exclamation mark icon in the message box.
 *		  - MB_ICONASTERISK\n
 *			Display an information icon in the message box.
 *		  - MB_ICONINFORMATION\n
 *			Display an information icon in the message box.
 *		  - MB_ICONSTOP\n
 *			Display a hand/stop icon in the message box.
 *		  - MB_DEFBUTTON1\n
 *			The first push button acts as the default button.
 *		  - MB_DEFBUTTON2\n
 *			The second push button acts as the default button.
 *		  - MB_DEFBUTTON3\n
 *			The third push button acts as the default button.
 *		  - MB_ALIGNCENTER\n
 *			The message box is center aligned.
 *		  - MB_ALIGNTOPLEFT\n
 *			The message box is upper-left aligned.
 *		  - MB_ALIGNBTMLEFT\n
 *			The message box is lower-left aligned.
 *		  - MB_ALIGNTOPRIGHT\n
 *			The message box is upper-right aligned.
 *		  - MB_ALIGNBTMRIGHT\n
 *			The message box is lower-right aligned.
 *		  - MB_BASEDONPARENT\n
 *			A flag indicates that the alignments above are based on the hosting window, not the desktop. 
 *
 * \return The identifier of the button clicked by user, can be one of the following values:
 *		  - IDOK\n
 *			The "OK" button clicked.
 *		  - IDCANCEL\n
 *			The "Cancel" or "Previous" button clicked.
 *		  - IDABORT\n
 *			The "Abort" button clicked.
 *		  - IDRETRY\n
 *			The "Retry" button clicked.
 *		  - IDIGNORE\n
 *			The "Ignore" button clicked.
 *		  - IDYES\n
 *			The "Yes" button clicked.
 *		  - IDNO\n
 *			The "No" button clicked.
 *
 * \note This function will call \a GetSysText to translate the button titles to localized text.
 *
 * \sa GetSysText, DialogBoxIndirectParam
 */
long GUIAPI MessageBox (HWND hParentWnd, STRINGID text1,  STRINGID text2, 
					   STRINGID caption, DWORD dwStyle, HANDLE tsk);

long GUIAPI PasswordDialog(HANDLE hOwner, INT32 owner, INT32 tipsID);

#endif /* _CTRL_STATIC && _CTRL_BUTTON */

DWORD  GUIAPI  GetControlStatus(PCONTROL pCtrl);
PCONTROL  GUIAPI  GetSubCtrlItem(INT32 parent, INT32 ctrl);
PMAINWIN  GUIAPI  GetTopWndItem(INT32 id);

INT16 GUIAPI GetControlPtr(UINT16 parent_id, UINT16 ctrl_id,
							const char * CtrlName, PCONTROL *pCtrl);

#endif

