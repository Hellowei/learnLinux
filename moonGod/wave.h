/*******************************************************************************
* FILE		: wave.h
* Description	: 
*			  
* Copyright (c) 2013 by zondan. All Rights Reserved.
* 
* History:
* Version		Name	   		Date			Description
   0.1			wave.h		2013/11/16		Initial Version
   
*******************************************************************************/


#ifndef _WAVE_H_
#define _WAVE_H_


typedef enum print_wave_type{
	PRINT_WAVE_SAMPLE,	// 一般的波形
	PRINT_WAVE_FHR,		// 特殊波形,胎监波形需要断线
	PRINT_WAVE_MARK,	// 标记,因为数据远少于波形但比波形复杂,采用特殊画法
	PRINT_WAVE_STR,		// 字符标记,因为数据远少于波形但比波形复杂,采用特殊画法
}PRINT_WAVE_TYPE;

/* 波形速度 */
typedef enum {
	WAVE_SPEED_10,		/* 10 mm / min */
	WAVE_SPEED_20,
	WAVE_SPEED_30,
	WAVE_SPEED_MAX
}WAVESPEED;

#if 0
#ifndef HWND
typedef unsigned long HWND;
#endif

#ifndef GAL_PIXEL
typedef unsigned long GAL_PIXEL;
#endif

#ifndef PBITMAPMEM
typedef struct _bitmap_memory{
	short		   bits;   //图像每像素位数
	short		   free;   //是否需要释放内存
	long			cx;	 //图像的水平分辨率
	long			cy;	 //图象的垂直分辨率
	unsigned char   *data;  //图像显存
}BITMAPMEM, *PBITMAPMEM;
#endif
#endif

typedef struct __wave_base{
	HWND 		hWnd;			//	handle control
	PBITMAPMEM	background;		//	brush with background
	WAVESPEED 	*speed;			//	brush/wave speed
	char 		isBrush;		//	true:use brush
	char 		is3dBrush;		//	true:brColor[brushWidth] false:brColor[1]
	short		brushWidth;		//	brush width
	int			xPos;			//	current x position
	GAL_PIXEL 	*brColor;		//	draw brush with brColor(s)
}WAVEBASE, *PWAVEBASE;

#ifndef WAVE_GLOBALS
#define WAVE_EXT	extern
#else
#define WAVE_EXT
#endif

#endif /*_WAVE_H_*/

