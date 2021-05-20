/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:50:55 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/19 19:41:31 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

void		*ft_memset(void *b, int c, size_t len)
{
	unsigned	char	*ub;

	ub = (unsigned char *)b;
	while (len > 0)
	{
		*ub = c;
		len--;
		ub++;
	}
	return (b);
}

int			ft_memdel(void **ptr)
{
	if (*ptr)
	{
		ft_memset(*ptr, 0, ft_strlen(*ptr));
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	unsigned long	counter;

	counter = 0;
	while (str[counter])
		counter++;
	return (counter);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*copy;
	size_t			i;
	size_t			j;

	if (!s1 || !s2)
		return (NULL);
	copy = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * (sizeof(char)));
	if (!(copy))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		copy[i] = s2[j];
		i++;
		j++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strchr(const char *str, int c)
{
	char			*new_ptr;
	char			d;
	unsigned int	iter;

	iter = 0;
	if (!str)
		return (NULL);
	d = (unsigned char)c;
	new_ptr = (char *)str;
	while (str[iter])
	{
		if (str[iter] != d)
			new_ptr++;
		else
			return (new_ptr);
		iter++;
	}
	if (str[iter] == d)
		return (new_ptr);
	else
		return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*copy;
	size_t			len_copy;
	size_t			iter;

	len_copy = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) > start)
		len_copy = (ft_strlen(s) - start);
	if (len < len_copy && ft_strlen(s) > start)
		len_copy = len;
	len_copy++;
	copy = malloc(len_copy * (sizeof(char)));
	if (!(copy))
		return (NULL);
	iter = 0;
	while (len_copy > 1 && s[start] && len > 0)
	{
		copy[iter] = s[start];
		iter++;
		start++;
		len--;
	}
	copy[iter] = '\0';
	return (copy);
}

// explanations 

/*

return (-1) si couille [line == NULL, temp_size = 0 ou negatif, fd < 0]
return 0 si EOF atteint
return 1 si \n atteint (il reste des lignes dans le fichier)

!! return = et doit lit si fichier vide (soit lire une string vide mais pas NULL)

!! cut le \n si présent
!! stop si le temp_size est atteint

du coup on arrête gnl si on atteint le buffer ou un \n (a la premiere condition remplie)

*/

/*

pseudo code :

1) intialiser variable static char *stc_line == NULL;
2) intialiser variable char *buffer (array temporaire)
3) créer variable reader type ssize_t pour contenir le return des differentes lectures.

4) malloquer cet array temporaire avec buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))
5) tant que l'on ne rencontre pas de \n ou de EOF, lire avec read en boucle dans la limit du 
BUFFER_SIZE (stocker dans variable read de type ssize_t)
 	=> si read < 0 on va free buffer et return -1 (couille)
 	=> sinon join buffer à stc_line;
6) deux possibilités : on atteint le EOF ou on rencontre un \n :
	=> on rencontre un \n : point |7|
	=> on recontre un EOF : point |8|
7) suivre ces étapes :
	=> join buffer à stc_line sans le \n et ce qui suit après
	=> free buffer
	=> retourner 1
8) suivre ces étapes :
	=> join buffer à stc_line, '\0' compris
	=> free buffer
	=> retourner 0

!!!!! il faudra aussi penser à calculer ou on en est (quelle ligne) => variable static size_t ?

!!!!! EOF se matérialise par un '/0'

*/

// static int	ft_ln_checker(char *stc_line, char *buffer, int fd) // check le num de lignes
// {
// 	// TODO
// }

char	*ft_trim_bfr_ln(const char *stc_line)
{
	char	*relic;

	if (!stc_line)
		return (NULL);
	relic = (char *)stc_line;
	while (relic[0])
	{
		if (relic[0] != '\n')
		{
			relic++;
			printf("%s\n", relic);
		}
		if (ft_strlen(relic) > 1)
			relic++;
		else
			return (NULL);
	}
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
		return (0);
	}
	else
		return (-1);
}

int	get_next_line(int fd, char **line) // WIP
{
	static char		*stc_line = NULL;
	char			*buffer;
	char			*temp;
	char			*relic;
	ssize_t			reader;

	if (fd < 0 || BUFFER_SIZE <= 0) // OK voir si rajouter !line
		return (-1);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	relic = ft_trim_bfr_ln(stc_line);
	printf("%s\n", relic);
	if (stc_line != NULL && relic == NULL)
	{
		free(stc_line);
		stc_line = strdup("");
	}	
	else if (relic)
	{
		stc_line = strdup(relic);
	}	
	else
		stc_line = strdup("");
	while (!ft_strchr(stc_line, '\n') 
		&& ((reader = read(fd, buffer, BUFFER_SIZE)) > 0)) // good : check if \n or EOF
	{
		buffer[reader] = '\0'; //finishing the buffer by \0;
		temp = ft_strjoin(stc_line, buffer);
		free(stc_line);
		stc_line = strdup(temp);
		free(temp);
	}
	free(buffer);
	return (ft_gnl_output(stc_line, line));
}

int		main(void)
{
	char	*line;
	int		nb_line;
	int		fd;
	// int		fd2;
	// int		fd3;

	nb_line = 1;
	if ((fd = open("./baudelaire.txt", O_RDONLY)) == -1)
		printf("le fichier n'existe pas.");
	// if ((fd2 = open(av[2], O_RDONLY)) == -1)
	// 	printf("le fichier n'existe pas.");
	// if ((fd3 = open(av[3], O_RDONLY)) == -1)
	// 	printf("le fichier n'existe pas.");
	line = NULL;
	int ret = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && nb_line < 10)
	{
		printf("line[%d]: %s\n", nb_line, line);
		free(line);
		// line = NULL;
		// ret = get_next_line(fd2, &line);
		// printf("line[%d]: %s\n", nb_line, line);
		// free(line);
		// line = NULL;
		// ret = get_next_line(fd3, &line);
		// printf("line[%d]: %s\n", nb_line, line);
		// free(line);
		nb_line++;
	}
	printf("line[%d]: %s\n", nb_line, line);
	free(line);
	// line = NULL;
	// ret = get_next_line(fd2, &line);
	// printf("line[%d]: %s\n", nb_line, line);
	// free(line);
	// line = NULL;
	// ret = get_next_line(fd3, &line);
	// printf("line[%d]: %s\n", nb_line, line);
	// free(line);
	system("leaks a.out");
}
