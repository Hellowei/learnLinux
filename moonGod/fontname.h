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
#ifndef   _FONTNAME_H
#define   _FONTNAME_H

int fontGetFontTypeFromName (const char* name);
int fontGetTypeNameFromName (const char* name, char* type);
int fontConvertFontType (const char* type);

BOOL fontGetFamilyFromName (const char* name, char* family);

DWORD fontGetStyleFromName (const char* name);
DWORD fontConvertStyle (const char* style_part);

int fontGetWidthFromName (const char* name);
int fontGetHeightFromName (const char* name);
BOOL fontGetCharsetFromName (const char* name, char* charset);
BOOL fontGetCompatibleCharsetFromName (const char* name, char* charset);


#endif

