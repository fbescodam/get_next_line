/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 16:16:20 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/04 21:21:06 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static unsigned long long	add_to_line(char **line, unsigned long long *line_size, void *buff, unsigned long long start)
{
	char				*temp;
	unsigned long long	buff_size_nl;
	void				*nl;

	nl = ft_memchr(buff, '\n', BUFFER_SIZE);
	if (nl)
		buff_size_nl = nl - buff;
	else
		buff_size_nl = BUFFER_SIZE;
	temp = (char *)malloc((*line_size + buff_size_nl + 1) * sizeof(char));
	if (temp)
	{
		if (*line)
		{
			ft_memcpy(temp, *line, (size_t)line_size);
			free(*line);
		}
		ft_memcpy(temp + *line_size, buff, buff_size_nl);
		temp[*line_size + buff_size_nl] = '\0';
		*line = temp;
		if (buff_size_nl < BUFFER_SIZE)
			return (nl - buff);
		*line_size += buff_size_nl;
		return (0);
	}
	return (-1);
}

int						garbage_collect(int ret, char *buff)
{
	if (buff)
		free(buff);
	return (ret);
}

int						get_next_line(int fd, char **line)
{
	static void					*buff;
	static unsigned long long	read_bytes;
	unsigned long long			line_size;
	static unsigned long long	ret;

	if (BUFFER_SIZE < 1)
		return (-1);
	if (fd >= 0)
	{
		line_size = 0;
		if (!buff)
		{
			buff = (void *)malloc(BUFFER_SIZE);
			ft_bzero(buff, BUFFER_SIZE);
			read_bytes = read(fd, buff, BUFFER_SIZE);
		}
		while (read_bytes > 0)
		{
			ret = add_to_line(line, &line_size, buff, ret);
			if (ret > 0)
				return (1);
			else if (ret < 0)
				return (garbage_collect(-1, buff));
			read_bytes = read(fd, buff, BUFFER_SIZE);
		}
		free(buff);
		return (0);
	}
	else
		return (-1);
}
