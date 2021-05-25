/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:50:55 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/25 16:31:37 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

char	*ft_trim_bfr_ln(const char *stc_line)
{
	char	*relic;

	if (!stc_line)
		return (NULL);
	relic = (char *)stc_line;
	while (relic[0] && relic[0] != '\n')
		relic++;
	if (strlen(relic) > 1)
		relic++;
	else
		return (NULL);
	return (relic);
}

int	ft_gnl_output(char *stc_line, char **line)
{	
	char	*temp;

	if (!stc_line)
		return (-1);
	if (ft_strchr(stc_line, '\n') != NULL)
	{
		temp = ft_substr(stc_line, 0, (ft_strchr(stc_line, '\n') - stc_line));
		*line = strdup(temp);
		if (temp)
			free(temp);
		return (1);
	}
	else if (ft_strchr(stc_line, '\0') != NULL)
	{
		*line = strdup(stc_line);
		free(stc_line);
		return (0);
	}
	else
		return (-1);
}

void	ft_free_and_clean(char **temp, char **stc_line)
{
	if (*stc_line != NULL && *temp == NULL)
	{
		free(*stc_line);
		*stc_line = strdup("");
	}	
	else if (*temp != NULL && *stc_line != NULL)
	{
		free(*stc_line);
		*stc_line = strdup(*temp);
	}	
	else
		*stc_line = strdup("");
}

int	get_next_line(int fd, char **line)
{
	static char		*stc_line = NULL;
	char			*buffer;
	char			*temp;
	ssize_t			reader;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line) // OK
		return (-1);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1); // OK
	temp = ft_trim_bfr_ln(stc_line);
	ft_free_and_clean(&temp, &stc_line);
	reader = 1;
	while (!ft_strchr(stc_line, '\n') && reader > 0)
	{
		reader = read(fd, buffer, BUFFER_SIZE);
		buffer[reader] = '\0';
		temp = ft_strjoin(stc_line, buffer);
		free(stc_line);
		stc_line = strdup(temp);
		free(temp);
	}
	free(buffer);
	return (ft_gnl_output(stc_line, line));
}
