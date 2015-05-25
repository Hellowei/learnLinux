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
#define   USERCFG_GLOBALS 
#include  "includes.h"

extern INT8 EnterOs;
extern INT8 FirstBoot;
extern UINT8 LCSysBoard;

#define  LOADCFG_ENTER_CRITCAL()
#define  LOADCFG_EXIT_CRITCAL()

PARAM_ALM_INFO  ParaAlarmInfo[ALM_PARA_MAX] =
{
	{PARA_BLOCK_FHR1, ALM_PARA_FHR1, FALSE, 0, STR_ALM_FHR_ALM_LMT_ERR, STR_ALM_FHR1_TOO_HI, STR_ALM_FHR1_TOO_LO, FALSE},
	{PARA_BLOCK_FHR2, ALM_PARA_FHR2, FALSE, 0, STR_ALM_FHR_ALM_LMT_ERR, STR_ALM_FHR2_TOO_HI, STR_ALM_FHR2_TOO_LO, FALSE}
};

INT8  ApplyDefaultCfg = FALSE;

static UINT8 *Mem_Map = NULL;
static UINT8 *MemTail = NULL;
static UINT8 *pReadMM = NULL;

static UINT32 Mem_Checksum = 0;

const static CHAR cszConfKey[CFG_KEYID_MAX][32] = {
	 "MonitorType"
 	,"DatetimeFormat"
	,"ModuleKeyboardOnline"
	,"ModuleFetalOnline"
	,"ModulePrinterOnline"
	,"KeyboardCOM"
	,"FetalCOM"
	,"PrinterCOM"
	,"KeyVolume"
	,"Language"
	,"NightMode"
	,"HelpInfo"
	,"FaceType"
	,"BedNumber"
	,"Fhr1Color"
	,"Fhr2Color"
	,"TocoColor"
	,"FmColor"
	,"AlarmFhrHi"
	,"AlarmFhrLo"
	,"AlarmSwitch"
	,"AlarmVolume"
	,"AlarmSound"
	,"FetalMode"
	,"FhrVoiceChannel"
	,"FhrVolume"
	,"TocoZeroValue"
	,"FetalMoveCalc"
	,"PrintFast"
	,"PrintType"
	,"PrintSpeed"
	,"PrintDetach"
	,"PrintLength"
	,"PrintAuto"
	,"PrintMode"
	,"PrintChroma"
	,"PrintRegionStart"
	,"PrintRegionEnd"
	,"PrintScale"
	,"PrintFhrMax"
	,"PrintFhrMin"
	,"AnalyType"
	,"AnalyAuto"
	,"NetworkCfgFile"
	,"NetworkAuto"
	,"NetworkName"
	,"NetworkIP"
	,"NetworkMac"
	,"NetworkServer"
	,"NetworkGateway"
	,"NetworkMask"
	,"TouchCOM"
	,"TouchEnable"
	,"TouchCalFlag"
	,"TouchOffsetX"
	,"TouchOffsetY"
	,"TouchScaleX"
	,"TouchScaleY"
	,"LowCost"
	,"DefaultAnalyType"//用户保存的评分设置默认值
};

static int siKeyLen[CFG_KEYID_MAX];

#define USER_CFG_FILE		FPC_CONFIG
// 写入转存临时文件,不从该文件读取任何信息
#define USER_TMP_FILE		FPC_TMPCFG
#define ENB_ENCRYPT_FILE	 0	  // 使用加密配置文件

const UCHAR LanguageAkaName[MAX_LANGUAGE][6][8] = {
	{"ENGLISH", "English", "english", "en", "En", "EN"}
   ,{"CHINESE", "Chinese", "chinese", "zh", "Zh", "ZH"}
   ,{"RUSSIAN", "Russian", "russian", "ru", "Ru", "RU"}
   ,{"SPANISH", "Spanish", "spanish", "es", "Es", "ES"}
   ,{"TURKISH", "Turkish", "turkish", "tr", "Tr", "TR"}
};

const UCHAR DateTimeFormat[FORMAT_DATETIME_MAX][12] = {
	 "yyyy-MM-dd"
	,"MM-dd-yyyy"
	,"dd-MM-yyyy"
	,"hh:mm:ss"
	,"hh:mm"
	,"tt hh:mm:ss"
	,"tt hh:mm"
};

const UCHAR MonitorLocalName[2][12] = {"Artemis4S", "Artemis2"};
const UCHAR PrinterTypeName[PAPER_TYPE_MAX][12] = {
	 "110MM"
 	,"LTPV445C"
 	,"150MM"
 	,"PT1561P"
};

VOID EncryptData(UCHAR *buff, INT32 len)
{
#if ENB_ENCRYPT_FILE
	const UCHAR key[16] =
		{'I','C','S','P','1','8','6','1','_','E','2','P','S','I','Z','E'};
	INT32 i, loops;
	loops = 2;
	for (i = 0; i < len; i++)
	{
		*(buff + i) ^= key[loops++];
		if (loops == sizeof(key)) loops = 0;
	}
#endif
}

#if 0
// 32位crc
static unsigned int crc_table[256];
/*
**初始化crc表,生成32位大小的crc表
*/
static void init_crc32_table(void)
{
	unsigned int c;
	unsigned int i, j;
	for (i = 0; i < 256; i++)
	{
		c = (unsigned int)i;
		for (j = 0; j < 8; j++)
		{
			if (c & 1)
				c = 0xEDB88320L ^ (c >> 1);
			else
				c = c >> 1;
		}
		crc_table[i] = c;
	}
}

/*计算buffer的crc校验码*/
static unsigned long
crc32(unsigned long crc,unsigned char *buffer, unsigned long size)
{
	unsigned long i;
	for (i = 0; i < size; i++)
	{
		crc = crc_table[(crc ^ buffer[i]) & 0xff] ^ (crc >> 8);
	}
	return crc ;
}
#endif

VOID InitKeyLength(VOID)
{
	int i;
	for (i = 0; i < CFG_KEYID_MAX; i++)
		siKeyLen[i] = strlen(cszConfKey[i]);
}


/**
 ** 检查用户配置文件是否存在
 **/
BOOL  CheckCfgFileIsExist (VOID)
{
	return CheckFileExist(USER_CFG_FILE);
}

#if 0
static VOID  Update_Checksum(UCHAR *buff, INT32 len)
{
	Mem_Checksum = crc32(0, buff, len);
}
#endif

/**
  \brief
  \note   
**/
//static  STATUS  mem_write_e2prom_checksum(UINT16 base_addr, UINT16 byte_num, UINT8 *data)
//{
//	STATUS status;

//	status = mem_write_e2prom(base_addr, byte_num, data);
//	if (status > 0) {
//		Update_Checksum(data, byte_num);
//		return status;
//	} else {
//		return (-1);
//	}
//	return 0;
//}

BOOL GetConfigSection(UCHAR *buffer, UINT32 len)
{
	UCHAR *p = buffer;
	UCHAR *tail = p + (len - 2 * strlen(cszConfKey[0]));
	while (p < tail)
	{
		if (*p != '[')
		{
			// 跳过注释和多余的行
			while(p < tail)
			{
				if (*p++ == '\n')
					break;
			}
		}
		// 在正文中查找 USER_CFG_HEAD
		else 
		{
			if (memcmp(p+1, USER_CFG_HEAD, strlen(USER_CFG_HEAD)))
			{
				// 跳过不是 USER_CFG_HEAD 的行
				while(p < tail)
				{
					if (*p++ == '\n')
						break;
				}
				continue;
			}
			pReadMM = p;
			return TRUE;
		}
	}
	return FALSE;
}

// 由于不修改源数据,key和value需要预先分配内存,返回读指针
UCHAR *GetConfigFileNextKey(UCHAR *pCur, UCHAR *pTail, UCHAR *key, UINT32 kLen,
							UCHAR *value, UINT32 vLen)
{
	UCHAR *p = pCur;
	UINT32 i;
	memset(key, '\0', kLen);
	memset(value, '\0', vLen);
	while (p < pTail)
	{
		// 遇到下一个Section返回
		if (*p == '[')
		{
			break;
		}
		else 
		{
			if (*p == '\n') p++;											// 跳过空行
			else if (*p == ';')
			{
				while(p < pTail)
				{
					if (*p++ == '\n') break;   // 跳过注释
				}
				if (p >= pTail)
					break;
			}
			else if (*p == ' ')
			{
				while(*(++p) == ' ');					   // 跳过空格
			}
			else
			{
				i = 0;
				//prinfo("// 开始查找本行\r\n");
				while(p < pTail)
				{
					*(key + i++) = *p++;
					if (*p == '\n')
					{
						memset(key, '\0', kLen);
						p++;
						i = 0;
					}
					if (*p == '=')
						break;
					if (*p == '\0')
						break;
				}
				//prinfo("// 找到key:%s, i:%d\r\n", key, i);
				i = 0;
				p++;
				while(p < pTail)
				{
					*(value + i++) = *p;
					if (*p == '\0')
						break;
					if (*p == '\n')
						break;
					if (*p == ';')
						break;
					if (i == vLen - 1)
						break;
					p++;
				}
				//prinfo("// 找到value:%s\r\n", value);
				while (*(value + i) == '\r' || *(value + i) == '\n')
				{
					*(value + i--) = '\0';
				}
				//prinfo("去掉\\r\\n, value:%s\r\n", value);
				break;
			}
		}
	}
	return p;
}

/**

**/
BOOL   InitE2eprom(VOID)
{
//	STATUS  status;
//	INT16   i;
//	CHAR	str[50];
	#if ENB_ENCRYPT_FILE
	UINT32  check_sum;
	#endif
	UCHAR   *p;
	UINT32   len;
	if (Mem_Map == NULL)
	{
		if (NULL == (Mem_Map = (UINT8 *)malloc(USER_CFG_CACHE_SIZE)))
		{
			// 分配文件缓存失败
			printf("\r\nInitE2eprom error:Cannot malloc cache!\r\n");
		}
		else
		{
			// 这里实际上只需要2k,但是分配了60k
			MemTail = Mem_Map + USER_CFG_CACHE_SIZE - 1;
			pReadMM = Mem_Map;
		}
	}
	#if ENB_ENCRYPT_FILE
	init_crc32_table();
	#endif
	if (!CheckCfgFileIsExist())  //文件存在；
	{ 
		return  FALSE;
	}

	p = LoadSmallFile(USER_CFG_FILE, &len);
	if ((!p) || (len == 0))
		return FALSE;
	//prinfo("read file len...%d\r\n", len);
	memcpy(Mem_Map, p, len);
	free(p);
	Mem_Checksum = 0;
	p = Mem_Map;
	#if ENB_ENCRYPT_FILE
	// 尝试解密
	len -= sizeof(Mem_Checksum);
	check_sum = *((UINT32*)(p + len));
	Update_Checksum(p, len);
	EncryptData(p, len);
	// 如果解密后还是错误的文件头,重新初始化该文件
	#endif
	InitKeyLength();
	if (GetConfigSection(p , len))
	{
	#if ENB_ENCRYPT_FILE
		return (Mem_Checksum == check_sum);
	#endif
		return TRUE;
	}
	return FALSE;
}

/***********************************************************************************
函数：	Save_Sys_Config
函数功能：将当前系统配置信息写入到EPROM中
调用方式：在确认执行“保存设置”后调用
调用参数：
		  info_ndx:
			＝ SAVE_ALLINFO  存储全部系统配置项
			!= SAVE_ALLINFO  存储单独系统配置项,由InforNo指定

其他说明：
		  本程序不处理缺省配置。
***********************************************************************************/
VOID  Save_Sys_Config (INT16 info_ndx)
{
	//Save_Sys_Config2(info_ndx);
}

BOOL GetBooleanKeyValue(UCHAR *value)
{
	if (*value == 'T' || *value == 't' || *value == 'Y' || *value == 'y' || *value == '1')
		return TRUE;
	else if (*value == 'F' || *value == 'f' || *value == 'N' || *value == 'n' || *value == '0')
		return FALSE;
	else
		return FALSE;
}

INT32 GetIntegerKeyValue(UCHAR *value)
{
	#if 1
	extern int StrHex2Int(UCHAR *szHex);
	//	16进制支持
	if (*value == '&' && *(value+1) == 'H')
		return StrHex2Int(value+2);
	if (*value == '0' && (*(value+1) == 'x' || *(value+1) == 'X'))
		return StrHex2Int(value+2);
	#endif
	return atoi((char*)value);
}

FLOAT GetFloatKeyValue(UCHAR *value)
{
	CHAR *p = (CHAR*)value;
	while (*p != '\0')
	{
		if ((*p >= '0' && *p <= '9') || *p == '.' || *p == '-' || *p == '+')
		{
			break;
		}
		p++;
	}
	if (*p == '\0')
		return 0;
	if (strlen(p) > 8)
	{
		*(p + 8) = '\0';
	}
	return atof(p);
}

INT16 GetRecorderType(UCHAR *value)
{
	INT16 i;
	for (i = 0; i < PAPER_TYPE_MAX; i++)
	{
		if (0 == strncmp(PrinterTypeName[i], value, strlen(PrinterTypeName[i])))
		{
			break;
		}
	}
	if (i == PAPER_TYPE_MAX)
	{
		if (MonitorConfig.MonitorName == MONITOR_TYPE_AR2)
		{
			i = PAPER_TYPE_PT1561P;
		}
		else
		{
			i = PAPER_TYPE_112MM;
		}
	}
	return i;
}

VOID GetDatetimeFormat(UCHAR *value)
{
	CHAR *p = (CHAR*)value;
	int i;
	char tmp[FORMAT_DATETIME_MAX][12];
	MonitorConfig.time_delimiter = ':';
	while(*p == ' ')
		p++;
	if (*value < ' ')
	{
		MonitorConfig.date_delimiter = '-';
		MonitorConfig.date_format_type = FORMAT_YYYY_MM_DD;
		MonitorConfig.time_format_type = FORMAT_HH_MM_SS;
		return;
	}
	while (*p >= ' ')
	{
		if (*p++ == 'M')
		{
			if (*p == 'M')
			{
				p++;
				if (*p == '-' || *p == '/' || *p == '.')
					MonitorConfig.date_delimiter = *p;
				else
					MonitorConfig.date_delimiter = '-';
			}
		}
	}
	memcpy(tmp[0], DateTimeFormat[0], sizeof(DateTimeFormat));
	if (MonitorConfig.date_delimiter != '-')
	{
		p = tmp[0];
		for (i = 0; i < sizeof(tmp); i++)
		{
			if (*p == '-')
				*p = MonitorConfig.date_delimiter;
			p++;
		}		
	}
	p = (CHAR*)value;
	for (i = FORMAT_YYYY_MM_DD; i <= FORMAT_DD_MM_YYYY; i++)
	{
		if (strstr(p, tmp[i]))
		{
			MonitorConfig.date_format_type = i;
			break;
		}
	}
	
	for (i = FORMAT_TT_HH_MM_SS; i <= FORMAT_TT_HH_MM; i++)
	{
		if (strstr(p, tmp[i]))
		{
			MonitorConfig.time_format_type = i;
			return;
		}
	}
	for (i = FORMAT_HH_MM_SS; i <= FORMAT_HH_MM; i++)
	{
		if (strstr(p, tmp[i]))
		{
			MonitorConfig.time_format_type = i;
			break;
		}
	}
}

VOID PutDatetimeFormat(CHAR *value)
{
	int i;
	char tmp[12];
	strcpy(tmp, (char*)DateTimeFormat[(UCHAR)MonitorConfig.date_format_type]);
	if (MonitorConfig.date_delimiter != '-')
	{
		for (i = 0; i < sizeof(tmp); i++)
		{
			if (tmp[i] == '-')
				tmp[i] = MonitorConfig.date_delimiter;
		}
	}
	sprintf(value, "%s %s",
		tmp, DateTimeFormat[(UCHAR)MonitorConfig.time_format_type]);
}

// 语言允许多种别称,需要专门的函数处理
LANGUAGE GetLanguageKeyValue(UCHAR *value)
{
	int i, j, aka = TABLESIZE(LanguageAkaName[0]);
	char *lan;
	if (*value == '\0') return DEFAULT_LANGUAGE;
	for (i = 0; i < MAX_LANGUAGE; i++)
	{
		for (j = 0; j < aka; j++)
		{
			lan = (char*)LanguageAkaName[i][j];
			if (0 == strncmp(lan, (char*)value, strlen(lan)))
				return i;
		}
	}
	return DEFAULT_LANGUAGE;
}

UART_PORT GetModulePortKeyValue(UCHAR *value)
{
	UCHAR *p = value;
	UART_PORT port = COMMAX;
	while (*p == ' ') p++;
	do {
		if (*p > '0' && *p <= '9') {
			port = COM1 + (*p) - '1';
			break;
		}
		if (*p != 'c' && *p != 'C')
			break;
		p++;
		if (*p != 'o' && *p != 'O')
			break;
		p++;
		if (*p != 'm' && *p != 'M')
			break;
		p++;
		if (*p > '0' && *p <= '9') {
			port = COM1 + (*p) - '1';
			break;
		}
	} while (0);
	return port;
}

#if 0
static int StrRowLen(char *str)
{
	int len;
	int cnt = 0;
	char *p = str;
	len = strlen(p);
	while (len > cnt)
	{
		if (*p == '\n') break;
		cnt++;
	}
	return cnt;
}
#endif

int ChangeKeyValue(UCHAR *pKey, UCHAR *value)
{
	
	CHAR *pVal;
	CHAR *p;
	CHAR *pTmp;
	INT32 vLen, i, mLen;
	p = strchr((char*)pKey, '=');
	pVal = p + 1;
	p = strchr((char*)pKey, '\n');
	if (p > strchr((char*)pKey, ';') && pKey < (UCHAR*)strchr((char*)pKey, ';')) // 行中有注释
		p = strchr((char*)pKey, ';');
	vLen = strlen ((char*)value);
	if (vLen == p - pVal)
	{
		memcpy(pVal, value, vLen);
	}
	else
	{
		//需要移动字符串
		mLen = strlen(p) + 1;
		if (vLen > p - pVal)
		{
			// 缓存足够大，直接将要移动的数据移到数据末
			pTmp = p + mLen + vLen;
			memcpy(pTmp, p, mLen);
			memcpy(pVal, value, vLen);
			p = pVal + vLen;
			memcpy(p, pTmp, mLen);
		}
		else
		{
			memcpy(pVal, value, vLen);
			pVal += vLen;
			for (i = 0; i < mLen; i++)
			{
				*pVal++ = *p++;
			}
		}
	}
	return 0;
}

/*******************************************************************************
函数名称:VOID PushStrKeyValue(const UCHAR *key, const UCHAR *value)

生成日期:2013/9/23
功能说明:将键值写入缓存
输入参数:key value
函数返回:缓存不足返回-1
*******************************************************************************/
int PushStrKeyValue(const CHAR *key, const CHAR *value)
{
	UCHAR buff[128];
	UCHAR *p;
	
	if (MemTail < Mem_Map + strlen((char*)Mem_Map) + strlen((char*)value))
		return -1;
	//printf("setvalue key value %s %s\n",key,value);
	strcpy((char*)buff, (char*)key);
	strcat((char*)buff, "=");
	if (NULL != (p = (UCHAR*)strstr((char*)Mem_Map, (char*)buff)))
	{
		if (*(p-1) == '\n') //行开头,由于有Section,不会出现第一行就是key的情况
		{
			return ChangeKeyValue(p, (UCHAR *)value);
		}
		else
		{
			while(*(p-1) != '\n')
			{
				if (NULL != (p = (UCHAR*)strstr((char*)(p+1), (char*)buff)))
				{
					return ChangeKeyValue(p, (UCHAR *)value);
				}
				else
				{
					break;
				}
			}
		}
	}
	sprintf((char*)buff, "%s=%s\n", key, value);
	if (MemTail < Mem_Map + strlen((char*)Mem_Map) + strlen((char*)buff))
		return -1;
	// 加入到最后
	strcat((char*)Mem_Map, (char*)buff);
	return 0;
}

STATUS PutConfigKeyValue2(CFG_KEYID keyID, UINT8 *value)
{
	int ret;
	extern PARAM_LIMITS ParamLimits[PARAM_LMTS_MAX];
	switch (keyID)
	{
		case CFG_KEYID_MONITORTYPE:
			/**
			if (strcmp((char*)value, MONITOR_TYPE_NAME))
			{
				prinfo("error monitor type, rebuild the configure file!\n");
				return FALSE;
			}
			else
			{
				return TRUE;
			}
			**/
			{
				MonitorConfig.MonitorName = 0;
				if (0 == strncmp(value, MonitorLocalName[1], strlen(MonitorLocalName[1])))
				{
					MonitorConfig.MonitorName = 1;
				}
				else
				{
					strcpy(value, MonitorLocalName[0]);
				}
				SetMachineName(value);
			}
			break;

		case CFG_KEYID_DATETIME_FORMAT:
			GetDatetimeFormat(value);
			break;
		
		case CFG_KEYID_MODULEKEYBOARDONLINE:
			MonitorConfig.moduleInfo[MID_KB].OnLineFalag =
				GetBooleanKeyValue(value);
			break;
		
		case CFG_KEYID_MODULEFETALONLINE:
			MonitorConfig.moduleInfo[MID_FHR].OnLineFalag =
				GetBooleanKeyValue(value);
			break;
		
		case CFG_KEYID_MODULEPRINTERONLINE:
			MonitorConfig.moduleInfo[MID_RECODER].OnLineFalag =
				GetBooleanKeyValue(value);
			break;

		case CFG_KEYID_KEYBOARDCOM:
			MonitorInfo.deviceInfo[DEV_KB].port = GetModulePortKeyValue(value);
			if ((COM9 < MonitorInfo.deviceInfo[DEV_KB].port)
				|| (COM1 > MonitorInfo.deviceInfo[DEV_KB].port))
			{
				MonitorInfo.deviceInfo[DEV_KB].port = COM1;
			}
			break;

		case CFG_KEYID_FETALCOM:
			MonitorInfo.deviceInfo[DEV_PM].port = GetModulePortKeyValue(value);
			if ((COM9 < MonitorInfo.deviceInfo[DEV_PM].port)
				|| (COM1 > MonitorInfo.deviceInfo[DEV_PM].port))
			{
				MonitorInfo.deviceInfo[DEV_PM].port = COM3;
			}
			break;

		case CFG_KEYID_PRINTERCOM:
			MonitorInfo.deviceInfo[DEV_REC].port = GetModulePortKeyValue(value);
			if ((COM9 < MonitorInfo.deviceInfo[DEV_REC].port)
				|| (COM1 > MonitorInfo.deviceInfo[DEV_REC].port))
			{
				MonitorInfo.deviceInfo[DEV_REC].port = COM9;
			}
			break;

		case CFG_KEYID_KEYVOLUME:
			ret = GetIntegerKeyValue(value);
			if (ret > 7 || ret < 0) ret = 4;
			MonitorConfig.kbVol = ret;
			break;
		
		case CFG_KEYID_LANGUAGE:
			MonitorConfig.language = GetLanguageKeyValue(value);
			//prinfo("MonitorConfig.language...%d\n", MonitorConfig.language);
			break;
		
		case CFG_KEYID_NIGHTMODE:
			MonitorConfig.nightModeOn = GetBooleanKeyValue(value);
			break;

		case CFG_KEYID_HELPINFO:
			MonitorConfig.showHelp = GetBooleanKeyValue(value);
			break;
		
		case CFG_KEYID_FACETYPE:
			ret = GetIntegerKeyValue(value);
			if (ret > FACE_MAX || ret < FACE_STD) ret = FACE_STD;
			MonitorConfig.faceType = ret;
			break;
		
		case CFG_KEYID_BEDNUMBER:
			ret = GetIntegerKeyValue(value);
			MonitorConfig.bedNo = LOBYTE(ret);
			break;

		case CFG_KEYID_FHR1COLOR:
			ret = GetIntegerKeyValue(value);
			if (ret < 0 || ret >= WEC_ITEM_NUMBER) ret = BLOCK_FHR1_COLOR;
			MonitorConfig.colorParam[PARA_BLOCK_FHR1] = ret;
			break;

		case CFG_KEYID_FHR2COLOR:
			ret = GetIntegerKeyValue(value);
			if (ret < 0 || ret >= WEC_ITEM_NUMBER) ret = BLOCK_FHR2_COLOR;
			MonitorConfig.colorParam[PARA_BLOCK_FHR2] = ret;
			break;

		case CFG_KEYID_TOCOCOLOR:
			ret = GetIntegerKeyValue(value);
			if (ret < 0 || ret >= WEC_ITEM_NUMBER) ret = BLOCK_TOCO_COLOR;
			MonitorConfig.colorParam[PARA_BLOCK_TOCO] = ret;
			break;

		case CFG_KEYID_FMCOLOR:
			ret = GetIntegerKeyValue(value);
			if (ret < 0 || ret >= WEC_ITEM_NUMBER) ret = BLOCK_AFM_COLOR;
			MonitorConfig.colorParam[PARA_BLOCK_FM] = ret;
			break;
		
		case CFG_KEYID_ALARMFHRHI:
			ret = GetIntegerKeyValue(value);
			if (ret < ParamLimits[PARAM_LMTS_FHR].low
				|| ret > ParamLimits[PARAM_LMTS_FHR].high)
			{
				ret = 160;
			}
			FhrConfig.FhrAlarmLimitHi = ret;
			break;
		
		case CFG_KEYID_ALARMFHRLO:
			ret = GetIntegerKeyValue(value);
			if (ret < ParamLimits[PARAM_LMTS_FHR].low
				|| ret > ParamLimits[PARAM_LMTS_FHR].high)
			{
				ret = 120;
			}
			FhrConfig.FhrAlarmLimitLo = ret;
			break;
		
		case CFG_KEYID_ALARMSWITCH:
			FhrConfig.alarm = GetBooleanKeyValue(value);
			break;
		
		case CFG_KEYID_ALARMVOLUME:
			ret = GetIntegerKeyValue(value);
			if (ret > 3 || ret < 0) ret = 2;
			MonitorConfig.alarmVolume = ret;
			break;

		case CFG_KEYID_ALARMSILENCE:
			MonitorConfig.alarmSoundOn = GetBooleanKeyValue(value);
			break;
		
		case CFG_KEYID_FETALMODE:
			ret = GetIntegerKeyValue(value);
			if (ret > 2 || ret < 0) ret = 2;
			FhrConfig.mode = ret;
			break;
		
		case CFG_KEYID_FHRVOICECHANNEL:
			ret = GetIntegerKeyValue(value);
			if (ret < 0 || ret > 1) ret = 0;
			FhrConfig.source = ret;
			break;

		case CFG_KEYID_FHRVOLUME:
			ret = GetIntegerKeyValue(value);
			FhrConfig.volume = (ret & 0x0F);
			break;
		
		case CFG_KEYID_TOCOZEROVALUE:
			ret = GetIntegerKeyValue(value);
			if (ret > 4 || ret < 0) ret = 4;
			FhrConfig.zero = ret;
			break;
		
		case CFG_KEYID_FETALMOVECALC:
			ret = GetIntegerKeyValue(value);
			if (ret < 0 || ret > 1) ret = 0;
			FhrConfig.type = ret;
			break;
		
		case CFG_KEYID_PRINTFAST:
			FhrConfig.fastPrint = GetBooleanKeyValue(value);
			break;

		case CFG_KEYID_PRINTTYPE:
			MonitorConfig.RecorderType = GetRecorderType(value);
			break;
		
		case CFG_KEYID_PRINTSPEED:
			ret = GetIntegerKeyValue(value);
			if (ret < 0 || ret > 2) ret = 0;
			FhrConfig.sweep = ret;
			break;
		case CFG_KEYID_DEFAULTANALYTYPE://用户保存的评分设置默认值:
			ret = GetIntegerKeyValue(value);
			printf("读出默认值defaultAnalyType=%d \n",ret);
			FhrConfig.defaultAnalyType = ret?ret:1;//没有默认值设为NST评分法
			break;

		case CFG_KEYID_PRINTDETACH:
			FhrConfig.detach = GetBooleanKeyValue(value);
			break;
			
		case CFG_KEYID_PRINTLENGTH:
			ret = GetIntegerKeyValue(value);
			if (ret < 0 || ret > 7) ret = 0;
			FhrConfig.printLength = ret;
			break;
		
		case CFG_KEYID_PRINTAUTO:
			FhrConfig.autoPrint = GetBooleanKeyValue(value);
			break;
		
		case CFG_KEYID_PRINTMODE:
			ret = GetIntegerKeyValue(value);
			if (ret < 0 || ret > 2) ret = 0;
			FhrConfig.printMode = ret;
			break;
		
		case CFG_KEYID_PRINTCHROMA:
			ret = GetIntegerKeyValue(value);
			if (ret < 50 || ret > 100) ret = 80;
			RecConfig.chroma = ret;
			break;
		
		case CFG_KEYID_PRINTREGIONSTART:
			ret = GetIntegerKeyValue((UCHAR*)strtok((char*)value, ","));
			if (REC_REGION_FHR210_MAX < ret || REC_REGION_FHR210_MIN > ret)
				ret = REC_REGION_FHR210_112;
			RecConfig.regStar[PAPER_REG_FHR] = ret;

			ret = GetIntegerKeyValue((UCHAR*)strtok(NULL, ","));
			if (REC_REGION_TOCO100_MAX < ret || REC_REGION_TOCO100_MIN > ret)
				ret = REC_REGION_TOCO100_112;
			RecConfig.regStar[PAPER_REG_TOCO] = ret;
			break;
		
		case CFG_KEYID_PRINTREGIONEND:
			ret = GetIntegerKeyValue((UCHAR*)strtok((char*)value, ","));
			if (REC_REGION_FHR60_MAX < ret || REC_REGION_FHR60_MIN > ret)
				ret = REC_REGION_FHR60_112;
			RecConfig.regEnd[PAPER_REG_FHR] = ret;

			ret = GetIntegerKeyValue((UCHAR*)strtok(NULL, ","));
			if (REC_REGION_TOCO0_MAX < ret || REC_REGION_TOCO0_MIN > ret)
				ret = REC_REGION_TOCO0_112;
			RecConfig.regEnd[PAPER_REG_TOCO] = ret;
			break;
		
		case CFG_KEYID_PRINTSCALE:
			RecConfig.isScale = GetBooleanKeyValue(value);
			break;
		
		case CFG_KEYID_PRINTFHRMAX:
			ret = GetIntegerKeyValue(value);
			if (ret < 0 || ret > 1) ret = 0;
			RecConfig.fhrMax = ret;
			break;
		
		case CFG_KEYID_PRINTFHRMIN:
			ret = GetIntegerKeyValue(value);
			if (ret < 0 || ret > 1) ret = 0;
			RecConfig.fhrMin = ret;
			break;
		
		case CFG_KEYID_ANALYTYPE:
			ret = GetIntegerKeyValue(value);
			if (ret < 0 || ret > 2) ret = 0;
			AnalyConfig.type = ret;
			break;

		case CFG_KEYID_ANALYAUTO:
			ret = GetBooleanKeyValue(value);
			if (ret < 0 || ret > 1) ret = 0;
			AnalyConfig.autoFlag = ret;
			break;

#if 0
		case CFG_KEYID_NETWORKCFGFILE:
			break;
		
		case CFG_KEYID_NETWORKAUTO:
			break;
		
		case CFG_KEYID_NETWORKNAME:
			break;
		
		case CFG_KEYID_NETWORKIP:
			break;
		
		case CFG_KEYID_NETWORKMAC:
			break;
		
		case CFG_KEYID_NETWORKSERVER:
			break;
		
		case CFG_KEYID_NETWORKGATEWAY:
			break;
		
		case CFG_KEYID_NETWORKMASK:
			break;
#endif
		
#if _ENB_TOUCH
		case CFG_KEYID_TOUCHCOM:
			MonitorInfo.deviceInfo[DEV_TOUCH].port =
				GetModulePortKeyValue(value);
			break;

		case CFG_KEYID_TOUCHENABLE:
			MonitorInfo.enableTouch = GetBooleanKeyValue(value);
			MonitorConfig.UseTouch = MonitorInfo.enableTouch;
			break;

		case CFG_KEYID_TOUCHCALFLAG:
			MonitorInfo.touchCalFlag = GetBooleanKeyValue(value);
			break;
		
		case CFG_KEYID_TOUCHOFFSETX:
			MonitorConfig.offsetX = GetIntegerKeyValue(value);
			break;
		
		case CFG_KEYID_TOUCHOFFSETY:
			MonitorConfig.offsetY = GetIntegerKeyValue(value);
			break;
		
		case CFG_KEYID_TOUCHSCALEX:
			MonitorConfig.scaleX = GetFloatKeyValue(value);
			break;
		
		case CFG_KEYID_TOUCHSCALEY:
			MonitorConfig.scaleY = GetFloatKeyValue(value);
			break;
#endif
		case CFG_KEYID_SYS_LCBOARD:
			LCSysBoard = GetBooleanKeyValue(value);
			break;

		default:
			break;
	}
	return TRUE;
}

STATUS PutConfigKeyValue(UINT8 *key, UINT8 *value)
{
	int i, kLen;
	kLen = strlen((char*)key);
	//prinfo("key...%s, len = %d\r\n", key, kLen);
	for (i = 0; i < CFG_KEYID_MAX; i++)
	{
		if (siKeyLen[i] == kLen)
		{
			if (memcmp(cszConfKey[i], key, kLen))
				continue;
			return PutConfigKeyValue2(i, value);
		}
	}
	return FALSE;
}

/***********************************************************************************
函数：	Load_Sys_Config
函数功能：将EPROM中的系统配置信息读取到当前系统配置信息中
调用方式：1. 在系统初始化期间，获取系统配置信息
		  2. 在其他时候，确认调用“读取用户配置”
函数功能: 将系统配置EPROM中的全部系统配置信息读取到当前系统配置中
其他说明：
		  本程序不处理缺省配置。
***********************************************************************************/

STATUS  Load_Sys_Config (VOID)
{
	UCHAR key[64], value[64];   // 必须大于配置文件key和value的最大长度
	STATUS status;
	if (!pReadMM) return FALSE;

	pReadMM++;
	while(pReadMM < MemTail)
	{
		pReadMM = GetConfigFileNextKey(pReadMM, MemTail,
										key, sizeof(key), value, sizeof(value));
		if (key[0] == '\0') break;					  // 遇到下一个Section或结尾
		if (key[sizeof(key) - 1] != '\0') continue;	 // 小于最大长度,不能读取
		if (value[sizeof(value) - 1] != '\0') continue; // 小于最大长度,不能读取
		status = PutConfigKeyValue(key, value);
		if (!status)
		{
			return status;
		}
	}
	return TRUE;
}


/***********************************************************************************
函数：	Load_Config
函数功能：将EPROM或者缺省配置信息读入到当前系统配置中
调用方式：在确认执行“读取设置”后调用
调用参数：type：
		  ＝ 0 读入缺省配置
		  ＝ 1 读入E2PROM中用户配置  

其他说明：
		  缺省配置是从程序内存中读入的，其他配置是从EPROM中读入的。
***********************************************************************************/
STATUS  Load_Config (INT8 type)
{
	STATUS  status ;
//	INT16   i;
	if (!type)
	{
		Load_Default_Config(); // 从程序内存中读取缺省配置
		return TRUE;
	}

	// 从EPROM中读取缺省配置
	status = Load_Sys_Config();
	return status;
	
}

BOOL ChangeConfigFile(VOID)
{
	FILE *fp = fopen(USER_TMP_FILE, "wb");
	if (fp)
	{
		//prinfo("strlen(Mem_Map)...%d\r\n", strlen(Mem_Map));
		fwrite(Mem_Map, 1, strlen((char*)Mem_Map), fp);
		flush(fp);
		fclose(fp);
		rename(USER_TMP_FILE, USER_CFG_FILE);
		return TRUE;
	}
	return FALSE;
}

VOID Save_Config2 (INT16 cfg_kid)
{
	UCHAR flag = TRUE;
	CHAR value[64];
	if (cfg_kid == CFG_KEYID_MAX)
	{
		flag = FALSE;
		cfg_kid = 0;
		//ZeroMemory(Mem_Map, USER_CFG_CACHE_SIZE);//首先初始化配置缓冲区。
		//sprintf(Mem_Map, "%s\n", USER_CFG_HEAD);
	}
	switch(cfg_kid)
	{
		case CFG_KEYID_DEFAULTANALYTYPE://用户默认的评分方法在这里保存
			sprintf(value, "%d",FhrConfig.defaultAnalyType);
			
			printf("这里存%s FhrConfig.defaultAnalyType=%d\n",value,FhrConfig.defaultAnalyType);
			PushStrKeyValue(cszConfKey[CFG_KEYID_DEFAULTANALYTYPE], value);
			if (flag) break;
		case CFG_KEYID_MONITORTYPE:
			strcpy(value, MonitorLocalName[MonitorConfig.MonitorName & 0x01]);
			SetMachineName(value);
			PushStrKeyValue(cszConfKey[CFG_KEYID_MONITORTYPE], value);
			if (flag) break;

		case CFG_KEYID_DATETIME_FORMAT:
			PutDatetimeFormat(value);
			PushStrKeyValue(cszConfKey[CFG_KEYID_DATETIME_FORMAT], value);
			if (flag) break;

		case CFG_KEYID_MODULEKEYBOARDONLINE:
			value[1] = '\0';
			value[0] = '0'
				+ (MonitorConfig.moduleInfo[MID_KB].OnLineFalag & 0x01);
			PushStrKeyValue(cszConfKey[CFG_KEYID_MODULEKEYBOARDONLINE], value);
			if (flag) break;

		case CFG_KEYID_MODULEFETALONLINE:
			value[1] = '\0';
			value[0] = '0'
				+ (MonitorConfig.moduleInfo[MID_FHR].OnLineFalag & 0x01);
			PushStrKeyValue(cszConfKey[CFG_KEYID_MODULEFETALONLINE], value);
			if (flag) break;

		case CFG_KEYID_MODULEPRINTERONLINE:
			value[1] = '\0';
			value[0] = '0'
				+ (MonitorConfig.moduleInfo[MID_RECODER].OnLineFalag & 0x01);
			PushStrKeyValue(cszConfKey[CFG_KEYID_MODULEPRINTERONLINE], value);
			if (flag) break;

		case CFG_KEYID_KEYBOARDCOM:
			strcpy(value, "COM1");
			value[3] += MonitorInfo.deviceInfo[DEV_KB].port;
			PushStrKeyValue(cszConfKey[CFG_KEYID_KEYBOARDCOM], value);
			if (flag) break;

		case CFG_KEYID_FETALCOM:
			strcpy(value, "COM1");
			value[3] += MonitorInfo.deviceInfo[DEV_PM].port;
			PushStrKeyValue(cszConfKey[CFG_KEYID_FETALCOM], value);
			if (flag) break;

		case CFG_KEYID_PRINTERCOM:
			strcpy(value, "COM1");
			value[3] += MonitorInfo.deviceInfo[DEV_REC].port;
			PushStrKeyValue(cszConfKey[CFG_KEYID_PRINTERCOM], value);
			if (flag) break;

		case CFG_KEYID_KEYVOLUME:
			value[1] = '\0';
			value[0] = '0' + (MonitorConfig.kbVol & 0x07);
			PushStrKeyValue(cszConfKey[CFG_KEYID_KEYVOLUME], value);
			if (flag) break;

		case CFG_KEYID_LANGUAGE:
			strcpy(value, (char*)LanguageAkaName[MonitorConfig.language][1]);
			PushStrKeyValue(cszConfKey[CFG_KEYID_LANGUAGE], value);
			if (flag) break;

		case CFG_KEYID_NIGHTMODE:
			if (MonitorConfig.nightModeOn)
			{
				strcpy(value, "True");
			}
			else
			{
				strcpy(value, "False");
			}
			PushStrKeyValue(cszConfKey[CFG_KEYID_NIGHTMODE], value);
			if (flag) break;

		case CFG_KEYID_HELPINFO:
			if (MonitorConfig.showHelp)
			{
				strcpy(value, "True");
			}
			else
			{
				strcpy(value, "False");
			}
			PushStrKeyValue(cszConfKey[CFG_KEYID_HELPINFO], value);
			if (flag) break;

		case CFG_KEYID_FACETYPE:
			value[1] = '\0';
			value[0] = '0' + (MonitorConfig.faceType & 0x07);
			PushStrKeyValue(cszConfKey[CFG_KEYID_FACETYPE], value);
			if (flag) break;

		case CFG_KEYID_BEDNUMBER:
			sprintf(value, "%d", MonitorConfig.bedNo);
			PushStrKeyValue(cszConfKey[CFG_KEYID_BEDNUMBER], value);
			if (flag) break;

		case CFG_KEYID_FHR1COLOR:
			//MonitorConfig.colorParam[PARA_BLOCK_FHR1] = BLOCK_FHR1_COLOR; // 参数（和波形）的显示颜色
			sprintf(value, "%d", MonitorConfig.colorParam[PARA_BLOCK_FHR1]);
			PushStrKeyValue(cszConfKey[CFG_KEYID_FHR1COLOR], value);
			if (flag) break;

		case CFG_KEYID_FHR2COLOR:
			//MonitorConfig.colorParam[PARA_BLOCK_FHR2] = BLOCK_FHR2_COLOR; // 参数（和波形）的显示颜色
			sprintf(value, "%d", MonitorConfig.colorParam[PARA_BLOCK_FHR2]);
			PushStrKeyValue(cszConfKey[CFG_KEYID_FHR2COLOR], value);
			if (flag) break;

		case CFG_KEYID_TOCOCOLOR:
			//MonitorConfig.colorParam[PARA_BLOCK_TOCO] = BLOCK_TOCO_COLOR; // 参数（和波形）的显示颜色
			sprintf(value, "%d", MonitorConfig.colorParam[PARA_BLOCK_TOCO]);
			PushStrKeyValue(cszConfKey[CFG_KEYID_TOCOCOLOR], value);
			if (flag) break;

		case CFG_KEYID_FMCOLOR:
			//MonitorConfig.colorParam[PARA_BLOCK_FM]   = BLOCK_AFM_COLOR;  // 参数（和波形）的显示颜色
			sprintf(value, "%d", MonitorConfig.colorParam[PARA_BLOCK_FM]);
			PushStrKeyValue(cszConfKey[CFG_KEYID_FMCOLOR], value);
			if (flag) break;

		case CFG_KEYID_ALARMFHRHI:
			sprintf(value, "%d", FhrConfig.FhrAlarmLimitHi);
			PushStrKeyValue(cszConfKey[CFG_KEYID_ALARMFHRHI], value);
			if (flag) break;

		case CFG_KEYID_ALARMFHRLO:
			sprintf(value, "%d", FhrConfig.FhrAlarmLimitLo);
			PushStrKeyValue(cszConfKey[CFG_KEYID_ALARMFHRLO], value);
			if (flag) break;

		case CFG_KEYID_ALARMSWITCH:
			value[1] = '\0';
			value[0] = '0' + (FhrConfig.alarm & 0x01);
			PushStrKeyValue(cszConfKey[CFG_KEYID_ALARMSWITCH], value);
			if (flag) break;

		case CFG_KEYID_ALARMVOLUME:
			value[1] = '\0';
			value[0] = '0' + (MonitorConfig.alarmVolume & 0x07);
			PushStrKeyValue(cszConfKey[CFG_KEYID_ALARMVOLUME], value);
			if (flag) break;

		case CFG_KEYID_ALARMSILENCE:
			if (MonitorConfig.alarmSoundOn)
			{
				strcpy(value, "True");
			}
			else
			{
				strcpy(value, "False");
			}
			PushStrKeyValue(cszConfKey[CFG_KEYID_ALARMSILENCE], value);
			if (flag) break;

		case CFG_KEYID_FETALMODE:
			value[1] = '\0';
			value[0] = '0' + (FhrConfig.mode & 0x03);
			PushStrKeyValue(cszConfKey[CFG_KEYID_FETALMODE], value);
			if (flag) break;

		case CFG_KEYID_FHRVOICECHANNEL:
			value[1] = '\0';
			value[0] = '0' + (FhrConfig.source & 0x01);
			PushStrKeyValue(cszConfKey[CFG_KEYID_FHRVOICECHANNEL], value);
			if (flag) break;

		case CFG_KEYID_FHRVOLUME:
			value[1] = '\0';
			value[0] = '0' + (FhrConfig.volume & 0x0F);
			PushStrKeyValue(cszConfKey[CFG_KEYID_FHRVOLUME], value);
			if (flag) break;

		case CFG_KEYID_TOCOZEROVALUE:
			value[1] = '\0';
			value[0] = '0' + (FhrConfig.zero & 0x07);
			PushStrKeyValue(cszConfKey[CFG_KEYID_TOCOZEROVALUE], value);
			if (flag) break;

		case CFG_KEYID_FETALMOVECALC:
			value[1] = '\0';
			value[0] = '0' + (FhrConfig.type & 0x01);
			PushStrKeyValue(cszConfKey[CFG_KEYID_FETALMOVECALC], value);
			if (flag) break;

		case CFG_KEYID_PRINTFAST:
			value[1] = '\0';
			value[0] = '0' + (FhrConfig.fastPrint & 0x01);
			PushStrKeyValue(cszConfKey[CFG_KEYID_PRINTFAST], value);
			if (flag) break;

		case CFG_KEYID_PRINTTYPE:
			strcpy(value, PrinterTypeName[MonitorConfig.RecorderType]);
			PushStrKeyValue(cszConfKey[CFG_KEYID_PRINTTYPE], value);
			if (flag) break;

		case CFG_KEYID_PRINTSPEED:
			value[1] = '\0';
			value[0] = '0' + (FhrConfig.sweep & 0x03);
			PushStrKeyValue(cszConfKey[CFG_KEYID_PRINTSPEED], value);
			if (flag) break;

		case CFG_KEYID_PRINTDETACH:
			if (FhrConfig.detach)
			{
				strcpy(value, "True");
			}
			else
			{
				strcpy(value, "False");
			}
			PushStrKeyValue(cszConfKey[CFG_KEYID_PRINTDETACH], value);
			if (flag) break;

		case CFG_KEYID_PRINTLENGTH:
			value[1] = '\0';
			value[0] = '0' + (FhrConfig.printLength & 0x0F);
			PushStrKeyValue(cszConfKey[CFG_KEYID_PRINTLENGTH], value);
			if (flag) break;

		case CFG_KEYID_PRINTAUTO:
			value[1] = '\0';
			value[0] = '0' + (FhrConfig.autoPrint & 0x01);
			PushStrKeyValue(cszConfKey[CFG_KEYID_PRINTAUTO], value);
			if (flag) break;

		case CFG_KEYID_PRINTMODE:
			value[1] = '\0';
			value[0] = '0' + (FhrConfig.printMode & 0x03);
			PushStrKeyValue(cszConfKey[CFG_KEYID_PRINTMODE], value);
			if (flag) break;

		case CFG_KEYID_PRINTCHROMA:
			sprintf(value, "%d", RecConfig.chroma);
			PushStrKeyValue(cszConfKey[CFG_KEYID_PRINTCHROMA], value);
			if (flag) break;

		case CFG_KEYID_PRINTREGIONSTART:
			sprintf(value, "%ld,%ld", RecConfig.regStar[PAPER_REG_FHR],
									 RecConfig.regStar[PAPER_REG_TOCO]);
			PushStrKeyValue(cszConfKey[CFG_KEYID_PRINTREGIONSTART], value);
			if (flag) break;

		case CFG_KEYID_PRINTREGIONEND:
			sprintf(value, "%ld,%ld", RecConfig.regEnd[PAPER_REG_FHR],
									 RecConfig.regEnd[PAPER_REG_TOCO]);
			PushStrKeyValue(cszConfKey[CFG_KEYID_PRINTREGIONEND], value);
			if (flag) break;

		case CFG_KEYID_PRINTSCALE:
			value[1] = '\0';
			value[0] = '0' + (RecConfig.isScale & 0x01);
			PushStrKeyValue(cszConfKey[CFG_KEYID_PRINTSCALE], value);
			if (flag) break;

		case CFG_KEYID_PRINTFHRMAX:
			value[1] = '\0';
			value[0] = '0' + (RecConfig.fhrMax & 0x01);
			PushStrKeyValue(cszConfKey[CFG_KEYID_PRINTFHRMAX], value);
			if (flag) break;

		case CFG_KEYID_PRINTFHRMIN:
			value[1] = '\0';
			value[0] = '0' + (RecConfig.fhrMin & 0x01);
			PushStrKeyValue(cszConfKey[CFG_KEYID_PRINTFHRMIN], value);
			if (flag) break;

		case CFG_KEYID_ANALYTYPE:
			value[1] = '\0';
			value[0] = '0' + (AnalyConfig.type & 0x03);
			PushStrKeyValue(cszConfKey[CFG_KEYID_ANALYTYPE], value);
			if (flag) break;

		case CFG_KEYID_ANALYAUTO:
			if (AnalyConfig.autoFlag)
			{
				strcpy(value, "True");
			}
			else
			{
				strcpy(value, "False");
			}
			PushStrKeyValue(cszConfKey[CFG_KEYID_ANALYTYPE], value);
			if (flag) break;

		case CFG_KEYID_NETWORKCFGFILE:
			value[0] = '\0';
			PushStrKeyValue(cszConfKey[CFG_KEYID_NETWORKCFGFILE], value);
			if (flag) break;

		case CFG_KEYID_NETWORKAUTO:
			value[0] = '\0';
			PushStrKeyValue(cszConfKey[CFG_KEYID_NETWORKAUTO], value);
			if (flag) break;

		case CFG_KEYID_NETWORKNAME:
			strcpy(value, NETWORK_CONFIG_FILE);
			PushStrKeyValue(cszConfKey[CFG_KEYID_NETWORKNAME], value);
			if (flag) break;

		case CFG_KEYID_NETWORKIP:
			value[0] = '\0';
			PushStrKeyValue(cszConfKey[CFG_KEYID_NETWORKIP], value);
			if (flag) break;

		case CFG_KEYID_NETWORKMAC:
			value[0] = '\0';
			PushStrKeyValue(cszConfKey[CFG_KEYID_NETWORKMAC], value);
			if (flag) break;

		case CFG_KEYID_NETWORKSERVER:
			value[0] = '\0';
			PushStrKeyValue(cszConfKey[CFG_KEYID_NETWORKSERVER], value);
			if (flag) break;

		case CFG_KEYID_NETWORKGATEWAY:
			value[0] = '\0';
			PushStrKeyValue(cszConfKey[CFG_KEYID_NETWORKGATEWAY], value);
			if (flag) break;

		case CFG_KEYID_NETWORKMASK:
			value[0] = '\0';
			PushStrKeyValue(cszConfKey[CFG_KEYID_NETWORKMASK], value);
			if (flag) break;

#if _ENB_TOUCH
		case CFG_KEYID_TOUCHCOM:
			strcpy(value, "COM1");
			value[3] += MonitorInfo.deviceInfo[DEV_TOUCH].port;
			PushStrKeyValue(cszConfKey[CFG_KEYID_TOUCHCOM], value);
			if (flag) break;

		case CFG_KEYID_TOUCHENABLE:
			if (MonitorInfo.enableTouch)
			{
				strcpy(value, "True");
			}
			else
			{
				strcpy(value, "False");
			}
			PushStrKeyValue(cszConfKey[CFG_KEYID_TOUCHENABLE], value);
			if (flag) break;

		case CFG_KEYID_TOUCHCALFLAG:
			if (MonitorInfo.touchCalFlag)
			{
				strcpy(value, "True");
			}
			else
			{
				strcpy(value, "False");
			}
			PushStrKeyValue(cszConfKey[CFG_KEYID_TOUCHCALFLAG], value);
			if (flag) break;

		case CFG_KEYID_TOUCHOFFSETX:
			sprintf(value, "%d", MonitorConfig.offsetX);
			PushStrKeyValue(cszConfKey[CFG_KEYID_TOUCHOFFSETX], value);
			if (flag) break;

		case CFG_KEYID_TOUCHOFFSETY:
			sprintf(value, "%d", MonitorConfig.offsetY);
			PushStrKeyValue(cszConfKey[CFG_KEYID_TOUCHOFFSETY], value);
			if (flag) break;

		case CFG_KEYID_TOUCHSCALEX:
			sprintf(value, "%.6f", MonitorConfig.scaleX);
			PushStrKeyValue(cszConfKey[CFG_KEYID_TOUCHSCALEX], value);
			if (flag) break;

		case CFG_KEYID_TOUCHSCALEY:
			sprintf(value, "%.6f", MonitorConfig.scaleY);
			PushStrKeyValue(cszConfKey[CFG_KEYID_TOUCHSCALEY], value);
			if (flag) break;
#endif

		case CFG_KEYID_SYS_LCBOARD:
			sprintf(value, "%d", LCSysBoard);
			PushStrKeyValue(cszConfKey[CFG_KEYID_SYS_LCBOARD], value);
			if (flag) break;

		default:
			break;
	}
}

VOID Save_Config (INT16 cfg_kid)
{
	Save_Config2(cfg_kid);
	ChangeConfigFile();
}

VOID Save_Touch_Config(VOID)
{
	int i;
	for (i = CFG_KEYID_TOUCHCOM /*CFG_KEYID_TOUCHENABLE*/; i <= CFG_KEYID_TOUCHSCALEY; i++)
	{
		Save_Config2(i);
	}
	ChangeConfigFile();
}

VOID Save_Record_Config(INT16 info_ndx,INT8 type)
{
	int i;
	if (info_ndx < CFG_KEYID_PRINTFAST || info_ndx > CFG_KEYID_PRINTFHRMIN)
	{
		for (i = CFG_KEYID_PRINTFAST; i <= CFG_KEYID_PRINTFHRMIN; i++)
		{
			Save_Config2(i);
		}
	}
	else
	{
		Save_Config2(info_ndx);
	}
	if (!type)
		return;
	ChangeConfigFile();
}

VOID Save_Fetal_Config(INT16 info_ndx,INT8 type)
{
	int i;
	if (info_ndx < CFG_KEYID_ALARMFHRHI || info_ndx > CFG_KEYID_PRINTMODE)
	{
		for (i = CFG_KEYID_ALARMFHRHI; i <= CFG_KEYID_PRINTMODE; i++)
		{
			Save_Config2(i);
		}
	}
	else
	{
		Save_Config2(info_ndx);
	}
	if (type)
		return;
	ChangeConfigFile();
}

VOID Load_DefCfg_Fetal(VOID)
{
	FhrConfig.enbFhr1		   = TRUE;
	FhrConfig.enbFhr2		   = TRUE;
	FhrConfig.enbToco		   = TRUE;
	FhrConfig.enbAfm			= TRUE;
	FhrConfig.alarm			 = ON;
	FhrConfig.alarmRec		  = OFF;
	FhrConfig.alarmLevel		= 1;
	FhrConfig.mode			  = 0;
	FhrConfig.volume			= 5;
	FhrConfig.source			= 0;
	FhrConfig.sweep			 = 2;
	FhrConfig.detach			= 0;
	FhrConfig.zero			  = 4;
	FhrConfig.type			  = 0;
	FhrConfig.threshold		 = 0;
	FhrConfig.movement_calc	 = 0;
	FhrConfig.FhrAlarmLimitHi   = 160;
	FhrConfig.FhrAlarmLimitLo   = 120;
	FhrConfig.fastPrint		 = 1;
	FhrConfig.autoPrint		 = 0;
	FhrConfig.printMode		 = 0;
	FhrConfig.printLength	   = 3;
}

static VOID Load_DefCfg_RecPT1561P(VOID)
{
	RecConfig.regStar[PAPER_REG_FHR] = REC_REGION_FHR210_1561;
	RecConfig.regStar[PAPER_REG_TOCO] = REC_REGION_TOCO100_1561;
	RecConfig.regEnd[PAPER_REG_FHR] = REC_REGION_FHR60_1561;
	RecConfig.regEnd[PAPER_REG_TOCO] = REC_REGION_TOCO0_1561;
}


static VOID Load_DefCfg_Rec112(VOID)
{
	RecConfig.regStar[PAPER_REG_FHR] = REC_REGION_FHR210_112;
	RecConfig.regStar[PAPER_REG_TOCO] = REC_REGION_TOCO100_112;
	RecConfig.regEnd[PAPER_REG_FHR] = REC_REGION_FHR60_112;
	RecConfig.regEnd[PAPER_REG_TOCO] = REC_REGION_TOCO0_112;
	RecConfig.chroma = 80;
	RecConfig.fhrMax = 0;
	RecConfig.fhrMin = 0;
}

VOID Load_DefCfg_Recorder(VOID)
{
	if (MonitorConfig.RecorderType == PAPER_TYPE_112MM)
	{
		Load_DefCfg_Rec112();
	}
	else
	{
		Load_DefCfg_RecPT1561P();
	}
	RecConfig.fhrMax = 0;
	RecConfig.fhrMin = 0;
}

VOID Load_DefCfg_Touch(VOID)
{
	MonitorInfo.enableTouch = MonitorConfig.UseTouch;
	MonitorInfo.touchCalFlag = FALSE;
}

VOID Load_DefCfg_Monitor(BOOL setup)
{
	if (FALSE == setup)
	{
		MonitorConfig.showHelp	= TRUE;			// 是否显示菜单的帮助信息: TRUE
		MonitorConfig.showAlarmLimits = FALSE;	  // 是否显示报警限: 不显示
		MonitorConfig.brightness  = 4;			   // 屏幕亮度
		MonitorConfig.alarmWaveRecordLength = 0 ;// 报警波形记录时间长度：8秒
		ConfigBackup.recWave1Name   = 0;
		ConfigBackup.recWave2Name   = 0;
		MonitorConfig.recRTMode	 = 1;					 // 实时记录的波形长度: 1：8秒
		MonitorConfig.recPeriod	 = 0;					  // 定时记录的定时间隔：关闭
		MonitorConfig.recSweepSpeed = 0;					 // 记录速度 0：25mm/s
		MonitorConfig.recDrawGrid   = TRUE ;				  // 记录输出网格: TRUE：是
		MonitorConfig.analogOutputEnabled = TRUE;			 // 模拟输出是否打开: TRUE：是
		ConfigBackup.anaWaveName		  = 0;

		MonitorConfig.colorParam[PARA_BLOCK_FHR1] = BLOCK_FHR1_COLOR; // 参数（和波形）的显示颜色
		MonitorConfig.colorParam[PARA_BLOCK_FHR2] = BLOCK_FHR2_COLOR; // 参数（和波形）的显示颜色
		MonitorConfig.colorParam[PARA_BLOCK_TOCO] = BLOCK_TOCO_COLOR; // 参数（和波形）的显示颜色
		MonitorConfig.colorParam[PARA_BLOCK_FM]   = BLOCK_AFM_COLOR;  // 参数（和波形）的显示颜色
		//  Load default HT. & WT. unit.
		MonitorConfig.heightUnit = 0;
		MonitorConfig.weightUnit = 0;
		MonitorConfig.language = DEFAULT_LANGUAGE;
		MonitorConfig.bedNo = BEDNO_INVALID;
		MonitorInfo.backToBigFontFace = FALSE;
		MonitorConfig.patientIsPace = FALSE;	//病人没有装起搏器.
		MonitorConfig.moduleInfo[MID_KB].OnLineFalag = TRUE;
		MonitorConfig.moduleInfo[MID_FHR].OnLineFalag = TRUE;
		MonitorConfig.moduleInfo[MID_RECODER].OnLineFalag = TRUE;

		MonitorConfig.MonitorName = MONITOR_TYPE_AR4S;
		MonitorConfig.RecorderType = PAPER_TYPE_112MM;
		MonitorConfig.UseTouch = FALSE;
	}
	MonitorConfig.kbVol	   = KB_VOL_MED;	  // 键盘音量
	MonitorConfig.nightModeOn = TRUE;		  // 夜间模式是否打开: FALSE
	MonitorConfig.showHelp	= TRUE;

	MonitorConfig.faceType	= FACE_STD;		  // 基本界面类型：标准；
	MonitorConfig.alarmVolume = ALM_VOL_MED;	   // 报警音量：中
	ConfigBackup.alarmVolume  = ALM_VOL_MED;			  // 报警音量：中
	MonitorConfig.alarmSuspendTime = ALM_SUSPEND_2min;	// 报警挂起时间长度：2分钟
	MonitorConfig.alarmLatched	 = FALSE ;			  // 报警是否栓锁：否

	MonitorConfig.kbVol = KB_VOL_MED;
	MonitorConfig.alarmSoundOn = ON;
	MonitorConfig.faceType = FACE_STD;

	MonitorInfo.deviceInfo[DEV_KB].port = COM1;
	MonitorInfo.deviceInfo[DEV_PM].port = COM3;
	if(MonitorConfig.MonitorName != MONITOR_TYPE_AR4S){
    	MonitorInfo.deviceInfo[DEV_TOUCH].port = COM9;  //artemis2
    	MonitorInfo.deviceInfo[DEV_REC].port = COM4;    //artemis2
    	printf("MonitorConfig.MonitorName = %d\n",MonitorConfig.MonitorName);
	}
	else
	{
    	MonitorInfo.deviceInfo[DEV_TOUCH].port = COM8; //artemis4
    	MonitorInfo.deviceInfo[DEV_REC].port = COM9;   //artemis4
	}
	MonitorInfo.deviceInfo[DEV_NET].port = 2014;
	
	MonitorConfig.date_delimiter = '-';
	MonitorConfig.date_format_type = FORMAT_YYYY_MM_DD;
	MonitorConfig.time_delimiter = ':';
	MonitorConfig.time_format_type = FORMAT_HH_MM_SS;
}

/***********************************************************************************
函数：	Load_Default_Config
函数功能：用来读取缺省配置的各选项到当前配置数据结构中
调用方式：在确认执行“缺省设置”后调用
***********************************************************************************/

VOID  Load_Default_Config(VOID)
{
	Load_DefCfg_Monitor(FALSE);
	Load_DefCfg_Fetal();
	Load_DefCfg_Recorder();
}


/***********************************************************************************
函数：	Set_Module_Alarm_OnLoad( INT16 moduleid )
函数功能：对模块参数报警进行相关设置; called by GUI Task
调用方式：在模块加载完毕
调用参数：
		  moduleid:
			表示 ECG, SPO2, NIBP, TEMP, IBP,  等模块
其他说明：RR参数此处包含在ECG模块中
***********************************************************************************/

VOID  Set_Module_Alarm_OnLoad (INT16 moduleid)
{
	INT16 i ;

	for (i = 0 ; i < ALM_PARA_MAX ; i++) 
	{
		if (ParaAlarmInfo[i].ModuleID == moduleid) 
		{			
			ParaAlarmInfo[i].IsLoad = TRUE; // 置位相应的加载标志
		}
	}
}

/***********************************************************************************
函数：	Set_Module_Alarm_OnUnLoad( INT16 moduleid )
函数功能：对模块参数报警进行相关设置; called by GUI Task
调用方式：在模块卸载完毕
调用参数：
		  moduleid:
			表示 ECG, SPO2, NIBP, TEMP, IBP, CO,  等模块
其他说明：RR参数此处包含在ECG模块中
***********************************************************************************/

VOID  Set_Module_Alarm_OnUnLoad (INT16 moduleid)
{
	INT16 i ;

	for (i = 0 ; i < ALM_PARA_MAX; i++) {
		if (ParaAlarmInfo[i].ModuleID == moduleid) {
			ParaAlarmInfo[i].IsLoad = FALSE;// 清除所有相关的内容
		}
	}
}

VOID  InitRedundantStore (VOID)
{
}

/**********************************************************************************
函数：	Para_Alarm_Judge_Int()
函数功能：对模块整型参数进行报警判断
调用方式：在1s中断处理Para_Alarm_Judge函数中调用;由于和报警模块在一个任务中,不用消息传递.
调用参数：
		  paraid:	   参数代码
		  high:		 报警上限
		  low:		  报警下限
		  paravalue:	参数值
返回：
		  TRUE		  返回正确
		  FALSE		 返回错误

***********************************************************************************/
STATUS  Para_Alarm_Judge_Int (INT16 paraid, INT16 high, INT16 low, INT16 paravalue)
{
   INT16  tmp;
	
   if (ParaAlarmInfo[paraid].AlarmLimitIsChangingFlag)
	  return TRUE;

	// 首先判断报警限是否与冗余存储的报警限一致，如不一致，返回错误
	if (0) {

		TriggerAlarm2(0x0001, ParaAlarmInfo[paraid].LimitErrStr);
		TriggerAlarm2(0x0000, ParaAlarmInfo[paraid].HighStr);
		TriggerAlarm2(0x0000, ParaAlarmInfo[paraid].LowStr);
//		prinfo("%s\n", LoadString(ParaAlarmInfo[paraid].LimitErrStr));
		return  ERROR_IN_COMPARE_STORAGE;
	} else {
		TriggerAlarm2(0x0000, ParaAlarmInfo[paraid].LimitErrStr);
	}

	// 有的数据虽然是整数值,但是发到了10倍,甚至100倍;在和无效值比较前,必须缩小;
	if (ParaRedundantInfo[paraid].type == INT_X10)
		tmp = paravalue / 10;
	else if (ParaRedundantInfo[paraid].type == INT_X100)
		tmp = paravalue / 100;
	else
		tmp = paravalue;

	// 如果参数是无效数值，关闭报警，返回
	if ((tmp == INVALID_PARAM_INT)
		 ||(tmp == UNKNOWN_PARAM)
		 ||(tmp == PARAM_MODULE_NOT_EXIST)
		 ||(tmp == 0)
		 )
	{
		TriggerAlarm2(0x0000, ParaAlarmInfo[paraid].HighStr);
		TriggerAlarm2(0x0000, ParaAlarmInfo[paraid].LowStr);

		return TRUE ;
	}

	// 是否符合了报警条件
	if (paravalue > high) {
		TriggerAlarm2(0x0001, ParaAlarmInfo[paraid].HighStr);
		TriggerAlarm2(0x0000, ParaAlarmInfo[paraid].LowStr);
//		prinfo("%s\n", LoadString(ParaAlarmInfo[paraid].HighStr));
	} else if (paravalue < low) {
		TriggerAlarm2(0x0000, ParaAlarmInfo[paraid].HighStr);
		TriggerAlarm2(0x0001, ParaAlarmInfo[paraid].LowStr);
//		prinfo("%s\n", LoadString(ParaAlarmInfo[paraid].LowStr));
	} else {
		TriggerAlarm2(0x0000, ParaAlarmInfo[paraid].HighStr);
		TriggerAlarm2(0x0000, ParaAlarmInfo[paraid].LowStr);
	}

	return TRUE ;
}


/**********************************************************************************
函数：	Para_Alarm_Judge()
函数功能：对模块参数进行报警判断
调用方式：在1s, data Process task 中进行
调用参数：无
返回：
		  TRUE		  返回正确
		  FALSE		 返回错误
***********************************************************************************/

STATUS  Para_Alarm_Judge (VOID)
{
//	INT16   i , channel;
	BOOL	bStatus = TRUE ;
//	FLOAT   high, low;

    //printf("ZT:FhrConfig.mode = %d\n",FhrConfig.mode);
    if (FhrConfig.mode != 1){
    	bStatus &= Para_Alarm_Judge_Int(ALM_PARA_FHR1,
    									FhrConfig.FhrAlarmLimitHi,
    									FhrConfig.FhrAlarmLimitLo,
    									FhrParams.fhr1);
    }
    if (FhrConfig.mode > 0){
    	bStatus &= Para_Alarm_Judge_Int(ALM_PARA_FHR2,
    									FhrConfig.FhrAlarmLimitHi,
    									FhrConfig.FhrAlarmLimitLo,
    									FhrParams.fhr2);
    }

	// 如果某个参数报警判断出现错误，返回错误
	return bStatus;
}

/**********************************************************************************
函数：	InitConfigWhoHasNoDefaultValue
函数功能：初始化没有缺省值的系统配置
调用方式：在InitConfig中调用
调用参数：无
返回：	无
***********************************************************************************/
VOID  InitConfigWhoHasNoDefaultValue (VOID)
{
//	INT i;

	// 以下这些设置没有缺省配置,不进行重新设置
	MonitorConfig.dateTime.year		= 2014;	// 系统时间－－－年
	MonitorConfig.dateTime.month		= 3;	// 系统时间－－－月
	MonitorConfig.dateTime.day		= 31;	// 系统时间－－－日
	MonitorConfig.dateTime.hour		= 23;	// 系统时间－－－时
	MonitorConfig.dateTime.minute	= 59;	// 系统时间－－－分
	MonitorConfig.dateTime.second	= 59;	// 系统时间－－－秒

	MonitorConfig.vgasize = VGA_TFT_12INCH;

	MonitorConfig.language  = DEFAULT_LANGUAGE;// 语言类型/*CHINESE*/

	/* 从配置信息中读取波形的分布信息，此时要求配置信息中必须有默认值*/
	MonitorConfig.moduleInfo[MID_KB].OnLineFalag		 = TRUE;
	MonitorConfig.moduleInfo[MID_FHR].OnLineFalag		= TRUE;
	MonitorConfig.moduleInfo[MID_RECODER].OnLineFalag	= TRUE;
	/*the end*/ 

	MonitorConfig.bedNo			= BEDNO_INVALID;
	MonitorConfig.sex			= 2;	// 病人性别   
	MonitorConfig.bloodType		= BLOOD_INVALID;  // 血型
	MonitorConfig.drawWaveMode	= 1;			  // 波形画法

	MonitorConfig.patientType = PATIENT_ADULT;

#if _ENB_TOUCH > 0
	MonitorConfig.offsetX	= 155;					
	MonitorConfig.scaleX		= 2.323333;				   
	MonitorConfig.offsetY	= 74;						
	MonitorConfig.scaleY		= 3.061250;					
	MonitorInfo.touchCalFlag	= FALSE;					  //add by empty 2011/04/21 
#endif

	ZeroMemory(&MonitorConfig.department[0],  13);
	ZeroMemory(&MonitorConfig.patientNum[0],  32);
	ZeroMemory(&MonitorConfig.doctorName[0],  13);
	ZeroMemory(&MonitorConfig.patientName[0], 32);
	sprintf((char*)Mem_Map, "[%s]\n", USER_CFG_HEAD);
}


/**********************************************************************************
函数：	InitUserConfig
函数功能：初始化系统配置，判断系统是否为第一次运行（EEPROM中没有标志），
		  如果是，保存3种厂家缺省配置为相应的用户缺省配置，初始化当前配置
		  为厂家缺省成人配置;

说明:
		  系统初始化调用时,任务环境还没有建立.所以,不能调用有OS系统接口.
		  在这之前,必须对E2PROM首先进行初始化.
		  在这之前,必须对系统环境进行初始化. 读m1000.ini文件,对FuncConfig进行
		  初始化.
		  
调用方式：系统初始化时调用一次
调用参数：force_init -- 是否强行初始化所有配置而不判断系统是否已经初始化
返回：
		  TRUE	  系统是第一次运行
		  FALSE	 系统不是第一次运行
***********************************************************************************/
BOOL  InitUserConfig (BOOL force_init)
{
	/* TODO: 读取配置文件 */
	if (force_init)
	{  // not init
		#if ENB_ENCRYPT_FILE
		Mem_Checksum = 0;
		#endif
		InitConfigWhoHasNoDefaultValue();
		// current configuration is Default adult
		Load_Config(FALSE);
		ClearPatientInfo();
		MonitorConfig.patientType = PATIENT_ADULT;   
		Save_Config(CFG_KEYID_MAX);
		FirstBoot = TRUE;
		return TRUE;
	}
	else
	{
		if (!Load_Config(TRUE))
		{
#if ENB_ENCRYPT_FILE
			Mem_Checksum = 0;
#endif
			InitConfigWhoHasNoDefaultValue();
			// current configuration is Default adult
			Load_Config(FALSE);
			ClearPatientInfo();
			MonitorConfig.patientType = PATIENT_ADULT;   
			FhrConfig.alarmLevel		= 1;
			Save_Config(CFG_KEYID_MAX);
			return TRUE;
		}
		Save_Config(CFG_KEYID_MAX);
		return FALSE;
	}
}


