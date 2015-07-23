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
#ifndef   _RAWBMP_H
#define   _RAWBMP_H

/**
**  \brief  �����Ƶ���ģ�ṹ�в�����ȫ�����ַ�������;��ô���԰�ʵ�ֵ��ַ�����, 
**		  Ҳ����charset_ops���ص�offset. ���Ӵ�С�Ĵ������mapper��,������;
**		  Ҫ��Ӵ�С��Ϊ�˲���Ѹ�ٵ���Ҫ;
**/
typedef struct
{
	INT8	   * name;
	INT32		nr_chars;
	INT32		width;
	INT32		height;
	UINT16	 * mapper;  /** mapper, �е�����ֻ�����޵ļ����ַ�;����charset ops
							  ���ص�offset, ӳ�䵽bits�еĴ����				 **/
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

