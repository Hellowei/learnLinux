/*******************************************************************************
版权所有:			和心重典
版本号:				1.0.0
生成日期:			2011.04.15
文件名:				uart.c
作者:				empty
功能说明:			串口操作
其它说明:			无
所属文件关系:		本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*******************************************************************************/

#define	MAIN_GLOBALS 
#include	"includes.h"
//#include	<mcheck.h>

BOOL InitHardware(VOID);
BOOL InitDriver(VOID);
BOOL InitApp(VOID);
BOOL InitGUI(VOID);
VOID _sys_main(VOID);
VOID ScreenInfoOut(UCHAR *info);

/**********************************************Test Process********************/
#if 0
VOID test_turkish(VOID)
{
	char * upper = "\x80 \x87 \xb0 \xb3 \xb4 \xb1 \x99 \x94 \xb2 \xb5 \x9a \x81";		//Change by Latrom_07-05-2011
	char * lower = "\200 \207 \260 \263 \264 \261 \231 \224 \262 \265 \232 \201";		//Changed 80, 99, 9a, b0, b1, b2
	
	SelectFont(HDC_SCREEN, GetSystemFont(SYSLOGFONT_DEF_ASC));
	TextOut(HDC_SCREEN, 200,  30, lower);

	SelectFont(HDC_SCREEN, GetSystemFont(SYSLOGFONT_NOR_ASC));
	TextOut(HDC_SCREEN, 200, 60, lower);
}

VOID test_spanish(VOID)
{
	char * upper = "\x8e \xa0 \x90 \x82 \xb6 \xa1 \xa5 \xa4 \xb7 \xa2 \xb8 \xa3 \x81 \xa8 \xad"; //Change by Latrom_06-22-2011
	char * lower = "\216 \240 \220 \202 \266 \241 \245 \244 \267 \242 \270 \243 \201 \250 \255"; //Changed 82, 8e, a0, a1, a2, a3, a4, a5, a8, ad

	SelectFont(HDC_SCREEN, GetSystemFont(SYSLOGFONT_DEF_ASC));
	TextOut(HDC_SCREEN, 200,  90, lower);
	//TextOut(HDC_SCREEN, 200, 100, upper);

	SelectFont(HDC_SCREEN, GetSystemFont(SYSLOGFONT_NOR_ASC));
	TextOut(HDC_SCREEN, 200, 120, lower);
	//TextOut(HDC_SCREEN, 200, 200, upper);	
}

#if _RUS_SUPPORT
VOID test_russian(VOID)
{
	char * upper = "ЮАБЦДЕФГХИЙКЛМНОПЯРСТУЖВЬЫЗШЭЩЧЪ△№";		//Change by Latrom_06-09-2011
	char * lower = "юабцдефгхийклмнопярстужвьызшэщчъ△№";
		
	SelectFont(HDC_SCREEN, GetSystemFont(SYSLOGFONT_DEF_RUS));
	TextOut(HDC_SCREEN, 200, 150, lower);
	TextOut(HDC_SCREEN, 200, 180, upper);
	
	SelectFont(HDC_SCREEN, GetSystemFont(SYSLOGFONT_NOR_RUS));
	TextOut(HDC_SCREEN, 200, 210, lower);
	TextOut(HDC_SCREEN, 200, 240, upper);
}
#endif

#if _ENB_YAHEI17_FONT > 0
VOID test_Yahei17P(VOID)
{
	char * text = "啊吧才的额飞个好就看了吗你哦平去人是他我想一在";
	SelectFont(HDC_SCREEN, GetSystemFont(SYSLOGFONT_YAHEI17_FONT));
	TextOut(HDC_SCREEN, 100, 240, text);
}
#endif
#endif
/************************************************Test End**********************/

char  DebugSupportDevice = 0;

/*******************************************************************************
* 名称：int main(int argc,char *argv[])
* 功能：主程序
* MAIN 函数声明
*******************************************************************************/
int main(int argc,char *argv[])
{
	printf("add ++++++++++\n");
	int	rtn = 0;
	if (argc == 2)
	{
		printf("\n\r argc: %d ", argc);		
		printf("\n\r argv: %s ", argv[1]);

		if (strcmp(argv[1], "TOUCH") == 0)
			DebugSupportDevice	= Debug_PORT_TOUCH;

		if (strcmp(argv[1], "CONFIG") == 0)
			DebugSupportDevice	= Debug_PORT_CONFIG;

		if (strcmp(argv[1], "FHR") == 0)
			DebugSupportDevice	= Debug_PORT_FHR;

		if (strcmp(argv[1], "KEY") == 0)
			DebugSupportDevice	= Debug_PORT_KB;

	}
	//mtrace();
	fb_open();

	if (!InitHardware()) 
	{
		printf("InitHardware failure .\n");
		rtn	= (-1);
		goto	error_init;
	}

	if (!InitDriver()) 
	{
		printf("Init Driver failure .\n");
		rtn	= (-1);
		goto	error_init;
	}

	if (!InitGUI()) 
	{
		printf ("Init GUI failure .\n");
		rtn	= (-1);
		goto	error_init;
	}

/*
//
    char info[2][72] = {
    "юабцдефгхийклмнопярстужвьызшэщчъ△№",
    "ЮАБЦДЕФГХИЙКЛМНОПЯРСТУЖВЬЫЗШЭЩЧЪ△№"};
    __mg_screen_dc.pLogFont = GetSystemFont(SYSLOGFONT_DEF_RUS);
    ScreenTextOut(HDC_SCREEN, DLG_OFFSET, SCREEN_HIGH / 2 - 40, info[0], -1);
    ScreenTextOut(HDC_SCREEN, DLG_OFFSET, SCREEN_HIGH / 2 - 20, info[1], -1);

    __mg_screen_dc.pLogFont = GetSystemFont(12);
    ScreenTextOut(HDC_SCREEN, DLG_OFFSET, SCREEN_HIGH / 2 + 20, info[0], -1);
    ScreenTextOut(HDC_SCREEN, DLG_OFFSET, SCREEN_HIGH / 2 + 40, info[1], -1);

    char info2[4][72] = {
    "юабцдефгхийклмноп","ярстужвьызшэщчъ△№",
    "ЮАБЦДЕФГХИЙКЛМНОП","ЯРСТУЖВЬЫЗШЭЩЧЪ△№"};

    __mg_screen_dc.pLogFont = GetSystemFont(SYSLOGFONT_YAHEI17_FONT);
    ScreenTextOut(HDC_SCREEN, DLG_OFFSET, SCREEN_HIGH / 2 + 60, info2[0], -1);
    ScreenTextOut(HDC_SCREEN, DLG_OFFSET, SCREEN_HIGH / 2 + 90, info2[1], -1);
    ScreenTextOut(HDC_SCREEN, DLG_OFFSET, SCREEN_HIGH / 2 + 120, info2[2], -1);
    ScreenTextOut(HDC_SCREEN, DLG_OFFSET, SCREEN_HIGH / 2 + 150, info2[3], -1);
return 0;
*/
//
	if (!InitApp()) 
	{
		printf ("Init APP failure .\n");
		ScreenInfoOut("Init APP failure!");
		rtn	= (-1);
		goto	error_init;
	}
#if 0
	int i;
	for (i = 0; i < 8; i++)
	{
		fb_fillrect(0, i * 100, 0, (i + 1) * 100, 160, 0x01 << (7 - i), 0, 0);
		fb_fillrect(0, i * 100, 160, (i + 1) * 100, 320, 0, 0x01 << (7 - i), 0);
		fb_fillrect(0, i * 100, 320, (i + 1) * 100, 480, 0, 0, 0x01 << (7 - i));
	}
	
#endif
//	printf("start _sys_main\n");
	_sys_main();
	while(1)
		ms_sleep(1000);

	rtn	= 0;

error_init:
	return	rtn;
}
