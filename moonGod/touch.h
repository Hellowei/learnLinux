/*******************************************************************************
* FILE		: touch.h
* Description	: 
*			  
* Copyright (c) 2014 by XXX. All Rights Reserved.
* 
* History:
* Version		Name       		Date			Description
   0.1			XXX			2014/03/26		Initial Version
   
*******************************************************************************/


#ifndef _TOUCH_H_
#define _TOUCH_H_


typedef struct __tagTouchPoint
{
	INT32 pressed;	/* status */
	INT32 X;		/* current point x */
	INT32 Y;		/* current point y */
	INT32 Xs;		/* press/release point x */
	INT32 Ys;		/* press/release point y */
	INT32 Xv;		/* move speed x, pixel per second */
	INT32 Yv;		/* move speed y, pixel per second */
}TOUCHPOINT;

#ifndef TOUCH_GLOBALS
#define TOUCH_EXT	extern
#else
#define TOUCH_EXT
#endif

TOUCH_EXT void TouchServer(void *pdata);
TOUCH_EXT BOOL InitTouchScreen(void);

#endif /*_TOUCH_H_*/

