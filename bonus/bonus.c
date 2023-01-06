/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 20:31:56 by mben-zeh          #+#    #+#             */
/*   Updated: 2022/12/29 15:19:49 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	ft_exec(t_cmd *cmd_st, int in, int out, char *cmd)
{
	if (dup2(in, STDIN_FILENO) < 0)
		exit(1);
	dup2(out, STDOUT_FILENO);
	ft_exec_cmd(cmd_st, cmd);
}

void	ft_child_process(t_cmd *cmd_st, int i, char **av, int ac)
{
	cmd_st->childs[i] = fork();
	if (cmd_st->childs[i] == 0)
	{
		if (i == 0)
		{
			close(cmd_st->fd[i][0]);
			ft_exec(cmd_st, cmd_st->infile, cmd_st->fd[i][1], av[2]);
		}
		else if (i == ac - 4)
		{
			cmd_st->outfile = open(av[ac - 1], cmd_st->mode, 0644);
			if (cmd_st->outfile < 0)
				ft_msg_error(av[ac - 1]);
			close(cmd_st->fd[i - 1][1]);
			ft_exec(cmd_st, cmd_st->fd[i - 1][0], cmd_st->outfile, av[i + 2]);
		}
		else
		{
			close(cmd_st->fd[i - 1][1]);
			close(cmd_st->fd[i][0]);
			ft_exec(cmd_st, cmd_st->fd[i - 1][0], cmd_st->fd[i][1], av[i + 2]);
		}
	}
}

void	pipex(t_cmd *cmd_st, int ac, char **av)
{
	int	i;

	i = 0;
	cmd_st->fd = (int **)malloc((ac - 4) * sizeof(int *));
	cmd_st->childs = (int *)malloc((ac - 3) * sizeof(int));
	if (! cmd_st->fd)
		exit(1);
	while (i <= ac - 4)
	{
		if (i != ac - 4)
		{
			cmd_st->fd[i] = malloc((2) * sizeof(int));
			if (pipe(cmd_st->fd[i]) < 0)
				ft_msg_error("pipe");
		}
		ft_child_process(cmd_st, i, av, ac);
		if (i != 0)
		{
			close(cmd_st->fd[i - 1][1]);
			close(cmd_st->fd[i - 1][0]);
			free(cmd_st->fd[i - 1]);
		}
		i++;
	}
	ft_status(cmd_st, ac - 4);
}

void	here_doc(char *limiter, t_cmd *cmd_st)
{
	char	*str;
	int		fd[2];
	int		lim;

	lim = ft_strlen(limiter);
	cmd_st->mode = _O_A_;
	if (pipe(fd) < 0)
		ft_msg_error("pipe");
	while (1)
	{
		ft_putstr_fd("> ", 1);
		str = get_next_line(0);
		if (!ft_strncmp(str, limiter, lim) && str[lim] == '\n')
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, fd[1]);
		free(str);
	}
	cmd_st->infile = fd[0];
	close(fd[1]);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	cmd_st;

	if (ac < 5)
		return (ft_putstr_fd ("usage: ./pipex file1 cmd cmd ... file2\n", 2), 1);
	cmd_st.env = envp;
	if (!ft_strncmp(av[1], "here_doc", 9))
	{
		if (ac == 6)
		{
			here_doc(av[2], &cmd_st);
			pipex(&cmd_st, ac - 1, av + 1);
		}
		ft_putstr_fd("usage: ./pipex here_doc LIMITER cmd cmd file", 2);
	}
	else
	{
		cmd_st.infile = open(av[1], O_RDONLY);
		if (cmd_st.infile < 0)
			perror(av[1]);
		cmd_st.mode = _O_T_;
		pipex(&cmd_st, ac, av);
	}
	return (1);
}
