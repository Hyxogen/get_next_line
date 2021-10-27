/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dmeijer <dmeijer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/27 09:32:39 by dmeijer       #+#    #+#                 */
/*   Updated: 2021/10/27 09:32:50 by dmeijer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <wchar.h>
#include <stdlib.h>

char
	*ft_strchr(const char *str, char c)
{
	while (1)
	{
		if (*str == c)
			return ((char *) str);
		if (!*str)
			break ;
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
	unsigned char				*dst_cpy;
	const	unsigned char	*src_cpy;

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
	*ft_strndup(const char *str, size_t len)
{
	char				*ret;
	const char	*temp;
	size_t			str_len;

	temp = str;
	while (*temp)
		temp++;
	str_len = temp - str;
	if (len <= str_len)
		len = len + 1;
	else
		len = str_len + 1;
	ret = malloc(len);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, str, len);
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
	unsigned char *src_cpy;
	unsigned char	*ret;

	ret = malloc(new_len);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, src, old_len);
	free(src);
	return (ret);
}

char
	*ft_strjoin(const char *str1, const char *str2)
{
	size_t	str1_len;
	size_t	str2_len;
	char*		ret;

	str1_len = ft_strchr(str1, '\0') - str1;
	str1_len = ft_strchr(str2, '\0') - str1;
	ret = malloc (str1_len + str2_len + 1);
	if (!ret)
		return (0);
	ft_memcpy(ret, str1, str1_len);
	ft_memcpy(ret + str1_len + 1, str2, str2_len + 1);
	return (ret);
}
