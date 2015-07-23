#define PROTOCOL_GLOBALS
#include  "includes.h"


/******************************************************************************/
/*																			*/
/*								模块协议部分								*/
/*																			*/
/******************************************************************************/
const UCHAR cUCAllCommPackSTX  = 0x55;			//协议指定的帧的起始字节
const UCHAR cUCAllCommPackSync = 0x02;			//协议指定的帧的同步字节
const UCHAR cUCAllCommPackEnd  = 0x03;			//协议指定的帧结束字节

static UCHAR UartReadBuffer[MDL_RECE_MAX_LEN];

static PACKBUFF sFetalBuff = {0};
static PACKBUFF sSysBrdBuff = {0};
static PACKBUFF sPrinterBuff = {0};
static PACKBUFF sAnalyBuff = {0};

static PACKETFRAME  sFetalPack;
static PACKETFRAME  sSysBrdPack;
static PACKETFRAME  sPrinterPack;
static PACKETFRAME2 sAnalyPack;


UCHAR GetChkSum(UCHAR *packet)
{
	int	 i;
	int	 iChkSum = 0;
	// 正确的包头
	if ((packet[0] == cUCAllCommPackSTX) && (packet[1] == cUCAllCommPackSync))
	{
		for (i = 0; i < packet[3] + 2; i++)
		{
			iChkSum += packet[2 + i];
		}
		return ((UCHAR)(iChkSum & 0xFF));
	}
	return 0;
}


static INT32 CheckPacket(PACKETFRAME *pFrame)
{
	INT32  checkSum;
	UINT8  i;
	
	if ((pFrame->frame.stx == cUCAllCommPackSTX)
		&& (pFrame->frame.sync == cUCAllCommPackSync)
		&& (pFrame->frame.end == cUCAllCommPackEnd))
	{
		checkSum = pFrame->frame.id + pFrame->frame.len;
		for (i = 0; i < pFrame->frame.len; i++)
		{
			checkSum += pFrame->frame.data[i];
		}
		if (pFrame->frame.chksum == (UCHAR)(checkSum & 0xFF))
		{
			return 0;
		}
		// 胎监包特殊处理,不需要校验
		if (pFrame->frame.id == 0x83)
		{
			return 0;
		}
	}
	#if 0
	prinfo("sFetalBuff, sSysBrdBuff, sPrinterBuff, {%d,%d,%d}{%d,%d,%d}{%d,%d,%d}\r\n",
		sFetalBuff.readIndex, sFetalBuff.prereadIndex, sFetalBuff.writeIndex,
		sSysBrdBuff.readIndex, sSysBrdBuff.prereadIndex, sSysBrdBuff.writeIndex,
		sPrinterBuff.readIndex, sPrinterBuff.prereadIndex, sPrinterBuff.writeIndex);
	prinfo("Not packet::frame.stx:0x%02X, frame.sync:0x%02X, frame.end:0x%02X\r\n",
		pFrame->frame.stx, pFrame->frame.sync, pFrame->frame.end);
	prinfo("buffer: %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
		pFrame->buffer[0],pFrame->buffer[1],pFrame->buffer[2],pFrame->buffer[3],
		pFrame->buffer[4],pFrame->buffer[5],pFrame->buffer[6],pFrame->buffer[7],
		pFrame->buffer[8],pFrame->buffer[9],pFrame->buffer[10],pFrame->buffer[11]);
	#endif
	return -1;
}


INT32 BuildPacket(UCHAR mdlID, UCHAR cmdID, UCHAR *buffer)
{
	int len;
	buffer[0] = cUCAllCommPackSTX;
	buffer[1] = cUCAllCommPackSync;
	buffer[2] = mdlID;
	len = buffer[3] + 4;
	buffer[4] = cmdID;
	//buffer[len+2] = buffer[len];//拿出data[3]值isNeedTocoAmend
	//buffer[len+3] = buffer[len+1];//拿出data[4]值0x05 
	buffer[len++] = GetChkSum(buffer);
	buffer[len++] = cUCAllCommPackEnd;
	return len;
}

INT32 BuildPacket2(PACKETFRAME *pack)
{	
	int len = pack->frame.len;
	if (len == 0) return len;
	pack->frame.stx = cUCAllCommPackSTX;
	pack->frame.sync = cUCAllCommPackSync;
	len += FIELD_OFFSET(PACKETFRAME, frame.data[0]);
	pack->buffer[len++] = GetChkSum(pack->buffer);
	pack->buffer[len++] = cUCAllCommPackEnd;
	return len;
}

// 将数据复制到数据包结构体
// 本函数数据包结构为
// Head(1)+Sync(1)+ModuleID(1)+Len(1)+data(Len)+ChkSum(1)+Tail(1)
static VOID CopyPackBuffToFrame(PACKBUFF *pBuff, PACKETFRAME *pFrame)
{
	int i;
	memset(pFrame, 0, sizeof(PACKETFRAME));
	//prinfo("pBuff->prereadIndex...%d\r\n", pBuff->prereadIndex);
	for (i = 0; i < FIELD_OFFSET(PACKETFRAME, frame.data[0]); i++)
	{
		//prinfo("pBuff->prereadIndex...%d\r\n", pBuff->prereadIndex);
		pFrame->buffer[i] = pBuff->buff[pBuff->prereadIndex++];
		if (pBuff->prereadIndex == MDL_RECE_MAX_LEN)
		{
			pBuff->prereadIndex = 0;
		}
		if (pBuff->writeIndex == pBuff->prereadIndex) return;
	}
	for ( i = 0; i < pFrame->frame.len; i++)
	{
		//prinfo("pBuff->prereadIndex...%d\r\n", pBuff->prereadIndex);
		pFrame->frame.data[i] = pBuff->buff[pBuff->prereadIndex++];
		if (pBuff->prereadIndex == MDL_RECE_MAX_LEN)
		{
			pBuff->prereadIndex = 0;
		}
		if (pBuff->writeIndex == pBuff->prereadIndex) return;
	}
	//prinfo("pBuff->prereadIndex...%d\r\n", pBuff->prereadIndex);
	pFrame->frame.chksum = pBuff->buff[pBuff->prereadIndex++];
	if (pBuff->prereadIndex == MDL_RECE_MAX_LEN)
	{
		pBuff->prereadIndex = 0;
		if (pBuff->writeIndex == pBuff->prereadIndex) return;
	}
	//prinfo("pBuff->prereadIndex...%d\r\n", pBuff->prereadIndex);
	pFrame->frame.end = pBuff->buff[pBuff->prereadIndex];
	if (pBuff->prereadIndex == MDL_RECE_MAX_LEN)
	{
		pBuff->prereadIndex = 0;
	}
#if 0
	if (pFrame->frame.id == 0x79)
	{
		prinfo("packet stx	  :0x%02X\r\n", pFrame->frame.stx);
		prinfo("packet sync	 :0x%02X\r\n", pFrame->frame.sync);
		prinfo("packet id	   :0x%02X\r\n", pFrame->frame.id);
		prinfo("packet len	  :0x%02X\r\n", pFrame->frame.len);
		for (i = 0; i < pFrame->frame.len; i++)
			prinfo("packet data[%d] :0x%02X\r\n", i, pFrame->frame.data[i]);
		prinfo("packet chksum   :0x%02X\r\n", pFrame->frame.chksum);
		prinfo("packet end	  :0x%02X\r\n", pFrame->frame.end);
	}
#endif
}


static INT32 MovePacketBuffer(PACKBUFF *pBuff, UINT32 read, UINT32 write)
{
	int i;
	if (write)
	{
		for (i = 0; i < write; i++)
		{
			
			if (++pBuff->writeIndex == MDL_RECE_MAX_LEN)
				pBuff->writeIndex = 0;
			if (pBuff->readIndex == pBuff->writeIndex)
			{
				if (++pBuff->readIndex == MDL_RECE_MAX_LEN)
					pBuff->readIndex = 0;
			}
		}
		return write;
	}
	if (read)
	{
		if (pBuff->readIndex == pBuff->writeIndex)
			return 0;
		for (i = 0; i < read; i++)
		{
			if (pBuff->readIndex == pBuff->writeIndex)
				break;
			if (++pBuff->readIndex == MDL_RECE_MAX_LEN)
				pBuff->readIndex = 0;
		}
		return i;
	}
	return 0;
}


static VOID CopyToPackBuff(PACKBUFF *pMdlBuff, UCHAR *pReadBuff, INT32 len)
{
	INT32 i;
	for (i = 0; i < len; i++)
	{
//		if (pReadBuff[2] == 0x83)
//		prinfo("pMdlBuff->buff[%d] = 0x%02X\r\n", pMdlBuff->writeIndex, pReadBuff[i]);
		pMdlBuff->buff[pMdlBuff->writeIndex] = pReadBuff[i];
		MovePacketBuffer(pMdlBuff, 0, 1);
	}
}


// 针对固定包头数据包,本函数数据包包头为cUCAllCommPackSTX:0x55
static INT32 Unpacker(PACKBUFF *pBuff, void *pFrame)
{
	// 查找包头
	if (cUCAllCommPackSTX != pBuff->buff[pBuff->prereadIndex])
	{
		pBuff->prereadIndex++;
		if (pBuff->prereadIndex == MDL_RECE_MAX_LEN)
		{
			pBuff->prereadIndex = 0;
		}
		return -2;
	}

	// 复制到包结构体
	CopyPackBuffToFrame(pBuff, pFrame);

	// 校验返回
	return CheckPacket(pFrame);
}

static INT32 CopyPackBuffToFrame2(PACKBUFF *pBuff, PACKETFRAME2 *pFrame)
{
	// 分析结果数据包有固定长度
	const INT32 len[5 + 1] = {0, 3, 6, 3, 6, 20};
	INT32 i;
	i = 0;
	memset(pFrame, 0, sizeof(PACKETFRAME));
	for (i = 0; i < 3; i++)
	{
		pFrame->buffer[i] = pBuff->buff[pBuff->prereadIndex++];
		if (pBuff->prereadIndex == MDL_RECE_MAX_LEN)
			pBuff->prereadIndex = 0;

		if (pBuff->writeIndex == pBuff->prereadIndex)
			return i;
	}
	if (pFrame->frame.id >= TABLESIZE(len))
		return 0;
	for (; i < len[pFrame->frame.id]; i++)
	{
		pFrame->frame.data[i] = pBuff->buff[pBuff->prereadIndex++];
		if (pBuff->prereadIndex == MDL_RECE_MAX_LEN)
			pBuff->prereadIndex = 0;

		if (pBuff->writeIndex == pBuff->prereadIndex)
			return 0;
	}
	return i;
}

// 针对固定包头数据包,本函数数据包包头为cUCAllCommPackSTX:0x55
static INT32 Unpacker2(PACKBUFF *pBuff, void *pFrame)
{
	// 查找包头
	if (cUCAllCommPackSTX != pBuff->buff[pBuff->prereadIndex])
	{
		pBuff->prereadIndex++;
		if (pBuff->prereadIndex == MDL_RECE_MAX_LEN)
		{
			pBuff->prereadIndex = 0;
		}
		return 0;
	}

	// 复制到包结构体
	return CopyPackBuffToFrame2(pBuff, pFrame);
}


INT32 AnalysisUnPackProc(PACKBUFF *pBuff, void *pFrame)
{
	INT32 read;
//	INT32 i;
	UCHAR	   *pread  = &UartReadBuffer[0];
	PACKBUFF	*pbuff  = &sAnalyBuff;
	PACKETFRAME2 *pPack  = &sAnalyPack;
	MdlUartRece(UART_PORT_ANALY, pread, MDL_RECE_MAX_LEN, &read);
	if (read == 0)
		return 0;
	
	CopyToPackBuff(pbuff, UartReadBuffer, read);
	
	pbuff->prereadIndex = pbuff->readIndex;
	while(pbuff->prereadIndex != pbuff->writeIndex)
	{
		if (0 > (read = Unpacker2(pbuff, pPack)))
		{
			MovePacketBuffer(pbuff, read, 0);
			AnalysisPacketFound(pPack);
		}
	}
	return read;
}


VOID FetalMdlUnPackProc(VOID)
{
	static short errcnt = 0;
	INT32 read;
	UCHAR	   *pread  = &UartReadBuffer[0];
	PACKBUFF	*pbuff  = &sFetalBuff;
	PACKETFRAME *pPack  = &sFetalPack;
	MdlUartRece(UART_PORT_FETAL, pread, MDL_RECE_MAX_LEN, &read);
	CheckFetalRcvTimeout(read);
	if (read == 0)
	{
		if (IsCommStoped(MID_FHR))//胎监通信停止 不画波形
		{	
			CHAR zeroPack[12] = {0x55, 0x02, 0x83, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03};
    		FetalPacketFound((PACKETFRAME *)zeroPack);
    	}
		return;
	}
	
	CopyToPackBuff(pbuff, UartReadBuffer, read);
	
	pbuff->prereadIndex = pbuff->readIndex;
	while(pbuff->prereadIndex != pbuff->writeIndex)
	{
		INT32 ret = Unpacker(pbuff, pPack);
		if (!ret)
		{
			ret = MovePacketBuffer(pbuff, pPack->frame.len + 6, 0);
			if (MonitorInfo.inDemo == FALSE)
				FetalPacketFound(pPack);
			errcnt = 0;
		}
		else if (ret == -1)
		{
			errcnt++;
		}
	}
	TriggerAlarm((errcnt > 2), STR_ALM_FETAL_COMM_ERR);
}


VOID SysBoardUnPackProc(VOID)
{
	INT32 readNdx;
	INT32 nrCopy;
	INT32 read;
	INT32 i;
	INT32 j;
	UCHAR	   *pread  = &UartReadBuffer[0];
	PACKBUFF	*pbuff  = &sSysBrdBuff;
	PACKETFRAME *pPack  = &sSysBrdPack;
	MdlUartRece(UART_PORT_KB, pread, MDL_RECE_MAX_LEN, &read);
	CheckKbRcvTimeout(read);
	if (read == 0)
		return;
	
	CopyToPackBuff(pbuff, UartReadBuffer, read);
	pbuff->prereadIndex = pbuff->readIndex;
	if (pbuff->writeIndex == pbuff->prereadIndex) return;
//	prinfo("UartReadBuffer[%d] = ", read);
//	for (i = 0; i < read; i++)
//	{
//		printf("0x%02X ", UartReadBuffer[i]);
//	}
//	printf("\n");
	while(pbuff->prereadIndex != pbuff->writeIndex)
	{
		if (!Unpacker(pbuff, pPack))
		{
			MovePacketBuffer(pbuff, pPack->frame.len + 6, 0);
			
			SysBrdPacketProc(pPack);
		}
	}
}

static void PrinterUnPack_PT1561P(INT32 read)
{
	INT32 i;
	INT32 j;
	PACKBUFF	*pbuff	= &sPrinterBuff;
	pbuff->prereadIndex = pbuff->readIndex;
	for (i = 0; i < read; i++)
	{
		/** HEAD, data0, data1, ..., datak, CHECK, END
			0xAA, ..............................., 0xBB **/
		if (0xAA == pbuff->buff[pbuff->prereadIndex])	// packet found
		{
			if (pbuff->prereadIndex == pbuff->writeIndex)
			{
				return;
			}
			pbuff->prereadIndex++;
			i++;
			if (pbuff->prereadIndex == MDL_RECE_MAX_LEN)
			{
				pbuff->prereadIndex = 0;
			}
			switch (pbuff->buff[pbuff->prereadIndex])
			{
				case 'V'://0x56
					if (PACKBUFFREMAINP(pbuff) < 5)
					{
						return;
					}
					else
					{
						char tmp[5];
						int checksum = 0;
						for (j = 0; j < 5; j++)
						{
							pbuff->prereadIndex++;
							i++;
							if (pbuff->prereadIndex == MDL_RECE_MAX_LEN)
							{
								pbuff->prereadIndex = 0;
							}
							tmp[j] = pbuff->buff[pbuff->prereadIndex];
						}
						checksum = tmp[0] + tmp[1] + tmp[2];
						if (0xBB == tmp[4] && LOBYTE(checksum) == tmp[3])
						{
							SetPt1561pVersion(tmp);
						}
					}
					break;

				case 0x01:
				case 0x02:
				case 0x03:
					if (PACKBUFFREMAINP(pbuff) < 3)
					{
						return;
					}
					else
					{
						char tmp[4];
						int checksum = 0;
						tmp[0] = pbuff->buff[pbuff->prereadIndex];
						for (j = 0; j < 3; j++)
						{
							pbuff->prereadIndex++;
							i++;
							if (pbuff->prereadIndex == MDL_RECE_MAX_LEN)
							{
								pbuff->prereadIndex = 0;
							}
							tmp[j + 1] = pbuff->buff[pbuff->prereadIndex];
						}
						checksum = tmp[0] + tmp[1];
						if (0xBB == tmp[3] && LOBYTE(checksum) == tmp[2])
						{
							Pt1561pAlarmPacket(tmp);
						}
					}
					break;

				default:
					break;
			}
			pbuff->readIndex = pbuff->prereadIndex;
		}
		else
		{
			pbuff->prereadIndex++;
			if (pbuff->prereadIndex == MDL_RECE_MAX_LEN)
			{
				pbuff->prereadIndex = 0;
			}
			if (pbuff->prereadIndex == pbuff->writeIndex)
			{
				return;
			}
		}
	}
}

static void PrinterUnPack_112(INT32 read)
{
	INT32 i;
	INT32 j;
	UCHAR		*pread	= UartReadBuffer;
	PACKBUFF	*pbuff	= &sPrinterBuff;
	PACKETFRAME	*pPack	= &sPrinterPack;
	for (i = 0; i < read; i++)
	{
		pbuff->prereadIndex = pbuff->readIndex;
		if (PRINT_RTN_BUSY == *pread)
		{
			RecConfig.recstatus |= (PRINT_RTN_BUSY << 8);
			pbuff->readIndex++;
			if (pbuff->readIndex == MDL_RECE_MAX_LEN)
			{
				pbuff->readIndex = 0;
			}
		}
		else if (PRINT_RTN_NOBUSY == *pread)
		{
			//RecConfig.recstatus &= (PRINT_RTN_NOBUSY << 8);
			RecConfig.recstatus &= 0xFF;
			pbuff->readIndex++;
			if (pbuff->readIndex == MDL_RECE_MAX_LEN)
			{
				pbuff->readIndex = 0;
			}
		}
		else if (PRINT_RTN_HOT == *pread)
		{
			RecConfig.recstatus = PRINT_RTN_HOT;
			pbuff->readIndex = pbuff->writeIndex - 1;
			if (pbuff->readIndex < 0)
			{
				pbuff->readIndex = 0;
			}
		}
		else if (PRINT_RTN_OPEN == *pread)
		{
			RecConfig.recstatus = PRINT_RTN_OPEN;
			pbuff->readIndex = pbuff->writeIndex - 1;
			if (pbuff->readIndex < 0)
			{
				pbuff->readIndex = 0;
			}
		}
		else if (PRINT_RTN_PAPER == *pread)
		{
			RecConfig.recstatus = PRINT_RTN_PAPER;
			pbuff->readIndex = pbuff->writeIndex - 1;
			if (pbuff->readIndex < 0)
			{
				pbuff->readIndex = 0;
			}
		}
		else if (!Unpacker(pbuff, pPack))
		{
			for (j = 0; j < pPack->frame.len + 6; j++)
			{
				if (pbuff->prereadIndex == pbuff->writeIndex)
				{
					return;
				}
				pbuff->prereadIndex++;
				i++;
				if (pbuff->prereadIndex == MDL_RECE_MAX_LEN)
				{
					pbuff->prereadIndex = 0;
				}
			}
			if (PrinterPacketFound(pPack))
			{
				pbuff->readIndex = (j + pbuff->readIndex) % MDL_RECE_MAX_LEN;
			}
		}
		else
		{
			pbuff->readIndex++;
			if (pbuff->readIndex == MDL_RECE_MAX_LEN)
			{
				pbuff->readIndex = 0;
			}
		}
		pread++;
	}
}


VOID PrinterUnPackProc(INT8 type)
{
#if _ENB_REC_FUNC
	static short cnt = 0;
	INT32 read;
	UCHAR		*pread	= UartReadBuffer;
	PACKBUFF	*pbuff	= &sPrinterBuff;
	MdlUartRece(UART_PORT_PRINTER, pread, MDL_RECE_MAX_LEN, &read);
	int i;
	if (read == 0)
	{
		if (RecConfig.recstatus)
			cnt++;
		else
			cnt = 0;
		if (cnt > 400)
		{
			RecConfig.recstatus = 0;
			cnt = 0;
		}
		return;
	}
#if 0
	printf("PrinterUnPackProc::read %d:", read);
	for (i = 0; i < read; i++)
		printf("0x%02X,", UartReadBuffer[i]);
	printf("\n");
#endif
	cnt = 0;
//	prinfo("pread...0x%X\r\n", *pread);
	CopyToPackBuff(pbuff, UartReadBuffer, read);
	switch (type)
	{
		case PAPER_TYPE_112MM:
			PrinterUnPack_112(read);
			break;

		case PAPER_TYPE_PT1561P:
			PrinterUnPack_PT1561P(read);
			break;

		default:
			break;
	}
#endif
}


VOID LCSendPrinterUnPackProc(INT8 type, int read, UCHAR *buff)
{
#if _ENB_REC_FUNC
	static short cnt = 0;
#if 0
	printf("%s::read %d\n", __FUNCTION__, read);
	int i;
	for (i = 0; i < read; i++)
		printf("0x%02X, ", *(buff+i));
	printf("\n\n");
#endif
	UCHAR		*pread	= UartReadBuffer;
	PACKBUFF	*pbuff	= &sPrinterBuff;
	if (read == 0 || !buff)
	{
		if (RecConfig.recstatus)
			cnt++;
		else
			cnt = 0;
		if (cnt > 400)
		{
			RecConfig.recstatus = 0;
			cnt = 0;
		}
		return;
	}
	cnt = 0;
	CopyToPackBuff(pbuff, buff, read);
	switch (type)
	{
		case PAPER_TYPE_112MM:
			memcpy(pread, buff, read);
			PrinterUnPack_112(read);
			break;

		case PAPER_TYPE_PT1561P:
			PrinterUnPack_PT1561P(read);
			break;

		default:
			break;
	}
#endif
}


BOOL IsPrinterBusy(VOID)
{
	if (PRINT_RTN_BUSY == (HIBYTE(RecConfig.recstatus)))
	{
		return TRUE;
	}
	return FALSE;
}


