/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskeleto <mskeleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 23:24:18 by mskeleto          #+#    #+#             */
/*   Updated: 2021/10/26 22:35:15 by mskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_command_line *all, t_command_block *block)
{
	printf("exit\n");
	if (block->narg[1] == NULL)
		ft_exit0(all);
	if (ft_digit(block->narg[1]) == 0)
	{
		if (block->narg[2])
		{
			ft_error("exit: ", NULL, "too many arguments");
			return (1);
		}
		all->error = ft_exit_status(block->narg[1]);
		exit (all->error);
	}
	else
	{
		ft_error("exit: ", block->narg[1], "numeric argument required");
		all->error = 255;
		exit(all->error);
	}
	return (0);
}

void	ft_exit0(t_command_line *all)
{
	all->error = 0;
	exit(all->error);
}

int	ft_exit_status(char *str)
{
	int	x;

	x = ft_atoi(str);
	if (x >= 0)
		return (x % 256);
	else
		return (256 - ((x * -1) % 256));
}

int	ft_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || (str[i] >= '0' && str[i] <= '9'))
		i++;
	else
		return (-1);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	return (0);
}
