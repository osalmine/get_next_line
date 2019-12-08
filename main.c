/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:04:42 by osalmine          #+#    #+#             */
/*   Updated: 2019/11/12 14:02:00 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		i;
	int		fd;
	int		ret;
	char	*line;

	ret = 0;
	i = 1;
	fd = 0;
	line = NULL;
	if (argc == 1)
	{
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			printf("%s\n", line);
			free(line);
		}
	}
	else if (argc >= 2)
	{
		while (argc > i)
		{
			fd = open(argv[i], O_RDONLY);
			if (fd < 0)
			{
				printf("Fd error\n");
				return (1);
			}
			while (get_next_line(fd, &line))
			{
				printf("$%s$\n", line);
				free(line);
			}
			i++;
		}
		fd = close(fd);
	}
	return (0);
}
