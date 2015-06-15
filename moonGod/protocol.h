#ifndef _PROTOCOL_H
#define _PROTOCOL_H

typedef enum __module_packet_enum_id
{
	MDL_PID_IDM_SYSKB	   = 0x0A,
	MDL_PID_IDP_KEYDATA	 = 0x78,
	MDL_PID_IDM_KEYSTAT	 = 0x0A,
	MDL_PID_IDM_KEYACK	  = 0x04,
	MDL_PID_IDM_KEYSYSINFO  = 0x77,

	MDL_PID_IDM_FETAL	   = 0x83,
	MDL_PID_IDP_FETAL	   = 0x00,
	MDL_PID_IDP_FETALCMD	= 0x01,

	MDL_PID_IDM_PRINTER	 = 0x79,
	MDL_PID_IDP_PRINTCMD	= 0x99,
	MDL_PID_IDP_PRINTDAT	= 0x31,
	MDL_PID_IDP_PRINTSTS	= 0x00,
	
}MDL_PACK_ID;

typedef enum _module_cmd_message
{
	MSG_PRTCL_FIRST = 0x80,
	MSG_PRTCL_SYSKB = MSG_PRTCL_FIRST,
	MSG_PRTCL_FETAL,
	MSG_PRTCL_PRINTER,
	MSG_PRTCL_ANALY,
	MSG_PRTCL_MAX
}MSG_PRTCL_ID;

#define ALLCOMM_LEN_MIN	 6			   //单个包的最小允许长度
#define ALLCOMM_LEN_MAX	 (4 + 256 + 4)   //单个包的最长允许长度(Len:0~0xFF)
#define MDL_RECE_MAX_LEN	4096			//ALLCOMM_LEN_MAX

typedef union {  
	struct {
		UINT8 stx;
		UINT8 sync;
		UINT8 id;
		UINT8 len;
		UINT8 data[256];
		UINT8 chksum;
		UINT8 end;
		UINT8 isNeedTocoAmend;//是否需要修正宫压放大倍数
		UINT8 tocoEnd;///宫压放大倍数结尾标志
	} __attribute__ ((packed, aligned(1))) frame;
	UINT8 buffer[ALLCOMM_LEN_MAX];
}   __attribute__ ((packed, aligned(1))) PACKETFRAME;

typedef union {  
	struct {
		UINT8 stx;
		UINT8 sync;
		UINT8 id;
		UINT8 data[17];
	} __attribute__ ((packed, aligned(1))) frame;
	UINT8 buffer[20];
}   __attribute__ ((packed, aligned(1))) PACKETFRAME2;


typedef	struct _tag_packet_buffer
{
	int	 readIndex;
	int	 prereadIndex;
	int  writeIndex;
	UCHAR buff[MDL_RECE_MAX_LEN];
}PACKBUFF;


#ifndef PROTOCOL_GLOBALS
#define PROTOCOL_EXT extern
#else
#define PROTOCOL_EXT
#endif

// 串口函数定义
typedef struct _uart_config MDL_UARTCFG;
typedef struct _uart_config *PMDLUARTCFG;
#define MdlUartOpen(port)				   UartOpen(port)
#define MdlUartSetup(port, pCfg)			UartSetup(port, pCfg)
#define MdlUartRece(port, buff, len, ret)   UartRead(port, (UCHAR*)buff, len, ret, 0)
#define MdlUartTran(port, buff, len, ret)   UartWrite(port, (UCHAR*)buff, len, ret, 0)
#define PACKBUFFREMAINP(p)	((MDL_RECE_MAX_LEN + p->writeIndex - p->prereadIndex) % MDL_RECE_MAX_LEN)

PROTOCOL_EXT const UCHAR cUCAllCommPackSTX;	 //协议指定的帧的起始字节
PROTOCOL_EXT const UCHAR cUCAllCommPackSync;	//协议指定的帧的同步字节
PROTOCOL_EXT const UCHAR cUCAllCommPackEnd;	 //协议指定的帧结束字节

PROTOCOL_EXT UCHAR GetChkSum(UCHAR *packet);
//PROTOCOL_EXT VOID PrtclTskProc(VOID *pdata);
PROTOCOL_EXT INT32 BuildPacket(UCHAR mdlID, UCHAR cmdID, UCHAR *buffer);
PROTOCOL_EXT INT32 BuildPacket2(PACKETFRAME *pack);
PROTOCOL_EXT INT32 AnalysisUnPackProc(PACKBUFF *pBuff, void *pFrame);
PROTOCOL_EXT VOID FetalMdlUnPackProc(VOID);
PROTOCOL_EXT VOID SysBoardUnPackProc(VOID);
PROTOCOL_EXT VOID PrinterUnPackProc(INT8 type);
PROTOCOL_EXT BOOL IsPrinterBusy(VOID);

#endif

