/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:33:09 by mben-zeh          #+#    #+#             */
/*   Updated: 2022/12/29 15:22:55 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_msg_cmd_error(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Command not found\n", 2);
}

void	ft_msg_error(char *file)
{
	perror(file);
	exit(1);
}

void	ft_status(t_cmd *cmd_st, int n)
{
	int	i;

	i = 0;
	close(cmd_st->infile);
	close(cmd_st->outfile);
	while (i <= n)
	{
		waitpid(cmd_st->childs[i], &cmd_st->status, 0);
		i++;
	}
	free(cmd_st->fd);
	free(cmd_st->childs);
	exit(WEXITSTATUS(cmd_st->status));
}

int	ft_path_envp(t_cmd *cmd_st, char **envp)
{
	char	*env;
	int		i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			env = envp[i];
		i++;
	}
	i = 0;
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
