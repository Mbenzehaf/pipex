/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 10:15:16 by mben-zeh          #+#    #+#             */
/*   Updated: 2022/12/29 00:32:33 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	ft_child1_process(t_cmd *cmd_st, int *fd, char **av)
{
	cmd_st->infile = open(av[1], O_RDONLY);
	if (cmd_st->infile < 0)
	{
		perror(av[1]);
		exit(1);
	}
	close(fd[0]);
	dup2(cmd_st->infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	ft_exec_cmd(cmd_st, av[2]);
}

void	ft_child2_process(t_cmd *cmd_st, int *fd, char **av)
{
	cmd_st->outfile = open(av[4], _O_T_, 0644);
	if (cmd_st->outfile < 0)
	{
		perror(av[4]);
		exit(1);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	dup2(cmd_st->outfile, STDOUT_FILENO);
	ft_exec_cmd(cmd_st, av[3]);
}

void	pipex(t_cmd *cmd_st, char **av)
{
	int	fd[2];

	if (pipe(fd) < 0)
	{
		perror("pipe");
		exit(1);
	}
	cmd_st->child[0] = fork();
	if (cmd_st->child[0] < 0)
		perror("Fork: ");
	if (cmd_st->child[0] == 0)
		ft_child1_process(cmd_st, fd, av);
	cmd_st->child[1] = fork();
	if (cmd_st->child[1] < 0)
		perror("Fork: ");
	if (cmd_st->child[1] == 0)
		ft_child2_process(cmd_st, fd, av);
	close(fd[0]);
	close(fd[1]);
	waitpid(cmd_st->child[0], &cmd_st->status, 0);
	waitpid(cmd_st->child[1], &cmd_st->status, 0);
	exit(WEXITSTATUS(cmd_st->status));
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	cmd_st;

	if (ac == 5)
	{
		cmd_st.env = envp;
		pipex(&cmd_st, av);
	}
	else
	{
		ft_putstr_fd("usage: ./pipex [file1] [cmd1] [cmd2] [file2]\n", 2);
		exit(1);
	}
	return (0);
}
