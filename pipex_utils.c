/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 10:16:08 by mben-zeh          #+#    #+#             */
/*   Updated: 2022/12/29 00:40:17 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_msg_cmd_error(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Command not found\n", 2);
}

char	*ft_envchr(char **envp, char *str)
{
	int	i;

	i = 0;
	if (!envp || !str)
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], str, 5))
		{
			return (envp[i]);
		}
		i++;
	}
	return (NULL);
}

int	ft_path_envp(t_cmd *cmd_st, char **envp)
{
	char	*env;
	int		i;

	i = 0;
	env = ft_envchr(envp, "PATH=");
	if (!env)
		return (0);
	env = ft_substr(&env[5], 0, ft_strlen(&(env[5])));
	cmd_st->path = ft_split(env, ':');
	while (cmd_st->path[i])
	{
		cmd_st->path[i] = ft_strjoin(cmd_st->path[i], "/");
		i++;
	}
	free(env);
	return (1);
}

void	ft_exec_cmd(t_cmd *cmd_st, char *cmd)
{
	int		i;
	char	**arg;
	char	*path;

	i = 0;
	arg = ft_split(cmd, ' ');
	if (arg)
	{
		if (execve(arg[0], arg, cmd_st->env) < 0)
		{
			if (!ft_path_envp(cmd_st, cmd_st->env))
			{
				ft_msg_cmd_error(cmd);
				exit(127);
			}
			while (cmd_st->path[i])
			{
				path = ft_strjoin(ft_strdup(cmd_st->path[i++]), arg[0]);
				execve(path, arg, cmd_st->env);
				free(path);
			}
		}
	}
	ft_msg_cmd_error(arg[0]);
	exit(127);
}
