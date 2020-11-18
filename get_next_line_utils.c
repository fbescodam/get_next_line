/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 15:33:10 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/18 16:22:10 by fbes          ########   odam.nl         */
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

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	size_t			size_to_malloc;

	if (nmemb == 0 || size == 0)
		return (malloc(1));
	size_to_malloc = size * nmemb;
	ptr = malloc(size_to_malloc);
	if (ptr)
		ft_bzero(ptr, size_to_malloc);
	return (ptr);
}

void		ft_strlcpy_nl(char *dest, const char *src, size_t size)
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
	}
}

size_t		ft_strlen_nl(const char *s, size_t maxlen)
{
	size_t	i;

	i = 0;
	while (i < maxlen && s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}
