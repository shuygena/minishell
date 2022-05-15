/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskeleto <mskeleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 00:48:37 by mskeleto          #+#    #+#             */
/*   Updated: 2021/10/26 22:18:46 by mskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_command_line *all, t_command_block *block)
{
	if (ft_find_export(all, "PATH") == NULL)
	{
		ft_error(NULL, "env", "No such file or directory");
		exit(127);
	}
	if (block->narg[1] == NULL)
		ft_print_env(all->env);
	else
		(ft_error(NULL, "env", "too many arguments"));
	exit(0);
}

void	ft_print_env(t_env_list *env)
{
	t_env_list	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->value != NULL && ft_find_sym(tmp->key, '=') != 0)
			printf("%s%s\n", tmp->key, tmp->value);
		else if (ft_find_sym(tmp->key, '=') != 0)
			printf("%s\n", tmp->key);
		tmp = tmp->next;
	}
}
