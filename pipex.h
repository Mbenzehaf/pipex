/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 10:18:40 by mben-zeh          #+#    #+#             */
/*   Updated: 2022/12/29 16:32:14 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define _O_A_ 0x0209
# define _O_T_ 0x0601
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_cmd
{
	int		infile;
	int		outfile;
	pid_t	child[2];
	char	*cmd;
	char	**arg;
	char	**path;
	int		status;
	int		**fds;
	char	**env;
	int		mode;
}			t_cmd;
void		ft_status(t_cmd *cmd_st, int n);
char		*ft_envchr(char **envp, char *str);
int			ft_path_envp(t_cmd *cmd_st, char **envp);
void		ft_msg_error(char *file);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *str, const char *to_find, size_t len);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *s1);
void		ft_exec_cmd(t_cmd *cmd_st, char *cmd);
void		ft_putstr_fd(char *s, int fd);
#endif
