/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osalmine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:04:42 by osalmine          #+#    #+#             */
/*   Updated: 2019/11/08 16:21:43 by osalmine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
//	char	s[1];
	int		i;
	int		fd;
	char	*line;

//	read(0, s, 1);
	i = 1;
	line = (char *)malloc(sizeof(char) * 100);
	if (argc == 1)
	{
			while (get_next_line(0, &line))
				printf("%s\n", line);
	}
	if (argc >= 2)
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
				printf("$%s$\n", line);
			i++;
		}
	}
	free(line);
//	read(0, s, 1);
	return (0);
}
