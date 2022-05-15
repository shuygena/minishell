/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskeleto <mskeleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 18:12:03 by mskeleto          #+#    #+#             */
/*   Updated: 2021/10/26 22:45:08 by mskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_export(char *str)
{
	int		error;
	int		fd;
	DIR		*dir;
	char	**path;

	path = ft_split(str, '=');
	error = 0;
	fd = open(path[0], O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		error = 1;
	}
	dir = opendir(path[0]);
	if (dir != NULL)
	{
		closedir(dir);
		error = 1;
	}
	if (ft_add_export(str) != 0)
		error = 1;
	return (error);
}

char	**ft_vk(char *str)
{
	char	**vk;
	int		i;
	char	*tmpstr;

	i = 0;
	vk = (char **)malloc(2 * (sizeof(char *)));
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	vk[0] = ft_substr(str, 0, i);
	if (vk[0][i - 2] == '+')
	{
		tmpstr = ft_substr(str, 0, i - 2);
		free(vk[0]);
		vk[0] = ft_strjoin(tmpstr, "=");
		free(tmpstr);
	}
	vk[1] = ft_strdup(str + i);
	return (vk);
}

void	ft_append_env(t_command_line *all, char *str)
{
	t_env_list	*new;
	t_env_list	*tmp;
	char		**vk;

	new = (t_env_list *)malloc(sizeof(t_env_list));
	vk = ft_vk(str);
	new->key = vk[0];
	new->value = vk[1];
	new->next = NULL;
	tmp = all->env;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

char	*ft_export_val(char *str)
{
	char	*new;
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=' && str[i] != '+')
		i++;
	new = (char *)malloc(i + 1);
	i = 0;
	while (str[i] != '\0' && str[i] != '=' && str[i] != '+')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_export(t_command_line *all, t_command_block *block)
{
	t_env_list	*tmp;
	int			i;
	char		*str2;

	i = 0;
	all->error = 0;
	while (block->narg[++i] != NULL)
	{
		str2 = ft_export_val(block->narg[i]);
		tmp = ft_find_export(all, str2);
		if (ft_check_export(block->narg[i]) == 1)
			ft_navi(all, block->narg[i]);
		else if (tmp == NULL)
			ft_append_env(all, block->narg[i]);
		else if (ft_find_sym(block->narg[i], '=') != 0)
			ft_change_env(tmp, block->narg[i]);
		free(str2);
	}
	if (block->narg[1] == NULL)
		ft_export_print(all->env);
	return (all->error);
}
