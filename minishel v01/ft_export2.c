/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskeleto <mskeleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:46:17 by mskeleto          #+#    #+#             */
/*   Updated: 2021/10/27 09:53:33 by mskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_sym(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

t_env_list	*ft_find_export(t_command_line *all, char *str)
{
	t_env_list	*tmp;

	tmp = all->env;
	while (tmp != NULL)
	{
		if (!ft_strncmp(str, tmp->key, ft_strlen(str) + 1)
			&& ft_strlen(str) == ft_strlen(tmp->key))
			return (tmp);
		if ((ft_strncmp(str, tmp->key, ft_strlen(str))) == 0
			&& ft_strlen(tmp->key) - 1 == ft_strlen(str)
			&& ft_find_sym(tmp->key, '=') == 1)
			return (tmp);
		if ((ft_strncmp(str, tmp->key, ft_strlen(tmp->key))) == 0
			&& ft_strlen(tmp->key) == ft_strlen(str) - 1
			&& ft_find_sym(str, '=') == 1)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_navi(t_command_line *all, char *str)
{
	char	*new;

	new = ft_strjoin(str, "'");
	ft_error("export: `", new, "not a valid identifier");
	free(new);
	all->error = 1;
}

void	ft_change_env(t_env_list *tmp, char *str)
{
	char	**vk;
	int		i;
	char	*tmpstr;

	i = 0;
	vk = ft_vk(str);
	free(tmp->key);
	tmp->key = vk[0];
	while (str[i] && str[i] != '=')
		i++;
	if (str[i - 1] == '+' && tmp->value != NULL)
	{
		tmpstr = tmp->value;
		tmp->value = ft_strjoin(tmpstr, vk[1]);
		free(tmpstr);
	}
	else if (tmp->value == NULL)
		tmp->value = vk[1];
	else
	{
		free(tmp->value);
		tmp->value = vk[1];
	}
}

void	ft_export_print(t_env_list *env)
{
	t_env_list	*tmp;

	tmp = ft_dup_env(env);
	ft_env_sort(tmp);
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, "_=", 3) != 0)
		{
			write(1, "declare -x ", 11);
			write(1, tmp->key, ft_strlen(tmp->key));
			if (ft_find_sym(tmp->key, '='))
				write(1, "\"", 1);
			if (tmp->value != NULL)
				write(1, tmp->value, ft_strlen(tmp->value));
			if (ft_find_sym(tmp->key, '='))
				write(1, "\"", 1);
			write(1, "\n", 1);
		}
		tmp = tmp->next;
	}
	ft_free_env(tmp);
}
