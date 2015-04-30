/*****************************************************************************************
版权所有:			和心重典
版本号:				1.0.0
生成日期:			2010.05.11
文件名:				
作者:				ZONDAN
功能说明:			应用层主文件
其它说明:			
所属文件关系:		本文件为工程规约代码文件

修改记录:
记录1:
修改者:
修改日期:
修改内容:
修改原因:
*****************************************************************************************/
#define   GB16X18_GLOBALS 
#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "gal.h"
#include "gdi.h"
#include "rawbmp.h"


#if _ENB_PRT16X18_FONT > 0
static UCHAR font[] =
{
/* 新宋体  13号 加粗*/
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 时
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x30,0xD8,0x30,0xF8,0x30,0xD8,0x3E,0xDB,0xF8,
0xD8,0x30,0xFB,0x30,0xD9,0xB0,0xD9,0xB0,0xD8,0x30,0xD8,0x30,0xF8,0x30,0xD8,0x30,
0x00,0xF0,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 间
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x30,0x00,0x18,0x06,0x1B,0xFE,0x70,0x06,0x60,0x66,0x67,0xE6,
0x66,0x66,0x66,0x66,0x67,0xE6,0x66,0x66,0x66,0x66,0x67,0xE6,0x60,0x06,0x60,0x06,
0x60,0x1E,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 区
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0xC0,0x1C,0xFF,0xF0,0xC0,0x60,0xF0,0x70,0xD8,0xE0,0xCE,0xC0,
0xC3,0x80,0xC3,0xC0,0xC6,0xE0,0xCC,0x70,0xD8,0x30,0xF0,0x00,0xC0,0x0C,0xFF,0xFE,
0x00,0x00,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 日
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x3F,0xF8,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
0x3F,0xF0,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x3F,0xF0,0x30,0x30,
0x00,0x00,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 分
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x06,0x60,0x0E,0x60,0x0C,0x60,0x18,0x30,0x18,0x18,0x30,0x3E,
0x7F,0xFE,0xC3,0x30,0x06,0x30,0x06,0x30,0x06,0x30,0x0C,0x30,0x18,0x30,0x30,0xE0,
0x60,0x00,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 参
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x07,0x00,0x0C,0x30,0x3F,0xFC,0x33,0x0C,0x06,0x07,0x7F,0xFC,
0x0D,0xB0,0x1B,0x9C,0x76,0x6F,0xDC,0xC0,0x03,0x98,0x0E,0x70,0x19,0xC0,0x07,0x00,
0x7C,0x00,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 数
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x0C,0x30,0x6D,0xB0,0x3F,0x60,0x3E,0x60,0xFF,0xFF,0x1E,0xEC,0x3F,0xEC,
0x6D,0xEC,0xCC,0x6C,0x1B,0xEC,0x7F,0x38,0x36,0x38,0x1E,0x38,0x1F,0xEC,0x30,0xC7,
0x63,0x80,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 选
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x63,0x60,0x33,0x60,0x1B,0x6C,0x07,0xF8,0x00,0x60,0xF8,0x66,
0x3F,0xFC,0x31,0xB0,0x31,0xB0,0x31,0xB0,0x33,0x36,0x7E,0x3E,0xCC,0x00,0xC7,0xFF,
0x00,0x00,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 择
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x1B,0xFE,0x19,0x8C,0x18,0xD8,0xFE,0x70,0x18,0x70,0x18,0xFF,
0x1F,0xF6,0x78,0x66,0xD9,0xFC,0x18,0x60,0x18,0x67,0x1B,0xFC,0x18,0x60,0x38,0x60,
0x30,0x60,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 辨
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x30,0x00,0x30,0xD8,0x06,0xC6,0x7C,0xFC,0x6C,0xF6,0x78,0xFC,0x1B,0xD8,
0xFF,0xFE,0x31,0x98,0x31,0x98,0xFD,0xFF,0x31,0x98,0x33,0x18,0x63,0x18,0xC6,0x18,
0x1C,0x18,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 率
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x03,0x00,0x01,0x80,0x7F,0xFE,0x03,0x80,0x33,0x6C,0x3E,0xD8,0x03,0xB0,
0x03,0x18,0x3E,0x6E,0x67,0xC6,0x01,0x80,0xFF,0xFF,0x01,0x80,0x01,0x80,0x01,0x80,
0x01,0x80,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 事
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x03,0x00,0x03,0x0C,0xFF,0xF8,0x03,0x00,0x3F,0xF0,0x33,0x30,0x3F,0xF8,
0x03,0x30,0x7F,0xF0,0x03,0x36,0xFF,0xFC,0x03,0x30,0x7F,0xF8,0x03,0x00,0x0F,0x00,
0x06,0x00,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 件
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x30,0x0E,0x30,0x0D,0xF0,0x0D,0xB0,0x19,0xB3,0x19,0xFE,0x3B,0x30,
0x78,0x30,0x18,0x31,0x1B,0xFF,0x18,0x30,0x18,0x30,0x18,0x30,0x18,0x30,0x18,0x30,
0x18,0x30,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 类
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x01,0x80,0x19,0x9C,0x0D,0xB0,0x0D,0xE0,0x7F,0xFE,0x07,0xF0,0x0D,0x9C,
0x19,0x86,0x71,0x80,0x03,0x86,0xFF,0xFC,0x03,0xC0,0x06,0x60,0x0C,0x38,0x38,0x0F,
0xE0,0x00,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 型
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x00,0x06,0x01,0x86,0x3F,0x36,0x1B,0x36,0x1B,0xF6,0x7F,0xF6,
0x1B,0x36,0x33,0x06,0x33,0x3E,0x63,0x1C,0xC1,0x80,0x01,0x9C,0x3F,0xF0,0x01,0x80,
0x7F,0xFF,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 全
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x07,0x00,0x07,0x00,0x0F,0x80,0x0C,0xC0,0x18,0xE0,0x30,0x70,
0x60,0x7C,0xFF,0xCC,0x03,0x00,0x03,0x00,0x3F,0xF8,0x03,0x00,0x03,0x00,0x03,0x0C,
0xFF,0xFE,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 部
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x18,0x00,0x0C,0x00,0x0D,0xBF,0x7F,0x36,0x33,0xB6,0x1B,0x3C,
0x1E,0xFC,0xFF,0xFC,0x00,0x36,0x3F,0xB6,0x33,0x33,0x33,0x33,0x33,0x3E,0x3F,0x30,
0x30,0x30,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 钟
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x30,0x38,0x30,0x30,0x30,0x3E,0x30,0x61,0xFF,0x67,0xB6,0xFD,0xB6,
0x19,0xB6,0x1F,0xB6,0x7F,0xFF,0x18,0x30,0x1E,0x30,0x1C,0x30,0x38,0x30,0x00,0x30,
0x00,0x30,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 收
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0xC0,0x0C,0xC0,0x0D,0x80,0x0D,0x86,0x6D,0xFC,0x6F,0x8C,0x6F,0x98,
0x6F,0x98,0x6C,0xD8,0x6C,0xD8,0x7C,0x70,0xCC,0x30,0x0C,0x78,0x0C,0xDC,0x0F,0x8F,
0x06,0x00,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 缩
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x60,0x30,0x30,0x33,0xFF,0x66,0x06,0x6D,0x87,0xD9,0xFC,0xF3,0x30,
0x33,0x76,0x67,0x7E,0xFF,0x66,0x03,0x66,0x03,0x7E,0x3B,0x66,0xE3,0x66,0x03,0x7E,
0x03,0x00,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 压
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x30,0x06,0x3F,0xFC,0x31,0xC0,0x31,0x80,0x31,0x80,0x31,0x80,
0x3F,0xFC,0x31,0x80,0x31,0xB0,0x31,0x9C,0x61,0x8C,0x61,0x80,0xC1,0x87,0xDF,0xFC,
0x00,0x00,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 平
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0xFF,0xFC,0x03,0x00,0x63,0x38,0x33,0x30,0x1B,0x60,0x1B,0xC0,
0x03,0x0E,0xFF,0xF8,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,
0x03,0x00,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 均
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0xC0,0x18,0xC0,0x18,0xC0,0x19,0x86,0x19,0xFE,0xFF,0x06,0x1B,0xC6,
0x18,0x66,0x18,0x66,0x18,0x06,0x1E,0x36,0x3D,0xE6,0xE3,0x06,0x00,0x06,0x00,0x3C,
0x00,0x18,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 舒
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x18,0x00,0x18,0x06,0x1E,0xFC,0x33,0x18,0x67,0x70,0x7C,0x30,
0xD8,0x07,0x1B,0xFE,0x7E,0x30,0x18,0x30,0x7F,0x30,0x63,0x30,0x63,0x30,0x7F,0x30,
0x63,0x70,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 张
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x01,0x80,0x0D,0x80,0x7D,0x8E,0x0D,0x98,0x0D,0xB0,0x7D,0xE0,
0x61,0xC0,0x61,0x87,0xFF,0xFC,0x0D,0xB0,0x0D,0xB0,0x19,0x98,0x19,0x9C,0x19,0xFF,
0x71,0xC6,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 测
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x3F,0xE6,0x3C,0xC6,0x0C,0xDE,0xCF,0xDE,0x7F,0xDE,0x7F,0xDE,
0x3F,0xDE,0x3F,0xDE,0x3F,0xDE,0x7F,0x1E,0xE3,0x1E,0x67,0xC6,0x66,0xE6,0x7C,0x6E,
0x00,0x00,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 量
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x3F,0xF0,0x30,0x30,0x3F,0xF0,0x30,0x30,0x60,0x06,0xFF,0xFC,
0x3F,0xF0,0x33,0x30,0x3F,0xF0,0x33,0x30,0x3F,0xF0,0x03,0x18,0x7F,0xF0,0xFF,0xFE,
0x00,0x00,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 当
;  宽×高（像素）: 16×18
;  字模格式/大小 : 单色点阵液晶字模，横向取模，字节正序/36字节
;  数据转换日期  : 2012-1-9 17:03:28
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x01,0x80,0x31,0x9C,0x1D,0x98,0x0D,0xB0,0x01,0xE0,0x7F,0xFE,
0x00,0x06,0x00,0x06,0x00,0x06,0x3F,0xFE,0x00,0x06,0x00,0x06,0x00,0x06,0x3F,0xFE,
0x00,0x00,0x00,0x00,
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 前
;  宽×高（像素）: 16×18
;  字模格式/大小 : 单色点阵液晶字模，横向取模，字节正序/36字节
;  数据转换日期  : 2012-1-9 17:03:28
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x0E,0x60,0x06,0xC0,0x7F,0xFE,0x00,0x18,0x33,0x0C,0x3F,0x6C,
0x33,0x6C,0x3F,0x6C,0x33,0x6C,0x33,0x6C,0x3F,0x6C,0x33,0x6C,0x33,0x0C,0x37,0x3C,
0x32,0x18,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 记
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x19,0xF8,0x18,0x0E,0x00,0x0C,0x00,0x0C,0x78,0x0C,0xD8,0xFC,
0x19,0x8C,0x19,0x80,0x19,0x80,0x1F,0x80,0x1D,0x80,0x1D,0x86,0x19,0x86,0x19,0xFF,
0x00,0x00,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 录
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x3F,0xF8,0x00,0x30,0x0F,0xF0,0x00,0x30,0x7F,0xFE,0xC1,0x80,0x31,0x8C,
0x1D,0xDC,0x0D,0xF0,0x07,0xE0,0x0D,0xB0,0x39,0x9C,0xE1,0x8F,0x03,0x86,0x03,0x00,
0x00,0x00,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 秒
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x30,0x1E,0x30,0xF8,0x30,0x18,0x30,0x18,0xFE,0xFF,0xB7,0x19,0xB3,
0x3D,0xB0,0x3F,0x36,0x7B,0x3E,0xD8,0x3C,0x18,0x18,0x18,0x30,0x18,0xE0,0x1B,0x80,
0x0E,0x00,0x00,0x00,


/* AutoAdd on 2012-3-29 15:42:18 by zimo3 */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 床
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x01,0x80,0x00,0xC0,0x3F,0xFF,0x30,0xC0,0x30,0xC0,0x30,0xC0,0x3F,0xFE,
0x31,0xC0,0x31,0xE0,0x33,0xF0,0x33,0xD8,0x36,0xCC,0x36,0xC7,0x6C,0xC6,0x78,0xC0,
0xC0,0xC0,0x00,0x00,

/* AutoAdd on 2012-3-29 15:42:30 by zimo3 */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 号
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x1F,0xF8,0x18,0x18,0x18,0x18,0x18,0x18,0x1F,0xF8,0x00,0x00,0xFF,0xFF,
0x0C,0x00,0x0C,0x00,0x1F,0xF8,0x0C,0x18,0x00,0x18,0x00,0x18,0x01,0x98,0x00,0xF0,
0x00,0x60,0x00,0x00,

/* AutoAdd on 2012-3-29 15:42:45 by zimo3 */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 波
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x30,0x60,0x18,0x60,0x18,0x60,0x07,0xFF,0xC6,0x66,0x7E,0x60,0x7E,0x60,
0x1F,0xFC,0x37,0x8C,0x36,0xD8,0xF6,0xD8,0x36,0x70,0x3C,0x70,0x3C,0xDC,0x39,0x8F,
0x37,0x06,0x00,0x00,
	
/* AutoAdd on 2012-3-29 15:43:53 by zimo3 */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 形
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x06,0x7F,0xC7,0x1B,0x0E,0x1B,0x18,0x1B,0x30,0x1B,0x0C,0xFF,0xEE,
0x1B,0x1C,0x1B,0x30,0x1B,0x66,0x1B,0xC7,0x1B,0x0E,0x33,0x18,0x33,0x30,0x63,0x60,
0xC0,0xC0,0x00,0x00,

/* AutoAdd on 2012-3-29 15:43:20 by zimo3 */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 速
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x00,0x00,0x00,0xC0,0x60,0xC0,0x3F,0xFE,0x30,0xC0,0x00,0xC0,0x07,0xFC,
0xF6,0xCC,0x36,0xCC,0x37,0xFC,0x31,0xF0,0x33,0xDC,0x3E,0xCC,0x30,0xC0,0x78,0xC0,
0xCF,0xFF,0x00,0x00,

/* AutoAdd on 2012-3-29 15:43:32 by zimo3 */
/*------------------------------------------------------------------------------
;  源文件 / 文字 : 度
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x01,0x80,0x00,0xC0,0x3F,0xFF,0x33,0x30,0x33,0x30,0x3F,0xFE,0x33,0x30,
0x33,0xF0,0x30,0x00,0x37,0xFC,0x33,0x18,0x31,0xB0,0x30,0xE0,0x61,0xB8,0x67,0x0F,
0xDC,0x06,0x00,0x00,

/*------------------------------------------------------------------------------
;  源文件 / 文字 : 洋
;  宽×高（像素）: 16×18
------------------------------------------------------------------------------*/
0x00,0x00,0x01,0x8C,0x30,0xCC,0x18,0xF8,0x00,0xDB,0x03,0xFE,0x66,0x30,0x3C,0x30,
0x3D,0xFE,0x18,0x30,0x18,0x30,0x1F,0xFF,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
0x00,0x30,0x00,0x00,
};


static char mapper[] =
"时间区日分参数选择辨率事件类型全部钟收缩压平均舒张测量当前记录秒床号波形速度洋";


RBFINFO rbf_gb16x18 = 
{
	FONT_RBF_ROM_16X18_GB2312,   //name
	39,						  //nr_chars
	16,						  //width
	18,						  //height
	(UINT16*)mapper,					  //mapper
	(UINT8*)font,						//font
	30 *  36					 //font_size
};


#endif

