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
#ifndef   _VARBMP_H
#define   _VARBMP_H

/**
**  \brief  为了可以表示只实现了部分字符集的字模;可以用first_char, last_char来表示;
**		  这样可以表达一个连续字符的范围;
**		  如果是离散的字符实现, 可以用nchars和mapper实现,nchars表示mapper的表项数量
**		  和bits数据的字符数量;
**		  在实现时, 首先检查mapper值,检查是否有映射表; 若没有, 按first char和last char
**		  来检查;
**/
typedef struct
{
	const INT8*	 name;		   /* font name										*/
	INT32		   nchars;		 /* number of Char								   */
	INT16		   max_width;	  /* max width in pixels							  */
	INT16		   ave_width;	  /* average width in pixels						  */
	INT32		   height;		 /* height in pixels								 */
	INT32		   descent;		/* pixels below the base line					   */
	UINT8		   first_char;	 /* first character in this font					 */
	UINT8		   last_char;	  /* last character in this font					  */
	UINT8		   def_char;	   /* default character in this font				   */
	const UINT32  * offset;		 /* character glyph offsets into bitmap data or NULL */
	const INT16   * width;		  /* character widths or NULL						 */
	const UINT8   * mapper;		 /* mapper, 有的字体只有有限的几个字符;根据charset ops
									   返回的offset, 映射到bits中的次序号			   */
	const UINT8   * bits;		   /* 8-bit right-padded bitmap data				   */
	INT32		   font_size;	  /* used by mmap									 */
} VBFINFO;

#define LEN_VERSION_INFO	10


#define SBC_VARFONT_INFO(logfont) ((VBFINFO*)(((DEVFONT*) (logfont.sbc_devfont))->data))
#define MBC_VARFONT_INFO(logfont) ((VBFINFO*)(((DEVFONT*) (logfont.mbc_devfont))->data))

#define SBC_VARFONT_INFO_P(logfont) ((VBFINFO*)(((DEVFONT*) (logfont->sbc_devfont))->data))
#define MBC_VARFONT_INFO_P(logfont) ((VBFINFO*)(((DEVFONT*) (logfont->mbc_devfont))->data))

#define VARFONT_INFO_P(devfont) ((VBFINFO*)(devfont->data))
#define VARFONT_INFO(devfont) ((VBFINFO*)(devfont.data))

extern  FONTOPS   var_bitmap_font_ops;

extern  VBFINFO   vbf_rom5x7; 
extern  VBFINFO   vbf_rom8x8; 
extern  VBFINFO   vbf_rom8x12; 
extern  VBFINFO   vbf_rom8x16; 
extern  VBFINFO   vbf_rom16x20; 
extern  VBFINFO   vbf_impact24X32; 
extern  VBFINFO   vbf_rom32x48; 
extern  VBFINFO   vbf_rom40x60; 
extern  VBFINFO   vbf_rom48x72; 
extern  VBFINFO   vbf_rom56x84; 
extern  VBFINFO   vbf_rom80x120;

extern  VBFINFO   vbf_rom16x18;

#endif
