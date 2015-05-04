#ifndef _PINYIN_H
#define _PINYIN_H

#ifndef PINYIN_GLOBALS
#define PINYIN_EXTERN extern
#else
#define PINYIN_EXTERN 
#endif

PINYIN_EXTERN UCHAR *GetPyIndex (UCHAR *str);
#endif
