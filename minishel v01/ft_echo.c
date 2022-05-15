/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 02:26:14 by mskeleto          #+#    #+#             */
/*   Updated: 2021/10/27 20:44:01 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_command_block *block)
{
	int	flag;
	int	i;

	i = 1;
	flag = 0;
	if (block->narg[i] == NULL)
		ft_putstr_fd("\n", 1);
	else
	{
		while (block->narg[i] && ft_strncmp(block->narg[i], "-n", 3) == 0)
			flag = i++;
		while (block->narg[i] != NULL)
		{
			if (block->narg[i] != NULL)
				ft_putstr_fd(block->narg[i], 1);
			if (block->narg[i + 1] != NULL)
				ft_putstr_fd(" ", 1);
			i++;
		}
		if (flag == 0)
			ft_putstr_fd("\n", 1);
	}
	exit(0);
}
