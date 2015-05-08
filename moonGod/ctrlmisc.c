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

#define	CTRLMISC_GLOBALS 
#include   "includes.h"

VOID Draw3DControlFrame (HDC hdc, INT32 x0, INT32 y0, INT32 x1, INT32 y1, 
						 GAL_PIXEL fillc, BOOL updown)
{
	INT32 left, top, right, bottom;
	
	left   = MIN (x0, x1);
	top	= MIN (y0, y1);
	right  = MAX (x0, x1);
	bottom = MAX (y0, y1);
	
	if (fillc != 0) {
		SetBrushColor (hdc, fillc);
		FillRect (hdc, left + 1, top + 1, right - left - 1 , bottom - top - 1); 
	}

	if (updown) {
		SetPenColor (hdc, GetWindowElementColor (WEC_3DFRAME_RIGHT_OUTER));
		MoveTo (hdc, left, bottom);
		LineTo (hdc, left, top);
		LineTo (hdc, right, top);
		SetPenColor (hdc, GetWindowElementColor (WEC_3DFRAME_LEFT_OUTER));
		LineTo (hdc, right, bottom);
		LineTo (hdc, left, bottom);

		left++; top++; right--; bottom--;
		SetPenColor (hdc, GetWindowElementColor (WEC_3DFRAME_LEFT_INNER));
		MoveTo (hdc, left, bottom);
		LineTo (hdc, left, top);
		LineTo (hdc, right, top);
		SetPenColor (hdc, GetWindowElementColor (WEC_3DFRAME_LEFT_INNER));
		LineTo (hdc, right, bottom);
		LineTo (hdc, left, bottom);
	}
	else {
		SetPenColor (hdc, GetWindowElementColor (WEC_3DFRAME_LEFT_INNER));
		MoveTo (hdc, left, bottom);
		LineTo (hdc, left, top);
		LineTo (hdc, right, top);
		SetPenColor (hdc, GetWindowElementColor (WEC_3DFRAME_RIGHT_OUTER));
		MoveTo (hdc, left, bottom);
		LineTo (hdc, right, bottom);
		LineTo (hdc, right, top);

		left++; top++; right--; bottom--;
		SetPenColor (hdc, GetWindowElementColor (WEC_3DFRAME_LEFT_OUTER));
		MoveTo (hdc, left, bottom);
		LineTo (hdc, left, top);
		LineTo (hdc, right, top);
		SetPenColor (hdc, GetWindowElementColor (WEC_3DFRAME_LEFT_INNER));
		MoveTo (hdc, left, bottom);
		LineTo (hdc, right, bottom);
		LineTo (hdc, right, top);
	}

}

VOID DrawFlatControlFrameEx (HDC hdc, INT32 x0, INT32 y0, INT32 x1, INT32 y1, 
			GAL_PIXEL fillc, INT32 corner, BOOL updown)
{
	INT32 left, top, right, bottom;
	
	left   = MIN (x0, x1);
	top	= MIN (y0, y1);
	right  = MAX (x0, x1);
	bottom = MAX (y0, y1);
	
	if (fillc != 0) {
		SetBrushColor (hdc, fillc);
		FillRect (hdc, left, top, right - left + 1, bottom - top + 1); 
	}

	SetPenColor (hdc, GetWindowElementColor (WEC_FLAT_BORDER));

	if (corner < 1) {
		Rectangle (hdc, left, top, right, bottom);
	}

	if (updown == 1) {
		right --; bottom --;
	}

	MoveTo (hdc, left + corner, top);
	LineTo (hdc, right - corner, top);
	LineTo (hdc, right, top + corner);
	LineTo (hdc, right, bottom - corner);
	LineTo (hdc, right - corner, bottom);
	LineTo (hdc, left + corner, bottom);
	LineTo (hdc, left, bottom - corner);
	LineTo (hdc, left, top + corner);
	LineTo (hdc, left + corner, top);

	corner++;
	if (updown == 1) {
		MoveTo (hdc, right + 1, top + corner);
		LineTo (hdc, right + 1, bottom - corner);
		MoveTo (hdc, left + corner, bottom + 1);
		LineTo (hdc, right - corner + 1, bottom + 1);
	}
	else if (updown == 0) {
		MoveTo (hdc, left + corner, top + 1);
		LineTo (hdc, right - corner, top + 1);
		MoveTo (hdc, left + 1, top + corner);
		LineTo (hdc, left + 1, bottom - corner);
	}
}

