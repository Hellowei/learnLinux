#ifndef SOUND_H
#define SOUND_H


#ifdef	SOUND_GLOBALS
#define SOUND_EXTERN	
#else
#define SOUND_EXTERN 	extern
#endif


#define WAV_MSG_KEY 											2844


/* 音量级别 */
typedef enum _sound_vol_lev 
{
	SOUND_VOLUME_LEV_SILENCE,
	SOUND_VOLUME_LEV_LOW,
	SOUND_VOLUME_LEV_MED,
	SOUND_VOLUME_LEV_HIGH
}SOUNDVOLUMELEVEL;


/* 按键板指令ID. */
typedef enum _sound_cmd_id
{
   CMD_SOUND_SET_BEAT_VOLUME,	  /* 心跳声音量		   */
   CMD_SOUND_SET_KNOB_VOLUME,	  /* 键盘声音量		   */
   CMD_SOUND_SET_KNOB_SOUND,
   CMD_SOUND_SET_ALM_SOUND,
   CMD_SOUND_SET_PULSE_VOLUME,	 /* 设置脉搏音量		 */
   
   CMD_SOUND_MAX
}SOUNDCMDID;


enum SND_ID_ENUM 
{
	SND_ID_BEAT,
	SND_ID_HIGH,
	SND_ID_MIDDLE,
	SND_ID_LOW,
	SND_ID_KEY,
	SND_ID_EXAMPLE,
	SND_ID_OPEN,
	SND_ID_CLOSE,
	SND_ID_MAX,
};


enum SND_EVT_ENUM 
{
	SND_EVT_PRI_LO,
	SND_EVT_PRI_MI,
	SND_EVT_PRI_HI,
};


struct wav_msg_t 
{
	long int msg_type;
	int flag;
	int vol;
	int snd_id;
};


SOUND_EXTERN int  ac_init();
SOUND_EXTERN void ac_sound_beat(int vol);
SOUND_EXTERN void ac_sound_high(int vol);
SOUND_EXTERN void ac_sound_middle(int vol);
SOUND_EXTERN void ac_sound_low(int vol);
SOUND_EXTERN void ac_sound_key(int vol);
SOUND_EXTERN void ac_sound_example(int vol);
#endif

