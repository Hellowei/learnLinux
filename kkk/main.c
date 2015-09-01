#include "stdio.h"
#include "file.h"

int main()
{
	FILE*	fp = fopen("data.txt","wb+");
	if(fp)
		set_file_size(fileno(fp), BYTE_NUM);
	return 0;
}

