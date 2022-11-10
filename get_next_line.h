/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjulienn <cjulienn@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 13:28:47 by cjulienn          #+#    #+#             */
/*   Updated: 2021/08/05 13:43:49 by cjulienn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef	BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*manage_errors(int fd);
char	*ft_output(ssize_t reader, char	**line, int iter);
char	*ft_cut_rtn(const char *line);
char	*ft_cut_line(ssize_t reader, char *line);
char	*ft_strjoin_and_free(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_protec_strdup(const char *str);
char	*ft_free_and_return(char **buffer, char *rtn_value);
size_t	ft_strlen(const char *str);

#endif
