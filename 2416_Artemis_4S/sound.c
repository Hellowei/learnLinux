/*****************************************************************************************
版权所有:			和心重典
版本号:				1.0.0
生成日期:			2012.10.25
文件名:				Sound.c
作者:					zhoutao
功能说明:			声音初始化设置和播放声音函数
其它说明:			无
所属文件关系:		本文件为工程规约代码文件
*****************************************************************************************/
#define	 SOUND_GLOBALS
#include "includes.h"

#include <malloc.h>
#include <getopt.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <locale.h>
#include <assert.h>
#include <sys/poll.h>
#include <sys/uio.h>
#include <sys/signal.h>
#include <sys/ipc.h>
#include <sys/msg.h>


static int msg_id;

/*
 * 初始化音频客户端
 * 在调用以下接口之前初始化函数，且只能初始化一次
 * 成功返回：0
 * 错误返回：－1
 */
int ac_init()
{
	msg_id = msgget((key_t)WAV_MSG_KEY, 0666 | IPC_CREAT);

	if (msg_id == -1) 
	{
		perror("can't create msg queue from system");
		return -1;
	}
	return 0;
}

/*
 * 播放心率音
 * 输入参数: 0 ~ 128
 * 0: 静音
 * 128: 最大
 */
void ac_sound_beat(int vol)
{
	struct wav_msg_t wav_msg;

	if (vol > 128) vol = 128;
	if (vol < 0) vol = 0;

	wav_msg.msg_type = 1;
	wav_msg.flag = SND_EVT_PRI_MI;
	wav_msg.vol = vol;
	wav_msg.snd_id = SND_ID_BEAT;
	msgsnd(msg_id, (void *)&wav_msg, sizeof(struct wav_msg_t) - sizeof(long int), IPC_NOWAIT);
}


/*
 * 播放高级报警音
 * 输入参数: 0 ~ 128
 * 0: 静音
 * 128: 最大
 */
void ac_sound_high(int vol)
{
	struct wav_msg_t wav_msg;

	if (vol > 128) vol = 128;
	if (vol < 0) vol = 0;

	wav_msg.msg_type = 1;
	wav_msg.flag = SND_EVT_PRI_HI;
	wav_msg.vol = vol;
	wav_msg.snd_id = SND_ID_HIGH;
	msgsnd(msg_id, (void *)&wav_msg, sizeof(struct wav_msg_t) - sizeof(long int), IPC_NOWAIT);
}


/*
 * 播放中级报警音
 * 输入参数: 0 ~ 128
 * 0: 静音
 * 128: 最大
 */
void ac_sound_middle(int vol)
{
	struct wav_msg_t wav_msg;

	if (vol > 128) vol = 128;
	if (vol < 0) vol = 0;

	wav_msg.msg_type = 1;
	wav_msg.flag = SND_EVT_PRI_HI;
	wav_msg.vol = vol;
	wav_msg.snd_id = SND_ID_MIDDLE;
	msgsnd(msg_id, (void *)&wav_msg, sizeof(struct wav_msg_t) - sizeof(long int), IPC_NOWAIT);
}


/*
 * 播放低级报警音
 * 输入参数: 0 ~ 128
 * 0: 静音
 * 128: 最大
 */
void ac_sound_low(int vol)
{
	struct wav_msg_t wav_msg;

	if (vol > 128) vol = 128;
	if (vol < 0) vol = 0;

	wav_msg.msg_type = 1;
	wav_msg.flag = SND_EVT_PRI_HI;
	wav_msg.vol = vol;
	wav_msg.snd_id = SND_ID_LOW;
	msgsnd(msg_id, (void *)&wav_msg, sizeof(struct wav_msg_t) - sizeof(long int), IPC_NOWAIT);
}


/*
 * 播放按键音
 * 输入参数: 0 ~ 128
 * 0: 静音
 * 128: 最大
 */
void ac_sound_key(int vol)
{
	struct wav_msg_t wav_msg;

	if (vol > 128) vol = 128;
	if (vol < 0) vol = 0;

	wav_msg.msg_type = 1;
	wav_msg.flag = SND_EVT_PRI_LO;
	wav_msg.vol = vol;
	wav_msg.snd_id = SND_ID_KEY;
	msgsnd(msg_id, (void *)&wav_msg, sizeof(struct wav_msg_t) - sizeof(long int), IPC_NOWAIT);
}


/*
 * 播放示例音
 * 输入参数: 0 ~ 128
 * 0: 静音
 * 128: 最大
 */
void ac_sound_example(int vol)
{
	struct wav_msg_t wav_msg;

	if (vol > 128) vol = 128;
	if (vol < 0) vol = 0;

	wav_msg.msg_type = 1;
	wav_msg.flag = SND_EVT_PRI_LO;
	wav_msg.vol = vol;
	wav_msg.snd_id = SND_ID_EXAMPLE;
	msgsnd(msg_id, (void *)&wav_msg, sizeof(struct wav_msg_t) - sizeof(long int), IPC_NOWAIT);
}

