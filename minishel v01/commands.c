/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 20:17:49 by mskeleto          #+#    #+#             */
/*   Updated: 2022/05/15 20:18:02 by mskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#	define NOT_COMMAND "command not found"

void	ft_exec(char **path, char **narg, char **envp, t_command_line *all)
{
	int		i;
	char	*file;

	i = 0;
	if (narg[0][0] == '/' || narg[0][0] == '.')
		return (ft_just_do_it(narg, envp));
	if (ft_find_export(all, "PATH") == NULL)
	{
		ft_error(NULL, narg[0], "No such file or directory");
		exit(127);
	}
	file = ft_strcat(path[i], narg[0]);
	while (path[i + 1] && (execve(file, narg, envp) == -1))
	{
		free(file);
		i++;
		file = ft_strcat(path[i], narg[0]);
	}
	ft_error(NULL, narg[0], NOT_COMMAND);
	exit(127);
}

void	ft_just_do_it(char **narg, char **envp)
{
	execve(narg[0], narg, envp);
	ft_error(NULL, narg[0], NOT_COMMAND);
	exit(127);
}

int	ft_one_time_cmd(t_command_line *all, t_command_block *block)
{
	if (!ft_strncmp(all->block->narg[0], "exit", 5))
		all->error = ft_exit(all, block);
	if (!ft_strncmp(all->block->narg[0], "cd", 3))
		all->error = ft_cd(all, block);
	if (!ft_strncmp(all->block->narg[0], "unset", 6))
		all->error = ft_unset(all, block);
	if (!ft_strncmp(all->block->narg[0], "export", 7))
		all->error = ft_export(all, block);
	return (all->error);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_str = (char *)malloc(ft_strlen(dest) + ft_strlen(src) + 2);
	while (dest != NULL && (dest[j] != '\0'))
	{
		new_str[j] = dest[j];
		j++;
	}
	new_str[j] = '/';
	j++;
	while (src != NULL && src[i] != '\0')
	{
		new_str[j] = src[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	ft_minishell(t_command_line *all)
{
	if (all->num_pipes == 0 && ((!ft_strncmp(all->block->narg[0], "exit", 5))
			|| (!ft_strncmp(all->block->narg[0], "export", 5))
			|| (!ft_strncmp(all->block->narg[0], "cd", 5))
			|| (!ft_strncmp(all->block->narg[0], "unset", 5))))
		return (ft_command_block(all, 0));
	else
		return (ft_start_fork(all));
	return (0);
}
