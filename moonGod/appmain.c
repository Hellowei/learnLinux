/*****************************************************************************************
版权所有:            和心重典
版本号:                1.0.0
生成日期:            2011.04.15
文件名:                
作者:                和心重典
功能说明:            
其它说明:            无
所属文件关系:        本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*****************************************************************************************/
#define   APPMAIN_GLOBALS 
#include  "includes.h"

VOID init_all_module(VOID);

//static VOID GraphProcDialog (void)
//{
//    static UCHAR type = 0;
//    if (++type >= 8) type = 0;
//    ReInitFhrGphMem(type);
//    ReInitFetalWave();
//}

GROUPBOXDATA gGroupboxAdddata[GPB_SYS_INDEX_MAX];

static INT32 OnClickGraphProcDialog(HWND parent, HWND crtrl, LPARAM lParam)
{
    parent = parent;
    crtrl  = crtrl;
    lParam = lParam;
    //GraphProcDialog();
	ExitViewWaveModule();
    return 0;
}

static INT32 OnClickFhrSetupDialog(HWND parent, HWND crtrl, LPARAM lParam)
{
    printf("hehehe\n");
    parent = parent;
    crtrl  = crtrl;
    lParam = lParam;
    if ((HWND)GetTopWndItem(IDD_FHR_SETUP) == HWND_INVALID && _menu_lev <= 0)
        FhrSetupDialog(0);
    return 0;
}

static INT32 OnClickTocoSetupDialog(HWND parent, HWND crtrl, LPARAM lParam)
{
    parent = parent;
    crtrl  = crtrl;
    lParam = lParam;
    if ((HWND)GetTopWndItem(IDD_TOCO_SETUP) == HWND_INVALID && _menu_lev <= 0)
        TocoSetupDialog(0);
    return 0;
}


static INT32 OnClickFmSetupDialog(HWND parent, HWND crtrl, LPARAM lParam)
{
    parent = parent;
    crtrl  = crtrl;
    lParam = lParam;
    if ((HWND)GetTopWndItem(IDD_FM_SETUP) == HWND_INVALID && _menu_lev <= 0)
        FmSetupDialog(0);
    return 0;
}

static INT32 OnClickAlarmThListDialog(HWND parent, HWND crtrl, LPARAM lParam)
{
    parent = parent;
    crtrl  = crtrl;
    lParam = lParam;
    if ((HWND)GetTopWndItem(IDD_ALARM_TECH_INFO) == HWND_INVALID && _menu_lev <= 0)
        AlarmThListDialog(0);
    return 0;
}

static INT32 OnClickAlarmPhListDialog(HWND parent, HWND crtrl, LPARAM lParam)
{
    parent = parent;
    crtrl  = crtrl;
    lParam = lParam;
    if ((HWND)GetTopWndItem(IDD_ALARM_PHYS_INFO) == HWND_INVALID && _menu_lev <= 0)
        AlarmPhListDialog(0);
    return 0;
}

static INT32 OnClickStatusDialog(HWND parent, HWND crtrl, LPARAM lParam)
{
    parent = parent;
    crtrl  = crtrl;
    lParam = lParam;
    if ((HWND)GetTopWndItem(IDD_STATUS_INFO) == HWND_INVALID && _menu_lev <= 0)
        StatusDialog(0);
    return 0;
}

INT32 OnClickPatientSetupDialog(HWND parent, HWND crtrl, LPARAM lParam)
{
    parent = parent;
    crtrl  = crtrl;
    lParam = lParam;
    if ((HWND)GetTopWndItem(IDD_PATIENT_SETUP) == HWND_INVALID && _menu_lev <= 0)
        PatientSetupDialog(0);
    return 0;
}

static INT32 OnClickTimeSetupDialog(HWND parent, HWND crtrl, LPARAM lParam)
{
    parent = parent;
    crtrl  = crtrl;
    lParam = lParam;
    if ((HWND)GetTopWndItem(IDD_DATETIME_SETUP) == HWND_INVALID && _menu_lev <= 0)
        TimeSetupDialog(0);
    return 0;
}

static INT32 OnClickScrollLeft(HWND parent, HWND crtrl, LPARAM lParam)
{
    parent = parent;
    crtrl  = crtrl;
    lParam = lParam;
    WavePageUp();
    return 0;
}

static INT32 OnClickScrollRight(HWND parent, HWND crtrl, LPARAM lParam)
{
    parent = parent;
    crtrl  = crtrl;
    lParam = lParam;
    WavePageDown();
    return 0;
}

static INT32 OnChangeScrollBar(HWND parent, HWND crtrl, LPARAM lParam)
{
    parent = parent;
    crtrl  = crtrl;
    lParam = lParam;
    PCONTROL pCtrl = (PCONTROL)crtrl;
    WavePageChange(SCROLL_MAXNUM(pCtrl)-SCROLL_VALUE(pCtrl));
    return 0;
}

static INT32 OnPressedWaveGraph(HWND parent, HWND crtrl, LPARAM lParam)
{
	PCONTROL pCtrl = (PCONTROL)crtrl;
	HWND hWnd = GetDlgItem(parent, GROUPBOX_HELPID(pCtrl));
	if (hWnd)
		SetWindowText(hWnd, STR_HELP_EXIT_VIEW_WAVE);
}

static MSGMAP_ENTRY  MainScn_MsgMapEntry[] = 
{
    /* nMessage,   control id,                 notify code,    pfn  */
    
    { MSG_COMMAND, IDC_MAIN_GRAPH_G,		GRBN_CLICKED,   OnClickGraphProcDialog    },
	{ MSG_COMMAND, IDC_MAIN_GRAPH_G,		GRBN_KEY_LEFT,  OnClickScrollLeft	},
	{ MSG_COMMAND, IDC_MAIN_GRAPH_G,		GRBN_KEY_RIGHT, OnClickScrollRight	},
	{ MSG_COMMAND, IDC_MAIN_GRAPH_G,		GRBN_PRESSED,   OnPressedWaveGraph	},
    { MSG_COMMAND, IDC_MAIN_PARAM_FHR1_G,	GRBN_CLICKED,   OnClickFhrSetupDialog     },
    { MSG_COMMAND, IDC_MAIN_PARAM_FHR2_G,	GRBN_CLICKED,   OnClickFhrSetupDialog     },
    { MSG_COMMAND, IDC_MAIN_PARAM_TOCO_G,	GRBN_CLICKED,   OnClickTocoSetupDialog    },
    { MSG_COMMAND, IDC_MAIN_PARAM_FM_G,		GRBN_CLICKED,   OnClickFmSetupDialog      },
    { MSG_COMMAND, IDC_TOPBAR_ALARM_TECH_G,	GRBN_CLICKED,   OnClickAlarmThListDialog   },
    { MSG_COMMAND, IDC_TOPBAR_ALARM_PHYS_G,	GRBN_CLICKED,   OnClickAlarmPhListDialog   },
    { MSG_COMMAND, IDC_TOPBAR_STATUS_G,		GRBN_CLICKED,   OnClickStatusDialog       },
    { MSG_COMMAND, IDC_BOTTOMBAR_PATIENT_G,	GRBN_CLICKED,   OnClickPatientSetupDialog },
    { MSG_COMMAND, IDC_BOTTOMBAR_MENU0_G,	GRBN_CLICKED,   NULL               },
    { MSG_COMMAND, IDC_BOTTOMBAR_MENU1_G,	GRBN_CLICKED,   NULL               },
    { MSG_COMMAND, IDC_BOTTOMBAR_MENU2_G,	GRBN_CLICKED,   NULL               },
    { MSG_COMMAND, IDC_BOTTOMBAR_MENU3_G,	GRBN_CLICKED,   NULL               },
    { MSG_COMMAND, IDC_BOTTOMBAR_MENU4_G,	GRBN_CLICKED,   NULL               },
    { MSG_COMMAND, IDC_BOTTOMBAR_MENU5_G,	GRBN_CLICKED,   NULL               },
    { MSG_COMMAND, IDC_BOTTOMBAR_MENU6_G,	GRBN_CLICKED,   NULL               },
    { MSG_COMMAND, IDC_BOTTOMBAR_TIME_G,	GRBN_CLICKED,   OnClickTimeSetupDialog    },
    { MSG_COMMAND, IDC_MAIN_GRAPH_SCROLL_LEFT_B,  BN_CLICKED, OnClickScrollLeft     },
    { MSG_COMMAND, IDC_MAIN_GRAPH_SCROLL_BAR_SC,  SCR_CHANGE, OnChangeScrollBar     },
    { MSG_COMMAND, IDC_MAIN_GRAPH_SCROLL_RIGHT_B, BN_CLICKED, OnClickScrollRight    },
};
#define MAINSN_MSGMAN_NR  TABLESIZE(MainScn_MsgMapEntry)

static BOOL CreateTechAlarmInfoGroups(VOID)
{
    HWND hCtrl;
    PCONTROL pCtrl;
    GAL_PIXEL bkColor;
	short y = 0;
    bkColor = GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE);
    if (MonitorConfig.nightModeOn)
    {
        bkColor = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_GRAY);
    }
	if (MONITOR_TYPE_AR2 == MonitorConfig.MonitorName)
	{
		y += ARTEMIS2_TOP_OFFSET;
	}

    pCtrl = GetCtrlWndMem(IDC_TOPBAR_ALARM_TECH_G);
    hCtrl = CreateWindowEx(CTRL_GROUPBOX, 0, WS_VISIBLE | WS_TABSTOP, 0,
                           IDC_TOPBAR_ALARM_TECH_G,
                           0,
                           y,
                           300,
                           TOPBAR_HEIGHT - 2,
                           MainScnHWnd,
                           0,
                           (UINT32)&gGroupboxAdddata[GPB_TOPBAR_PATIENT_ID],
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
//    EnableWindow(hCtrl, TRUE);
    SetWindowBkColor(hCtrl, bkColor);
    pCtrl = GetCtrlWndMem(IDC_TOPBAR_ALM_TECH_L);
    hCtrl = CreateWindowEx(CTRL_STATIC, (STRINGID)0,//STR_MAIN_TOPBAR_ALARM_TECH,
                           WS_VISIBLE | SS_CENTER, 0,
                           IDC_TOPBAR_ALM_TECH_L,
                           2,
                           y + TOPBAR_TOP,
                           296,
                           STATIC_HEIGHT,
                           MainScnHWnd,
                           0,
                           0,
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
    SetWindowBkColor(hCtrl, bkColor);
    //SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_FIXED));
    SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_BIGFONT));//phh

    

}

static BOOL CreatePhysAlarmInfoGroups(VOID)
{
    HWND hCtrl;
    PCONTROL pCtrl;
    RESID id[] = {
        IDC_TOPBAR_ALM_LVL_L,
        IDC_TOPBAR_ALM_INFO_L,
        IDC_TOPBAR_ALM_DATE_L,
        IDC_TOPBAR_ALM_TIME_L,
    };
    STRINGID strid[] = {
        0,// STR_MAIN_TOPBAR_ALARM_LVL,
        0,// STR_MAIN_TOPBAR_ALARM_INFO,
        0,// STR_MAIN_TOPBAR_ALARM_DATE,
        0 // STR_MAIN_TOPBAR_ALARM_TIME,
    };
    INT16 i;
    INT16 rect[][4] = {
        { 302, TOPBAR_TOP,  25, STATIC_HEIGHT}, // IDC_TOPBAR_ALM_LVL_L
        { 327, TOPBAR_TOP, 241, STATIC_HEIGHT}, // IDC_TOPBAR_ALM_INFO_L
        { 568, TOPBAR_TOP,  80, STATIC_HEIGHT/2}, // IDC_TOPBAR_ALM_DATE_L
        { 568, TOPBAR_TOP + STATIC_HEIGHT/2,  80, STATIC_HEIGHT/2}, // IDC_TOPBAR_ALM_TIME_L
        { 300, 0, 350, TOPBAR_HEIGHT - 2}  // IDC_TOPBAR_PATIENT_NAME_G
    };
    GAL_PIXEL bkColor;
	short y = 0;
    bkColor = GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE);
    if (MonitorConfig.nightModeOn)
    {
        bkColor = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_GRAY);
    }
	if (MONITOR_TYPE_AR2 == MonitorConfig.MonitorName)
	{
		y += ARTEMIS2_TOP_OFFSET;
	}
    pCtrl = GetCtrlWndMem(IDC_TOPBAR_ALARM_PHYS_G);
    hCtrl = CreateWindowEx(CTRL_GROUPBOX, 0, WS_VISIBLE | WS_TABSTOP, 0,
                           IDC_TOPBAR_ALARM_PHYS_G,
                           rect[TABLESIZE(rect) - 1][0],
                           rect[TABLESIZE(rect) - 1][1] + y,
                           rect[TABLESIZE(rect) - 1][2],
                           rect[TABLESIZE(rect) - 1][3],
                           MainScnHWnd,
                           0,
                           (UINT32)&gGroupboxAdddata[GPB_TOPBAR_ALARM_INFO],
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
//    EnableWindow(hCtrl, TRUE);
    SetWindowBkColor(hCtrl, bkColor);

    for (i = 0; i < TABLESIZE(id); i++)
    {
        if ((rect[i][0] + rect[i][2] + 2) > 
            (rect[TABLESIZE(rect) - 1][0] + rect[TABLESIZE(rect) - 1][2]))
            break;
        pCtrl = GetCtrlWndMem(id[i]);
        hCtrl = CreateWindowEx(CTRL_STATIC,
                                strid[i],
                                WS_VISIBLE | SS_CENTER,
                                0,
                                id[i],
                                rect[i][0],
                                rect[i][1] + y,
                                rect[i][2],
                                rect[i][3],
                                MainScnHWnd,
                                0,
                                0,
                                pCtrl);
        if (hCtrl == HWND_INVALID)
        {
            return FALSE;
        }
        SetWindowBkColor(hCtrl, bkColor);//(hCtrl, GetWindowElementColor(BKC_CAPTION_NORMAL));
        SetWindowTextColor(hCtrl, GetWindowElementColor(WEC_FRAME_NORMAL));
        switch(id[i])
        {
            case IDC_TOPBAR_ALM_LVL_L:
                SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_WCHAR_DEF));
                break;
            case IDC_TOPBAR_ALM_INFO_L:
                SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_BIGFONT));//phh

                break;
            case IDC_TOPBAR_ALM_DATE_L:
                SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_DEFAULT));
                break;
            case IDC_TOPBAR_ALM_TIME_L:
                SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_DEFAULT));
                break;

			default:
				break;
        }
    }
}

static VOID CreateAlarmInfoGroups(VOID)
{
    CreateTechAlarmInfoGroups();
    CreatePhysAlarmInfoGroups();
}

static BOOL CreateStatusGroups(VOID)
{
    enum{
        GROUP_LEFT = 650,
        GROUP_WIDTH = SCREEN_WIDTH - GROUP_LEFT - 1,
        GROUP_ITEM_TOP = 2,
        GROUP_ITEM_WIDTH = 24,
        GROUP_ITEM_HIGH = 24,
        GROUP_ITEM_LEFT1 = GROUP_LEFT + 2 + GROUP_ITEM_WIDTH * 0,
        GROUP_ITEM_LEFT2 = GROUP_LEFT + 2 + GROUP_ITEM_WIDTH * 1,
        GROUP_ITEM_LEFT3 = GROUP_LEFT + 2 + GROUP_ITEM_WIDTH * 2,
        GROUP_ITEM_LEFT4 = GROUP_LEFT + 2 + GROUP_ITEM_WIDTH * 3,
        GROUP_ITEM_LEFT5 = GROUP_LEFT + 2 + GROUP_ITEM_WIDTH * 4,
        GROUP_ITEM_LEFT6 = GROUP_LEFT + 2 + GROUP_ITEM_WIDTH * 5,
        GROUP_ITEM_LEFT7 = GROUP_LEFT + 2 + GROUP_ITEM_WIDTH * 6,
        GROUP_ITEM_LEFT8 = GROUP_LEFT + 2 + GROUP_ITEM_WIDTH * 7,
        GROUP_ITEM_LEFT9 = GROUP_LEFT + 2 + GROUP_ITEM_WIDTH * 8
    };
    HWND hCtrl;
    PCONTROL pCtrl;
    RESID id[] = {
        IDC_TOPBAR_STATUS_AC_L,
        IDC_TOPBAR_STATUS_BAT_L,
        IDC_TOPBAR_STATUS_NET_L,
        IDC_TOPBAR_STATUS_REC_L,
        IDC_TOPBAR_STATUS_FVOL_L,
        IDC_TOPBAR_STATUS_AVOL_L,
    };
    INT16 i;
    INT16 rect[][4] = {
        { GROUP_ITEM_LEFT1, GROUP_ITEM_TOP, GROUP_ITEM_WIDTH, GROUP_ITEM_HIGH}, // IDC_TOPBAR_STATUS_AC_L
        { GROUP_ITEM_LEFT2, GROUP_ITEM_TOP, GROUP_ITEM_WIDTH, GROUP_ITEM_HIGH}, // IDC_TOPBAR_STATUS_BAT_L
        { GROUP_ITEM_LEFT3, GROUP_ITEM_TOP, GROUP_ITEM_WIDTH, GROUP_ITEM_HIGH}, // IDC_TOPBAR_STATUS_NET_L
        { GROUP_ITEM_LEFT4, GROUP_ITEM_TOP, GROUP_ITEM_WIDTH, GROUP_ITEM_HIGH}, // IDC_TOPBAR_STATUS_REC_L
        { GROUP_ITEM_LEFT5, GROUP_ITEM_TOP, GROUP_ITEM_WIDTH, GROUP_ITEM_HIGH}, // IDC_TOPBAR_STATUS_FVOL_L
        { GROUP_ITEM_LEFT6, GROUP_ITEM_TOP, GROUP_ITEM_WIDTH, GROUP_ITEM_HIGH}, // IDC_TOPBAR_STATUS_AVOL_L
        { GROUP_LEFT, 0, GROUP_WIDTH, TOPBAR_HEIGHT - 2}  // IDC_TOPBAR_STATUS_G
    };
    GAL_PIXEL bkColor;
    bkColor = GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE);
    if (MonitorConfig.nightModeOn)
    {
        bkColor = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_GRAY);
    }
	if (MONITOR_TYPE_AR2 == MonitorConfig.MonitorName)
	{
		for (i = 0; i < TABLESIZE(rect); i++)
		{
			rect[i][1] += ARTEMIS2_TOP_OFFSET;
		}
	}
    pCtrl = GetCtrlWndMem(IDC_TOPBAR_STATUS_G);
    hCtrl = CreateWindowEx(CTRL_GROUPBOX, 0, WS_VISIBLE | WS_TABSTOP, 0,
                            IDC_TOPBAR_STATUS_G,
                            rect[TABLESIZE(rect) - 1][0],
                            rect[TABLESIZE(rect) - 1][1],
                            rect[TABLESIZE(rect) - 1][2],
                            rect[TABLESIZE(rect) - 1][3],
                            MainScnHWnd,
                            0,
                            (UINT32)&gGroupboxAdddata[GPB_TOPBAR_STATUS],
                            pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
//    EnableWindow(hCtrl, TRUE);
    SetWindowBkColor(hCtrl, bkColor);

    INT8 night = MonitorConfig.nightModeOn;
    UINT32 icon[] =
        {   (UINT32)ac_icon[night],     (UINT32)batt_icon[night][3],
            (UINT32)net_icon[night],    (UINT32)print_icon[night],
            (UINT32)GetFetalHearIcon(), (UINT32)alm_icon[night]     };
    for (i = 0; i < TABLESIZE(id); i++)
    {
        if ((rect[i][0] + rect[i][2] + 2) > 
            (rect[TABLESIZE(rect) - 1][0] + rect[TABLESIZE(rect) - 1][2]))
            break;
        pCtrl = GetCtrlWndMem(id[i]);
        hCtrl = CreateWindowEx(CTRL_STATIC,
                                0,
                                WS_VISIBLE | SS_BITMAP,
                                0,
                                id[i],
                                rect[i][0],
                                rect[i][1],
                                rect[i][2],
                                rect[i][3],
                                MainScnHWnd,
                                icon[i],
                                0,
                                pCtrl);
        if (hCtrl == HWND_INVALID)
        {
            return FALSE;
        }
        SetWindowBkColor(hCtrl, bkColor);//WEC_EXCOLOR_ROYALBLUE));
        SetWindowTextColor(hCtrl, GetWindowElementColor(FGC_CAPTION_NORMAL));
        SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_MINI));
    }
}

static BOOL CreateTimeGroups(VOID)
{
    enum{
        GROUP_TOP = BOTTOM_TOP + 1,
        GROUP_HIGH = BOTBAR_HEIGHT - 1,
        GROUP_WIDTH = 85,
        GROUP_LEFT = SCREEN_WIDTH - GROUP_WIDTH - 1,
        GROUP_ITEM_WIDTH = 81,
        GROUP_ITEM_HIGH = 14,
        GROUP_ITEM_LEFT = GROUP_LEFT + 2,
        GROUP_ITEM_TOP1 = GROUP_TOP + 2 + GROUP_ITEM_HIGH * 0,
        GROUP_ITEM_TOP2 = GROUP_TOP + 2 + GROUP_ITEM_HIGH * 1,
        GROUP_ITEM_TOP3 = GROUP_TOP + 2 + GROUP_ITEM_HIGH * 2
    };
    HWND hCtrl;
    PCONTROL pCtrl;
    RESID id[] = {
        IDC_BOTTOMBAR_TIME_L,
        IDC_BOTTOMBAR_WEEK_L,
        IDC_BOTTOMBAR_DATE_L
    };
    STRINGID strid[] = {
        STR_MAIN_BOTTOM_TIME,
        STR_MAIN_BOTTOM_WEEK,
        STR_MAIN_BOTTOM_DATE
    };
    INT16 i;
    INT16 rect[][4] = {
        { GROUP_ITEM_LEFT, GROUP_ITEM_TOP1, GROUP_ITEM_WIDTH, GROUP_ITEM_HIGH}, // IDC_BOTTOMBAR_TIME_L
        { GROUP_ITEM_LEFT, GROUP_ITEM_TOP2, GROUP_ITEM_WIDTH, GROUP_ITEM_HIGH}, // IDC_BOTTOMBAR_DATE_L
        { GROUP_ITEM_LEFT, GROUP_ITEM_TOP3, GROUP_ITEM_WIDTH, GROUP_ITEM_HIGH}, // IDC_BOTTOMBAR_WEEK_L
        { GROUP_LEFT, GROUP_TOP, GROUP_WIDTH, GROUP_HIGH}, // IDC_BOTTOMBAR_TIME_G
    };

    short y = 0;
    GAL_PIXEL bkColor;
    bkColor = GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE);
    if (MonitorConfig.nightModeOn)
    {
        bkColor = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_GRAY);
    }
	if (MONITOR_TYPE_AR2 == MonitorConfig.MonitorName)
	{
		y -= ARTEMIS2_BOTTOM_OFFSET;
	}

    pCtrl = GetCtrlWndMem(IDC_BOTTOMBAR_TIME_G);
    hCtrl = CreateWindowEx(CTRL_GROUPBOX, 0, WS_VISIBLE | WS_TABSTOP, 0,
                           IDC_BOTTOMBAR_TIME_G,
                           rect[TABLESIZE(rect) - 1][0],
                           rect[TABLESIZE(rect) - 1][1] + y,
                           rect[TABLESIZE(rect) - 1][2],
                           rect[TABLESIZE(rect) - 1][3],
                           MainScnHWnd,
                           0,
                           (UINT32)&gGroupboxAdddata[GPB_BOTTOMBAR_TIME],
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
//    EnableWindow(hCtrl, TRUE);
    SetWindowBkColor(hCtrl, bkColor);

    for (i = 0; i < TABLESIZE(id); i++)
    {
        if ((rect[i][0] + rect[i][2] + 2) > 
            (rect[TABLESIZE(rect) - 1][0] + rect[TABLESIZE(rect) - 1][2]))
            break;
        pCtrl = GetCtrlWndMem(id[i]);
        hCtrl = CreateWindowEx(CTRL_STATIC,
                                strid[i],
                                WS_VISIBLE | SS_CENTER,
                                0,
                                id[i],
                                rect[i][0],
                                rect[i][1] + y,
                                rect[i][2],
                                rect[i][3],
                                MainScnHWnd,
                                0,
                                0,
                                pCtrl);
        if (hCtrl == HWND_INVALID)
        {
            return FALSE;
        }
        SetWindowBkColor(hCtrl, bkColor);
        SetWindowTextColor(hCtrl, GetWindowElementColor(FGC_CAPTION_NORMAL));
        SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_SMAFONT));
    }
}


BOOL DestroyMainWindowControl(RESID id)
{
    return DestroyDialogControl(MainScnHWnd, id);
}

BOOL CreatePatientInfoCtrlGroup(VOID)
{
    enum{
        LABEL_HIGH = 14,
        MENU_LEFT = 1,
        MENU_TOP = BOTTOM_TOP + 1,
        MENU_RIGHT = SCREEN_WIDTH - 90,
        MENU_BOTTOM = SCREEN_HIGH,
        GROUP_LEFT = MENU_LEFT,
        GROUP_TOP = MENU_TOP,
        GROUP_WIDTH = 150,
        GROUP_HIGH = BOTTOMBAR_HEIGHT - 2,
    };
    RESID group_id[] = {
        IDC_BOTTOMBAR_PATIENT_G
    };
    RESID static_id[] = {
        IDC_BOTTOMBAR_PATIENT_INFO1_L,
        IDC_BOTTOMBAR_PATIENT_INFO2_L,
        IDC_BOTTOMBAR_PATIENT_INFO3_L
    };
    STRINGID caption[] = {
        STR_MAIN_PATIENT_INFO1,
        STR_MAIN_PATIENT_INFO2,
        STR_MAIN_PATIENT_INFO3
    };
    HWND hCtrl;
    PCONTROL pCtrl;
    PMSGMAP_ENTRY pMsgMap;
    int i;
	int y = GROUP_TOP;
    GAL_PIXEL bkColor;
	if (MONITOR_TYPE_AR2 == MonitorConfig.MonitorName)
	{
		y -= ARTEMIS2_BOTTOM_OFFSET;
	}
    bkColor = GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE);
    if (MonitorConfig.nightModeOn)
    {
        bkColor = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_GRAY);
    }

    for (i = 0; i < TABLESIZE(static_id); i++)
    {
        if (GetDlgItem(MainScnHWnd,static_id[i]))
        {
            if (!DestroyMainWindowControl(static_id[i]))
                return FALSE;
        }
    }
    i = 0;
    if (GetDlgItem(MainScnHWnd,group_id[i]))
    {
        if (!DestroyMainWindowControl(group_id[i]))
            return FALSE;
    }

    pCtrl = GetCtrlWndMem(group_id[i]);
    hCtrl = CreateWindowEx(CTRL_GROUPBOX, 0, WS_VISIBLE | WS_TABSTOP, 0,
                           group_id[i],
                           GROUP_LEFT,
                           y,
                           GROUP_WIDTH,
                           GROUP_HIGH,
                           MainScnHWnd,
                           0L,
                           (UINT32)&gGroupboxAdddata[GPB_BOTTOMBAR_PATIENT],
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
    SetWindowBkColor(hCtrl, bkColor);
    for (i = 0; i < TABLESIZE(static_id); i++)
    {
        pCtrl = GetCtrlWndMem(static_id[i]);
        hCtrl = CreateWindowEx(CTRL_STATIC, caption[i], WS_VISIBLE | SS_SIMPLE,
                               WS_NONE,     static_id[i],
                               GROUP_LEFT  + 2,
                               y   + 2 + i * LABEL_HIGH + i,
                               GROUP_WIDTH - 4,
                               LABEL_HIGH,
                               MainScnHWnd,
                               0L,
                               0L,
                               pCtrl);
        if (hCtrl == HWND_INVALID)
        {
            return FALSE;
        }
        SetWindowBkColor  (hCtrl, bkColor);
        SetWindowTextColor(hCtrl, GetWindowElementColor(FGC_CAPTION_NORMAL));
        SetWindowFont     (hCtrl, GetSystemFont(SYSLOGFONT_SMAFONT));
        SetWindowText     (hCtrl, caption[i]);
    }
}


BOOL CreateMenuGroupsCtrlGroup(int index, STRINGID caption, DWORD dwStyle,
                                DWORD dwAddData, DWORD dwAddData2, MSG_PFN proc)
{
    enum{
        MENU_LEFT = 220,
        MENU_TOP = BOTTOM_TOP + 1,
        MENU_RIGHT = SCREEN_WIDTH - 90,
        MENU_BOTTOM = SCREEN_HIGH,
        GROUP_LEFT = MENU_LEFT,
        GROUP_TOP = MENU_TOP,
        GROUP_WIDTH = 50,
        GROUP_HIGH = BOTTOMBAR_HEIGHT - 2,
    };
    RESID group_id[] = {
        IDC_BOTTOMBAR_MENU0_G,
        IDC_BOTTOMBAR_MENU1_G,
        IDC_BOTTOMBAR_MENU2_G,
        IDC_BOTTOMBAR_MENU3_G,
        IDC_BOTTOMBAR_MENU4_G,
        IDC_BOTTOMBAR_MENU5_G,
        IDC_BOTTOMBAR_MENU6_G,
    };
    RESID static_id[] = {
        IDC_BOTTOMBAR_MENU0_L,
        IDC_BOTTOMBAR_MENU1_L,
        IDC_BOTTOMBAR_MENU2_L,
        IDC_BOTTOMBAR_MENU3_L,
        IDC_BOTTOMBAR_MENU4_L,
        IDC_BOTTOMBAR_MENU5_L,
        IDC_BOTTOMBAR_MENU6_L,
    };
    HWND hCtrl;
    PCONTROL pCtrl;
    PMSGMAP_ENTRY pMsgMap;
    int i;
	int y = GROUP_TOP;
    GAL_PIXEL bkColor;
	if (MONITOR_TYPE_AR2 == MonitorConfig.MonitorName)
	{
		y -= ARTEMIS2_BOTTOM_OFFSET;
	}
    bkColor = GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE);
    if (MonitorConfig.nightModeOn)
    {
        bkColor = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_GRAY);
    }


    if (GetDlgItem(MainScnHWnd,static_id[index]))
    {
        if (!DestroyMainWindowControl(static_id[index]))
            return FALSE;
    }
    if (GetDlgItem(MainScnHWnd,group_id[index]))
    {
        if (!DestroyMainWindowControl(group_id[index]))
            return FALSE;
    }
    for (i = 0; i < MAINSN_MSGMAN_NR; i++)
    {
        pMsgMap = MainScn_MsgMapEntry + i;
        if (pMsgMap->nID == group_id[index])
        {
            pMsgMap->pfn = proc;
            break;
        }
        else
        {
            if (TABLESIZE(MainScn_MsgMapEntry) == i + 1)
                return FALSE;
        }
    }

    pCtrl = GetCtrlWndMem(group_id[index]);
    hCtrl = CreateWindowEx(CTRL_GROUPBOX, 0, WS_VISIBLE | WS_TABSTOP, 0,
                           group_id[index],
                           GROUP_LEFT + index * GROUP_WIDTH,
                           y,
                           GROUP_WIDTH,
                           GROUP_HIGH,
                           MainScnHWnd,
                           0,
                           (UINT32)&gGroupboxAdddata[GPB_BOTTOMBAR_MENU00 + index],
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
    SetWindowBkColor(hCtrl, bkColor);

    pCtrl = GetCtrlWndMem(static_id[index]);
    hCtrl = CreateWindowEx(CTRL_STATIC, caption, dwStyle, 0,
                           static_id[index],
                           GROUP_LEFT + index * GROUP_WIDTH + 2,
                           y + 2,
                           GROUP_WIDTH - 4,
                           GROUP_HIGH - 4,
                           MainScnHWnd,
                           dwAddData,
                           dwAddData2,
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
    SetWindowBkColor(hCtrl, bkColor);

    if (strlen(LoadString(caption)) > 0)
    {
        SetWindowTextColor(hCtrl, GetWindowElementColor(FGC_CAPTION_NORMAL));
        SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_WCHAR_DEF));
    }
    SetWindowText(hCtrl,caption);
    return TRUE;
}

VOID ShowPatinetInfo(VOID)
{
    HWND    hWnd;
    HDC     hdc;
    INT16   width;
    INT16   i;
    CHAR    *txt;
    CHAR    *text;
    INT16   show_len;
    
    /* 1 */
    hWnd = GetDlgItem(MainScnHWnd, IDC_BOTTOMBAR_PATIENT_INFO1_L);
    if (!hWnd)
    {
        return;
    }
    
    if (NULL == (txt = TextNew(128)))
        TextDel(txt);
    
    strcpy(txt, LoadString(STR_MAIN_TOPBAR_NAME_STR));
    strcat(txt, LoadString(STR_MAIN_TOPBAR_NAME_NAME));
    hdc   = GetDC(hWnd);
    width = RECTW(dc_HDC2PDC(hdc)->DevRC);
    show_len = GetTextOutLenExtent(hdc, width - 1, txt);
    ReleaseDC(hdc);
    
    text  = LoadString(STR_MAIN_PATIENT_INFO1);
    memset(text, '\0', GetWinStrLen(STR_MAIN_PATIENT_INFO1));
    strncpy(text, txt, show_len);
    SetWindowText(hWnd, STR_MAIN_PATIENT_INFO1);
    /* 2 */
    hWnd = GetDlgItem(MainScnHWnd, IDC_BOTTOMBAR_PATIENT_INFO2_L);
    if (!hWnd)
    {
        TextDel(txt);
        return;
    }
    strcpy(txt, LoadString(STR_MAIN_TOPBAR_ID_STR));
    strcat(txt, LoadString(STR_MAIN_TOPBAR_ID_NUM));
    hdc   = GetDC(hWnd);
    width = RECTW(dc_HDC2PDC(hdc)->DevRC);
    show_len = GetTextOutLenExtent(hdc, width - 1, txt);
    ReleaseDC(hdc);
    
    text  = LoadString(STR_MAIN_PATIENT_INFO2);
    memset(text, '\0', GetWinStrLen(STR_MAIN_PATIENT_INFO2));
    strncpy(text, txt, show_len);
    SetWindowText(hWnd, STR_MAIN_PATIENT_INFO2);
    /* 3 * /
    hWnd = GetDlgItem(MainScnHWnd, IDC_BOTTOMBAR_PATIENT_INFO3_L);
    if (!hWnd)
    {
        TextDel(txt);
        return;
    }
    strcpy(txt, LoadString(STR_MAIN_TOPBAR_ID_STR));
    strcat(txt, LoadString(STR_MAIN_TOPBAR_ID_NUM));
    
    hdc   = GetDC(hWnd);
    width = RECTW(dc_HDC2PDC(hdc)->DevRC);
    show_len = GetTextOutLenExtent(hdc, width - 1, txt);
    ReleaseDC(hdc);
    
    text  = LoadString(STR_MAIN_PATIENT_INFO3);
    memset(text, '\0', 150);
    strncpy(text, txt, show_len);
    SetWindowText(hWnd, STR_MAIN_PATIENT_INFO3);
    /* end */
    TextDel(txt);
}

BOOL CreateGroupsCtrlGroup()
{
    CreateAlarmInfoGroups();
    CreateStatusGroups();
    CreatePatientInfoCtrlGroup();
    CreateSysMenus();
    CreateTimeGroups();
    ShowPatinetInfo();
}



BOOL CreateInfobarBoard(VOID)
{
#if 0
    HWND hCtrl;
    PCONTROL pCtrl;
    pCtrl = GetCtrlWndMem(IDC_TOPBAR_BOARD);
    hCtrl = CreateWindowEx(CTRL_STATIC, 0, WS_VISIBLE | SS_SIMPLE, 0,
                           IDC_TOPBAR_BOARD,
                           0,
                           0,
                           SCREEN_WIDTH,
                           TOPBAR_HEIGHT,
                           MainScnHWnd,
                           0,
                           0,
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
    SetWindowBkColor(hCtrl, GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE));

    pCtrl = GetCtrlWndMem(IDC_BOTTOM_BOARD);
    hCtrl = CreateWindowEx(CTRL_STATIC, 0, WS_VISIBLE | SS_SIMPLE, 0,
                           IDC_BOTTOM_BOARD,
                           0,
                           BOTTOM_TOP,
                           SCREEN_WIDTH,
                           BOTTOMBAR_HEIGHT,
                           MainScnHWnd,
                           0,
                           0,
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
    SetWindowBkColor(hCtrl, GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE));
#else
    HWND hCtrl;
    PCONTROL pCtrl;
    int x, y, w, h;
    int i;
    GAL_PIXEL bkColor;
    bkColor = GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE);
    if (MonitorConfig.nightModeOn)
    {
        bkColor = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_GRAY);
    }

    y = BOTTOM_TOP + 1;
    h = BOTTOMBAR_HEIGHT - 2;
	if (MONITOR_TYPE_AR2 == MonitorConfig.MonitorName)
	{
		y -= ARTEMIS2_BOTTOM_OFFSET;
	}
    hCtrl = GetDlgItem(MainScnHWnd, IDC_BOTTOMBAR_PATIENT_G);
    if (hCtrl)
    {
        pCtrl = (PCONTROL)hCtrl;
        x = pCtrl->right;
        i = IDC_BOTTOMBAR_MENU0_G;
        while(!(hCtrl = GetDlgItem(MainScnHWnd, i)))
        {
            if (++i >= IDC_BOTTOMBAR_MENU6_G)
                break;
        }
        if (hCtrl)
        {
            pCtrl = (PCONTROL)hCtrl;
            w = pCtrl->left - x;
        }
        else
        {
            w = SCREEN_WIDTH - x;
        }
        pCtrl = GetCtrlWndMem(IDC_TOPBAR_BOARD);
        hCtrl = CreateWindowEx(CTRL_STATIC, 0, WS_VISIBLE | SS_SIMPLE, 0,
                               IDC_TOPBAR_BOARD,
                               x, y, w, h,
                               MainScnHWnd,
                               0,
                               0,
                               pCtrl);
        if (hCtrl == HWND_INVALID)
        {
            return FALSE;
        }
        SetWindowBkColor(hCtrl, bkColor);
    }
    i = IDC_BOTTOMBAR_MENU6_G;
    while(!GetDlgItem(MainScnHWnd, i))// 找到最右边的动态加载功能按件
    {
        if (--i == IDC_BOTTOMBAR_MENU0_G)
        {
            break;
        }
    }
    hCtrl = GetDlgItem(MainScnHWnd, i);
    if (hCtrl)
    {
        pCtrl = (PCONTROL)hCtrl;
        x = pCtrl->right;
        hCtrl = GetDlgItem(MainScnHWnd, IDC_BOTTOMBAR_TIME_G);
        if (hCtrl)
        {
            pCtrl = (PCONTROL)hCtrl;
            w = pCtrl->left - x;
        }
        else
        {
            w = SCREEN_WIDTH - x;
        }
        pCtrl = GetCtrlWndMem(IDC_BOTTOM_BOARD);
        hCtrl = CreateWindowEx(CTRL_STATIC, 0, WS_VISIBLE | SS_SIMPLE, 0,
                               IDC_BOTTOM_BOARD,
                               x, y, w, h,
                               MainScnHWnd,
                               0,
                               0,
                               pCtrl);
        if (hCtrl == HWND_INVALID)
        {
            return FALSE;
        }
        SetWindowBkColor(hCtrl, bkColor);
    }
#endif
    if (MonitorConfig.showHelp)
    {
        CreateHelpInfoLabel();
    }
}


/**
 * control list: groupbox x1
 
 IDC_MAIN_GRAPH_G = IDC_MAIN_FIRST,
 IDC_MAIN_GRAPH_L,
 IDC_MAIN_GRAPH_FHR_L,
 IDC_MAIN_GRAPH_TOCO_L,
 IDC_MAIN_GRAPH_TIME_L,
 *               static x4
 *               button x5
**/
BOOL CreateFetalGraph = FALSE;
BOOL CreateGraphGroup(VOID)
{
    extern BITMAP sys_icon[];
    enum graph_size{
        GPH_LEFT = WAVE_START,
        GPH_TOP = TOPBAR_HEIGHT + 3,
        GPH_WIDTH = WAVE_WIDTH,
        GPH_HIGH = WAVE_HIGH - 4,
        GPH_FHR_TOP = GPH_TOP,
        GPH_FHR_HIGH = 700 * SCREEN_HIGH / DIMENSIONS_H - 2,
        GPH_TIME_TOP = GPH_FHR_TOP + GPH_FHR_HIGH,
        GPH_TIME_HIGH = STATIC_HEIGHT,
        GPH_TOCO_TOP = GPH_TIME_TOP + GPH_TIME_HIGH,
        GPH_TOCO_HIGH = GPH_TOP + GPH_HIGH - GPH_TOCO_TOP - 2,
        GPH_TIME_LEFT = GPH_LEFT,
        GPH_TIME_WIDTH = 71,
        GPH_MOVL_LEFT = GPH_TIME_LEFT + GPH_TIME_WIDTH + 1,
        GPH_MOVL_WIDTH = 35,
        GPH_SCORLL_LEFT = GPH_MOVL_LEFT + GPH_MOVL_WIDTH + 1,
        GPH_SCORLL_WIDTH = 432,
        GPH_MOVR_LEFT = GPH_SCORLL_LEFT + GPH_SCORLL_WIDTH + 1,
        GPH_MOVR_WIDTH = GPH_MOVL_WIDTH,
        GPH_SPEED_LEFT = GPH_MOVR_LEFT + GPH_MOVR_WIDTH + 1,
        GPH_SPEED_WIDTH = GPH_WIDTH - GPH_SPEED_LEFT - 1
    };
    HWND     hCtrl;
    PCONTROL pCtrl;
    PWIN     pWin;
	int x, y, w, h;
	x = WAVE_START - 3;
	y = TOPBAR_HEIGHT + ARTEMIS2_TOP_OFFSET;
	w = WAVE_WIDTH + 7;
	h = WAVE_HIGH;
	if (MONITOR_TYPE_AR2 == MonitorConfig.MonitorName)
	{
		h -= ARTEMIS2_TOP_OFFSET + ARTEMIS2_BOTTOM_OFFSET;
	}
    pCtrl = GetCtrlWndMem(IDC_MAIN_GRAPH_G);
    hCtrl = CreateWindowEx(CTRL_GROUPBOX, 0,
						   WS_VISIBLE | WS_TABSTOP | GRB_SCROLL, 0,
                           IDC_MAIN_GRAPH_G,
                           x,
                           y,
                           w,
                           h,
                           MainScnHWnd,
                           0,
                           (UINT32)&gGroupboxAdddata[GPB_MAIN_GRAPH],
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
//    EnableWindow(hCtrl, FALSE);
    SetWindowBkColor(hCtrl, PIXEL_transparent);

    pCtrl = GetCtrlWndMem(IDC_MAIN_GRAPH_L);
    hCtrl = CreateWindowEx(CTRL_STATIC, 0, WS_VISIBLE | SS_SIMPLE, 0,
                           IDC_MAIN_GRAPH_L,
                           x,
                           y,
                           w,
                           h,
                           MainScnHWnd,
                           0,
                           0,
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
    SetWindowBkColor(hCtrl, PIXEL_transparent);

	x = GPH_LEFT;
	y += 2;
	w = sys_icon[IDI_FHR_GPH].width -1;
	h = sys_icon[IDI_FHR_GPH].height;
    pCtrl = GetCtrlWndMem(IDC_MAIN_GRAPH_FHR_L);
    hCtrl = CreateWindowEx(CTRL_STATIC, 0, WS_VISIBLE | SS_SIMPLE, 0,
                           IDC_MAIN_GRAPH_FHR_L,
                           x,
                           y,
						   w,
						   h,
                           MainScnHWnd,
                           0,
                           0,
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
    SetWindowBkColor(hCtrl, PIXEL_transparent);
    
//    SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_SMAFONT));//
    FetalWavePrint->hFhrGph = hCtrl;

	h = WAVE_HIGH;
	if (MONITOR_TYPE_AR2 == MonitorConfig.MonitorName)
	{
		h -= (ARTEMIS2_TOP_OFFSET + ARTEMIS2_BOTTOM_OFFSET);
	}
	y = TOPBAR_HEIGHT + ARTEMIS2_TOP_OFFSET;
	y += (h - sys_icon[IDI_TOCO_GPH].height - 1);
	w = sys_icon[IDI_TOCO_GPH].width + 1;
	h = sys_icon[IDI_TOCO_GPH].height + 1;
    pCtrl = GetCtrlWndMem(IDC_MAIN_GRAPH_TOCO_L);
    hCtrl = CreateWindowEx(CTRL_STATIC, 0, WS_VISIBLE | SS_SIMPLE, 0,
                           IDC_MAIN_GRAPH_TOCO_L,
                           x,
                           y,
                           w,
                           h,
                           MainScnHWnd,
                           0,
                           0,
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
    SetWindowBkColor(hCtrl, PIXEL_transparent);
    FetalWavePrint->hTocoGph = hCtrl;

	w = GPH_TIME_WIDTH;
	h = 13;
	y -= h;
    pCtrl = GetCtrlWndMem(IDC_MAIN_GRAPH_TIME_L);
    hCtrl = CreateWindowEx(CTRL_STATIC, 0, WS_VISIBLE | SS_CENTER, 0,
                           IDC_MAIN_GRAPH_TIME_L,
                           x,
                           y,
                           w,
                           h,
                           MainScnHWnd,
                           0,
                           0,
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
    SetWindowBkColor(hCtrl, PIXEL_black);
    SetWindowTextColor(hCtrl, GetWindowElementColor(FGC_CAPTION_NORMAL));

	x = GPH_SPEED_LEFT;
	w = GPH_SPEED_WIDTH;
    pCtrl = GetCtrlWndMem(IDC_MAIN_GRAPH_SPEED_L);
    hCtrl = CreateWindowEx(CTRL_STATIC, (STR_SWEEP_SPEED_1 + FhrConfig.sweep),
                           WS_VISIBLE | SS_CENTER, 0,
                           IDC_MAIN_GRAPH_SPEED_L,
                           x,
                           y,
                           w,
                           h,
                           MainScnHWnd,
                           0,
                           0,
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
    SetWindowBkColor(hCtrl, PIXEL_black);
    SetWindowTextColor(hCtrl, GetWindowElementColor(FGC_CAPTION_NORMAL));
    #if 0
    pCtrl = GetCtrlWndMem(IDC_MAIN_GRAPH_SCROLL_LEFT_B);
    hCtrl = CreateWindowEx(CTRL_BUTTON, STR_ARROW_LEFT,
                           WS_VISIBLE | WS_TABSTOP, 0,
                           IDC_MAIN_GRAPH_SCROLL_LEFT_B,
                           GPH_MOVL_LEFT,
                           GPH_TIME_TOP,
                           GPH_MOVL_WIDTH,
                           GPH_TIME_HIGH,
                           MainScnHWnd,
                           0,
                           (UINT32)&(FetalWavePrint->btnleft),
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
    SetWindowBkColor(hCtrl, PIXEL_black);
    SetWindowTextColor(hCtrl, GetWindowElementColor(FGC_CAPTION_NORMAL));
    SetWindowFont(hCtrl, GetSystemFont(SYSLOGFONT_FIXED));
    
    pCtrl = GetCtrlWndMem(IDC_MAIN_GRAPH_SCROLL_BAR_SC);
    if (FetalWavePrint->scrdata.maxnum != 1)
    {
        FetalWavePrint->scrdata.status = 0;
        FetalWavePrint->scrdata.minnum = 1;
        FetalWavePrint->scrdata.maxnum = 6;
        FetalWavePrint->scrdata.value = 1;
        FetalWavePrint->scrdata.step = 1;
        FetalWavePrint->scrdata.border = 1;
        FetalWavePrint->scrdata.minVisual = 2;
        FetalWavePrint->scrdata.addData = 0;
    }
    hCtrl = CreateWindowEx(CTRL_SCROLL, 0,
                           WS_VISIBLE | WS_HSCROLL | WS_TABSTOP, 0,
                           IDC_MAIN_GRAPH_SCROLL_BAR_SC,
                           GPH_SCORLL_LEFT,
                           GPH_TIME_TOP,
                           GPH_SCORLL_WIDTH,
                           GPH_TIME_HIGH,
                           MainScnHWnd,
                           0,
                           (UINT32)&(FetalWavePrint->scrdata),
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
    SetWindowBkColor(hCtrl, PIXEL_black);
//    SetWindowTextColor(hCtrl, GetWindowElementColor(WEC_EXCOLOR_BLANCHEDALMOND));
    
    pCtrl = GetCtrlWndMem(IDC_MAIN_GRAPH_SCROLL_RIGHT_B);
    hCtrl = CreateWindowEx(CTRL_BUTTON, STR_ARROW_RIGHT,
                           WS_VISIBLE | WS_TABSTOP, 0,
                           IDC_MAIN_GRAPH_SCROLL_RIGHT_B,
                           GPH_MOVR_LEFT,
                           GPH_TIME_TOP,
                           GPH_MOVR_WIDTH,
                           GPH_TIME_HIGH,
                           MainScnHWnd,
                           0,
                           (UINT32)&(FetalWavePrint->btnrignt),
                           pCtrl);
    if (hCtrl == HWND_INVALID)
    {
        return FALSE;
    }
    SetWindowBkColor(hCtrl, PIXEL_black);
    SetWindowTextColor(hCtrl, GetWindowElementColor(FGC_CAPTION_NORMAL));
    #endif
    CreateFetalGraph = TRUE;
}


VOID AddHelpString(VOID)
{
    int add[][2] = {
         { IDC_TOPBAR_ALARM_TECH_G,         STR_HELP_TECH_ALARM_INFO        }
        ,{ IDC_TOPBAR_ALARM_PHYS_G,         STR_HELP_PHYS_ALARM_INFO        }
        ,{ IDC_TOPBAR_STATUS_G,             STR_HELP_SYSTEM_STATUS          }
        ,{ IDC_BOTTOMBAR_PATIENT_G,         STR_HELP_PATIENT_SETUP          }
        ,{ IDC_BOTTOMBAR_MENU0_G,           STR_HELP_CHANGE_FACE            }
        ,{ IDC_BOTTOMBAR_MENU1_G,           STR_HELP_SYSTEM_MENU            }
        ,{ IDC_BOTTOMBAR_TIME_G,            STR_HELP_DATETIME_SETUP         }
        ,{ IDC_MAIN_GRAPH_SCROLL_LEFT_B,    STR_HELP_FETAL_WAVE_MOVE_LEFT   }
        ,{ IDC_MAIN_GRAPH_SCROLL_RIGHT_B,   STR_HELP_FETAL_WAVE_MOVE_RIGHT  }
		,{ IDC_MAIN_GRAPH_G,				STR_HELP_ENTER_VIEW_WAVE		}
    };
    int i;
    HWND hWnd;
    for (i = 0; i < TABLESIZE(add); i++)
    {
        if (hWnd = GetDlgItem(MainScnHWnd, add[i][0]))
        {
            SetHelpStringID(hWnd, IDC_HELP_INFORMATION_L, add[i][1]);
        }
    }
    
}
/**
**/
BOOL  CeateHotkeyCtrlGroup (VOID)
{
    return TRUE;
}




VOID  InitHotkeyChoice (VOID)
{
//    HWND     hWnd;
//    PCONTROL pCtrl;
    
    return;
}


#include <linux/rtc.h>
#include <fcntl.h>
#include <sys/ioctl.h>

int get_curr_time(void)
{
    time_t t;
    time (&t);
    return ((int)t);
}



VOID  UpdateSysDatetime (DATETIME *datetime)
{
        time_t cal_time;
        struct tm *plocal_time;
                 
        cal_time = (time_t)get_curr_time();
        plocal_time = localtime((const time_t *)&cal_time);
        DateTimeEx = *plocal_time;
            
        datetime->hour=plocal_time->tm_hour;
        datetime->minute=plocal_time->tm_min;
        datetime->second=plocal_time->tm_sec;

        datetime->year= plocal_time->tm_year + 1900;

        datetime->month=plocal_time->tm_mon + 1;
        datetime->day=plocal_time->tm_mday;

}


void SetRTCTime(void)
{
    int fd;
    time_t cal_time;
    struct tm *plocal_time;
    struct tm myLocalTime;
    time_t myTime;
    struct rtc_time rtcTime;
    time(&cal_time);

    memcpy(&myLocalTime,localtime((const time_t *)&cal_time),sizeof(myLocalTime));
    plocal_time=&myLocalTime;

    fd = open("/dev/rtc0", O_RDWR, 0);
    rtcTime.tm_year=plocal_time->tm_year;
    rtcTime.tm_mon=plocal_time->tm_mon;
    rtcTime.tm_mday=plocal_time->tm_mday;
    rtcTime.tm_hour=plocal_time->tm_hour;
    rtcTime.tm_min=plocal_time->tm_min;
    rtcTime.tm_sec=plocal_time->tm_sec;

   ioctl(fd,RTC_SET_TIME,&rtcTime);
   close(fd);
}


BOOL  InitMonitor (VOID)
{
    int  i; 
    
    UpdateSysDatetime(&DateTime);
    if (DateTime.year < 2000)
    {
        DateTime.year = 2013;
        DateTime.month = 12;
        DateTime.day = 1;
        DateTime.hour = 12;
        DateTime.minute = 0;
        DateTime.second = 0;
        SetSysDatetime(&DateTime);
    }

    ZeroMemory(&VerInfo[0], sizeof(VerInfo));

    MonitorConfig.moduleInfo[MID_KB].Id         = MID_KB;
    MonitorConfig.moduleInfo[MID_KB].OnLine     = TRUE;

    MonitorConfig.moduleInfo[MID_FHR].Id        = MID_FHR;
    MonitorConfig.moduleInfo[MID_FHR].OnLine    = TRUE;
    
    MonitorConfig.moduleInfo[MID_RECODER].Id    = MID_RECODER;
    MonitorConfig.moduleInfo[MID_RECODER].OnLine= TRUE;

    /** MONITOR INFO  **/
    MonitorInfo.inDemo             = OFF;
    MonitorInfo.inFrozen           = OFF;          
    MonitorInfo.skipKeyMessage     = FALSE;        
    
    MonitorInfo.keyCode            = KEY_UNDEFINED;  
    MonitorInfo.menuLev            = 0;              
    MonitorInfo.waveHeight         = 90;             

    InitWaveTypeInfo();                     
    MonitorInfo.waveTypeNum        = 5;          
    MonitorInfo.moduleNum          = 7;
    MonitorInfo.faceChanged        = FALSE;       
    MonitorInfo.battVolume         = -1;          
    MonitorInfo.powerStatus        = 0;           

//	ZeroMemory( MonitorInfo.deviceInfo, sizeof(MonitorInfo.deviceInfo));
	for (i = 0; i < DEV_MAX; i++) {
		MonitorInfo.deviceInfo[i].id	  = i;
		MonitorInfo.deviceInfo[i].devType = DEVTYPE_UART;
	//	MonitorInfo.deviceInfo[DEV_KB].port	= UART_PORT_KB;
		MonitorInfo.deviceInfo[i].online  = FALSE;
		MonitorInfo.deviceInfo[i].version = 0;
		MonitorInfo.deviceInfo[i].state   = 0;
		MonitorInfo.deviceInfo[i].addData = 0;
		MonitorInfo.deviceInfo[i].postResult = 0;
		ZeroMemory(MonitorInfo.deviceInfo[i].name, 10);
	}
	MonitorInfo.deviceInfo[DEV_NET].devType = DEVTYPE_NET;
	MonitorInfo.deviceInfo[DEV_NET].port	= 2014;
    return TRUE;
}


VOID  ClearPatientInfo (VOID)
{
    MonitorConfig.bedNo = BEDNO_INVALID;
    //Save_Sys_Config2(MMAP_SYS_PATIENT_BED_NO_PACE);

    return;
}


static INT32  OnCommand (HWND parent, UINT16 ctrl_id, UINT16 notify_code, LPARAM lParam)
{
    PMSGMAP_ENTRY     pMsgMap;
    int               i;
    for (i = 0; i < MAINSN_MSGMAN_NR; i++)
    {
        pMsgMap = MainScn_MsgMapEntry + i;
        if ((pMsgMap->nID == ctrl_id) && (pMsgMap->nCode == notify_code))
        {
            return (*pMsgMap->pfn)(parent, GetDlgItem(parent, ctrl_id), lParam);
        }
    }
    return (-1);
}

VOID ShowSweepSpeed(VOID)
{
    if(MonitorConfig.faceType == FACE_STD 
        || MonitorConfig.faceType == FACE_STD_SINGLE)
    {
        HWND  hWnd = GetDlgItem(MainScnHWnd, IDC_MAIN_GRAPH_SPEED_L);
        if (hWnd)
        {
            SetWindowText(hWnd, (STR_SWEEP_SPEED_1 + FhrConfig.sweep));
        }
    }
}

VOID   MainWndInit(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    hWnd = hWnd;
    wParam = wParam;
    lParam = lParam;
}




INT32  MainScnProc(HWND hWnd, INT32 message, WPARAM wParam, LPARAM lParam)
{    
//    HWND hwnd;
//    RECT rc;
//    HDC  hdc;
//    INT8 i = 0;
//    GAL_PIXEL oldColor;
    switch (message) {
        case  MSG_INITDIALOG:
            MainWndInit(hWnd, wParam, lParam);
            return 0;

        case  MSG_COMMAND:
            if (OnCommand(hWnd, LOWORD(wParam), HIWORD(wParam), lParam) < 0)    
                break;

            return 0;

        default:
            break;
    }

    return DefaultMainWinProc(hWnd, message, wParam, lParam);
}


/************************************************************************/
/*  函数名：ShowPhsAlarmInfo                                            */
/*  描述：  显示生理报警信息的函数.在gui server task中执行.             */
/*  参数：  无                                                          */
/*  返回值：无                                                          */
/************************************************************************/
VOID  ShowPhsAlarmInfo (VOID)
{
    GAL_PIXEL      bg_color[4];
    CHAR           str[20];
    CHAR          *text;
    HWND           hWnd;
    
    if ((AlmPrsntInfo.PhsAlm.Redraw == FALSE)
        && (MonitorInfo.faceChanged == FALSE))
    {
        return;
    }
    
    bg_color[0] = COLOR_red;                                         //高级报警
    bg_color[1] = COLOR_yellow;                                      //中级报警
    bg_color[2] = COLOR_yellow;                                      //低级报警
    bg_color[3] = GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE);   //正常背景; topbar的背景色
    if (MonitorConfig.nightModeOn)
    {
        bg_color[3] = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_DIMGRAY);
    }
    // 没有报警，清除生理报警区，返回
    if (AlmPrsntInfo.PhsAlm.AlmIndex == 0)//NULL) 
    {
        if (hWnd = GetDlgItem(MainScnHWnd, IDC_TOPBAR_ALM_INFO_L))
        {
            SetWindowBkColor(hWnd, bg_color[3]);//GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE));
            SetWindowText(hWnd, 0);
        }
        if (hWnd = GetDlgItem(MainScnHWnd, IDC_TOPBAR_ALM_DATE_L))
        {
            SetWindowBkColor(hWnd, bg_color[3]);//GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE));
            SetWindowText(hWnd, 0);
        }
        if (hWnd = GetDlgItem(MainScnHWnd, IDC_TOPBAR_ALM_TIME_L))
        {
            SetWindowBkColor(hWnd, bg_color[3]);//GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE));
            SetWindowText(hWnd, 0);
        }
        if (hWnd = GetDlgItem(MainScnHWnd, IDC_TOPBAR_ALM_LVL_L))
        {
            SetWindowBkColor(hWnd, bg_color[3]);//GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE));
            SetWindowText(hWnd, 0);
        }
        return;
    }
    
    // 显示报警级别提示
    hWnd = GetDlgItem(MainScnHWnd, IDC_TOPBAR_ALM_LVL_L);
    if (AlmPrsntInfo.PhsAlm.AlmLev != INVALIDALARMLEVEL) 
    {
        text = LoadString(STR_MAIN_TOPBAR_ALARM_LVL);
        SetWindowTextColor(hWnd, WAVE_REGION_BKCOLOR);
        SetWindowBkColor(hWnd, bg_color[AlmPrsntInfo.PhsAlm.BkGndColor]);
        SetWindowText(hWnd, STR_MAIN_TOPBAR_ALARM_LVL);
    }else {
        SetWindowBkColor(hWnd, bg_color[3]);//GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE));
        SetWindowText(hWnd, 0);
    }
    
    // 显示报警的字符串
    hWnd = GetDlgItem(MainScnHWnd, IDC_TOPBAR_ALM_INFO_L);
    text = LoadString(STR_MAIN_TOPBAR_ALARM_INFO);
    strcpy(text, AlmPrsntInfo.PhsAlm.AlmStr);
    SetWindowTextColor(hWnd, WAVE_REGION_BKCOLOR);
    SetWindowBkColor(hWnd, bg_color[AlmPrsntInfo.PhsAlm.BkGndColor]);
    SetWindowText(hWnd, STR_MAIN_TOPBAR_ALARM_INFO);

    // 显示报警发生的时间
    if (AlmPrsntInfo.PhsAlm.AlmTimePrsnt == TRUE)
    {
        hWnd = GetDlgItem(MainScnHWnd, IDC_TOPBAR_ALM_DATE_L);
        text = LoadString(STR_MAIN_TOPBAR_ALARM_DATE);
        if (MonitorConfig.language == CHINESE)
            sprintf(text, "%04d-%02d-%02d", AlmPrsntInfo.PhsAlm.Time.year,
                     AlmPrsntInfo.PhsAlm.Time.month, AlmPrsntInfo.PhsAlm.Time.day);
        else
            sprintf(text, "%02d-%02d-%04d", AlmPrsntInfo.PhsAlm.Time.month,
                     AlmPrsntInfo.PhsAlm.Time.day, AlmPrsntInfo.PhsAlm.Time.year);
                     
        SetWindowTextColor(hWnd, WAVE_REGION_BKCOLOR);
        SetWindowBkColor(hWnd, bg_color[AlmPrsntInfo.PhsAlm.BkGndColor]);
        SetWindowText(hWnd, STR_MAIN_TOPBAR_ALARM_DATE);

        hWnd = GetDlgItem(MainScnHWnd, IDC_TOPBAR_ALM_TIME_L);
        text = LoadString(STR_MAIN_TOPBAR_ALARM_TIME);
        sprintf(text, "%02d:%02d:%02d", AlmPrsntInfo.PhsAlm.Time.hour,
                AlmPrsntInfo.PhsAlm.Time.minute, AlmPrsntInfo.PhsAlm.Time.second);
        SetWindowTextColor(hWnd, WAVE_REGION_BKCOLOR);
        SetWindowBkColor(hWnd, bg_color[AlmPrsntInfo.PhsAlm.BkGndColor]);
        SetWindowText(hWnd, STR_MAIN_TOPBAR_ALARM_TIME);
    }else {
        hWnd = GetDlgItem(MainScnHWnd, IDC_TOPBAR_ALM_DATE_L);
        SetWindowBkColor(hWnd, bg_color[3]);//GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE));
        SetWindowText(hWnd, 0);

        hWnd = GetDlgItem(MainScnHWnd, IDC_TOPBAR_ALM_TIME_L);
        SetWindowBkColor(hWnd, bg_color[3]);//GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE));
        SetWindowText(hWnd, 0);
    }

    return;
}


/************************************************************************/
/*  函数名：ShowTechAlarmInfo                                           */
/*  描述：  显示技术报警信息的函数.在gui server task中执行.             */
/*  参数：  无                                                          */
/*  返回值：无                                                          */
/************************************************************************/
VOID ShowTechAlarmInfo(VOID)
{
    GAL_PIXEL    bg_color[4];
    CHAR         str[20];
    CHAR        *text;
    HWND         hWnd;
    
    if ((AlmPrsntInfo.TechAlm.Redraw == FALSE)
        && (MonitorInfo.faceChanged == FALSE))
    {
        return;
    }
    bg_color[0] = COLOR_red;           //高级报警
    bg_color[1] = COLOR_yellow;        //中级报警
    bg_color[2] = COLOR_yellow;        //低级报警
    bg_color[3] = GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE); 
    
    if (MonitorConfig.nightModeOn)
    {
        bg_color[3] = DEF_BACK_COLOR;//GetWindowElementColor(WEC_EXCOLOR_DIMGRAY);
    }
    hWnd = GetDlgItem(MainScnHWnd, IDC_TOPBAR_ALM_TECH_L);
    if (AlmPrsntInfo.TechAlm.AlmIndex == 0)//NULL) 
    {
        SetWindowBkColor(hWnd, bg_color[3]);//GetWindowElementColor(WEC_EXCOLOR_ROYALBLUE)); 
        SetWindowText(hWnd, 0);
        return;
    }
    text = LoadString(STR_MAIN_TOPBAR_ALARM_TECH);
    strcpy(text, AlmPrsntInfo.TechAlm.AlmStr);
    if (3 == AlmPrsntInfo.TechAlm.BkGndColor)
    {
        SetWindowTextColor(hWnd, PIXEL_white);
    }
    else
    {
        SetWindowTextColor(hWnd, PIXEL_black);
    }
    SetWindowBkColor(hWnd, bg_color[AlmPrsntInfo.TechAlm.BkGndColor]);
    SetWindowText(hWnd, STR_MAIN_TOPBAR_ALARM_TECH);
    return;
}

/************************************************************************/
/************************************************************************/
INT8  Alm_Lev = 3; 

INT8  Sound_Alm_Lev = 3;

VOID  ShowAlarmInfo (VOID)
{
    static INT32 Alm_Timer = 0;
    INT8   almLev;
    
    ShowPhsAlarmInfo();
    ShowTechAlarmInfo();

    if (AlmPrsntInfo.AlmLevel != -1) 
    {
    
        Alm_Lev = AlmPrsntInfo.AlmLevel;

        if (AlmPrsntInfo.AlmLevel == 3)
            almLev = 0;
        else
            almLev = AlmPrsntInfo.AlmLevel + 1;

        Sound_Alm_Lev = almLev;
    }

    Alm_Timer ++;
    if (Sound_Alm_Lev == 1)
    {
        if (Alm_Timer >= 11)
        {
            Alm_Timer = 0;
            PostMessage(SysApp_HTSK, MSG_APP_SOUND_CMD, 
                CMD_SOUND_SET_ALM_SOUND, Sound_Alm_Lev);
        }
    }
    else if (Sound_Alm_Lev == 2)
    {
        if (Alm_Timer >= 15)
        {
            Alm_Timer = 0;
            PostMessage(SysApp_HTSK, MSG_APP_SOUND_CMD,
                CMD_SOUND_SET_ALM_SOUND, Sound_Alm_Lev);
        }
    }
    if (AlmGlbCtlr.HighestAlmLev == 3)
    {
        Alm_Lev = 0;
    }
    else
    {
        Alm_Lev = AlmGlbCtlr.HighestAlmLev + 1;
    }    
    //因为现在的界面风格,切换界面后必须对报警信息重绘
    if (TRUE == MonitorInfo.faceChanged)
    {
        MonitorInfo.faceChanged = FALSE;
    }   
  return;
}

UCHAR *GetFetalHearIcon(VOID)
{
    return (vol_icon[MonitorConfig.nightModeOn][(FhrConfig.volume + 2) / 3]);
}

VOID ScreenSaver(CHAR *text)
{
    static int xpos = 1, ypos = 30;
    static int xstep = 5, ystep = 5;
    static SIZE size = {0};
    PDC pdc = &__mg_screen_dc;
    if (pdc->pLogFont != GetSystemFont(SYSLOGFONT_HUGE_PARAM))
        pdc->pLogFont=GetSystemFont(SYSLOGFONT_HUGE_PARAM);
    FillRect(HDC_SCREEN, xpos, ypos, size.cx, size.cy);
    gdi_get_TextOut_extent(pdc, pdc->pLogFont, text, strlen(text), &size);
    if (xpos + xstep + size.cx > SCREEN_WIDTH)
    {
        xstep = -5;
        xpos = SCREEN_WIDTH - size.cx - 1;
    }
    else if (xpos + xstep < 1)
    {
        xstep = 5;
        xpos = 1;
    }
    else
    {
        xpos += xstep;
    }
    if (ypos + ystep + size.cy > SCREEN_HIGH - BOTBAR_HEIGHT - 5)
    {
        ystep = -5;
        ypos = SCREEN_HIGH - BOTBAR_HEIGHT - 5 - size.cy;
    }
    else if (ypos + ystep < TOPBAR_HEIGHT + 5)
    {
        ystep = 5;
        ypos = TOPBAR_HEIGHT + 5;
    }
    else
    {
        ypos += ystep;
    }
    TextOut(HDC_SCREEN, xpos, ypos, text);
}

VOID FormatDateString(DATETIME *time, CHAR *str)
{
	char delimiter = MonitorConfig.date_delimiter;
	switch (MonitorConfig.date_format_type)
	{
		case FORMAT_YYYY_MM_DD:
			sprintf(str, "%04d%c%02d%c%02d",
				time->year, delimiter, time->month, delimiter, time->day);
			break;

		case FORMAT_MM_DD_YYYY:
			sprintf(str, "%02d%c%02d%c%04d",
				time->month, delimiter, time->day, delimiter, time->year);
			break;

		case FORMAT_DD_MM_YYYY:
			sprintf(str, "%02d%c%02d%c%04d",
				time->day, delimiter, time->month, delimiter, time->year);
			break;

		default:
			*str = '\0';
			break;
	}
}

VOID FormatTimeString(DATETIME *time, CHAR *str)
{
	char delimiter = ':';//MonitorConfig.time_delimiter;
	switch (MonitorConfig.time_format_type)
	{
		case FORMAT_HH_MM_SS:
			sprintf(str, "%02d%c%02d%c%02d",
				time->hour, delimiter, time->minute, delimiter, time->second);
			break;

		case FORMAT_HH_MM:
			sprintf(str, "%02d%c%02d", time->hour, delimiter, time->minute);
			break;

		case FORMAT_TT_HH_MM_SS:
			if (time->hour > 11)
			{
				char hour = time->hour;
				if (hour > 12)
					hour -= 12;
				sprintf(str, "PM%02d%c%02d%c%02d",
					hour, delimiter, time->minute, delimiter, time->second);
			}
			else
			{
				char hour = time->hour;
				if (hour == 0)
					hour = 12;
				sprintf(str, "AM%02d%c%02d%c%02d",
					hour, delimiter, time->minute, delimiter, time->second);
			}
			break;

		case FORMAT_TT_HH_MM:
			if (time->hour > 11)
			{
				char hour = time->hour;
				if (hour > 12)
					hour -= 12;
				sprintf(str, "PM %02d%c%02d", hour, delimiter, time->minute);
			}
			else
			{
				char hour = time->hour;
				if (hour == 0)
					hour = 12;
				sprintf(str, "AM %02d%c%02d", hour, delimiter, time->minute);
			}
			break;

		default:
			*str = '\0';
			break;
	}
}

VOID  ShowDateTime(VOID)
{
    static char sday = 7;
    HWND   hWnd;
    char  *text;
    
    UpdateSysDatetime(&DateTime);
    /**/
    hWnd = GetDlgItem(MainScnHWnd, IDC_BOTTOMBAR_DATE_L);
    if(hWnd == HWND_INVALID)
        return;
    text = LoadString(STR_MAIN_BOTTOM_DATE);
	FormatDateString(&DateTime, text);
//	sprintf(text, "%04d-%02d-%02d", DateTime.year, DateTime.month, DateTime.day);
    SetWindowText(hWnd, STR_MAIN_BOTTOM_DATE);

    if (DateTimeEx.tm_wday >= 0 && DateTimeEx.tm_wday < 7)
    {
        hWnd = GetDlgItem(MainScnHWnd, IDC_BOTTOMBAR_WEEK_L);
        if(hWnd == HWND_INVALID)
            return;
        sday = DateTimeEx.tm_wday;
        text = LoadString(STR_MAIN_BOTTOM_WEEK);
        strcpy(text, LoadString(gWeekName[DateTimeEx.tm_wday]));
        SetWindowText(hWnd, STR_MAIN_BOTTOM_WEEK);
    }
    
    hWnd = GetDlgItem(MainScnHWnd, IDC_BOTTOMBAR_TIME_L);
    if(hWnd == HWND_INVALID)
        return;
    /**/
    text = LoadString(STR_MAIN_BOTTOM_TIME);
	FormatTimeString(&DateTime, text);
//	sprintf(text, "%02d:%02d:%02d", DateTime.hour, DateTime.minute, DateTime.second);
    SetWindowText(hWnd, STR_MAIN_BOTTOM_TIME);
//	ScreenSaver(text);
}

VOID  SwitchOffDemoText (VOID)
{;}

VOID  ShowDemo(VOID)
{;}

VOID  BlinkDemo(VOID)
{;}

/*
 Function Name: SetParamStatus
 Description:   Set parameters canUsing status ;'写'墓锟斤拷sys server task锟街达拷.  
 Parameters:    module_id -- set which module's parameters,
                0: all modules, MID_ECG: ECG, MID_SPO2: spo2,
                MID_NIBP: nibp, MID_IBP: ibp, 
 Return:        Nothing
 Output:        Nothing
 Test&Revision: Done
*/
VOID  SetParamStatus (UINT8 mid, BOOL can_using)
{
    SetParamStatus2(mid, can_using);
}

VOID  SetParamStatus2 (UINT8 module_id, BOOL can_using)
{
   INT i;

   if (0 == module_id) {
      for (i = PARAM_MAX; i < PARAM_MAX; i++) {
         ParamsInfo[i].canUsing = can_using;
      }   
      return;   
   }

   switch (module_id) {

      default:
         break;
   }
}


/*
 Function Name: SetSensorStatus
 Parameters:    module_id -- set which module's sensors,
                0: all modules, MID_ECG: ECG, MID_SPO2: spo2,
                MID_NIBP: nibp, MID_IBP: ibp, 
                '写'墓锟斤拷sys server task锟街达拷.              
 Return:        Nothing
 Output:        Nothing
 Test&Revision: Done
*/
VOID  SetSensorStatus (UINT8 mid, INT8 recovered_sec)
{
    SetSensorStatus2(mid, recovered_sec);
}

VOID  SetSensorStatus2 (UINT8 module_id, INT8 recovered_sec)
{
   INT i;

   if (0 == module_id)
   {
      for (i = SENSOR_FIRST; i < SENSOR_MAX; i++) 
      {
         SensorStatus[i].recoveredSeconds = recovered_sec;
      }
      return;
   }

   switch (module_id) {

      default:
         break;
   }
}


VOID  GetTimeStr (DATETIME *time, CHAR *str)
{
    if ( MonitorConfig.language == CHINESE )
    {
        sprintf(str, "%04d-%02d-%02d  %02d:%02d:%02d", time->year, time->month,
                time->day, time->hour, time->minute, time->second);
    }
    else
    {
        sprintf(str, "%02d-%02d-%04d  %02d:%02d:%02d", time->month, time->day,
                time->year, time->hour, time->minute, time->second);
    }
}

/**
 **/
VOID  SetCtrlDataAddData2 (PCTRLDATA pData, INT16 ctrl_nr, INT16 id, UINT32 addData)
{
    int i;

    for (i = 0; i < ctrl_nr; i++)
    {
        if (pData[i].id == id)
        {
            pData[i].dwAddData2 = addData;
            break;
        }
    }
}


/**
 ** load monitor all module, called by GUI Task.
 **/
VOID  LoadSysModule (VOID)
{
    INT           i;
    MODULE_INFO  *module_info;
    
    module_info = &(MonitorConfig.moduleInfo[0]);
    for (i = 0; i < MID_MAX; i ++) {
       if (TRUE == module_info->OnLine) {
       
          switch (module_info->Id) {

             default:
                break;
          }
       }
       module_info ++;
    }
}

/**
**/
VOID  ProcAfterCreateTasks (VOID)
{
    INT16 open_trd_file = 0;
    
//    InitWave();

    if (!InitSysInfoItem()) {
        errprintf("Init infobar item failure\n");
    }
    
    if (!InitSysEvent()) {
        errprintf("Init monitor events failure\n");
    }
    
    InitKboard();

    InitFetal();
#if _ENB_REC_FUNC
    RecInit();
#endif
#if _ENB_TOUCH
	InitTouchScreen();
#endif
    StartLayoutSession();  //开始荧幕布局

    PostMessage(SysApp_HTSK, MSG_APP_POWERON, 0, 0);

    LoadSysModule();  //初始化模块的相关信息 -- empty 
    ClearScreen(COLOR_black); //这个函数可以不要，清屏函数   
//    RegisterSysEvent(STR_EVE_BOOTUP); //将系统事件写进注册表 
	PostMessage(SysUdpT_HTSK, MSG_NET_UDP_SETUP, 0, 0);
}


/*
 Function Name:  DataCorrection
 Description:    Add some data to complete the samples in one second,
                 this function must be called every second. 
                 sys server task.
 Parameters:     No
 Return:         Nothing
 Output:         Nothing
 Test&Revision:  Not yet
*/
VOID  DataCorrection( VOID )
{
   INT           i;
   MODULE_INFO * module_info;

   module_info = &(MonitorConfig.moduleInfo[0]);

   for(i = 0; i < MID_MAX; i ++) {
      if (TRUE == module_info->OnLine) {
      
         switch(module_info->Id) {
			case MID_FHR:
				FhrDataCorrection();
				break;
            default:
               break;
         }
      }
      module_info ++;
   }

   // Activate Data Process task
   //PostMessage(SysData_HTSK, MSG_SYS_DATA_PROC, 0, 0);
}

VOID  UpdateStatus(VOID)
{
   INT           i;
   MODULE_INFO  *module_info;
   static UINT8 oldstatus[MONITOR_STATUS_MAX] = {0};
   module_info = &(MonitorConfig.moduleInfo[0]);

   for(i = 0; i < MID_MAX; i ++)
   {
      if (TRUE == module_info->OnLine)
      {
         switch(module_info->Id)
         {
            case MID_KB:
                UpdateKeyboardStatus();
                //UpdateNetworkSataus();
                break;

            case MID_FHR:
                //UpdateFhrVOlStatus();
                break;

            case MID_RECODER:
			#if _ENB_REC_FUNC
                UpdatePrinterStatus();
			#endif
                break;

            default:
               break;
         }
      }
      module_info ++;
   }
   
   CollectParams(0);/*for all modules*/
}

VOID SetAllParamFont ()                                  //Change by Latrom_06-24-2011
{
    INT           i;
    MODULE_INFO  *module_info;

    module_info = &(MonitorConfig.moduleInfo[0]);
    for (i = 0; i < MID_MAX; i ++) 
    {       
       if (TRUE == module_info->OnLine) 
       {   
          switch (module_info->Id) 
          {
             default:
                break;
          }
       }
       module_info ++;
    }
}

VOID ReSetAllParamFont ()                                //Change by Latrom_06-24-2011
{
    INT           i;
    MODULE_INFO  *module_info;

    module_info = &(MonitorConfig.moduleInfo[0]);
    for (i = 0; i < MID_MAX; i ++) 
    {
       if (TRUE == module_info->OnLine) 
       {
       
          switch (module_info->Id) 
          {

             default:
                break;
          }
       }
       module_info ++;
    }
}

BOOL DealWithLangChange(UINT8 lang)
{
	HWND hMainWin;
	HWND hwnd;

	if (HWND_INVALID == MainScnHWnd)
	{
		return FALSE;
	}
	hMainWin = MainScnHWnd;
	hwnd = GetDlgItem(hMainWin, IDC_BOTTOMBAR_TIME_L);
	SetWindowFont(hwnd, GetSystemFont(SYSLOGFONT_DEFAULT));

	hwnd = GetDlgItem(hMainWin, IDC_BOTTOMBAR_WEEK_L);
	SetWindowFont(hwnd, GetSystemFont(SYSLOGFONT_DEFAULT));

	hwnd = GetDlgItem(hMainWin, IDC_BOTTOMBAR_DATE_L);
	SetWindowFont(hwnd, GetSystemFont(SYSLOGFONT_DEFAULT));

	hwnd = GetDlgItem(hMainWin, IDC_PATIENTINFO_SAVE_TIME_L);
	SetWindowFont(hwnd, GetSystemFont(SYSLOGFONT_DEFAULT));

	hwnd = GetDlgItem(hMainWin, IDC_PRINTERINFO_ELAPSE_TIME_L);
	SetWindowFont(hwnd, GetSystemFont(SYSLOGFONT_DEFAULT));

	hwnd = GetDlgItem(hMainWin, IDC_PRINTERINFO_PERIOD_TIME_L);
	SetWindowFont(hwnd, GetSystemFont(SYSLOGFONT_DEFAULT));

	hwnd = GetDlgItem(hMainWin, IDC_TOPBAR_ALM_TECH_L);
	SetWindowFont(hwnd, GetSystemFont(SYSLOGFONT_BIGFONT));

	hwnd = GetDlgItem(hMainWin, IDC_TOPBAR_ALM_INFO_L);
	SetWindowFont(hwnd, GetSystemFont(SYSLOGFONT_BIGFONT));

	return TRUE;

}

VOID SetAllModuleSelect (VOID)
{
    INT           i;
    MODULE_INFO  *module_info;
    
    module_info = &(MonitorConfig.moduleInfo[0]);
    for (i = 0; i < MID_MAX; i ++) 
    {
       if (TRUE == module_info->OnLine) 
       {
       
          switch (module_info->Id) 
          {
             default:
                break;
          }
       }
       module_info++;
    }
}

VOID IntoStandby (VOID)
{
    MonitorInfo.standby = 1;
    BacktoMainScreen ();
    fb_fillrect_ex(0, 0, 0, SCREEN_WIDTH, SCREEN_HIGH, 0, 0, 0);
    return;
}


VOID  SetSysDatetime (DATETIME *datep)
{
    struct tm tmp;
    struct timeval tv;
    tv.tv_usec = 0;//NULL;
    tmp.tm_year = datep->year - 1900;
    tmp.tm_mon = datep->month - 1;
    tmp.tm_mday = datep->day;
    tmp.tm_hour = datep->hour;
    tmp.tm_min = datep->minute;
    tmp.tm_sec = datep->second;
    tmp.tm_isdst = -1;
    tv.tv_sec = mktime(&tmp);

    if(settimeofday(&tv, NULL))
    {
        char datetime[32];
        sprintf (datetime ,
            "date -s \"%04d-%02d-%02d %02d:%02d:%02d\"",
            datep->year,    datep->month,   datep->day,
            datep->hour,    datep->minute,  datep->second);
        system(datetime);
    }
    // 写入硬件时钟
    system("hwclock -w");
}

// 在屏幕中央显示信息,必须在InitGDI之后调用
VOID ScreenInfoOut(UCHAR *info)
{
    PLOGFONT pFont = __mg_screen_dc.pLogFont;
    fb_fillrect_ex(0, DLG_OFFSET, SCREEN_HIGH - 50, SCREEN_WIDTH, SCREEN_HIGH - 1, 0, 0, 0);
    __mg_screen_dc.pLogFont = GetSystemFont(SYSLOGFONT_YAHEI17_FONT);
    ScreenTextOut(HDC_SCREEN, DLG_OFFSET, SCREEN_HIGH - 50, info, -1);
    __mg_screen_dc.pLogFont = pFont;
}

