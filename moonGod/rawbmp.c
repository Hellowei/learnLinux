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

#define   RAWBMP_GLOBALS 
#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "gal.h"
#include "gdi.h"
#include "dc.h"
#include "rawbmp.h"

extern INT8 EnterOs;


BOOL InitRawBitmapFonts (VOID)
{
	return TRUE;
}

/*************** Raw bitmap font operations *********************************/
static INT32 get_char_width (LOGFONT* logfont, DEVFONT* devfont, 
							 const UCHAR* mchar, INT32 len)
{
	logfont = logfont;
	mchar   = mchar;
	len	 = len;
	
	return RBFONT_INFO_P (devfont)->width;
}

static INT32 get_str_width (LOGFONT* logfont, DEVFONT* devfont, 
							const UCHAR* mstr, INT32 len)
{
	INT32 number;
	
	logfont = logfont;
	
	number = (*devfont->charset_ops->nr_chars_in_str) (mstr, len);
	return (RBFONT_INFO_P (devfont)->width )* number;   //注意:这里这个*号不是指针，是乘号的意思 -- empty 2011/05/05
}

static INT32 get_ave_width (LOGFONT* logfont, DEVFONT* devfont)
{
	logfont = logfont;
	return RBFONT_INFO_P (devfont)->width;
}

static INT32 get_font_height (LOGFONT* logfont, DEVFONT* devfont)
{
	logfont = logfont;
	return RBFONT_INFO_P (devfont)->height;
}

static INT32 get_font_size (LOGFONT* logfont, DEVFONT* devfont, INT32 expect)
{
	logfont = logfont;
	expect  = expect;
	
	return RBFONT_INFO_P (devfont)->height;
}

static INT32 get_font_descent (LOGFONT* logfont, DEVFONT* devfont)
{
	logfont = logfont;
	devfont = devfont;
	
	return 0;
}

static INT32 char_bitmap_size (LOGFONT* logfont, DEVFONT* devfont, 
							   const UCHAR* mchar, INT32 len)
{
	logfont = logfont;
	mchar   = mchar;
	len	 = len;
	
	return ((RBFONT_INFO_P (devfont)->width + 7) >> 3) 
				* RBFONT_INFO_P (devfont)->height;
}

static INT32 max_bitmap_size (LOGFONT* logfont, DEVFONT* devfont)
{
	logfont = logfont;
	return ((RBFONT_INFO_P (devfont)->width + 7) >> 3) 
		   * RBFONT_INFO_P (devfont)->height;
}

/**
  \brief  根据offset查阅映射表,返回在字模数据表的次序号, 以字符为单位; 1,就是第一个字符;
  \param  offset,   字符在字符集的位置偏移量, ASCII字符集就是其本身的值;也就是内码值;
  \param  mapper,   映射表入口
  \param  nr_chars, 映射表项的数量;
  \return   非负, 返回在字模数据表的次序号,以字符为单位; 1,就是第一个字符;
			< 0,  没有找到
**/
static long  get_mapper_offset (long offset, const UINT16 * mapper, long nr_chars)
{
	long i;
	for (i = 0; i < nr_chars; i++)
	{
		if (offset == mapper[i])  
			break;
	}
	if (i < nr_chars) 
		return  i;
	else
		return  (-1);
}

static const void* get_char_bitmap (LOGFONT* logfont, DEVFONT* devfont,
									const UCHAR* mchar, INT32 len)
#if 1
{
	long bitmap_size;
	long offset;

	logfont = logfont;
	len	 = len;

	offset = (*devfont->charset_ops->char_offset) (mchar);/* 获得输入字符在字符集中的偏移量 */

	if (RBFONT_INFO_P (devfont)->mapper) 
	{ /* 如果存在映射表, 需要查对表才能找字模数据 */
		offset = MAKEWORD(mchar[1], mchar[0]);
		offset = get_mapper_offset( offset, RBFONT_INFO_P (devfont)->mapper, 
							   RBFONT_INFO_P (devfont)->nr_chars );
		
		if (offset < 0) 
		{ /* 找不到字符的映射,使用默认字符 */
		
			offset = MAKEWORD(devfont->charset_ops->def_char[1], devfont->charset_ops->def_char[0]);
			offset = get_mapper_offset( offset, RBFONT_INFO_P (devfont)->mapper, 
								   RBFONT_INFO_P (devfont)->nr_chars );
		}
	} 
	else  
	{
		if (offset >= RBFONT_INFO_P (devfont)->font_size)
			offset = (*devfont->charset_ops->char_offset)(devfont->charset_ops->def_char);

	}
	bitmap_size = ((RBFONT_INFO_P (devfont)->width + 7) >> 3) 
				  * RBFONT_INFO_P (devfont)->height; 

	return PTR_ADD(RBFONT_INFO_P (devfont)->font, bitmap_size * offset);
}
#else
{
	long bitmap_size;
	long offset;
	long i;
	
	logfont = logfont;
	len	 = len;
	
	offset = (*devfont->charset_ops->char_offset) (mchar);/* 获得输入字符在字符集中的偏移量 */

	if (RBFONT_INFO_P (devfont)->mapper) /* 如果存在映射表, 需要查对表才能找字模数据 */
	{ 
	
		i = get_mapper_offset( offset, RBFONT_INFO_P (devfont)->mapper, 
							   RBFONT_INFO_P (devfont)->nr_chars );
				
		if (i < 0) /* 找不到字符的映射,使用默认字符 */
		{ 
			offset = (*devfont->charset_ops->char_offset)(devfont->charset_ops->def_char);
			i = get_mapper_offset( offset, RBFONT_INFO_P (devfont)->mapper, 
								   RBFONT_INFO_P (devfont)->nr_chars );
			offset = i;  //add by empty to midified the bug 2011/05/11
		}
		else			 
		{
			offset = i;  //add by empty to midified the bug 2011/05/11
		}
	} 
	else  
	{
		if (offset >= RBFONT_INFO_P (devfont)->font_size)
			offset = (*devfont->charset_ops->char_offset)(devfont->charset_ops->def_char);

	}
	bitmap_size = ((RBFONT_INFO_P (devfont)->width + 7) >> 3) 
				  * RBFONT_INFO_P (devfont)->height; 

	return PTR_ADD(RBFONT_INFO_P (devfont)->font, bitmap_size * offset);
}

#endif

/**************************** Global data ************************************/
FONTOPS raw_bitmap_font_ops = {
	get_char_width,
	get_str_width,
	get_ave_width,
	get_ave_width,	 // max_width same as ave_width
	get_font_height,
	get_font_size,
	get_font_height,   // ascent same as height
	get_font_descent,
	char_bitmap_size,
	max_bitmap_size,
	get_char_bitmap
};


