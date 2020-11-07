/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/07 17:16:03 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/07 20:07:58 by fbes          ########   odam.nl         */
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
	static int					buff_from_static;
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
		if (nl && buff_from_static == 0)
			bytes_to_copy = nl - buff;
		else if (nl && buff_from_static == 1)
			bytes_to_copy = BUFFER_SIZE - (nl - buff) - 1;
		else
			bytes_to_copy = BUFFER_SIZE;
		//printf("bytes_to_copy: %llu\n", bytes_to_copy);
		//printf("line_length: %llu\n", line_length);
		temp = (char *)malloc((line_length + bytes_to_copy + 1) * sizeof(char));
		if (*line && line_length > 0)
		{
			//printf("*line not NULL, copying %ld bytes\n", line_length);
			ft_memcpy(temp, *line, line_length);
			free(*line);
		}
		if (buff_from_static == 0)
			ft_memcpy(temp + line_length, buff, bytes_to_copy);
		else
			ft_memcpy(temp + line_length, nl + 1, bytes_to_copy);
		*line = temp;
		line_length += bytes_to_copy;
		if (nl && buff_from_static == 0)
		{
			//printf("newline found\n");
			temp[line_length] = '\0';
			//printf("line_length: %llu\n", line_length);
			//printf("ft_strlen(*line): %ld\n", ft_strlen(*line));
			buff_from_static = 1;
			return (1);
		}
		//else
			//printf("no newline found\n");
		ft_bzero(buff, BUFFER_SIZE);
		read_bytes = read(fd, buff, BUFFER_SIZE);
		buff_from_static = 0;
	}
	if (buff)
		free(buff);
	return (0);
}
