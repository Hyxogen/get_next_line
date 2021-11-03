/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/27 09:32:39 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/10/28 13:16:00 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void
	*ft_memchr(const void *arr, unsigned char c, size_t n)
{
	const unsigned char	*arr_cpy;

	arr_cpy = arr;
	while (n)
	{
		if (*arr_cpy == c)
			return ((void *) arr_cpy);
		if (!*arr_cpy)
			break ;
		n--;
		arr_cpy++;
	}
	return (NULL);
}

/**
 * Todo try to optimize this function like
 * my libft memset
 */
void
	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char			*dst_cpy;
	const unsigned char		*src_cpy;

	if (dst == src)
		return (dst);
	dst_cpy = dst;
	src_cpy = src;
	while (len)
	{
		dst_cpy[len - 1] = src_cpy[len - 1];
		len--;
	}
	return (dst);
}

char
	*ft_strndup(const char *str, size_t len) {
	char *ret;
	const char *temp;
	size_t str_len;

	temp = str;
	str_len = len;
	while (str_len && *temp)
	{
		temp++;
		str_len--;
	}
	str_len = temp - str;
//	str_len = strnlen(str, len);
	if (len <= str_len)
		len = len + 1;
	else
		len = str_len + 1;
	ret = malloc(len);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, str, len - 1);
	ret[len - 1] = '\0';
	return (ret);
}

/**
 * Can probably speed up this function by
 * copying 8 bytes ints first etc like my
 * memset from libft
 */
void
	*ft_realloc(void *src, size_t old_len, size_t new_len)
{
	unsigned char	*ret;

	ret = malloc(new_len);
	if (!ret)
		return (NULL);
	if (src) {
		ft_memcpy(ret, src, old_len);
		free(src);
	}
	return (ret);
}

/*
 * TODO check if this memset works
 */
void
	*ft_memset(void *src, int c, size_t len)
{
	unsigned char	*src_cpy;

    src_cpy = src;
    while (len)
    {
        src_cpy[len - 1] = (unsigned char) c;
        len--;
    }
    return (src);
}
