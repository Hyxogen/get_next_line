#include <stdio.h>
#include <fcntl.h>

char *get_next_line(int fd);

int
	main(void)
{
	int fd = open("test", O_RDONLY);
	get_next_line(fd);
	return (0);
}
