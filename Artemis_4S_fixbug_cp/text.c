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

#define   TEXT_GLOBALS 
#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "gal.h"
#include "gdi.h"
#include "dc.h"

#include "includes.h"

#define  GRAPH_TEXT_COLOR(c)
#define  GRAPH_TEXT_BKCOLOR(c)


/* ����ʮ����(0-7)==>ʮ������λת����������ʾ�������������ң�����ʮ������λ˳���ǵ��� */
UINT8 const  DCB2HEX_TAB[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};



#define gdi_width_one_char(logfont, devfont, mchar, len, h )  (*devfont->font_ops->get_char_width) (logfont, devfont, mchar, len)

INT32 GUIAPI RuStringNum (const CHAR* text)
{
	char *upper = "��������������������������������������������������������������������";
	char *lower = "��ѧҧ�է֧�ԧ�ڧۧܧݧާߧ�������اӧ��٧��������";
	int   i;
	char *p;
	int   j;
	int string_num = 0; // modified by gjl
	for (i = 0; i < strlen(text); i++)
	{
		for (j = 0; j < 34; j++)
		{
			p = lower + j * 2;
			if (p[0] == text[i] && p[1] == text[i + 1])
				string_num++;
			p = upper + j * 2;
			if (p[0] == text[i] && p[1] == text[i + 1])
				string_num++;
		}
	}
	return string_num;
}
/**
** \brief  ���������ַ�����size��Ϣ
** \param  size, ���ڱ���������ַ�����Ϣ
**/
VOID gdi_get_TextOut_extent (PDC pdc, LOGFONT* log_font, const CHAR* text, INT32 len, SIZE* size)
{
	DEVFONT  * sbc_devfont = log_font->sbc_devfont;
	DEVFONT  * mbc_devfont = log_font->mbc_devfont; 
	INT32	  len_cur_char;
	INT32	  left_bytes = len;
	INT32	  sbc_height = (*sbc_devfont->font_ops->get_font_height) (log_font, sbc_devfont);
	INT32	  mbc_height = 0;
	pdc = pdc;
	sbc_height = sbc_height;
	mbc_height = mbc_height;
	
	if (mbc_devfont)
		mbc_height = (*mbc_devfont->font_ops->get_font_height) (log_font, mbc_devfont);
	
	/* cy is not the height when rotate font */
	size->cy = log_font->size;
	size->cx = 0;

	
	while (left_bytes) 
	{
		//��Ϊ˫�ֽ��ֿ⣬�����Ȳ��� -- empty 2011/05/11
		if (mbc_devfont != NULL) 
		{
			len_cur_char = (*mbc_devfont->charset_ops->len_first_char) (text, left_bytes);
			if (len_cur_char != 0) 
			{
				size->cx += gdi_width_one_char (log_font, mbc_devfont, text, 
												len_cur_char, mbc_height);				
				left_bytes -= len_cur_char;
				text += len_cur_char;
				continue;
			}
		}

		//Ĭ��ΪASCII���ֿ⡣ -- empty 2011/05/11
		len_cur_char = (*sbc_devfont->charset_ops->len_first_char) (text, left_bytes);
		if (len_cur_char != 0) 
		{
			size->cx += gdi_width_one_char (log_font, sbc_devfont, text,
											len_cur_char, sbc_height);
		}
		else 
		{
			break;
		}

		left_bytes -= len_cur_char;
		text += len_cur_char;
	}
}

// �������ַ��������ڸ������ȵ���������ʾ�����ַ�
// ����ʾ������Ϣ��ʱ���ַ���������������Ҫ����
INT16 GUIAPI GetTextOutLenExtent (HDC hdc, INT16 width, const CHAR* text)
{
	PDC		pdc = dc_HDC2PDC(hdc);
	LOGFONT  * log_font = pdc->pLogFont;
	DEVFONT  * sbc_devfont = log_font->sbc_devfont;
	DEVFONT  * mbc_devfont = log_font->mbc_devfont;
	INT32	  len_cur_char;
	INT32	  len = strlen(text);
	INT32	  left_bytes = len;
	INT32	  sbc_height = (*sbc_devfont->font_ops->get_font_height) (log_font, sbc_devfont);
	INT32	  mbc_height = 0;
	INT16	  x = 0;

	sbc_height = sbc_height;
	mbc_height = mbc_height;
	
	if (mbc_devfont)
		mbc_height = (*mbc_devfont->font_ops->get_font_height) (log_font, mbc_devfont);
	
	while (left_bytes) 
	{
		if (mbc_devfont != NULL) 
		{
			len_cur_char = (*mbc_devfont->charset_ops->len_first_char) (text, left_bytes);
			if (len_cur_char != 0) 
			{ // 
				x += gdi_width_one_char (log_font, mbc_devfont, text, 
												len_cur_char, mbc_height);
				if (x > width)
				{
				  return len - left_bytes;
				}
				
				left_bytes -= len_cur_char;
				text += len_cur_char;
				continue;
			}
		}

		len_cur_char = (*sbc_devfont->charset_ops->len_first_char) (text, left_bytes);
		if (len_cur_char != 0) 
		{
			x += gdi_width_one_char (log_font, sbc_devfont, text,
											len_cur_char, sbc_height);
			if (x > width)
			{
			  return len - left_bytes;
			}			
		}
		else 
		{
			break;
		}

		left_bytes -= len_cur_char;
		text += len_cur_char;
	}
	
	return len - left_bytes;
}


static INT16 GetTextOutLen(PLOGFONT pFont, INT16 width, const CHAR* text)
{
	DEVFONT  * sbc_devfont = pFont->sbc_devfont;
	DEVFONT  * mbc_devfont = pFont->mbc_devfont;
	INT32	  len_cur_char;
	INT32	  len = strlen(text);
	INT32	  left_bytes = len;
	INT32	  sbc_height = (*sbc_devfont->font_ops->get_font_height) (pFont, sbc_devfont);
	INT32	  mbc_height = 0;
	INT16	  x = 0;

	sbc_height = sbc_height;
	mbc_height = mbc_height;
	
	if (mbc_devfont)
		mbc_height = (*mbc_devfont->font_ops->get_font_height) (pFont, mbc_devfont);
	
	while (left_bytes) 
	{
		if (mbc_devfont != NULL) 
		{
			len_cur_char = (*mbc_devfont->charset_ops->len_first_char) (text, left_bytes);
			if (len_cur_char != 0) 
			{ // 
				x += gdi_width_one_char (pFont, mbc_devfont, text, 
												len_cur_char, mbc_height);
				if (x > width)
				{
				  return len - left_bytes;
				}
				
				left_bytes -= len_cur_char;
				text += len_cur_char;
				continue;
			}
		}

		len_cur_char = (*sbc_devfont->charset_ops->len_first_char) (text, left_bytes);
		if (len_cur_char != 0) 
		{
			x += gdi_width_one_char (pFont, sbc_devfont, text,
											len_cur_char, sbc_height);
			if (x > width)
			{
			  return len - left_bytes;
			}		   
		}
		else 
		{
			break;
		}

		left_bytes -= len_cur_char;
		text += len_cur_char;
	}
	
	return len - left_bytes;
}

char *GetTextInLen(PLOGFONT pFont, int width, char *text)
{
	char szTmp[256];
	SIZE size;
	int  textLen;
	int  widthLen;
	strncpy(szTmp, text, 255);
	textLen = GetTextOutLen(pFont, width, szTmp);
	if (strlen(szTmp) > textLen)
	{
		gdi_get_TextOut_extent(0, pFont, "..", 2, &size);
		widthLen = width - size.cx;
		textLen = GetTextOutLen(pFont, widthLen, szTmp);
		szTmp[textLen] = '\0';
		strcat(szTmp, "....");
		textLen = GetTextOutLen(pFont, width, szTmp);
		szTmp[textLen] = '\0';
	}
	else
	{
		while(strlen(szTmp) < 256 - 2)
		{
			gdi_get_TextOut_extent(0, pFont, szTmp, strlen(szTmp), &size);
			if (size.cx >=-width)
				break;
			strcat(szTmp, " ");
		}
		szTmp[strlen(szTmp) - 1] = '\0';
	}
	strcpy(text, szTmp);
	return text;
}



CHAR* strnchr (const CHAR* s, INT32 n, INT32 c)
{
	INT32 i;
	
	for (i = 0; i < n; i++) {
		if (*s == c)
			return (CHAR *)s;

		s ++;
	}

	return NULL;
}




INT32 substrlen (const CHAR* text, INT32 len, CHAR delimiter, INT32* nr_delim)
{
	CHAR* substr;

	*nr_delim = 0;

	if ((substr = strnchr (text, len, delimiter)) == NULL)
		return len;

	len = substr - text;

	while (*substr == delimiter) {
		(*nr_delim) ++;
		substr ++;
	}

	return len;
}




INT32 GUIAPI GetFontHeight (HDC hdc)
{
	PDC pdc = dc_HDC2PDC(hdc);

	return pdc->pLogFont->size;
}



INT32 GUIAPI GetMaxFontWidth (HDC hdc)
{
	PDC		pdc		   = dc_HDC2PDC(hdc);
	DEVFONT  * sbc_devfont   = pdc->pLogFont->sbc_devfont;
	DEVFONT  * mbc_devfont   = pdc->pLogFont->mbc_devfont;
	INT32	  sbc_max_width = (*sbc_devfont->font_ops->get_max_width) (pdc->pLogFont, sbc_devfont);
	INT32	  mbc_max_width = 0;

	if (mbc_devfont)
		mbc_max_width = (*mbc_devfont->font_ops->get_max_width) (pdc->pLogFont, mbc_devfont);
	
	return (sbc_max_width > mbc_max_width) ? sbc_max_width : mbc_max_width;
}



VOID GUIAPI GetTextExtent (HDC hdc, const CHAR* spText, INT32 len, SIZE* pSize)
{
	PDC pdc;

	pdc = dc_HDC2PDC(hdc);
	if (len < 0) 
		len = strlen (spText);

	gdi_get_TextOut_extent (pdc, pdc->pLogFont, spText, len, pSize);
}

VOID GUIAPI GetTextExtentEx (PLOGFONT pLogFont, const CHAR* spText, INT32 len, SIZE *pSize)
{
	if (len < 0) 
		len = strlen (spText);

	gdi_get_TextOut_extent (HDC_SCREEN, pLogFont, spText, len, pSize);
}




static BOOL  IsGB2132andSize16(HDC hdc)
{
	PDC		pdc		   = dc_HDC2PDC(hdc);
	DEVFONT  * mbc_devfont   = pdc->pLogFont->mbc_devfont;
	int		size;

	if ( mbc_devfont ) {
		size = (* mbc_devfont->font_ops->get_font_size)(pdc->pLogFont, mbc_devfont, 0);
		if ( 16 == size 
			 && 0 == (*mbc_devfont->charset_ops->is_this_charset)(FONT_CHARSET_GB2312_1980_0) )
			 return TRUE;
	}
	return FALSE;
}


static void native_put_bmchar( HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h, UCHAR * imgP )
{
	PDC		pdc;
	GAL_PIXEL  color;
	INT32	   i;
	INT32	   j;
	INT32	   m;
	INT32	   nr_bytes;
	INT32	   remained;
	UCHAR	* p;
	int		 index;
	static UCHAR buff[800 * 3]; // �����Ϊ 512 / 3 = 170����
	GAL_COLOR bkcolor, textcolor;
	BOOL transparent = FALSE;

	pdc = dc_HDC2PDC(hdc);
	PMAINWIN pWin = (PMAINWIN)(pdc->hwnd);
	int fb_level = 0;
	if (pWin != NULL)
			fb_level = pWin->fblayer;	
	p   = imgP;
	nr_bytes = w >> 3;   // �ַ��Ŀ�Լ����ֽڵ�����
	remained = w & 0x07; // w % 8; ����ַ��Ŀ���8��������,���Ƕ����pixel��;

	coor_LP2SP(pdc, &x, &y);
	UnmapPixel(pdc->scrdev, pdc->textcolor, &textcolor);
	UnmapPixel(pdc->scrdev, pdc->bkcolor, &bkcolor);
	if (bkcolor.reserved == 0xEA)
	{
		transparent = TRUE;
	}

	for ( i = 0; i < h; i ++ ) 
	{ 
		index = 0;
		fb_getlinemem(x, y, w, buff);
		//fb_getlinemem2(fb_level,x, y, w, buff);
		for ( j = 0; j < nr_bytes; j ++ ) 
		{ // j ��ʾһ��pixel��Ҫ�����ֽ�����
			for ( m = 0; m < 8; m ++ )  
			{	
#if PIXEL_BIT_16
				unsigned short * pp = (unsigned short *)(buff + index);
				if (((*p) & DCB2HEX_TAB[m]) == 0)
				{
					if (! transparent)
						*pp = fb_color(bkcolor.r, bkcolor.g, bkcolor.b);
				}
				else
				{
					*pp = fb_color(textcolor.r, textcolor.g, textcolor.b);
				}
				index += 2;
#endif
			}
			p++;
		}
		
		for ( j = 0; j < remained; j ++ ) 
		{ // ����ַ��Ŀ���8��������,��ô��Ҫ����
#if PIXEL_BIT_16
				unsigned short * pp = (unsigned short *)(buff + index);
			if (((*p) & DCB2HEX_TAB[j]) == 0)
			{
				if (! transparent)
					*pp = fb_color(bkcolor.r, bkcolor.g, bkcolor.b);
			}
			else
			{
				*pp = fb_color(textcolor.r, textcolor.g, textcolor.b);
			}
			index += 2;
#endif	
		}
		if ( remained )  
			p ++;  // �������Ļ�, ����ָ��Ҫ���һ��

		if (!MonitorInfo.standby)
		{
			fb_putlinemem(fb_level, x, y, w, buff);
		}
			
		y ++;	 // ��ʼ����һ�еĵ�
	}
}

void native_put_bmcharEx ( HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h, UCHAR * imgP )
{
	PDC        pdc;
	GAL_PIXEL  color;
	INT32       i;
	INT32       j;
	INT32       m;
   	INT32       nr_bytes;
	INT32       remained;
	UCHAR    * p;
	int         index;
	static UCHAR buff[800 * 3]; // �����Ϊ 512 / 3 = 170����
	GAL_COLOR bkcolor, textcolor;
	BOOL transparent = FALSE;

	pdc = dc_HDC2PDC(hdc);
	PMAINWIN pWin = (PMAINWIN)(pdc->hwnd);
	int fb_level = 0;
	if (pWin != NULL)
	    	fb_level = pWin->fblayer;
    
	p   = imgP;
	nr_bytes = w>>3;   // �ַ��Ŀ�Լ����ֽڵ�����
	remained = w&0x07; // w % 8; ����ַ��Ŀ���8��������,���Ƕ����pixel��;

	coor_LP2SP(pdc, &x, &y);
	UnmapPixel(pdc->scrdev, pdc->textcolor, &textcolor);
	UnmapPixel(pdc->scrdev, pdc->bkcolor, &bkcolor);

	if (bkcolor.reserved == 0xEA)
	{
		transparent = TRUE;
	}

  //  printf("transparent = %d \n",transparent);
     
	for ( i = 0; i < h; i ++ ) 
	{ 
		// i ��ʾ�е�����,Ҳ��ʾy��Ĳ�����;
		//RELEASE_GUI_PERMIT(); //protect from block the Systime Task.
		//GET_GUI_PERMIT();

		index = 0;
		
		fb_getlinemem(x, y, w, buff);
		
		for ( j = 0; j < nr_bytes; j ++ ) 
		{ // j ��ʾһ��pixel��Ҫ�����ֽ�����
			for ( m = 0; m < 8; m ++ ) 
			{    // ÿ�λ�8����
	                	//color = ((*p) & DCB2HEX_TAB[m]) ? pdc->textcolor : pdc->textbkcolor;
              #if PIXEL_BIT_32
				if (((*p) & DCB2HEX_TAB[m]) == 0)
				{
					if (! transparent)
					{
						buff[index ++] = bkcolor.r;
						buff[index ++] = bkcolor.g;
						buff[index ++] = bkcolor.b;	
						buff[index ++] = 0 ;			
				   }
				   else
				   {
				       	index += 4;
				   }
				}   
				else
				{
					buff[index ++] = textcolor.r;
					buff[index ++] = textcolor.g;
					buff[index ++] = textcolor.b;	
					buff[index ++] = 0 ;			
				}
			#endif
              #if PIXEL_BIT_24
				if (((*p) & DCB2HEX_TAB[m]) == 0)
				{
					if (! transparent)
					{
						buff[index ++] = bkcolor.r;
						buff[index ++] = bkcolor.g;
						buff[index ++] = bkcolor.b;				
				    }
					else
					{
					    index += 3; 
					}
				}	
				else
				{
					buff[index ++] = textcolor.r;
					buff[index ++] = textcolor.g;
					buff[index ++] = textcolor.b;				
				}
			#endif

              #if PIXEL_BIT_16
              
	            unsigned short * pp = (unsigned short *)(buff + index);

				if (((*p) & DCB2HEX_TAB[m]) == 0)
				{
				  	if (! transparent)
					{  
					*pp = fb_color(bkcolor.r, bkcolor.g, bkcolor.b);
					}
				}
				else
				{
					*pp = fb_color(textcolor.r, textcolor.g, textcolor.b);
				}
               index += 2;   //test by CLY 

			#endif

              #if PIXEL_BIT_8
	              	unsigned char * pp = (unsigned char *)(buff + index);
				if (((*p) & DCB2HEX_TAB[m]) == 0)
				{
	               if (! transparent)
					{  			
					*pp = fb_color(bkcolor.r, bkcolor.g, bkcolor.b);
					}

				}
				else
				{
					*pp = fb_color(textcolor.r, textcolor.g, textcolor.b);
				}
				index += 1;
			#endif

			
			}
			p++;
		}
        
		for ( j = 0; j < remained; j ++ ) 
		{ // ����ַ��Ŀ���8��������,��ô��Ҫ����
		#if PIXEL_BIT_32
			if (((*p) & DCB2HEX_TAB[j]) == 0)
			{
               if (! transparent)
				{   
				buff[index ++] = bkcolor.r;
				buff[index ++] = bkcolor.g;
				buff[index ++] = bkcolor.b;	
				buff[index ++] = 0 ;
				}
				else
				   index += 4;			
			}
			else
			{
				buff[index ++] = textcolor.r;
				buff[index ++] = textcolor.g;
				buff[index ++] = textcolor.b;				
				buff[index ++] = 0 ;
			}	
		#endif
		#if PIXEL_BIT_24
			if (((*p) & DCB2HEX_TAB[j]) == 0)
			{
				if (! transparent)
				{
			
				buff[index ++] = bkcolor.r;
				buff[index ++] = bkcolor.g;
				buff[index ++] = bkcolor.b;		
				}
				else
				    index += 3;		
			}
			else
			{
				buff[index ++] = textcolor.r;
				buff[index ++] = textcolor.g;
				buff[index ++] = textcolor.b;				
			}	
		#endif


	       #if PIXEL_BIT_16
	        	unsigned short * pp = (unsigned short *)(buff + index);
			if (((*p) & DCB2HEX_TAB[j]) == 0)
			{
                if (! transparent)
			   	     *pp = fb_color(bkcolor.r, bkcolor.g, bkcolor.b);
			}
			else
			{
				*pp = fb_color(textcolor.r, textcolor.g, textcolor.b);
			}
			index += 2;
			#endif		
	
	       #if PIXEL_BIT_8
	        	unsigned char * pp = (unsigned char *)(buff + index);
			if (((*p) & DCB2HEX_TAB[j]) == 0)
			{
			  if (! transparent)
				*pp = fb_color(bkcolor.r, bkcolor.g, bkcolor.b);
			}
			else
			{
				*pp = fb_color(textcolor.r, textcolor.g, textcolor.b);
			}
			index += 1;
			#endif			

		}

		if ( remained )  
			p ++;  // �������Ļ�, ����ָ��Ҫ���һ��

		fb_putlinemem_ex(fb_level, x, y, w, buff);
			
		y ++;     // ��ʼ����һ�еĵ�
	}
}

static VOID  put_bitmap_char( HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h, UCHAR * imgP )
{
	native_put_bmchar(hdc, x, y, w, h, imgP);
}

void  put_bitmap_charEx( HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h, UCHAR * imgP )
{
    native_put_bmcharEx(hdc, x, y, w, h, imgP);
}

static INT32 gdi_put_strn (HDC hdc, INT32 x, INT32 y, const CHAR* text, INT32 len)
{
	PDC		pdc		   = dc_HDC2PDC(hdc);
	DEVFONT  * sbc_devfont   = pdc->pLogFont->sbc_devfont;
	DEVFONT  * mbc_devfont   = pdc->pLogFont->mbc_devfont;
	long	   len_cur_char;
	long	   left_bytes = len; // �д�������ַ��ֽ�����
	long	   origx = x;
	long	   sbc_height = (*sbc_devfont->font_ops->get_font_height)(pdc->pLogFont,
																	  sbc_devfont);
	long	   mbc_height = 0;
	long	   sbc_width  = 0;
	long	   mbc_width  = 0;
	UCHAR	* imgP;
	UINT8	  err;

	if (mbc_devfont)
	{
		mbc_height = (*mbc_devfont->font_ops->get_font_height) (pdc->pLogFont, mbc_devfont);
	}

	while (left_bytes) 
	{
	
		RELEASE_GUI_PERMIT();
		GET_GUI_PERMIT();
				
		if (mbc_devfont != NULL)	 // ���ڶ��ֽ��ַ�������
		{   
			len_cur_char = (*mbc_devfont->charset_ops->len_first_char)(text, left_bytes);
			if (len_cur_char != 0)  // ��ǰ�ַ���������豸����
			{
				mbc_width = (*mbc_devfont->font_ops->get_char_width)(pdc->pLogFont,mbc_devfont,
																	 text, len_cur_char);
				imgP = (UCHAR *)(*mbc_devfont->font_ops->get_char_bitmap)(pdc->pLogFont,mbc_devfont, 
																		  text, len_cur_char);
				put_bitmap_char (hdc, x, y, mbc_width, mbc_height, imgP);
				
				x += mbc_width; // ����x����, ��������ֽڵݼ�, �ı�ָ������ƶ�;
				left_bytes -= len_cur_char;
				text += len_cur_char;
				continue;
			}
		}

		// ���ֽ��ַ������崦��
		len_cur_char = (*sbc_devfont->charset_ops->len_first_char) (text, left_bytes);
		if (len_cur_char != 0) 
		{
			sbc_width = (*sbc_devfont->font_ops->get_char_width)(pdc->pLogFont,sbc_devfont,
																 text, len_cur_char);
			imgP = (UCHAR *)(*sbc_devfont->font_ops->get_char_bitmap)(pdc->pLogFont,sbc_devfont, 
																	  text, len_cur_char);
			put_bitmap_char (hdc, x, y, sbc_width, sbc_height, imgP);
		}
		else 
		{
			break; // �����ڸ��ַ���; �˳�����
		}
		// ����x����, ��������ֽڵݼ�, �ı�ָ������ƶ�;
		x += sbc_width;
		left_bytes -= len_cur_char;
		text += len_cur_char;
	}
	
	return x - origx;
}


INT32 gdi_put_strnEx (HDC hdc, INT32 x, INT32 y, const CHAR* text, INT32 len)
{
    PDC        pdc           = dc_HDC2PDC(hdc);
    DEVFONT  * sbc_devfont   = pdc->pLogFont->sbc_devfont;
    DEVFONT  * mbc_devfont   = pdc->pLogFont->mbc_devfont;
    long       len_cur_char;
    long       left_bytes = len; // �д�������ַ��ֽ�����
    long       origx = x;
    long       sbc_height = (*sbc_devfont->font_ops->get_font_height)(pdc->pLogFont,
                                                                      sbc_devfont);
    long       mbc_height = 0;
    long       sbc_width  = 0;
    long       mbc_width  = 0;
    UCHAR    * imgP;


    if (mbc_devfont) 
    {
        mbc_height = (*mbc_devfont->font_ops->get_font_height) (pdc->pLogFont, mbc_devfont);
    }

    while (left_bytes) 
    {            
        if (mbc_devfont != NULL) {   // ���ڶ��ֽ��ַ�������
            len_cur_char = (*mbc_devfont->charset_ops->len_first_char)((const UCHAR*)text, left_bytes);
            if (len_cur_char != 0) { // ��ǰ�ַ���������豸����
                mbc_width = (*mbc_devfont->font_ops->get_char_width)(pdc->pLogFont,mbc_devfont,
                                                                     (const UCHAR*)text, len_cur_char);
                imgP = (UCHAR *)(*mbc_devfont->font_ops->get_char_bitmap)(pdc->pLogFont,mbc_devfont, 
                                                                          (const UCHAR*)text, len_cur_char);
                put_bitmap_charEx (hdc, x, y, mbc_width, mbc_height, imgP);

                
                x += mbc_width; // ����x����, ��������ֽڵݼ�, �ı�ָ������ƶ�;
                left_bytes -= len_cur_char ;
                text += len_cur_char;
                continue;
            }
        }

        // ���ֽ��ַ������崦��
        len_cur_char = (*sbc_devfont->charset_ops->len_first_char) ((const UCHAR*)text, left_bytes);
        if (len_cur_char != 0) 
        {
            sbc_width = (*sbc_devfont->font_ops->get_char_width)(pdc->pLogFont,sbc_devfont,
                                                                 (const UCHAR*)text, len_cur_char);
            imgP = (UCHAR *)(*sbc_devfont->font_ops->get_char_bitmap)(pdc->pLogFont,sbc_devfont, 
                                                                      (const UCHAR*)text, len_cur_char);

            put_bitmap_charEx (hdc, x, y, sbc_width, sbc_height, imgP);
        }
        else 
        {
           break;
        }
        
        x += sbc_width; // ����x����, ��������ֽڵݼ�, �ı�ָ������ƶ�;
        left_bytes -= len_cur_char;
        text += len_cur_char;
    }
    return x - origx;
}
extern BOOL g_eventMark,g_changeSpeed;
INT32 GUIAPI TextOutLen (HDC hdc, INT32 x, INT32 y, const CHAR* text, INT32 len)
{
	PDC	pdc;
	RECT   rcOutput;
	SIZE   size;
    INT32  ru_str_num;
	if (len == 0) 
	    return 0;

	//panhonghui
    if (len < 0)
    {
        len = strlen (text);
        if (MonitorConfig.language == RUSSIAN)
        {
            ru_str_num = RuStringNum(text);
        }
        
    }
    
 	pdc = dc_HDC2PDC(hdc);
 	//�ı仭ˢĿ�ı���ı��ӡ�ٶ�ʱ�¼����ֳ���һ�Ű׵�
	if(g_eventMark && g_changeSpeed)//�¼����ֱ��ٵ�����£��ı仭ˢ @VinYin 2015-05-22
	{
		pdc->bkcolor = 1;
		pdc->textcolor = -1;
		pdc->pencolor = 1;
		pdc->brushcolor = 1;
	}
	
	coor_LP2SP(pdc, &x, &y); // Transfer logical to device to screen here.

	if (!PtInRect(&pdc->DevRC, x, y) ||
		!PtInRect(&pdc->DevRC, x, y + GetFontHeight(hdc)))
		 return 0;//����ַ�����ʼ�㲻��DC�Ĵ�����,�����Ƴ�;���ؼ�������Ĺ���;

	while (len)
	{  // ���뱣֤�����ַ��������DC�Ĵ�����,�������������ַ�;
	
		gdi_get_TextOut_extent (pdc, pdc->pLogFont, text, len, &size);

		rcOutput.left   = x;
		rcOutput.top	= y;
		rcOutput.right  = x + size.cx ; 
		rcOutput.bottom = y + size.cy ; 
		NormalizeRect(&rcOutput);

		if (IsCovered(&pdc->DevRC, &rcOutput))  
			break;//�����Χ����DC�Ĵ�����,��ѭ��;
		
		len --;
	}
	if (len > 0)
	{
		GRAPH_TEXT_COLOR(pdc->textcolor);
		GRAPH_TEXT_BKCOLOR(pdc->bkcolor);

		//fixed bug: ������Ĵ�����Ҫ����set_pixel,����Ҫ�����߼�����,��������Ļ����.
		coor_SP2LP(pdc, &x, &y);
		gdi_put_strn(hdc, x, y, text + strlen(text) - len, len);
	}
	else 
	{
		size.cx = 0;
	}
	return size.cx;
}


INT32 GUIAPI ScreenTextOut (HDC hdc, INT32 x, INT32 y, const CHAR* text, INT32 len)
{
    PDC    pdc;
    RECT   rcOutput;
    SIZE   size;

    if (len == 0) return 0;
    if (len < 0)  len = strlen (text); 

    pdc = dc_HDC2PDC(hdc);

    coor_LP2SP(pdc, &x, &y); // Transfer logical to device to screen here.

    if (!PtInRect(&pdc->DevRC, x, y) ||
        !PtInRect(&pdc->DevRC, x, y + GetFontHeight(hdc)))
         return 0;//����ַ�����ʼ�㲻��DC�Ĵ�����,�����Ƴ�;���ؼ�������Ĺ���;

    while (len) {  // ���뱣֤�����ַ��������DC�Ĵ�����,�������������ַ�;
    
        gdi_get_TextOut_extent (pdc, pdc->pLogFont, text, len, &size);

        rcOutput.left   = x;
        rcOutput.top    = y;
        rcOutput.right  = x + size.cx ; // + 1;
        rcOutput.bottom = y + size.cy ; // + 1;
        NormalizeRect(&rcOutput);

        if (IsCovered(&pdc->DevRC, &rcOutput))  
            break;//�����Χ����DC�Ĵ�����,��ѭ��;
            
        len --;
    }
    if (len > 0) 
    {
        GRAPH_TEXT_COLOR(pdc->textcolor);
        GRAPH_TEXT_BKCOLOR(pdc->bkcolor);
        coor_SP2LP(pdc, &x, &y);
        gdi_put_strnEx(hdc, x, y, text + strlen(text) - len, len);
    }
    else 
    {
        size.cx = 0;
    }
    return size.cx;
}

const UINT8 DC2HEX_TABEX[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
static void put_bitmap_char_ex
	( HDC hdc, INT32 x, INT32 y, INT32 w, INT32 h, UCHAR * imgP , INT32 mode)
{
	PDC 	pdc;
	GAL_PIXEL  color;
	INT32	   i;
	INT32	   j;
	INT32	   m;
	INT32	   nr_bytes;
	INT32	   remained;
	UCHAR	* p;
	int 	 index;
	static UCHAR buff[800 * 3]; // 800����
	GAL_COLOR bkcolor, textcolor;
	BOOL transparent = FALSE;
	pdc = dc_HDC2PDC(hdc);
	PMAINWIN pWin = (PMAINWIN)(pdc->hwnd);
	int fb_level = 0;
	if (pWin != NULL)
			fb_level = pWin->fblayer;	
	p	= imgP;
	nr_bytes = w >> 3;	 // �ַ��Ŀ�Լ����ֽڵ�����
	remained = (w & 0x07); // w % 8; ����ַ��ĸ߶Ȳ���8��������,���Ƕ����pixel��;
	if (remained > 0)
		nr_bytes++;
	coor_LP2SP(pdc, &x, &y);
	UnmapPixel(pdc->scrdev, pdc->textcolor, &textcolor);
	UnmapPixel(pdc->scrdev, pdc->bkcolor, &bkcolor);
	#if PIXEL_BIT_16
	UINT16 back_pixel = fb_color(bkcolor.r, bkcolor.g, bkcolor.b);
	UINT16 text_pixel = fb_color(textcolor.r, textcolor.g, textcolor.b);
	#endif

	if (bkcolor.reserved == 0xEA)
	{
		transparent = TRUE;
	}
//	printf("remained...%d\n", remained);
	for ( i = 0; i < w; i ++)
	{
		index = 0;
		if (transparent)
			fb_getlinemem(x, y, h, buff);
		for (j = 0; j < h; j++)
		{
			#if PIXEL_BIT_16
			unsigned short * pp = (unsigned short *)(buff + index);
			if (((*(p + (h - j - 1) * nr_bytes)) & DCB2HEX_TAB[i & 0x07]) == 0)
			{
				if (! transparent)
					*pp = back_pixel;
			}
			else
			{
				*pp = text_pixel;
			}
			index += 2;
			#endif
		}
		if (!MonitorInfo.standby)
			fb_putlinemem(fb_level, x, y, h, buff);
		if (i > 0 && (i & 0x07) == 0)
			p++;
		y++;
	}
	
}



static INT32 gdi_put_strn_ex
	(HDC hdc, INT32 x, INT32 y, const CHAR* text, INT32 len, INT32 mode)
{
	PDC 	pdc 	   = dc_HDC2PDC(hdc);
	DEVFONT  * sbc_devfont	 = pdc->pLogFont->sbc_devfont;
	DEVFONT  * mbc_devfont	 = pdc->pLogFont->mbc_devfont;
	long	   len_cur_char;
	long	   left_bytes = len; // �д�������ַ��ֽ�����
	long	   origx = x;
	long	   origy = y;
	long	   sbc_height = (*sbc_devfont->font_ops->get_font_height)
								(pdc->pLogFont, sbc_devfont);
	long	   mbc_height = 0;
	long	   sbc_width  = 0;
	long	   mbc_width  = 0;
	UCHAR	* imgP;
	UINT8	  err;
	CHAR	flag = (mode & 0x01);

	if (mbc_devfont)
	{
		mbc_height = (*mbc_devfont->font_ops->get_font_height)
			(pdc->pLogFont, mbc_devfont);
	}

	while (left_bytes) 
	{
	
		RELEASE_GUI_PERMIT();
		GET_GUI_PERMIT();
				
		if (mbc_devfont != NULL)	 // ���ڶ��ֽ��ַ�������
		{	
			len_cur_char = (*mbc_devfont->charset_ops->len_first_char)(text, left_bytes);
			if (len_cur_char != 0)	// ��ǰ�ַ���������豸����
			{
				mbc_width = (*mbc_devfont->font_ops->get_char_width)(pdc->pLogFont,mbc_devfont,
																	 text, len_cur_char);
				imgP = (UCHAR *)(*mbc_devfont->font_ops->get_char_bitmap)(pdc->pLogFont,mbc_devfont, 
																		  text, len_cur_char);
				put_bitmap_char_ex(hdc, x, y, sbc_width, sbc_height, imgP, mode);
				if (flag)
				{
					// ����y����, ��������ֽڵݼ�, �ı�ָ������ƶ�;
					y += pdc->pLogFont->size;
				}
				else
				{
					// ����x����, ��������ֽڵݼ�, �ı�ָ������ƶ�;
					x += mbc_width;
				}
				left_bytes -= len_cur_char;
				text += len_cur_char;
				continue;
			}
		}

		// ���ֽ��ַ������崦��
		len_cur_char = (*sbc_devfont->charset_ops->len_first_char) (text, left_bytes);
		if (len_cur_char != 0) 
		{
			sbc_width = (*sbc_devfont->font_ops->get_char_width)(pdc->pLogFont,sbc_devfont,
																 text, len_cur_char);
			imgP = (UCHAR *)(*sbc_devfont->font_ops->get_char_bitmap)(pdc->pLogFont,sbc_devfont, 
																	  text, len_cur_char);
			put_bitmap_char_ex (hdc, x, y, sbc_width, sbc_height, imgP, mode);
		}
		else 
		{
			break; // �����ڸ��ַ���; �˳�����
		}
		if (flag)
		{
			// ����y����, ��������ֽڵݼ�, �ı�ָ������ƶ�;
			y += pdc->pLogFont->size;
		}
		else
		{
			// ����x����, ��������ֽڵݼ�, �ı�ָ������ƶ�;
			x += mbc_width;
		}
		left_bytes -= len_cur_char;
		text += len_cur_char;
	}
	
	if (flag)
	{
//		printf("y ... %d\n", y);
		return y - origy;
	}
	else
	{
		return x - origx;
	}
}



INT32 GUIAPI TextOutLenEx
	(HDC hdc, INT32 x, INT32 y, const CHAR* text, INT32 len, INT32 mode)
{
	PDC	pdc;
	RECT   rcOutput;
	SIZE   size;
	CHAR	flag = (mode & 0x01);

	if (len == 0) return 0;
	if (len < 0)  len = strlen (text); 
	if (0 == mode)
	{
		return TextOutLen(hdc, x, y, text, len);
	}
	pdc = dc_HDC2PDC(hdc);

	coor_LP2SP(pdc, &x, &y); // Transfer logical to device to screen here.

	if (!PtInRect(&pdc->DevRC, x, y) ||
		!PtInRect(&pdc->DevRC, x, y + GetFontHeight(hdc)))
		 return 0;//����ַ�����ʼ�㲻��DC�Ĵ�����,�����Ƴ�;���ؼ�������Ĺ���;

	while (len)
	{  // ���뱣֤�����ַ��������DC�Ĵ�����,�������������ַ�;
	
		gdi_get_TextOut_extent (pdc, pdc->pLogFont, text, len, &size);

		rcOutput.left   = x;
		rcOutput.top	= y;
		if (flag) // ��ֱ��־
		{
			rcOutput.right  = x + size.cy ; 
			rcOutput.bottom = y + size.cx ; 
		}
		else
		{
			rcOutput.right	= x + size.cx ; 
			rcOutput.bottom = y + size.cy ; 
		}
		NormalizeRect(&rcOutput);

		if (IsCovered(&pdc->DevRC, &rcOutput))  
			break;//�����Χ����DC�Ĵ�����,��ѭ��;
			
		len --;
	}
	if (len > 0)
	{
		GRAPH_TEXT_COLOR(pdc->textcolor);
		GRAPH_TEXT_BKCOLOR(pdc->bkcolor);

		//fixed bug: ������Ĵ�����Ҫ����set_pixel,����Ҫ�����߼�����,��������Ļ����.
		coor_SP2LP(pdc, &x, &y);
		gdi_put_strn_ex(hdc, x, y, text + strlen(text) - len, len, mode);
	}
	else 
	{
		size.cx = 0;
	}
	return size.cx;
}


char *NewStrBuffer(StrBuffer * buff, int len)
{
	buff->maxlen = (((len + 3) >> 2) << 2);
	buff->string = TextNew(buff->maxlen);
	if (!buff->string)
	{
		return NULL;
	}
	memset(buff->string, '\0', buff->maxlen);
	return (buff->string);
}

// �ھ�������ʾ�ַ�
VOID TextOutWrap(HDC hdc, PRECT prc, const char *text, int len)
{
	INT32 x;
	INT32 y;
	INT32 w;
	INT32 h;
	INT16 show_len;
	INT16 show_height;
	INT16 font_height;
	INT16 spacing;
	StrBuffer strbuff;
	char  *str;
	if (len < 0)
	{
		len = strlen(text);
	}
	//printf("len=%d text =%s\n",len,text);
	x		   = prc->left;
	y		   = prc->top;
	w		   = RECTWP(prc);
	h		   = RECTHP(prc);
	str		 = NewStrBuffer(&strbuff, len + 1);
	show_len	= 0;
	show_height = 0;
	font_height = GetFontHeight(hdc);
	spacing = (font_height >> 3);
	if (spacing < 2)
	{
		spacing = 2;
	}
//	FillRect(hdc, x, y, w, h);
	while (len > 0)
	{
		text += show_len;
		show_len = GetTextOutLenExtent(hdc, w - 1, text);
		memset(strbuff.string, '\0', strbuff.maxlen);
		strncpy(str, text, show_len);
		//printf("str =%s\n",str);
		TextOut(hdc, x, y + show_height, str);
		len -= show_len;
		show_height += (font_height + spacing);
		if (show_height > h - font_height)
			break;
	}
	TextDel(str);
}


//fn:Ĭ�϶Գ����ַ����Ĵ��� 2011/06/02
BOOL GUIAPI OutlenCharDefDeal (HDC hdc, CHAR *string, INT32 width, SIZE *size)
{	
	DEVFONT	*sbc_devfont;
	DEVFONT	*mbc_devfont;
	LOGFONT	*log_font;
	INT32	len_cur_char;
	INT32	left_bytes;
	INT32	sbc_height;
	INT32	mbc_height;
	long	sbc_width ;
	long	mbc_width ;
	PDC		pdc;	

	pdc		 = dc_HDC2PDC(hdc);
	log_font	= pdc->pLogFont;
	sbc_devfont	= log_font->sbc_devfont;
	mbc_devfont	= log_font->mbc_devfont;
	sbc_height  = (*sbc_devfont->font_ops->get_font_height) (log_font, sbc_devfont);
	left_bytes  = strlen (string);

	sbc_width  = 0;
	mbc_width  = 0;

	if (mbc_devfont)
		mbc_height  = (*mbc_devfont->font_ops->get_font_height) (log_font, mbc_devfont);
	else
		mbc_height	= 0;

	while (left_bytes && ((size->cx + 8*2) > width))   //��Ϊ'.'�ַ��Ĺ̶����Ϊ8pixel�������������� -- empty 2011/06/02
	{
		if (mbc_devfont != NULL) 
		{
			len_cur_char = (*mbc_devfont->charset_ops->len_first_char) (&string[left_bytes - 2], left_bytes);
			if (len_cur_char != 0) 
			{
				mbc_width = gdi_width_one_char (log_font, mbc_devfont, &string[left_bytes - 2], len_cur_char, mbc_height);
				size->cx -= mbc_width;
				left_bytes -= len_cur_char;
				continue;
			}
		}

		len_cur_char = (*sbc_devfont->charset_ops->len_first_char) (&string[left_bytes - 1], left_bytes);
		if (len_cur_char != 0) 
		{
			sbc_width = gdi_width_one_char (log_font, sbc_devfont, &string[left_bytes - 1],len_cur_char, sbc_height);
			size->cx  -= sbc_width;
		}
		else 
			break;

		left_bytes -= len_cur_char;
	}

	//�������ֽڵĴ��� 2011/06/02
	if (left_bytes)
	{
		string[left_bytes] = '\0';
		strcat (string, "..");	
		size->cx += 8*2;
		return TRUE;
	}
	else
		return FALSE;
}




INT32 TextOutCenterLen(HDC hdc, PRECT prc, CHAR* text, INT32 len)
{
	PDC			pdc		= dc_HDC2PDC(hdc);
	PLOGFONT	pFont	= pdc->pLogFont;
	SIZE		size;
	INT32		x, y;

	GetTextExtent(hdc, text, len, &size);
	if (RECTWP(prc) <= size.cx)
	{
		prc->left++;
		prc->top++;
		x = prc->left;
		y = prc->top;
		char str[64];
		char *p = text;
		int show_len;
		show_len = GetTextOutLenExtent (hdc, RECTWP(prc) - 2, p);
		while(len > 0)
		{
			show_len = CopyWords(str, p, show_len);
			if (show_len <= 0)
				break;
			len -= show_len;
			GetTextExtent(hdc, str, -1, &size);
			x = prc->left + (RECTWP(prc) - size.cx) / 2;
			TextOut(hdc, x, y, str);
			y += size.cy;
			if (len <= 0)
			{
				break;
			}
			p += show_len;
			show_len = GetTextOutLenExtent (hdc, RECTWP(prc) - 2, p);
		}
		return (RECTWP(prc));
	}
	else
	{
		{x = prc->left + (RECTWP(prc) - size.cx) / 2;}
	}
	if (RECTHP(prc) < size.cy)
	{
		{y = prc->top;}
	}
	else
	{
		{y = prc->top + (RECTHP(prc) - size.cy) / 2;}
	}
	return TextOutLen(hdc,x,y,text, len);
}


VOID GUIAPI TextOutVLen (HDC hdc, INT32 x, INT32 y, const CHAR* text, INT32 len)
{
	PDC	 pdc;
	INT32   ontput_x;
	INT32   ontput_y;
	DEVFONT *sbc_devfont;
	DEVFONT *mbc_devfont;
	INT32   sbc_height;
	INT32   mbc_height;
	INT32   len_cur_char;
	SIZE	size;

	if (len == 0)
	{
		return;
	}
	if (len < 0)
	{
		len = strlen (text); 
	}
	pdc = dc_HDC2PDC(hdc);
	coor_LP2SP(pdc, &x, &y); // Transfer logical to device to screen here.

	if (!PtInRect(&pdc->DevRC, x, y) || !PtInRect(&pdc->DevRC, x, y + GetFontHeight(hdc)))
	{
		return;//����ַ�����ʼ�㲻��DC�Ĵ�����,�����Ƴ�;���ؼ�������Ĺ���;
	}	
	sbc_devfont = pdc->pLogFont->sbc_devfont;
	mbc_devfont = pdc->pLogFont->mbc_devfont;
	sbc_height = (*sbc_devfont->font_ops->get_font_height) (pdc->pLogFont, sbc_devfont);
	if (mbc_devfont)
	{
		mbc_height = (*mbc_devfont->font_ops->get_font_height) (pdc->pLogFont, mbc_devfont);
	}
	else
	{
		mbc_devfont = 0;
	}	
	ontput_x = x;
	ontput_y = y;
	coor_SP2LP(pdc, &ontput_x, &ontput_y);
	while (len) 
	{
		if (mbc_devfont != NULL)
		{
			len_cur_char = (*mbc_devfont->charset_ops->len_first_char)(text, len);
			if (len_cur_char != 0)
			{
				gdi_put_strn(hdc, ontput_x, ontput_y, text + strlen(text) - len, len_cur_char);
				ontput_y += mbc_height;
				len -= len_cur_char;
				text += len_cur_char;
				continue;
			}
		}

		len_cur_char = (*sbc_devfont->charset_ops->len_first_char) (text, len);
		if (len_cur_char != 0) 
		{
			gdi_put_strn(hdc, ontput_x, ontput_y, text + strlen(text) - len, len_cur_char);
			ontput_y += sbc_height;
		}
		else 
		{
			break;
		}
		len -= len_cur_char;
		text += len_cur_char;
	}
   	coor_LP2SP(pdc, &ontput_x, &ontput_y);
	size.cy = ontput_y - y;
	size.cx = 12;
	
	return;
}

#define IS_GB_CN(ch1,ch2) (ch1 >= 0xB0 && ch1 <= 0xF7 && ch2 >= 0xA1 && ch2 <= 0xFE)
INT32 VerticalTextOutLen(HDC hdc, int left, int top, const CHAR* text, INT32 len)
{
	/* �����ַ��͵����ַ�������ʾ */
	/* ���������������������ַ���ת90����ʾ */
}

INT32 GetAreaStrLen(PLOGFONT pFont, INT32 w, PCHAR str)
{
	return ((INT32)GetTextOutLen(pFont, w, str));
}

int CopyWords(char *dest, const char *src, int len)
{
	int i;
	char *p = dest;
	strncpy(dest, src, len);
	for (i = 0; i < len; i++)
	{
		if (dest[i] == '-'
			|| dest[i] == ','
			|| dest[i] == '.'
			|| dest[i] == '!'
			|| dest[i] == ' '
			|| dest[i] == '\n'
			|| dest[i] == '\0')
		{
			p = dest + i + 1;
		}
	}
	dest[len] = '\0';
	i = 0;
	if (*p == ' ')
	{
		i = 1;
	}
	if (strlen(src) != strlen(dest))
	{
		*p = '\0';
	}
	i += strlen(dest);
	return i;
}

