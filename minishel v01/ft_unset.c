/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 02:52:15 by mskeleto          #+#    #+#             */
/*   Updated: 2021/10/27 17:48:02 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_command_line *all, t_command_block *block)
{
	int	i;

	i = 0;
	while (block->narg[++i])
		ft_delete(ft_strjoin(block->narg[i], "="), all,
			ft_strlen(block->narg[i]) + 2, block->narg[i]);
	return (0);
}

int	ft_delete(char *var, t_command_line *all, int cmp, char *var1)
{
	t_env_list	*delta;
	t_env_list	*tmp;

	if (!ft_strncmp(var, all->env->key, cmp)
		|| !ft_strncmp(var1, all->env->key, cmp - 1))
		return (ft_del1(all));
	tmp = all->env;
	while (tmp->next != NULL)
	{
		if (!ft_strncmp(var, tmp->next->key, cmp)
			|| !ft_strncmp(var1, tmp->next->key, cmp - 1))
		{
			delta = tmp->next;
			tmp->next = tmp->next->next;
			free(delta->key);
			if (delta->value)
				free(delta->value);
			free(delta);
			return (0);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

int	ft_del1(t_command_line *all)
{
	t_env_list	*tmp;

	tmp = all->env;
	all->env = all->env->next;
	free(tmp->key);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
	return (0);
}

void	ft_update_shlvl(char **envp)
{
	int		i;
	int		level;
	char	*shl;
	char	*tmp;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "SHLVL=", 6))
		{
			level = ft_atoi(envp[i] + 6) + 1;
			shl = ft_itoa(level);
			tmp = envp[i];
			envp[i] = ft_strjoin("SHLVL=", shl);
			free(shl);
			free(tmp);
		}
	}
}
