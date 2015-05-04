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

#define   VARBMP_GLOBALS 
#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "gal.h"
#include "gdi.h"
#include "dc.h"
#include "varbmp.h"


/*************** Variable bitmap font operations *********************************/
/**
  \brief  根据offset查阅映射表,返回在字模数据表的次序号, 以字符为单位; 1,就是第一个字符;
  \param  offset,   字符在字符集的位置偏移量, ASCII字符集就是其本身的值;
  \param  mapper,   映射表入口
  \param  nr_chars, 映射表项的数量;
  \return   非负, 返回在字模数据表的次序号,以字符为单位; 1,就是第一个字符;
			< 0,  没有找到
**/
static long  get_mapper_offset( long offset, const UCHAR * mapper, long nr_chars )
{
	long i;
	for ( i = 0; i < nr_chars; i ++ )
	{
		if ( offset == mapper[i] )  break;
	}

	if ( i < nr_chars ) return  i;
	else				return  (-1);
}

/**
* \note 首先检查width是否有效; 有效的话, 检查映射表mapper, 然后是first char和last char,它们之一
*	   一定是有效的.
**/
static INT32 get_char_width (LOGFONT* logfont, DEVFONT* devfont, 
							 const UCHAR* mchar, INT32 len)
{
	VBFINFO* vbf_info = VARFONT_INFO_P (devfont);
	int			   i;

	logfont = logfont;
	
	if (vbf_info->width == NULL)
		return vbf_info->max_width;

	EXAM_ASSERT (len == 1);

	if ( vbf_info->mapper ) 
	{
		i = get_mapper_offset( *mchar, vbf_info->mapper, vbf_info->nchars );
		if ( i < 0 )   i = get_mapper_offset(vbf_info->def_char, vbf_info->mapper, vbf_info->nchars );
	}
	else 
	{
		if (*mchar < vbf_info->first_char || *mchar > vbf_info->last_char)
			i = vbf_info->def_char - vbf_info->first_char;
		else
			i = *mchar - vbf_info->first_char;
	}
	return vbf_info->width [i];   
}

static INT32 get_max_width (LOGFONT* logfont, DEVFONT* devfont)
{
   logfont = logfont;
   return VARFONT_INFO_P (devfont)->max_width; 
}

static INT32 get_str_width (LOGFONT* logfont, DEVFONT* devfont, 
							const UCHAR* mstr, INT32 n)
{
	INT32	 i;
	INT32	 index;
	INT32	 str_width;
	VBFINFO * vbf_info = VARFONT_INFO_P (devfont);
	
	logfont = logfont;
	
	if (vbf_info->width == NULL)
		return n * (vbf_info->max_width);

	str_width = 0;
	for (i = 0; i < n; i++) {
		if ( vbf_info->mapper ) {
			index = get_mapper_offset( mstr[i], vbf_info->mapper, vbf_info->nchars );
			if ( index < 0 )  index = get_mapper_offset(vbf_info->def_char, vbf_info->mapper, 
												vbf_info->nchars );
		}
		else {
			if (mstr[i] < vbf_info->first_char || mstr[i] > vbf_info->last_char)
				index = vbf_info->def_char - vbf_info->first_char;
			else
				index = mstr[i] - vbf_info->first_char;
		}

		str_width += vbf_info->width[index];
	}

	return str_width;
}

static INT32 get_ave_width (LOGFONT* logfont, DEVFONT* devfont)
{
	logfont = logfont;
	return VARFONT_INFO_P(devfont)->ave_width;
}

static INT32 get_font_height (LOGFONT* logfont, DEVFONT* devfont)
{
	logfont = logfont;
	return VARFONT_INFO_P (devfont)->height;
}

static INT32 get_font_size (LOGFONT* logfont, DEVFONT* devfont, INT32 expect)
{
	logfont = logfont;
	expect  = expect;
	
	return VARFONT_INFO_P (devfont)->height;
}

static INT32 get_font_ascent (LOGFONT* logfont, DEVFONT* devfont)
{
	logfont = logfont;
	return VARFONT_INFO_P (devfont)->height - VARFONT_INFO_P (devfont)->descent;
}

static INT32 get_font_descent (LOGFONT* logfont, DEVFONT* devfont)
{
	logfont = logfont;
	return VARFONT_INFO_P (devfont)->descent;
}

static INT32 char_bitmap_size (LOGFONT* logfont, DEVFONT* devfont, 
							   const UCHAR* mchar, INT32 len)
{
	INT32	 width;
	long	  i;
	VBFINFO * vbf_info = VARFONT_INFO_P (devfont);

	logfont = logfont;
	len	 = len;
	
	if (vbf_info->width == NULL) {
		width = vbf_info->max_width;
	}
	else {
		if ( vbf_info->mapper ) {
			i = get_mapper_offset( *mchar, vbf_info->mapper, vbf_info->nchars );
			if ( i < 0 )  i = get_mapper_offset(vbf_info->def_char, vbf_info->mapper, 
												vbf_info->nchars );
		}
		else {
			if (*mchar < vbf_info->first_char || *mchar > vbf_info->last_char)
				i = vbf_info->def_char - vbf_info->first_char;
			else
				i = *mchar - vbf_info->first_char;
		}
		width = vbf_info->width [i];
	}
	return ((width + 7) >> 3) * vbf_info->height;
}

static INT32 max_bitmap_size (LOGFONT* logfont, DEVFONT* devfont)
{
	logfont = logfont;
	return (((INT32)VARFONT_INFO_P (devfont)->max_width + 7) >> 3) 
				* VARFONT_INFO_P (devfont)->height;
}

/* 如果存在映射表, 需要查对表才能找字模数据 */
static const void* get_char_bitmap (LOGFONT* logfont, DEVFONT* devfont,
									const UCHAR* mchar, INT32 len)
{
	INT32		 offset;
	long		  i;
	VBFINFO *	 vbf_info = VARFONT_INFO_P (devfont);

	logfont = logfont;
	len	 = len;
	
	if ( vbf_info->mapper ) 
	{
		i = get_mapper_offset( *mchar, vbf_info->mapper, vbf_info->nchars );
		if ( i < 0 )   i = get_mapper_offset(vbf_info->def_char, vbf_info->mapper, vbf_info->nchars );
	}
	else 
	{
		if (*mchar < vbf_info->first_char || *mchar > vbf_info->last_char)
			i = vbf_info->def_char - vbf_info->first_char;
		else
			i = *mchar - vbf_info->first_char;
	}

	if (vbf_info->offset == NULL)  
	{
		offset = (((INT32)vbf_info->max_width + 7) >> 3) * vbf_info->height* i;
	}
	else {
		offset = vbf_info->offset [i];
	}

	return PTR_ADD(vbf_info->bits, offset);
}

/**************************** Global data ************************************/
FONTOPS var_bitmap_font_ops = {
	get_char_width,
	get_str_width,
	get_ave_width,
	get_max_width,  
	get_font_height,
	get_font_size,
	get_font_ascent,
	get_font_descent,
	char_bitmap_size,
	max_bitmap_size,
	get_char_bitmap
};


