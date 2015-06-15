#define  FHRCOMM_GLOBALS
#include "includes.h"
#include "fhrcomm.h"
#include "netcenter.h"

static PACKETFRAME sFetalSendPack;

static FILE *SaveUsbfp = NULL;

VOID FetalSetMoudle(BOOL zero,BOOL isNeedTocoAmend);

extern INT32 GetUsbBlockStat(CHAR unit);

static VOID OpenSaveUsbFile(VOID)
{
//    if (GetUsbBlockStat('M') > 80)
/**
	int fd;
	char usbStatus;
#include <fcntl.h>
	if (0 <= (fd = open("/tmp/usb", O_RDONLY)))
	{
		read(fd, &usbStatus, 1);
		close(fd);
		if (usbStatus == '1')
		{
			SaveUsbfp = fopen("/mnt/disk/FetalSound.dat", "wb+");
			return;
		}
	}
    prinfo("GetUsbBlockStat('M') is %d\r\n", GetUsbBlockStat('M'));
**/
	if (NULL == SaveUsbfp)
	{
//		printf("GetUsbStorage is %c\n", GetUsbStorage());
		if ('1' == GetUsbStorage())
		{
			SaveUsbfp = fopen("/mnt/disk/FetalSound.dat", "wb+");
//			prinfo("create file ptr %p\n", SaveUsbfp);
		}
		else
		{
			prinfo("U-disk not found!\n");
		}
	}
}

BOOL InitFhrModule (VOID)
{
    UART_CONFIG config;

    config.baudRate = MapUartBPS(115200);
    config.parity   = PARITY_NO;
    config.dataBits = DBTS_8;
    config.stopBits = STOPBITS_1;
    if (UartOpen(UART_PORT_FETAL) < 0) 
    {
        printf( "Fetus Uart Init error !\r\n" );
        return FALSE;
    }
    UartSetup(UART_PORT_FETAL, &config);
    FetalSetMoudle(TRUE,FALSE);
	OpenSaveUsbFile();
    return TRUE;
}

static BOOL CalcAutoFmFalgProc(VOID)
{

#define CALC_SAMPLE_SIZE 50

    static UCHAR Fhr1Buf[CALC_SAMPLE_SIZE] = { 0 };
    static UCHAR Fhr2Buf[CALC_SAMPLE_SIZE] = { 0 };
    static CHAR  TocoBuf[16] = { -1 };
    static UCHAR  ndx1 = 0;
    static UCHAR  ndx2 = 0;
    static INT8  valid_flag = 3;
    BOOL ret = FALSE;
    UCHAR i;
    UCHAR fhr;
    fhr = (FhrConfig.source == 0) ? FhrParams.fhr1 : FhrParams.fhr2;
    if (fhr < 60 || fhr > 210)
    {
        valid_flag--;
    }
    else
    {
        valid_flag = 2;
    }

    if (valid_flag < 1)
    {
        FhrParams.afm = 0;
        if (valid_flag < 0)
        {
            valid_flag = -1;
            return ret;
        }
        ZeroMemory(Fhr1Buf, sizeof(Fhr1Buf));
        ZeroMemory(Fhr2Buf, sizeof(Fhr2Buf));
        ZeroMemory(TocoBuf, sizeof(TocoBuf));
        ndx1 = 0;
        ndx2 = 0;
        return ret;
    }
    Fhr1Buf[ndx1] = FhrParams.fhr1;
    Fhr2Buf[ndx1] = FhrParams.fhr2;
    TocoBuf[ndx2] = FhrParams.toco;

    if (++ndx1 >= CALC_SAMPLE_SIZE)
        ndx1 = 0;
    if (++ndx2 >= sizeof(TocoBuf))
        ndx2 = 0;
    if(0 == FhrConfig.type) 
    { 
        UINT16 summ=0;
        UCHAR  base;
        UCHAR  *p;
        if (FhrConfig.source == 1) // ͨ��2ʱʹ��
        {
            base = Fhr2Buf[(ndx1 + 1)%CALC_SAMPLE_SIZE];
            p = Fhr1Buf;
        }
        else
        {
            base = Fhr1Buf[(ndx1 + 1)%CALC_SAMPLE_SIZE];
            p = Fhr1Buf;
        }
        for(i = 0; i < CALC_SAMPLE_SIZE; i++)
        {
            if((base > 100) && (p[i] > base) && (p[i] < base + 20 + i)
				&& ABS(p[i] - p[(ndx1 + 1)%CALC_SAMPLE_SIZE]) < 8)
            {
                summ += p[i] - base;
            }
        }
        if(summ > 740 )
        {
            ret = TRUE;
        }
        FhrParams.afm = (INT8)((summ >> 6) % 40);
        if (ret == FALSE)
        {
            base = ((ndx2 + 1) & 0x0F);
            if ((TocoBuf[base] > 20)
                && (TocoBuf[(base + 3) & 0x0F] - TocoBuf[base] > 12))
            {
                for (i = 3; i < 14; i++)
                {
                    if (TocoBuf[(base + i) & 0x0F]
                        - TocoBuf[(base + i + 2) & 0x0F] > 20 - i)
                    {
                        ret = TRUE;
                    }
                }
            }
        }
    }//�Զ�̥������
    return ret;
}


/*****************************************************************************************
* Function    : DealWithGetFmFlag
* Description : ��������ʾģʽ�л�����5����Բ�Ӧ�ڣ��ڴ��ڼ䲻�����κ�̥������
* Input Para  : 
* Output Para : 
* Return Value: 
*****************************************************************************************/
static VOID DealWithGetFmFlag(UINT8 flag)
{
    static UINT8 manualCnt = 5;
    static UINT8 autoCnt = 10;
    
    BOOL afm;
    BOOL fm;
    
    if (MonitorInfo.inDemo)
    {
        manualCnt = 5;
        autoCnt = 10;
        return;
    }
    
    fm  = (flag & 0x40) > 0;
    if (manualCnt > 0)
        manualCnt --;

    if (0 == manualCnt)
    {
        if (fm)
        {
            manualCnt = FM_INTERVAL_LIMIT;
            if (FhrConfig.type == 1)
            {
                FhrParams.fm++;
            }
            else
            {
                if (0 == autoCnt)
                {
                    FhrParams.fm++;
                }
            }
            if (FhrParams.fm > 99)
            {
                FhrParams.fm = 99;
            }
            FhrParams.mark |= 0x01; // fm
        }
    }
    else
    {
        if ((fm) && (FM_INTERVAL_LIMIT - 3 < manualCnt))
            manualCnt = FM_INTERVAL_LIMIT;
    }
    
    if (FhrConfig.type == 1) //�ֶ�ģʽ,������Զ�̥��
    {
        return;
    }
    
    if (autoCnt > 0)
        autoCnt --;

    afm = CalcAutoFmFalgProc();//(flag & 0x20) > 0;
    static INT afmTimes = 0;//̥������
    static INT effectAfmTimes = 0;//��Ч̥������
    if(afm)
    	afmTimes++;
    if (0 == autoCnt)
    {
        if (afm)
        {
            autoCnt = FM_INTERVAL_LIMIT;
            if (manualCnt == 0)
            {
            	effectAfmTimes++;
                FhrParams.fm++;
                if (FhrParams.fm > 99)
                {
                    FhrParams.fm = 99;
                }
            }
            FhrParams.mark |= 0x08; // afm
        }
    }
    else
    {
        if ((afm) && (FM_INTERVAL_LIMIT - 3 < autoCnt))
            autoCnt = FM_INTERVAL_LIMIT;
    }
    printf("��⵽̥������%d ʵ����Ч����%d\n",afmTimes,effectAfmTimes);
}

static VOID FhrControlCommand (UINT32 param)
{    
#if _ENB_REC_FUNC
  	PostMessage(SysRec_HTSK, MSG_PRTCL_FETAL, 0, param);
#endif
}

static INT8 GetTocoZeroValue(INT8 zero)
{
    return (zero * 5);
}

VOID FetalSetMoudle(BOOL zero,BOOL isNeedTocoAmend)
{
	
    sFetalSendPack.frame.len = 3;
    sFetalSendPack.frame.data[1] = 0x80;
    sFetalSendPack.frame.data[1] |= ((FhrConfig.source << 4) & 0x10);
    sFetalSendPack.frame.data[1] |= (FhrConfig.volume & 0x0F);
    sFetalSendPack.frame.data[2] = 0x80;
    if (zero)
    {
        sFetalSendPack.frame.data[2] |= 0x40;
    }
	else
	{
        sFetalSendPack.frame.data[2] &= ~0x40;
	}
	sFetalSendPack.frame.data[3] = isNeedTocoAmend;
	sFetalSendPack.frame.data[4] = 0x05;//��ֵ��ʱ����� ֻ�û���������
    sFetalSendPack.frame.data[2] |= (GetTocoZeroValue(FhrConfig.zero) & 0x1F);
    BuildPacket(MDL_PID_IDM_FETAL,MDL_PID_IDP_FETALCMD, sFetalSendPack.buffer);
    FhrControlCommand((UINT32)&sFetalSendPack);
}

VOID FetalSendSound(char sound)
{
	sFetalSendPack.frame.data[1] &= 0x9F;
    sFetalSendPack.frame.data[1] |= ((sound & 0x03) << 5);
	if (sFetalSendPack.frame.data[2] & 0x40)
		sFetalSendPack.frame.data[2] &= ~0x40;
    BuildPacket(MDL_PID_IDM_FETAL,MDL_PID_IDP_FETALCMD, sFetalSendPack.buffer);
    FhrControlCommand((UINT32)&sFetalSendPack);
}

VOID FetalSendPack(PACKETFRAME *pack)
{
    INT32 send, len;
    len = BuildPacket2(pack);
    MdlUartTran(UART_PORT_FETAL, pack, len, &send);
    if (len != send)
    {
        printf("FetalSendPack::injure packet!!\r\n");
    }
    #if 0
    {
        int i;
		prinfo("packet stx	  :0x%02X\r\n", pack->frame.stx);
		prinfo("packet sync	 :0x%02X\r\n", pack->frame.sync);
		prinfo("packet id	   :0x%02X\r\n", pack->frame.id);
		prinfo("packet len	  :0x%02X\r\n", pack->frame.len);
        for (i = 0; i < pack->frame.len; i++)
            prinfo("packet data[%d] :0x%02X\r\n", i, pack->frame.data[i]);
        prinfo("packet chksum   :0x%02X\r\n", pack->frame.data[i++]);
        prinfo("packet end      :0x%02X\r\n", pack->frame.data[i++]);
         prinfo("packet amend   :0x%02X\r\n", pack->frame.data[i++]);
        prinfo("packet tocoend      :0x%02X\r\n", pack->frame.data[i++]);
    }
    #endif
}


#if _ENB_NET_THREAD
	#if _ENB_NET_SEND_ALARM_INFO
static FETALINFO sFetalInfo = { 0 };
static pthread_mutex_t sNetErrorCodeLocker = PTHREAD_MUTEX_INITIALIZER;
net_FETAL_ERR sNetErrCode[2] = { 0 };

VOID SetNetErrorCode(net_FETAL_ERR err1, net_FETAL_ERR err2)
{
	pthread_mutex_lock(&sNetErrorCodeLocker);
	sNetErrCode[0] = err1;
	sNetErrCode[1] = err2;
	pthread_mutex_unlock(&sNetErrorCodeLocker);
}

VOID GetNetErrorCode(VOID)
{
	static char flag = FALSE;
	pthread_mutex_lock(&sNetErrorCodeLocker);
	if (net_FETAL_NO_ALM != sNetErrCode[!flag])
	{
		flag = !flag;
	}
	sFetalInfo.error_code = sNetErrCode[flag];
	pthread_mutex_unlock(&sNetErrorCodeLocker);
}
	#endif
#endif

VOID FetalPacketFound(PACKETFRAME *pack)
{
    if (pack->frame.id == FETAL_MODULE_ID)
    {
        UCHAR status1 = 0;
        UCHAR status2 = 0;
        FhrParams.fhr1 = pack->frame.data[1];
        FhrParams.fhr2 = pack->frame.data[2];
        FhrParams.toco = pack->frame.data[3];
        FhrParams.mark = 0;
        status1  = pack->frame.data[4];
        status2  = pack->frame.data[5];
        
        FhrParams.signal = status1;
        DealWithGetFmFlag(status1);
        FetalAnalysisPutValue(&FhrParams);
        //PutFhrValue�ᵼ��FetalWaveBuffWritePtrָ�����ƶ�ʧҽ������¼� ���Ｐʱ����
		UCHAR dotorEvent = FetalWaveBuffWritePtr->event;
		dotorEvent = (dotorEvent > 15 || dotorEvent < 0)?0:dotorEvent;
        PutFhrValue(&FhrParams);// ����հ�Ƶ����4Hz,ģ��ʵ�ʷ���Ƶ����2Hz
        if (status2 & 0x40)
        {
            FhrParams.mark |= 0x02;
            
        }
		PutFhrValue(&FhrParams);// ����һ�����ݱ���
		if (MonitorInfo.inDemo == FALSE)
	        PutFhrStatusByte(status1, status2);
	#if _ENB_NET_THREAD
		#if _ENB_NET_SEND_ALARM_INFO
		//���ݺϷ��Ե�У��
		sFetalInfo.fhr1 = (FhrParams.fhr1<30)?0:FhrParams.fhr1;
		sFetalInfo.fhr2 = (FhrParams.fhr2<30)?0:FhrParams.fhr2;
		sFetalInfo.toco = (FhrParams.toco<0)?0:FhrParams.toco;//��ѹ��

		sFetalInfo.afm = (FhrParams.afm<0)?0:FhrParams.afm;//e̥������
		sFetalInfo.fm = (FhrParams.fm<0)?0:FhrParams.fm;//̥������
		printf("time=%d ̥������%d ����=%d\n",get_curr_time(),FhrParams.fm,FhrParams.afm);
		sFetalInfo.fm_mode = FhrConfig.mode;
		sFetalInfo.fm_count_mode = FhrConfig.type;//ϵͳ���ñ����̥������ģʽ��FhrConfig.type������FhrConfig.movement_calc;
		sFetalInfo.fhr_high = FhrConfig.FhrAlarmLimitHi;// FhrAlarmLimitHi;
		sFetalInfo.fhr_low = FhrConfig.FhrAlarmLimitLo;
		sFetalInfo.signal = FhrParams.signal;
		UCHAR zerobits = (FhrParams.mark == 0x02)?16:0;//��ѹ����
		sFetalInfo.event = dotorEvent?dotorEvent:zerobits;//1-15����ҽ���¼� 16����ѹ����
//		printf("sFetalInfo.fm =%d\n",sFetalInfo.fm);
		GetNetErrorCode();
		PostMessage(SysUdpT_HTSK, MSG_NET_UDP_SEND, sizeof(sFetalInfo),(LPARAM)&sFetalInfo);
		PostMessage(SysTcpT_HTSK, MSG_NET_TCP_SEND, sizeof(sFetalInfo),(LPARAM)&sFetalInfo);
		#endif
	#endif
        return;
    }
    else
    {
        // ����̥��̥�������ݰ�
        if (SaveUsbfp)
        {
            fwrite(pack, pack->frame.len, 1, SaveUsbfp);
            flush(SaveUsbfp);
        }
		else
		{
			OpenSaveUsbFile();
		}
    }
    printf("FetalPacketFound::error packet!\r\n");
    return;
}

