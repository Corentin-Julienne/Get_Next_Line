/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:50:55 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/17 18:21:31 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static int	ft_ln_checker(char *stc_line, char *temp, int fd) // check le num de lignes
{
	// TODO
}

static int	ft_gnl_output(int fd, char **temp, char *stc_line, ssize_t reader)
{	
	if (ft_strchr(stc_line, '\n')) // cas \n
	{
		
		temp = ft_subtr(temp, 0, ft_strlen(ft_strchr(temp, '\n')));
		ft_strjoin(stc_line, temp);
		free(temp);
		return (1);
	}
	else if (ft_strchr(stc_line, '\0')) // cas EOF 
	{
		ft_strjoin(stc_line, temp);
		free(temp);
		return (0);
	}
}

int	get_next_line(int fd, char **line) // WIP
{
	static char	*stc_line;
	char		*temp;
	ssize_t		reader;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0) // OK
		return (-1);
	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (-1); // changer en NULL si place dans autre fonction
	while (!ft_strchr(stc_line, '\n') || !ft_strchr(stc_line, '\0'))
	{
		reader = read(fd, temp, BUFFER_SIZE);
		if (reader < 0)
		{
			free(temp);
			return (-1);
		}
		if (!stc_line)
			stc_line = ft_strjoin("", temp);
		else
			stc_line = ft_strjoin(stc_line, temp);
		if (!stc_line)
			return (-1);
	}
	return (ft_gnl_ouput(fd, &temp, stc_line, reader));
}

// main de test

int main(void)
{
	return 0;
}