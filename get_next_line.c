/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/11 15:30:52 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/11 17:24:30 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		handle_buffer(char **line, size_t *line_length, char *buff, size_t *start, size_t read_bytes)
{
	char			*temp;
	size_t			bytes_to_copy;

	//printf("start: %ld\n", *start);
	if (*start > read_bytes)
	{
		*start = 0;
		return (read_bytes);
	}
	bytes_to_copy = ft_strllen(buff + *start, read_bytes - *start);
	//printf("bytes_to_copy: %ld\n", bytes_to_copy);
	//printf("line_length: %ld\n", *line_length);
	temp = (char *)malloc((*line_length + bytes_to_copy + 1) * sizeof(char));
	if (!temp)
		return (-1);
	if (*line && line_length > 0)
	{
		//printf("now copying old string\n");
		//ft_strlcpy(temp, *line, *line_length);
		ft_memcpy(temp, *line, *line_length);
		free(*line);
	}
	//printf("now copying buffer\n");
	if (bytes_to_copy > 0)
		ft_strlcpy(temp + *line_length, buff + *start, bytes_to_copy);
	else
		temp[0] = '\0';
	*line = temp;
	*line_length += bytes_to_copy;
	if (bytes_to_copy < read_bytes - *start)
	{
		temp[*line_length] = '\0';
		*start += bytes_to_copy + 1;
		return (1);
	}
	else
	{
		ft_bzero(buff, BUFFER_SIZE);
		*start = 0;
		return (0);
	}
}

int		get_next_line(int fd, char **line)
{
	static void		*buff;
	static size_t	start;
	ssize_t			read_bytes;
	size_t			line_length;
	int				handle_result;

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
		handle_result = handle_buffer(line, &line_length, buff, &start, read_bytes);
		if (handle_result > 0)
			return (1);
		else if (handle_result < 0)
			return (-1);
		read_bytes = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	if (read_bytes < 0)
		return (-1);
	return (0);
}
