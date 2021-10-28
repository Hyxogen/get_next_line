/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/27 17:25:58 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/10/28 09:38:03 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char *get_next_line(int fd);

int
	main(void)
{
	char	*line;
	int		fd;

	fd = open("test", O_RDONLY);
	while (1)
	{
	    line = get_next_line(fd);
        printf("RESULT:\"%s\"\n", line);
        if (!line)
            break ;
        free(line);
    }
	return (0);
}
