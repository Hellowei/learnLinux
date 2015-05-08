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
#define   PARSE_GLOBALS 
#include  "includes.h"

/**
 *  Unpack a pack by restoring the bit7 of all data bytes fron the first
 *  byte, the first byte will be saved in the last position of the packet
 *
 *  @param  pack	the pack that will been unpacked
 *  @param  len	 the length of given pack(include byte)
 *
 *  @return  unpacked data been stored in source pack. so be careful: you
 *		   data will be changed
 */

BOOL  UnpackWithCheckSum(UINT8 *pack, INT len)
{
	UINT8  byte;
	INT	i;
	UINT8  checkSum;
	
	if ( 2 > len )		return FALSE;

	// calculate check sum
	checkSum  = *(pack);

	if ( 2 < len )
	{
		byte = *(pack+1);
		checkSum += byte;//*(pack+2);
		
		for (i = 1; i < len - 2; i ++)
		{
			// calculate check sum
			checkSum += *(pack+i+1);
			
			*(pack+i) = (*(pack+i+1)&0x7f) | ( (byte&0x1)<<7 );
			
			byte >>= 1;
		}
	}

	if ( (checkSum & 0x7f ) != ((*(pack+len-1)) &0x7f))
		return FALSE;

	return TRUE;
}


/**
 *  Unpack a pack by restoring the bit7 of all data bytes fron the first
 *  byte, the first byte will be saved in the last position of the packet
 *
 *  @param  pack	the pack that will been unpacked
 *  @param  len	 the length of given pack(include byte)
 *
 *  @return  unpacked data been stored in source pack. so be careful: you
 *		   data will be changed
 */
BOOL  Unpack(UINT8 *pack, INT len)
{
	UINT8  byte, byteSaved;
	INT	i;

	byte = *pack;
	byteSaved = byte;

	for ( i = 0; i < len; i ++ )
	{
		*( pack + i ) = ( *( pack + i + 1 ) & 0x7f ) | (( byte & 0x1 ) << 7 );
		byte >>= 1;
	}

	*( pack + i ) = byteSaved;

	return TRUE;
}


/**
 *  Pack some bytes by storing the bit7 of all data bytes to the first byte,
 *  make the bit7 of all bytes(include byte) are 1
 *
 *  @param  pack	pack that will been packed
 *  @param  len	 number of bytes
 *
 *  @return  packed data been stored in source pack. so be careful: you
 *		   data will be changed
 */
VOID  PackWithCheckSum(UINT8 *pack, INT len)
{
	UINT8  byte;
	INT	i;
	UINT8  checkSum;
	
	// There is no need to pack a packet that length less than 3
	if ( 2 > len )		return;
	
	// make check sum, add packet id
	checkSum = *(pack);

	if ( 2 < len )
	{
		byte = 0;
		for (i = len-2; i > 1; i --)
		{
			// shift left by one bit
			byte <<= 1;
			
			// set bit7 to 1
			*(pack+i) = *(pack+i-1) | 0x80;
			
			// make check sum, add packet data
			checkSum += *(pack+i);
			
			// get bit7 in bit0 of byte
			byte |= (*(pack+i-1)&0x80) >> 7;
		}
		
		// the byte
		*(pack+1) = byte | 0x80;
		
		// make check sum, add packet BYTE
		checkSum += *(pack+1);//byte;
	}
	// write the check sum
	*(pack+len-1) = checkSum | 0x80;
}


/**
 *  Pack some bytes by storing the bit7 of all data bytes to the first byte,
 *  make the bit7 of all bytes(include byte) are 1
 *
 *  @param  pack	pack that will been packed
 *  @param  len	 number of bytes
 *
 *  @return  packed data been stored in source pack. so be careful: you
 *		   data will be changed
 */
VOID  Pack(UINT8 *pack, INT len)
{
	UINT8  byte;
	INT	i;

	// There is no need to pack a packet of length 0
	if ( 0 >= len )		return;

	byte = 0;

	for ( i = len; i > 0; i-- )
	{
		// shift left by one bit
		byte <<= 1;

		// set bit7 to 1
		*( pack + i ) = *( pack + i - 1 ) | 0x80;

		// get bit7 in bit0 of byte
		byte |= ( *( pack + i - 1 ) & 0x80 ) >> 7;
	}

	// the byte
	*pack = byte | 0x80;
}


