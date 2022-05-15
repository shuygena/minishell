/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 18:58:41 by mskeleto          #+#    #+#             */
/*   Updated: 2021/10/27 20:40:03 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_create_redir_files(t_command_block *block)
{
	int	i;
	int	fd;
	int	l1;
	int	l2;

	i = 0;
	l1 = ft_last_len(block->last_left_redir) + 1;
	l2 = ft_last_len(block->last_right_redir) + 1;
	while (block->redirects[i].type != 0)
	{
		if (ft_strncmp(block->redirects[i].file, block->last_left_redir, l1)
			== 0
			|| ft_strncmp(block->redirects[i].file, block->last_right_redir, l2)
			== 0)
			fd = ft_last_redir(block->redirects[i], block->redirects[i].type,
					block);
		else
			fd = ft_open(block, i, block->redirects[i].file);
		if (fd == -1)
			return (ft_fd_error(block->redirects[i].file));
		if (fd != 0 && fd != block->close_fd1 && fd != block->close_fd2)
			close(fd);
		i++;
	}
	return (0);
}

int	ft_open(t_command_block *block, int i, char *file)
{
	DIR	*dir;
	int	fd;

	fd = 0;
	dir = opendir(file);
	if (dir != NULL && block->redirects[i].type != 2)
	{
		closedir(dir);
		return (-1);
	}
	if (block->redirects[i].type == 1)
		fd = open(file, O_RDONLY);
	else if (block->redirects[i].type == 3)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (block->redirects[i].type == 4)
		fd = open(file, O_RDWR | O_CREAT | 0777);
	else if (block->redirects[i].type == 2)
		return (0);
	return (fd);
}

int	ft_unlink(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		return (unlink(name));
	}
	return (0);
}

int	ft_redirect2(char *key, char *index)
{
	int		fd;
	int		cmp;
	char	*line;
	char	*name;

	cmp = ft_strlen(key) + 1;
	name = ft_strjoin(".tmp_", index);
	ft_unlink(name);
	fd = open(name, O_RDWR | O_CREAT, 0777);
	write(1, "> ", 2);
	get_next_line(0, &line);
	while (ft_strncmp(line, key, cmp) != 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		write(1, "> ", 3);
		get_next_line(0, &line);
	}
	free(line);
	return (fd);
}

int	ft_last_redir(t_redirect redirect, int type, t_command_block *block)
{
	DIR	*dir;
	int	fd;

	dir = opendir(redirect.file);
	if (dir != NULL && type != 2)
	{
		closedir(dir);
		return (-1);
	}
	if (type == 1)
		fd = open(redirect.file, O_RDONLY);
	else if (type == 3)
		fd = open(redirect.file, O_RDWR | O_CREAT | O_TRUNC, 0777);
	else if (type == 4)
		fd = open(redirect.file, O_RDWR | O_CREAT | O_APPEND, 0777);
	else
		fd = open(redirect.file, O_RDONLY);
	if (type == 3 || type == 4)
		block->close_fd2 = fd;
	else
		block->close_fd1 = fd;
	if (fd == -1)
		return (-1);
	return (0);
}
