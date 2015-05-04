#include "includes.h"
#include "keyboardDlg.h"
#if 1
enum keyboard_size{
	// 键盘设置
	DLG_KB_HIGH   = KEY_HEIGHT,
	DLG_KB_W	  = KEY_HEIGHT + 2,
	DLG_KB_OFFSET = DLG_KB_W + 10,
	DLG_KB_STATIC_OFFSET = (DLG_KB_HIGH - STATIC_HEIGHT + 1) / 2,
	// 其它设置
	DLG_KB_W_DB   = DLG_KB_W + DLG_KB_OFFSET,
	DLG_KB_W_SF   = DLG_KB_W * 6, // sixfold,for space
};

#define NUMPAD_CAPTION_MAXLEN ((DLG_KB_OFFSET *  4 - 10) / 8)
#define KEYBRD_CAPTION_MAXLEN ((DLG_KB_OFFSET * 10 - 10) / 8)
#define NUMPAD_VARIANT_MAXLEN 10
#define KB_IME_PY_CHARNUM	 (KEYBOARD_CN8 - KEYBOARD_CN1 + 1)

static KBCFG sKbConfig;
static RESID srCtrl_id[KEYBOARD_MAX] = {
	IDC_KBDLG_BOARDER_L,
	IDC_KBDLG_KB_PREVIOUS_B,	//  KEYBOARD_PREVIOUS,
	IDC_KBDLG_CN1_B,			//  KEYBOARD_CN1,
	IDC_KBDLG_CN2_B,			//  KEYBOARD_CN2,
	IDC_KBDLG_CN3_B,			//  KEYBOARD_CN3,
	IDC_KBDLG_CN4_B,			//  KEYBOARD_CN4,
	IDC_KBDLG_CN5_B,			//  KEYBOARD_CN5,
	IDC_KBDLG_CN6_B,			//  KEYBOARD_CN6,
	IDC_KBDLG_CN7_B,			//  KEYBOARD_CN7,
	IDC_KBDLG_CN8_B,			//  KEYBOARD_CN8,
	IDC_KBDLG_KB_NEXT_B,		//  KEYBOARD_NEXT,
	IDC_KBDLG_KB_Q_B,		   //  KEYBOARD_Q,
	IDC_KBDLG_KB_W_B,		   //  KEYBOARD_W,
	IDC_KBDLG_KB_E_B,		   //  KEYBOARD_E,
	IDC_KBDLG_KB_R_B,		   //  KEYBOARD_R,
	IDC_KBDLG_KB_T_B,		   //  KEYBOARD_T,
	IDC_KBDLG_KB_Y_B,		   //  KEYBOARD_Y,
	IDC_KBDLG_KB_U_B,		   //  KEYBOARD_U,
	IDC_KBDLG_KB_I_B,		   //  KEYBOARD_I,
	IDC_KBDLG_KB_O_B,		   //  KEYBOARD_O,
	IDC_KBDLG_KB_P_B,		   //  KEYBOARD_P,
	IDC_KBDLG_KB_A_B,		   //  KEYBOARD_A,
	IDC_KBDLG_KB_S_B,		   //  KEYBOARD_S,
	IDC_KBDLG_KB_D_B,		   //  KEYBOARD_D,
	IDC_KBDLG_KB_F_B,		   //  KEYBOARD_F,
	IDC_KBDLG_KB_G_B,		   //  KEYBOARD_G,
	IDC_KBDLG_KB_H_B,		   //  KEYBOARD_H,
	IDC_KBDLG_KB_J_B,		   //  KEYBOARD_J,
	IDC_KBDLG_KB_K_B,		   //  KEYBOARD_K,
	IDC_KBDLG_KB_L_B,		   //  KEYBOARD_L,
	IDC_KBDLG_KB_CAPS_B,		//  KEYBOARD_CAPS,
	IDC_KBDLG_KB_Z_B,		   //  KEYBOARD_Z,
	IDC_KBDLG_KB_X_B,		   //  KEYBOARD_X,
	IDC_KBDLG_KB_C_B,		   //  KEYBOARD_C,
	IDC_KBDLG_KB_V_B,		   //  KEYBOARD_V,
	IDC_KBDLG_KB_B_B,		   //  KEYBOARD_B,
	IDC_KBDLG_KB_N_B,		   //  KEYBOARD_N,
	IDC_KBDLG_KB_M_B,		   //  KEYBOARD_M,
	IDC_KBDLG_KB_DEL_B,		 //  KEYBOARD_DELETE,
	IDC_KBDLG_KB_NUM_MARKS_B,   //  KEYBOARD_NUM_MARKS,
	IDC_KBDLG_KB_IME_B,		 //  KEYBOARD_IME,
	IDC_KBDLG_KB_MARK_B,		//  KEYBOARD_MARK,
	IDC_KBDLG_KB_SPACE_B,	   //  KEYBOARD_SPACE,
	IDC_KBDLG_KB_MARK1_B,	   //  KEYBOARD_MARK1,
	IDC_KBDLG_KB_MARK2_B,	   //  KEYBOARD_MARK2,
	IDC_KBDLG_ENTER_B,		  //  KEYBOARD_ENTER,
};
static STRINGID ssCaption[KEYBOARD_MAX] = {
	STR_DLG_KB_INPUT,
	STR_DLG_KB_PY_PRE,
	STR_DLG_KB_PY_CHAR1,
	STR_DLG_KB_PY_CHAR2,
	STR_DLG_KB_PY_CHAR3,
	STR_DLG_KB_PY_CHAR4,
	STR_DLG_KB_PY_CHAR5,
	STR_DLG_KB_PY_CHAR6,
	STR_DLG_KB_PY_CHAR7,
	STR_DLG_KB_PY_CHAR8,
	STR_DLG_KB_PY_NEXT,
	STR_DLG_CHAR_Q,
	STR_DLG_CHAR_W,
	STR_DLG_CHAR_E,
	STR_DLG_CHAR_R,
	STR_DLG_CHAR_T,
	STR_DLG_CHAR_Y,
	STR_DLG_CHAR_U,
	STR_DLG_CHAR_I,
	STR_DLG_CHAR_O,
	STR_DLG_CHAR_P,
	STR_DLG_CHAR_A,
	STR_DLG_CHAR_S,
	STR_DLG_CHAR_D,
	STR_DLG_CHAR_F,
	STR_DLG_CHAR_G,
	STR_DLG_CHAR_H,
	STR_DLG_CHAR_J,
	STR_DLG_CHAR_K,
	STR_DLG_CHAR_L,
	STR_DLG_CHAR_CAPS,
	STR_DLG_CHAR_Z,
	STR_DLG_CHAR_X,
	STR_DLG_CHAR_C,
	STR_DLG_CHAR_V,
	STR_DLG_CHAR_B,
	STR_DLG_CHAR_N,
	STR_DLG_CHAR_M,
	STR_DLG_CHAR_DEL,
	STR_DLG_CHAR_NUM_MARK,
	STR_DLG_CHAR_IME,
	STR_DLG_CHAR_MARK,
	STR_DLG_CHAR_SPACE,
	STR_DLG_CHAR_COMMA,
	STR_DLG_CHAR_DOT,
	STR_DLG_CHAR_OK,	   
};

static POINT sDispPinyinPos;
static UCHAR kbswap[150];

static VOID SetPinyinPos(INT32 x, INT32 y)
{
	sDispPinyinPos.x = x;
	sDispPinyinPos.y = y;
}

static VOID ShowPinyin (HWND hWnd)
{
	HWND	hCtrl;
	HDC	 hdc = GetDC(hWnd);
	INT16   i;
	STRINGID strid;
	UCHAR   *outPtr;
	UCHAR   tmpTxt[3];
	GAL_PIXEL textcolor = SetTextColor(hdc, PIXEL_blue);
	GAL_PIXEL bkcolor = SetBkColor(hdc, 
		GetWindowElementColor (BKC_CONTROL_DEF));
	TextOut(hdc, sDispPinyinPos.x, sDispPinyinPos.y, "       ");
	TextOut(hdc, sDispPinyinPos.x, sDispPinyinPos.y, &(sKbConfig.szPinyin[0]));
	SetTextColor(hdc, textcolor);
	SetBkColor(hdc, bkcolor);
	ReleaseDC(hdc);
	outPtr = GetPyIndex(sKbConfig.szPinyin);
	if (sKbConfig.OutPtr != outPtr)
	{
		sKbConfig.OutPtr = outPtr;
		sKbConfig.CurrPtr = NULL;
	}
	if (sKbConfig.CurrPtr == NULL)
	{
		sKbConfig.CurrPtr   = sKbConfig.OutPtr;
	}
	//prinfo("CurrPtr...%p, OutPtr...%p\n", sKbConfig.CurrPtr, sKbConfig.OutPtr);
	outPtr = sKbConfig.CurrPtr;
	tmpTxt[2] = '\0';
	for (i = KEYBOARD_CN1; i <= KEYBOARD_CN8; i++)
	{
		hCtrl = GetDlgItem(hWnd, srCtrl_id[i]);
		strid = ssCaption[i];
		if (outPtr && strlen(outPtr) > 1)
		{
			strncpy(tmpTxt, outPtr, 2);
			outPtr += 2;
			strcpy(LoadString(ssCaption[i]), tmpTxt);
			EnableWindow(hCtrl, TRUE);
		}
		else
		{
			*LoadString(ssCaption[i]) = '\0';
			EnableWindow(hCtrl, FALSE);
		}
		SetWindowText(hCtrl, ssCaption[i]);
	}
	hCtrl = GetDlgItem(hWnd, srCtrl_id[KEYBOARD_PREVIOUS]);
	EnableWindow(hCtrl, (sKbConfig.CurrPtr != sKbConfig.OutPtr));
	hCtrl = GetDlgItem(hWnd, srCtrl_id[KEYBOARD_NEXT]);
	if (outPtr && strlen(outPtr) / 2 > 1)
	{
		EnableWindow(hCtrl, TRUE);
	}
	else
	{
		EnableWindow(hCtrl, FALSE);
	}
}

static VOID CleanKeyboard(long code)
{
	if (code == IDCANCEL)
	{
		memset(sKbConfig.variant.string, '\0', sKbConfig.variant.maxlen);
	}
}

static VOID sShowKbVariant(HWND hWnd)
{
	if (strlen(sKbConfig.variant.string) == 0)
	{
	    SetWindowTextColor(hWnd, PIXEL_darkgray);
		SetWindowText(hWnd, STR_DLG_KB_TIPS);
	}
	else
	{
	    SetWindowTextColor(hWnd, PIXEL_black);
		SetWindowText(hWnd, STR_DLG_KB_INPUT);
	}
}

static VOID sSetKbKeyStatus(HWND hDlg,KBTYPE type)
{
	int		 i;
	HWND		hCtrl;
	GAL_PIXEL   setcolor = PIXEL_red;
	GAL_PIXEL   defcolor = PIXEL_black;
	if (type & KEYBOARD_MARKS)
	{
			hCtrl = GetDlgItem(hDlg, srCtrl_id[KEYBOARD_MARK]);
			SetWindowTextColor(hCtrl, setcolor);
			hCtrl = GetDlgItem(hDlg, srCtrl_id[KEYBOARD_CAPS]);
			SetWindowTextColor(hCtrl, defcolor);
			hCtrl = GetDlgItem(hDlg, srCtrl_id[KEYBOARD_NUM_MARKS]);
			SetWindowTextColor(hCtrl, defcolor);
			return;
	}

	if (type & KEYBOARD_NUMMARKS)
	{
			hCtrl = GetDlgItem(hDlg, srCtrl_id[KEYBOARD_NUM_MARKS]);
			SetWindowTextColor(hCtrl, setcolor);
			hCtrl = GetDlgItem(hDlg, srCtrl_id[KEYBOARD_CAPS]);
			SetWindowTextColor(hCtrl, defcolor);
			hCtrl = GetDlgItem(hDlg, srCtrl_id[KEYBOARD_MARK]);
			SetWindowTextColor(hCtrl, defcolor);
			return;
	}

	if (type & KEYBOARD_UPPERCS)
	{
		hCtrl = GetDlgItem(hDlg, srCtrl_id[KEYBOARD_CAPS]);
		SetWindowTextColor(hCtrl, setcolor);
		hCtrl = GetDlgItem(hDlg, srCtrl_id[KEYBOARD_NUM_MARKS]);
		SetWindowTextColor(hCtrl, defcolor);
		hCtrl = GetDlgItem(hDlg, srCtrl_id[KEYBOARD_MARK]);
		SetWindowTextColor(hCtrl, defcolor);
		return;
	}

	hCtrl = GetDlgItem(hDlg, srCtrl_id[KEYBOARD_CAPS]);
	SetWindowTextColor(hCtrl, defcolor);
	hCtrl = GetDlgItem(hDlg, srCtrl_id[KEYBOARD_NUM_MARKS]);
	SetWindowTextColor(hCtrl, defcolor);
	hCtrl = GetDlgItem(hDlg, srCtrl_id[KEYBOARD_MARK]);
	SetWindowTextColor(hCtrl, defcolor);
	if (CHINESE != MonitorConfig.language)
	{
		hCtrl = GetDlgItem(hDlg, srCtrl_id[KEYBOARD_IME]);
		EnableWindow(hCtrl, FALSE);
	}
	return;
}

static UINT8 sGetKbStatus(KBTYPE type)
{
	if (type & (~KEYBOARD_MASK))
	{
		if (type & KEYBOARD_MARKS)
			return KEYBOARD_MARKS;

		if (type & KEYBOARD_NUMMARKS)
			return KEYBOARD_NUMMARKS;

		if (type & KEYBOARD_UPPERCS)
			return KEYBOARD_UPPERCS;

		if (type & KEYBOARD_LOWERCS)
			return KEYBOARD_LOWERCS;
	}
	return type;
}

/*******************************************************************************
函数名称:sReinitKbKey
生成日期:2013-5-6
功能说明:重新初始化键盘按键
输入参数:type:键盘类型
函数返回:无
*******************************************************************************/
static BOOL sReinitKbKey(HWND hDlg,UINT8 type)
{
	int	 i;
	HWND	hCtrl;
	sSetKbKeyStatus(hDlg, sGetKbStatus(type));
	if (type & KEYBOARD_MARKS)
	{
		hCtrl = GetDlgItem(hDlg, srCtrl_id[KEYBOARD_MARK]);
		EnableWindow(hCtrl, FALSE);
		return FALSE;
		const char kbChar[][8] = 
			{ " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
			"~" , "`" , "^" , "\"" , "<" , ">" , "{" , "}" , "[" , "]" ,
			 "|", "+", "=", "\13", "\14", "\361", "\366", "\370", "#" ,
			"\30", "'" , "/" , "-" , "_" , ":" , ";" , "?" , "<-" ,
			"12,", "中", "\1", "Space", ",", ".", "Enter"};
		for (i = KEYBOARD_PREVIOUS; i <= KEYBOARD_NEXT; i++ )
		{
			hCtrl = GetDlgItem(hDlg, srCtrl_id[i]);
			EnableWindow(hCtrl, FALSE);
		}
		for (i = KEYBOARD_PREVIOUS; i < KEYBOARD_MAX; i++)
		{
			strcpy(LoadString(ssCaption[i]), kbChar[i-1]);
			hCtrl = GetDlgItem(hDlg, srCtrl_id[i]);
			SetWindowText(hCtrl, ssCaption[i]);
		}
		return TRUE;
	}

	if (type & KEYBOARD_NUMMARKS)
	{
		char kbChar[][8] = 
			{ " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
			"1" , "2" , "3" , "4" , "5" , "6" , "7" , "8" , "9" , "0" ,
				"!" , "@" , "#" , "$" , "%" , "&" , "*" , "(" , ")" ,
			"\30", "'" , "/" , "-" , "_" , ":" , ";" , "?" , "<-" ,
			"12,", "中", "\1", "Space", ",", ".", "Enter"};
		if (CHINESE != MonitorConfig.language)
		{
			strcpy(kbChar[KEYBOARD_IME - 1], "abc");
		}
		for (i = KEYBOARD_PREVIOUS; i <= KEYBOARD_NEXT; i++ )
		{
			hCtrl = GetDlgItem(hDlg, srCtrl_id[i]);
			EnableWindow(hCtrl, FALSE);
		}
		for (i = KEYBOARD_PREVIOUS; i < KEYBOARD_MAX; i++)
		{
			strcpy(LoadString(ssCaption[i]), kbChar[i-1]);
			hCtrl = GetDlgItem(hDlg, srCtrl_id[i]);
			SetWindowText(hCtrl, ssCaption[i]);
		}
		return TRUE;
	}

	if (type & KEYBOARD_UPPERCS)
	{
		const char kbChar[][8] = 
			{ " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
			"Q" , "W" , "E" , "R" , "T" , "Y" , "U" , "I" , "O" , "P" ,
				"A" , "S" , "D" , "F" , "G" , "H" , "J" , "K" , "L" ,
			"\30", "Z" , "X" , "C" , "V" , "B" , "N" , "M" , "<-" ,
			"12,", "ABC", "\1", "Space", ",", ".", "Enter"};
		for (i = KEYBOARD_PREVIOUS; i <= KEYBOARD_NEXT; i++ )
		{
			hCtrl = GetDlgItem(hDlg, srCtrl_id[i]);
			EnableWindow(hCtrl, FALSE);
		}
		for (i = KEYBOARD_PREVIOUS; i < KEYBOARD_MAX; i++)
		{
			strcpy(LoadString(ssCaption[i]), kbChar[i-1]);
			hCtrl = GetDlgItem(hDlg, srCtrl_id[i]);
			SetWindowText(hCtrl, ssCaption[i]);
		}
		return TRUE;
	}

	if (type & KEYBOARD_LOWERCS)
	{
		const char kbChar[][8] = 
		  { " ", " ", " ", " ", " ", " ", " ", " ", " ", " ",
			"q" , "w" , "e" , "r" , "t" , "y" , "u" , "i" , "o" , "p" ,
				"a" , "s" , "d" , "f" , "g" , "h" , "j" , "k" , "l" ,
			"\30", "z" , "x" , "c" , "v" , "b" , "n" , "m" , "<-" ,
			"12,", "abc", "\1", "Space", ",", ".", "Enter"};
		for (i = KEYBOARD_PREVIOUS; i <= KEYBOARD_NEXT; i++ )
		{
			hCtrl = GetDlgItem(hDlg, srCtrl_id[i]);
			EnableWindow(hCtrl, FALSE);
		}
		for (i = KEYBOARD_PREVIOUS; i < KEYBOARD_MAX; i++)
		{
			strcpy(LoadString(ssCaption[i]), kbChar[i-1]);
			hCtrl = GetDlgItem(hDlg, srCtrl_id[i]);
			SetWindowText(hCtrl, ssCaption[i]);
		}
		return TRUE;
	}

	if ((type & KEYBOARD_MASK) == KEYBOARD_CHINESE)
	{
		const char kbChar[][8] = 
		  { "<<", " ", " ", " ", " ", " ", " ", " ", " ", ">>",
			"q" , "w" , "e" , "r" , "t" , "y" , "u" , "i" , "o" , "p" ,
				"a" , "s" , "d" , "f" , "g" , "h" , "j" , "k" , "l" ,
			"\30", "z" , "x" , "c" , "v" , "b" , "n" , "m" , "<-" ,
			"12,", "中", "\1", "Space", ",", ".", "Enter"};
		for (i = KEYBOARD_PREVIOUS; i < KEYBOARD_Q; i++ )
		{
			hCtrl = GetDlgItem(hDlg, srCtrl_id[i]);
			EnableWindow(hCtrl, FALSE);
		}
		for (i = KEYBOARD_Q; i < KEYBOARD_MAX; i++ )
		{
			hCtrl = GetDlgItem(hDlg, srCtrl_id[i]);
			EnableWindow(hCtrl, TRUE);
		}
		for (i = KEYBOARD_PREVIOUS; i < KEYBOARD_MAX; i++)
		{
			strcpy(LoadString(ssCaption[i]), kbChar[i-1]);
			hCtrl = GetDlgItem(hDlg, srCtrl_id[i]);
			SetWindowText(hCtrl, ssCaption[i]);
		}
		return TRUE;
	}
	return FALSE;
}

static VOID InitKeyboardInfo(VOID)
{
	if (NULL != sKbConfig.caption)
	{
		UCHAR *ptxt;
		UCHAR szCaption[NUMPAD_CAPTION_MAXLEN + 1];
		ptxt = LoadString(STR_DLG_KB_CAPTION);
		if (sKbConfig.caption != ptxt)
		{
			memset(ptxt, '\0', NUMPAD_CAPTION_MAXLEN + 1);
			memset(szCaption, '\0', NUMPAD_CAPTION_MAXLEN + 1);
			ptxt = sKbConfig.caption;
			if (strlen(ptxt) > NUMPAD_CAPTION_MAXLEN)
			{
				strncpy(szCaption, ptxt, NUMPAD_CAPTION_MAXLEN - 2);
				strcat(szCaption, "..");
			}
			else
			{
				strncpy(szCaption, ptxt, NUMPAD_CAPTION_MAXLEN);
			}
			strcpy(LoadString(STR_DLG_KB_CAPTION), szCaption);
		}
	}
	strcpy(LoadString(STR_DLG_KB_TIPS), sKbConfig.tips);
}

static BOOL NumPadOnCommand(HANDLE hWnd, DWORD wParam, LPARAM lParam)
{
	BOOL ret = TRUE;
	char *pVar = sKbConfig.variant.string;
	char szKey[2];
	szKey[1] = '\0';
	switch(LOWORD(wParam))
	{
		case IDC_NUMPAD_ESC:
			CleanKeyboard(IDCANCEL);
			EndDialog(hWnd, IDOK);
			break;

		case IDC_NUMPAD_ENTER:
			CleanKeyboard(IDOK);
			EndDialog(hWnd, IDOK);
			break;

		case IDC_NUMPAD_DOT:
			if (sKbConfig.kbType >= KEYBOARD_UNS_DEC 
				&& sKbConfig.kbType <= KEYBOARD_DECIMAL)
			{
				if (!strchr(pVar, '.'))
				{
					if (strlen(pVar) < NUMPAD_VARIANT_MAXLEN - 1)
					{
						szKey[0] = '.';
						strcat(pVar, szKey);
					}
				}
			}
			break;

		case IDC_NUMPAD_DEL:
			{
				INT32 len = strlen(pVar);
				if (len > 0)
				{
					memset(pVar, '\0', 100);
					//*(pVar + len - 1) = '\0';
				}
			}
			break;

		case IDC_NUMPAD_MINUS:
			{
				memset(kbswap, '\0', sizeof(kbswap));
				if (*pVar == '-')
				{
					strcpy(kbswap, pVar + 1);
					strcpy(pVar, kbswap);
				}
				else if ((sKbConfig.kbType != KEYBOARD_UNS_INT) 
						&& (sKbConfig.kbType != KEYBOARD_UNS_DEC))
				{
					strcpy(kbswap, pVar);
					*pVar = '-';
					strcpy(pVar + 1, kbswap);
				}
			}
			break;

		case IDC_NUMPAD_0:
		case IDC_NUMPAD_1:
		case IDC_NUMPAD_2:
		case IDC_NUMPAD_3:
		case IDC_NUMPAD_4:
		case IDC_NUMPAD_5:
		case IDC_NUMPAD_6:
		case IDC_NUMPAD_7:
		case IDC_NUMPAD_8:
		case IDC_NUMPAD_9:
			if(strlen(pVar) < NUMPAD_VARIANT_MAXLEN - 1)
			{
				szKey[0] = LOBYTE(LOWORD(wParam) - IDC_NUMPAD_0 + '0');
				strcat(pVar, szKey);
			}
			//prinfo("pVar...%s\r\n", pVar);
			break;

		default:
			ret = FALSE;
			break;		
	}
	if (ret)
	{
		HWND hCtrl = GetDlgItem(hWnd, IDC_NUMPAD_NUM_L);
		if (!hCtrl)
		{
			return FALSE;
		}
		strcpy(LoadString(STR_DLG_KB_INPUT), pVar);
		sShowKbVariant(hCtrl);
		/*/
		if (strlen(pVar) > 0)
		{
			strcpy(LoadString(STR_DLG_KB_INPUT), pVar);
			SetWindowText(hCtrl, STR_DLG_KB_INPUT);
		}
		else
		{
			SetWindowText(hCtrl, STR_DLG_KB_TIPS);
		}
		/*/
	}
	return ret;
}
static VOID NumPadInit(HANDLE hWnd, DWORD wParam, LPARAM lParam)
{
	int i;
	HWND hCtrl;
	PCONTROL pCtrl;
	pCtrl = (PCONTROL)hWnd;
	for (i = IDC_NUMPAD_NUM_L; i <= IDC_NUMPAD_ENTER; i++)
	{
		hCtrl = GetDlgItem(hWnd, i);
		if (hCtrl == 0)
			continue;
		SetWindowBkColor(hCtrl, pCtrl->iBkColor);
	}
	InitKeyboardInfo();
}

INT32  NumPadProc(HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	switch (message) {
		case MSG_INITDIALOG:
			NumPadInit(hWnd, wParam, lParam);
			return 0;
			
		case MSG_COMMAND:
			if (NumPadOnCommand(hWnd, wParam, lParam))
				return 0;
			break;
			
		default:
			break;
	}
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}

static INLINE VOID DeleteKbOutPutCharacter(VOID)
{
	INT32	 len;
	len = strlen(sKbConfig.variant.string);
	if (len-- > 0)
	{
		StrBuffer tmp_str;
		tmp_str.string = NULL;
		if (!NewStrBuffer(&tmp_str, sKbConfig.variant.maxlen))
		{
			return;
		}
		strcpy(tmp_str.string, sKbConfig.variant.string);
		memset(sKbConfig.variant.string, '\0', sKbConfig.variant.maxlen);
		if (len > 0)
		{
			if (IS_GB(*(tmp_str.string + len - 1), *(tmp_str.string + len)))
			{
				len--;
			}
			if (len > 0)
			{
				strncpy(sKbConfig.variant.string, tmp_str.string, len);
			}
		}
		TextDel(tmp_str.string);
		tmp_str.string = NULL;
	}
}

static INLINE VOID sPinyinCharacterOut(INT8 index, UINT32 limit)
{
	UCHAR   *key = LoadString(ssCaption[KEYBOARD_CN1 + index]);
	memset(sKbConfig.szPinyin, '\0', sizeof(sKbConfig.szPinyin));
	if (strlen(key) > 1)
	{
		if (strlen(sKbConfig.variant.string) + strlen(key) < limit)
		{
			strcat(sKbConfig.variant.string, key);
		}
	}
}

static INLINE VOID sPinyinCodeOut(UINT32 limit)
{
	UCHAR tmpTxt[8];
	UINT32 offlen;
	UINT32 pyLen = strlen(sKbConfig.szPinyin);
	strcpy(tmpTxt, sKbConfig.szPinyin);
	memset(sKbConfig.szPinyin, '\0', sizeof(sKbConfig.szPinyin));
	offlen = limit - strlen(sKbConfig.variant.string);
	if (offlen < pyLen)
	{
		tmpTxt[offlen] = '\0';
	}
	strcat(sKbConfig.variant.string, tmpTxt);
}

static VOID DealWithPinyin(HANDLE hWnd, RESID ctrl_id)
{
	HWND	 hCtrl = GetDlgItem(hWnd, ctrl_id);
	PCONTROL pCtrl = (PCONTROL)hCtrl;
	UINT32   hardlimit = sKbConfig.variant.maxlen - 1;
	UINT32   pyLen = strlen(sKbConfig.szPinyin);

	if (ctrl_id >= srCtrl_id[KEYBOARD_A] && ctrl_id <= srCtrl_id[KEYBOARD_Z])
	{
		UCHAR   *key = LoadString(pCtrl->caption);
		if (pyLen + 1 < sizeof(sKbConfig.szPinyin) - 1)
		{
			strcat(sKbConfig.szPinyin, key);
		}
	}

	if (ctrl_id == srCtrl_id[KEYBOARD_SPACE])
	{
		if (pyLen > 0)
		{
			sPinyinCharacterOut(0, hardlimit);
		}
		else if (strlen(sKbConfig.variant.string) + 1 < hardlimit)
		{
			strcat(sKbConfig.variant.string, " ");
		}
	}

	if ((ctrl_id == srCtrl_id[KEYBOARD_MARK1]) || (ctrl_id == srCtrl_id[KEYBOARD_MARK2]))
	{
		if (pyLen > 0)
		{
			sPinyinCharacterOut(0, hardlimit);
		}
		if (strlen(sKbConfig.variant.string) + 1 < hardlimit)
		{
			strcat(sKbConfig.variant.string, LoadString(pCtrl->caption));
		}
	}

	if (ctrl_id == srCtrl_id[KEYBOARD_DELETE])
	{
		if (pyLen > 0)
		{
			sKbConfig.szPinyin[pyLen - 1] = '\0';
		}
		else
		{
			DeleteKbOutPutCharacter();
		}
	}

	if (ctrl_id == srCtrl_id[KEYBOARD_ENTER])
	{
		if (pyLen > 0)
		{
			sPinyinCodeOut(hardlimit);
		}
		else
		{
			EndDialog(hWnd, IDOK);
		}
	}

	if (ctrl_id == srCtrl_id[KEYBOARD_PREVIOUS])
	{
		sKbConfig.CurrPtr -= KB_IME_PY_CHARNUM * 2;
		if (sKbConfig.CurrPtr < sKbConfig.OutPtr)
		{
			sKbConfig.CurrPtr = sKbConfig.OutPtr;
		}
	}

	if (ctrl_id == srCtrl_id[KEYBOARD_NEXT])
	{
		if (strlen(sKbConfig.CurrPtr) > KB_IME_PY_CHARNUM * 2)
		{
			sKbConfig.CurrPtr += KB_IME_PY_CHARNUM * 2;
		}
	}

	if (ctrl_id >= srCtrl_id[KEYBOARD_CN1] && ctrl_id <= srCtrl_id[KEYBOARD_CN8])
	{
		sPinyinCharacterOut(ctrl_id - srCtrl_id[KEYBOARD_CN1], hardlimit);
	}
	ShowPinyin(hWnd);
}

static BOOL OnIMEKey(HANDLE hWnd, RESID ctrl_id)
{
	if (sKbConfig.kbType == KEYBOARD_CHINESE)
	{
		DealWithPinyin(hWnd, ctrl_id);
		return TRUE;
	}
}

static BOOL OnClickOtherKey(HANDLE hWnd, RESID ctrl_id, UINT8 status)
{
	if (status > KEYBOARD_MASK)// 如果是键盘，直接显示字符
	{
		HWND	 hCtrl = GetDlgItem(hWnd, ctrl_id);
		PCONTROL pCtrl = (PCONTROL)hCtrl;
		UINT32   hardlimit = sKbConfig.variant.maxlen - 1;
		if ((ctrl_id >= srCtrl_id[KEYBOARD_A] 
				&& ctrl_id <= srCtrl_id[KEYBOARD_Z])
			|| ctrl_id == srCtrl_id[KEYBOARD_MARK1]
			|| ctrl_id == srCtrl_id[KEYBOARD_MARK2])
		{
			UCHAR   *key = LoadString(pCtrl->caption);
			if (strlen(sKbConfig.variant.string) + strlen(key) < hardlimit)
			{
				strcat(sKbConfig.variant.string, key);
			}
		}
		if (ctrl_id == srCtrl_id[KEYBOARD_SPACE])
		{
			if (strlen(sKbConfig.variant.string) + 1 < hardlimit)
			{
				strcat(sKbConfig.variant.string, " ");
			}
		}
		if (ctrl_id == srCtrl_id[KEYBOARD_DELETE])
		{
			DeleteKbOutPutCharacter();
		}
		if (ctrl_id == srCtrl_id[KEYBOARD_ENTER])
		{
			EndDialog(hWnd, IDOK);
		}
	}
	else // 开启了输入法
	{
		OnIMEKey(hWnd, ctrl_id);
	}
	strcpy(LoadString(ssCaption[KEYBOARD_FIRST]), sKbConfig.variant.string);
	return TRUE;
}

static BOOL StringKbOnCommand(HANDLE hWnd, DWORD wParam, LPARAM lParam)
{
	BOOL ret = TRUE;
	UINT8 KbStatus = sGetKbStatus(sKbConfig.kbType);
	switch (LOWORD(wParam))
	{
		case IDC_KBDLG_KB_CAPS_B:
			if (KbStatus == KEYBOARD_UPPERCS)
			{
				sKbConfig.kbType &= (~KEYBOARD_UPPERCS);
			}
			else
			{
				sKbConfig.kbType |= KEYBOARD_UPPERCS;
			}
			sReinitKbKey(hWnd, sKbConfig.kbType);
			break;

		case IDC_KBDLG_KB_NUM_MARKS_B:
			if (KbStatus == KEYBOARD_NUMMARKS)
			{
				sKbConfig.kbType &= (~KEYBOARD_NUMMARKS);
			}
			else
			{
				sKbConfig.kbType |= KEYBOARD_NUMMARKS;
			}
			sReinitKbKey(hWnd, sKbConfig.kbType);
			break;

		case IDC_KBDLG_KB_IME_B:
			if (KbStatus == KEYBOARD_LOWERCS)
			{
				sKbConfig.kbType &= KEYBOARD_MASK;
			}
			else
			{
				sKbConfig.kbType &= KEYBOARD_MASK;
				sKbConfig.kbType |= KEYBOARD_LOWERCS;
			}
			sReinitKbKey(hWnd, sKbConfig.kbType);
			break;

		case IDC_KBDLG_KB_MARK_B:
			if (KbStatus == KEYBOARD_MARKS)
			{
				sKbConfig.kbType &= (~KEYBOARD_MARKS);
			}
			else
			{
				sKbConfig.kbType |= KEYBOARD_MARKS;
			}
			sReinitKbKey(hWnd, sKbConfig.kbType);
			break;

		default:
			ret = OnClickOtherKey(hWnd, LOWORD(wParam), KbStatus);
			break;
	}
	HWND hCtrl;
	if (0 != (hCtrl = GetDlgItem(hWnd, srCtrl_id[KEYBOARD_FIRST])))
	{
		sShowKbVariant(hCtrl);
	}
	return ret;
}

static VOID StringKeyboardInit(HANDLE hWnd, DWORD wParam, LPARAM lParam)
{
	HWND hCtrl;
	if (KEYBOARD_CHINESE !=(sKbConfig.kbType & KEYBOARD_MASK))
	{
		sKbConfig.kbType |= KEYBOARD_CHINESE;
	}
	sReinitKbKey(hWnd, sKbConfig.kbType);
	memset(sKbConfig.szPinyin, '\0', sizeof(sKbConfig.szPinyin));
	hCtrl = GetDlgItem(hWnd, srCtrl_id[KEYBOARD_FIRST]);
	SetWindowBkColor(hCtrl, PIXEL_white);
	InitKeyboardInfo();
	ShowPinyin(hWnd);
	hCtrl = GetDlgItem(hWnd, srCtrl_id[KEYBOARD_MARK]);
	EnableWindow(hCtrl, FALSE);
	hCtrl = GetDlgItem(hWnd, srCtrl_id[KEYBOARD_IME]);
	EnableWindow(hCtrl, (CHINESE == MonitorConfig.language));
}

INT32 StringKeyboardProc(HANDLE hWnd, INT32 message, DWORD wParam, LPARAM lParam)
{
	switch (message) {
		case MSG_INITDIALOG:
			StringKeyboardInit(hWnd, wParam, lParam);
			return 0;
			
		case MSG_COMMAND:
			if (StringKbOnCommand(hWnd, wParam, lParam))
				return 0;
			break;
			
		default:
			break;
	}
	return DefaultDialogProc (hWnd, message, wParam, lParam);
}


static INT32 *integerKeyboard(HWND hWnd, RESID child, INT32 *value)
{
	enum dlg_size{
		KEY_OFFSET  = DLG_KB_OFFSET,
		KEY_LEFT	= DLG_OFFSET,
		KEY_HIGH	= KEY_HEIGHT,
		KEY_WIDTH   = DLG_KB_W,
		KEY_DB_W	= DLG_KB_W + KEY_OFFSET,
		KEY_ROW1	= DLG_OFFSET,
		KEY_ROW2	= KEY_ROW1 + KEY_OFFSET,
		KEY_ROW3	= KEY_ROW2 + KEY_OFFSET,
		KEY_ROW4	= KEY_ROW3 + KEY_OFFSET,
		KEY_ROW5	= KEY_ROW4 + KEY_OFFSET,
		KEY_COLUMN1 = DLG_OFFSET,
		KEY_COLUMN2 = KEY_COLUMN1 + KEY_OFFSET,
		KEY_COLUMN3 = KEY_COLUMN2 + KEY_OFFSET,
		KEY_COLUMN4 = KEY_COLUMN3 + KEY_OFFSET,
		KEY_DLG_W   = KEY_COLUMN4 + KEY_WIDTH + DLG_OFFSET,
		KEY_DLG_H   = KEY_ROW5 + KEY_HIGH + DLG_MENU_HIGHT + DLG_OFFSET,
	};
	POINT	   ctrl_pos[NUMPAD_MAX] = {
		{ KEY_COLUMN1, KEY_ROW1 },			  // IDC_NUMPAD_NUM_L
		{ KEY_COLUMN1, KEY_ROW2 },			  // IDC_NUMPAD_7
			{ KEY_COLUMN2, KEY_ROW2 },		  // IDC_NUMPAD_8
				{ KEY_COLUMN3, KEY_ROW2 },	  // IDC_NUMPAD_9
					{ KEY_COLUMN4, KEY_ROW2 },  // IDC_NUMPAD_ESC
		{ KEY_COLUMN1, KEY_ROW3 },			  // IDC_NUMPAD_4
			{ KEY_COLUMN2, KEY_ROW3 },		  // IDC_NUMPAD_5
				{ KEY_COLUMN3, KEY_ROW3 },	  // IDC_NUMPAD_6
					{ KEY_COLUMN4, KEY_ROW3 },  // IDC_NUMPAD_DEL
		{ KEY_COLUMN1, KEY_ROW4 },			  // IDC_NUMPAD_1
			{ KEY_COLUMN2, KEY_ROW4 },		  // IDC_NUMPAD_2
				{ KEY_COLUMN3, KEY_ROW4 },	  // IDC_NUMPAD_3
					{ KEY_COLUMN4, KEY_ROW4 },  // IDC_NUMPAD_MINUS
//	  { KEY_COLUMN1, KEY_ROW5 },			  // IDC_NUMPAD_DOT
			{ KEY_COLUMN2, KEY_ROW5 },		  // IDC_NUMPAD_0
				{ KEY_COLUMN3, KEY_ROW5 }	   // IDC_NUMPAD_ENTER
	};
	RESID	   ctrl_id[NUMPAD_MAX] = {
		IDC_NUMPAD_NUM_L,
		IDC_NUMPAD_7,
		IDC_NUMPAD_8,
		IDC_NUMPAD_9,
		IDC_NUMPAD_ESC,
		IDC_NUMPAD_4,
		IDC_NUMPAD_5,
		IDC_NUMPAD_6,
		IDC_NUMPAD_DEL,
		IDC_NUMPAD_1,
		IDC_NUMPAD_2,
		IDC_NUMPAD_3,
		IDC_NUMPAD_MINUS,
//	  IDC_NUMPAD_DOT,
		IDC_NUMPAD_0,
		IDC_NUMPAD_ENTER
	};
	STRINGID	caption[NUMPAD_MAX] = {
		STR_DLG_KB_INPUT,
		STR_DLG_CHAR_7,
		STR_DLG_CHAR_8,
		STR_DLG_CHAR_9,
		STR_DLG_CHAR_ESC,
		STR_DLG_CHAR_4,
		STR_DLG_CHAR_5,
		STR_DLG_CHAR_6,
		STR_DLG_CHAR_DEL,
		STR_DLG_CHAR_1,
		STR_DLG_CHAR_2,
		STR_DLG_CHAR_3,
		STR_DLG_CHAR_MINUS,
//	  STR_DLG_CHAR_DOT,
		STR_DLG_CHAR_0,
		STR_DLG_CHAR_OK
	};
	DLGTEMPLATE dlg_data = {
		WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
		0, 0, KEY_DLG_W, KEY_DLG_H,  STR_DLG_KB_CAPTION, 0, NULL, 0L,
	};
	CTRLDATA	ctrl_data[NUMPAD_MAX] = {0};
	BUTTONDATA  btn[NUMPAD_MAX - 1] = {0};
	SIZE		ctrl_size[NUMPAD_MAX];
	INT16	   i;
	INT16	   loops;
	WNDMEM	  wndMem;
	
	ctrl_size[0].cx = KEY_DLG_W - DLG_OFFSET * 2;
	ctrl_size[0].cy = STATIC_HEIGHT;
	loops = TABLESIZE(ctrl_size);
	for (i = 1; i < loops; i++)
	{
		ctrl_size[i].cx = KEY_WIDTH;
		ctrl_size[i].cy = KEY_HIGH;
	}
	ctrl_size[i - 1].cx = KEY_DB_W;
	ctrl_data[0].class_name = CTRL_STATIC;
	ctrl_data[0].dwStyle = WS_VISIBLE | SS_SIMPLE;
	for (i = 0; i < loops; i++)
	{
		ctrl_data[i].x = ctrl_pos[i].x;
		ctrl_data[i].y = ctrl_pos[i].y;
		ctrl_data[i].w = ctrl_size[i].cx;
		ctrl_data[i].h = ctrl_size[i].cy;
		ctrl_data[i].id = ctrl_id[i];
		ctrl_data[i].caption = caption[i];
		if (i != 0)
		{
			ctrl_data[i].class_name = CTRL_BUTTON;
			ctrl_data[i].dwStyle = WS_VISIBLE | WS_TABSTOP;
			ctrl_data[i].dwAddData2 = (UINT32)&btn[i - 1];
		}
	}
	
	sKbConfig.variant.maxlen = NUMPAD_VARIANT_MAXLEN + 2;
	sKbConfig.variant.string = LoadString(STR_DLG_KB_INPUT);
	memset(sKbConfig.variant.string, '\0', 150 - 1);

	if (*value == INVALID_PARAM)
	{
		ctrl_data[0].caption = STR_DLG_KB_TIPS;
	}
	else
	{
		//sprintf(LoadString(STR_DLG_KB_INPUT), "%d", *value);
		sprintf(sKbConfig.variant.string, "%d", *value);
	}
	
	wndMem.pMainWin = GetMainWndMem(IDD_NUMPAD);
	wndMem.pControl = GetCtrlWndMem(IDC_NUMPAD_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;
	
	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;
	
	DialogBoxIndirectParam
		(&dlg_data, hWnd, IDD_NUMPAD, NumPadProc, 0, &wndMem);
	
	if(strlen(sKbConfig.variant.string) > 0)
	{
		*value = atoi(sKbConfig.variant.string);
	}
	switch (sKbConfig.kbType)
	{
		case KEYBOARD_UNS_INT:
		{
			*value = ABS(*value);
			break;
		}

		default:
			break;
	}
	return value;
}




static FP64 *doubleKeyboard(HWND hWnd, RESID child, FP64 *value)
{
	enum dlg_size{
		KEY_OFFSET  = DLG_KB_OFFSET,
		KEY_LEFT	= DLG_OFFSET,
		KEY_HIGH	= KEY_HEIGHT,
		KEY_WIDTH   = DLG_KB_W,
		KEY_DB_W	= DLG_KB_W + KEY_OFFSET,
		KEY_ROW1	= DLG_OFFSET,
		KEY_ROW2	= KEY_ROW1 + KEY_OFFSET,
		KEY_ROW3	= KEY_ROW2 + KEY_OFFSET,
		KEY_ROW4	= KEY_ROW3 + KEY_OFFSET,
		KEY_ROW5	= KEY_ROW4 + KEY_OFFSET,
		KEY_COLUMN1 = DLG_OFFSET,
		KEY_COLUMN2 = KEY_COLUMN1 + KEY_OFFSET,
		KEY_COLUMN3 = KEY_COLUMN2 + KEY_OFFSET,
		KEY_COLUMN4 = KEY_COLUMN3 + KEY_OFFSET,
		KEY_DLG_W   = KEY_COLUMN4 + KEY_WIDTH + DLG_OFFSET,
		KEY_DLG_H   = KEY_ROW5 + KEY_HIGH + DLG_MENU_HIGHT + DLG_OFFSET,
	};
	POINT	   ctrl_pos[NUMPAD_MAX + 1] = {
		{ KEY_COLUMN1, KEY_ROW1 },			  // IDC_NUMPAD_NUM_L
		{ KEY_COLUMN1, KEY_ROW2 },			  // IDC_NUMPAD_7
			{ KEY_COLUMN2, KEY_ROW2 },		  // IDC_NUMPAD_8
				{ KEY_COLUMN3, KEY_ROW2 },	  // IDC_NUMPAD_9
					{ KEY_COLUMN4, KEY_ROW2 },  // IDC_NUMPAD_ESC
		{ KEY_COLUMN1, KEY_ROW3 },			  // IDC_NUMPAD_4
			{ KEY_COLUMN2, KEY_ROW3 },		  // IDC_NUMPAD_5
				{ KEY_COLUMN3, KEY_ROW3 },	  // IDC_NUMPAD_6
					{ KEY_COLUMN4, KEY_ROW3 },  // IDC_NUMPAD_DEL
		{ KEY_COLUMN1, KEY_ROW4 },			  // IDC_NUMPAD_1
			{ KEY_COLUMN2, KEY_ROW4 },		  // IDC_NUMPAD_2
				{ KEY_COLUMN3, KEY_ROW4 },	  // IDC_NUMPAD_3
					{ KEY_COLUMN4, KEY_ROW4 },  // IDC_NUMPAD_MINUS
		{ KEY_COLUMN1, KEY_ROW5 },			  // IDC_NUMPAD_DOT
			{ KEY_COLUMN2, KEY_ROW5 },		  // IDC_NUMPAD_0
				{ KEY_COLUMN3, KEY_ROW5 }	   // IDC_NUMPAD_ENTER
	};
	RESID	   ctrl_id[NUMPAD_MAX + 1] = {
		IDC_NUMPAD_NUM_L,
		IDC_NUMPAD_7,
		IDC_NUMPAD_8,
		IDC_NUMPAD_9,
		IDC_NUMPAD_ESC,
		IDC_NUMPAD_4,
		IDC_NUMPAD_5,
		IDC_NUMPAD_6,
		IDC_NUMPAD_DEL,
		IDC_NUMPAD_1,
		IDC_NUMPAD_2,
		IDC_NUMPAD_3,
		IDC_NUMPAD_MINUS,
		IDC_NUMPAD_DOT,
		IDC_NUMPAD_0,
		IDC_NUMPAD_ENTER
	};
	STRINGID	caption[NUMPAD_MAX + 1] = {
		STR_DLG_KB_INPUT,
		STR_DLG_CHAR_7,
		STR_DLG_CHAR_8,
		STR_DLG_CHAR_9,
		STR_DLG_CHAR_ESC,
		STR_DLG_CHAR_4,
		STR_DLG_CHAR_5,
		STR_DLG_CHAR_6,
		STR_DLG_CHAR_DEL,
		STR_DLG_CHAR_1,
		STR_DLG_CHAR_2,
		STR_DLG_CHAR_3,
		STR_DLG_CHAR_MINUS,
		STR_DLG_CHAR_DOT,
		STR_DLG_CHAR_0,
		STR_DLG_CHAR_OK
	};
	DLGTEMPLATE dlg_data = {
		WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
		0, 0, KEY_DLG_W, KEY_DLG_H,  STR_DLG_KB_CAPTION, 0, NULL, 0L,
	};
	CTRLDATA	ctrl_data[NUMPAD_MAX + 1] = {0};
	BUTTONDATA  btn[NUMPAD_MAX] = {0};
	SIZE		ctrl_size[NUMPAD_MAX + 1];
	INT16	   i;
	INT16	   loops;
	WNDMEM	  wndMem;
	
	ctrl_size[0].cx = KEY_DLG_W - DLG_OFFSET * 2;
	ctrl_size[0].cy = STATIC_HEIGHT;
	loops = TABLESIZE(ctrl_size);
	for (i = 1; i < loops; i++)
	{
		ctrl_size[i].cx = KEY_WIDTH;
		ctrl_size[i].cy = KEY_HIGH;
	}
	ctrl_size[i - 1].cx = KEY_DB_W;
	ctrl_data[0].class_name = CTRL_STATIC;
	ctrl_data[0].dwStyle = WS_VISIBLE | SS_SIMPLE;
	for (i = 0; i < loops; i++)
	{
		ctrl_data[i].x = ctrl_pos[i].x;
		ctrl_data[i].y = ctrl_pos[i].y;
		ctrl_data[i].w = ctrl_size[i].cx;
		ctrl_data[i].h = ctrl_size[i].cy;
		ctrl_data[i].id = ctrl_id[i];
		ctrl_data[i].caption = caption[i];
		if (i != 0)
		{
			ctrl_data[i].class_name = CTRL_BUTTON;
			ctrl_data[i].dwStyle = WS_VISIBLE | WS_TABSTOP;
			ctrl_data[i].dwAddData2 = (UINT32)&btn[i - 1];
		}
	}

	CHAR		szFormat[8];
	RESID	   parent = ((PWIN)hWnd)->id;
	switch (GetSpinBoxFloatFormat(parent, child))
	{
		case FORM_41F:
		case FORM_51F:
			strcpy(szFormat, "%%f.1");
			break;

		case FORM_52F:
		case FORM_72F:
			strcpy(szFormat, "%%f.2");
			break;

		case FORM_53F:
			strcpy(szFormat, "%%f.3");
			break;

		default:
			return value;
	}
	
	sKbConfig.variant.maxlen = NUMPAD_VARIANT_MAXLEN + 2;
	sKbConfig.variant.string = LoadString(STR_DLG_KB_INPUT);
	memset(sKbConfig.variant.string, '\0', 150 - 1);

	if (*value == INVALID_PARAM_FLOAT)
	{
		ctrl_data[0].caption = STR_DLG_KB_TIPS;
	}
	else
	{
		sprintf(LoadString(STR_DLG_KB_INPUT), szFormat, *value);
	}
	
	wndMem.pMainWin = GetMainWndMem(IDD_NUMPAD);
	wndMem.pControl = GetCtrlWndMem(IDC_NUMPAD_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;
	
	dlg_data.controlnr = loops;
	dlg_data.controls  = ctrl_data;
	DialogBoxIndirectParam
		(&dlg_data, hWnd, IDD_NUMPAD, NumPadProc, 0, &wndMem);
	
	if(strlen(sKbConfig.variant.string))
	{
		*value = atof(sKbConfig.variant.string);
	}
	switch (sKbConfig.kbType)
	{
		case KEYBOARD_UNS_DEC:
		{
			*value = ABS(*value);
			break;
		}

		default:
			break;
	}
	return value;
}

static StrBuffer 
	*stringKeyboard(HWND hWnd, RESID child, StrBuffer *buffer)
{
	enum dlg_size{
		KEY_OFFSET  = DLG_KB_OFFSET,
		KEY_LEFT	= DLG_OFFSET,
		KEY_TOP	 = DLG_OFFSET,
		KEY_HIGH	= KEY_HEIGHT,
		KEY_WIDTH   = DLG_KB_W + KEY_OFFSET * 0,
		KEY_DB_W	= DLG_KB_W + KEY_OFFSET * 1,
		KEY_TB_W	= DLG_KB_W + KEY_OFFSET * 2,
		KEY_HALF	= KEY_WIDTH / 2,
		KEY_ROW1	= KEY_TOP,
		KEY_ROW2	= KEY_ROW1 + KEY_OFFSET,
		KEY_ROW3	= KEY_ROW2 + KEY_OFFSET,
		KEY_ROW4	= KEY_ROW3 + KEY_OFFSET,
		KEY_ROW5	= KEY_ROW4 + KEY_OFFSET,
		KEY_ROW6	= KEY_ROW5 + KEY_OFFSET,
		KEY_COLUMN1 = KEY_LEFT,
		KEY_COLUMN2 = KEY_COLUMN1 + KEY_OFFSET,
		KEY_COLUMN3 = KEY_COLUMN2 + KEY_OFFSET,
		KEY_COLUMN4 = KEY_COLUMN3 + KEY_OFFSET,
		KEY_COLUMN5 = KEY_COLUMN4 + KEY_OFFSET,
		KEY_COLUMN6 = KEY_COLUMN5 + KEY_OFFSET,
		KEY_COLUMN7 = KEY_COLUMN6 + KEY_OFFSET,
		KEY_COLUMN8 = KEY_COLUMN7 + KEY_OFFSET,
		KEY_COLUMN9 = KEY_COLUMN8 + KEY_OFFSET,
		KEY_COLUMN10= KEY_COLUMN9 + KEY_OFFSET,
		KEY_DLG_W   = KEY_COLUMN10 + KEY_WIDTH + DLG_OFFSET,
		KEY_DLG_H   = KEY_ROW6 + KEY_HIGH + DLG_MENU_HIGHT + DLG_OFFSET,
	};
	POINT	   ctrl_pos[KEYBOARD_MAX] = {
		{ KEY_COLUMN1 , 0 },//  boarder
		{ KEY_COLUMN1 , KEY_ROW2 },//  KEYBOARD_PREVIOUS,
		{ KEY_COLUMN2 , KEY_ROW2 },//  KEYBOARD_CN1,
		{ KEY_COLUMN3 , KEY_ROW2 },//  KEYBOARD_CN2,
		{ KEY_COLUMN4 , KEY_ROW2 },//  KEYBOARD_CN3,
		{ KEY_COLUMN5 , KEY_ROW2 },//  KEYBOARD_CN4,
		{ KEY_COLUMN6 , KEY_ROW2 },//  KEYBOARD_CN5,
		{ KEY_COLUMN7 , KEY_ROW2 },//  KEYBOARD_CN6,
		{ KEY_COLUMN8 , KEY_ROW2 },//  KEYBOARD_CN7,
		{ KEY_COLUMN9 , KEY_ROW2 },//  KEYBOARD_CN8,
		{ KEY_COLUMN10, KEY_ROW2 },//  KEYBOARD_NEXT,
		{ KEY_COLUMN1 , KEY_ROW3 },//  KEYBOARD_Q,
		{ KEY_COLUMN2 , KEY_ROW3 },//  KEYBOARD_W,
		{ KEY_COLUMN3 , KEY_ROW3 },//  KEYBOARD_E,
		{ KEY_COLUMN4 , KEY_ROW3 },//  KEYBOARD_R,
		{ KEY_COLUMN5 , KEY_ROW3 },//  KEYBOARD_T,
		{ KEY_COLUMN6 , KEY_ROW3 },//  KEYBOARD_Y,
		{ KEY_COLUMN7 , KEY_ROW3 },//  KEYBOARD_U,
		{ KEY_COLUMN8 , KEY_ROW3 },//  KEYBOARD_I,
		{ KEY_COLUMN9 , KEY_ROW3 },//  KEYBOARD_O,
		{ KEY_COLUMN10, KEY_ROW3 },//  KEYBOARD_P,
		{ KEY_COLUMN1 + KEY_HALF, KEY_ROW4 },//  KEYBOARD_A,
		{ KEY_COLUMN2 + KEY_HALF, KEY_ROW4 },//  KEYBOARD_S,
		{ KEY_COLUMN3 + KEY_HALF, KEY_ROW4 },//  KEYBOARD_D,
		{ KEY_COLUMN4 + KEY_HALF, KEY_ROW4 },//  KEYBOARD_F,
		{ KEY_COLUMN5 + KEY_HALF, KEY_ROW4 },//  KEYBOARD_G,
		{ KEY_COLUMN6 + KEY_HALF, KEY_ROW4 },//  KEYBOARD_H,
		{ KEY_COLUMN7 + KEY_HALF, KEY_ROW4 },//  KEYBOARD_J,
		{ KEY_COLUMN8 + KEY_HALF, KEY_ROW4 },//  KEYBOARD_K,
		{ KEY_COLUMN9 + KEY_HALF, KEY_ROW4 },//  KEYBOARD_L,
		{ KEY_COLUMN1 , KEY_ROW5 },//  KEYBOARD_CAPS,
		{ KEY_COLUMN2 , KEY_ROW5 },//  KEYBOARD_Z,
		{ KEY_COLUMN3 , KEY_ROW5 },//  KEYBOARD_X,
		{ KEY_COLUMN4 , KEY_ROW5 },//  KEYBOARD_C,
		{ KEY_COLUMN5 , KEY_ROW5 },//  KEYBOARD_V,
		{ KEY_COLUMN6 , KEY_ROW5 },//  KEYBOARD_B,
		{ KEY_COLUMN7 , KEY_ROW5 },//  KEYBOARD_N,
		{ KEY_COLUMN8 , KEY_ROW5 },//  KEYBOARD_M,
		{ KEY_COLUMN9 , KEY_ROW5 },//  KEYBOARD_DELETE,
		{ KEY_COLUMN1 , KEY_ROW6 },//  KEYBOARD_NUM_MARKS,
		{ KEY_COLUMN2 , KEY_ROW6 },//  KEYBOARD_IME,
		{ KEY_COLUMN3 , KEY_ROW6 },//  KEYBOARD_MARK,
		{ KEY_COLUMN4 , KEY_ROW6 },//  KEYBOARD_SPACE,
		{ KEY_COLUMN7 , KEY_ROW6 },//  KEYBOARD_MARK1,
		{ KEY_COLUMN8 , KEY_ROW6 },//  KEYBOARD_MARK2,
		{ KEY_COLUMN9 , KEY_ROW6 },//  KEYBOARD_ENTER,
	};
	DLGTEMPLATE dlg_data = {
		WS_ABSSCRPOS | WS_CAPTION | WS_BORDER | WS_MODALDLG, WS_NONE, 
		0, 0, KEY_DLG_W, KEY_DLG_H,  STR_DLG_KB_CAPTION, 0, NULL, 0L,
	};
	CTRLDATA	ctrl_data[KEYBOARD_MAX] = {0};
	BUTTONDATA  btn[KEYBOARD_MAX] = {0};
	SIZE		ctrl_size[KEYBOARD_MAX];
	INT16	   i;
	WNDMEM	  wndMem;

	SetPinyinPos(KEY_COLUMN2, KEY_ROW2 + DLG_MENU_HIGHT - 12);
	
	for (i = KEYBOARD_FIRST; i < KEYBOARD_MAX; i++)
	{
		ctrl_size[i].cx = KEY_WIDTH;
		ctrl_size[i].cy = KEY_HIGH;
	}
	ctrl_size[KEYBOARD_SPACE].cx	= KEY_TB_W;
	ctrl_size[KEYBOARD_DELETE].cx   = KEY_DB_W;
	ctrl_size[KEYBOARD_ENTER].cx	= KEY_DB_W;
	ctrl_size[KEYBOARD_FIRST].cx	= KEY_DLG_W - DLG_OFFSET * 2;
	// (12 + 2) * 3 + 2 - 1 = 43 // (字高 + 行间距) * 行数 + 开始坐标 - 1
	ctrl_size[KEYBOARD_FIRST].cy	= 43;//STATIC_HEIGHT * 2;
	for (i = KEYBOARD_FIRST; i < KEYBOARD_MAX; i++)
	{
		ctrl_data[i].class_name = CTRL_BUTTON;
		ctrl_data[i].dwStyle	= WS_VISIBLE | WS_TABSTOP;
		ctrl_data[i].dwExStyle  = WS_NONE;
		ctrl_data[i].x		  = ctrl_pos[i].x;
		ctrl_data[i].y		  = ctrl_pos[i].y;
		ctrl_data[i].w		  = ctrl_size[i].cx;
		ctrl_data[i].h		  = ctrl_size[i].cy;
		ctrl_data[i].id		 = srCtrl_id[i];
		ctrl_data[i].caption	= ssCaption[i];
		ctrl_data[i].dwAddData  = 0L;
		ctrl_data[i].dwAddData2 = (DWORD)&btn[i];
	}
	
	ctrl_data[KEYBOARD_FIRST].class_name = CTRL_STATIC;
	ctrl_data[KEYBOARD_FIRST].dwStyle	= WS_VISIBLE | SS_LEFTNOWORDWRAP;
	ctrl_data[KEYBOARD_FIRST].dwAddData2 = 0L;
	
	sKbConfig.variant.maxlen = 150 - 1;
	sKbConfig.variant.string = LoadString(STR_DLG_KB_INPUT);
	memset(sKbConfig.variant.string, '\0', 150 - 1);
	strncpy(sKbConfig.variant.string, buffer->string, buffer->maxlen);
	sKbConfig.variant.maxlen = buffer->maxlen;

	if (strlen(sKbConfig.variant.string) == 0)
	{
		ctrl_data[0].caption = STR_DLG_KB_TIPS;
		strcpy(LoadString(STR_DLG_KB_TIPS), sKbConfig.tips);
	}
	else
	{
		strcpy(LoadString(STR_DLG_KB_INPUT), sKbConfig.variant.string);
	}
	
	wndMem.pMainWin = GetMainWndMem(IDD_KBDLG_KEYBOARD);
	wndMem.pControl = GetCtrlWndMem(IDC_KBDLG_KB_FIRST);
	wndMem.ctrlNum  = TABLESIZE(ctrl_data);
	wndMem.task	 = SysGui_HTSK;
	
	dlg_data.controlnr = KEYBOARD_MAX;
	dlg_data.controls  = ctrl_data;
	
	DialogBoxIndirectParam
		(&dlg_data, hWnd, IDD_KBDLG_KEYBOARD, StringKeyboardProc, 0, &wndMem);
	
	memset(buffer->string, '\0', buffer->maxlen - 1);
	strncpy(buffer->string, sKbConfig.variant.string, buffer->maxlen);
	return (&sKbConfig.variant);
}


VOID SelectKeyboardType(UINT8 kbType, UCHAR *caption, UCHAR *tips)
{
	sKbConfig.kbType = kbType;
	sKbConfig.caption = caption;
	sKbConfig.tips = tips;
}

INT32 UseKeyboard(HANDLE hWnd, DWORD wParam, LPARAM lParam)
{
	KBTYPE type;
	type = sKbConfig.kbType;
	switch (type)
	{
		case KEYBOARD_UNS_INT:
		case KEYBOARD_INTEGER:
			return (INT32)integerKeyboard(hWnd, wParam, (INT32*)lParam);

		case KEYBOARD_UNS_DEC:
		case KEYBOARD_DECIMAL:
			return (INT32)doubleKeyboard(hWnd, wParam, (FP64*)lParam);

		case KEYBOARD_LOWERCS:
		case KEYBOARD_UPPERCS:
		case KEYBOARD_CHINESE:
		case KEYBOARD_NUMMARKS:
		case KEYBOARD_MARKS:
			return (INT32)stringKeyboard(hWnd, wParam, (StrBuffer*)lParam);

		default:
			return 0;
	}
}

#endif


