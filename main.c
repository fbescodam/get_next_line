/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 16:16:54 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/11 19:30:22 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	int		fd;
	char	**line;
	int		result;

	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	else
		fd = 0;
	line = (char **)malloc(sizeof(char *));
	*line = NULL;
	if (line)
	{
		result = 1;
		while (result > 0)
		{
			result = get_next_line(fd, line);
			if (result > 0)
				printf("%s\n", *line);
			else if (result < 0)
				printf("An error occurred\n");
		}
		if (*line)
			free(*line);
		free(line);
	}
	else
		printf("Memory allocation failed!\n");
	//system("leaks a.out");
	return (0);
}
