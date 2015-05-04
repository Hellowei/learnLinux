/*****************************************************************************************
��Ȩ����:			�����ص�
�汾��:				1.0.0
��������:			2011.04.15
�ļ���:				
����:				�����ص�
����˵��:			
����˵��:			��
�����ļ���ϵ:		���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
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
	return (RBFONT_INFO_P (devfont)->width )* number;   //ע��:�������*�Ų���ָ�룬�ǳ˺ŵ���˼ -- empty 2011/05/05
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
  \brief  ����offset����ӳ���,��������ģ���ݱ�Ĵ����, ���ַ�Ϊ��λ; 1,���ǵ�һ���ַ�;
  \param  offset,   �ַ����ַ�����λ��ƫ����, ASCII�ַ��������䱾���ֵ;Ҳ��������ֵ;
  \param  mapper,   ӳ������
  \param  nr_chars, ӳ����������;
  \return   �Ǹ�, ��������ģ���ݱ�Ĵ����,���ַ�Ϊ��λ; 1,���ǵ�һ���ַ�;
			< 0,  û���ҵ�
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

	offset = (*devfont->charset_ops->char_offset) (mchar);/* ��������ַ����ַ����е�ƫ���� */

	if (RBFONT_INFO_P (devfont)->mapper) 
	{ /* �������ӳ���, ��Ҫ��Ա��������ģ���� */
		offset = MAKEWORD(mchar[1], mchar[0]);
		offset = get_mapper_offset( offset, RBFONT_INFO_P (devfont)->mapper, 
							   RBFONT_INFO_P (devfont)->nr_chars );
		
		if (offset < 0) 
		{ /* �Ҳ����ַ���ӳ��,ʹ��Ĭ���ַ� */
		
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
	
	offset = (*devfont->charset_ops->char_offset) (mchar);/* ��������ַ����ַ����е�ƫ���� */

	if (RBFONT_INFO_P (devfont)->mapper) /* �������ӳ���, ��Ҫ��Ա��������ģ���� */
	{ 
	
		i = get_mapper_offset( offset, RBFONT_INFO_P (devfont)->mapper, 
							   RBFONT_INFO_P (devfont)->nr_chars );
				
		if (i < 0) /* �Ҳ����ַ���ӳ��,ʹ��Ĭ���ַ� */
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


