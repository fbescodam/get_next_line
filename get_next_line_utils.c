/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 15:33:10 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/11 17:15:02 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		ft_bzero(void *s, size_t n)
{
	while (n > 0)
	{
		*(char *)s = '\0';
		s++;
		n--;
	}
}

void		*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dest_cpy;
	const char	*src_cpy;

	if (dest == NULL && src == NULL)
		return (NULL);
	dest_cpy = dest;
	src_cpy = src;
	while (n > 0)
	{
		*dest_cpy = *src_cpy;
		dest_cpy++;
		src_cpy++;
		n--;
	}
	return (dest);
}

size_t		ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	if (size != 0)
	{
		i = 0;
		while (i < size && src[i] != '\n')
		{
			dest[i] = src[i];
			i++;
		}
		//dest[i] = '\0';
	}
	return (1);
}

size_t		ft_strllen(const char *s, size_t maxlen)
{
	size_t	i;

	i = 0;
	while (i < maxlen && s[i] != '\0' && s[i] != '\n')
	{
		// printf("i: %ld, maxlen: %ld\n", i, maxlen);
		i++;
	}
	return (i);
}

void		replace_newlines(char *buff)
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (buff[i] == '\n')
			buff[i] = '\0';
		i++;
	}
}
