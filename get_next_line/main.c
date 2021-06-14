/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:14:57 by cjulienn          #+#    #+#             */
/*   Updated: 2021/06/14 11:19:58 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int		main(void)
{
	char	*line;
	int		nb_line;
	int		fd;

	nb_line = 1;
	if ((fd = open("./one_big_fat_line.txt", O_RDONLY)) == -1)
		printf("le fichier n'existe pas.");
	line = NULL;
	int ret = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && nb_line)
	{
		printf("line[%d]: %s\n", nb_line, line);
		free(line);
		nb_line++;
	}
	printf("line[%d]: %s\n", nb_line, line);
	free(line);
	system("leaks a.out");
}
