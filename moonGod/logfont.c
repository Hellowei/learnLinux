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

#define   LOGFONT_GLOBALS 
#include <string.h>
#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "gal.h"
#include "gdi.h"
#include "dc.h"
#include "rawbmp.h"
#include "varbmp.h"
#include "devfont.h"

static LOGFONT   _sys_logfont;

CHARSETOPS * GetCharsetOps (const char* charset_name);

/************************** Exported functions ******************************/
static PLOGFONT gdiCreateLogFont ( const char* type, const char* family, 
								   const char* charset, int size)
{
	PLOGFONT  log_font;
	char	  dev_family [LEN_FONT_NAME + 1];
	DEVFONT * sbc_devfont, *mbc_devfont;

	log_font = &_sys_logfont;
	
	// is supported charset?
	if (GetCharsetOps (charset) == NULL) 
	{
		return INV_LOGFONT;
	}

	if (type)
	{
		strncpy (log_font->type, type, LEN_FONT_NAME);
		log_font->type [LEN_FONT_NAME] = '\0';
	}
	else
		strcpy (log_font->type, FONT_TYPE_NAME_ALL);

	strncpy (log_font->family, family, LEN_FONT_NAME);
	log_font->family [LEN_FONT_NAME] = '\0';

	strncpy (log_font->charset, charset, LEN_FONT_NAME);
	log_font->charset [LEN_FONT_NAME] = '\0';

	if (size > FONT_MAX_SIZE)
		log_font->size = FONT_MAX_SIZE;
	else if (size < FONT_MIN_SIZE)
		log_font->size = FONT_MIN_SIZE;
	else
		log_font->size = size;

	sbc_devfont = GetMatchedSBDevFont (log_font);  
	
	if (sbc_devfont == NULL)  
	{
		return INV_LOGFONT;
	}

	mbc_devfont = GetMatchedMBDevFont (log_font);

	log_font->sbc_devfont = sbc_devfont;
	log_font->mbc_devfont = mbc_devfont;

	/* 
	 * Adjust the logical font information;如果,所有条件全部精确满足,则不需调整;
	 */

	// family name
	if (log_font->mbc_devfont) {
		fontGetFamilyFromName (log_font->mbc_devfont->name, dev_family);
		strncpy (log_font->family, dev_family, LEN_FONT_NAME);
		log_font->family [LEN_FONT_NAME] = '\0';
	}
	else {
		fontGetFamilyFromName (log_font->sbc_devfont->name, dev_family);
		strncpy (log_font->family, dev_family, LEN_FONT_NAME);
		log_font->charset [LEN_FONT_NAME] = '\0';
	}

	// charset name
	if (log_font->mbc_devfont) {
		strncpy (log_font->charset, log_font->mbc_devfont->charset_ops->name, LEN_FONT_NAME);
		log_font->charset [LEN_FONT_NAME] = '\0';
	}
	else {
		strncpy (log_font->charset, log_font->sbc_devfont->charset_ops->name, LEN_FONT_NAME);
		log_font->charset [LEN_FONT_NAME] = '\0';
	}

	// size
	log_font->size = (*log_font->sbc_devfont->font_ops->get_font_height)
					 (log_font, log_font->sbc_devfont);

	if (log_font->mbc_devfont) {
		int size = (*log_font->mbc_devfont->font_ops->get_font_height)
				   (log_font, log_font->mbc_devfont);

		if (size > log_font->size)
			log_font->size = size;
	}
	return log_font;
}

PLOGFONT GUIAPI CreateLogFontIndirect (LOGFONT *logfont)
{
	return gdiCreateLogFont (logfont->type, logfont->family, 
							 logfont->charset, logfont->size);
}

PLOGFONT GUIAPI CreateLogFont (const char* type, const char* family, 
							   const char* charset,  INT32 size )
{
	return gdiCreateLogFont (type, family, charset, size);
}

PLOGFONT GUIAPI GetCurFont (HDC hdc)
{
	PDC pdc;

	pdc = dc_HDC2PDC(hdc);
	return pdc->pLogFont;
}

PLOGFONT GUIAPI SelectFont (HDC hdc, PLOGFONT log_font)
{
	PLOGFONT old;
	PDC	  pdc;

	pdc = dc_HDC2PDC(hdc);
	old = pdc->pLogFont;
	if (log_font == INV_LOGFONT)
		pdc->pLogFont = g_SysLogFont [1] ? g_SysLogFont [1] : g_SysLogFont [0];
	else
		pdc->pLogFont = log_font;
	
	return old;
}

void GUIAPI GetLogFontInfo (HDC hdc, LOGFONT* log_font)
{
	memcpy (log_font, dc_HDC2PDC (hdc)->pLogFont, sizeof (LOGFONT));
}


