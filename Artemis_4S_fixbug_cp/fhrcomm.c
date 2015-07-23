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
//�Ƿ�һֱ�յ�̥����
static BOOL is_alway_get_fhr()
{	
	enum 
	{
		MAX_LOST_FHR_COUNT = 100,//������Ҳ������
	};
 	UCHAR fhr = (FhrConfig.source == 0) ? FhrParams.fhr1 : FhrParams.fhr2;
 	static UCHAR lostFhrCount = MAX_LOST_FHR_COUNT;//��ʱ��û���ʲ����̥�� 
 	if (fhr < 60 || fhr > 240) 
    {
        lostFhrCount = (lostFhrCount < MAX_LOST_FHR_COUNT)?(lostFhrCount+1):MAX_LOST_FHR_COUNT;
    }
    else
    {
       lostFhrCount = 0;
    }
    
    if (lostFhrCount >= MAX_LOST_FHR_COUNT)
    	return FALSE;
    else
    	return TRUE;
}
//ͨ��̥���ʱ仯���߼����Զ�̥��
static BOOL calc_autoFM_by_fhr()
{	
	enum 
	{
		CALC_SAMPLE_SIZE = 110,//̥�ļ��ٻ����
	};
    static UCHAR FhrBuf[CALC_SAMPLE_SIZE] = { 0 };
    static UCHAR  ndx1 = 0;
    static UCHAR  lastFhrConfigSource = 0;
    if(lastFhrConfigSource != FhrConfig.source)//�л���̥����
    {
    	lastFhrConfigSource = FhrConfig.source;
    	ZeroMemory(FhrBuf, sizeof(FhrBuf));
        ndx1 = 0;
    }
    UCHAR fhr = (FhrConfig.source == 0) ? FhrParams.fhr1 : FhrParams.fhr2;
    FhrBuf[ndx1++] = fhr;
    if (ndx1 >= CALC_SAMPLE_SIZE)
        ndx1 = 0;
 	BOOL ret = FALSE;
    UCHAR i;
    UINT16 summ=0;
    UCHAR  base = fhr;
    UCHAR  *p = FhrBuf;
    enum 
	{
	    ZERO = 2,//���ڼ������4-->2
   		MINHEIGHT = 15,//̥���߶�11-->15
   		MINWIDTH = 25,//��С���¿��
   		INTERPOLATION_WIDTH = 25,
	}; 
   	UCHAR width = 0;
    UCHAR maxHeight = 0;
    BOOL  isStart = FALSE;
    UCHAR L1 = (ndx1 - 2 + CALC_SAMPLE_SIZE) % CALC_SAMPLE_SIZE;
    UCHAR L2 = (ndx1 - 3 + CALC_SAMPLE_SIZE) % CALC_SAMPLE_SIZE;
    UCHAR L3 = (ndx1 - 4 + CALC_SAMPLE_SIZE) % CALC_SAMPLE_SIZE;
    if(fhr && p[L1] > fhr && p[L2] > fhr && p[L3] > fhr)//�ҵ�һ������ ps:����������С
	{		
        INT j;
        UCHAR zeroCount = 0;	
        UCHAR lastValue = 0;
        for(i = 1; i < CALC_SAMPLE_SIZE; i++)
        {	
        	j = (ndx1 - i + CALC_SAMPLE_SIZE) % CALC_SAMPLE_SIZE;
            if((base > 60) && (p[j] >= base) && (p[j] < base + 20 + i))
            {
                summ += p[j] - base;
                ++width;
            }
            if(maxHeight <=  p[j])
            {
            	maxHeight =  p[j];
            }
            if(ABS(p[j] - base) <= ZERO && i > MINWIDTH)
            {
            	isStart = TRUE;//�ҵ���ʼ���ٵ����
            	break;
            }
            	
            if(p[j] == 0)
            	++zeroCount;
            else
            {	
            	if(zeroCount != 0 && INTERPOLATION_WIDTH > zeroCount)
            	{	
            		if((zeroCount*(lastValue+p[j]-base-base)/2) > 0)
            		{//��ֵ����	
            			summ += (zeroCount*(lastValue+p[j]-base-base)/2);
                    	width += zeroCount;
                    }
            	}
            	zeroCount = 0;
            	lastValue = p[j];
            }
        }
    }
    UCHAR addSum = 18 * width / 20;//���ֲ���20->18*width/20
    //����� ���ִ� ��ȹ� �߶ȹ�summ->summ+
    if(isStart && summ + addSum > (maxHeight-base)*width/2 && 
    	width > MINWIDTH && (maxHeight-base) > MINHEIGHT && 
    		(maxHeight-base)>width/5)//6 -3 -->5
    {	
    	ZeroMemory(FhrBuf, sizeof(FhrBuf));
    	ndx1 = 0;
        ret = TRUE;
    }
    
   	if(ret)
   		FhrParams.afm = (INT8)((summ >> 5) % 40);
   	else
   		FhrParams.afm = isStart? (INT8)((summ >> 7) % 40):0;
    return ret;
}
//ͨ����ѹ�߼����Զ�̥��
static BOOL calc_autoFM_by_toco()
{	enum 
	{
		TOCO_SAMPLE_SIZE = 16,//��ѹ���ٻ����
	};
    static CHAR  TocoBuf[TOCO_SAMPLE_SIZE] = { -1 };
    static UCHAR  ndx2 = 0;
    TocoBuf[ndx2++] = FhrParams.toco;
    if (ndx2 >= TOCO_SAMPLE_SIZE)
        ndx2 = 0;
	BOOL ret = FALSE; 
   
	//�ҵ�һ�������£�����ǰ�Ҽ����� ��ͨ�˲�   
    UCHAR minChange,MAXHEIGHT,i;
    minChange = 6;
    MAXHEIGHT = 85;
  	UCHAR base = (ndx2-1 >= 0)?ndx2-1:(TOCO_SAMPLE_SIZE-1);
	BOOL isDown,down3,down2,down1;
	down3 = (TocoBuf[(base - 3 + TOCO_SAMPLE_SIZE) & 0x0F] - TocoBuf[base] > minChange);
	down2 = (TocoBuf[(base - 2 + TOCO_SAMPLE_SIZE) & 0x0F] - TocoBuf[base] > minChange);
	down1 = (TocoBuf[(base - 1 + TOCO_SAMPLE_SIZE) & 0x0F] - TocoBuf[base] > minChange);
   	isDown = down1 || down2 || down3;
   					 
    if (isDown)
    {   
     	 BOOL up3,up2,up1;
     	 UCHAR maxHeightPoint = TocoBuf[(base  - 3 + TOCO_SAMPLE_SIZE) & 0x0F];
     	 UCHAR index = 2;
     	 for (i = 2; i <= 8; i++)//һ��̥����Ϊ��Ҫ��ȳ���8,���µ���֮ǰ����֮ǰ����2����           
     	 {                   	
         	 UCHAR right = (base - i + TOCO_SAMPLE_SIZE) & 0x0F;                	
         	 UCHAR left = (base - i - 3 + TOCO_SAMPLE_SIZE) & 0x0F;  
         	 UCHAR left2 = (base - i - 2 + TOCO_SAMPLE_SIZE) & 0x0F; 
         	 UCHAR left1 = (base - i - 1 + TOCO_SAMPLE_SIZE) & 0x0F; 
         	 up3 =  (TocoBuf[right] - TocoBuf[left] > minChange);
         	 up2 =  (TocoBuf[right] - TocoBuf[left2] > minChange);
         	 up1 =  (TocoBuf[right] - TocoBuf[left1] > minChange);
         	 if (maxHeightPoint < TocoBuf[right])
     	 	 {	
     	 	 	maxHeightPoint = TocoBuf[right];
     	 	 	index = i;
     	 	 }
     	 	 if (up3 || up2 || up1)//�ҵõ��������
         	 {    
         	 	ret = TRUE; 
         	 	if (maxHeightPoint > MAXHEIGHT)//���˵�����  
           		{	UCHAR toco1 = TocoBuf[(base - index - 1 + TOCO_SAMPLE_SIZE) & 0x0F];
             	 	UCHAR toco2 = TocoBuf[(base - index - 2 + TOCO_SAMPLE_SIZE) & 0x0F];
             	 	UCHAR toco3 = TocoBuf[(base - index - 3 + TOCO_SAMPLE_SIZE) & 0x0F];
             	 	UCHAR toco4 = TocoBuf[(base - index - 4 + TOCO_SAMPLE_SIZE) & 0x0F];
             	 	UCHAR toco5 = TocoBuf[(base - index - 5 + TOCO_SAMPLE_SIZE) & 0x0F];
					if (toco1>MAXHEIGHT && toco2 >MAXHEIGHT && toco3 >MAXHEIGHT && toco4 >MAXHEIGHT && toco5 >MAXHEIGHT)
						ret = FALSE;
				}
				if(ret)
					break;
         	 }
         }
     }       
  	return ret;
}
static BOOL CalcAutoFmFalgProc(VOID)
{	
	FhrParams.afm = 0;//̥������߳�ʼֵ
    BOOL isAutoFm = FALSE;
    BOOL isNoLostFhr = is_alway_get_fhr();
    if (isNoLostFhr)//����ʱ���ղ���̥�ģ������ټ��̥��
    {	
    	isAutoFm = calc_autoFM_by_fhr();
	    if (!isAutoFm)//̥���޼���ʱ�Ŵӹ�ѹ����̥��
	    	isAutoFm = calc_autoFM_by_toco();
    }
    return isAutoFm;
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
    
    if (FhrConfig.type == 1) //�ֶ�ģʽ,������Զ�̥��
    {
        return;
    }
    
    if (autoCnt > 0)
        autoCnt --;

    afm = CalcAutoFmFalgProc();//(flag & 0x20) > 0;
    if (0 == autoCnt)
    {
        if (afm)
        {
            autoCnt = FM_INTERVAL_LIMIT;
            if (manualCnt == 0)
            {
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
	//sFetalSendPack.frame.data[3] = isNeedTocoAmend;
	//sFetalSendPack.frame.data[4] = 0x05;//��ֵ��ʱ����� ֻ�û���������
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
        if (FhrConfig.mode == 0)//ֻ���ͨ��fhr1
        	FhrParams.fhr2 = 0;
        else if (FhrConfig.mode == 1)//ֻ���ͨ��fhr2
        	FhrParams.fhr1 = 0;
        
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
		sFetalInfo.fm_mode = FhrConfig.mode;
		sFetalInfo.fm_count_mode = FhrConfig.type;//ϵͳ���ñ����̥������ģʽ��FhrConfig.type������FhrConfig.movement_calc;
		sFetalInfo.fhr_high = FhrConfig.FhrAlarmLimitHi;// FhrAlarmLimitHi;
		sFetalInfo.fhr_low = FhrConfig.FhrAlarmLimitLo;
		sFetalInfo.signal = FhrParams.signal;
		UCHAR zerobits = (FhrParams.mark == 0x02)?16:0;//��ѹ����
		sFetalInfo.event = dotorEvent?dotorEvent:zerobits;//1-15����ҽ���¼� 16����ѹ����
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

