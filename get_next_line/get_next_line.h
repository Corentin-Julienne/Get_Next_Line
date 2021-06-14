/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:50:58 by cjulienn          #+#    #+#             */
/*   Updated: 2021/06/14 11:34:26 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 2
#endif

# include <stdlib.h>
# include <unistd.h>
// # include "wraloc.h" // testing purpose

int		get_next_line(int fd, char **line);
int		ft_gnl_output(char *stc_line, char **line);
void	ft_free_and_clean(char **temp, char **stc_line);
char	*ft_trim_bfr_ln(const char *stc_line);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);

#endif