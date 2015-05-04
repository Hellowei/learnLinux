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

#define   SYSFONT_GLOBALS 
#include "includes.h"


/**************************** Global data ************************************/
/* 根据系统默认,窗口需要对应的逻辑字体指针 */
PLOGFONT g_SysLogFont [NR_SYSLOGFONTS];


static LOGFONT sys_logFont [] = {
/*  :type				   :family		  :charset					:size :sbc_devfont :mbc_devfont */
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_ISO8859_1,	 8,	NULL,		NULL },
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_GB2312_1980_0, 16,   NULL,		NULL },
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_ISO8859_1,	 7,	NULL,		NULL },
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_ISO8859_1,	 20,   NULL,		NULL },
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_ISO8859_1,	 32,   NULL,		NULL },
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_ISO8859_1,	 48,   NULL,		NULL },
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_ISO8859_1,	 60,   NULL,		NULL },
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_ISO8859_1,	 12,	NULL,	   NULL },
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_ISO8859_1,	 16,	NULL,	   NULL },
#if _ENB_GB12X12_FONT > 0
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_GB2312_1980_0, 12,   NULL,		NULL },
#endif

#if _ENB_48X72_FONT > 0
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_ISO8859_1,	 72,   NULL,		NULL },
#endif
#if _ENB_56X84_FONT > 0
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_ISO8859_1,	 84,   NULL,		NULL },
#endif
#if _ENB_80X120_FONT > 0
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_ISO8859_1,	 120,  NULL,		NULL },
#endif

#if  _ENB_RUS8X12_FONT > 0
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_RUSSIAN_1980_0, 12,  NULL,		NULL },	//Change by Latrom_06-21-2011
#endif

#if  _ENB_RUS8X16_FONT > 0
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_RUSSIAN_1980_0,16,  NULL,		NULL },	//Change by Latrom_06-21-2011
#endif

#if _ENB_PRT16X18_FONT > 0
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_ISO8859_1,	  18,  NULL,		NULL },
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_GB2312_1980_0,  18,  NULL,		NULL },
#endif

#if _ENB_YAHEI17_FONT > 0
{FONT_TYPE_NAME_ALL,		FONT_FAMILY_ROM, FONT_CHARSET_GB2312_1980_0,  30,  NULL,		NULL }
#endif

};

/**
*  系统逻辑指针(g_SysLogFont) 映射到sys_logFont的数组索引 

*  default	
*  wchar_def  
*  fixed	  
*  caption	
*  menu	  
*  control	
**/
static const CHAR  sys_font_id[NR_SYSLOGFONTS] = {
	0,  // "default",
	9,  // "wchar_def",
	2,  // "mini",
	3,  // "micro param",
	4,  // "small param",
	5,  // "mid param"
	6,  // "big param",
	1,  // "fixed",
	7,  // "default ascii"
	8,  // "normal ascii"
	10,
	
#if _ENB_RUS8X12_FONT	   //Change by Latrom_06-21-2011
	11,
#endif

#if _ENB_RUS8X16_FONT	   //Change by Latrom_06-21-2011
	12,
#endif

#if _ENB_PRT16X18_FONT
	13, // "printer ascii"
	14, // "gb16x18&ascii" 
#endif

#if _ENB_YAHEI17_FONT > 0
	15,
#endif

};

#define NR_LOGFONTS  TABLESIZE(sys_logFont)


BOOL InitSysFont (VOID)
{
	INT32		i;
	PLOGFONT	 sys_fonts;
	CHAR		 type[LEN_FONT_NAME + 1];
	CHAR		 family[LEN_FONT_NAME + 1];
	CHAR		 charset[LEN_FONT_NAME + 1];
	INT32		height;
	INT32		font_id;
	CHARSETOPS * char_ops;

	memset( g_SysLogFont, 0, sizeof(g_SysLogFont) );
	 
	for (i = 0; i < NR_LOGFONTS; i++) {

		strcpy( type,	sys_logFont[i].type	);
		strcpy( family,  sys_logFont[i].family  );
		strcpy( charset, sys_logFont[i].charset );
		height = sys_logFont[i].size;

		char_ops = (CHARSETOPS *)GetCharsetOps (charset);
		if (i == 0 && char_ops->bytes_maxlen_char > 1)
		{
			errprintf ("GDI: First system font should be a single-byte charset\n");
			goto error_init;
		}

		if ((sys_fonts = CreateLogFont (type, family, charset, height)) == NULL) 
		{
			errprintf ("GDI: Error when creating system logical font\n");
			goto error_init;
		}

		sys_logFont[i] = *sys_fonts;
		
		/* 第一个创建的是系统默认的逻辑字体;它必须立即赋值给g_SysLogFont [0] ;因为在后面的
		 * CreateLogFont中回使用到g_SysLogFont [0]
		*/
		if (i == 0)
		{
			g_SysLogFont [0] = & sys_logFont [0];
		}
	}

	for (i = 0; i < NR_SYSLOGFONTS; i++) 
	{
		font_id = sys_font_id[i];
		g_SysLogFont [i] = & sys_logFont[font_id];
	}

	return TRUE;

error_init:
	errprintf ("GDI: Error in creating system logical fonts!\n");
	return FALSE;
}


/**************************** API: System Font Info *************************/
const CHAR* GUIAPI GetSysCharset (BOOL wchar)
{
	if (wchar) {
		if (g_SysLogFont[1]->mbc_devfont)
			return MBC_DEVFONT_INFO_P (g_SysLogFont[1])->charset_ops->name;
		else
			return NULL;
	}
	else 
		return SBC_DEVFONT_INFO_P (g_SysLogFont[0])->charset_ops->name;
}

// get default logofont width
INT32 GUIAPI GetSysCharWidth (VOID)
{
	DEVFONT* sbc_devfont = g_SysLogFont[0]->sbc_devfont;

	return sbc_devfont->font_ops->get_max_width (g_SysLogFont[0], sbc_devfont);
}

// get default wchar logofont width
INT32 GUIAPI GetSysCCharWidth (VOID)
{
	DEVFONT* mbc_devfont = g_SysLogFont[1]->mbc_devfont;

	if (mbc_devfont)
		return mbc_devfont->font_ops->get_max_width (g_SysLogFont[1], mbc_devfont);
	else
		return GetSysCharWidth () * 2;
}

INT32 GUIAPI GetSysCharHeight (VOID)
{
	return g_SysLogFont[0]->size;
}

PLOGFONT GUIAPI GetSystemFont (INT32 font_id)
{
	if (font_id >= 0 && font_id < NR_SYSLOGFONTS)
		return g_SysLogFont [font_id];
	else
		return (PLOGFONT)NULL;
}



