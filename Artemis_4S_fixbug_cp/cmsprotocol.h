
#ifndef CMSPROTOCOL_H
#define CMSPROTOCOL_H

	//���ݰ���Ϣͷ�ṹ
	typedef struct  
	{
		unsigned char   iVersion;			  //�汾
		unsigned char   iCmdKeyType;		   //����������
		unsigned short  iCmdKeyID;			 //������ID
		unsigned long   iPacketTotalLen;	   //���ܳ���
		unsigned long   iPacketTypeID;		 //������ID
		unsigned long   iCoPacketTypeID;	   //����������ID
		unsigned short  iChecksum;			 //У���
		unsigned short  iFlag;				 //��־λ
		unsigned char   iReplyCode;			//Ӧ����
		unsigned char   iReserved;			 //����λ
		unsigned short  iOptionLen;			//Option���
		unsigned char   iOption[1];			//Option��
	}__attribute__ ((packed, aligned(1))) PACKETINFOHEADER, *PPACKETINFOHEADER;
	
	//�ֶ���Ϣͷ�ṹ
	typedef struct 
	{
		unsigned short  iFieldID;			  //�ֶ�ID
		unsigned char   iDataType;			 //��������
		unsigned long   iValueLen;			 //ֵ����
		unsigned char   iValue[1];			 //ֵ
	}__attribute__ ((packed, aligned(1))) FIELDINFOHEADER, *PFIELDINFOHEADER;
	
	//���������Ͷ���
	typedef enum 
	{
		cmd_unknown,
		cmd_get_data_request,
		cmd_get_data_reply,
		cmd_set_data_request,
		cmd_set_data_reply,
		cmd_notify_packet
	}__attribute__ ((packed, aligned(1))) CMD_KEY_TYPE;
	
	//Ӧ���붨��
	typedef enum 
	{
		reply_code_success,
		reply_code_fail,
		reply_code_not_support
	}__attribute__ ((packed, aligned(1))) REPLY_CODE;
	
	typedef enum
	{
		data_type_unknown,
		data_type_byte,
		data_type_char,
		data_type_bool,
		data_type_unsigned_short,
		data_type_short,
		data_type_unsigned_int,
		data_type_int,
		data_type_char_array,
		data_type_struct,
		data_type_float,
		data_type_double
	}__attribute__ ((packed, aligned(1))) DATA_TYPE;

int ParseCMSPlusDataPacket(CProcessObject *pObject, unsigned char* pData, INT32 iDataLen);

int AppendField(unsigned char* pBuf, INT32 *iLen, FIELDINFOHEADER *pFieldInfoHeader, unsigned char *pFieldValue);

int BeginConstructPacket(unsigned char *pBuf, INT32 *iLen, PACKETINFOHEADER* pPacketInfoHeader);
int EndConstructPacket(unsigned char *pBuf, INT32 *iLen);

int AppendFieldStructArray(unsigned char *pBuf, INT32 *iLen, unsigned short iFieldID, unsigned char* pArray, INT32 iElementCount, INT32 iStructLen);
int AppendFieldStruct(unsigned char *pBuf, INT32 *iLen, unsigned short iFieldID, unsigned char* pStruct, INT32 iStructLen);

int AppendFieldFloatArray(unsigned char *pBuf, INT32 *iLen, unsigned short iFieldID, float* pArray, INT32 iElementCount);
int AppendFieldFloat(unsigned char *pBuf, INT32 *iLen, unsigned short iFieldID, float fValue);

int AppendFieldLongArray(unsigned char *pBuf, INT32 *iLen, unsigned short iFieldID, long* pArray, INT32 iElementCount);
int AppendFieldLong(unsigned char *pBuf, INT32 *iLen, unsigned short iFieldID, long iValue);

int AppendFieldULongArray(unsigned char* pBuf, INT32 *iLen, unsigned short iFieldID, INT32* pArray, INT32 iElementCount);
int AppendFieldULong(unsigned char* pBuf, INT32 *iLen, unsigned short iFieldID, INT32 iValue);

int AppendFieldShortArray(unsigned char *pBuf, INT32 *iLen, unsigned short iFieldID, short* pArray, INT32 iElementCount);
int AppendFieldShort(unsigned char *pBuf, INT32 *iLen, unsigned short iFieldID, short iValue);

int AppendFieldUShortArray(unsigned char* pBuf, INT32 *iLen, unsigned short iFieldID, unsigned short* pArray, INT32 iElementCount);
int AppendFieldUShort(unsigned char* pBuf, INT32 *iLen, unsigned short iFieldID, unsigned short iValue);

int AppendFieldCharArray(unsigned char *pBuf, INT32 *iLen, unsigned short iFieldID, char* pArray, INT32 iElementCount);
int AppendFieldWCharArray(unsigned char *pBuf, INT32 *iLen, unsigned short iFieldID, WCHAR* pArray, INT32 iElementCount);
int AppendFieldChar(unsigned char *pBuf, INT32 *iLen, unsigned short iFieldID, char iValue);

int AppendFieldByteArray(unsigned char* pBuf, INT32 *iLen, unsigned short iFieldID, unsigned char* pArray, INT32 iElementCount);
int AppendFieldByte(unsigned char* pBuf, INT32 *iLen,unsigned short iFieldID,  unsigned char iValue);

int AppendFieldBoolArray(unsigned char* pBuf, INT32 *iLen, unsigned short iFieldID, bool* pArray, INT32 iElementCount);
int AppendFieldBool(unsigned char* pBuf, INT32 *iLen,unsigned short iFieldID,  bool iValue);

int AppendStreamData(unsigned char* pBuf, INT32 *iLen,unsigned char* pData, INT32 iDataLen);
int AppendStreamDataField(unsigned char* pBuf, INT32 *nLen, unsigned short iFieldID, INT32 iTotalDataLen );
int AppendStreamDataFieldByte(unsigned char* pBuf, INT32 *iLen, unsigned short iFieldID, unsigned char byteData, INT32 iTotalDataLen);

int GetNextField(unsigned char* pData, INT32 iLen, FIELDINFOHEADER** ppFieldInfoHeader);
int GetPacketInfoHeader(unsigned char *pData, INT32 iLen, PACKETINFOHEADER** ppPacketInfoHeader);
int GetPaceketLength(UCHAR * packet_body, INT16 packet_len);
void PacketChecksum(unsigned char* pData, INT32 iPacketLen, unsigned char *pCheckSum);


#endif
