/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 22:51:16 by mskeleto          #+#    #+#             */
/*   Updated: 2021/10/27 20:42:51 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*ft_dup_env(t_env_list *env)
{
	t_env_list	*tmp;
	t_env_list	*new;
	t_env_list	*start;

	new = (t_env_list *)malloc(sizeof(t_env_list));
	tmp = env;
	start = new;
	while (tmp != NULL)
	{
		new->key = ft_strdup(tmp->key);
		new->value = ft_strdup(tmp->value);
		if (tmp->next != NULL)
		{
			new->next = (t_env_list *)malloc(sizeof(t_env_list));
			new = new->next;
		}
		tmp = tmp->next;
	}
	new = NULL;
	return (start);
}

void	ft_env_sort(t_env_list *env)
{
	t_env_list	*tmp;
	char		*k;
	char		*v;

	while (env->next != NULL)
	{
		tmp = env->next;
		while (tmp != NULL)
		{
			if (ft_strcmp(tmp->key, env->key) < 0)
			{
				k = tmp->key;
				v = tmp->value;
				tmp->key = env->key;
				tmp->value = env->value;
				env->value = v;
				env->key = k;
			}
			tmp = tmp->next;
		}
		env = env->next;
	}
}

void	ft_free_env(t_env_list *env)
{
	t_env_list	*tmp;

	while (env != NULL)
	{
		tmp = env;
		env = env->next;
		free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

int	ft_add_export(char *str)
{
	int	i;

	i = 0;
	if (str[0] >= '0' && str[0] <= '9')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if ((ft_isalnum(str[i]) == 0 && str[i] != '_')
			&& !(str[i] == '+' && str[i + 1] == '=' && str[0] != '+'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
