/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:50:55 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/18 16:55:20 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>


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

du coup on arrête gnl si on atteint le temp ou un \n (a la premiere condition remplie)

*/

/*

pseudo code :

1) intialiser variable static char *stc_line == NULL;
2) intialiser variable char *temp (array temporaire)
3) créer variable reader type ssize_t pour contenir le return des differentes lectures.

4) malloquer cet array temporaire avec temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))
5) tant que l'on ne rencontre pas de \n ou de EOF, lire avec read en boucle dans la limit du 
BUFFER_SIZE (stocker dans variable read de type ssize_t)
 	=> si read < 0 on va free temp et return -1 (couille)
 	=> sinon join temp à stc_line;
6) deux possibilités : on atteint le EOF ou on rencontre un \n :
	=> on rencontre un \n : point |7|
	=> on recontre un EOF : point |8|
7) suivre ces étapes :
	=> join temp à stc_line sans le \n et ce qui suit après
	=> free temp
	=> retourner 1
8) suivre ces étapes :
	=> join temp à stc_line, '\0' compris
	=> free temp
	=> retourner 0

!!!!! il faudra aussi penser à calculer ou on en est (quelle ligne) => variable static size_t ?

!!!!! EOF se matérialise par un '/0'

*/

// static int	ft_ln_checker(char *stc_line, char *temp, int fd) // check le num de lignes
// {
// 	// TODO
// }

int	ft_gnl_output(char **temp, char *stc_line)
{	
	if (ft_strchr(stc_line, '\n')) // cas \n
	{
		
		// *temp = ft_substr(*temp, 0, ft_strlen(ft_strchr(*temp, '\n')));
		// ft_strjoin(stc_line, *temp);
		// free(*temp);
		(void)temp;
		printf("%s",stc_line);
		return (1);
	}
	else if (ft_strchr(stc_line, '\0')) // cas EOF 
	{
		// ft_strjoin(stc_line, *temp);
		// free(*temp);
		return (0);
		printf("%s",stc_line);
	}
	else
		return (-1);
}

int	get_next_line(int fd, char **line) // WIP
{
	static char		*stc_line = NULL;
	char			*temp;
	ssize_t			reader;
	size_t i;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0) // OK
		return (-1);
	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)); // OK
	if (!temp)
		return (-1); // protection OK
	while (!ft_strchr(stc_line, '\n') 
		&& (reader = read(fd, temp, BUFFER_SIZE) > 0)) // good : check if \n or EOF
	{
		if (reader < 0) // if couille free et return -1
		{
			free(temp);
			return (-1);
		}
		temp[reader] = '\0'; //finishing the temp by \0;
		// printf("%s\n", temp); // to suppress after
		if (!stc_line)
			stc_line = ft_strjoin("", temp);
		else
			stc_line = ft_strjoin(stc_line, temp);
		if (!stc_line)
			return (-1);
		printf("%s", stc_line); // to suppress after
		// change *line;
		i = 0;
	}
	return (ft_gnl_output(&temp, stc_line));
}

int		main(void)
{
	char	*line;
	int		nb_line;
	int		fd;
	char	*url;

	url = "baudelaire.txt";
	// int		fd2;
	// int		fd3;

	nb_line = 1;
	if ((fd = open(url, O_RDONLY)) == -1)
		printf("le fichier n'existe pas.");
	// if ((fd2 = open(av[2], O_RDONLY)) == -1)
	// 	printf("le fichier n'existe pas.");
	// if ((fd3 = open(av[3], O_RDONLY)) == -1)
	// 	printf("le fichier n'existe pas.");
	line = NULL;
	int ret = 0;
	while ((ret = get_next_line(fd, &line)) > 0 && nb_line)
	{
		printf("line[%d]: %s\n", nb_line, line);
		// free(line);
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
	// free(line);
	// line = NULL;
	// ret = get_next_line(fd2, &line);
	// printf("line[%d]: %s\n", nb_line, line);
	// free(line);
	// line = NULL;
	// ret = get_next_line(fd3, &line);
	// printf("line[%d]: %s\n", nb_line, line);
	// free(line);
	// system("leaks a.out");
}
