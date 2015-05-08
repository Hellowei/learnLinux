#define NETCENTER_GLOBALS
#include "includes.h"

int StrHex2Int(UCHAR *szHex)
{
	UCHAR *ptr;
	int ret;
	ret = 0;
	ptr = szHex;
	while (*ptr == ' ') ptr++;
	while(*ptr <= 'f' && *ptr >= '0')
	{
		if (*ptr <= '9')
		{
			ret = (ret << 4);
			ret += (*ptr) - '0';
		}
		else if ((*ptr >= 'a' && *ptr <= 'f'))
		{
			ret = (ret << 4);
			ret += (*ptr) - 'a' + 0x0A;
		}
		else if ((*ptr >= 'A' && *ptr <= 'F'))
		{
			ret = (ret << 4);
			ret += (*ptr) - 'A' + 0x0A;
		}
		else
		{
			break;
		}
		if (ret & 0xF0000000)
		{
			break;//溢出
		}
		ptr++;
	}
	return ret;
}

VOID GetHWaddr(UCHAR *HWaddr)
{
	FILE *fp;
	CHAR buff[128];
	CHAR *pbuff;
	int   i;

	if (!HWaddr) return;

	memset(HWaddr, 0, 6);

	fp = popen("ifconfig eth0 | grep HWaddr", "r");

	if (fp == NULL) return;

	fread(&buff, sizeof(buff), 1, fp);

	pclose(fp);

	pbuff = strstr(buff, "HWaddr ");
	if (pbuff)
	{
		pbuff += strlen("HWaddr ");
		for (i = 0; i < 6; i++)
		{
			*(HWaddr + i) = (UCHAR)StrHex2Int(pbuff + i * 3);
		}
	}
}

BOOL GetNetworkStatus(VOID)
{
	FILE *fp;
	CHAR buff[128];
	CHAR *pbuff;
	BOOL ret = FALSE;

	fp = popen("ifconfig eth0 | grep RUNNING", "r");
	if (fp == NULL)
	{
		return ret;
	}
	fread(buff,sizeof(buff), 1, fp);
	pclose(fp);
	pbuff = strstr(buff, "RUNNING");
	if (pbuff)
	{
		ret = TRUE;
	}
	return ret;
}

VOID GetDefaultNetConfig()
{
	uint8  ipAddress[4] = {192,168,  1,135};				// IP
	uint8  ipGateWay[4] = {192,168,  1,  1};				// 网关
	uint8  ipMASK[4]	= {255,255,255,  0};				// 掩码
	uint8  ipServer[4]  = {192,168,  1,245};				// 服务器
	uint8  ipMAC[6]	 = {0x00,0x40,0x3d,0x9f,0x29,0x13};  // MAC地址
	NetConfig.enable = TRUE;

#if 0
	srand((unsigned)time(NULL));
	ipMAC[1] = LOBYTE(DateTime.year) + 1;
	ipMAC[2] = LOBYTE(DateTime.day) + 1;
	ipMAC[3] = LOBYTE(DateTime.hour) + 1;
	ipMAC[4] = LOBYTE(DateTime.second) + 1;
	ipMAC[5] = rand() & 0xff;
	memcpy(NetConfig.hwaddr, ipMAC, sizeof(ipMAC));
#else
	//不修改物理地址,直接获取
	GetHWaddr(NetConfig.hwaddr);
#endif

	memcpy(NetConfig.inet,   ipAddress, sizeof(ipAddress));
	memcpy(NetConfig.mask,   ipMASK,	sizeof(ipMASK));
	memcpy(NetConfig.gate,   ipGateWay, sizeof(ipGateWay));
//	memcpy(NetConfig.server, ipServer,  sizeof(ipServer));
	strcpy(NetConfig.server, "192.168.1.245");
	NetConfig.port = 2014;
	NetConfig.changeflag = FALSE;
}

BOOL SaveNetworkConfig(VOID)
{
	FILE *fp;
	fp = fopen(NETWORK_CONFIG_FILE, "wb");
	if (!fp)
	{
		perror("save network file error");
		return FALSE;
	}
	// 确保标志一致
	NetConfig.CharE = 'E';
	NetConfig.CharG = 'G';
	NetConfig.CharH = 'H';
	NetConfig.CharI = 'I';
	NetConfig.CharM = 'M';
	NetConfig.CharP = 'P';
	NetConfig.CharS = 'S';
	
	fwrite(&NetConfig, sizeof(NetConfig), 1, fp);
	fclose(fp);
	return TRUE;
}

VOID SetupServerIpPort(VOID)
{
	return;
}


static VOID SetupNetworkProc(VOID)
{
	#if QVFB_DEBUG
	return;
	#endif
	UCHAR cmd[128];
	// 设置IP和子网掩码
	sprintf(cmd, "ifconfig eth0 %d.%d.%d.%d netmask %d.%d.%d.%d",
	NetConfig.inet[0], NetConfig.inet[1], NetConfig.inet[2], NetConfig.inet[3],
	NetConfig.mask[0], NetConfig.mask[1], NetConfig.mask[2], NetConfig.mask[3]);
	system(cmd);

	// 设置网关
	sprintf(cmd, "route del default");
	//sprintf(cmd, "route del -net 192.168.1.0 netmask 255.255.255.0 dev eth0");
	system(cmd);
//	sprintf(cmd, "/sbin/route add default gw %d.%d.%d.%d",
//	NetConfig.gate[0], NetConfig.gate[1], NetConfig.gate[2], NetConfig.gate[3]);
//	printf("%s\n", cmd);
//	system(cmd);

#if 0
	// 设置物理地址
	sprintf(cmd, "ifconfig eth0 hw ether %02x:%02x:%02x:%02x:%02x:%02x",
	NetConfig.hwaddr[0], NetConfig.hwaddr[1], NetConfig.hwaddr[2],
	NetConfig.hwaddr[3], NetConfig.hwaddr[4], NetConfig.hwaddr[5]);
	system(cmd);
#endif
	if (NetConfig.enable == FALSE)
	{
		strcpy(cmd, "ifconfig eth0 down");
	}
	else
	{
		strcpy(cmd, "ifconfig eth0 down;ifconfig eth0 up");
	}
	system(cmd);

	sprintf(cmd, "route add default gw %d.%d.%d.%d",
	NetConfig.gate[0], NetConfig.gate[1], NetConfig.gate[2], NetConfig.gate[3]);
	system(cmd);
	// 设置服务器IP和端口
	SetupServerIpPort();
	// 恢复修改标志
	NetConfig.changeflag = FALSE;
	// 保存网络设置
	SaveNetworkConfig();
}

BOOL InitNetworkConfig(VOID)
{
	if (CheckFileExist(NETWORK_CONFIG_FILE))
	{
		FILE *fp;
		fp = fopen(NETWORK_CONFIG_FILE, "rb");
		if (fp)
		{
			fread(&NetConfig, sizeof(NetConfig), 1, fp);
			fclose(fp);
			// 判断读取的标志是否一致
			if (	NetConfig.CharE == 'E'
				&&  NetConfig.CharG == 'G'
				&&  NetConfig.CharH == 'H'
				&&  NetConfig.CharI == 'I'
				&&  NetConfig.CharM == 'M'
				&&  NetConfig.CharP == 'P'
				&&  NetConfig.CharS == 'S'	)
			{
				NetConfig.changeflag = TRUE;
				SetupNetworkProc();
				return TRUE;
			}
		}
	}
	GetDefaultNetConfig();
	NetConfig.changeflag = TRUE;
	SetupNetworkProc();
	return SaveNetworkConfig();
}

VOID NetworkSetupInit(HWND hWnd)
{
	SetListBoxCurChoi(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_SWITCH_LB,
		NetConfig.enable);
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_IPv4ADDR1_SB,
		NetConfig.inet[0]);
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_IPv4ADDR2_SB,
		NetConfig.inet[1]);
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_IPv4ADDR3_SB,
		NetConfig.inet[2]);
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_IPv4ADDR4_SB,
		NetConfig.inet[3]);
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_MASKADDR1_SB,
		NetConfig.mask[0]);
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_MASKADDR2_SB,
		NetConfig.mask[1]);
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_MASKADDR3_SB,
		NetConfig.mask[2]);
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_MASKADDR4_SB,
		NetConfig.mask[3]);
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_GATEADDR1_SB,
		NetConfig.gate[0]);
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_GATEADDR2_SB,
		NetConfig.gate[1]);
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_GATEADDR3_SB,
		NetConfig.gate[2]);
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_GATEADDR4_SB,
		NetConfig.gate[3]);
	/**
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_SERVERIP1_SB,
		NetConfig.server[0]);
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_SERVERIP2_SB,
		NetConfig.server[1]);
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_SERVERIP3_SB,
		NetConfig.server[2]);
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_SERVERIP4_SB,
		NetConfig.server[3]);
	**/
	SetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_PORT_SB,
		NetConfig.port);
	int i;
	HWND hCtrl;
	for (i = IDC_NETWORK_CFG_SWITCH_L; i <= IDC_NETWORK_CFG_PORT_L; i++)
	{
		hCtrl = GetDlgItem(hWnd, i);
		if (hCtrl)
			SetWindowBkColor(hCtrl,GetWindowElementColor(WEC_EXCOLOR_LAVENDER));
	}
	for ( i=IDC_NETWORK_CFG_SERVERIP1_SB; i<=IDC_NETWORK_CFG_SERVERIP4_SB; i++ )
	{
		hCtrl = GetDlgItem(hWnd, i);
		if (hCtrl)
		{
			ShowWindow(hCtrl, SW_HIDE);
			EnableWindow(hCtrl, FALSE);
		}
	}
	SetEditboxHardLimit(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_SERVER_EDIT,
		sizeof(NetConfig.server) - 1);
	NetConfig.server[sizeof(NetConfig.server) - 1] = '\0';
	SetEditText(IDD_NETWORK_CONFIGURE, IDC_NETWORK_CFG_SERVER_EDIT,
		NetConfig.server);
}



BOOL NetworkSetupOnCommand(HWND hWnd, DWORD wParam)
{
	INT16 ret = -100;
	switch(LOWORD(wParam))
	{
		case IDC_NETWORK_CFG_EXIT_B:
			// 无修改直接返回
			if (NetConfig.changeflag == TRUE)
			{
				SetupNetworkProc();
				PostMessage(SysUdpT_HTSK, MSG_NET_UDP_RESET, 0, 0);
			}
			EndDialog(hWnd, IDOK);
			break;
			
		case IDC_NETWORK_CFG_SWITCH_LB:
			if (HIWORD(wParam) == LBN_CHANGED)
			{
				ret = GetListBoxCurChoi(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.enable)
				{
					NetConfig.enable = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;
		
		
		case IDC_NETWORK_CFG_IPv4ADDR1_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.inet[0])
				{
					NetConfig.inet[0] = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;
		
		
		case IDC_NETWORK_CFG_IPv4ADDR2_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.inet[1])
				{
					NetConfig.inet[1] = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;
		
		
		case IDC_NETWORK_CFG_IPv4ADDR3_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.inet[2])
				{
					NetConfig.inet[2] = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;
		
		
		case IDC_NETWORK_CFG_IPv4ADDR4_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.inet[3])
				{
					NetConfig.inet[3] = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;
		
		
		case IDC_NETWORK_CFG_MASKADDR1_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.mask[0])
				{
					NetConfig.mask[0] = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;
		
		
		case IDC_NETWORK_CFG_MASKADDR2_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.mask[1])
				{
					NetConfig.mask[1] = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;
			
		
		case IDC_NETWORK_CFG_MASKADDR3_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.mask[2])
				{
					NetConfig.mask[2] = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;
		
		case IDC_NETWORK_CFG_MASKADDR4_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.mask[3])
				{
					NetConfig.mask[3] = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;
			
			
		case IDC_NETWORK_CFG_GATEADDR1_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.gate[0])
				{
					NetConfig.gate[0] = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;
				
				
		case IDC_NETWORK_CFG_GATEADDR2_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.gate[1])
				{
					NetConfig.gate[1] = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;

		case IDC_NETWORK_CFG_GATEADDR3_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.gate[2])
				{
					NetConfig.gate[2] = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;
				
				
		case IDC_NETWORK_CFG_GATEADDR4_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.gate[3])
				{
					NetConfig.gate[3] = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;

		case IDC_NETWORK_CFG_SERVERIP1_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.server[0])
				{
					NetConfig.server[0] = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;
			
		case IDC_NETWORK_CFG_SERVERIP2_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.server[1])
				{
					NetConfig.server[1] = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;
		
		
		case IDC_NETWORK_CFG_SERVERIP3_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.server[2])
				{
					NetConfig.server[2] = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;
		
		
		case IDC_NETWORK_CFG_SERVERIP4_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.server[3])
				{
					NetConfig.server[3] = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;
		
		
		case IDC_NETWORK_CFG_PORT_SB:
			if (HIWORD(wParam) == SBN_CHANGED)
			{
				ret = GetSpinBoxIntCurValue(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (ret != NetConfig.port)
				{
					NetConfig.port = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			if (HIWORD(wParam) == SBN_ENTER)
			{
				char tips[64];
				PCONTROL pCtrl = 
					GetSubCtrlItem(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				if (!pCtrl)
					return FALSE;
				sprintf(tips, "%d~%d", 
					SPINBOX_IMIN(pCtrl), SPINBOX_IMAX(pCtrl));
				INT32 value = GetSpinBoxIntCurValue
					(IDD_NETWORK_CONFIGURE, LOWORD(wParam));
				SelectKeyboardType(0, LoadString(STR_DLG_NET_PORT),  tips);
				UseKeyboard(hWnd, LOWORD(wParam), (LPARAM)&value);
				ret = (INT16)value;
				SetSpinBoxIntCurValue
					(IDD_NETWORK_CONFIGURE, LOWORD(wParam), ret);
				if (ret != NetConfig.port)
				{
					NetConfig.port = ret;
					NetConfig.changeflag = TRUE;
				}
			}
			break;

		case IDC_NETWORK_CFG_SERVER_EDIT:
			if (EN_CLICKED == HIWORD(wParam))
			{
				StrBuffer strbuff;
				NewStrBuffer(&strbuff, sizeof(NetConfig.server));
				if (strlen(NetConfig.server) > 0)
				{
					strcpy(strbuff.string, NetConfig.server);
				}
				SelectKeyboardType(KEYBOARD_LOWERCS, 
					LoadString(STR_DLG_NET_SERVERIP), "http://");
				UseKeyboard(hWnd, LOWORD(wParam),(LPARAM)&strbuff);
				memset(NetConfig.server, '\0', sizeof(NetConfig.server));
				strncpy(NetConfig.server, strbuff.string, 
					sizeof(NetConfig.server) - 1);
				TextDel(strbuff.string);
				SetEditText(IDD_NETWORK_CONFIGURE, LOWORD(wParam),
					NetConfig.server);
				NetConfig.changeflag = TRUE;
			}
			break;

		default:
			break;
	}
	return TRUE;
}

static INT32
NetworkSetupProc(HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	switch (message)
	{
		case MSG_INITDIALOG:
			NetworkSetupInit(hWnd);
			break;
		
		case MSG_COMMAND:
			if (NetworkSetupOnCommand(hWnd, wParam))
			{
				return 0;
			}
			break;

		default:
			break;
	}
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}

VOID NetworkSetupDialog(HANDLE hOwner)
{
	
//	if (IDOK != PasswordDialog(hOwner, 2, 0))
//	{
//		return;
//	}
	enum dialog_size{
		DLG_COLUMN1_W = 100,
		DLG_COLUMN2_W = 44,
		DLG_COLUMN3_W = DLG_COLUMN2_W * 4 + DLG_OFFSET * (4 - 1),
		DLG_COLUMN1_X = DLG_OFFSET,
		DLG_COLUMN2_X = DLG_COLUMN1_X + DLG_COLUMN1_W + DLG_OFFSET,
		DLG_COLUMN3_X = DLG_COLUMN2_X + DLG_COLUMN2_W + DLG_OFFSET,
		DLG_COLUMN4_X = DLG_COLUMN3_X + DLG_COLUMN2_W + DLG_OFFSET,
		DLG_COLUMN5_X = DLG_COLUMN4_X + DLG_COLUMN2_W + DLG_OFFSET,
			DLG_WIDTH = DLG_COLUMN2_X + DLG_COLUMN3_W + DLG_OFFSET,
		DLG_ROW_H	 = 29,
		LABEL_HIGH	= 14,
		LABEL_OFFSET  = (DLG_ROW_H - LABEL_HIGH) / 2,
		DLG_ROW1_Y	= DLG_OFFSET,
		DLG_ROW2_Y	= DLG_ROW1_Y + DLG_ROW_H + DLG_OFFSET,
		DLG_ROW3_Y	= DLG_ROW2_Y + DLG_ROW_H + DLG_OFFSET,
		DLG_ROW4_Y	= DLG_ROW3_Y + DLG_ROW_H + DLG_OFFSET,
		DLG_ROW5_Y	= DLG_ROW4_Y + DLG_ROW_H + DLG_OFFSET,
		DLG_ROW6_Y	= DLG_ROW5_Y + DLG_ROW_H + DLG_OFFSET,
			DLG_HIGH  = DLG_ROW6_Y + DLG_ROW_H + DLG_MENU_HIGHT + DLG_OFFSET,
			DLG_XPOS  = (SCREEN_WIDTH - DLG_WIDTH) / 2,
			DLG_YPOS  = SCREEN_HIGH - DLG_HIGH - BOTTOMBAR_HEIGHT
	};
	DLGTEMPLATE dlg_data = {
	   WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
	   (SCREEN_WIDTH - DLG_WIDTH) / 2, TOPBAR_HEIGHT + 1, DLG_WIDTH, DLG_HIGH,
	   STR_DLG_SETUP_NETWORK, 0, NULL, 0L	};
	CTRLDATA ctrl_data[]={ 
		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE,
			DLG_OFFSET, DLG_ROW1_Y + LABEL_OFFSET, DLG_COLUMN1_W, LABEL_HIGH,
			IDC_NETWORK_CFG_SWITCH_L, STR_DLG_NET_AUTOLINK, 0L, 0L }, 
		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE,
			DLG_OFFSET, DLG_ROW2_Y + LABEL_OFFSET, DLG_COLUMN1_W, LABEL_HIGH,
			IDC_NETWORK_CFG_IPv4_ADDR_L, STR_DLG_NET_IPADDR, 0L, 0L }, 
		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE,
			DLG_OFFSET, DLG_ROW3_Y + LABEL_OFFSET, DLG_COLUMN1_W, LABEL_HIGH,
			IDC_NETWORK_CFG_MASK_L, STR_DLG_NET_MASK, 0L, 0L }, 
		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE,
			DLG_OFFSET, DLG_ROW4_Y + LABEL_OFFSET, DLG_COLUMN1_W, LABEL_HIGH,
			IDC_NETWORK_CFG_GATEWAY_L, STR_DLG_NET_GATEWAY, 0L, 0L }, 
		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE,
			DLG_OFFSET, DLG_ROW5_Y + LABEL_OFFSET, DLG_COLUMN1_W, LABEL_HIGH,
			IDC_NETWORK_CFG_SERVERIP_L, STR_DLG_NET_SERVERIP, 0L, 0L }, 
		{ CTRL_STATIC,  WS_VISIBLE | SS_SIMPLE,  WS_EX_NONE,
			DLG_OFFSET, DLG_ROW6_Y + LABEL_OFFSET, DLG_COLUMN1_W, LABEL_HIGH,
			IDC_NETWORK_CFG_PORT_L, STR_DLG_NET_PORT, 0L, 0L }, 
		{ CTRL_LISTBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN2_X, DLG_ROW1_Y, DLG_COLUMN3_W, DLG_ROW_H,
			IDC_NETWORK_CFG_SWITCH_LB, 0, 0L, 0L }, 
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN2_X, DLG_ROW2_Y, DLG_COLUMN2_W, DLG_ROW_H,
			IDC_NETWORK_CFG_IPv4ADDR1_SB, 0, 0L, 0L }, 
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN3_X, DLG_ROW2_Y, DLG_COLUMN2_W, DLG_ROW_H,
			IDC_NETWORK_CFG_IPv4ADDR2_SB, 0, 0L, 0L },
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN4_X, DLG_ROW2_Y, DLG_COLUMN2_W, DLG_ROW_H,
			IDC_NETWORK_CFG_IPv4ADDR3_SB, 0, 0L, 0L },
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN5_X, DLG_ROW2_Y, DLG_COLUMN2_W, DLG_ROW_H,
			IDC_NETWORK_CFG_IPv4ADDR4_SB, 0, 0L, 0L },
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN2_X, DLG_ROW3_Y, DLG_COLUMN2_W, DLG_ROW_H,
			IDC_NETWORK_CFG_MASKADDR1_SB, 0, 0L, 0L },
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN3_X, DLG_ROW3_Y, DLG_COLUMN2_W, DLG_ROW_H,
			IDC_NETWORK_CFG_MASKADDR2_SB, 0, 0L, 0L },
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN4_X, DLG_ROW3_Y, DLG_COLUMN2_W, DLG_ROW_H,
			IDC_NETWORK_CFG_MASKADDR3_SB, 0, 0L, 0L },
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN5_X, DLG_ROW3_Y, DLG_COLUMN2_W, DLG_ROW_H,
			IDC_NETWORK_CFG_MASKADDR4_SB, 0, 0L, 0L },
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN2_X, DLG_ROW4_Y, DLG_COLUMN2_W, DLG_ROW_H,
			IDC_NETWORK_CFG_GATEADDR1_SB, 0, 0L, 0L },
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN3_X, DLG_ROW4_Y, DLG_COLUMN2_W, DLG_ROW_H,
			IDC_NETWORK_CFG_GATEADDR2_SB, 0, 0L, 0L },
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN4_X, DLG_ROW4_Y, DLG_COLUMN2_W, DLG_ROW_H,
			IDC_NETWORK_CFG_GATEADDR3_SB, 0, 0L, 0L },
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN5_X, DLG_ROW4_Y, DLG_COLUMN2_W, DLG_ROW_H,
			IDC_NETWORK_CFG_GATEADDR4_SB, 0, 0L, 0L },
		{ CTRL_EDIT, WS_VISIBLE | WS_TABSTOP, WS_EX_NONE, DLG_COLUMN2_X,
			DLG_ROW5_Y, DLG_WIDTH - DLG_OFFSET - DLG_COLUMN2_X, DLG_ROW_H,
			IDC_NETWORK_CFG_SERVER_EDIT,  STR_DLG_NET_SERVER, 0L, 0L },
			#if 0
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN2_X, DLG_ROW5_Y, DLG_COLUMN2_W, DLG_ROW_H,
			IDC_NETWORK_CFG_SERVERIP1_SB, 0, 0L, 0L },
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN3_X, DLG_ROW5_Y, DLG_COLUMN2_W, DLG_ROW_H,
			IDC_NETWORK_CFG_SERVERIP2_SB, 0, 0L, 0L },
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN4_X, DLG_ROW5_Y, DLG_COLUMN2_W, DLG_ROW_H,
			IDC_NETWORK_CFG_SERVERIP3_SB, 0, 0L, 0L },
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN5_X, DLG_ROW5_Y, DLG_COLUMN2_W, DLG_ROW_H,
			IDC_NETWORK_CFG_SERVERIP4_SB, 0, 0L, 0L },
			#endif
		{ CTRL_SPINBOX,  WS_VISIBLE | WS_TABSTOP,  WS_EX_NONE,
			DLG_COLUMN2_X, DLG_ROW6_Y, DLG_COLUMN3_W, DLG_ROW_H,
			IDC_NETWORK_CFG_PORT_SB, 0, 0L, 0L },
		{ CTRL_BUTTON,  WS_VISIBLE | WS_TABSTOP | BS_ICON,  WS_EX_NONE,
			DLG_WIDTH-EXIT_ICON_WIDTH - DLG_OFFSET,
			-(DLG_MENU_HIGHT + EXIT_ICON_HIGH) / 2,
			EXIT_ICON_WIDTH,  EXIT_ICON_HIGH,
			IDC_NETWORK_CFG_EXIT_B, STR_DLG_EXIT, 0L, 0L },
	};
	LISTBOXDATA lb = {
		.itemNum	= 2,
		.currItem	= 0,
		.topNdx		= 0,
		.botNdx		= 2,
		.infoList	= gOnOff,
	};
	EDITDATA edit_srv = {
		.hardLimit	= 99,
	};
	SPINBOXDATA sb[] = {
		//	IDC_NETWORK_CFG_IPv4ADDR1_SB,
		 { FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  0,   255, 0,  1,  0,  0 }
		//	IDC_NETWORK_CFG_IPv4ADDR2_SB,
		,{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  0,   255, 0,  1,  0,  0 }
		//	IDC_NETWORK_CFG_IPv4ADDR3_SB,
		,{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  0,   255, 0,  1,  0,  0 }
		//	IDC_NETWORK_CFG_IPv4ADDR4_SB,
		,{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  0,   255, 0,  1,  0,  0 }
		//	IDC_NETWORK_CFG_MASKADDR1_SB,
		,{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  0,   255, 0,  1,  0,  0 }
		//	IDC_NETWORK_CFG_MASKADDR2_SB,
		,{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  0,   255, 0,  1,  0,  0 }
		//	IDC_NETWORK_CFG_MASKADDR3_SB,
		,{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  0,   255, 0,  1,  0,  0 }
		//	IDC_NETWORK_CFG_MASKADDR4_SB,
		,{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  0,   255, 0,  1,  0,  0 }
		//	IDC_NETWORK_CFG_GATEADDR1_SB,
		,{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  0,   255, 0,  1,  0,  0 }
		//	IDC_NETWORK_CFG_GATEADDR2_SB,
		,{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  0,   255, 0,  1,  0,  0 }
		//	IDC_NETWORK_CFG_GATEADDR3_SB,
		,{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  0,   255, 0,  1,  0,  0 }
		//	IDC_NETWORK_CFG_GATEADDR4_SB,
		,{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  0,   255, 0,  1,  0,  0 }
		#if 0
		//	IDC_NETWORK_CFG_SERVERIP1_SB,
		,{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  0,   255, 0,  1,  0,  0 }
		//	IDC_NETWORK_CFG_SERVERIP2_SB,
		,{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  0,   255, 0,  1,  0,  0 }
		//	IDC_NETWORK_CFG_SERVERIP3_SB,
		,{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  0,   255, 0,  1,  0,  0 }
		//	IDC_NETWORK_CFG_SERVERIP4_SB,
		,{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,  0,   255, 0,  1,  0,  0 }
		#endif
		//	IDC_NETWORK_CFG_PORT_SB,
		,{ FORM_3D, SBTXT_NUM,   0,   0,   0,   0,1025, 9999,2014,1,  0,  0 }
	};
	BUTTONDATA  btn = gBtn_Exit;
	WNDMEM	  wndMem;
	
	int i, j, loops;
	
	loops = TABLESIZE(ctrl_data);
	
	for(i = IDC_NETWORK_CFG_IPv4ADDR1_SB; i <= IDC_NETWORK_CFG_GATEADDR4_SB; i++)
	{
		SetCtrlDataAddData2(ctrl_data, loops, i,
			(UINT32)&sb[i - IDC_NETWORK_CFG_IPv4ADDR1_SB]);
	}
	SetCtrlDataAddData2(ctrl_data, loops, IDC_NETWORK_CFG_PORT_SB,
		(UINT32)&sb[TABLESIZE(sb) - 1]);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_NETWORK_CFG_SERVER_EDIT,
		(UINT32)&edit_srv);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_NETWORK_CFG_SWITCH_LB,
		(UINT32)&lb);
	SetCtrlDataAddData2(ctrl_data, loops, IDC_NETWORK_CFG_EXIT_B,
		(UINT32)&btn);
	
	wndMem.pMainWin = GetMainWndMem(IDD_NETWORK_CONFIGURE);
	wndMem.pControl = GetCtrlWndMem(IDC_NETWORK_CFG_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;

	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;

	
	DialogBoxIndirectParam
		(&dlg_data, hOwner, IDD_NETWORK_CONFIGURE, NetworkSetupProc, 0, &wndMem);
}

