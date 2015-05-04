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

#define   INIT_GLOBALS 
#include  "includes.h"


#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <linux/soundcard.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/soundcard.h>


#define LENGTH 3	/* how many seconds of speech to store */

#define RATE 22050   /* the sampling rate */
#define SAMPLE_SIZE 8	  /* sample size: 8 or 16 bits */
#define CHANNELS 1  /* 1 = mono 2 = stereo */


static int mixer_fd = -1;
static int audio_fd = -1;


void set_volume(int vol)
{
	;
}


int open_sound(void)
{
	int arg;	/* argument for ioctl calls */
	int status;   /* return status of system calls */

	
	audio_fd = open("/dev/dsp", O_RDWR);
	if (audio_fd < 0) 
	{
		perror("open of /dev/dsp failed");
		return -1;
	}

	arg = SAMPLE_SIZE;
	status = ioctl(audio_fd, SOUND_PCM_WRITE_BITS, &arg);
	if (status == -1)
		perror("SOUND_PCM_WRITE_BITS ioctl failed");
	if (arg != SAMPLE_SIZE)
		perror("unable to set sample size");

	arg = CHANNELS;  /* mono or stereo */
	status = ioctl(audio_fd, SOUND_PCM_WRITE_CHANNELS, &arg);
	if (status == -1)
		perror("SOUND_PCM_WRITE_CHANNELS ioctl failed");
	if (arg != CHANNELS)
		perror("unable to set number of channels");

	arg = RATE;
	status = ioctl(audio_fd, SOUND_PCM_WRITE_RATE, &arg);
	if (status == -1)
		perror("SOUND_PCM_WRITE_WRITE ioctl failed");

	return audio_fd;
}


struct RIFF_HEADER
{
	char szRiffID[4]; // 'R','I','F','F'
	UINT32 dwRiffSize;
	char szRiffFormat[4]; // 'W','A','V','E'
};

struct WAVE_FORMAT
{
	UINT16 wFormatTag;
	UINT16 wChannels;
	UINT32 dwSamplesPerSec;
	UINT32 dwAvgBytesPerSec;
	UINT16 wBlockAlign;
	UINT16 wBitsPerSample;
};

struct FMT_BLOCK
{
	char szFmtID[4]; // 'f','m','t',' '
	UINT32 dwFmtSize;
	struct WAVE_FORMAT wavFormat;
};


struct FACT_BLOCK
{
	char szFactID[4]; // 'f','a','c','t'
	UINT32 dwFactSize;
};

struct DATA_BLOCK
{
	char szDataID[4]; // 'd','a','t','a'
	UINT32 dwDataSize;
};

int play_sound(unsigned char * buff)
{
	int offset = 0;
	struct RIFF_HEADER riff;

	memcpy(&riff, buff + offset, sizeof(struct RIFF_HEADER));
	offset += sizeof(struct RIFF_HEADER);

	struct FMT_BLOCK fmt;
	memcpy(&fmt, buff + offset, sizeof(struct FMT_BLOCK));
	offset += sizeof(struct FMT_BLOCK);
	offset += fmt.dwFmtSize - 16;

	struct FACT_BLOCK fact;
	struct DATA_BLOCK data;
	memcpy(&fact, buff + offset, sizeof(struct FACT_BLOCK));
	offset += sizeof(struct FACT_BLOCK);

	if (strncmp(fact.szFactID, "fact", 4))
	{
		memcpy(&data, &fact, sizeof(struct FACT_BLOCK));
	}
	else
	{
		offset += fact.dwFactSize;
		memcpy(&data, buff + offset, sizeof(struct DATA_BLOCK));
		offset += sizeof(struct DATA_BLOCK);
	}
	int status;   /* return status of system calls */
	status = write(audio_fd, buff + offset, data.dwDataSize); /* play it back */
	if (status != data.dwDataSize)
		perror("wrote wrong number of bytes");
	/* wait for playback to complete before recording again */
	status = ioctl(audio_fd, SOUND_PCM_SYNC, 0);
	if (status == -1)
	{
		perror("SOUND_PCM_SYNC ioctl failed");
		return -1;
	}
	else
	{
		return 1;
	}
}



BOOL  InitDesktop(VOID);
BOOL  InitDesktopMem(VOID);
VOID  TermDesktopMem(VOID);


RECT	  g_rcScr = { 0, 0, 800, 400 };
INT8	  EnterOs = FALSE; // TRUE, 进入了OS系统调用处理。  FALSE，没有;
INT8	FirstBoot = FALSE; // Default not first boot;

/**
 ** 功能配置项是从配置文件中读出来的；
 **/
VOID  InitFuncConfig (VOID)
{
	long		 value;
	 
	FuncConfig.dynamicTrendEnabled    = FALSE; // 动态短趋势界面是否可用  1：是  0：否 lookingout
	FuncConfig.oxyCRGEnabled		  = FALSE;	// oxyCRG界面是否可用  1：是  0：否
	FuncConfig.waveScrollEnabled	  = FALSE;	   // 波形滚动显示是否可用  1：是  0：否
	FuncConfig.alarmVolumeOffEnabled  = TRUE;		// 报警音量关闭是否可用  1：是  0：否

	FuncConfig.isPasswordEnabled	  = TRUE;		// Download password??
	FuncConfig.isMultiLanguageEnabled = FALSE;	   // Download Multi language??
	FuncConfig.isPaceSmoothEnabled	  = FALSE;	   // choose pace smooth??
	FuncConfig.isCompanyNameEnabled   = TRUE;		// download company name??
	FuncConfig.isNurseCallEnable	  = FALSE;
	FuncConfig.isBigFontEnable		  = TRUE;		//modified by empty 2011/01/18

}

/**
 ** 根据配置文件的配置项，初始化一些系统的全局变量。
 **/
VOID  InitSysParamsFromFile(VOID)
{
	long		 value;
	char		 path[40];
	size_t	   size;

	value = 0;
	DemoPassWord	= DEF_DEMO_PASSWORD;
	UserPassWord	= DEF_USER_PASSWORD;
	FactoryPassWord = DEF_FACTORY_PASSWORD;
	AnalysisPassWord= DEF_ANALYSIS_PASSWORD;
	strcpy(LogoPicFileName, LOGO_PIC_FILE_DEF);
	strcpy(CaptionPicFileName, CAPTION_PIC_FILE_DEF);
}

void InitMonitorUUID(void)
{
	const char uuid[6] = ".uuid";
	char uuidbuff[40] = { 0 };
	FILE *fp = fopen(uuid, "rb");
	if (fp)
	{
		fgets(uuidbuff, sizeof(uuidbuff) - 1, fp);
		fclose(fp);
		fp = NULL;
		if (36 == strlen(uuidbuff))
		{
			fp++;
		}
	}
	if (NULL == fp)
	{
		FILE *uuidfp = fopen("/proc/sys/kernel/random/uuid", "r");
		if (uuidfp)
		{
			fgets(uuidbuff, sizeof(uuidbuff) - 1, uuidfp);
			fclose(uuidfp);
			fp = fopen(uuid, "wb");
			if (fp)
			{
				fwrite(uuidbuff, 36, 1, fp);
				fclose(fp);
			}
		}
	}
	strncpy(gMonitorUUID, uuidbuff, 36);
	gMonitorUUID[36] = '\0';
}

/**
* \brief  硬件初始化
**/
BOOL InitHardware (void)
{
	InitMonitorUUID();
	SetMachineNumber();
	Speaker_ctrl_gpio_value(0);
	ac_init();
	return TRUE;
}

BOOL InitDriver (void)
{   
	if (!InitGraphDriver()) {
		printf ("Init Graphi BGI failure .\n");
		return (-1);
	}
	
	EXIT_PROC(quit);

	if (!InitUart()) 
	{
		printf ("Init UART failure .\n");
		return (-1);
	}

	EXIT_PROC(TermUart);
	return TRUE;
}

BOOL InitApp(VOID)
{
	EnterOs = FALSE;

	ZeroMemory(&MonitorConfig.moduleInfo[0], sizeof(MonitorConfig.moduleInfo)); // modified by empty 2011/03/15
	InitFuncConfig();
	InitSysParamsFromFile();
	InitScrBaseInfo();
#if 1
	if (InitE2eprom()) 
	{
		InitUserConfig(FALSE);
	} 
	else 
	{
		InitUserConfig(TRUE);
	}
#endif
	if (!InitParam()) {
		printf("Init System Params failure\n");
		goto err;
	}
	
#if _ENB_REC_FUNC
	RecClassInitOps();
	RecEventClassInitOps();
#endif

	if (!InitGlobalString(MonitorConfig.language)) {
		printf("Init Global String failure\n");
		goto err;
	}
	
	if (!InitAlarmSystem()) {
		printf("Init Alarm System failure\n");
		goto err;
	}

#if _ENB_FILE_SYSTEM > 0
	FmsPtr = &fms;
	if (!InitSaveFileSystem(FmsPtr))
	{
		printf("Init Save File System Failure\n");
		goto err;
	}
	if (!FmsPtr->Register(FmsPtr, DATA_FILE))
	{
		printf("Register Save File System Failure\n");
		goto err;
	}
#endif


	InitMonitor();
	SetAllParamFont();	  //add by empty to support different lang 2011/06/30
	SetAllModuleSelect();   //add by empty to support replace module  2011/07/01
	InitTimer();
	//InitFetal();			// add by gjl to support feat
	//InitRecModule();		//add by empty 2011/04/28
	//InitKeyModule();		//add by empty 2011/04/28
	InitModuleMan();
	InitLastParaValue();
	if (!InitNetworkConfig())
	{
		printf("Init network failure\n");
		//goto err;
	}
	SetNetStatus();
#if _ENB_TELNET_DEBUG
	system("killall telnetd");
	system("telnetd &");
#endif
	return TRUE;

err:
	return FALSE;
}

BOOL GUIAPI InitGUI (void)
{
	if(!InitGDI())
	{
		errprintf ("DESKTOP: Initialization of GDI failure!");
		return FALSE;
	}
	ScreenInfoOut("Preparing...");
		
#if _ENB_USB_UPDATE
	UpdateLocker = -1;
	if (UsbUpdateProc())
	{
		exit(0);
	}
	UpdateLocker = 0;
#endif
	g_rcScr.left   = 0;
	g_rcScr.top	= 0;
	g_rcScr.right  = WIDTHOFPHYGC;
	g_rcScr.bottom = HEIGHTOFPHYGC;
	
	if (!InitWindowElementColors ()) 
	{
		errprintf ("DESKTOP: Can not initialize colors of window element!");
		return FALSE;
	}
	if(!InitIcon()) 
	{
		errprintf("DESKTOP: Icon initialization failure!");
		return FALSE;
	}
	
	if (!InitControlClass ()) 
	{
		errprintf("GUI: Init Control Class failure!");
		goto failure;
	}
	EXIT_PROC(TerminateControlClass);
	
	InitDesktop();

	if (!InitDesktopMem()) 
	{
		errprintf("GUI: Init Desktop Mem failure!");
		goto failure;
	}
	EXIT_PROC(TermDesktopMem);
	
	return TRUE;
	
failure:
	
	return FALSE;

}

