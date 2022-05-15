/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:11:48 by mskeleto          #+#    #+#             */
/*   Updated: 2021/10/27 17:01:32 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_env(t_command_line *all, char **envp)
{
	int			i;
	t_env_list	*tmp;
	t_env_list	*tmp2;

	i = 0;
	all->env = (t_env_list *)malloc(sizeof(t_env_list));
	all->env->value = ft_strdup((const char *)(ft_strchr(envp[i], '=') + 1));
	all->env->key = ft_substr((const char *)envp[i], 0, ft_strlen(envp[i])
			- ft_strlen(all->env->value));
	tmp = all->env;
	while (envp[++i] != NULL)
	{
		tmp2 = (t_env_list *)malloc(sizeof(t_env_list));
		tmp2->value = ft_strdup((const char *)(ft_strchr(envp[i], '=') + 1));
		tmp2->key = ft_substr((const char *)envp[i], 0, ft_strlen(envp[i])
				- ft_strlen(tmp2->value));
		if (ft_strncmp(tmp2->key, "HOME=", 6) == 0)
			all->home = ft_strdup(tmp2->value);
		tmp->next = tmp2;
		tmp = tmp->next;
	}
	tmp->next = NULL;
}

void	ft_parse_envp(t_command_line *all, char **en)
{
	int	i;

	i = -1;
	all->envp = (char **)malloc(sizeof(char *) * (ft_count_str(en) + 1));
	while (en[++i])
		all->envp[i] = ft_strdup(en[i]);
	all->envp[i] = NULL;
	ft_update_shlvl(all->envp);
}

char	**ft_split_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("PATH", envp[i], 4) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

int	ft_count_str(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		i++;
	return (i);
}

void	ft_pro_redirs(t_command_line *all, int index)
{
	char	*filename;
	int		j;

	j = -1;
	ft_creat_redirects(all, index);
	while (all->block[index].redirects[++j].type != 0)
	{
		if (all->block[index].redirects[j].type == 1
			|| all->block[index].redirects[j].type == 3)
			filename = ft_strdup(all->block[index].redirects[j].file + 1);
		else
			filename = ft_strdup(all->block[index].redirects[j].file + 2);
		all->block[index].redirects[j].file = filename;
		if (all->block[index].redirects[j].type == 2
			|| all->block[index].redirects[j].type == 1)
			all->block[index].last_left_redir = filename;
		else
			all->block[index].last_right_redir = filename;
	}
}
