	#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

#define FHR_FIS_DIAG_RESULT_MAX_LEN 100

#define FHR_DIAGNOSE_SEND_FHR_NUM   2400	//20���Ӿ���������֮��Ĳ�������
#define FHR_DIAGNOSE_BUF_LEN		4804	//Ŀǰ�����ģ�������Ϊ4084�ֽ�����


typedef struct fischer_infoex{
	CHAR   major;			   // 0x02 ���� 0x04 ����
	CHAR   type;				// �仯����
	UINT16 point;			   // ����λ��(����������ݿ�ͷ)
}FISCINFOEX;
	//��ѹ�ļ���(��ֵ���յ�)
	typedef struct {
		INT startPosX;//��ѹ��ʼ����λ��
		INT endPosX;///���ٽ���λ��
		INT maxPosX;//��ֵλ��
		INT maxValue;//���ٷ�ֵ
		INT averageValue;//��ѹ���ߡ�
	}TOCOADDSPEED;
	typedef struct _fastFhr{
		INT maxPosX;
		INT start;
		INT end;
		INT addValue;
	}FASTFHR;
	typedef struct _slowFhr{
		INT maxPosX;
		INT start;
		INT downValue;//�½������ ��������С��50 �������70
		INT end;
	}SLOWFHR;

typedef struct _fhr_diagnose_ctrl
{
	DATETIME end;
	INT16   len;	// 600~1200, len < 600 || len > 1200 ���ṹ����������Ч
	INT16   nr_valid;

	UINT8   UsedFlag;
	//Fischer���ַ����浥���
	UINT8   accSum;				//���ٵĸ���
	UINT8   littleAccSum;		//С���ٵĸ���
	UINT8   fastigiaAccSum;		//�������ٵĸ���
	UINT8   slowReduceSum;		//�ٷ����ٵĸ���
	UINT8   heavyReduceSum;		//�ر仯���ٵĸ���
	UINT8   lightReduceSum;		//��仯���ٵĸ���
	UINT8   earlyReduceSum;		//���ڼ��ٵĸ���
	UINT8   extendReduceSum;	//�ӳ����ٵĸ���
	UINT8   baselineVal;		//20�����ڻ��ߵ�ֵ
	UINT8   swingVal;			//�������ֵ���Ŵ�10����
	UINT8   periodVal;			//���ڱ���ֵ���Ŵ�10����
	UINT8   baselinePoints;		//���ߵ÷�
	UINT8   swingPoints;		//�������÷�
	UINT8   periodPoints;		//���ڱ���÷�
	UINT8   accPoints;			//���ٵ÷�
	UINT8   reducePoints;		//���ٵ÷�
	UINT8   totalPoints;		//�ܷ�

	//���ٽ��
	//���ٱ�עλ��
	//���ٵ����� (1->����, 2->С����,  3->��������)
	//���ٽ��
	//���ٱ�עλ��
	//���ٵ�����  1->�ٷ�����, 2->΢С�ٷ�����,  3->�ٷ�����β���ӳ���4->�仯����+�ٷ�����
	//5->�ر仯���٣� 6->��仯���٣�7->���ڼ��٣� 8->�ӳ����٣� 9->���ڼ���+�仯����
	UINT8	   fisDiaPosSum;
	FISCINFOEX fiscInfo[FHR_FIS_DIAG_RESULT_MAX_LEN];

}__attribute__ ((packed, aligned(1)))FHRDIAGNOSECTRL;

typedef struct __tagAnalyConfig{
	UINT32 type		 :2;
	UINT32 autoFlag	 :1;
	UINT32 enbType	  :1;
	UINT32 enbAuto	  :1;
	UINT32 enbStart	 :1;
	UINT32 enbDone	  :1;
	UINT32 enbShow	  :1;
	UINT32 putFlag	  :1;	 // put data falg
	UINT32 sendFlag	 :1;	 // data send, waitting for result
	UINT32 waitCnt	  :5;	 // wait count 0~24
	UINT32 nr_valid	 :12;	// valid data number 0~2400
}ANALYCFG;

typedef struct __analysis_result_save{
	UINT32  len;
	UINT8   anls_type;  // 
	UINT8   data_pct;   // ��������
	UINT8   vld_pct;	// ��Ч����
	UINT8   fm_nr;	  // ̥������
	
	int fhr_JX;	  //���ʻ���
	int fhr_QV;	  //���ڱ���
	int fhr_ZV;	  //�������
	int fasttime;	//����ʱ����ʱ�� ��ƽ��ֵ��
	int fasthigh;	//����ʱ��������
	int tdfast;	  //���ʼ��ٴ���
	int tdslow;	  //���ʼ��ٴ���
	int fastType;		//��������
	int slowType;		//��������
	int LDTime;			//���ڼ���
	int EDTime;			//���ڼ���
	int VDTime;			//vd��
	UINT32  endtime;
	UINT32  second;
}ARET_SAVE;


#ifdef ANALYSIS_GLOBALS
#define ANALY_EXT
#else
#define ANALY_EXT   extern
#endif

ANALY_EXT   ANALYCFG		AnalyConfig;
ANALY_EXT   ARET_SAVE	   AnlsRet;

ANALY_EXT   VOID AnalysisPacketFound (PACKETFRAME2 *pPack);
ANALY_EXT   VOID AnalySendPack(UCHAR *pack);
ANALY_EXT   VOID AnalyInSecond(VOID);
ANALY_EXT   char get_analysis_enable(void);
#endif /*_ANALYSIS_H_*/

