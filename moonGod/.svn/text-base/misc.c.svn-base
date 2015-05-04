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

#define   MISC_GLOBALS 
#include  "includes.h"

#if 0
#define INIFILENAME "monitor.ini"
char	INIFILEPATH [MAX_PATH + 1];

/**
*  \brief  从运行环境中得到配置文件的目录;不同环境要求不同;比如dos和unix,目前系统中无须处理。
*		  配置文件+目录, 最后保存到ETCFILEPATH中;
**/
static BOOL LookForIniFile (void)
{
	strcpy(INIFILEPATH, INIFILENAME);
	return TRUE;
}

BOOL InitMisc (void)
{
	if (!LookForIniFile ())
	{
		errprintf("Monitor: Can not locate your monitor.ini file or bad files!\n");
		return FALSE;
	}

	return TRUE;
}
#endif
/****************************** INI file support ******************************/

// This function locate the specified section in the ini file.
static INT32 ini_LocateSection(FILE* fp, const char* pSection, FILE* bak_fp)
{
	char  szBuff[INI_MAXLINE + 1];
	char* current;
	char* tail;

	while (TRUE) {
		if (!fgets(szBuff, INI_MAXLINE, fp)) {
			if (feof (fp))
				return INI_SECTIONNOTFOUND;
			else
				return INI_FILEIOFAILED;
		}
		else if (bak_fp && fputs (szBuff, bak_fp) == EOF)
			return INI_FILEIOFAILED;
		
		current = szBuff;

		while (*current == ' ' ||  *current == '\t') current++; 

		if (*current == ';' || *current == '#') continue;

		if (*current++ == '[') 
			while (*current == ' ' ||  *current == '\t') current ++;
		else
			continue;

		// Locate the tail.
		tail = current;
		while (*tail != ']' && *tail != '\n' &&
			  *tail != ';' && *tail != '#' && *tail != '\0')
			  tail++;
		*tail = '\0';
		while (*tail == ' ' || *tail == '\t') {
			*tail = '\0';
			tail--; 
		}
			
		if (strcmp (current, pSection) == 0)
			return INI_OK; 
	}
}

// This function locate the specified key in the ini file.
static INT32 ini_LocateKeyValue(FILE* fp, const char* pKey, 
								BOOL bCurSection, char* pValue, INT32 iLen,
								FILE* bak_fp, char* nextSection)
{
	char   szBuff[INI_MAXLINE + 1 + 1];
	char * current;
	char * tail;
	char * value;

	while (TRUE) {
		if (!fgets(szBuff, INI_MAXLINE, fp))
			return INI_FILEIOFAILED;
		if (szBuff [strlen (szBuff) - 1] == '\n')
			szBuff [strlen (szBuff) - 1] = '\0';
		current = szBuff;

		while (*current == ' ' ||  *current == '\t') current++; 

		if (*current == ';' || *current == '#') continue;

		if (*current == '[') {
			if (bCurSection) {
				strcpy (nextSection, current);
				return INI_KEYNOTFOUND; 
			}
			else
				continue;
		}

		tail = current;
		while (*tail != '=' && *tail != '\n' &&
			  *tail != ';' && *tail != '#' && *tail != '\0')
			  tail++;

		value = tail + 1;
		if (*tail != '=')
			*value = '\0'; 

		*tail-- = '\0';
		while (*tail == ' ' || *tail == '\t') {
			*tail = '\0';
			tail--; 
		}
			
		if (strcmp (current, pKey) == 0) {
			tail = value;
			while (*tail != '\n' && *tail != '\0') tail++;
			*tail = '\0'; 

			if (pValue)
				strncpy (pValue, value, iLen);

			return INI_OK; 
		}
		else if (bak_fp && *current != '\0')
			fprintf (bak_fp, "%s=%s\n", current, value);
	}
}

static INT32 GUIAPI ini_GetKeyValUntilEnd(FILE *fp, char *pKey,
											BOOL bCurSection, long *pValue)
{
	char   szBuff[INI_MAXLINE + 1 + 1];
	char * current;
	char * tail;
	char * value;
	*pKey   = '\0';
	*pValue = '\0';
	if (!fgets(szBuff, INI_MAXLINE, fp)) return INI_FILEIOFAILED;
	// fgets 会自动转换行末'\n'为'\0',mark by gjl
	//if (szBuff [strlen (szBuff) - 1] == '\n')
	//	szBuff [strlen (szBuff) - 1] = '\0';
	current = szBuff;
	
	while (*current == ' ' ||  *current == '\t') current++; 
	
	if (*current == ';' || *current == '#') return INI_OK;
	
	if (*current == '[')
	{
		if (bCurSection)
		{
			return INI_KEYNOTFOUND; 
		}
		else
		{
			return INI_OK;
		}
	}

	tail = current;
	while (*tail != '=' && *tail != '\n' &&
		  *tail != ';' && *tail != '#' && *tail != '\0')
	{
		  tail++;
	}
	
	value = tail + 1;
	if (*tail != '=') *value = '\0'; 
	
	*tail-- = '\0';
	
	while (*tail == ' ' || *tail == '\t')
	{
		*tail = '\0';
		tail--; 
	}
	// 复制到key
	strcpy(pKey, current);
	
	tail = value;
	
	while (*tail != '\n' && *tail != '\0') tail++;
	
	*tail = '\0'; 

	if (pValue) strcpy ((char*)pValue, value);

	return INI_OK; 
}


/* Function: GetValueFromIniFile(const char* pIniFile, const char* pSection,
 *							   const char* pKey, char* pValue, INT32 iLen);
 * Parameter:
 *	 pIniFile: ini file path name.
 *	 pSection: Section name.
 *	 pKey:	 Key name.
 *	 pValue:   The buffer will store the value of the key.
 *	 iLen:	 The max length of value string.
 * Return:
 *	 INT32			   meaning
 *	 INI_FILENOTFOUND		   The ini file not found. 
 *	 INI_SECTIONNOTFOUND		The section is not found. 
 *	 ETC_EKYNOTFOUND		The Key is not found.
 *	 INI_OK			OK.
 */
INT32 GUIAPI GetValueFromIniFile(const char* pIniFile, const char* pSection,
								 const char* pKey, char* pValue, long iLen)
{
	FILE* fp;
	char tempSection [INI_MAXLINE + 2];

	fp = fopen(pIniFile, "r");
	if (!fp)
		 return INI_FILENOTFOUND;

	//首先定位SECTION段的位置；
	if (pSection) 
	{
		if (ini_LocateSection (fp, pSection, NULL) != INI_OK)
		{
			fclose (fp);
			return INI_SECTIONNOTFOUND;
		}
	}

	//使用当前SECTION段;
	if (ini_LocateKeyValue (fp, pKey, pSection != NULL, pValue, iLen, NULL, 
							tempSection) != INI_OK)
	{
		fclose (fp);
		return INI_KEYNOTFOUND;
	}

	fclose (fp);
	return INI_OK;
}

/* Function: GetIntValueFromIniFile(const char* pIniFile, const char* pSection,
 *							   const char* pKey);
 * Parameter:
 *	 pIniFile: ini file path name.
 *	 pSection: Section name.
 *	 pKey:	 Key name.
 * Return:
 *	 INT32					  meaning
 *	 INI_FILENOTFOUND			 The ini file not found. 
 *	 INI_SECTIONNOTFOUND		  The section is not found. 
 *	 ETC_EKYNOTFOUND			  The Key is not found.
 *	 INI_OK					   OK.
 */
INT32 GUIAPI GetIntValueFromIniFile(const char* pIniFile, const char* pSection,
									const char* pKey, long * value)
{
	INT32 ret;
	char szBuff [51];

	ret = GetValueFromIniFile (pIniFile, pSection, pKey, szBuff, 50);
	if (ret < 0)
		return ret;

	*value = strtol (szBuff, NULL, 0);
	return INI_OK;
}

// 快速读取INI文件中指定SECTION中的指定KEY值
INT32 GUIAPI GetSerialValueFromIniFile(const char* pIniFile, 
	const char* pSection, char **pKey, char **value, int num)
{
	FILE* fp;
	int   i;
	int   readNum;
	char  tmpKey[INI_MAXLINE];
	char  tmpVal[INI_MAXLINE];
	fp = fopen(pIniFile, "r");
	if (!fp)
		 return INI_FILENOTFOUND;

	//首先定位SECTION段的位置；
	if (pSection) 
	{
		if (ini_LocateSection (fp, pSection, NULL) != INI_OK)
		{
			fclose (fp);
			return INI_SECTIONNOTFOUND;
		}
	}
	
	readNum = 0;
	while (readNum < num)
	{
		if (!ini_GetKeyValUntilEnd(fp, tmpKey, pSection != NULL, (long*)tmpVal))
		{
			return readNum;
		}
		for (i = 0; i < num; i++)
		{
			if (strcmp(tmpKey, pKey[i]) == 0)
			{
				if (strlen(tmpVal) == 0)
				{
					if (strlen(tmpVal) == 0)
					{
						value[i][0] = tmpVal[0];
					}
					else
					{
						strcpy(value[i], tmpVal);
					}
				}
				readNum++;
			}
		}
	}
	return readNum;
}

DATETIME *GetCompileDateTime(VOID)
{        
    const char szEnglishMonth[12][4] =
	{
		"Jan",
		"Feb",
		"Mar",
		"Apr",
		"May",
		"Jun",
		"Jul",
		"Aug",
		"Sep",
		"Oct",
		"Nov",
		"Dec"
	};
	static DATETIME *dt = NULL;
	if (NULL == dt)
	{
	    char szTmpDate[40]={0};
	    char szTmpTime[20]={0};
	    char szMonth[4]={0};
	    int i, iYear, iMonth, iDay, iHour, iMin, iSec;

	    sprintf(szTmpDate, "%s", __DATE__); //"Sep 18 2010"
	    sprintf(szTmpTime, "%s", __TIME__);    //"10:59:19"
	    
	    sscanf(szTmpDate, "%s %d %d", szMonth, &iDay, &iYear);
	    sscanf(szTmpTime, "%d:%d:%d", &iHour, &iMin, &iSec);
	            
		for(i = 0; i < 12; i++)
		{
			if(0 == strncmp(szMonth, szEnglishMonth[i], 3))
			{
				iMonth=i+1;
				break;
			}
		}
		dt = (DATETIME*)malloc(sizeof(DATETIME));
		if (dt != NULL)
		{
		    dt->year = iYear;
			dt->month = iMonth;
			dt->day = iDay;
			dt->hour = iHour;
			dt->minute = iMin;
			dt->second = iSec;
		}
	}
	return dt;
}


#if 0
static INT32 ini_CopyAndLocate (FILE* etc_fp, FILE* tmp_fp, 
				const char* pSection, const char* pKey, char* tempSection)
{
	if (pSection && ini_LocateSection (etc_fp, pSection, tmp_fp) != INI_OK)
		return INI_SECTIONNOTFOUND;

	if (ini_LocateKeyValue (etc_fp, pKey, pSection != NULL, NULL, 0, tmp_fp, 
							tempSection) != INI_OK)
		return INI_KEYNOTFOUND;

	return INI_OK;
}

static INT32 ini_FileCopy (FILE* sf, FILE* df)
{
	char line [INI_MAXLINE + 1];
	
	while (fgets (line, INI_MAXLINE + 1, sf) != NULL)
		if (fputs (line, df) == EOF) {
			return INI_FILEIOFAILED;
		}

	return INI_OK;
}

/* Function: SetValueToIniFile(const char* pIniFile, const char* pSection,
 *							   const char* pKey, char* pValue);
 * brief:  在目前系统中ini文件格式主要用于初始化配置文件；
 *		 用户配置文件是二进制文件，所以不能使用下面的函数处理
 * Parameter:
 *	 pIniFile: ini file path name.
 *	 pSection: Section name.
 *	 pKey:	 Key name.
 *	 pValue:   Value.
 * Return:
 *	 INT32					  meaning
 *	 INI_FILENOTFOUND		 The ini file not found.
 *	 INI_TMPFILEFAILED		Create tmp file failure.
 *	 INI_OK				   OK.
 */
INT32 GUIAPI SetValueToIniFile ( const char* pIniFile, const char* pSection,
							   const char* pKey, char* pValue )
{
	FILE * etc_fp;
	FILE * tmp_fp;
	INT32	rc;
	char   tempSection [INI_MAXLINE + 2];

	/* 首先打开一个临时文件  */
	if ((tmp_fp = tmpfile ()) == NULL)
		return INI_TMPFILEFAILED;

	etc_fp = fopen (pIniFile, "r+");
	if (!etc_fp) {	 /* 指定文件不存在 */
		fclose (tmp_fp);
		etc_fp = fopen (pIniFile, "w");
		if (!etc_fp)	/* 新建一个文件 */
			return INI_FILEIOFAILED;
		fprintf (etc_fp, "[%s]\n", pSection);	 /* 写入 SECTION */
		fprintf (etc_fp, "%s=%s\n", pKey, pValue);/* 写入 KET 和 VALUE */
		fclose (etc_fp);
		return INI_OK;
	}

	switch (ini_CopyAndLocate (etc_fp, tmp_fp, pSection, pKey, tempSection)) {
	case INI_SECTIONNOTFOUND:
		fprintf (tmp_fp, "\n[%s]\n", pSection);
		fprintf (tmp_fp, "%s=%s\n", pKey, pValue);
		break;
	
	case INI_KEYNOTFOUND:
		fprintf (tmp_fp, "%s=%s\n\n", pKey, pValue);
		fprintf (tmp_fp, "%s\n", tempSection);
	break;

	default:
		fprintf (tmp_fp, "%s=%s\n", pKey, pValue);
		break;
	}

	if ((rc = ini_FileCopy (etc_fp, tmp_fp)) != INI_OK)
		goto error;
	
	// replace ini content with tmp file content
	// truncate ini content first
	fclose (etc_fp);
	etc_fp = fopen (pIniFile, "w");
	if (!etc_fp)
		return INI_FILEIOFAILED;
	
	rewind (tmp_fp);
	rc = ini_FileCopy (tmp_fp, etc_fp);

error:
	fclose (etc_fp);
	fclose (tmp_fp);
	return rc;
}

/****************************** Drawing Helpers *******************************/
void GUIAPI Draw3DUpFrame(HDC hDC, INT32 l, INT32 t, INT32 r, INT32 b, GAL_PIXEL fillc)
{
	r--;
	b--;

	SetPenColor(hDC, GetWindowElementColor (WEC_3DFRAME_RIGHT_INNER));
	Rectangle(hDC, l, t, r, b);
	SetPenColor(hDC, GetWindowElementColor (WEC_3DFRAME_LEFT_INNER));
	Rectangle(hDC, l, t, r - 1, b - 1);
	SetPenColor(hDC, GetWindowElementColor (WEC_3DFRAME_LEFT_OUTER));
	MoveTo(hDC, l, b);
	LineTo(hDC, r, b);
	LineTo(hDC, r, t);
	SetPenColor(hDC, GetWindowElementColor (WEC_3DFRAME_RIGHT_OUTER));
	MoveTo(hDC, l + 1, b - 1);
	LineTo(hDC, l + 1, t + 1);
	LineTo(hDC, r - 1, t + 1); 

	if (fillc != 0) {
		 SetBrushColor(hDC, fillc);
		 FillRect(hDC, l + 2, t + 2, r - l - 3, b - t - 3);
	}
}

void GUIAPI Draw3DDownFrame(HDC hDC, INT32 l, INT32 t, INT32 r, INT32 b, GAL_PIXEL fillc)
{
	SetPenColor(hDC, GetWindowElementColor (WEC_3DFRAME_LEFT_OUTER));
	MoveTo(hDC, l, b);
	LineTo(hDC, l, t);
	LineTo(hDC, r, t);
	SetPenColor(hDC, GetWindowElementColor (WEC_3DFRAME_LEFT_INNER));
	MoveTo(hDC, l + 1, b - 1);
	LineTo(hDC, l + 1, t + 1);
	LineTo(hDC, r - 1, t + 1);
	SetPenColor(hDC, GetWindowElementColor (WEC_3DFRAME_RIGHT_INNER));
	MoveTo(hDC, l + 1, b - 1);
	LineTo(hDC, r - 1, b - 1);
	LineTo(hDC, r - 1, t + 1);
	SetPenColor(hDC, GetWindowElementColor (WEC_3DFRAME_RIGHT_OUTER));
	MoveTo(hDC, l, b);
	LineTo(hDC, r, b);
	LineTo(hDC, r, t);

	if (fillc != 0) {
		SetBrushColor(hDC, fillc);
		FillRect(hDC, l + 2, t + 2, r - l - 3, b - t - 3);
	}
}

void GUIAPI Draw3DUpThinFrame(HDC hDC, INT32 l, INT32 t, INT32 r, INT32 b, GAL_PIXEL fillc)
{
	SetPenColor(hDC, GetWindowElementColor (WEC_3DFRAME_RIGHT));
	MoveTo(hDC, l, b);
	LineTo(hDC, r, b);
	LineTo(hDC, r, t);
	SetPenColor(hDC, GetWindowElementColor (WEC_3DFRAME_LEFT));
	MoveTo(hDC, l, b);
	LineTo(hDC, l, t);
	LineTo(hDC, r, t); 

	if (fillc != 0) {
		SetBrushColor(hDC, fillc);
		FillRect(hDC, l + 1, t + 1, r - l - 2, b - t - 2);
	}
}

void GUIAPI Draw3DDownThinFrame (HDC hDC, INT32 l, INT32 t, INT32 r, INT32 b, GAL_PIXEL fillc)
{
	SetPenColor(hDC, GetWindowElementColor (WEC_3DFRAME_LEFT));
	MoveTo(hDC, l, b);
	LineTo(hDC, r, b);
	LineTo(hDC, r, t);
	SetPenColor(hDC, GetWindowElementColor (WEC_3DFRAME_RIGHT));
	MoveTo(hDC, l, b);
	LineTo(hDC, l, t);
	LineTo(hDC, r, t);

	if (fillc != 0) {
		 SetBrushColor(hDC, fillc);
		 FillRect(hDC, l + 1, t + 1, r - l - 2, b - t - 2);
	}
}

void GUIAPI Draw3DBorder (HDC hdc, INT32 l, INT32 t, INT32 r, INT32 b)
{
	SetPenColor(hdc, GetWindowElementColor (WEC_3DFRAME_LEFT));
	Rectangle (hdc, l + 1, t + 1, r - 1, b - 1);

	SetPenColor(hdc, GetWindowElementColor (WEC_3DFRAME_RIGHT));
	Rectangle (hdc, l, t, r - 2, b - 2);
}

/* 把16位数据转变成8bit的; */
VOID  Swap16to8(INT32 size, void * dataP )
{
	long	i;
	UINT16 *p16;
	UINT16  data;

	p16 = (UINT16 *)dataP;
	
	for ( i = 0; i < size/2; i ++  ) {
		data	 = *p16;
		data	 = SWAP16(data);
		*p16++   = data;
	}
}
#endif

static char sUsbStorageStatus = ' ';
void SetUsbStorageStatus(char status)
{
	sUsbStorageStatus = status;
}

//rtn :1 -- U盘连接并可以使用  
//rtn :0 -- U盘已连接但是不可以使用
//other  -- U盘未连接
#include <fcntl.h>
char GetUsbStorage(void)
{
	#if _ENB_AUTOUSB
	return sUsbStorageStatus;
	#endif
	char ret = ' ';
	int fd;
	
	if (0 <= (fd = open("/tmp/usb", O_RDONLY)))
	{
		read(fd, &ret, 1);
		close(fd);
	}
	else
	{
		;// autousb 未运行处理
	}
	return ret;
}

#if _ENB_USB_UPDATE
#define USB_MOUNT_PATH  "/mnt/disk"
#define USB_UPDATE_FILE "Artemis4S.zip"
#define TEMP_FOLDER	 "/tmp"
static const UCHAR UpDateShellScript[][48] = 
{
	 "chmod -R 777 "	FILEPATH
	,"cp -rf " USB_MOUNT_PATH "/" USB_UPDATE_FILE " " FILEPATH
	,"cd "			  FILEPATH
	,"rm -rf "		  FPC_CONFIG
	,"rm -rf "		  FPP_M1000
	,"unzip -o "		USB_UPDATE_FILE
	,"chmod 777 "	   FPP_M1000
	,"chmod -R 700 "	FILEPATH_FONT
	,"chmod -R 700 "	FILEPATH_LANG
	,"chmod -R 700 "	FILEPATH	PATH_ICON
	,"rm -rf "		  USB_UPDATE_FILE
	,"reboot"
};

volatile INT8 UpdateLocker;
BOOL UsbUpdateProc(VOID)
{
	UCHAR filename[32];
	int i = 0;
	UCHAR *p = filename;
	char stat = GetUsbStorage();
	
	if ('0' != stat && '1' != stat)
	{
		return FALSE;
	}
	strcpy(p, "正在识别USB设备...0");
	p = p + strlen(p) - 1;
	
	while('1' != GetUsbStorage())
	{
		if (MonitorInfo.standby == FALSE && UpdateLocker == 0)
		{
			goto exit;
		}
		if (i < 9)
		{
			i++;
			(*p)++;
			ScreenInfoOut(filename);
			ms_sleep(1000);
		}
		else
		{
			ScreenInfoOut("识别USB设备失败,退出");
			ms_sleep(1000);
			return FALSE;
		}
	}
	if (MonitorInfo.standby == FALSE && UpdateLocker == 0)
	{
		goto exit;
	}
	sprintf(filename, "%s/%s", USB_MOUNT_PATH, USB_UPDATE_FILE);
	if (!CheckFileExist(filename))
	{
		return FALSE;
	}
	ScreenInfoOut("检测到升级包...3");
	ms_sleep(1000);
	if (MonitorInfo.standby == FALSE && UpdateLocker == 0)
	{
		goto exit;
	}
	if (!CheckFileExist(filename))
	{
		return FALSE;
	}
	ScreenInfoOut("检测到升级包...2");
	ms_sleep(1000);
	if (MonitorInfo.standby == FALSE && UpdateLocker == 0)
	{
		goto exit;
	}
	if (!CheckFileExist(filename))
	{
		return FALSE;
	}
	ScreenInfoOut("检测到升级包...1");
	ms_sleep(1000);
	if (MonitorInfo.standby == FALSE && UpdateLocker == 0)
	{
		goto exit;
	}
	ScreenInfoOut("检测到升级包...0");
	if (UpdateLocker == TRUE)
		return FALSE;

	if (MonitorInfo.standby == FALSE && UpdateLocker == 0)
	{
		goto exit;
	}
	UpdateLocker = TRUE;

	i = 0;
	system(UpDateShellScript[i++]);
	ms_sleep(100);
	ScreenInfoOut("复制文件...");
	system(UpDateShellScript[i++]);
	system(UpDateShellScript[i++]);
	if (!CheckFileExist(filename))
	{
		ScreenInfoOut("升级失败!");
		return FALSE;
	}
	ms_sleep(1000);
	ScreenInfoOut("正在升级,请勿断电...");
	system(UpDateShellScript[i++]);//移除配置文件
	system(UpDateShellScript[i++]);//移除执行文件
	ms_sleep(2000);
	ScreenInfoOut("提取文件...");
	system(UpDateShellScript[i++]);//解压文件
	ms_sleep(1000);
	system(UpDateShellScript[i++]);
	system(UpDateShellScript[i++]);
	system(UpDateShellScript[i++]);
	system(UpDateShellScript[i++]);
	ms_sleep(1000);
	ScreenInfoOut("升级成功!");
	system(UpDateShellScript[i++]);
	ms_sleep(500);
	ScreenInfoOut("请移除U盘,系统将自动重启");
	while('1' == GetUsbStorage())
	{
		ms_sleep(1000);
	}
	system(UpDateShellScript[i]);
	ms_sleep(10);
	return TRUE;

exit:
	ScreenInfoOut("用户终止升级程序,退出!");
	return TRUE;
}

VOID PutSystemLog(const char *log)
{
	static FILE *fp = NULL;
	if (NULL == fp)
	{
		char name[32];
		sprintf(name, "/var/log/%s.log", MONITOR_TYPE_NAME);
		fp = fopen(name, "a+"); // 需要手动创建该文件,不会自动创建
	}
	if (fp)
	{
		fputs(log, fp);
		flush(fp);
	}
}
#endif

