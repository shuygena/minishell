/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:13:03 by tacarlen          #+#    #+#             */
/*   Updated: 2021/10/27 15:14:04 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#	define MINISHELL "minishell$ "

void	ft_party(t_command_line *all, char *line)
{
	add_history(line);
	line = ft_preparser(line);
	if (line)
	{
		ft_parser(line, all);
		all->error = ft_minishell(all);
		ft_free_unlink(all);
		ft_free_all(all);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_command_line	all;
	char			*line;

	signal(SIGINT, sig);
	signal(SIGQUIT, SIG_IGN);
	if (argc != 1 && argv == NULL)
		return (0);
	all.error = 0;
	all.path = ft_split_path(envp);
	ft_parse_envp(&all, envp);
	all.mystery = 0;
	ft_parse_env(&all, all.envp);
	line = readline(MINISHELL);
	if (!line)
		write(1, "exit\n", 5);
	while (line)
	{
		ft_party(&all, line);
		line = readline(MINISHELL);
		if (!line)
			write(1, "exit\n", 5);
	}
}
