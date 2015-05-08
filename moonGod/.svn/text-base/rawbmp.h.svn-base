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
#ifndef   _RAWBMP_H
#define   _RAWBMP_H

/**
**  \brief  如果设计的字模结构中不包含全部的字符集数据;那么可以把实现的字符内码, 
**		  也就是charset_ops返回的offset. 按从大到小的次序组成mapper表,供查阅;
**		  要求从大到小是为了查阅迅速的需要;
**/
typedef struct
{
	INT8	   * name;
	INT32		nr_chars;
	INT32		width;
	INT32		height;
	UINT16	 * mapper;  /** mapper, 有的字体只有有限的几个字符;根据charset ops
							  返回的offset, 映射到bits中的次序号				 **/
	UINT8	  * font;
	INT32		font_size;
} RBFINFO;

extern  FONTOPS   raw_bitmap_font_ops;

extern  RBFINFO   rbf_gb12x12; 
extern  RBFINFO   rbf_gb16x16; 

#if _ENB_RUS8X12_FONT
extern  RBFINFO   rbf_russian8x12;  //Change by Latrom_06-21-2011
#endif

#if _ENB_RUS8X16_FONT
extern  RBFINFO   rbf_russian8x16;  //Change by Latrom_06-21-2011
#endif

#if _ENB_PRT16X18_FONT > 0
extern  RBFINFO   rbf_gb16x18;
#endif

#if _ENB_YAHEI17_FONT > 0
extern  RBFINFO   rbf_gb23x30;
#endif

#define SBC_RBFONT_INFO(logfont)   ((RBFINFO*)(((DEVFONT*) (logfont.sbc_devfont))->data))
#define MBC_RBFONT_INFO(logfont)   ((RBFINFO*)(((DEVFONT*) (logfont.mbc_devfont))->data))

#define SBC_RBFONT_INFO_P(logfont) ((RBFINFO*)(((DEVFONT*) (logfont->sbc_devfont))->data))
#define MBC_RBFONT_INFO_P(logfont) ((RBFINFO*)(((DEVFONT*) (logfont->mbc_devfont))->data))

#define RBFONT_INFO_P(devfont)	 ((RBFINFO*)(devfont->data))
#define RBFONT_INFO(devfont)	   ((RBFINFO*)(devfont.data))

#endif

