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
#ifndef   _DEVFONT_H
#define   _DEVFONT_H

CHARSETOPS* GetCharsetOps (const char* charset_name);
#define  BYTE_NUM_ONETIME_READ   61440   // 60K=60X1024,一次可以读出来的数据


DEVFONT * GetMatchedSBDevFont (LOGFONT* log_font);
DEVFONT * GetMatchedMBDevFont (LOGFONT* log_font);

BOOL  InitDeviceFonts(VOID);
VOID  TermDeviceFonts(VOID);

#endif

