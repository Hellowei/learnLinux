#include "file.h"

BOOL set_file_size(int fd, long size)
{
	if (fd < 0)
	{
		return 0;
	}
	
	if (size > 0)
	{
		short buf = 0;
		long b = lseek(fd, size - 1, SEEK_SET);
		write(fd, &buf, 1);
		buf = dup(fd);
		close(buf);
		fsync(fd);
		return 1;
	}
	
	return 0;
}


