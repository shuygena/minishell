/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 17:17:50 by mskeleto          #+#    #+#             */
/*   Updated: 2021/10/27 20:46:31 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipes_count(char *line)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] && line[i] != '|' && line[i] != '\'' && line[i] != '\"')
			i++;
		c = line[i];
		count += (c == '|');
		if (c == '|')
			i++;
		if (c == '\'' || c == '\"')
		{
			i++;
			while (line[i] && line[i] != c)
				i++;
			if (line[i] == c)
				i++;
		}
	}
	return (count);
}

int	ft_iterations(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		i++;
	return (i);
}

int	ft_find_end_block(char *line, int index)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] && line[i] != '|' && line[i] != '\'' && line[i] != '\"')
			i++;
		c = line[i];
		count += (c == '|');
		if (count == index + 1)
			return (i);
		if (c == '|')
			i++;
		if (c == '\'' || c == '\"')
		{
			i += ft_iterations(line + i + 1, c);
			if (line[i] == c)
				i++;
		}
	}
	return (i);
}

char	**ft_split_line(char *line, t_command_line *all)
{
	char		**commands;
	t_vector	a;
	int			i;

	commands = (char **)malloc(sizeof(char *) * (all->num_pipes + 2));
	a.x2 = 0;
	i = 0;
	while (i <= all->num_pipes)
	{
		a.x1 = a.x2 + ((a.x2 != 0));
		a.x2 = ft_find_end_block(line, i);
		commands[i] = ft_substr(line, a.x1, a.x2 - a.x1);
		i++;
	}
	commands[i] = NULL;
	return (commands);
}

int	ft_crutch(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i] != NULL)
	{
		if (ft_check_for_ft_hand(tmp[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}
