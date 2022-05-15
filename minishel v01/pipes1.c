/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/21 22:01:47 by mskeleto          #+#    #+#             */
/*   Updated: 2021/10/27 15:17:05 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_start_fork(t_command_line *all)
{
	int	i;
	int	status;
	int	*buf_pid;

	i = -1;
	buf_pid = (int *)malloc(sizeof(int) * (all->num_pipes + 1));
	signal(SIGQUIT, sig);
	while (++i <= all->num_pipes)
	{
		buf_pid[i] = fork();
		if (buf_pid[i] < 0)
			return (-1);
		else if (buf_pid[i] == 0)
		{
			if (ft_command_block(all, i) == -1)
				exit(all->error);
		}
		else if (buf_pid[i] > 0 && i != all->num_pipes)
			close(all->pipes_fd[i][1]);
	}
	i = -1;
	while (++i <= all->num_pipes)
		waitpid(buf_pid[i], &status, 0);
	all->error = status;
	return (ft_free_buf(all->error, buf_pid));
}

int	ft_command_block(t_command_line *all, int index)
{
	if (all->num_pipes > 0)
	{
		ft_close_pipe_fds(all, index);
		ft_dup_or_close_pipes(all, index);
	}
	if (ft_create_redir_files(&(all->block[index])) == -1)
		exit(1);
	if (all->block[index].close_fd1 != 0)
		dup2(all->block[index].close_fd1, 0);
	if (all->block[index].close_fd2 != 0)
		dup2(all->block[index].close_fd2, 1);
	if (all->num_pipes == 0 && ((!ft_strncmp(all->block->narg[0], "exit", 5))
			|| (!ft_strncmp(all->block->narg[0], "export", 5))
			|| (!ft_strncmp(all->block->narg[0], "cd", 5))
			|| (!ft_strncmp(all->block->narg[0], "unset", 5))))
		return (ft_one_time_cmd(all, &all->block[index]));
	ft_make_command(all, &all->block[index]);
	return (-1);
}

int	ft_make_command(t_command_line *all, t_command_block *block)
{
	if (!ft_strncmp(block->narg[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(block->narg[0], "echo", 5))
		ft_echo(block);
	else if (!ft_strncmp(block->narg[0], "cd", 3))
		exit(ft_cd(all, block));
	else if (!ft_strncmp(block->narg[0], "export", 7))
		exit(ft_export(all, block));
	else if (!ft_strncmp(block->narg[0], "unset", 6))
		exit(ft_unset(all, block));
	else if (!ft_strncmp(block->narg[0], "env", 4))
		ft_env(all, block);
	else if (!ft_strncmp(block->narg[0], "exit", 5))
		ft_exit(all, block);
	else
		ft_exec(all->path, block->narg, all->envp, all);
	return (0);
}

void	ft_dup_or_close_pipes(t_command_line *all, int index)
{
	if (index == 0)
	{
		if (all->block[index].last_right_redir != NULL)
			close(all->pipes_fd[index][1]);
		else
			dup2(all->pipes_fd[index][1], 1);
	}
	else if (index == all->num_pipes)
	{
		if (all->block[index].last_left_redir != NULL)
			close(all->pipes_fd[index - 1][0]);
		else
			dup2(all->pipes_fd[index - 1][0], 0);
	}
	else
	{
		if (all->block[index].last_left_redir != NULL)
			close(all->pipes_fd[index - 1][0]);
		else
			dup2(all->pipes_fd[index - 1][0], 0);
		if (all->block[index].last_right_redir != NULL)
			close(all->pipes_fd[index][1]);
		else
			dup2(all->pipes_fd[index][1], 1);
	}
}

void	ft_close_pipe_fds(t_command_line *all, int index)
{
	int	i;

	i = 0;
	while (i < all->num_pipes)
	{
		if (i == index)
			close(all->pipes_fd[i][0]);
		if (i == index - 1)
			close(all->pipes_fd[i][1]);
		if (i != index && i != index - 1)
		{
			close(all->pipes_fd[i][0]);
			close(all->pipes_fd[i][1]);
		}
		i++;
	}
}
