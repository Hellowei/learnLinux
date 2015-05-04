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

#define   DEVFONT_GLOBALS 
#include <string.h>
#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "gal.h"
#include "gdi.h"
#include "dc.h"
#include "fontname.h"

/** Font name format:
*   type-family-style-width-height-charset-encoding
*   description:
*   type		:  vaf,  rbf, tty, type1, etc
*   family	  :  system, courier, times, Helvetica, song, ming, etc
*   style	   :  weight, slant, setwidth , spacing, underline, strokeout
*   charset	 :  BIG8859, GB2312, BIG5, GB18030
*
*   目前, 字体名字:
*	 type-family-width-height-charset-encoding
**/

#define NR_LOOP_FOR_WIDTH   3
#define NR_LOOP_FOR_HEIGHT  3
#define NR_LOOP_FOR_CHARSET 4


/*  type: VBF, VBF, TTY, TYPE1 etc. */
BOOL fontGetTypeNameFromName (const char* name, char* type)
{
	int i = 0;
	
	while (name [i]) {
		if (name [i] == '-') {
			type [i] = '\0';
			break;
		}

		type [i] = name [i];
		i++;
	}

	if (name [i] == '\0')
		return FALSE;

	return TRUE;
}

/* family: ROM, SYSTEM, TERMINAL, etc */
BOOL fontGetFamilyFromName (const char* name, char* family)
{
	int i = 0;
	const char* family_part;

	if ((family_part = strchr (name, '-')) == NULL)
		return FALSE;
	if (*(++family_part) == '\0')
		return FALSE;

	while (family_part [i] && i <= LEN_FONT_NAME) {
		if (family_part [i] == '-') {
			family [i] = '\0';
			break;
		}

		family [i] = family_part [i];
		i++;
	}

	return TRUE;
}

int fontGetWidthFromName (const char* name)
{
	int i;
	const char* width_part = name;
	char width [LEN_FONT_NAME + 1];

	for (i = 0; i < NR_LOOP_FOR_WIDTH; i++) {
		if ((width_part = strchr (width_part, '-')) == NULL)
			return (-1);

		if (*(++width_part) == '\0')
			return (-1);
	}

	i = 0;
	while (width_part [i]) {
		if (width_part [i] == '-') {
			width [i] = '\0';
			break;
		}

		width [i] = width_part [i];
		i++;
	}

	if (width_part [i] == '\0')
		return (-1);

	return atoi (width);
}

int fontGetHeightFromName (const char* name)
{
	int i;
	const char* height_part = name;
	char height [LEN_FONT_NAME + 1];

	for (i = 0; i < NR_LOOP_FOR_HEIGHT; i++) {
		if ((height_part = strchr (height_part, '-')) == NULL)
			return (-1);
		if (*(++height_part) == '\0')
			return -1;
	}

	i = 0;
	while (height_part [i]) {
		if (height_part [i] == '-') {
			height [i] = '\0';
			break;
		}

		height [i] = height_part [i];
		i++;
	}

	if (height_part [i] == '\0')
		return (-1);

	return atoi (height);
}

BOOL fontGetCharsetFromName (const char* name, char* charset)
{
	int i;
	char* delim;
	const char* charset_part = name;

	for (i = 0; i < NR_LOOP_FOR_CHARSET; i++) 
	{
		if ((charset_part = strchr (charset_part, '-')) == NULL)
			return FALSE;
		if (*(++charset_part) == '\0')
			return FALSE;
	}

	delim = strchr (charset_part, ',');
	if (delim) 
	{
		int len;								  //有多个字符集,取第一个;
		len = delim - charset_part;
		strncpy (charset, charset_part, len);
		charset [len] = '\0';
		return TRUE;
	}

	strncpy (charset, charset_part, LEN_FONT_NAME);
	charset [LEN_FONT_NAME] = '\0';
	return TRUE;
}
