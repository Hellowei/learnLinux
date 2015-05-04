#ifndef TEXT_H
#define TEXT_H

#ifdef TEXT_GLOBALS
#define TEXT_EXT
#else
#define TEXT_EXT extern
#endif

#define IS_GB(ch1, ch2) (ch1 >= 0xA1 && ch1 <= 0xFE && ch2 >= 0xA1 && ch2 <= 0xFE)

typedef struct strbuffer_s{
	char	*string;
	int	 maxlen;
}StrBuffer;

#define TextNew(size_t)	 ((UCHAR *)malloc(size_t))
#define TextDel(pStr)	   free(pStr);
TEXT_EXT INT32 GUIAPI RuStringNum (const CHAR* text);
char *NewStrBuffer(StrBuffer * buff, int len);
#endif

