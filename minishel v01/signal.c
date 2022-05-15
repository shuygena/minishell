/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 07:21:00 by tacarlen          #+#    #+#             */
/*   Updated: 2021/10/27 18:29:50 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#	define MINISHELL "minishell$ "

void	sig(int signum)
{
	char	*str;
	pid_t	pid;

	if (signum == 2)
	{
		str = ft_strdup(rl_line_buffer);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		write(1, str, ft_strlen(str));
		write(1, "  \b\b\n", 5);
		write(1, MINISHELL, ft_strlen(MINISHELL));
	}
	else if (signum == 3)
	{
		pid = waitpid(-1, 0, 0);
		if (pid > 0)
		{
			rl_replace_line("", 0);
			rl_redisplay();
			write(2, "Quit: 3\n", 8);
		}
	}
}
