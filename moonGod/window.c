/*****************************************************************************************
��Ȩ����:			�����ص�
�汾��:				1.0.0
��������:			2011.04.15
�ļ���:				
����:				�����ص�
����˵��:			
����˵��:			��
�����ļ���ϵ:		���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
*****************************************************************************************/

#define   WINDOW_GLOBALS 
#include  "includes.h"


extern INT _menu_lev;


/* 3D ��� */
GAL_PIXEL WinElementColors [WEC_ITEM_NUMBER] = 
{
	//  b,g,r
	0x00808000,
	0x00FFFFFF,	// title fgcolor, (text color) white
	0x00808000,	// bkcolor, caption actived, dark cyan
	0x00FFFFFF,	// fgcolor, caption actived, black
	0x00808080,
	0x00EFC5BB,
	0x00000000,
	0x00FF0000,
	0x00000000,
	0x00C0C0C0,
	0x00000000,
	0x00800000,
	0x00FFFFFF,
	0x00808080,
	0x00C0C0C0,
	0x00000000,
	0x00800000,
	0x00FFFFFF,
	0x00808080,
	0x00C0C0C0,
	0x00FF0000,
	0x00000000,
	0x00808080,
	0x00000000,
	0x00808080,
	0x00FFFFFF,
	0x00C0C0C0,
	0x00FFFFFF,
	0x00C0C0C0,
	0x00FFFFFF,
	0x00FFFFFF,
	0x00808080,
	0x00808080,
	0x00C0C0C0,  // control bkcolor, light gray;  No 33
	0x00000000,  // control fgcolor, black
	0x00808080,  // dark gray
	0x00000000,  // text color, black
	0x00C0C0C0,  // dialog backgroundcolor, light gray
	0x00FF0000,  // focus control background color,  blue
	0x00FF0000,  // focus control frame background color, blue
	0x00808080,  // listbox drop background color, dark gray


	0x00FFB6C1, //41
	0x00FFC0CB, //42
	0x00DC143C, //43
	0x00FFF0F5, //44
	0x00DB7093, //45
	0x00FF69B4, //46
	0x00FF1493, //47
	0x00C71585, //48
	0x00DA70D6, //49
	0x00D8BFD8, //50
	0x00DDA0DD, //51
	0x00EE82EE, //52
	0x00FF00FF, //53
	0x00FF00FF, //54
	0x008B008B, //55
	0x00800080, //56
	0x00BA55D3, //57
	0x009400D3, //58
	0x009932CC, //59
	0x004B0082, //60
	0x008A2BE2, //61
	0x009370DB, //62
	0x007B68EE, //63
	0x006A5ACD, //64
	0x00483D8B, //65
	0x00E6E6FA, //66
	0x00F8F8FF, //67
	0x000000FF, //68
	0x000000CD, //69
	0x00191970, //70
	0x0000008B, //71
	0x00000080, //72
	0x004169E1, //73
	0x006495ED, //74
	0x00B0C4DE, //75
	0x00778899, //76
	0x00708090, //77
	0x001E90FF, //78
	0x00F0F8FF, //79
	0x004682B4, //80
	0x0087CEFA, //81
	0x0087CEEB, //82
	0x0000BFFF, //83
	0x00ADD8E6, //84
	0x00B0E0E6, //85
	0x005F9EA0, //86
	0x00F0FFFF, //87
	0x00E0FFFF, //88
	0x00AFEEEE, //89
	0x0000FFFF, //90
	0x0000FFFF, //91
	0x0000CED1, //92
	0x002F4F4F, //93
	0x00008B8B, //94
	0x00008080, //95
	0x0048D1CC, //96
	0x0020B2AA, //97
	0x0040E0D0, //98
	0x007FFFD4, //99
	0x0066CDAA, //100
	0x0000FA9A, //101
	0x00F5FFFA, //102
	0x0000FF7F, //103
	0x003CB371, //104
	0x002E8B57, //105
	0x00F0FFF0, //106
	0x0090EE90, //107
	0x0098FB98, //108
	0x008FBC8F, //109
	0x0032CD32, //110
	0x0000FF00, //111
	0x00228B22, //112
	0x00008000, //113
	0x00006400, //114
	0x007FFF00, //115
	0x007CFC00, //116
	0x00ADFF2F, //117
	0x00556B2F, //118
	0x009ACD32, //119
	0x006B8E23, //120
	0x00F5F5DC, //121
	0x00FAFAD2, //122
	0x00FFFFF0, //123
	0x00FFFFE0, //124
	0x00FFFF00, //125
	0x00808000, //126
	0x00BDB76B, //127
	0x00FFFACD, //128
	0x00EEE8AA, //129
	0x00F0E68C, //130
	0x00FFD700, //131
	0x00FFF8DC, //132
	0x00DAA520, //133
	0x00B8860B, //134
	0x00FFFAF0, //135
	0x00FDF5E6, //136
	0x00F5DEB3, //137
	0x00FFE4B5, //138
	0x00FFA500, //139
	0x00FFEFD5, //140
	0x00FFEBCD, //141
	0x00FFDEAD, //142
	0x00FAEBD7, //143
	0x00D2B48C, //144
	0x00DEB887, //145
	0x00FFE4C4, //146
	0x00FF8C00, //147
	0x00FAF0E6, //148
	0x00CD853F, //149
	0x00FFDAB9, //150
	0x00F4A460, //151
	0x00D2691E, //152
	0x008B4513, //153
	0x00FFF5EE, //154
	0x00A0522D, //155
	0x00FFA07A, //156
	0x00FF7F50, //157
	0x00FF4500, //158
	0x00E9967A, //159
	0x00FF6347, //160
	0x00FFE4E1, //161
	0x00FA8072, //162
	0x00FFFAFA, //163
	0x00F08080, //164
	0x00BC8F8F, //165
	0x00CD5C5C, //166
	0x00FF0000, //167
	0x00A52A2A, //168
	0x00B22222, //169
	0x008B0000, //170
	0x00800000, //171
	0x00FFFFFF, //172
	0x00F5F5F5, //173
	0x00DCDCDC, //174
	0x00D3D3D3, //175
	0x00C0C0C0, //176
	0x00A9A9A9, //177
	0x00808080, //178
	0x00696969, //179
	0x00080808, //180 
	0x00101010, //181 
	0x00040404, //182 
	0x00020202, //183
	0x00010101, //184
	0x00000000, //185 
	0xEA000000, //186
};


/* ��window.h MWM_ITEM_NUMBER, ���ڽ���Ԫ�صĳߴ��С */
INT16 WinMainMetrics [] = {
	10,			 //minwidth,   ��������С���
	10,			 //minheight,  ��������С�߶�
	1,			  //border,	 �߽�Ŀ��.
	2,			  //thickframe, ��߿�Ŀ��.
	1,			  //thinframe,  �ݱ߿�Ŀ��.
	DLG_MENU_HIGHT  //captiony,   �������ĸ߶�
};

typedef struct _color_string{
	INT32   clrNdx;
	UCHAR   clrName[60];
}CLR_STR; 
const CLR_STR clr_str[] = {
	{WEC_EXCOLOR_LIGHTPINK,			 "ǳ�ۺ�"},
	{WEC_EXCOLOR_PINK,				  "�ۺ�"},
	{WEC_EXCOLOR_CRIMSON,			   "���/�ɺ�"},
	{WEC_EXCOLOR_LAVENDERBLUSH,		 "���Ϻ�"},
	{WEC_EXCOLOR_PALEVIOLETRED,		 "����������"},
	{WEC_EXCOLOR_HOTPINK,			   "����ķۺ�"},
	{WEC_EXCOLOR_DEEPPINK,			  "��ۺ�"},
	{WEC_EXCOLOR_MEDIUMVIOLETRED,	   "����������"},
	{WEC_EXCOLOR_ORCHID,				"����ɫ/������"},
	{WEC_EXCOLOR_THISTLE,			   "��ɫ"},
	{WEC_EXCOLOR_PLUM,				  "����ɫ/������"},
	{WEC_EXCOLOR_VIOLET,				"������"},
	{WEC_EXCOLOR_MAGENTA,			   "���/õ���"},
	{WEC_EXCOLOR_FUCHSIA,			   "�Ϻ�/��������"},
	{WEC_EXCOLOR_DARKMAGENTA,		   "�����"},
	{WEC_EXCOLOR_PURPLE,				"��ɫ"},
	{WEC_EXCOLOR_MDEIUMORCHID,		  "��������"},
	{WEC_EXCOLOR_DARKVIOLET,			"��������"},
	{WEC_EXCOLOR_DARKORCHID,			"��������"},
	{WEC_EXCOLOR_INDIGO,				"����/����ɫ"},
	{WEC_EXCOLOR_BLUEVIOLET,			"��������"},
	{WEC_EXCOLOR_MEDIUMPURPLE,		  "����ɫ"},
	{WEC_EXCOLOR_MEDIUMSLATEBLUE,	   "�а���ɫ/�а�����"},
	{WEC_EXCOLOR_SLATEBLUE,			 "ʯ��ɫ/������"},
	{WEC_EXCOLOR_DARKSLATBLUE,		  "������ɫ/��������"},
	{WEC_EXCOLOR_LAVENDER,			  "����ɫ/Ѭ�²ݵ���"},
	{WEC_EXCOLOR_GHOSTWHITE,			"�����"},
	{WEC_EXCOLOR_BLUE,				  "����"},
	{WEC_EXCOLOR_MEDIUMBLUE,			"����ɫ"},
	{WEC_EXCOLOR_MIDNIGHTBLUE,		  "��ҹ��"},
	{WEC_EXCOLOR_DARKBLUE,			  "����ɫ"},
	{WEC_EXCOLOR_NAVY,				  "������"},
	{WEC_EXCOLOR_ROYALBLUE,			 "�ʼ���/����"},
	{WEC_EXCOLOR_CORNFLOWERBLUE,		"ʸ������"},
	{WEC_EXCOLOR_LIGHTSTEELBLUE,		"������"},
	{WEC_EXCOLOR_LIGHTSLATEGRAY,		"������/��ʯ���"},
	{WEC_EXCOLOR_SLATEGRAY,			 "��ʯɫ/ʯ���"},
	{WEC_EXCOLOR_DODGERBLUE,			"����ɫ/������"},
	{WEC_EXCOLOR_ALICEBLUE,			 "����˿��"},
	{WEC_EXCOLOR_STEELBLUE,			 "����/����"},
	{WEC_EXCOLOR_LIGHTSKYBLUE,		  "������ɫ"},
	{WEC_EXCOLOR_SKYBLUE,			   "����ɫ"},
	{WEC_EXCOLOR_DEEPSKYBLUE,		   "������"},
	{WEC_EXCOLOR_LIGHTBLUE,			 "����"},
	{WEC_EXCOLOR_POWDERBLUE,			"����ɫ/��ҩ��"},
	{WEC_EXCOLOR_CADETBLUE,			 "����ɫ/������"},
	{WEC_EXCOLOR_AZURE,				 "ε��ɫ"},
	{WEC_EXCOLOR_LIGHTCYAN,			 "����ɫ"},
	{WEC_EXCOLOR_PALETURQUOISE,		 "���̱�ʯ"},
	{WEC_EXCOLOR_CYAN,				  "��ɫ"},
	{WEC_EXCOLOR_AQUA,				  "ǳ��ɫ/ˮɫ"},
	{WEC_EXCOLOR_DARKTURQUOISE,		 "���̱�ʯ"},
	{WEC_EXCOLOR_DARKSLATEGRAY,		 "���߻�ɫ/��ʯ���"},
	{WEC_EXCOLOR_DARKCYAN,			  "����ɫ"},
	{WEC_EXCOLOR_TEAL,				  "ˮѼɫ"},
	{WEC_EXCOLOR_MEDIUMTURQUOISE,	   "���̱�ʯ"},
	{WEC_EXCOLOR_LIGHTSEAGREEN,		 "ǳ������"},
	{WEC_EXCOLOR_TURQUOISE,			 "�̱�ʯ"},
	{WEC_EXCOLOR_AQUAMARINE,			"��ʯ����"},
	{WEC_EXCOLOR_MEDIUMAQUAMARINE,	  "�б�ʯ����"},
	{WEC_EXCOLOR_MEDIUMSPRINGGREEN,	 "�д���ɫ"},
	{WEC_EXCOLOR_MINTCREAM,			 "��������"},
	{WEC_EXCOLOR_SPRINGGREEN,		   "����ɫ"},
	{WEC_EXCOLOR_MEDIUMSEAGREEN,		"�к�����"},
	{WEC_EXCOLOR_SEAGREEN,			  "������"},
	{WEC_EXCOLOR_HONEYDEW,			  "��ɫ/�۹�ɫ"},
	{WEC_EXCOLOR_LIGHTGREEN,			"����ɫ"},
	{WEC_EXCOLOR_PALEGREEN,			 "����ɫ"},
	{WEC_EXCOLOR_DARKSEAGREEN,		  "��������"},
	{WEC_EXCOLOR_LIMEGREEN,			 "��������"},
	{WEC_EXCOLOR_LIME,				  "������"},
	{WEC_EXCOLOR_FORESTGREEN,		   "ɭ����"},
	{WEC_EXCOLOR_GREEN,				 "����"},
	{WEC_EXCOLOR_DARKGREEN,			 "����ɫ"},
	{WEC_EXCOLOR_CHARTREUSE,			"����ɫ/���ؾ���"},
	{WEC_EXCOLOR_LAWNGREEN,			 "����ɫ/��ƺ��"},
	{WEC_EXCOLOR_GREENYELLOW,		   "�̻�ɫ"},
	{WEC_EXCOLOR_DARKOLIVEGREEN,		"�������"},
	{WEC_EXCOLOR_YELLOWGREEN,		   "����ɫ"},
	{WEC_EXCOLOR_OLIVEDRAB,			 "��魺�ɫ"},
	{WEC_EXCOLOR_BEIGE,				 "��ɫ/����ɫ"},
	{WEC_EXCOLOR_LIGHTGOLDENRODYELLOW,  "���ջ�"},
	{WEC_EXCOLOR_IVORY,				 "����ɫ"},
	{WEC_EXCOLOR_LIGHTYELLOW,		   "ǳ��ɫ"},
	{WEC_EXCOLOR_YELLOW,				"����"},
	{WEC_EXCOLOR_OLIVE,				 "���"},
	{WEC_EXCOLOR_DARKKHAKI,			 "���ƺ�ɫ/�ߴ��"},
	{WEC_EXCOLOR_LEMONCHIFFON,		  "���ʳ�"},
	{WEC_EXCOLOR_PALEGOLDENROD,		 "�Ҿջ�/������ɫ"},
	{WEC_EXCOLOR_KHAKI,				 "�ƺ�ɫ/��ߴ��"},
	{WEC_EXCOLOR_GOLD,				  "��ɫ"},
	{WEC_EXCOLOR_CORNSILK,			  "����˿ɫ"},
	{WEC_EXCOLOR_GOLRENROD,			 "��ջ�"},
	{WEC_EXCOLOR_DARKGOLDENROD,		 "����ջ�"},
	{WEC_EXCOLOR_FLORALWHITE,		   "���İ�ɫ"},
	{WEC_EXCOLOR_OLDLACE,			   "�ϻ�ɫ/����˿"},
	{WEC_EXCOLOR_WHEAT,				 "ǳ��ɫ/С��ɫ"},
	{WEC_EXCOLOR_MOCCASIN,			  "¹Ƥɫ/¹Ƥѥ"},
	{WEC_EXCOLOR_ORANGE,				"��ɫ"},
	{WEC_EXCOLOR_PAPAYAWHIP,			"��ľɫ/��ľ��"},
	{WEC_EXCOLOR_BLANCHEDALMOND,		"����ɫ"},
	{WEC_EXCOLOR_NAVAJOEWHITE,		  "���߰�/������"},
	{WEC_EXCOLOR_ANTIQUEWHITE,		  "�Ŷ���"},
	{WEC_EXCOLOR_TAN,				   "��ɫ"},
	{WEC_EXCOLOR_BURLYWOOD,			 "Ӳľɫ"},
	{WEC_EXCOLOR_BISQUE,				"������"},
	{WEC_EXCOLOR_DARKORANGE,			"���ɫ"},
	{WEC_EXCOLOR_LINEN,				 "���鲼"},
	{WEC_EXCOLOR_PERU,				  "��³ɫ"},
	{WEC_EXCOLOR_PEACHPUFF,			 "����ɫ"},
	{WEC_EXCOLOR_SANDYBROWN,			"ɳ��ɫ"},
	{WEC_EXCOLOR_CHOCOLATE,			 "�ɿ���ɫ"},
	{WEC_EXCOLOR_SADDLEBROWN,		   "�غ�ɫ/����ɫ"},
	{WEC_EXCOLOR_SEASHELL,			  "������"},
	{WEC_EXCOLOR_SIENNA,				"������ɫ"},
	{WEC_EXCOLOR_LIGHTSALMON,		   "ǳ������ɫ"},
	{WEC_EXCOLOR_CORAL,				 "ɺ��"},
	{WEC_EXCOLOR_ORANGERED,			 "�Ⱥ�ɫ"},
	{WEC_EXCOLOR_DARKSALMON,			"������/����ɫ"},
	{WEC_EXCOLOR_TOMATO,				"���Ѻ�"},
	{WEC_EXCOLOR_MISTYROSE,			 "ǳõ��ɫ/����õ��"},
	{WEC_EXCOLOR_SALMON,				"����/����ɫ"},
	{WEC_EXCOLOR_SNOW,				  "ѩ��ɫ"},
	{WEC_EXCOLOR_LIGHTCORAL,			"��ɺ��ɫ"},
	{WEC_EXCOLOR_ROSYBROWN,			 "õ����ɫ"},
	{WEC_EXCOLOR_INDIANRED,			 "ӡ�Ⱥ�"},
	{WEC_EXCOLOR_RED,				   "����"},
	{WEC_EXCOLOR_BROWN,				 "��ɫ"},
	{WEC_EXCOLOR_FIREBRICK,			 "��שɫ/�ͻ�ש"},
	{WEC_EXCOLOR_DARKRED,			   "���ɫ"},
	{WEC_EXCOLOR_MAROON,				"��ɫ"},
	{WEC_EXCOLOR_WHITE,				 "����"},
	{WEC_EXCOLOR_WHITESMOKE,			"����"},
	{WEC_EXCOLOR_GAINSBORO,			 "����ɫ"},
	{WEC_EXCOLOR_LIGHTGREY,			 "ǳ��ɫ"},
	{WEC_EXCOLOR_SILVER,				"����ɫ"},
	{WEC_EXCOLOR_DARKGRAY,			  "���ɫ"},
	{WEC_EXCOLOR_GRAY,				  "��ɫ"},
	{WEC_EXCOLOR_DIMGRAY,			   "������"},
	{WEC_EXCOLOR_BLACK,				 "����"},
	{WEC_EXCOLOR_TRANSPARENT,		   "͸��"},
};

UCHAR *GetColorName(INT32 index)
{
	INT32 clrNdx;
	UCHAR *szRet = (UCHAR*)LoadString(STR_NULL);
	clrNdx = index - clr_str[0].clrNdx;
	if (clrNdx < 0)
		return szRet;
	if (clrNdx > TABLESIZE(clr_str) - 1)
		return szRet;
	szRet = (UCHAR *)&clr_str[clrNdx].clrName[0];
	return szRet;
}


BOOL InitWindowElementColors (VOID)
{
	int		   i;
	unsigned long rgb;

	for (i = 0; i < WEC_EXCOLOR_TRANSPARENT; i++)
	{
		rgb = WinElementColors[i];
		if (i < WEC_EXCOLOR_LIGHTPINK)
		{
			WinElementColors[i] = RGB2Pixel(HDC_SCREEN, GetRValue(rgb), GetGValue(rgb), GetBValue(rgb));
		}
		else
		{
			WinElementColors[i] = RGB2Pixel(HDC_SCREEN, GetBValue(rgb), GetGValue(rgb), GetRValue(rgb));
		}
	}
	return TRUE;
}


static void RecalcClientArea (HWND hWnd)
{
	PMAINWIN pWin;
	RECT	 rcWin, rcClient;

	pWin = (PMAINWIN)hWnd;
	memcpy (&rcWin, &pWin->left, sizeof (RECT));
	memcpy (&rcClient, &pWin->cl, sizeof (RECT));

	if (SendMessage (hWnd, MSG_SIZECHANGED, (WPARAM)&rcWin, (LPARAM)&rcClient))
		memcpy (&pWin->cl, &rcClient, sizeof(RECT));
}

/**
** \brief  ���������ڣ�
** \param  pCreateInfo, �����Ľṹ
** \param  pWin, Ŀǰ��֧�ֶ�̬����, ���Ա������봰�ڵĵ�ַ;
** \param  hTsk, �����������ڵ�����.
** \note   ���pWin�ǿյģ�null��˵�����ڽṹ��Ҫ��̬������
**		 ���pCreateStruct�ǿյģ�˵��pWin�����г�ʼ�������ˣ�
**/
HWND GUIAPI CreateMainWindow (PMAINWINCREATE pCreateInfo, PMAINWIN pWin, HTSK hTsk )
{
	if( !pWin ) 
		return HWND_INVALID;

	pWin->pMainWin	  = NULL;
	pWin->hParent	   = HWND_DESKTOP;
		
	pWin->dataType	  = TYPE_HWND;
	pWin->winType	   = TYPE_MAINWIN;

	pWin->task		  = hTsk;
	_Chain_Initialize_empty(&pWin->subWinList);
	
	pWin->hActiveChild  = 0;

	pWin->dwStyle	   = pCreateInfo->dwStyle;
	pWin->dwExStyle	 = pCreateInfo->dwExStyle;

	pWin->pLogFont	  = GetSystemFont (SYSLOGFONT_SMAFONT);

	pWin->caption	   = pCreateInfo->caption;
	pWin->id			= pCreateInfo->id;

	pWin->winProc	   = pCreateInfo->proc;
	pWin->iBkColor	  = pCreateInfo->iBkColor;
	pWin->textColor	 = pCreateInfo->textColor;

	pWin->dwAddData	 = pCreateInfo->dwAddData;
	pWin->dwAddData2	= 0;

	/*�����޸�createinfo�ṹ*/
	if (SendMessage ((HWND)pWin, MSG_NCCREATE, 0, (LPARAM)pCreateInfo))
		goto err;

	if (!(pWin->dwStyle & WS_ABSSCRPOS)) 
	{
		pCreateInfo->lx += g_rcScr.left;
		pCreateInfo->ty += g_rcScr.top;
		pCreateInfo->rx += g_rcScr.left;
		pCreateInfo->by += g_rcScr.top;
	}

	/* �����޸Ĵ�������С. */
	SendMessage ((HWND)pWin, MSG_SIZECHANGING, 
				 (WPARAM)&pCreateInfo->lx, (LPARAM)&pWin->left);
	
	SendMessage ((HWND)pWin, MSG_CHANGESIZE, (LPARAM)&pWin->left, 0);

	RecalcClientArea((HWND)pWin);
	
	SendMessage (HWND_DESKTOP, MSG_ADDNEWMAINWIN, (WPARAM)pWin, 0);
	
	/* There was a very large bug. 
	 * We should add the new main window in system and then
	 * SendMessage MSG_CREATE for application to create
	 * child windows.
	 */
	if (SendMessage ((HWND)pWin, MSG_CREATE, 0, (LPARAM)pCreateInfo)) 
	{
		SendMessage (HWND_DESKTOP, MSG_REMOVEMAINWIN, (WPARAM)pWin, 0);
		goto err;
	}

	return (HWND)pWin;

err:
	return HWND_INVALID;
}

/**
   dwAdddata2,   private data address.
   pNewCtrk,	 address of Control struct.
**/
HWND GUIAPI CreateWindowEx (const char *spClassName, STRINGID caption,
							DWORD dwStyle, DWORD dwExStyle, short id, 
							short x, short y, short w, short h,
							HWND hParentWnd, DWORD dwAddData,
							DWORD dwAddData2, PCONTROL pNewCtrl)
{
	PMAINWIN	   pMainWin;
	PCTRLCLASSINFO cci;
	RECT		   rcExpect;
//	int			i;

	pMainWin = GetMainWindow (hParentWnd);
	if (!pMainWin) return HWND_INVALID;

	cci = (PCTRLCLASSINFO)SendMessage (HWND_DESKTOP,
									   MSG_GETCTRLCLASSINFO,
									   0,
									   (LPARAM)spClassName );
				
	if (!cci) 
		return HWND_INVALID;

	if (!pNewCtrl) 
		return HWND_INVALID;

	pNewCtrl->dataType = TYPE_HWND;
	pNewCtrl->winType  = TYPE_CONTROL;

	pNewCtrl->left	 = x;
	pNewCtrl->top	  = y;
	pNewCtrl->right	= x + w;
	pNewCtrl->bottom   = y + h;

	memcpy (&pNewCtrl->cl, &pNewCtrl->left, sizeof (RECT));
	memcpy (&rcExpect, &pNewCtrl->left, sizeof (RECT));

	pNewCtrl->caption = caption;
		
	pNewCtrl->dwStyle   = dwStyle | WS_CHILD | cci->dwStyle;
	pNewCtrl->dwExStyle = dwExStyle | cci->dwExStyle;

	pNewCtrl->iBkColor  = cci->iBkColor;
	pNewCtrl->textColor = cci->textColor;
	if (pNewCtrl->dwExStyle & WS_EX_USEPARENTFONT)
		pNewCtrl->pLogFont = pMainWin->pLogFont;
	else
		pNewCtrl->pLogFont = GetSystemFont (SYSLOGFONT_SMAFONT);

	pNewCtrl->id		 = id;
	pNewCtrl->dwAddData  = dwAddData;
	pNewCtrl->dwAddData2 = dwAddData2;

	pNewCtrl->ctrlProc = cci->proc;
	pNewCtrl->active   = NULL;

	pNewCtrl->pMainWin = (PMAINWIN)pMainWin;
	pNewCtrl->pParent  = (PCONTROL)hParentWnd;
	_Chain_Initialize_empty(&pNewCtrl->subWinList);
	
	pNewCtrl->pcci	 = cci;

	if (SendMessage ((HWND)pNewCtrl, MSG_NCCREATE, 0, (LPARAM)pNewCtrl)) {
		goto error;
	}
	
	SendMessage (HWND_DESKTOP, MSG_NEWCTRLINSTANCE, 
				 (WPARAM)hParentWnd, (LPARAM)pNewCtrl);
	
	if (SendMessage((HWND)pNewCtrl, MSG_CREATE, (WPARAM)hParentWnd, (LPARAM)dwAddData)) {
		SendMessage (HWND_DESKTOP, MSG_REMOVECTRLINSTANCE, 
					 (WPARAM)hParentWnd, (LPARAM)pNewCtrl);
		goto error;
	}

	SendMessage ((HWND)pNewCtrl, MSG_SIZECHANGING,
				 (WPARAM)&rcExpect, (LPARAM)&pNewCtrl->left);
	
	SendMessage ((HWND)pNewCtrl, MSG_CHANGESIZE, (LPARAM)&pNewCtrl->left, 0);

	RecalcClientArea ((HWND)pNewCtrl);

	if (pNewCtrl->pParent->dwStyle & WS_VISIBLE && pNewCtrl->dwStyle & WS_VISIBLE)
		;//UpdateWindow ((HWND)pNewCtrl, TRUE);  //�˺��������ﲻ���κ����� -- empty 2011/04/13

	return (HWND)pNewCtrl;

error:
	return HWND_INVALID;
}


/*************************** Main window and thread **************************/
PMAINWIN MainWindow (HWND hWnd)
{
	PMAINWIN pWin;

	pWin = (PMAINWIN)hWnd;
	if(pWin->dataType != TYPE_HWND)
		return NULL;

	if (pWin->winType == TYPE_MAINWIN)
		return pWin;

	return NULL; 
}

PMAINWIN GetMainWindow (HWND hWnd)
{
	PMAINWIN pWin;

	/* ����HWND_DESKTOP����1, ����Ҫ���϶�0���ж�. */
	if (hWnd == HWND_DESKTOP || hWnd == HWND_INVALID || hWnd == 0 )
		return NULL;

	pWin = (PMAINWIN)hWnd;
	if(pWin->dataType != TYPE_HWND)
		return NULL;

	if (pWin->winType == TYPE_MAINWIN)
		return pWin;

	return ((PCONTROL)hWnd)->pMainWin;
}


BOOL GUIAPI IsWindow (HWND hWnd)
{
	PCONTROL pWin;

	pWin = (PCONTROL) hWnd;
	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return FALSE;

	return TRUE;
}

BOOL GUIAPI IsMainWindow(HWND hWnd)
{
	PCONTROL pChildWin;

	pChildWin = (PCONTROL)hWnd;
	if(pChildWin->dataType != TYPE_HWND) 
		return FALSE;
		
	if(pChildWin->winType == TYPE_MAINWIN) 
		return TRUE;

	return FALSE;
}

BOOL GUIAPI IsControl(HWND hWnd)
{
	PCONTROL pChildWin;

	pChildWin = (PCONTROL)hWnd;
	if(pChildWin->dataType != TYPE_HWND) 
		return FALSE;
		
	if(pChildWin->winType == TYPE_CONTROL) 
		return TRUE;

	return FALSE;
}

HWND GUIAPI GetParent (HWND hWnd)
{
	PCONTROL pChildWin = (PCONTROL)hWnd;

	if (hWnd == HWND_DESKTOP)
		return HWND_DESKTOP;

	if (pChildWin->dataType != TYPE_HWND)
		return HWND_INVALID;
	
	return (HWND)pChildWin->pParent;
}


HWND GUIAPI GetMainWindowHandle (HWND hWnd)
{
	return (HWND)GetMainWindow (hWnd);
}


BOOL GUIAPI ExcludeWindowStyle (HWND hWnd, DWORD dwStyle)
{
	PMAINWIN pWin = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return FALSE;

	pWin->dwStyle &= ~dwStyle;
	return TRUE;
}

BOOL GUIAPI IncludeWindowStyle (HWND hWnd, DWORD dwStyle)
{
	PMAINWIN pWin = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return FALSE;

	pWin->dwStyle |= dwStyle;
	return TRUE;
}

BOOL GUIAPI GetClientRect (HWND hWnd, PRECT prc)
{
	PMAINWIN pWin = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP) {
		*prc = g_rcScr;
		return TRUE;
	}
	else if (pWin->dataType != TYPE_HWND)
		return FALSE;

	prc->left   = prc->top = 0;
	prc->right  = pWin->cr - pWin->cl;
	prc->bottom = pWin->cb - pWin->ct;
	return TRUE;
}

/******************** main window and control styles support *****************/
GAL_PIXEL  GUIAPI GetWindowBkColor (HWND hWnd)
{
	PMAINWIN pWin = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return PIXEL_invalid;

	return pWin->iBkColor;
}

GAL_PIXEL  GUIAPI GetWindowTextColor (HWND hWnd)
{
	PMAINWIN pWin = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return PIXEL_invalid;

	return pWin->textColor;
}

GAL_PIXEL  GUIAPI  SetWindowBkColor (HWND hWnd, GAL_PIXEL new_bkcolor)
{
	GAL_PIXEL old_bkcolor;

	PMAINWIN pWin = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return PIXEL_invalid;

	old_bkcolor	= pWin->iBkColor;
	pWin->iBkColor = new_bkcolor;
	return old_bkcolor;
}

GAL_PIXEL  GUIAPI  SetWindowTextColor (HWND hWnd, GAL_PIXEL new_color)
{
	GAL_PIXEL old_color;

	PMAINWIN pWin = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return PIXEL_invalid;

	old_color	   = pWin->textColor;
	pWin->textColor = new_color;
	return old_color;
}

PLOGFONT GUIAPI GetWindowFont (HWND hWnd)
{
	PMAINWIN pWin = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return NULL;

	return pWin->pLogFont;
}

PLOGFONT GUIAPI SetWindowFont (HWND hWnd, PLOGFONT pLogFont)
{
	PLOGFONT old_logfont = NULL;
	PMAINWIN pWin = (PMAINWIN)hWnd;
	
	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		goto ret;

	if (pLogFont == NULL)
		pLogFont = GetSystemFont (SYSLOGFONT_SMAFONT);

	if (SendMessage (hWnd, MSG_FONTCHANGING, 0, (LPARAM)pLogFont))
		goto ret;

	old_logfont	= pWin->pLogFont;
	pWin->pLogFont = pLogFont;
	SendMessage (hWnd, MSG_FONTCHANGED, 0, 0);

ret:
	return old_logfont;
}

DWORD GetWindowStyle (HWND hWnd)
{
	PMAINWIN pWin = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return 0;

	return pWin->dwStyle;
}

DWORD GetWindowExStyle (HWND hWnd)
{
	PMAINWIN pWin = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return 0;

	return pWin->dwExStyle;
}

DWORD GUIAPI GetWindowAdditionalData (HWND hWnd)
{
	PMAINWIN pWin = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return 0;

	return pWin->dwAddData;
}

DWORD GUIAPI SetWindowAdditionalData (HWND hWnd, DWORD newData)
{
	DWORD	oldOne = 0L;
	PMAINWIN pWin   = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return oldOne;

	oldOne		  = pWin->dwAddData;
	pWin->dwAddData = newData;
	return oldOne;
}

DWORD GUIAPI GetWindowAdditionalData2 (HWND hWnd)
{
	PMAINWIN pWin = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return 0;

	return pWin->dwAddData2;
}

const char* GUIAPI GetClassName (HWND hWnd)
{
	PMAINWIN pWin;
	PCONTROL pCtrl;

	pWin = (PMAINWIN)hWnd;
	if (hWnd == HWND_DESKTOP || pWin->winType == TYPE_MAINWIN)
		return MAINWINCLASSNAME;
	else if (pWin->winType == TYPE_CONTROL) {
		pCtrl = (PCONTROL)hWnd;
		return pCtrl->pcci->name;
	}

	return NULL;
}

DWORD GUIAPI SetWindowAdditionalData2 (HWND hWnd, DWORD newData)
{
	DWORD	oldOne = 0L;
	PMAINWIN pWin = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return oldOne;

	oldOne		   = pWin->dwAddData2;
	pWin->dwAddData2 = newData;
	return oldOne;
}

BOOL GUIAPI IsWindowVisible (HWND hWnd)
{
	PMAINWIN pMainWin;
	PCONTROL pCtrl;
	
	pMainWin = MainWindow (hWnd);
	if (pMainWin) {
		return (pMainWin->dwStyle & WS_VISIBLE) > 0;
	}
	else if (IsControl (hWnd)) {
		if (!IsWindowVisible (GetParent (hWnd)))
			return FALSE;

		pCtrl = (PCONTROL)hWnd;
		return (pCtrl->dwStyle & WS_VISIBLE) > 0;
	}
		
	return FALSE;
}

void GUIAPI ScreenToClient (HWND hWnd, long* x, long* y)
{
	PCONTROL pParent;
	PCONTROL pCtrl;

	pParent = pCtrl = (PCONTROL) hWnd;
	if (hWnd == HWND_DESKTOP || pCtrl->dataType != TYPE_HWND)
		return;

	*x -= pCtrl->cl;
	*y -= pCtrl->ct;
	pParent = pParent->pParent;
	while (pParent) {
		*x -= pParent->cl;
		*y -= pParent->ct;
		pParent = pParent->pParent;
	}
}

void GUIAPI ClientToScreen(HWND hWnd, long* x, long* y)
{
	PCONTROL pParent;
	PCONTROL pCtrl;

	pParent = pCtrl = (PCONTROL) hWnd;
	if (hWnd == HWND_DESKTOP || pCtrl->dataType != TYPE_HWND)
		return;

	*x += pCtrl->cl;
	*y += pCtrl->ct;
	pParent = pParent->pParent;
	while (pParent) {
		*x += pParent->cl;
		*y += pParent->ct;
		pParent = pParent->pParent;
	}
}

void GUIAPI ScreenToWindow(HWND hWnd, long* x, long* y)
{
	PCONTROL pParent;
	PCONTROL pCtrl;

	pParent = pCtrl = (PCONTROL) hWnd;
	if (hWnd == HWND_DESKTOP || pCtrl->dataType != TYPE_HWND)
		return;

	*x -= pCtrl->left;
	*y -= pCtrl->top;
	pParent = pParent->pParent;
	while (pParent) {
		*x -= pParent->left;
		*y -= pParent->top;
		pParent = pParent->pParent;
	}
}

void GUIAPI WindowToScreen(HWND hWnd, long* x, long* y)
{
	PCONTROL pParent;
	PCONTROL pCtrl;

	pParent = pCtrl = (PCONTROL) hWnd;
	if (hWnd == HWND_DESKTOP || pCtrl->dataType != TYPE_HWND)
		return;

	*x += pCtrl->left;
	*y += pCtrl->top;
	pParent = pParent->pParent;
	while (pParent) {
		*x += pParent->left;
		*y += pParent->top;
		pParent = pParent->pParent;
	}
}

BOOL GUIAPI GetWindowRect (HWND hWnd, PRECT prc)
{
	PMAINWIN pWin = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return FALSE;

	prc->left   = pWin->left;
	prc->top	= pWin->top;
	prc->right  = pWin->right;
	prc->bottom = pWin->bottom;
	return TRUE;
}

WNDPROC GUIAPI GetWindowCallbackProc (HWND hWnd)
{
	PMAINWIN pWin = (PMAINWIN) hWnd;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return NULL;

	return pWin->winProc;
}

WNDPROC GUIAPI SetWindowCallbackProc (HWND hWnd, WNDPROC newProc)
{
	PMAINWIN pWin = (PMAINWIN) hWnd;
	WNDPROC  old_proc;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return NULL;

	old_proc = pWin->winProc;
	if (newProc)
		pWin->winProc = newProc;
	return old_proc;
}

INT16 GUIAPI GetWindowCaption (HWND hWnd)
{
	PMAINWIN pWin = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP || pWin->dataType != TYPE_HWND)
		return 0;

	return pWin->caption;
}

BOOL GUIAPI SetWindowCaption (HWND hWnd, INT16 caption)
{
	PMAINWIN pWin = (PMAINWIN)hWnd;

	if (hWnd == HWND_DESKTOP)
		return FALSE;
	else if (pWin->winType == TYPE_MAINWIN)
		return SetWindowText (hWnd, caption);
	else if (pWin->winType == TYPE_CONTROL) {
		PCONTROL pCtrl;
		pCtrl = (PCONTROL)hWnd;
		pCtrl->caption = caption;
		return TRUE;
	}

	return FALSE;
}
long  GUIAPI GetWindowTextLength (HWND hWnd)
{
	return SendMessage (hWnd, MSG_GETTEXTLENGTH, 0, 0);
}

long  GUIAPI GetWindowText (HWND hWnd, INT16* strP)
{
	return SendMessage (hWnd, MSG_GETTEXT, 0, (LPARAM)strP);
}

BOOL GUIAPI SetWindowText (HWND hWnd, INT16 string_id)
{
	return (SendMessage (hWnd, MSG_SETTEXT, 0, (LPARAM)string_id) == 0);
}

BOOL GUIAPI SetWindowItem (HWND hWnd, DWORD addData2)
{
	return (SendMessage (hWnd, MSG_SETITEM, 0, addData2) == 0);
}
/************************* GUI calls support ********************************/

static HWND set_focus_helper (HWND hWnd)
{
	PMAINWIN pWin;

	if (IsMainWindow (hWnd))
		return HWND_INVALID;

	pWin = (PMAINWIN) GetParent (hWnd);
	if (!_Addresses_Equal((void*)pWin->hActiveChild, (void*)hWnd)) {

		if (pWin->hActiveChild) 
		{
			SendMessage (pWin->hActiveChild, MSG_KILLFOCUS, 0, 0);
		}	  
		pWin->hActiveChild = hWnd;
		SendMessage (hWnd, MSG_SETFOCUS, 0, 0);
	}
	
	return pWin->hActiveChild;
}

HWND GUIAPI SetFocusChild (HWND hWnd)
{
	HWND hOldActive;

	if ((hOldActive = set_focus_helper (hWnd)) != HWND_INVALID) {
		do 
		{
			hWnd = GetParent (hWnd);
		} while (set_focus_helper (hWnd) != HWND_INVALID);
	}

	return hOldActive;
}

/**
	���ô���Ϊ���㴰��;ͬʱ����ǰһ�����㴰��ʧȥ����. 
**/
HWND GUIAPI GetFocusChild (HWND hWnd)
{
	PMAINWIN pWin;
	
	pWin = (PMAINWIN) hWnd;
	if (pWin)
		return pWin->hActiveChild;
	
	return HWND_INVALID;
}

// NOTE: this function support ONLY main window.
HWND GUIAPI SetActiveWindow(HWND hMainWnd)
{
	HWND hOld;
	
	if (!IsMainWindow (hMainWnd))
		return HWND_INVALID;
	hOld = (HWND) SendMessage (HWND_DESKTOP, MSG_SETACTIVEMAIN, (WPARAM)hMainWnd, 0);

/**
	SendMessage (hMainWnd, MSG_NCACTIVATE, TRUE, 0);

	if (hOld)
		SendMessage (hOld, MSG_NCACTIVATE, FALSE, 0);
**/
	return hOld;
}

// NOTE: this function support ONLY main window.
HWND GUIAPI GetActiveWindow (void)
{
	return (HWND)SendMessage (HWND_DESKTOP, MSG_GETACTIVEMAIN, 0, 0);
}

DWORD  GUIAPI  GetControlStatus(PCONTROL pCtrl)
{
	char   name[30+1];
	DWORD  status;

	status = 0;
	strncpy(name, GetClassName((HWND)pCtrl), 30);

	if (strcmp(name, CTRL_STATIC) == 0) 
		status = 0;
	else if (strcmp(name, CTRL_BUTTON) == 0)
		status = BUTTON_STATUS(pCtrl);
	else if (strcmp(name, CTRL_EDIT) == 0)
		status = EDIT_STATUS(pCtrl);
	else if (strcmp(name, CTRL_LISTBOX) == 0)
		status = LISTBOX_STATUS(pCtrl);
	else if (strcmp( name, CTRL_SPINBOX) == 0)
		status = SPINBOX_STATUS(pCtrl);
	else if (strcmp(name, CTRL_CHECKBOX) == 0)
		status = CHECKBOX_STATUS(pCtrl);
	else if (strcmp(name, CTRL_SCROLL) == 0)
		status = SCROLL_STATUS(pCtrl);
	else if (strcmp(name, CTRL_GROUPBOX) == 0)
		status = GROUPBOX_STATUS(pCtrl);

	return status;
}


PMAINWIN  GetTopWndItem(INT32 id)
{
	PMAINWIN  pMainWin;
	PMAINWIN  pStart;
	CHAIN_CONTROL *pWinList;
	
	pMainWin = (PMAINWIN)HWND_INVALID;
	pWinList = &((TSKP)SysGui_HTSK)->winList;
	
	if (_Chain_Is_empty(pWinList))  
		return  pMainWin;
	
	pStart = (PMAINWIN)pWinList->first;
	while (!_Addresses_Equal(pStart, _Chain_Tail(pWinList))) {
		if (pStart->id == id) {
			pMainWin = pStart;
			break;
		}
		pStart = (PMAINWIN) pStart->node.next;
	}

	return  pMainWin;
}

PCONTROL  GUIAPI  GetSubCtrlItem(INT32 parent, INT32 ctrl)
{
	PMAINWIN	   pMainWin;
	PCONTROL	   pStart;
	PCONTROL	   pCtrl;
	CHAIN_CONTROL *pWinList;

	pMainWin = GetTopWndItem(parent);
	if (HWND_INVALID == (HWND)pMainWin)  
		return NULL;

	pCtrl	= NULL;
	pWinList = &pMainWin->subWinList;
	pStart   = (PCONTROL)pWinList->first;

	while (!_Addresses_Equal(pStart, _Chain_Tail(&pMainWin->subWinList)))
	{
		if (pStart->id == ctrl)
		{
			pCtrl = pStart;
			break;
		}

		pStart = (PCONTROL)pStart->node.next;
	}

	return pCtrl;
}

INT16 GUIAPI GetControlPtr(UINT16 parent_id, UINT16 ctrl_id,
							const char * CtrlName, PCONTROL *pCtrl)
{
	char	   name[32];
	if (!pCtrl)
	{
		return ERR_CTRLCLASS_MEM;
	}
	if (!CtrlName)
	{
		return ERR_CTRLCLASS_INVNAME;
	}
	*pCtrl = GetSubCtrlItem(parent_id, ctrl_id);
	if (!(*pCtrl))
	{
		return ERR_CTRLID_NOT_EXIST;
	}
	strncpy(name, GetClassName((HWND)*pCtrl), 8);
	if (strcmp(name, CtrlName) != 0) 
	{
		return ERR_CTRLID_MISMATCH_CTRLCLASS;
	}
	return ERR_OK;
}

/// �ڴ������ϰ��£��л���ǰ����ؼ�
/// 1 ѭ�������ӿؼ�
/// 2 ����������ӿؼ���Χ֮�ڣ���Ϊ����ؼ�
/// 3 ���Ͱ�����Ϣ

static VOID WndClientRect(HWND hWnd, PRECT prc)
{
	PCONTROL pCtrl;
	PCONTROL pParent;
	pParent = pCtrl = (PCONTROL) hWnd;

	if (hWnd == HWND_DESKTOP) {
		*prc = g_rcScr;
		return;
	}

	prc->left   = pCtrl->cl;
	prc->top	= pCtrl->ct;
	prc->right  = pCtrl->cr;
	prc->bottom = pCtrl->cb;
	
	pParent = pParent->pParent;
	while (pParent) {
		prc->left   += pParent->cl;
		prc->top	+= pParent->ct;
		prc->right  += pParent->cl;
		prc->bottom += pParent->ct;
		pParent	  = pParent->pParent;
	}
}

BOOL FramFoucs(PMAINWIN pMainWin, INT32 x, INT32 y)
{
	PMAINWIN  pStart;
	CHAIN_CONTROL *pWinList;

	pWinList = &((TSKP)SysGui_HTSK)->winList;

	pWinList = &(pMainWin->subWinList);

	if (_Chain_Is_empty(pWinList))  
		return 0;

	pStart = (PMAINWIN)pWinList->first;

	while (!_Addresses_Equal(pStart, _Chain_Tail(pWinList))) 
	{
		RECT rc;
		WndClientRect ((HWND)pStart, &rc);

		if (PtInRect (&rc, x, y)) 
		{
			
			if (pStart->dwStyle & WS_DISABLED)
			{
				return 0;
			}
			if (pStart->dwStyle & WS_TABSTOP)
			{
				SetFocus((HWND)pStart);
				return 1;
			}
			return 0;
		}

		pStart = (PMAINWIN) pStart->node.next;
	}
	return 0;
}


/**
  �ػ������Ӵ���. 
**/
static void wndCascadeInvalidateChildren (PCONTROL pCtrl, const RECT *prc, BOOL bEraseBkgnd)
{
	PMAINWIN pMainWin;
//	RECT	 rcTmp;
	
	pMainWin = (PMAINWIN)GetParent((HWND)pCtrl);
	
	while (!_Addresses_Equal(pCtrl, _Chain_Tail(&pMainWin->subWinList))) {

		if (!(pCtrl->dwStyle & WS_VISIBLE)) {
			 pCtrl = (PCONTROL)pCtrl->node.next;
			 continue;
		}
		if (bEraseBkgnd)
			SendMessage ((HWND)pCtrl, MSG_ERASEBKGND, 0, (LPARAM)prc);
		SendMessage ((HWND)pCtrl, MSG_PAINT, 0, (LPARAM)prc);
		//if (!_Chain_Is_empty(&pCtrl->subWinList))
		//	wndCascadeInvalidateChildren ((PCONTROL)pCtrl->subWinList.first, prc, bEraseBkgnd);

		pCtrl = (PCONTROL)pCtrl->node.next;
	}
}

/**
 \note  �ػ洰��; prc��ʾ��Ҫ�ػ�ľ���; bEraseBkgnd��ʾ�Ƿ���Ҫͬʱ�ػ汳��;
 \param,  prc ,���ػ�������ʱ,����ָ����Ҫ�ػ�Ŀؼ��ͻ���.
		ϵͳ��֧�����Կؼ���Ϊ������ͬʱ��ָ����Ҫ�ػ�ľ�����.������Ҫ�����ཻ
		�ľ���.�Ƚ��鷳.
**/
BOOL GUIAPI InvalidateRect (HWND hWnd, const RECT* prc, BOOL bEraseBkgnd)
{
	PMAINWIN pMainwin;
	
	pMainwin = (PMAINWIN)hWnd;

	if (!IsWindowVisible(hWnd))	 //������ʾ, �������˳�.
		return 0;
	
	if (bEraseBkgnd)
	{
		SendMessage (hWnd, MSG_ERASEBKGND, 0, (LPARAM)prc);
	}

	if (IsMainWindow(hWnd)	 /* ֪ͨ�����Ӵ����ػ汳��. */ 
		&& !_Chain_Is_empty(&pMainwin->subWinList)
		&& !prc)
		wndCascadeInvalidateChildren ((PCONTROL)pMainwin->subWinList.first, prc, bEraseBkgnd);	
	  
	SendMessage (hWnd, MSG_PAINT, 0, 0);
	
	return TRUE;
}

BOOL GUIAPI DestroyWindow (HWND hWnd)
{
	PCONTROL pCtrl;
	PCONTROL pParent;
	
	if (!IsControl (hWnd)) 
		return FALSE;
	
	if (SendMessage (hWnd, MSG_DESTROY, 0, 0))
		return FALSE;

	pCtrl = (PCONTROL)hWnd;
	pParent = pCtrl->pParent;
	if (pParent->active == (PCONTROL) hWnd)
		pParent->active = NULL;

	if (SendMessage (HWND_DESKTOP, MSG_REMOVECTRLINSTANCE,
					 (WPARAM)pParent,(LPARAM)pCtrl))
		return FALSE;


	// �ػ游�������ӿؼ�����ľ�����.
	pCtrl->dwStyle &= ~WS_VISIBLE;
	if (IsWindowVisible ((HWND) pParent))
		InvalidateRect ((HWND) pParent, (PRECT)(&pCtrl->left), TRUE);

	ThrowAwayMessages (hWnd);

	return TRUE;
}

BOOL GUIAPI DestroyMainWindow (HWND hWnd)
{
	PMAINWIN pWin;
//	PMAINWIN head, next;	// hosted window list.
	
	pWin = MainWindow(hWnd);
	if(!pWin) 
		return FALSE;

	if (SendMessage (hWnd, MSG_DESTROY, 0, 0))
		return FALSE;

	SendMessage(HWND_DESKTOP, MSG_REMOVEMAINWIN, (WPARAM)hWnd, 0);

	ThrowAwayMessages (hWnd);

	return TRUE;
}

/*************************** Main window creation ****************************/
void GUIAPI UpdateWindow (HWND hWnd, BOOL fErase)
{
	if (fErase) {  // Recalculate the client area.
		SendMessage (hWnd, MSG_CHANGESIZE, 0, 0);
		InvalidateRect (hWnd, NULL, fErase);
	}
	
	SendMessage (hWnd, MSG_NCPAINT, 0, 0);
	SendMessage (hWnd, MSG_PAINT, 0, 0);
}

// this function show window in behavious by specified iCmdShow.
// if the window was previously visible, the return value is nonzero.
// if the window was previously hiddedn, the return value is zero.
//
BOOL  GUIAPI  ShowWindow (HWND hWnd, int iCmdShow)
{
	PCONTROL  pControl;
	
	if (IsMainWindow (hWnd)) 
	{
		switch (iCmdShow)
		{	 
			case SW_SHOWNORMAL:
			case SW_SHOW:
				SendMessage (HWND_DESKTOP, MSG_SHOWMAINWIN, (WPARAM)hWnd, 0); 
				break;

			case SW_HIDE:
				SendMessage (HWND_DESKTOP, MSG_HIDEMAINWIN, (WPARAM)hWnd, 0);
				break;
		}
	} 
	else 
	{
		pControl = (PCONTROL)hWnd;
		
		switch (iCmdShow) 
		{
			case SW_SHOWNORMAL:
			case SW_SHOW:
				if (!(pControl->dwStyle & WS_VISIBLE)) 
				{
					pControl->dwStyle |= WS_VISIBLE;

					SendMessage (hWnd, MSG_NCPAINT, 0, 0);
					InvalidateRect(hWnd, NULL, TRUE);
				}
				break;
			
			case SW_HIDE:
				if (pControl->dwStyle & WS_VISIBLE)
				{
				
					pControl->dwStyle &= ~WS_VISIBLE;
					InvalidateRect((HWND)(pControl->pParent),
								   (RECT*)(&pControl->left), TRUE);
				}
				break;
		}

		if (iCmdShow == SW_HIDE && pControl->pParent->active == pControl)
		{
			// ������ص��ǽ���ؼ�,��Ҫ�л�.
			HWND  hWnd;
			
			hWnd = GetNextDlgTabItem((HWND)pControl->pParent, (HWND)pControl, TRUE);
			if (!_Addresses_Equal((void*)hWnd , pControl)) 
			{ 
				SetFocus(hWnd);
			} 
			else 
			{ 
				SendMessage (hWnd, MSG_KILLFOCUS, 0, 0);
				pControl->pParent->active = NULL;
			}
		}
	}

	SendMessage (hWnd, MSG_SHOWWINDOW, (WPARAM)iCmdShow, 0);
	
	return TRUE;
}

BOOL GUIAPI EnableWindow (HWND hWnd, BOOL fEnable)
{
	BOOL fOldStatus;
	
	if (IsMainWindow (hWnd)) {
		fOldStatus = SendMessage(HWND_DESKTOP, MSG_ENABLEMAINWIN,
								 (WPARAM)hWnd, (LPARAM)fEnable);
	} else {
		PCONTROL pControl;
		HWND	 parent;
		HWND	 hCtrl;

		pControl = (PCONTROL)hWnd;
		fOldStatus = !(pControl->dwStyle & WS_DISABLED);
		
		parent = GetParent(hWnd);
		if (hWnd == GetFocus(parent)) {
			hCtrl = GetNextDlgTabItem(parent, hWnd, 0);
			if (hCtrl && (! fEnable))
				SetFocus(hCtrl);
		}
	}
	SendMessage (hWnd, MSG_ENABLE, fEnable, 0);

	return fOldStatus;
}

BOOL GUIAPI IsWindowEnabled (HWND hWnd)
{
	PMAINWIN pWin = (PMAINWIN)hWnd;

	return ((pWin->dwStyle & WS_DISABLED) != WS_DISABLED);
}

/**
  �õ��߽�Ĵ�С�ߴ�.
**/
static int wndGetBorder (const MAINWIN* pWin)
{
	if (pWin->dwStyle & WS_BORDER) 
		return GetMainWinMetrics(MWM_BORDER);
	else if (pWin->dwStyle & WS_THICKFRAME)
		return GetMainWinMetrics(MWM_THICKFRAME);
	else if (pWin->dwStyle & WS_THINFRAME)
		return GetMainWinMetrics (MWM_THINFRAME);

	return 0;
}

/**
 **  this function is CONTROL safe.ע��, ����ǰҪ�ж�capiton�Ƿ�Ϊ0,Ϊ0�������.
 **  �����hdc��GetDC�õ���,Ҳ����˵, ���������ڵ�����.
 **
 **/
static void wndDrawCaption (const MAINWIN* pWin, HDC hdc, BOOL bFocus)
{
	RECT  rc;
	int   iBorder = 0;
	int   iCaption = 0;
	long  left, top;
	SIZE  size;
	CHAR *pCaption;

	PDC pdc = dc_HDC2PDC(hdc);

	bFocus = bFocus;

	if (!(pWin->dwStyle & WS_CAPTION))
		return;
		
	if (pWin->dwStyle & WS_BORDER) 
		iBorder = GetMainWinMetrics(MWM_BORDER);//The border's width, 1 pixel
		
	iCaption = GetMainWinMetrics(MWM_CAPTIONY); // The Caption's Height;

	// draw Caption
	rc.left   = iBorder;
	rc.top	= iBorder;
	rc.right  = pWin->right - pWin->left - iBorder;
	rc.bottom = iBorder + iCaption ; // + 1;
	
	//SetBrushColor (hdc, GetWindowElementColor (BKC_CAPTION_NORMAL));
	SetBrushColor (hdc, pWin->iBkColor);
	FillBox(hdc, iBorder, iBorder,
			pWin->right - pWin->left - iBorder,
			iCaption - 1);
			
	SetPenColor(hdc, PIXEL_black);
	Line(hdc, rc.left, (rc.top-1)+ GetMainWinMetrics(MWM_CAPTIONY) ,
			  rc.right, (rc.top-1) + GetMainWinMetrics(MWM_CAPTIONY)) ;
	SetPenColor(hdc, GetWindowElementColor(WEC_EXCOLOR_BLACK));
	Line(hdc, rc.right, (rc.top-1), rc.right, GetMainWinMetrics(MWM_CAPTIONY));
	SetTextColor(hdc, pWin->iBkColor^GetWindowElementColor (FGC_CAPTION_NORMAL));
	SetBkColor(hdc, pWin->iBkColor);
	//panhonghui
    if (MonitorConfig.language == RUSSIAN)
    {
         pdc->pLogFont = GetSystemFont(SYSLOGFONT_NOR_RUS);	

    }
    else
    {
        pdc->pLogFont = GetSystemFont(SYSLOGFONT_FIXED);

    }

	pCaption = LoadString(pWin->caption);
	GetTextExtent(hdc, pCaption, strlen(pCaption), &size);
	left = rc.left + (RECTW(rc) - size.cx) / 2;
	top  = rc.top  + (RECTH(rc) - size.cy) / 2;
	TextOut(hdc, left, top, pCaption);
}

static void wndEraseBackground(const MAINWIN* pWin, 
							   HDC hdc, const RECT* pClipRect)
{
	RECT rcTemp;
	BOOL fGetDC = FALSE;

	if (hdc == 0) {
		hdc = GetClientDC ((HWND)pWin);
		fGetDC = TRUE;
	}

	if (pClipRect) {
		rcTemp = *pClipRect;
		if (pWin->winType == TYPE_MAINWIN) {
		}
	}
	else {
		rcTemp.left   = rcTemp.top = 0;
		rcTemp.right  = pWin->cr - pWin->cl;
		rcTemp.bottom = pWin->cb - pWin->ct;
	}
	
	SetBrushColor(hdc, pWin->iBkColor);

	FillRect(hdc, rcTemp.left, rcTemp.top, RECTW (rcTemp), RECTH (rcTemp)); 

	if (fGetDC)
		ReleaseDC (hdc);
}

/**
 **  this function is CONTROL safe.
 **  this function is CONTROL safe.ע��, ����ǰҪ�ж�capiton�Ƿ�Ϊ0,Ϊ0�������.
 **  �����hdc��GetDC�õ���,Ҳ����˵, ���������ڵ�����.
 **
 **/
static void wndDrawNCArea (const MAINWIN* pWin, HDC hdc)
{
	if (pWin->dwStyle & WS_BORDER) 
	{
		SetPenColor(hdc, PIXEL_lightgray);
		//Rect(hdc, 0, 0, pWin->right - pWin->left - 1, pWin->bottom - pWin->top - 1);
		//modified by gjl 2013-4-7 17:52:51
		//SetPenColor(hdc, PIXEL_red);
		//INT32 iCaption = GetMainWinMetrics(MWM_CAPTIONY);
		Rect(hdc, 
			0, 0, 
			pWin->right - pWin->left - 1, pWin->bottom - pWin->top);
		Rect(hdc, 
			1, 1, 
			pWin->right - pWin->left, pWin->bottom - pWin->top);
	}
}


// this function is CONTROL safe.
static void wndDrawNCFrame(MAINWIN* pWin, HDC hdc, const RECT* prcInvalid)
{
	BOOL fGetDC = FALSE;
	
	prcInvalid = prcInvalid;
	
	if (hdc == 0) {
		hdc = GetDC ((HWND)pWin);
		fGetDC = TRUE;
	}
	
	wndDrawNCArea (pWin, hdc);

	if (pWin->winType == TYPE_MAINWIN && pWin->caption) 
	{
		wndDrawCaption (pWin, hdc,  
						!(pWin->dwStyle & WS_DISABLED) 
						&& (GetActiveWindow() == (HWND)pWin));
	}	
	if (fGetDC)
		ReleaseDC (hdc);
}


/* ��������������, �������ںͿͻ����Ĵ�С. */
static void OnChangeSize(PMAINWIN pWin, PRECT pDestRect, PRECT pResultRect)
{
	int iBorder   = 0;
	int iCaptionY = 0;

	iBorder = wndGetBorder (pWin);
	if (pWin->dwStyle & WS_CAPTION) {
		iCaptionY = GetMainWinMetrics(MWM_CAPTIONY);
	}
	
	if (pDestRect) {
		int minWidth = 0, minHeight = 0;
		
		memcpy(&pWin->left, pDestRect, sizeof(RECT));/* ���ָ�����ڴ�С,�������ô��ڴ�С */

		/* ����������ڴ�С. */
		minHeight = (iCaptionY<<1);

		if (pWin->winType == TYPE_MAINWIN)
			minWidth += GetMainWinMetrics (MWM_MINWIDTH);
			
		if (minHeight > (pWin->bottom - pWin->top))
			pWin->bottom = pWin->top + minHeight;

		if (pWin->right < (pWin->left + minWidth))
			pWin->right = pWin->left + minWidth;
			
		if (pResultRect)
			 memcpy(pResultRect, &pWin->left, sizeof(RECT));/* ���ش��ڴ�С. */
	}
	
	memcpy(&pWin->cl, &pWin->left, sizeof(RECT));/* �������ÿͻ����ʹ���ͬ����С. */

	/* ����߽�ͱ������ĳ߶�. */
	pWin->cl += iBorder;
	pWin->ct += iBorder;
	pWin->cr -= iBorder;
	pWin->cb -= iBorder;
	pWin->ct += iCaptionY;

}

/**
   \brief  ����ƶ��ؼ�.
   \note   �����߱�֤, pWin���Ӵ���.�����л����.
**/
static PCONTROL GetNextControl (PMAINWIN pWin)
{
	PCONTROL  pActive;
	PCONTROL  pNext;
	
	pActive = (PCONTROL) pWin->hActiveChild;
	pNext   = (PCONTROL)GetNextDlgTabItem((HWND)pWin, (HWND)pActive, FALSE);
	if (!_Addresses_Equal(pActive, pNext)) 
	{
		SetFocus((HWND)pNext);
	}
	return pNext;
}

/**
   \brief  ��ǰ�ƶ��ؼ�.
   \note   �����߱�֤, pWin���Ӵ���.�����л����.
**/
static PCONTROL GetPreviousControl (PMAINWIN pWin)
{
	PCONTROL  pActive;
	PCONTROL  pNext;
	
	pActive = (PCONTROL) pWin->hActiveChild;
	pNext   = (PCONTROL)GetNextDlgTabItem((HWND)pWin, (HWND)pActive, TRUE);
	if (!_Addresses_Equal(pActive, pNext)) 
	{
		SetFocus((HWND)pNext);
	}
	return pNext;
}

static INT32 DefaultKeyMsgHandler (PMAINWIN pWin, INT32 message, 
								   WPARAM wParam, LPARAM lParam)
{
// NOTE:
// Currently only handle one message.
// Should handle fowllowing messages:
//
// MSG_KEYDOWN,
// MSG_KEYUP,
// MSG_CHAR,
// MSG_SYSKEYDOWN,
// MSG_SYSCHAR.

	DWORD   status;
	
	if (message == MSG_KEYENCODER) {
		// ��������ڲ����������¼�, �򲻴�����Ϣ.
		if (pWin->hActiveChild && !(pWin->dwStyle & WS_DISABLED)) {
			//if (_menu_lev > 0) {
			{
				status = GetControlStatus((PCONTROL)pWin->hActiveChild);
				if (!(status & GEN_PRESSED)) {
					if ((long)wParam == KEY_KNOB_ROTATE_RIGHT) {
						GetNextControl(pWin);
						return 0;
					}

					if ((long)wParam == KEY_KNOB_ROTATE_LEFT) {
						GetPreviousControl(pWin);
						return 0;
					}
				}
			}

			/* ����Ǳ���������, ��Ϣֱ�Ӵ��ݸ�����ؼ�; ���ȼ�����״̬��,Ҳ�����. */
			{
				SendMessage (pWin->hActiveChild, message, wParam, lParam);
			}
		}
	}
#if _ENB_TOUCH
	else
	if (message == MSG_TOUCHENCODER)
	{
		// ��������ڲ����������¼�, �򲻴�����Ϣ
		if (pWin->hActiveChild && !(pWin->dwStyle & WS_DISABLED))
		{
			/* ����Ǳ���������, ��Ϣֱ�Ӵ��ݸ�����ؼ�; ���ȼ�����״̬��,Ҳ����� */
			SendMessage(pWin->hActiveChild, message, wParam, lParam);
		}
	}
#endif
	return 0;
}

static INT32 DefaultPostMsgHandler(PMAINWIN pWin, INT32 message,
								   WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		case MSG_SIZECHANGING:
			memcpy ((PRECT)lParam, (PRECT)wParam, sizeof (RECT));
			break;
			
		case MSG_CHANGESIZE:
			OnChangeSize(pWin, (PRECT)wParam, (PRECT)lParam);
			break;

		case MSG_SETFOCUS:
		case MSG_KILLFOCUS:
			if (pWin->hActiveChild)
			{
				SendMessage (pWin->hActiveChild, message, 0, 0);
			}
			break;
		
		default:
			break;
	}

	return 0;
}

static INT32 DefaultCreateMsgHandler (PMAINWIN pWin, INT32 message,
									 WPARAM wParam, LPARAM lParam)
{
// NOTE:
// Currently does nothing.
// Should handle fowllowing messages:
//
// MSG_NCCREATE,
// MSG_CREATE,
// MSG_INITPANES,
// MSG_DESTROYPANES,
// MSG_DESTROY,
// MSG_NCDESTROY.

	pWin	= pWin;
	message = message;
	wParam  = wParam;
	lParam  = lParam;

	return 0;

}
static INT32 DefaultPaintMsgHandler (PMAINWIN pWin, INT32 message,
									 WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		case MSG_NCPAINT:
			wndDrawNCFrame (pWin, (HDC)wParam, (const RECT*)lParam);
		break;

		case MSG_ERASEBKGND:
			wndEraseBackground (pWin, (HDC)wParam, (const RECT*)lParam);
			break;

		case MSG_PAINT:
			{
			}

			break;

	}

	return 0;
}

static INT32 DefaultControlMsgHandler(PMAINWIN pWin, INT32 message,
									  WPARAM wParam, LPARAM lParam)
{
	HDC   hdc;
//	long  len;
	char *pCaption;

	switch (message) {
		case MSG_ENABLE:
			if ((!(pWin->dwStyle & WS_DISABLED) && !wParam)
					|| ((pWin->dwStyle & WS_DISABLED) && wParam)) {
				if (wParam)
					pWin->dwStyle &= ~WS_DISABLED;
				else
					pWin->dwStyle |=  WS_DISABLED;
			}
			break;
		

		case MSG_GETTEXTLENGTH:
			if (pWin->caption) {
				pCaption = LoadString(pWin->caption);
				return strlen (pCaption);
			} else {
				return 0;
			}

		case MSG_GETTEXT:
			if (pWin->caption) {
				INT16* buffer = (INT16*)lParam;
				*buffer = pWin->caption;
				return strlen (LoadString(pWin->caption));
			}
			else
				return 0;

		case MSG_FONTCHANGED:
			UpdateWindow ((HWND)pWin, TRUE);
			break;

		case MSG_SETTEXT:
//
// NOTE:
// this message is only implemented for main window.
// for CONTROL, must handle this message and should NOT 
// call default window procedure
// when handle MSG_SETTEXT.
//
			if (pWin->winType == TYPE_CONTROL)
				return 0;

			pWin->caption = (STRINGID)lParam;

			if (pWin->caption) {
				hdc = GetDC ((HWND)pWin);
				wndDrawCaption(pWin, hdc, GetForegroundWindow () == (HWND)pWin);
				ReleaseDC (hdc);
			}
			break;
	}

	return 0;
}

static INT32 DefaultSystemMsgHandler (PMAINWIN pWin, INT32 message,
									  WPARAM wParam, LPARAM lParam)
{
// NOTE:
// Currently does nothing, should handle following messages:
//
// MSG_IDLE:
	pWin	= pWin;
	message = message;
	wParam  = wParam;
	lParam  = lParam;
	return 0;
}

/**
  ��ϵͳ��ʱû������豸;
  ͬʱ,Ҳû��PC����;ֻ�б�����; ���԰ѱ�����������ת��ΪPCɨ����,Ȼ���ٴ���.
**/
long DefaultMainWinProc (HWND hWnd, long message, WPARAM wParam, LPARAM lParam)
{
	PMAINWIN pWin = (PMAINWIN)hWnd;
	if (message >= MSG_FIRSTKEYMSG && message <= MSG_LASTKEYMSG)
		return  DefaultKeyMsgHandler(pWin, message, wParam, lParam);
	else if (message >= MSG_FIRSTPOSTMSG && message <= MSG_LASTPOSTMSG)
		return  DefaultPostMsgHandler(pWin, message, wParam, lParam);
	else if (message >= MSG_FIRSTCREATEMSG && message <= MSG_LASTCREATEMSG) 
		return  DefaultCreateMsgHandler(pWin, message, wParam, lParam);
	else if (message >= MSG_FIRSTPAINTMSG && message <= MSG_LASTPAINTMSG) 
		return  DefaultPaintMsgHandler(pWin, message, wParam, lParam);
	else if (message >= MSG_FIRSTCONTROLMSG && message <= MSG_LASTCONTROLMSG) 
		return  DefaultControlMsgHandler(pWin, message, wParam, lParam);
	else if (message >= MSG_FIRSTSYSTEMMSG && message <= MSG_LASTSYSTEMMSG) 
		return  DefaultSystemMsgHandler(pWin, message, wParam, lParam);

	return 0;
}

INT32 DefaultControlProc (HWND hWnd, INT32 message, WPARAM wParam, LPARAM lParam)
{
	if (message == MSG_SETTEXT)
		return 0;

	return DefaultMainWinProc (hWnd, message, wParam, lParam);
}

