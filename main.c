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

#include "ft_ansi.h"
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

void	test_poems(void)
{
	size_t	line_count;
	char	*line;
	int		fd_i;
	int		fd_a;
	int		fd_b;

	line = NULL;
	line_count = 0;
	fd_i = open("timmy_test_interleave.txt", O_RDONLY);
	fd_a = open("timmy_test_a.txt", O_RDONLY);
	fd_b = open("timmy_test_b.txt", O_RDONLY);
	if (fd_i < 0 || fd_a < 0 || fd_b < 0)
	{
		printf(ANSI_F_RED "Error opening files.\n" ANSI_RESET);
		return ;
	}
	printf(ANSI_F_YELLOW "Starting interleaved file read test...\n\n" ANSI_RESET);
	line_count = 0;
	while (line_count < 4)
	{
		line_count++;
		get_next_line(fd_i, &line);
		printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
		free(line);
	}
	while (get_next_line(fd_a, &line))
	{
		line_count++;
		printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
		free(line);
	}
	line_count++;
	get_next_line(fd_i, &line);
	printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
	free(line);
	while (get_next_line(fd_b, &line))
	{
		line_count++;
		printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
		free(line);
	}
	while (get_next_line(fd_i, &line))
	{
		line_count++;
		printf(ANSI_F_CYAN "%zu" ANSI_RESET "\t|%s" ANSI_F_CYAN "$\n" ANSI_RESET, line_count, line);
		free(line);
	}
	if (line_count != 45)
		printf(ANSI_F_RED "\nERROR: Interleaved files test failed! [ test_poems(...); ]\n" ANSI_RESET);
	else
		printf(ANSI_F_GREEN "\nDone.\n" ANSI_RESET);
	printf(ANSI_F_YELLOW "[ Lines Expected: 45, Lines Read: %zu ]\n" ANSI_RESET, line_count);
	fd_i = close(fd_i);
	fd_a = close(fd_a);
	fd_b = close(fd_b);
	if (fd_i < 0 || fd_a < 0 || fd_b < 0)
	{
		printf(ANSI_F_BRED "Fatal Error: Could not close open files!\n" ANSI_RESET);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
//	char	s[1];
	int		i;
	int		fd;
	int		ret;
	char	*line;

//	read(0, s, 1);
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
		if (!strcmp(argv[1], "test_poem"))
		{
			test_poems();
		}
		else
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
	}
//	read(0, s, 1);
	return (0);
}
