#include <unistd.h>
#include "get_next_line.h"

#define BUFFER_SIZE 128

static char
	*process_line(char *line, ssize_t line_len, ssize_t buffer_len)
{
    
}

/**
 * After A newline there should probably be a NUL char
 */
char
	*get_next_line(int fd)
{
	static char	*ret;
	char		buffer[BUFFER_SIZE];
	char		*newline_pos;
	ssize_t 	bytes_read;
	ssize_t		old_size;

	if (fd < 0)
		return (0);
	bytes_read = 0;
	newline_pos = 0;
	while (1)
	{
		if (bytes_read)
			newline_pos = ft_strchr(&buffer[0], '\n');
		if (newline_pos || (bytes_read < BUFFER_SIZE))
		{
			//Found line
		}
        old_size = bytes_read;
		bytes_read += read(fd, &buffer[0], BUFFER_SIZE);
		if (bytes_read <= -1)
			return (NULL);
		ft_realloc(ret, old_size, bytes_read);
		if (!ret)
			return (NULL);
		ft_memcpy(ret + old_size + 1, &buffer[0], bytes_read - old_size);
	}
	newline_pos = ft_strchr(&buffer[0], '\n');
	return (0);
}
