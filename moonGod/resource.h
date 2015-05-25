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

#ifndef _RESOURCE_h
#define _RESOURCE_h

/**

 IDD  dialog
 IDC  control
 IDM  main window
 IDR  frame, icon, menu, tool, string,
 IDI  icon
 IDS  string
 IDC 格式:
 IDC_XXX(dialog name)_XXX(control name)_XXX(控件类型)
 控件类型:
 button	--- B
 static	--- L(albe)
 spinbox   --- S
 editbox   --- E
 checkbox  --- C
 hotkey	--- H
 listbox   --- LB
 
**/


/* Standard control IDs */
#define IDC_STATIC	0
#define IDOK		  1
#define IDCANCEL	  2
#define IDABORT	   3
#define IDRETRY	   4
#define IDIGNORE	  5
#define IDYES		 6
#define IDNO		  7
#define IDC_TEXT1	 8
#define IDC_TEXT2	 9
#define IDMB		  10  //消息对话框的主窗口号.

/**
   ID号的设计,是按主窗口分类的.
   正常界面下有三个主窗口.  系统标题栏, 系统状态栏, 系统主界面区(又分为参数区, 波形区)
   对话框也是主窗口.对话框将占据波形区下面的部分.必要时可以占据所有波形区.
   但是不影响参数区,和上下两个主窗口.

   每个主窗口开始第一个id都是有表示字符串"first"在其中的.
   前后缀说明:
		前缀:
			ID	  
			IDM	 主窗口ID
			IDD	 窗口ID
			IDC	 控件ID
			IDI	 图片ID,不在此定义
		后缀:
			L	   Label,static
			LB	  Listbox
			SB	  Spinbox
			B	   Button
			G	   Groupbox
			other   same as words
**/
typedef enum _res_id {

	ID_FIRST = 15,

	/* 系统标题栏窗口 */
	ID_TOPBAR_FIRST   = ID_FIRST,		  //TOPBAR的第一个窗口id,一般都是主窗口的.
	IDM_TOPBAR = ID_TOPBAR_FIRST,
	IDC_TOPBAR_FIRST,					  //TOPBAR的第一个控件id

	/* 系统状态栏窗口 */
	ID_BOTTOMBAR_FIRST,
	IDM_BOTTOMBAR = ID_BOTTOMBAR_FIRST,
	IDC_BOTTOMBAR_FIRST, 

	/* 系统主窗口; 包括波形区和参数区. */
	ID_MAINWND_FIRST,
	IDM_MAIN = ID_MAINWND_FIRST,	   /* 主窗口id */  
	IDC_MAIN_FIRST,
	IDC_MAIN_GRAPH_G = IDC_MAIN_FIRST,
	IDC_MAIN_GRAPH_L,
	IDC_MAIN_GRAPH_FHR_L,
	IDC_MAIN_GRAPH_TOCO_L,
	IDC_MAIN_GRAPH_TIME_L,
	IDC_MAIN_GRAPH_SPEED_L,
	IDC_MAIN_GRAPH_SCROLL_LEFT_B,
	IDC_MAIN_GRAPH_SCROLL_RIGHT_B,
	IDC_MAIN_GRAPH_SCROLL_BAR_SC,

	IDC_MAIN_PARAM_FHR1_G,
	IDC_MAIN_PARAM_FHR1_NAME,
	IDC_MAIN_PARAM_FHR1_PARAM,
	IDC_MAIN_PARAM_FHR1_SIGN,
	IDC_MAIN_PARAM_FHR1_ALARM,

	IDC_MAIN_PARAM_FHR2_G,
	IDC_MAIN_PARAM_FHR2_NAME,
	IDC_MAIN_PARAM_FHR2_PARAM,
	IDC_MAIN_PARAM_FHR2_SIGN,
	IDC_MAIN_PARAM_FHR2_ALARM,

	IDC_MAIN_PARAM_TOCO_G,
	IDC_MAIN_PARAM_TOCO_NAME,
	IDC_MAIN_PARAM_TOCO_PARAM,

	IDC_MAIN_PARAM_FM_G,
	IDC_MAIN_PARAM_FM_NAME,
	IDC_MAIN_PARAM_FM_PARAM,

	IDC_MAIN_PATAM_BOARD_L,

	IDC_BOTTOMBAR_PATIENT_G,
	IDC_BOTTOMBAR_PATIENT_INFO1_L,
	IDC_BOTTOMBAR_PATIENT_INFO2_L,
	IDC_BOTTOMBAR_PATIENT_INFO3_L,
	
	IDC_BOTTOMBAR_MENU0_G,
	IDC_BOTTOMBAR_MENU1_G,
	IDC_BOTTOMBAR_MENU2_G,
	IDC_BOTTOMBAR_MENU3_G,
	IDC_BOTTOMBAR_MENU4_G,
	IDC_BOTTOMBAR_MENU5_G,
	IDC_BOTTOMBAR_MENU6_G,
	IDC_BOTTOMBAR_TIME_G,
	
	IDC_TOPBAR_ALARM_TECH_G,
	IDC_TOPBAR_ALARM_PHYS_G,
	IDC_TOPBAR_STATUS_G,

	IDC_TOPBAR_BOARD,
	IDC_BOTTOM_BOARD,
	
	IDC_BOTTOMBAR_MENU_L,
	IDC_BOTTOMBAR_START_L ,
	IDC_BOTTOMBAR_SOUND_L,
	IDC_BOTTOMBAR_PRINT_L,
	IDC_BOTTOMBAR_TIME_L,
	IDC_BOTTOMBAR_WEEK_L,
	IDC_BOTTOMBAR_DATE_L,
	
	IDC_TOPBAR_ALM_TECH_L,
	IDC_TOPBAR_ALM_LVL_L,
	IDC_TOPBAR_ALM_INFO_L,
	IDC_TOPBAR_ALM_DATE_L,
	IDC_TOPBAR_ALM_TIME_L,
	IDC_TOPBAR_STATUS_AC_L,
	IDC_TOPBAR_STATUS_BAT_L,
	IDC_TOPBAR_STATUS_NET_L,
	IDC_TOPBAR_STATUS_REC_L,
	IDC_TOPBAR_STATUS_FVOL_L,
	IDC_TOPBAR_STATUS_AVOL_L,
	IDC_BOTTOMBAR_MENU0_L,
	IDC_BOTTOMBAR_MENU1_L,
	IDC_BOTTOMBAR_MENU2_L,
	IDC_BOTTOMBAR_MENU3_L,
	IDC_BOTTOMBAR_MENU4_L,
	IDC_BOTTOMBAR_MENU5_L,
	IDC_BOTTOMBAR_MENU6_L,

	IDC_DESKTOP_DEMO1_L,
	IDC_DESKTOP_DEMO2_L,
	IDC_DESKTOP_DEMO3_L,
	IDC_DESKTOP_DEMO4_L,

	IDC_PATIENTINFO_SAVE_TIME_L,
	IDC_PRINTERINFO_ELAPSE_TIME_L,
	IDC_PRINTERINFO_PERIOD_TIME_L,

	IDC_HELP_INFORMATION_L,

	IDD_PASSWORD,
	IDC_PASSWD_FIRST,
	IDC_PASSWD_TIPS_L = IDC_PASSWD_FIRST,
	IDC_PASSWD_WORD_SB,
	IDC_PASSWD_OK_B,
	IDC_PASSWD_CANCEL_B,

	IDD_SHUTDOWN,
	IDC_SHUTDOWN_FIRST,
	IDC_SHUTDOWN_ASKED_L = IDC_SHUTDOWN_FIRST,
	IDC_SHUTDOWN_WARNED_L,
	IDC_SHUTDOWN_OK_B,
	IDC_SHUTDOWN_CANCEL_B,

	
    IDD_LIST,
    IDC_LIST_FIRST,
	IDC_LIST_ITEM0_B = IDC_LIST_FIRST,
	IDC_LIST_ITEM1_B,
	IDC_LIST_ITEM2_B,
	IDC_LIST_ITEM3_B,
	IDC_LIST_ITEM4_B,
	IDC_LIST_ITEM5_B,
	IDC_LIST_ITEMUP_B,
	IDC_LIST_ITEMDN_B,

	IDD_FHR_SETUP,
	IDC_FHR_SETUP_FIRST,

	IDC_FHR_SETUP_ALMSWITCH_L = IDC_FHR_SETUP_FIRST,
	IDC_FHR_SETUP_ALMLEVEL_L,
	IDC_FHR_SETUP_FHR_HI_L,
	IDC_FHR_SETUP_FHR_LO_L,
	IDC_FHR_SETUP_TYPE_L,
	IDC_FHR_SETUP_SOURCE_L,
	IDC_FHR_SETUP_VOLUME_L,
	IDC_FHR_SETUP_DETACH_L,
	IDC_FHR_SETUP_SWITCH_LB,
	IDC_FHR_SETUP_LEVEL_LB,
	IDC_FHR_SETUP_ALMHI_SB,
	IDC_FHR_SETUP_ALMLO_SB,
	IDC_FHR_SETUP_TYPE_LB,
	IDC_FHR_SETUP_SOURCE_LB,
	IDC_FHR_SETUP_VOLUME_LB,
	IDC_FHR_SETUP_DETACH_SB,
	IDC_FHR_SETUP_EXIT_B,

	IDD_TOCO_SETUP,
	IDC_TOCO_SETUP_FIRST,

	IDC_TOCO_SETUP_ZEROVALUE_L = IDC_TOCO_SETUP_FIRST,
	IDC_TOCO_SETUP_ZEROVALUE_LB,
	IDC_TOCO_SETUP_ZERO_B,
	IDC_TOCO_SETUP_EXIT_B,

	IDD_FM_SETUP,
	IDC_FM_SETUP_FIRST,

	IDC_FM_SETUP_THRESHOLD_VAL_L = IDC_FM_SETUP_FIRST,
	IDC_FM_SETUP_MOVEMENT_CAL_L,
	IDC_FM_SETUP_THRESHOLD_VAL_LB,
	IDC_FM_SETUP_MOVEMENT_CAL_LB,
	IDC_FM_SETUP_MOVEMENT_ZERO_B,
	IDC_FM_SETUP_EXIT_B,

	IDD_ANALY_SETUP,
	IDC_ANALY_SETUP_FIRST,
	IDC_ANALY_SETUP_INFO_DATA_L = IDC_ANALY_SETUP_FIRST,
	IDC_ANALY_SETUP_INFO_VALID_L,
	IDC_ANALY_SETUP_START_B,
	IDC_ANALY_SETUP_DONE_B,
	IDC_ANALY_SETUP_EXIT_B,
	IDC_ANALY_SETUP_SONBUT1,

//////////////add by vinyin 2015-05-07
	IDD_ANALY_SETUP_DEFAULT,
	IDC_ANALY_SETUP_DEFAULT_FIRST,
	IDC_ANALY_SETUP_SONWINDOW_BUT1 = IDC_ANALY_SETUP_DEFAULT_FIRST,
	IDC_ANALY_SETUP_SONWINDOW_BUT2,
	IDC_ANALY_SETUP_SONWINDOW_BUT3,
	IDC_ANALY_SETUP_SONWINDOW_BUT4,
	IDC_ANALY_SETUP_SONWINDOW_BUT5,
	IDC_ANALY_SETUP_SONWINDOW_STR1,
	IDC_ANALY_SETUP_SONWINDOW_STR2,
	IDC_ANALY_SETUP_SONWINDOW_STR3,
	IDC_ANALY_SETUP_SONWINDOW_STR4,
	///////////////////////////2015-05-07

	IDD_ANALYSIS_RESULT,
	IDC_ANALYSIS_RESULT_FIRST,
	IDC_ANALYSIS_RESULT_INFO_L = IDC_ANALYSIS_RESULT_FIRST,
	IDC_ANALYSIS_RESULT_SAVE_B,
	IDC_ANALYSIS_RESULT_PRNT_B,
	IDC_ANALYSIS_RESULT_EXIT_B,

	IDD_PATIENT_SETUP,
	IDC_PATIENT_SETUP_FIRST,
	IDC_PATIENT_SETUP_INFO = IDC_PATIENT_SETUP_FIRST,
	IDC_PATIENT_SETUP_NAME_L,
	IDC_PATIENT_SETUP_ID_L,
	IDC_PATIENT_SETUP_AGE_L,
	IDC_PATIENT_SETUP_GESTATIONAL_L,
	IDC_PATIENT_SETUP_GTIMES_L,
	IDC_PATIENT_SETUP_NOTE_L,
	IDC_PATIENT_SETUP_NAME_EDIT,
	IDC_PATIENT_SETUP_ID_EDIT,
	IDC_PATIENT_SETUP_AGE_EDIT,
	IDC_PATIENT_SETUP_GESTATIONAL_EDIT,
	IDC_PATIENT_SETUP_GESTATIONAL_DAY_EDIT,
	IDC_PATIENT_SETUP_GTIMES_EDIT,
	IDC_PATIENT_SETUP_NOTE_EDIT,
	IDC_PATIENT_SETUP_RECALL_B,
	IDC_PATIENT_SETUP_NEWPATIENT_B,
	IDC_PATIENT_SETUP_EDIT_B,
	IDC_PATIENT_SETUP_ANALY_B,
	IDC_PATIENT_SETUP_EXIT_B,

	IDD_PATIENT_RECALL,
	IDC_PATIENT_RECALL_FIRST,
	IDC_PATIENT_RECALL_SCROLL_L = IDC_PATIENT_RECALL_FIRST,
	IDC_PATIENT_RECALL_ID_L,
	IDC_PATIENT_RECALL_NAME__L,
	IDC_PATIENT_RECALL_NAME1_L,
	IDC_PATIENT_RECALL_NAME2_L,
	IDC_PATIENT_RECALL_NAME3_L,
	IDC_PATIENT_RECALL_NAME4_L,
	IDC_PATIENT_RECALL_NAME5_L,
	IDC_PATIENT_RECALL_NAME6_L,
	IDC_PATIENT_RECALL_NAME7_L,
	IDC_PATIENT_RECALL_NAME8_L,
	IDC_PATIENT_RECALL_ALL_C,
	IDC_PATIENT_RECALL_ID1_C,
	IDC_PATIENT_RECALL_ID2_C,
	IDC_PATIENT_RECALL_ID3_C,
	IDC_PATIENT_RECALL_ID4_C,
	IDC_PATIENT_RECALL_ID5_C,
	IDC_PATIENT_RECALL_ID6_C,
	IDC_PATIENT_RECALL_ID7_C,
	IDC_PATIENT_RECALL_ID8_C,
	IDC_PATIENT_RECALL_PGUP_B,
	IDC_PATIENT_RECALL_PGDN_B,
	IDC_PATIENT_RECALL_OPEN_B,
	IDC_PATIENT_RECALL_DELETE_B,
	IDC_PATIENT_RECALL_EXIT_B,

	IDD_FETAL_RECALL,
	IDC_FETAL_RECALL_FIRST,
	IDC_FETAL_RECALL_FHRGPH_L = IDC_FETAL_RECALL_FIRST,
	IDC_FETAL_RECALL_TOCOGPH_L,
	IDC_FETAL_RECALL_TIME_L,
	IDC_FETAL_RECALL_SCROLL_L,
	IDC_FETAL_RECALL_ANALY_B,
	IDC_FETAL_RECALL_INFO_B,
	IDC_FETAL_RECALL_PAGEUP_B,
	IDC_FETAL_RECALL_PAGEDN_B,
	IDC_FETAL_RECALL_PRINTPAGE_B,
	IDC_FETAL_RECALL_PRINTALL_B,
	IDC_FETAL_RECALL_EXIT_B,
	
	IDD_KBDLG_KEYBOARD,
	IDC_KBDLG_KB_FIRST,
	IDC_KBDLG_BOARDER_L = IDC_KBDLG_KB_FIRST,
	IDC_KBDLG_KB_A_B,
	IDC_KBDLG_KB_B_B,
	IDC_KBDLG_KB_C_B,
	IDC_KBDLG_KB_D_B,
	IDC_KBDLG_KB_E_B,
	IDC_KBDLG_KB_F_B,
	IDC_KBDLG_KB_G_B,
	IDC_KBDLG_KB_H_B,
	IDC_KBDLG_KB_I_B,
	IDC_KBDLG_KB_J_B,
	IDC_KBDLG_KB_K_B,
	IDC_KBDLG_KB_L_B,
	IDC_KBDLG_KB_M_B,
	IDC_KBDLG_KB_N_B,
	IDC_KBDLG_KB_O_B,
	IDC_KBDLG_KB_P_B,
	IDC_KBDLG_KB_Q_B,
	IDC_KBDLG_KB_R_B,
	IDC_KBDLG_KB_S_B,
	IDC_KBDLG_KB_T_B,
	IDC_KBDLG_KB_U_B,
	IDC_KBDLG_KB_V_B,
	IDC_KBDLG_KB_W_B,
	IDC_KBDLG_KB_X_B,
	IDC_KBDLG_KB_Y_B,
	IDC_KBDLG_KB_Z_B,
	IDC_KBDLG_KB_CAPS_B,
	IDC_KBDLG_KB_NUM_MARKS_B,
	IDC_KBDLG_KB_IME_B,
	IDC_KBDLG_KB_MARK_B,
	IDC_KBDLG_KB_SPACE_B,
	IDC_KBDLG_KB_MARK1_B,
	IDC_KBDLG_KB_MARK2_B,
	IDC_KBDLG_KB_DEL_B,
	IDC_KBDLG_KB_PREVIOUS_B,
	IDC_KBDLG_CN1_B,
	IDC_KBDLG_CN2_B,
	IDC_KBDLG_CN3_B,
	IDC_KBDLG_CN4_B,
	IDC_KBDLG_CN5_B,
	IDC_KBDLG_CN6_B,
	IDC_KBDLG_CN7_B,
	IDC_KBDLG_CN8_B,
	IDC_KBDLG_KB_NEXT_B,
	IDC_KBDLG_ENTER_B,

	IDD_NUMPAD,
	IDC_NUMPAD_FIRST,
	IDC_NUMPAD_NUM_L = IDC_NUMPAD_FIRST,
	IDC_NUMPAD_ESC,
	IDC_NUMPAD_0,
	IDC_NUMPAD_1,
	IDC_NUMPAD_2,
	IDC_NUMPAD_3,
	IDC_NUMPAD_4,
	IDC_NUMPAD_5,
	IDC_NUMPAD_6,
	IDC_NUMPAD_7,
	IDC_NUMPAD_8,
	IDC_NUMPAD_9,
	IDC_NUMPAD_DOT,
	IDC_NUMPAD_DEL,
	IDC_NUMPAD_MINUS,
	IDC_NUMPAD_ENTER,

	IDD_DATETIME_SETUP,
	IDC_DATETIME_SETUP_FIRST,
	IDC_DATETIME_SETUP_YEAR_SB = IDC_DATETIME_SETUP_FIRST,
	IDC_DATETIME_SETUP_MONTH_SB,
	IDC_DATETIME_SETUP_DAY_SB,
	IDC_DATETIME_SETUP_HOUR_SB,
	IDC_DATETIME_SETUP_MINUTE_SB,
	IDC_DATETIME_SETUP_SECOND_SB,
	IDC_DATETIME_SETUP_SETDATE_B,
	IDC_DATETIME_SETUP_SETTIME_B,
	IDC_DATETIME_SETUP_EXIT_B,

	IDD_SYSTEM_INFORMATION,
	IDC_SYSTEM_INFO_FIRST,
	IDC_SYSTEM_INFO_L = IDC_SYSTEM_INFO_FIRST,
	IDC_SYSTEM_INFO_EXIT_B,

	IDD_SYSTEM_CONFIG,
	IDC_SYSTEM_CONFIG_FIRST,
	IDC_SYSTEM_CONFIG_FETAL_MODE_L = IDC_SYSTEM_CONFIG_FIRST,
	IDC_SYSTEM_CONFIG_FETAL_VOL_CH_L,
	IDC_SYSTEM_CONFIG_FETAL_TOCO_VAL_L,
	IDC_SYSTEM_CONFIG_FETAL_FM_MODE_L,
	IDC_SYSTEM_CONFIG_ALM_FHR_HI_L,
	IDC_SYSTEM_CONFIG_ALM_FHR_LO_L,
	IDC_SYSTEM_CONFIG_ALM_SWITCH_L,
	IDC_SYSTEM_CONFIG_ALM_VOL_L,
	IDC_SYSTEM_CONFIG_FETAL_VOL_L,
	IDC_SYSTEM_CONFIG_KEY_VOL_L,
	IDC_SYSTEM_CONFIG_FAST_PRINT_L,
	IDC_SYSTEM_CONFIG_SPEED_L,
	IDC_SYSTEM_CONFIG_SPLINE_L,
	IDC_SYSTEM_CONFIG_TIMER_L,
	IDC_SYSTEM_CONFIG_AUTO_PRINT_L,
	IDC_SYSTEM_CONFIG_PRINT_MODE_L,
	IDC_SYSTEM_CONFIG_PRINT_CONTRAST_L,
	IDC_SYSTEM_CONFIG_FETAL_MODE_LB,
	IDC_SYSTEM_CONFIG_FETAL_VOL_CH_LB,
	IDC_SYSTEM_CONFIG_FETAL_TOCO_VAL_LB,
	IDC_SYSTEM_CONFIG_FETAL_FM_MODE_LB,
	IDC_SYSTEM_CONFIG_ALM_SWITCH_LB,
	IDC_SYSTEM_CONFIG_ALM_VOL_LB,
	IDC_SYSTEM_CONFIG_FETAL_VOL_LB,
	IDC_SYSTEM_CONFIG_KEY_VOL_LB,
	IDC_SYSTEM_CONFIG_FAST_PRINT_LB,
	IDC_SYSTEM_CONFIG_SPEED_LB,
	IDC_SYSTEM_CONFIG_SPLINE_LB,
	IDC_SYSTEM_CONFIG_TIMER_LB,
	IDC_SYSTEM_CONFIG_AUTO_PRINT_LB,
	IDC_SYSTEM_CONFIG_PRINT_MODE_LB,
	IDC_SYSTEM_CONFIG_PRINT_CONTRAST_SB,
	IDC_SYSTEM_CONFIG_ALM_FHR_HI_SB,
	IDC_SYSTEM_CONFIG_ALM_FHR_LO_SB,
	IDC_SYSTEM_CONFIG_SET_FM_B,
	IDC_SYSTEM_CONFIG_PRINT_TEST_B,
	IDC_SYSTEM_CONFIG_SETUP_B,
	IDC_SYSTEM_CONFIG_DEFAULT_B,
	IDC_SYSTEM_CONFIG_EXIT_B,

	IDD_MAINTAIN_DIALOG,
	IDC_MAINTAIN_FIRST,
	IDC_MAINTAIN_NIGHTMODE_B = IDC_MAINTAIN_FIRST,
	IDC_MAINTAIN_HELPINFO_B,
	IDC_MAINTAIN_NETWORK_B,
	IDC_MAINTAIN_LANGUAGE_B,
	IDC_MAINTAIN_FACTORY_B,
	IDC_MAINTAIN_ABOUT_B,
	IDC_MAINTAIN_DEMO_B,
	IDC_MAINTAIN_EXIT_B,

	IDD_FACTORY_MAINTAIN,
	IDC_FACTORY_MAINTAIN_FIRST,
	IDC_FACTORY_MAINTAIN_MONITOR_TYPE_NAME_L = IDC_FACTORY_MAINTAIN_FIRST,
	IDC_FACTORY_MAINTAIN_ENABLE_TOUCH_L,
	IDC_FACTORY_MAINTAIN_RECORDER_TYPE_L,
	IDC_FACTORY_MAINTAIN_VERSION_L,
	IDC_FACTORY_MAINTAIN_MONITOR_TYPE_NAME_LB,
	IDC_FACTORY_MAINTAIN_ENABLE_TOUCH_LB,
	IDC_FACTORY_MAINTAIN_RECORDER_TYPE_LB,
	IDC_FACTORY_MAINTAIN_RECORDER_SETUP_B,
	IDC_FACTORY_MAINTAIN_UPDATE_B,
	IDC_FACTORY_MAINTAIN_ENBALALY_B,
	IDC_FACTORY_MAINTAIN_EXIT_B,

	IDD_ABOUT_DIALOG,
	IDC_ABOUT_FIRST,
	IDC_ABOUT_TIME_L = IDC_ABOUT_FIRST,
	IDC_ABOUT_START_TIME_L,
	IDC_ABOUT_VERSION_L,
	IDC_ABOUT_VERSION_NUMBER_L,
	IDC_ABOUT_COMPILE_TIME_L,
	IDC_ABOUT_COMPILE_DATE_L,
	IDC_ABOUT_COMPANY_L,
	IDC_ABOUT_EXIT_B,

	IDD_NETWORK_CONFIGURE,
	IDC_NETWORK_CFG_FIRST,
	IDC_NETWORK_CFG_SWITCH_L = IDC_NETWORK_CFG_FIRST,
	IDC_NETWORK_CFG_HWADDR_L,
	IDC_NETWORK_CFG_IPv4_ADDR_L,
	IDC_NETWORK_CFG_MASK_L,
	IDC_NETWORK_CFG_GATEWAY_L,
	IDC_NETWORK_CFG_SERVERIP_L,
	IDC_NETWORK_CFG_PORT_L,
	IDC_NETWORK_CFG_SWITCH_LB,
	IDC_NETWORK_CFG_IPv4ADDR1_SB,
	IDC_NETWORK_CFG_IPv4ADDR2_SB,
	IDC_NETWORK_CFG_IPv4ADDR3_SB,
	IDC_NETWORK_CFG_IPv4ADDR4_SB,
	IDC_NETWORK_CFG_MASKADDR1_SB,
	IDC_NETWORK_CFG_MASKADDR2_SB,
	IDC_NETWORK_CFG_MASKADDR3_SB,
	IDC_NETWORK_CFG_MASKADDR4_SB,
	IDC_NETWORK_CFG_GATEADDR1_SB,
	IDC_NETWORK_CFG_GATEADDR2_SB,
	IDC_NETWORK_CFG_GATEADDR3_SB,
	IDC_NETWORK_CFG_GATEADDR4_SB,
	IDC_NETWORK_CFG_SERVERIP1_SB,
	IDC_NETWORK_CFG_SERVERIP2_SB,
	IDC_NETWORK_CFG_SERVERIP3_SB,
	IDC_NETWORK_CFG_SERVERIP4_SB,
	IDC_NETWORK_CFG_SERVER_EDIT,
	IDC_NETWORK_CFG_PORT_SB,
	IDC_NETWORK_CFG_EXIT_B,

	IDD_PRINT_SETUP,
	IDC_PRINT_SETUP_FIRST,
	IDC_PRINT_SETUP_LEN_L = IDC_PRINT_SETUP_FIRST,
	IDC_PRINT_SETUP_AUTO_L,
	IDC_PRINT_SETUP_LEN_LB,
	IDC_PRINT_SETUP_AUTO_LB,
	IDC_PRINT_SETUP_PRINTER_B,
	IDC_PRINT_SETUP_EXIT_B,

	IDD_PRINTER_SETUP,
	IDC_PRINTER_SETUP_FIRST,
	IDC_PRINTER_SETUP_FHR60_L = IDC_PRINTER_SETUP_FIRST,
	IDC_PRINTER_SETUP_FHR210_L,
	IDC_PRINTER_SETUP_FHRMIN_L,
	IDC_PRINTER_SETUP_FHRMAX_L,
	IDC_PRINTER_SETUP_TOCO100_L,
	IDC_PRINTER_SETUP_TOCO0_L,
	IDC_PRINTER_SETUP_SCALE_L,
	IDC_PRINTER_SETUP_CONTRAST_L,
	IDC_PRINTER_SETUP_FHR60_SB,
	IDC_PRINTER_SETUP_FHR210_SB,
	IDC_PRINTER_SETUP_TOCO100_SB,
	IDC_PRINTER_SETUP_TOCO0_SB,
	IDC_PRINTER_SETUP_CONTRAST_SB,
	IDC_PRINTER_SETUP_FHRMIN_LB,
	IDC_PRINTER_SETUP_FHRMAX_LB,
	IDC_PRINTER_SETUP_SCALE_LB,
	IDC_PRINTER_SETUP_DEFAULT_B,
	IDC_PRINTER_SETUP_SELFTEST_B,
	IDC_PRINTER_SETUP_EXIT_B,

	
#if 1
	IDD_DOCTOR_MARK,
	IDC_DOCTOR_MARK_FIRST,
	IDC_DOCTOR_MARK_A = IDC_DOCTOR_MARK_FIRST,
	IDC_DOCTOR_MARK_B,
	IDC_DOCTOR_MARK_C,
	IDC_DOCTOR_MARK_D,
	IDC_DOCTOR_MARK_E,
	IDC_DOCTOR_MARK_F,
	IDC_DOCTOR_MARK_G,
	IDC_DOCTOR_MARK_H,
	IDC_DOCTOR_MARK_I,
	IDC_DOCTOR_MARK_J,
	IDC_DOCTOR_MARK_K,
	IDC_DOCTOR_MARK_L,
	IDC_DOCTOR_MARK_M,
	IDC_DOCTOR_MARK_N,
	IDC_DOCTOR_MARK_O,
	IDC_DOCTOR_MARK_EXIT,
#endif

	IDD_STATUS_INFO,
	IDC_STATUS_INFO_FIRST,
	IDC_STATUS_INFO_INFO1_L = IDC_STATUS_INFO_FIRST,
	IDC_STATUS_INFO_INFO2_L,
	IDC_STATUS_INFO_INFO3_L,
	IDC_STATUS_INFO_INFO4_L,
	IDC_STATUS_INFO_INFO5_L,
	IDC_STATUS_INFO_INFO6_L,
	IDC_STATUS_INFO_ICON1_B,
	IDC_STATUS_INFO_ICON2_B,
	IDC_STATUS_INFO_ICON3_B,
	IDC_STATUS_INFO_ICON4_B,
	IDC_STATUS_INFO_ICON5_B,
	IDC_STATUS_INFO_ICON6_B,
	IDC_STATUS_INFO_EXIT_B,

	IDD_ALARM_TECH_INFO,
	IDC_ALARM_TECH_INFO_FIRST,
	IDC_ALARM_TECH_INFO_BOARD_L = IDC_ALARM_TECH_INFO_FIRST,
	IDC_ALARM_TECH_INFO_PAGEDN_B,
	IDC_ALARM_TECH_INFO_PAGEUP_B,

	IDD_ALARM_PHYS_INFO,
	IDC_ALARM_PHYS_INFO_FIRST,
	IDC_ALARM_PHYS_INFO_BOARD_L = IDC_ALARM_PHYS_INFO_FIRST,
	IDC_ALARM_PHYS_INFO_PAGEDN_B,
	IDC_ALARM_PHYS_INFO_PAGEUP_B,

	IDD_SETUP_LANGUAGE,
	IDC_LANGUAGE_FIRST,
	IDC_LANGUAGE_CHOICE_L = IDC_LANGUAGE_FIRST,
	IDC_LANGUAGE_DATEFORMAT_L,
	IDC_LANGUAGE_DATE_DELIMITER_L,
	IDC_LANGUAGE_TIMEFORMAT_L,
	IDC_LANGUAGE_CHOICE_LB,
	IDC_LANGUAGE_DATEFORMAT_LB,
	IDC_LANGUAGE_DATE_DELIMITER_LB,
	IDC_LANGUAGE_TIMEFORMAT_LB,
	IDC_LANGUAGE_EXIT_B,

	ID_MAX
}RESID;

typedef enum _sys_groupbox_index
{
	GPB_TOPBAR_PATIENT_NAME,
	GPB_TOPBAR_PATIENT_ID,
	GPB_TOPBAR_ALARM_INFO,
	GPB_TOPBAR_STATUS,
	GPB_BOTTOMBAR_PATIENT,
	GPB_BOTTOMBAR_MENU00,
	GPB_BOTTOMBAR_MENU01,
	GPB_BOTTOMBAR_MENU02,
	GPB_BOTTOMBAR_MENU03,
	GPB_BOTTOMBAR_MENU04,
	GPB_BOTTOMBAR_MENU05,
	GPB_BOTTOMBAR_MENU06,
	GPB_BOTTOMBAR_TIME,
	GPB_MAIN_GRAPH,
	GPB_MAIN_FHR1,
	GPB_MAIN_FHR2,
	GPB_MAIN_TOCO,
	GPB_MAIN_FM,
	GPB_SYS_INDEX_MAX
}SYSGROUPBOXINDEDX;

#endif
