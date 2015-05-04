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

#ifndef _ALARM_H

#define _ALARM_H


#define INVALIDALARMLEVEL	3	 // this may be defined in other module.

#define ALARMPREHIBITSECONDS 30	// ģ����غ��ж����벻�ж�������


// ���ڱ����л����漰��ϵͳ/����/��Դ.����Ϊ��������ר�Ŷ���
// ���¡�ģ����š�
#define ALM_MID_SYSTEM	   100
#define ALM_MID_NET		  101
#define ALM_MID_POWER		102

//��������
typedef enum {
	ALM_TYPE_PHY	= 1,
	ALM_TYPE_TECH,
	ALM_TYPE_NIBP
} ALM_TYPE;

#define	ALM_FLAG_CLR				0		 /* ������־���		*/
#define	ALM_FLAG_SET				0x0001	/* ������־����		*/
#define	ALM_FLAG_NEW				0x8001	/* �µı���			*/
#define	ALM_FLAG_CLR_LEADOFF_AUDIO  0x4000	/* ����������䱨����  */

// ALMPRESENT - ������ʾ�����ڵ���ʾ����
typedef struct {
	 INT16		AlmIndex;	   // �����������š� ���Ϊ0, ����ʾ�κα�����Ϣ��
								  // ��ͣ��ʾ��Ϣ����ʾҲ���������С���������ʹ�á�
	 CHAR		*AlmStr;		 // ��Ҫ���õĴ�����
	 INT8		 AlmTimePrsnt;   // ��������֮���Ƿ�Ӧ����ʾ����������ʱ�䡣
	 INT8		 BkGndColor;	 // �����ĵ�ɫ��0: ��; 1,2:��; 3: �������ĵ�ɫ��
								  // �����NIBP��������ʾ�����ɫʵ������ָ��ʾ�ִ�����ɫ�����ǵ�ɫ��
	 INT8		 AlmLev;		 // �ñ����ļ��𡣱�������Ϊ��Чʱ����ʾ�������
	 INT8		 Redraw;		 // �Ƿ�Ҫ�ػ��ñ�����ʾ���� TRUE-�ػ���FALSE - ���֡�
	 DATETIME	 Time;		   // ��Ҫ��ʾ��ʱ�䡣
}ALM_PRESENT;

#define BLINK_MASK_BLINK	0x01   // ��˸
#define BLINK_MASK_FLUSH	0x80   // ˢ��

// bit0-���������Ƿ���˸��Bit1-�����Ƿ���˸��Bit2 - �����Ƿ���˸��
// bit7-�Ƿ���Ҫˢ�£�1-��Ҫ��0-����Ҫ��
typedef struct {
	 UINT8 FHR1Blink;
	 UINT8 FHR2Blink;
	 UINT8 TOCOBlink;
	 UINT8 FMBlink;
}BLINK_FEATURE;


// ALMPRESENTINFO - ϵͳ������ʾ������
typedef struct {
	ALM_PRESENT	PhsAlm;			  // ������������ʾ����
	ALM_PRESENT	TechAlm;			  // ��������������ʾ����
	BLINK_FEATURE  Blink;			   // �����Ƿ���˸���Ժ��ַ�ʽ��˸��
	INT8		   AudioLevel;		  // �Ƿ���Ҫ�򱨾�ģ�鷢����Ϣ��-1�������ͣ�
									 // 0��������1-3����������
	INT8		   AlmLevel;			// -1�������ͣ�0-2����Ӧ����3���ޱ�����
	INT16		  HighestNewPhsAlm;	// ��ǰһ���жϺ��·��ֵ���߼���������,�������
									 // ���ͬһ������±���������STRINGID�ж����
									 // ����˳����ѡȡ����һ��,��������ARR�����Ĵ���
	INT8		   HighestNewPhsAlmLevel;  
									 // ��ǰѡȡ�ı�������
	DATETIME	   Time;				// ��һ��������������ʱ�䡣
	CHAR		   PauseMsg[40];		// ������ͣ��Ϣ����ʾ�ռ䡣
}ALM_PRESENTINFO;


// ��ALARMINFOSTR������������Ŀ���״̬��
typedef struct {
	 
	 INT8	   *Effect;			// ָʾ����������Ƿ���Ч��TRUE, ��Ч,FLASE����Ч����ϵͳ�Ա������صĶ���һ�¡�
	 INT8		EffectLastTime;
									// ��һʱ�̵ı��������Ƿ�򿪣�
									// ��Ϊ��Ҫ�ڱ������شӹرյ���ʱΪ����trigger 
									// ״̬�ı��������±�������ʾ��������Ҫ�жϡ�
									// ĿǰֻΪ�����������ǣ���Ϊ����������ʼ�մ򿪵ġ�
	 INT8		Exist;			 // ��Ӧ�Ĳ���ģ���Ƿ���ڡ�
	 INT8		Trg;			   // ��ǰ�ñ������Ƿ񱻴�����TRUE��������FALSE�������
	 INT8		Prsnt;			 // ָʾ�ñ����Ƿ��Ѿ�����ʾ�����������󣬼����Ѿ�������ı�����ֻҪû����ʾ�����ͻ���Ҫ������ʾ��TRUE������ʾ����FALSE��δ��ʾ��
	 INT8		Clearable;		 // ��������ⱨ���Ƿ���������TRUE�����ԡ�FALSE�����ɡ�
	 INT8		Cleared;		   // ��ʾĿǰ�������Ƿ������״̬��TRUE�������״̬��FLASE���������״̬��
	 INT8		LeadOff;		   // ��ʾ�Ƿ������䣬TRUE����; FALSE, ���ǡ�remedy bug 8.
	 UINT16	  SpecialLeadOff;	// ��ʾΪ��ECG/SPO2��ĵ������䱨����
	 CHAR	  **AlmStr;			// ������ʾ���ִ�ָ���ָ�롣
	 INT8	   *AlmLevP;		   // ָ�򱨾������ָ�롣
	 INT8		Latch;			 // ָʾ����Ŀ�ı����Ƿ�latch.
	 INT8		Critical;		  // ˵�����ֱ����Ƿ�ϵͳ���ȼ���ߣ����ϵͳ���ȼ���ߣ���������ʾ��
	 DATETIME	Time;			  // ��һ�δ����̬�򴥷�̬ת����ϵͳʱ�䡣
	 INT8		Module;			// ָ���ñ�������һ��ģ����ء� 
	 INT8		NewAlarm;		  // �����һ���·����ı�������λ���ᱻдΪTRUE��������ǣ�
									// ���λ���ᱻдΪFALSE��Ŀǰֻ�������������á�
	 INT8		Hold;			  // ���ñ�����������δ���ڴ���������¼/�洢��ʱ��Holdһֱ��
									// ����ΪTRUE�����ñ�������������Ǳ����ڴ���������¼/�洢��
									// ������ΪFALSE��
	 INT8		AllClrable;		// �ڰ���Pause�����Ƿ���Ҫ�������ȫ�������
	 
}ALM_ITEM;


// ��ALM_CTRL_BLOCK���� ���ڱ�����ȫ�ֿ��ƿ�
typedef struct {
	 INT8	   *LatchP;				   // ָ��Latch��ʽ�ֽڵ�ָ�롣
	 INT8		PrvLatchState;			// ��һ�ε�latch״̬
	 INT8		AlmSilent;				// ��ǰ��Silence״̬������ΪSilence�Ŀ�����ȫ�ڸò�����ʵ�֣�����ϵͳ������������������ٶ���Silence��Pause״̬��
	 INT16	   AlmSilenceRemain;		 // Silence״̬��ʣ�¶����롣
	 INT16	   AlmPauseRemain;		   // Pause״̬��ʣ�¶����롣
	 INT8		AlmPause;				 // ��ǰ��Pause״̬��
	 INT8		TechNew;				  // �Ƿ����µļ������������������ڿ��ƴ�Ͼ���������ͣ״̬��
	 INT8		PhsNew;				   // �Ƿ����µ�������������
	 INT16	   PhsAlmDisFocusIndex;	  // ��ǰ���ڱ�����һ�������������Ϊ0,���ޱ�������
	 INT16	   TechAlmDisFocusIndex;	 // ��ǰ���ڱ�����һ�μ�������
	 
	 INT8		HighestAlmLev;			// ��ǰ��ߵı�������
	 INT8		HighestAlmLevLastTime;	// ��һ���ж�ʱ����߱�������
	 
	 INT8	   *AlmSoundLevel;			// ָ��һ��ȫ����������˵��ϵͳ������������ĵ�ǰֵ��
	 INT8		AlmSoundLevelLastTime;	// ˵����һ���ж�ʱϵͳ����������
	 INT8		AlmPauseLastTime;		 // ��һ�ε�Pause״̬
	 INT8		AlmSilentLastTime;		// ��һ�ε�Silent״̬��
	 INT8		LanChange;				// �����Ƿ����仯��
	 INT8		KeyboardLoad;			 // ��ʾkeyboard�ոռ��أ���Ҫ�ٴ�
										   // ���䷢�ͱ�����Ϣ��
}ALM_CTRL_BLOCK;

#ifdef  ALARM_GLOBALS
#define ALARM_EXTERN  
#else
#define ALARM_EXTERN   extern
#endif


//----------------------------------------------------------------
// Global things defined in this source file.
// Global data to say how to display alarm information.
ALARM_EXTERN ALM_PRESENTINFO AlmPrsntInfo;  

// things only used in this file.
ALARM_EXTERN BLINK_FEATURE   BlinkFeature;
 
// Global controller of the alarm system.
ALARM_EXTERN ALM_CTRL_BLOCK AlmGlbCtlr;   

// Global, counter to fire alarm system.
ALARM_EXTERN CHAR  AlmTimerForModuleChange[MID_MAX];
ALARM_EXTERN INT16 Alm_PrompNdx4MdlLoad[MID_MAX];

// Physical alarm information.
// As "pause" state is displayed in the area where physiological 
// alarm is displayed, so, plus 1.
ALARM_EXTERN ALM_ITEM   PhsAlmInfo[STR_ALM_PHS_MAX - STR_ALM_PHS_FIRST + 2]; 

// Technical alarm information.
ALARM_EXTERN ALM_ITEM   TechAlmInfo[STR_ALM_TECH_MAX - STR_ALM_TECH_FIRST + 2]; 

// NIBP technical alarm information.
ALARM_EXTERN ALM_ITEM   NibpTechAlmInfo[1 + 1]; 


/* �����ṩ�Ľӿں��� */
VOID  TriggerAlarm(UINT16 trg, INT16 index); 
VOID  TriggerAlarm2(UINT16 trg, INT16 index); 
VOID  ChangeModuleInfoForAlmSystem(BOOL load, INT16 module_type);
VOID  OnSilence(VOID);
VOID  OnPause(VOID);
VOID  ChangeModuleInfoForAlmSystem2(BOOL load, INT16 module_type);
VOID  OnSilence2(VOID);
VOID  OnPause2(VOID);
BOOL  InitAlarmSystem(VOID);
VOID  TermAlarm(VOID);
VOID  ClearAllAlarm (INT16 module_id);
VOID  ProcessAlarmInfo (VOID);

INT32 AlarmProc (HANDLE task, INT32 msg, UINT32 wParam, UINT32 lParam);
VOID  AlarmProcess(VOID);
#endif

