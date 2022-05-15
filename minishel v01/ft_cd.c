/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskeleto <mskeleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:13:53 by mskeleto          #+#    #+#             */
/*   Updated: 2021/10/25 18:43:59 by mskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_minus(t_command_line *all, t_env_list *old)
{
	int		res;
	int		fd;
	char	*str;

	if (old == NULL)
		return (ft_error("cd: ", NULL, "OLDPWD not set"));
	str = ft_strdup(old->value);
	ft_oldpwd(all);
	res = chdir(str);
	if (res == -1)
	{
		fd = open(old->value, O_RDONLY);
		if (fd == -1)
			ft_error("cd: ", old->value, "No such file or directory");
		else
		{
			ft_error("cd: ", old->value, "Not a directory");
			close(fd);
		}
		free(str);
		return (1);
	}
	free(str);
	ft_change_pwd(all);
	return (0);
}

t_env_list	*ft_find_env(t_command_line *all, char *str)
{
	t_env_list	*tmp;

	tmp = all->env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, str, ft_strlen(str) + 1) == 0)
			return (tmp);
		else
			tmp = tmp->next;
	}
	return (NULL);
}

int	ft_home(t_command_line *all, t_env_list *home)
{
	int	res;
	int	fd;

	if (home == NULL)
	{
		ft_error("cd: ", NULL, "HOME not set");
		return (1);
	}
	res = chdir(home->value);
	if (res == -1)
	{
		fd = open(home->value, O_RDONLY);
		if (fd == -1)
			ft_error("cd: ", home->value, "No such file or directory");
		else
		{
			close(fd);
			ft_error("cd: ", home->value, "Not a directory");
		}
		return (1);
	}
	ft_change_pwd(all);
	return (0);
}

int	ft_oldpwd(t_command_line *all)
{
	t_env_list	*tmp;
	char		*path;

	tmp = ft_find_env(all, "OLDPWD=");
	if (tmp != NULL)
	{
		path = (char *)malloc(1025);
		path = getcwd(path, 1024);
		if (tmp->value != NULL)
			free(tmp->value);
		tmp->value = ft_copy(path);
		free(path);
	}
	return (0);
}

int	ft_cd(t_command_line *all, t_command_block *block)
{
	if (ft_strncmp(block->narg[1], "-", 2) == 0)
		return (ft_minus(all, ft_find_env(all, "OLDPWD=")));
	ft_oldpwd(all);
	if (block->narg[1] == NULL || (ft_strncmp(block->narg[1], "--", 3) == 0))
		return (ft_home(all, ft_find_env(all, "HOME=")));
	else if (!(ft_strncmp(block->narg[1], "~", 2)))
		chdir(all->home);
	else
		ft_change_dir(all, block->narg[1]);
	ft_change_pwd(all);
	return (0);
}
