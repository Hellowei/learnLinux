/*
******************************************************************************** 
*								
*		   (c) Copyright 2005, TM Electronic Technology, Inc.
* 
* All rights reserved. TM’s source code is an unpublished work and the 
* use of a copyright notice does not imply otherwise. This source code contains 
* confidential, trade secret material of TM, Inc. Any attempt or participation 
* in deciphering, decoding, reverse engineering or in any way altering the source 
* code is strictly prohibited, unless the prior written consent of TM is obtained. 
* 
* Filename :  charset.c
* Programmer(s): eric 
*				 
* Created :   2005/10/10 
* Description : 
*	   gdi. 
* History:
*	 Name		  Date			   Remark
*	 eric		  2005/10/10		 Created initial version 1.0
******************************************************************************** 
*/

#define   CHARSET_GLOBALS 

#include <string.h>
#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "gal.h"
#include "gdi.h"
#include "dc.h"

#ifndef EXAM_ASSERT
#define EXAM_ASSERT(a)
#endif

/*************** Common Operations for single byte charsets ******************/

/**
	返回多字节字符串中第一个属于该字符集的字符的长度。若不属于该字符集，则返回 0;
	单位: byte;
**/
static INT32 sb_len_first_char (const UCHAR* mstr, INT32 len)
{
	if (len < 1)		return 0;
	if (*mstr != '\0')  return 1;
	return 0;
}

/**
	返回某个字符在该字符集中的位置。该信息可以由设备字体使用，用来从一个字体文件中
	获取该字符对应的宽度或点阵
**/
static INT32 sb_char_offset (const UCHAR* mchar)
{
	return (INT32)(*mchar);
}

/**
	计算字符串中属于该字符集的字符个数并返回。注意，传入的字符串必须均为该字符集字符.
**/
static INT32 sb_nr_chars_in_str (const UCHAR* mstr, INT32 mstrlen)
{
	mstr = mstr;
	return mstrlen;
}

/**
	返回某个多字节字符串中属于该字符集的子字符串长度。如果第一个字符不属于该字符集，
	则返回为 0。 
**/
static INT32 sb_len_first_substr (const UCHAR* mstr, INT32 mstrlen)
{
	mstr = mstr;
	return mstrlen;
}

/**
	该函数返回多字节字符串中属于该字符集的第一个字符的位置。 
**/
static INT32 sb_pos_first_char (const UCHAR* mstr, INT32 len)
{
	mstr = mstr;
	len  = len;
	return 0;
}

/**
	返回多字节字符串中属于该字符集的字符串中下一个单词的信息。对欧美语言来说，
	单词之间由空格、标点符号、制表符等相隔；对亚洲语言来说，单词通常定义为字符。 
**/
static const UCHAR* sb_get_next_word (const UCHAR* mstr,
											INT32 mstrlen, 
											WORDINFO* word_info)
{
	INT32 i;

	if (mstrlen == 0) return NULL;

	word_info->len		   = 0;
	word_info->delimiter	 = '\0';
	word_info->nr_delimiters = 0;

	for (i = 0; i < mstrlen; i++) {
		switch (mstr [i]) {
		case ' ':
		case '\t':
		case '\n':
		case '\r':
			if (word_info->delimiter == '\0') {  //第一次进入
				word_info->delimiter = mstr [i];
				word_info->nr_delimiters ++;
			}
			else if (word_info->delimiter == mstr[i])
				word_info->nr_delimiters ++;	 //分隔符累加
			else
				return mstr + word_info->len + word_info->nr_delimiters;//返回下一个单词的位置
		break;

		default:
			if (word_info->delimiter != '\0')
				break; // 已经找寻到了分隔符

			word_info->len ++; // 单词长度累加;
			break;
		}
	}
			
	return mstr + word_info->len + word_info->nr_delimiters;
}

/************************* ISO8859-1 Specific Operations **********************/
static INT32 iso8859_1_is_this_charset (const UCHAR* charset)
{
	INT32 i;
	char name [LEN_FONT_NAME + 1];

	for (i = 0; i < LEN_FONT_NAME + 1; i++) {
		if (charset [i] == '\0')
			break;
		name [i] = toupper (charset [i]);		
	}
	name [i] = '\0';

	if (strstr (name, "ISO") && strstr (name, "8859") && strstr (name, "1"))
		return 0;

	return 1;
}

static CHARSETOPS CharsetOps_iso8859_1 = {
	256,
	1,
	1,
	FONT_CHARSET_ISO8859_1,
	{' '},
	sb_len_first_char,
	sb_char_offset,
	sb_nr_chars_in_str,
	iso8859_1_is_this_charset,
	sb_len_first_substr,
	sb_get_next_word,
	sb_pos_first_char,
};

/************************* ISO8859-5 Specific Operations **********************/
static INT32 iso8859_5_is_this_charset (const UCHAR* charset)
{
	INT32 i;
	char name [LEN_FONT_NAME + 1];

	for (i = 0; i < LEN_FONT_NAME + 1; i++) {
		if (charset [i] == '\0')
			break;
		name [i] = toupper (charset [i]);		
	}
	name [i] = '\0';

	if (strstr (name, "ISO") && strstr (name, "8859") && strstr (name, "5"))
		return 0;

	return 1;
}

static CHARSETOPS CharsetOps_iso8859_5 = {
	256,
	1,
	1,
	FONT_CHARSET_ISO8859_5,
	{' '},
	sb_len_first_char,
	sb_char_offset,
	sb_nr_chars_in_str,
	iso8859_5_is_this_charset,
	sb_len_first_substr,
	sb_get_next_word,
	sb_pos_first_char,
};

/*************** Common Operations for double bytes charsets ******************/
#if defined(_GB_SUPPORT) | defined(_BIG5_SUPPORT) | defined (_EUCKR_SUPPORT) | defined(_UJIS_SUPPORT)

/**
*   计算字符串中属于该字符集的字符个数并返回。
*   注意，传入的字符串必须均为该字符集字符!!!
**/
static INT32 db_nr_chars_in_str (const UCHAR* mstr, INT32 len)
{
	EXAM_ASSERT ((len % 2) == 0);
	mstr = mstr;
	return len >> 1;
}

/**
* 返回多字节字符串中属于该字符集的字符串中下一个单词的信息。对欧美语言来说，单词之间由空格、
* 标点符号、制表符等相隔；对亚洲语言来说，单词通常定义为字符
**/
static const UCHAR* db_get_next_word (const UCHAR* mstr,
											INT32 mstrlen, 
											WORDINFO* word_info)
{
	EXAM_ASSERT ((mstrlen % 2) == 0);

	if (mstrlen == 0) return NULL;

	word_info->len = 2;
	word_info->delimiter = '\0';
	word_info->nr_delimiters = 0;

	return mstr + 2;
}

#endif

/************************* GB2312 Specific Operations ************************/

#ifdef _GB_SUPPORT

/* 返回多字节字符串中第一个属于该字符集的字符的长度。若不属于该字符集，则返回 0  */
static INT32 gb2312_len_first_char (const UCHAR* mstr, INT32 len)
{
	UCHAR ch1;
	UCHAR ch2;

	if (len < 2) return 0;

	ch1 = mstr [0];
	if (ch1 == '\0')
		return 0;

	ch2 = mstr [1];
	if (ch1 >= 0xA1 && ch1 <= 0xFE && ch2 >= 0xA1 && ch2 <= 0xFE)
		return 2;

	return 0;
}

/* 返回某个字符在该字符集中的位置。该信息可以由设备字体使用，
   用来从一个字体文件中获取该字符对应的宽度或点阵 */
static INT32 gb2312_char_offset (const UCHAR* mchar)
{
	return ((mchar [0] - 0xA1) * 94 + mchar [1] - 0xA1);
}

static INT32 gb2312_is_this_charset (const UCHAR* charset)
{
	INT32 i;
	char name [LEN_FONT_NAME + 1];

	for (i = 0; i < LEN_FONT_NAME + 1; i++) {
		if (charset [i] == '\0')
			break;
		name [i] = toupper (charset [i]);		
	}
	name [i] = '\0';

	if (strstr (name, "GB") && strstr (name, "2312"))
		return 0;

	return 1;
}

/* 返回某个多字节字符串中属于该字符集的子字符串长度。如果第一个字符不属于该字符集，则返回为 0 */
static INT32 gb2312_len_first_substr (const UCHAR* mstr, INT32 mstrlen)
{
	UCHAR ch1;
	UCHAR ch2;
	INT32 i, left;
	INT32 sub_len = 0;

	left = mstrlen;
	for (i = 0; i < mstrlen; i += 2) {
		if (left < 2) return sub_len;

		ch1 = mstr [i];
		if (ch1 == '\0') return sub_len;

		ch2 = mstr [i + 1];
		if (ch1 >= 0xA1 && ch1 <= 0xFE && ch2 >= 0xA1 && ch2 <= 0xFE)
			sub_len += 2;
		else
			return sub_len;

		left -= 2;
	}

	return sub_len;
}

/* 该函数返回多字节字符串中属于该字符集的第一个字符的位置 */
static INT32 gb2312_pos_first_char (const UCHAR* mstr, INT32 mstrlen)
{
	UCHAR ch1;
	UCHAR ch2;
	INT32 i, left;

	i = 0;
	left = mstrlen;
	while (left) {
		if (left < 2) return -1;

		ch1 = mstr [i];
		if (ch1 == '\0') return -1;

		ch2 = mstr [i + 1];
		if (ch1 >= 0xA1 && ch1 <= 0xFE && ch2 >= 0xA1 && ch2 <= 0xFE)
			return i;

		i += 1;
		left -= 1;
	}

	return -1;
}

static CHARSETOPS CharsetOps_gb2312 = {
	8836,
	2,
	2,
	FONT_CHARSET_GB2312_1980_0,
	{'\xA1', '\xA1'},
	gb2312_len_first_char,
	gb2312_char_offset,
	db_nr_chars_in_str,
	gb2312_is_this_charset,
	gb2312_len_first_substr,
	db_get_next_word,
	gb2312_pos_first_char,
};
#endif /* _GB_SUPPORT */

#ifdef _BIG5_SUPPORT
/************************** BIG5 Specific Operations ************************/
static INT32 big5_len_first_char (const UCHAR* mstr, INT32 len)
{
	UCHAR ch1;
	UCHAR ch2;

	if (len < 2) return 0;

	ch1 = mstr [0];
	if (ch1 == '\0')
		return 0;

	ch2 = mstr [1];
	if (ch1 >= 0xA1 && ch1 <= 0xFE && 
			((ch2 >=0x40 && ch2 <= 0x7E) || (ch2 >= 0xA1 && ch2 <= 0xFE)))
		return 2;

	return 0;
}

static INT32 big5_char_offset (const UCHAR* mchar)
{
	if (mchar [1] & 0x80)
		return (mchar [0] - 0xA1) * 94 + mchar [1] - 0xA1;
	else
		return 94 * 94 + (mchar [0] - 0xa1) * 63 + (mchar [1] - 0x40);
}

static INT32 big5_is_this_charset (const UCHAR* charset)
{
	INT32 i;
	char name [LEN_FONT_NAME + 1];

	for (i = 0; i < LEN_FONT_NAME + 1; i++) {
		if (charset [i] == '\0')
			break;
		name [i] = toupper (charset [i]);		
	}
	name [i] = '\0';

	if (strstr (name, "BIG5"))
		return 0;

	return 1;
}

static INT32 big5_len_first_substr (const UCHAR* mstr, INT32 mstrlen)
{
	UCHAR ch1;
	UCHAR ch2;
	INT32 i, left;
	INT32 sub_len = 0;

	left = mstrlen;
	for (i = 0; i < mstrlen; i += 2) {
		if (left < 2) return sub_len;

		ch1 = mstr [i];
		if (ch1 == '\0') return sub_len;

		ch2 = mstr [i + 1];
		if (ch1 >= 0xA1 && ch1 <= 0xFE && 
				((ch2 >=0x40 && ch2 <= 0x7E) || (ch2 >= 0xA1 && ch2 <= 0xFE)))
			sub_len += 2;
		else
			return sub_len;

		left -= 2;
	}

	return sub_len;
}

static INT32 big5_pos_first_char (const UCHAR* mstr, INT32 mstrlen)
{
	UCHAR ch1;
	UCHAR ch2;
	INT32 i, left;

	i = 0;
	left = mstrlen;
	while (left) {
		if (left < 2) return -1;

		ch1 = mstr [i];
		if (ch1 == '\0') return -1;

		ch2 = mstr [i + 1];
		if (ch1 >= 0xA1 && ch1 <= 0xFE && 
				((ch2 >=0x40 && ch2 <= 0x7E) || (ch2 >= 0xA1 && ch2 <= 0xFE)))
			return i;

		i += 1;
		left -= 1;
	}

	return -1;
}

static CHARSETOPS CharsetOps_big5 = {
	14758,
	2,
	2,
	FONT_CHARSET_BIG5,
	{'\xA1', '\x40'},
	big5_len_first_char,
	big5_char_offset,
	db_nr_chars_in_str,
	big5_is_this_charset,
	big5_len_first_substr,
	db_get_next_word,
	big5_pos_first_char,
};
#endif /* _BIG5_SUPPORT */

#ifdef _EUCKR_SUPPORT
/************************* EUCKR Specific Operations ************************/
static INT32 euckr_len_first_char (const UCHAR* mstr, INT32 len)
{
	UCHAR ch1;
	UCHAR ch2;

	if (len < 2) return 0;

	ch1 = mstr [0];
	if (ch1 == '\0')
		return 0;

	ch2 = mstr [1];
	if (ch1 >= 0xA1 && ch1 <= 0xFE && ch2 >= 0xA1 && ch2 <= 0xFE)
		return 2;

	return 0;
}

static INT32 euckr_char_offset (const UCHAR* mchar)
{
	if(mchar [0] > 0xAD)
		return ((mchar [0] - 0xA4) * 94 + mchar [1] - 0xA1 - 0x8E);
	else
		return ((mchar [0] - 0xA1) * 94 + mchar [1] - 0xA1 - 0x8E);
}

static INT32 euckr_is_this_charset (const UCHAR* charset)
{
	INT32 i;
	char name [LEN_FONT_NAME + 1];

	for (i = 0; i < LEN_FONT_NAME + 1; i++) {
		if (charset [i] == '\0')
			break;
		name [i] = toupper (charset [i]);
	}
	name [i] = '\0';

	if (strstr (name, "EUCKR") )
		return 0;

	return 1;
}

static INT32 euckr_len_first_substr (const UCHAR* mstr, INT32 mstrlen)
{
	UCHAR ch1;
	UCHAR ch2;
	INT32 i, left;
	INT32 sub_len = 0;

	left = mstrlen;
	for (i = 0; i < mstrlen; i += 2) {
		if (left < 2) return sub_len;

		ch1 = mstr [i];
		if (ch1 == '\0') return sub_len;

		ch2 = mstr [i + 1];
		if (ch1 >= 0xA1 && ch1 <= 0xFE && ch2 >= 0xA1 && ch2 <= 0xFE)
			sub_len += 2;
		else
			return sub_len;

		left -= 2;
	}

	return sub_len;
}

static INT32 euckr_pos_first_char (const UCHAR* mstr, INT32 mstrlen)
{
	UCHAR ch1;
	UCHAR ch2;
	INT32 i, left;

	i = 0;
	left = mstrlen;
	while (left) {
		if (left < 2) return -1;

		ch1 = mstr [i];
		if (ch1 == '\0') return -1;

		ch2 = mstr [i + 1];
		if (ch1 >= 0xA1 && ch1 <= 0xFE && ch2 >= 0xA1 && ch2 <= 0xFE)
			return i;

		i += 1;
		left -= 1;
	}

	return -1;
}

static CHARSETOPS CharsetOps_euckr = {
	8836,
	2,
	2,
	FONT_CHARSET_EUCKR,
	{'\xA1', '\xA1'},
	euckr_len_first_char,
	euckr_char_offset,
	db_nr_chars_in_str,
	euckr_is_this_charset,
	euckr_len_first_substr,
	db_get_next_word,
	euckr_pos_first_char,
};
/************************* End of EUCKR *************************************/
#endif  /* _EUCKR_SUPPORT */

#ifdef _UJIS_SUPPORT
/************************* UJIS Specific Operations ************************/
static INT32 ujis_len_first_char (const UCHAR* mstr, INT32 len)
{
	UCHAR ch1;
	UCHAR ch2;

	if (len < 2) return 0;

	ch1 = mstr [0];
	if (ch1 == '\0')
		return 0;

	ch2 = mstr [1];
	if (ch1 >= 0xA1 && ch1 <= 0xFE && ch2 >= 0xA1 && ch2 <= 0xFE)
		return 2;

	return 0;
}

static INT32 ujis_char_offset (const UCHAR* mchar)
{
	if(mchar [0] > 0xAA)
		return ((mchar [0] - 0xA6 - 0x02) * 94 + mchar [1] - 0xC1 - 0xC4);
	else
		return ((mchar [0] - 0xA1 - 0x02) * 83 + mchar [1] - 0xA1 + 0x7E);
}

static INT32 ujis_is_this_charset (const UCHAR* charset)
{
	INT32 i;
	char name [LEN_FONT_NAME + 1];

	for (i = 0; i < LEN_FONT_NAME + 1; i++) {
		if (charset [i] == '\0')
			break;
		name [i] = toupper (charset [i]);
	}
	name [i] = '\0';

	if (strstr (name, "UJIS") )
		return 0;

	return 1;
}

static INT32 ujis_len_first_substr (const UCHAR* mstr, INT32 mstrlen)
{
	UCHAR ch1;
	UCHAR ch2;
	INT32 i, left;
	INT32 sub_len = 0;

	left = mstrlen;
	for (i = 0; i < mstrlen; i += 2) {
		if (left < 2) return sub_len;

		ch1 = mstr [i];
		if (ch1 == '\0') return sub_len;

		ch2 = mstr [i + 1];
		if (ch1 >= 0xA1 && ch1 <= 0xFE && ch2 >= 0xA1 && ch2 <= 0xFE)
			sub_len += 2;
		else
			return sub_len;

		left -= 2;
	}

	return sub_len;
}

static INT32 ujis_pos_first_char (const UCHAR* mstr, INT32 mstrlen)
{
	UCHAR ch1;
	UCHAR ch2;
	INT32 i, left;

	i = 0;
	left = mstrlen;
	while (left) {
		if (left < 2) return -1;

		ch1 = mstr [i];
		if (ch1 == '\0') return -1;

		ch2 = mstr [i + 1];
		if (ch1 >= 0xA1 && ch1 <= 0xFE && ch2 >= 0xA1 && ch2 <= 0xFE)
			return i;

		i += 1;
		left -= 1;
	}

	return -1;
}


static CHARSETOPS CharsetOps_ujis = {
	8836,
	2,
	2,
	FONT_CHARSET_UJIS,
	{'\xA1', '\xA1'},
	ujis_len_first_char,
	ujis_char_offset,
	db_nr_chars_in_str,
	ujis_is_this_charset,
	ujis_len_first_substr,
	db_get_next_word,
	ujis_pos_first_char,
};
/************************* End of UJIS *************************************/
#endif /* _UJIS_SUPPORT */

/************************ Russian Specific Operations **********************/
#ifdef _RUS_SUPPORT
int GetTextIndex(char * text)
{
	int	i;
	char * p;
	char * upper = "ЮАБЦДЕФГХИЙКЛМНОПЯРСТУЖВЬЫЗШЭЩЧЪ△№";
	char * lower = "юабцдефгхийклмнопярстужвьызшэщчъ△№";

	 for (i = 0; i < 34; ++ i)
	 {
		   p = lower + i * 2;
		   if (p[0] == text[0] && p[1] == text[1])
		   return i;

		   p = upper + i * 2;
		   if (p[0] == text[0] && p[1] == text[1])
		   return i + 34;
	 }
	 return -1;
}
/* 返回多字节字符串mstr中第一个属于该字符集的字符的长度。若不属于该字符集，则返回 0  */
static INT32 russian_len_first_char (const UCHAR* mstr, INT32 len)
{
	UCHAR ch1;
	UCHAR ch2;

	if (len < 2) return 0;

	ch1 = mstr [0];
	if (ch1 == '\0')
		return 0;

	if (GetTextIndex((char *)mstr) >= 0)
		return 2;

	return 0;
}

/* 返回某个字符在该字符集中的位置。该信息可以由设备字体使用，
   用来从一个字体文件中获取该字符对应的宽度或点阵 */
static INT32 russian_char_offset (const UCHAR* mchar)
{
	return GetTextIndex((char *)mchar);
}

static INT32 russian_is_this_charset (const UCHAR* charset)
{
	INT32 i;
	char name [LEN_FONT_NAME + 1];

	return 0;
}

/* 返回某个多字节字符串中属于该字符集的子字符串长度。如果第一个字符不属于该字符集，则返回为 0 */
static INT32 russian_len_first_substr (const UCHAR* mstr, INT32 mstrlen)
{
	UCHAR ch1;
	UCHAR ch2;
	INT32 i, left;
	INT32 sub_len = 0;

	left = mstrlen;
	for (i = 0; i < mstrlen; i += 2)
	{
		if (left < 2) return sub_len;

		ch1 = mstr [i];
		if (ch1 == '\0') return sub_len;

		ch2 = mstr [i + 1];
		if (GetTextIndex((char *)mstr) >= 0)
			sub_len += 2;
		else
			return sub_len;

		left -= 2;
	}

	return sub_len;
}

/* 该函数返回多字节字符串中属于该字符集的第一个字符的位置 */
static INT32 russian_pos_first_char (const UCHAR* mstr, INT32 mstrlen)
{
	UCHAR ch1;
	UCHAR ch2;
	INT32 i, left;

	i = 0;
	left = mstrlen;
	while (left) 
	{
		if (left < 2) return -1;

		ch1 = mstr [i];
		if (ch1 == '\0') return -1;

		ch2 = mstr [i + 1];
		if (GetTextIndex((char *)mstr) >= 0)
			return i;

		i += 1;
		left -= 1;
	}

	return -1;
}

static CHARSETOPS CharsetOps_Russian = {
	68,
	2,
	2,
	FONT_CHARSET_RUSSIAN_1980_0,
	"Ф",
	russian_len_first_char,
	russian_char_offset,
	db_nr_chars_in_str,
	russian_is_this_charset,
	russian_len_first_substr,
	db_get_next_word,
	russian_pos_first_char,
};
/************************* End of Russian *************************************/
#endif/*_RUS_SUPPORT*/

#if 0
/************************ Spanish Specific Operations **********************/
#ifdef _SPAN_SUPPORT						   
static INT32 GetSpanIndex(UCHAR * text)
{
	int i;
	
	for (i = 0; i < rbf_span8x12.nr_chars; i++)
	{
		if (MAKEWORD(text[1], text[0]) == rbf_span8x12.mapper[i])
			return i;
	}
	return -1; //找不到此字符 -- empty 2011/05/11
}

/* 返回多字节字符串中第一个属于该字符集的字符的长度。若不属于该字符集，则返回 0  */
static INT32 span_len_first_char (const UCHAR* mstr, INT32 len)
{
	UCHAR ch1;

	if (len < 2) return 0;

	ch1 = mstr [0];
	if (ch1 == '\0')
		return 0;
	if (GetSpanIndex (mstr) != -1)
		return 2;
	else
		return 0;
}

/* 返回某个字符在该字符集中的位置。该信息可以由设备字体使用，
   用来从一个字体文件中获取该字符对应的宽度或点阵 */
static INT32 span_char_offset (const UCHAR* mchar)
{
	if (GetSpanIndex (mchar) != -1)
	{
		return (MAKEWORD(mchar[1], mchar[0]));
	}
}


/* 返回某个多字节字符串中属于该字符集的子字符串长度。如果第一个字符不属于该字符集，则返回为 0 */
static INT32 span_len_first_substr (const UCHAR* mstr, INT32 mstrlen)
{
	UCHAR ch1;
	UCHAR ch2;
	INT32 i, left;
	INT32 sub_len = 0;

	left = mstrlen;
	for (i = 0; i < mstrlen; i += 2)
	{
		if (left < 2) return sub_len;

		ch1 = mstr [i];
		if (ch1 == '\0') return sub_len;

		ch2 = mstr [i + 1];
		if (GetSpanIndex (mstr) >= 0)
			sub_len += 2;
		else
			return sub_len;

		left -= 2;
	}

	return sub_len;
}

static INT32 span_0_is_this_charset (const UCHAR* charset)
{
	INT32 i;
	char name [LEN_FONT_NAME + 1];

	for (i = 0; i < LEN_FONT_NAME + 1; i++) 
	{
		if (charset [i] == '\0')
			break;
		name [i] = toupper (charset [i]);		
	}
	name [i] = '\0';

	if (strstr (name, "SPAN") && strstr (name, "1980") && strstr (name, "0"))
		return 0;

	return 1;
}

/* 该函数返回多字节字符串中属于该字符集的第一个字符的位置 */
static INT32 span_pos_first_char (const UCHAR* mstr, INT32 mstrlen)
{
	UCHAR ch1;
	UCHAR ch2;
	INT32 i, left;

	i = 0;
	left = mstrlen;
	while (left) 
	{
		if (left < 2) return -1;

		ch1 = mstr [i];
		if (ch1 == '\0') return -1;

		ch2 = mstr [i + 1];
		if (GetSpanIndex (mstr) >= 0)
			return i;

		i += 1;
		left -= 1;
	}

	return -1;
}

static CHARSETOPS CharsetOps_span_0 = 
{
	2,
	2,
	2,
	FONT_CHARSET_SPAN_1980_0,
	"\xa5",										 // 待解决 Latrom_05-30-2011
	span_len_first_char,
	span_char_offset,
	db_nr_chars_in_str,
	span_0_is_this_charset,
	span_len_first_substr,
	db_get_next_word,
	span_pos_first_char,
};

#endif
/************************* End of Spanish *************************************/

#endif

static CHARSETOPS* Charsets [] =
{
	&CharsetOps_iso8859_1,
	&CharsetOps_iso8859_5,
#ifdef _GB_SUPPORT
	&CharsetOps_gb2312,
#endif
#ifdef _BIG5_SUPPORT
	&CharsetOps_big5,
#endif
#ifdef _EUCKR_SUPPORT
	&CharsetOps_euckr,
#endif
#ifdef _UJIS_SUPPORT
	&CharsetOps_ujis
#endif
#ifdef _RUS_SUPPORT
	&CharsetOps_Russian				//Change by Latrom_06-21-2011
#endif
};

#define NR_CHARSETS	 (sizeof(Charsets)/sizeof(CHARSETOPS*))

CHARSETOPS* GetCharsetOps (const char* charset_name)
{
	INT32 i;

	for (i = 0; i < NR_CHARSETS; i++) {
		if ((*Charsets [i]->is_this_charset) (charset_name) == 0)
			return Charsets [i];
	}

	return NULL;
}


