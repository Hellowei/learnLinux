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



#include "config.h"
#include "basetypes.h"
#include "mycommon.h"
#include "address.h"

/*PAGE
 *
 *  _Addresses_Add_offset
 *
 *  DESCRIPTION:
 *
 *  This function is used to add an offset to a base address.
 *  It returns the resulting address.  This address is typically
 *  converted to an access type before being used further.
 */

VOID *_Addresses_Add_offset (VOID *base, UINT32 offset)
{
	UCHAR *flat = PTR2FLAT(base) + offset;
	return FLAT2PTR(flat);
}

/*PAGE
 *
 *  _Addresses_Subtract_offset
 *
 *  DESCRIPTION:
 *
 *  This function is used to subtract an offset from a base
 *  address.  It returns the resulting address.  This address is
 *  typically converted to an access type before being used further.
 */

VOID *_Addresses_Subtract_offset (VOID *base, UINT32 offset)
{
	UCHAR *flat = PTR2FLAT(base) - offset;
	return FLAT2PTR(flat);
}

/*PAGE
 *
 *  _Addresses_Subtract
 *
 *  DESCRIPTION:
 *
 *  This function is used to subtract two addresses.  It returns the
 *  resulting offset.
 *
 *  NOTE:  The cast of an address to an UINT32 makes this code
 *		 dependent on an addresses being thirty two bits.
 */

UINT32 _Addresses_Subtract (VOID *left, VOID *right)
{
	return (PTR2FLAT(left) - PTR2FLAT(right));
}


/*PAGE
 *
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

BOOL  _Addresses_Is_in_range (VOID *address, VOID *base, VOID *limit)
{
	return  (PTR2FLAT(address) >= PTR2FLAT(base) && PTR2FLAT(address) <= PTR2FLAT(limit));
}

/**
 ** 在使用8086和80186体系结构的机器中,指针不是线性的.目前,使用的是大内存模式.
 ** 指针只要转化成线性的.比较才是安全的.
 ** return :
 **  TRUE, 相等;   FALSE,  不等.
 **/
BOOL  _Addresses_Equal(VOID *addr1,  VOID *addr2)
{
	return  (PTR2FLAT(addr1) == PTR2FLAT(addr2));
}

/**
 ** 指针比较
 ** RETURN:
 **   0,  相等;
 **   1,  addr1 大于 addr2;
 **   -1, addr1 小于 addr2;
 **/
INT16  _Addresses_Compare(VOID *addr1,  VOID *addr2)
{
	if (PTR2FLAT(addr1) == PTR2FLAT(addr2))
		return 0;
	else
	if (PTR2FLAT(addr1) > PTR2FLAT(addr2))
		return 1;
	else   
		return -1;
}

