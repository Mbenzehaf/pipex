/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 21:02:55 by mben-zeh          #+#    #+#             */
/*   Updated: 2022/11/08 04:54:19 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "pipex.h"

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
//int		ft_strlen(const char *str);
int		ft_strlen_n(const char *str, char c);
char	*ft_strdup(const char *s1);
int		ft_strfind(const char *s);
#endif
