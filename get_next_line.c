/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:50:55 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/21 14:29:54 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

// size_t	ft_strlen(const char *str)
// {
// 	unsigned long	counter;

// 	counter = 0;
// 	while (str[counter])
// 		counter++;
// 	return (counter);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char			*copy;
// 	size_t			i;
// 	size_t			j;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	copy = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * (sizeof(char)));
// 	if (!(copy))
// 		return (NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		copy[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j])
// 	{
// 		copy[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	copy[i] = '\0';
// 	return (copy);
// }

// char	*ft_strchr(const char *str, int c)
// {
// 	char			*new_ptr;
// 	char			d;
// 	unsigned int	iter;

// 	iter = 0;
// 	if (!str)
// 		return (NULL);
// 	d = (unsigned char)c;
// 	new_ptr = (char *)str;
// 	while (str[iter])
// 	{
// 		if (str[iter] != d)
// 			new_ptr++;
// 		else
// 			return (new_ptr);
// 		iter++;
// 	}
// 	if (str[iter] == d)
// 		return (new_ptr);
// 	else
// 		return (NULL);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char			*copy;
// 	size_t			len_copy;
// 	size_t			iter;

// 	len_copy = 0;
// 	if (!s)
// 		return (NULL);
// 	if (ft_strlen(s) > start)
// 		len_copy = (ft_strlen(s) - start);
// 	if (len < len_copy && ft_strlen(s) > start)
// 		len_copy = len;
// 	len_copy++;
// 	copy = malloc(len_copy * (sizeof(char)));
// 	if (!(copy))
// 		return (NULL);
// 	iter = 0;
// 	while (len_copy > 1 && s[start] && len > 0)
// 	{
// 		copy[iter] = s[start];
// 		iter++;
// 		start++;
// 		len--;
// 	}
// 	copy[iter] = '\0';
// 	return (copy);
// }



// real functions ! 



char	*ft_trim_bfr_ln(const char *stc_line) // OK
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
	if (ft_strchr(stc_line, '\n') != NULL) // cas \n
	{
		*line = strdup(ft_substr(stc_line, 0, (ft_strchr(stc_line, '\n') - stc_line))); 
		// check line before (do not merely copy, understand)
		return (1);
	}
	else if (ft_strchr(stc_line, '\0') != NULL) // cas EOF 
	{
		*line = strdup(stc_line);
		free(stc_line);
		return (0);
	}
	else
		return (-1);
}

int	get_next_line(int fd, char **line)
{
	static char		*stc_line = NULL;
	char			*buffer;
	char			*temp;
	char			*relic;
	ssize_t			reader;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	relic = ft_trim_bfr_ln(stc_line);
	if (stc_line != NULL && relic == NULL)
	{
		free(stc_line);
		stc_line = strdup("");
	}	
	else if (relic != NULL && stc_line != NULL)
		stc_line = strdup(relic);
	else
		stc_line = strdup("");
	while (!ft_strchr(stc_line, '\n') 
		&& ((reader = read(fd, buffer, BUFFER_SIZE)) > 0))
	{
		buffer[reader] = '\0'; 
		temp = ft_strjoin(stc_line, buffer);
		free(stc_line);
		stc_line = strdup(temp);
		free(temp);
	}
	free(buffer);
	return (ft_gnl_output(stc_line, line));
}

// int		main(void)
// {
// 	char	*line;
// 	int		nb_line;
// 	int		fd;

// 	nb_line = 1;
// 	if ((fd = open("tests/baudelaire.txt", O_RDONLY)) == -1)
// 		printf("le fichier n'existe pas.");
// 	line = NULL;
// 	int ret = 0;
// 	while ((ret = get_next_line(fd, &line)) > 0 && nb_line)
// 	{
// 		printf("line[%d]: %s\n", nb_line, line);
// 		free(line);
// 		nb_line++;
// 	}
// 	printf("line[%d]: %s\n", nb_line, line);
// 	free(line);
// 	system("leaks a.out");
// }
