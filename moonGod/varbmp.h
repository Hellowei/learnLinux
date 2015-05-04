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
#ifndef   _VARBMP_H
#define   _VARBMP_H

/**
**  \brief  Ϊ�˿��Ա�ʾֻʵ���˲����ַ�������ģ;������first_char, last_char����ʾ;
**		  �������Ա��һ�������ַ��ķ�Χ;
**		  �������ɢ���ַ�ʵ��, ������nchars��mapperʵ��,nchars��ʾmapper�ı�������
**		  ��bits���ݵ��ַ�����;
**		  ��ʵ��ʱ, ���ȼ��mapperֵ,����Ƿ���ӳ���; ��û��, ��first char��last char
**		  �����;
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
	const UINT8   * mapper;		 /* mapper, �е�����ֻ�����޵ļ����ַ�;����charset ops
									   ���ص�offset, ӳ�䵽bits�еĴ����			   */
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
