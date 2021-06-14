/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:50:51 by cjulienn          #+#    #+#             */
/*   Updated: 2021/05/21 13:51:18 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// complete file : 5 fonctions including strjoin, strdup, 
// strlen, substr et strchr

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
	d = (char)c;
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

char	*ft_strdup(const char *str)
{
	char				*copy;
	unsigned long		sizer;
	int					i;

	sizer = ft_strlen(str) + 1;
	copy = malloc(sizer * (sizeof(char)));
	if (!(copy))
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
