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

#define   RECT_GLOBALS 
#include <string.h>
#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "gal.h"
#include "gdi.h"
#include "dc.h"

/**************************** Rectangle support ******************************/
VOID GUIAPI SetRect(RECT* prc, INT32 left, INT32 top, INT32 right, INT32 bottom)
{
	prc->left   = left;
	prc->top	= top;
	prc->right  = right;
	prc->bottom = bottom;
}

VOID GUIAPI SetRectEmpty(RECT* prc)
{
	memset(prc, 0, sizeof(RECT));
}

VOID GUIAPI CopyRect(RECT* pdrc, const RECT* psrc)
{
	memcpy(pdrc, psrc, sizeof(RECT));
}

BOOL GUIAPI IsRectEmpty(const RECT* prc)
{
	if( prc->left == prc->right )  return TRUE;
	if( prc->top  == prc->bottom ) return TRUE;
	return FALSE;
}

BOOL GUIAPI EqualRect(const RECT* prc1, const RECT* prc2)
{
	if(prc1->left   != prc2->left)   return FALSE;
	if(prc1->top	!= prc2->top)	return FALSE;
	if(prc1->right  != prc2->right)  return FALSE;
	if(prc1->bottom != prc2->bottom) return FALSE;

	return TRUE;
}

VOID GUIAPI NormalizeRect(RECT* pRect)
{
	INT32 iTemp;

	if(pRect->left > pRect->right)
	{
		 iTemp		= pRect->left;
		 pRect->left  = pRect->right;
		 pRect->right = iTemp;
	}

	if(pRect->top > pRect->bottom)
	{
		 iTemp		 = pRect->top;
		 pRect->top	= pRect->bottom;
		 pRect->bottom = iTemp;
	}
}

/**
* \brief Determines whether one rectangle covers another.
* \return TRUE if the first rectangle covers the second, otherwise FALSE.
**/
BOOL GUIAPI IsCovered(const RECT* prc1, const RECT* prc2)
{
	if ( prc2->left < prc1->left
		 || prc2->top < prc1->top
		 || prc2->right > prc1->right
		 || prc2->bottom > prc1->bottom )
		return FALSE;

	return TRUE;
}

/**
 * \brief Calculates the intersection of two rectangles.
 *
 * This function calculates the intersection of two source rectangles (\a psrc1 and \a psrc2) 
 * and places the coordinates of the intersection rectangle into the destination rectangle
 * pointed to by \a pdrc. If the source rectangles do not intersect, and empty rectangle 
 * (in which all coordinates are set to zero) is placed into the destination rectangle.
 *
 * \param pdrc The pointer to the destination rectangle.
 * \param psrc1,psrc2 Two source rectangles.
 * \return TRUE if the source rectangles intersect, otherwise FALSE.
**/
BOOL GUIAPI IntersectRect(RECT* pdrc, const RECT* psrc1, const RECT* psrc2)
{
	pdrc->left   = (psrc1->left > psrc2->left)	 ? psrc1->left : psrc2->left;
	pdrc->top	= (psrc1->top > psrc2->top)	   ? psrc1->top : psrc2->top;
	pdrc->right  = (psrc1->right < psrc2->right)   ? psrc1->right : psrc2->right;
	pdrc->bottom = (psrc1->bottom < psrc2->bottom) ? psrc1->bottom : psrc2->bottom;

	if(pdrc->left >= pdrc->right || pdrc->top >= pdrc->bottom)
		return FALSE;

	return TRUE;
}


VOID GUIAPI OffsetRect(RECT* prc, INT32 x, INT32 y)
{
	prc->left   += x;
	prc->top	+= y;
	prc->right  += x;
	prc->bottom += y;
}

VOID GUIAPI InflateRect(RECT* prc, INT32 cx, INT32 cy)
{
	prc->left   -= cx;
	prc->top	-= cy;
	prc->right  += cx;
	prc->bottom += cy;
}


BOOL GUIAPI PtInRect(const RECT* prc, INT32 x, INT32 y)
{
	if ( x >= prc->left 
		 && x < prc->right 
		 && y >= prc->top 
		 && y < prc->bottom ) 
		return TRUE;
	
	return FALSE;
}

