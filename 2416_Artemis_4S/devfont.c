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
#define   DEVFONT_GLOBALS 
#include <string.h>
#include <stdlib.h>
#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "gal.h"
#include "gdi.h"
#include "dc.h"
#include "rawbmp.h"
#include "varbmp.h"
#include "devfont.h"
#include "externfile.h"	   /* �ⲿ�ļ�·��		*/
#include "stdio.h"

/* GB2132-1980�ĺ�����ģ�� */
#define   HZK12_FILENAME		FPF_HZK12
#define   HZK16_FILENAME		FPF_HZK16
#define   YAHEI17_FILENAME	  FPF_YH17

static  DEVFONT  sb_dev_font[] = {
	/* name						, font_ops		   , charset_ops, font data */
	{ FONT_VBF_ROM_5X7_ISO8859_1,	&var_bitmap_font_ops, NULL,		&vbf_rom5x7	 },
	{ FONT_VBF_ROM_8X8_ISO8859_1,	&var_bitmap_font_ops, NULL,		&vbf_rom8x8	 },
	{ FONT_VBF_ROM_8X12_ISO8859_1,   &var_bitmap_font_ops, NULL,		&vbf_rom8x12	},
	{ FONT_VBF_ROM_8X16_ISO8859_1,   &var_bitmap_font_ops, NULL,		&vbf_rom8x16	},
	{ FONT_VBF_ROM_16X20_ISO8859_1,  &var_bitmap_font_ops, NULL,		&vbf_rom16x20   },
	{ FONT_VBF_ROM_24X32_ISO8859_1,  &var_bitmap_font_ops, NULL,		&vbf_impact24X32},
	{ FONT_VBF_ROM_32X48_ISO8859_1,  &var_bitmap_font_ops, NULL,		&vbf_rom32x48   },
	{ FONT_VBF_ROM_40X60_ISO8859_1,  &var_bitmap_font_ops, NULL,		&vbf_rom40x60   },
#if _ENB_48X72_FONT > 0
	{ FONT_VBF_ROM_48X72_ISO8859_1,  &var_bitmap_font_ops, NULL,		&vbf_rom48x72   },
#endif
#if _ENB_56X84_FONT > 0
	{ FONT_VBF_ROM_56X84_ISO8859_1,  &var_bitmap_font_ops, NULL,		&vbf_rom56x84   },
#endif
#if _ENB_80X120_FONT > 0
	{ FONT_VBF_ROM_80X120_ISO8859_1, &var_bitmap_font_ops, NULL,		&vbf_rom80x120  },	
#endif  

#if _ENB_PRT16X18_FONT > 0		// added by gjl
	{ FONT_VBF_ROM_16X18_ISO8859_1,  &var_bitmap_font_ops, NULL,		&vbf_rom16x18	},
#endif

};

static  DEVFONT  mb_dev_font[] = {
#if  _ENB_GB12X12_FONT > 0
	/* name						, font_ops		   , charset_ops,  font data */
	{ FONT_RBF_ROM_12X12_GB2312,	 &raw_bitmap_font_ops, NULL,		&rbf_gb12x12   },
#endif
	
#if  _ENB_GB16X16_FONT > 0
	{ FONT_RBF_ROM_16X16_GB2312,	 &raw_bitmap_font_ops, NULL,		&rbf_gb16x16   },
#endif

#if  _ENB_RUS8X12_FONT > 0
	/* name						, font_ops		   , charset_ops,	 font data */
	{ FONT_RBF_ROM_8X12_RUSSIAN,	 &raw_bitmap_font_ops, NULL,		&rbf_russian8x12   },   //Change by Latrom_06-21-2011
#endif

#if  _ENB_RUS8X16_FONT > 0
	{ FONT_RBF_ROM_8X16_RUSSIAN,	 &raw_bitmap_font_ops, NULL,		&rbf_russian8x16   },   //Change by Latrom_06-21-2011  
#endif

#if _ENB_PRT16X18_FONT > 0
	{ FONT_RBF_ROM_16X18_GB2312,	 &raw_bitmap_font_ops, NULL,		&rbf_gb16x18   },
#endif

#if _ENB_YAHEI17_FONT > 0
	{ FONT_RBF_ROM_23X30_GB2312,	 &raw_bitmap_font_ops, NULL,		&rbf_gb23x30	}
#endif

};

#define  NR_SB_DEVFONT   TABLESIZE(sb_dev_font)
#define  NR_MB_DEVFONT   TABLESIZE(mb_dev_font)

#define MATCHED_TYPE		0x01
#define MATCHED_FAMILY	  0x02
#define MATCHED_CHARSET	 0x04

/**
* \note ���ҵ��㷨: 
*	   ����,��һ������,�ַ���,��family����ͬ������; size�����С;
*	   ���,��ǰ�治������;����һ���ַ�����ͬ,size�����С���豸����;
**/
DEVFONT * GetMatchedMBDevFont (LOGFONT* log_font)
{
	DEVFONT * dev_font;
	int	   i;
	BYTE	  match_bits[NR_MB_DEVFONT];
	char	  charset_req [LEN_FONT_NAME + 1];
	int	   min_error;
	DEVFONT * matched_font;
	int	   type_req;
	char	  family [LEN_FONT_NAME + 1];
	char	  charset [LEN_FONT_NAME + 1];
	int	   error;
	CHARSETOPS * char_ops = GetCharsetOps (log_font->charset);
	
	// is charset requested is a multiple-byte charset?
	if (char_ops->bytes_maxlen_char < 2)
		return NULL;

	strcpy (charset_req, log_font->charset);
		
	for ( i = 0; i < NR_MB_DEVFONT; i ++ ) 
	{
		dev_font = (DEVFONT *)(mb_dev_font+i);
		
		// clear match_bits first.
		match_bits [i] = 0;

		// always match type
		match_bits[i] = MATCHED_TYPE;

		// does match this family?
		fontGetFamilyFromName (dev_font->name, family);
		if (strcmp (family, log_font->family) == 0) 
		{
			match_bits [i] |= MATCHED_FAMILY;
		}

		// does match this charset 
		fontGetCharsetFromName (dev_font->name, charset);
		if (GetCharsetOps (charset) == GetCharsetOps (charset_req)) 
		{
			match_bits [i] |= MATCHED_CHARSET;
		}

		// FIXME: ignore style
	}

	matched_font = NULL;
	min_error	= FONT_MAX_SIZE;
	for (i = 0; i < NR_MB_DEVFONT; i++) 
	{
		dev_font	 = (DEVFONT *)(mb_dev_font + i);
		if ((match_bits [i] & MATCHED_TYPE)
			 && (match_bits [i] & MATCHED_FAMILY)
			 && (match_bits [i] & MATCHED_CHARSET)) 
		{
			error = ABS (log_font->size - 
					(*dev_font->font_ops->get_font_size) (log_font, dev_font, 
														  log_font->size));
			if (min_error > error) 
			{
				min_error = error;
				matched_font = dev_font;
			}
		}
	}

	if (matched_font) 
	{
		return matched_font;
	}

	min_error = FONT_MAX_SIZE;
	for (i = 0; i < NR_MB_DEVFONT; i++) 
	{
		int error;
		dev_font  = (DEVFONT *)(mb_dev_font+i);
		if (match_bits [i] & MATCHED_CHARSET) 
		{
			error = ABS (log_font->size - 
					(*dev_font->font_ops->get_font_size) (log_font, dev_font, 
														  log_font->size));
			if (min_error > error) 
			{
				min_error = error;
				matched_font = dev_font;
			}
		}
	}


	return matched_font;
}

DEVFONT * GetMatchedSBDevFont (LOGFONT* log_font)
{
	DEVFONT * dev_font;
	int	   i;
	BYTE	  match_bits[NR_SB_DEVFONT];
	char	  charset_req [LEN_FONT_NAME + 1];
	int	   min_error;
	DEVFONT * matched_font;
	int	   type_req;
	char	  family [LEN_FONT_NAME + 1];
	char	  charset [LEN_FONT_NAME + 1];
	int	   error;
	CHARSETOPS * char_ops;

	char_ops = GetCharsetOps (log_font->charset);
	
	if (char_ops->bytes_maxlen_char > 1) 
	{
		/* ���Ҫ����ַ������ǵ��ֽڵ�,ǿ�Ʊ�ɵ��ֽڵ��ַ��� */
		fontGetCharsetFromName (g_SysLogFont[0]->sbc_devfont->name, charset_req);
	}
	else 
	{
		strcpy (charset_req, log_font->charset);
	}
	
	for ( i = 0; i < NR_SB_DEVFONT; i ++ ) 
	{
		dev_font = (DEVFONT *)(sb_dev_font + i);
		
		// clear match_bits first.
		match_bits [i] = 0;

		// always match type
		match_bits[i] = MATCHED_TYPE;
		
		// does match this family?
		fontGetFamilyFromName (dev_font->name, family);
		if (strcmp (family, log_font->family) == 0) 
		{
			match_bits [i] |= MATCHED_FAMILY;
		}

		// does match this charset 
		fontGetCharsetFromName (dev_font->name, charset);
		if (GetCharsetOps (charset) == GetCharsetOps (charset_req)) 
		{
			match_bits [i] |= MATCHED_CHARSET;
		}

		// FIXME: ignore style
	}

	/* ������ƥ���devfont��ѡȡsize��ӽ���һ�� */
	min_error	= FONT_MAX_SIZE;
	matched_font = NULL;
	for (i = 0; i < NR_SB_DEVFONT; i++) 
	{
		dev_font	 = (DEVFONT *)(sb_dev_font+i);
		if ((match_bits [i] & MATCHED_TYPE)
				&& (match_bits [i] & MATCHED_FAMILY)
				&& (match_bits [i] & MATCHED_CHARSET)) 
	   {
			error = ABS (log_font->size - 
					(*dev_font->font_ops->get_font_size) (log_font, dev_font, 
														  log_font->size));
			if (min_error > error) 
			{
				min_error = error;
				matched_font = dev_font;
			}
		}
	}

	if (matched_font) 
	{
		return matched_font;
	}

	/* ���ǰ������������,��ѡ���ַ������ϵ�devfont */
	// check charset here.
	min_error = FONT_MAX_SIZE;
	for (i = 0; i < NR_SB_DEVFONT; i++) 
	{
		int error;
		dev_font =  (DEVFONT *)(sb_dev_font+i);
		if (match_bits [i] & MATCHED_CHARSET)
		{
			error = ABS (log_font->size - 
					(*dev_font->font_ops->get_font_size) (log_font, dev_font, log_font->size));
			if (min_error > error) 
			{
				min_error = error;
				matched_font = dev_font;
			}
		}
	}
	return matched_font;
}

/**
*  \brief
*  �����������ģ�ļ�,�����㹻���ڴ�,�������ݶ���;
*  ���ط�����ڴ��ַ; 
*  ֻ����pc�ϵĳ���;
*  \note  fread����һ�������Զ�65200byte������,��֪Ϊ��;���Ա���ֶ�ζ�;
*		 �����������, 16λģʽ�µ�ָ������ƶ�����64k,������������ָ��ֵ��ָֹ�뷴��;
**/
static void * load_fontData (const char * name)
{
	FILE   * fp;
	void   * memP;

#if _ENB_GB_READ_FILE > 0 
	//����һ���Է����ڴ棬��ȡ��д�����Ĳ���: Ҫд�ַ�����Ļ�ϲŴ��ļ���ȡ����
	memP = NULL;

	fp = fopen(name, "rb" );
	if (fp) { // ���ļ��ɹ�
		memP = (void *)1;  /* ���ܷ���0ָ��;����ָ��1��ʾ�ļ�����. */
		fclose(fp);
	} else {
		errprintf("open %s fail"_ENDL, name);
	}

#else

	//һ���Է��������ڴ棬���ļ���ȡ�������ݣ�

	unsigned char   * p;
	long	 len, sum;
	fpos_t   len_t;
	long	 status;
	long	 loop, remain, to_read;
	int	  i;
	
	memP = NULL;
	p	= NULL;
	
	fp = fopen(name, "rb" );
	if (fp) { // ���ļ��ɹ�
		status = fseek(fp, 0, SEEK_END);
		status = fgetpos( fp, &len_t);
		memcpy(&len, &len_t, sizeof(int));
		memP   = malloc(len);
		p	  = memP;
		if (p) {
			status  = fseek(fp, 0, SEEK_SET);
			loop	= len / BYTE_NUM_ONETIME_READ;
			remain  = len % BYTE_NUM_ONETIME_READ;
			to_read = BYTE_NUM_ONETIME_READ;
			sum	 = 0;

			for (i = 0; i < loop; i++) {
				status = fread(p, sizeof(char), to_read, fp);
				sum += status;
				p += to_read; 
			}
			to_read = remain;
			if (to_read > 0) {
				status = fread(p, sizeof(char), to_read, fp);
				sum += status;			 
			}
			
			if (len != sum) { // ��������ݺ�Ҫ��Ĳ���,����
				free(memP);	 // �ͷ��ڴ�

				memP = NULL;	// ���ؿ�ָ��,��ʾʧ��
			}
		}
		else {  // �����ڴ�ʧ��

		}
		fclose(fp);	
	}

#endif

	return memP;  /* ����ָ��. */

}

static VOID ReadFontFile (RBFINFO* fontdata, void *pbuf)
{
	INT32 bits;
	UINT8 *p;
	p = pbuf;
	fontdata->font_size = *((INT32 *)p);
	p += sizeof(INT32);
	fontdata->nr_chars = *((INT32 *)p);
	p += sizeof(INT32);
	bits = *((INT32 *)p);
	p += sizeof(INT32);
	fontdata->width = *((INT32 *)p);
	p += sizeof(INT32);
	fontdata->height = *((INT32 *)p);
	p += sizeof(INT32);
	fontdata->mapper = (UINT16 *)p;
	p += (fontdata->nr_chars) * bits / 8;
	fontdata->font = (char *)p;
}

BOOL  InitDeviceFonts (VOID)
{
	char		  charset[LEN_FONT_NAME+1];
	CHARSETOPS  * char_ops;
	
	int	  i;
	int	  j;
	int	  font_sizes;
	UINT16 * bitsP;
	UINT16   data;
	UCHAR  * p;
	
	for (i = 0; i < NR_SB_DEVFONT; i++) 
	{
		fontGetCharsetFromName(sb_dev_font[i].name, charset);
		char_ops = GetCharsetOps(charset);
		sb_dev_font[i].charset_ops = char_ops;
	}
	
	for (i = 0; i < NR_MB_DEVFONT; i++) 
	{
		fontGetCharsetFromName(mb_dev_font[i].name, charset);
		char_ops = GetCharsetOps(charset);
		mb_dev_font[i].charset_ops = char_ops;
		
		if (strcmp( mb_dev_font[i].name, FONT_RBF_ROM_12X12_GB2312 ) == 0) 
		{
			p = (UCHAR *)load_fontData(HZK12_FILENAME);
			if (p) 
			{
				RBFONT_INFO(mb_dev_font[i])->font = (char *)p;
			}
			else 
			{
				goto error_init;
			}
		}

		if (strcmp(mb_dev_font[i].name, FONT_RBF_ROM_16X16_GB2312) == 0) 
		{
			p = (UCHAR *)load_fontData(HZK16_FILENAME);
			if (p) 
			{
				RBFONT_INFO(mb_dev_font[i])->font = (char *)p;
			}
			else 
			{
				goto error_init;
			}			
		}

		if (strcmp(mb_dev_font[i].name, FONT_RBF_ROM_23X30_GB2312) == 0) 
		{
			p = (UCHAR *)load_fontData(YAHEI17_FILENAME);
			if (p) 
			{
				ReadFontFile(RBFONT_INFO(mb_dev_font[i]), p);
			}
			else 
			{
				goto error_init;
			}			
		}
	}
	return TRUE;
	
error_init:
	errprintf("GDI Init error: hzk16 | hzk12 | yahei17 font file can't open !\n");
	return  FALSE;
}

VOID   TermDeviceFonts (VOID)
{
	int  i;
	for (i = 0; i < NR_MB_DEVFONT; i++) {
		if (strcmp(mb_dev_font[i].name, FONT_RBF_ROM_12X12_GB2312) == 0) {
			if (RBFONT_INFO(mb_dev_font[i])->font)
				free(RBFONT_INFO(mb_dev_font[i])->font);
		}
		
		if (strcmp(mb_dev_font[i].name, FONT_RBF_ROM_16X16_GB2312) == 0) {
			if (RBFONT_INFO(mb_dev_font[i])->font)
				free(RBFONT_INFO(mb_dev_font[i])->font);		   
		}
		
		if (strcmp(mb_dev_font[i].name, FONT_RBF_ROM_23X30_GB2312) == 0) {
			UINT8 *p = NULL;
			p = RBFONT_INFO(mb_dev_font[i])->font;
			if (p)
			{
				UINT16 *pp;
				pp = RBFONT_INFO(mb_dev_font[i])->mapper;
				pp -= sizeof(INT32) * 5;
				free(pp);
			}
		}
	}
}

