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
* Filename :
* Programmer(s):
*				 
* Created :
* Description : 
*		所有和更改字体有关的数据结构,常量,宏,函数声明和数据定义,声明.
*
* History:
******************************************************************************** 
*/

#ifndef _CHOICEFONT_H

#define _CHOICEFONT_H

#ifdef  CHOICEFONT_GLOBALS
#define CHOICEFONT_EXTERN  
#else
#define CHOICEFONT_EXTERN   extern
#endif

CHOICEFONT_EXTERN INT8 SYSLOGFONT_SMAFONT;						   // 小号字体 8*12 ascii  12*12 hzk
CHOICEFONT_EXTERN INT8 SYSLOGFONT_BIGFONT;						   // 大号字体 8*16 ascii  16*16 hzk

CHOICEFONT_EXTERN VOID ChoiceFont(INT8 language_name);				   // 选择字体的函数

#endif

