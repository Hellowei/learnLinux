/*****************************************************************************************
��Ȩ����:			�����ص�
�汾��:				1.0.0
��������:			2011.04.15
�ļ���:				
����:				�����ص�
����˵��:			
����˵��:			��
�����ļ���ϵ:		���ļ�Ϊ���̹�Լ�����ļ�

�޸ļ�¼:
��¼1:
�޸���:
�޸�����:
�޸�����:
�޸�ԭ��:
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
 ** ��ʹ��8086��80186��ϵ�ṹ�Ļ�����,ָ�벻�����Ե�.Ŀǰ,ʹ�õ��Ǵ��ڴ�ģʽ.
 ** ָ��ֻҪת�������Ե�.�Ƚϲ��ǰ�ȫ��.
 ** return :
 **  TRUE, ���;   FALSE,  ����.
 **/
BOOL  _Addresses_Equal(VOID *addr1,  VOID *addr2)
{
	return  (PTR2FLAT(addr1) == PTR2FLAT(addr2));
}

/**
 ** ָ��Ƚ�
 ** RETURN:
 **   0,  ���;
 **   1,  addr1 ���� addr2;
 **   -1, addr1 С�� addr2;
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

