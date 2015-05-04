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

#ifndef __ADDRESSES_h
#define __ADDRESSES_h

/*
 *  _Addresses_Add_offset
 *
 *  DESCRIPTION:
 *
 *  This function is used to add an offset to a base address.
 *  It returns the resulting address.  This address is typically
 *  converted to an access type before being used further.
 */

VOID *_Addresses_Add_offset(VOID *base, UINT32 offset);

/*
 *  _Addresses_Subtract_offset
 *
 *  DESCRIPTION:
 *
 *  This function is used to subtract an offset from a base
 *  address.  It returns the resulting address.  This address is
 *  typically converted to an access type before being used further.
 */

VOID *_Addresses_Subtract_offset(VOID *base, UINT32 offset);

/*
 *  _Addresses_Add
 *
 *  DESCRIPTION:
 *
 *  This function is used to add two addresses.  It returns the
 *  resulting address.  This address is typically converted to an
 *  access type before being used further.
 */

VOID *_Addresses_Add(VOID *left, VOID *right);

/*
 *  _Addresses_Subtract
 *
 *  DESCRIPTION:
 *
 *  This function is used to subtract two addresses.  It returns the
 *  resulting offset.
 */

UINT32 _Addresses_Subtract(VOID *left, VOID *right);


/*
 *  _Addresses_Is_in_range
 *
 *  DESCRIPTION:
 *
 *  This function returns TRUE if the given address is within the
 *  memory range specified and FALSE otherwise.  base is the address
 *  of the first byte in the memory range and limit is the address
 *  of the last byte in the memory range.  The base address is
 *  assumed to be lower than the limit address.
 */
BOOL _Addresses_Is_in_range (VOID *address, VOID *base,VOID *limit);

BOOL  _Addresses_Equal(VOID *addr1,  VOID *addr2);
INT16 _Addresses_Compare(VOID *addr1,  VOID *addr2);


#if   0  /* 暂时不提供该功能 */
/*
 *  _Addresses_Is_aligned
 *
 *  DESCRIPTION:
 *
 *  This function returns TRUE if the given address is correctly
 *  aligned for this processor and FALSE otherwise.  Proper alignment
 *  is based on correctness and efficiency.
 */

BOOL _Addresses_Is_aligned(VOID *address);

#include "address.inl"

#endif

#endif
/* end of include file */
