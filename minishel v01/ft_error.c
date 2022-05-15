/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskeleto <mskeleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 19:25:59 by mskeleto          #+#    #+#             */
/*   Updated: 2021/10/27 09:34:19 by mskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(char *str1, char *str2, char *str3)
{
	write(2, "minishell: ", 11);
	if (str1 != NULL)
		write(2, str1, ft_strlen(str1));
	if (str2 != NULL)
	{
		write(2, str2, ft_strlen(str2));
		write(2, ": ", 2);
	}
	write(2, str3, ft_strlen(str3));
	write(2, "\n", 1);
	return (1);
}

int	ft_last_len(char *str)
{
	if (str == NULL)
		return (0);
	return (ft_strlen(str));
}

int	ft_free_tmp(char **tmp)
{
	int	i;

	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
	return (0);
}

int	ft_fd_error(char *filename)
{
	DIR	*dir;

	dir = opendir(filename);
	if (dir == NULL)
		ft_error(NULL, filename, "No such file or directory");
	else
	{
		ft_error(NULL, filename, "Is a directory");
		closedir(dir);
	}
	return (-1);
}

void	ft_free_all(t_command_line *all)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= all->num_pipes)
	{
		if (all->num_pipes > 0 && i < all->num_pipes)
		{
			close(all->pipes_fd[i][0]);
			free(all->pipes_fd[i]);
		}
		j = -1;
		while (all->block[i].redirects[++j].type != 0)
			free(all->block[i].redirects[j].file);
		free(all->block[i].redirects);
		j = -1;
		while (all->block[i].narg[++j] != NULL)
			free(all->block[i].narg[j]);
		free(all->block[i].narg);
	}
	free(all->block);
	if (all->pipes_fd > 0)
		free(all->pipes_fd);
}
