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

#define   GB16X16_GLOBALS 
#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "gal.h"
#include "gdi.h"
#include "rawbmp.h"

/* Exported structure definition. */
RBFINFO rbf_gb16x16 = {
	FONT_RBF_ROM_16X16_GB2312,   //
	8836,						//
	16,						  //
	16,						  //
	NULL,						//
	(UINT8*)0xfa0000,			// check it
	8836*32					  //
};


