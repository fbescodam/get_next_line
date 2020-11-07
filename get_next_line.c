/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/07 17:16:03 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/07 18:25:26 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int			get_next_line(int fd, char **line)
{
	char						*temp;
	void						*nl;
	static void					*buff;
	static unsigned long long	read_bytes;
	unsigned long long			line_length;
	unsigned long long			bytes_to_copy;

	if (!buff)
	{
		buff = malloc(BUFFER_SIZE);
		if (buff)
			ft_bzero(buff, BUFFER_SIZE);
		else
			return (-1);
		read_bytes = read(fd, buff, BUFFER_SIZE);
	}
	line_length = 0;
	while (read_bytes > 0)
	{
		nl = ft_memchr(buff, '\n', BUFFER_SIZE);
		if (nl)
			bytes_to_copy = nl - buff;
		else
			bytes_to_copy = BUFFER_SIZE;
		temp = (char *)malloc(line_length + bytes_to_copy + 1);
		if (*line)
		{
			ft_memcpy(temp, *line, line_length);
			free(*line);
		}
		ft_memcpy(temp + line_length, buff, bytes_to_copy);
		*line = temp;
		line_length += bytes_to_copy;
		if (nl)
		{
			line[line_length] = '\0';
			return (1);
		}
		ft_bzero(buff, BUFFER_SIZE);
		read_bytes = read(fd, buff, BUFFER_SIZE);
	}
	return (0);
}
