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
*		 根据选择系统的语言，判断选择何种字体进行显示。
* History:
******************************************************************************** 
*/  

#define  CHOICEFONT_GLOBALS
#include "includes.h"

VOID ChoiceFont(INT8 language_name)
{
	if (language_name == CHINESE || language_name == ENGLISH)
	{
		 SYSLOGFONT_SMAFONT	  =  SYSLOGFONT_WCHAR_DEF;			 // Chinese小号字体
		 SYSLOGFONT_BIGFONT	  =  SYSLOGFONT_FIXED;				 // Chinese大号字体
	#if _ENB_REC_FUNC
		 RecEventClass.pRecClass->RecSetNormalFont (RecEventClass.pRecClass, 
			(INT32)GetSystemFont(SYSLOGFONT_YAHEI17_FONT));
		 RecEventClass.pRecClass->RecSetCutterFont (RecEventClass.pRecClass, 
			(INT32)GetSystemFont(SYSLOGFONT_YAHEI17_FONT));
	#endif
	}
	else if (RUSSIAN == language_name)
	{
	    
		 SYSLOGFONT_SMAFONT	  =  SYSLOGFONT_DEF_RUS;			 // Russian小号字体
		 SYSLOGFONT_BIGFONT	  =  SYSLOGFONT_NOR_RUS;				 // Russian大号字体
	#if _ENB_REC_FUNC
	
		 RecEventClass.pRecClass->RecSetNormalFont (RecEventClass.pRecClass, 
			(INT32)GetSystemFont(SYSLOGFONT_YAHEI17_FONT));
		 RecEventClass.pRecClass->RecSetCutterFont (RecEventClass.pRecClass, 
			(INT32)GetSystemFont(SYSLOGFONT_YAHEI17_FONT));
    /*
    	 RecEventClass.pRecClass->RecSetNormalFont (RecEventClass.pRecClass, 
			(INT32)GetSystemFont(SYSLOGFONT_NOR_RUS));
		 RecEventClass.pRecClass->RecSetCutterFont (RecEventClass.pRecClass, 
			(INT32)GetSystemFont(SYSLOGFONT_NOR_RUS));
			*/
	#endif
	    
	}
	else
	{
		 SYSLOGFONT_SMAFONT	  =  SYSLOGFONT_DEF_ASC;			 // 默认小号字体
		 SYSLOGFONT_BIGFONT	  =  SYSLOGFONT_NOR_ASC;			 // 默认大号字体
	#if _ENB_REC_FUNC
		 RecEventClass.pRecClass->RecSetNormalFont (RecEventClass.pRecClass,
			(INT32)GetSystemFont(SYSLOGFONT_SMALL_PARAM));
		 RecEventClass.pRecClass->RecSetCutterFont (RecEventClass.pRecClass,
			(INT32)GetSystemFont(SYSLOGFONT_SMALL_PARAM));
	#endif
	}
}

