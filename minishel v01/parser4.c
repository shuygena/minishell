/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskeleto <mskeleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 20:45:25 by mskeleto          #+#    #+#             */
/*   Updated: 2021/10/26 23:55:29 by mskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_start_count_args(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 2;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	if (s[i])
		count += ft_count_args(s + i, 0);
	return (count);
}

int	ft_skip_spaces(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\t'))
		i++;
	return (i);
}

int	ft_skip_redirs(char *s, int *count)
{
	int	i;

	i = 0;
	if (s[i + 1] == '<' || s[i + 1] == '>')
		i++;
	i++;
	while (s[i] && s[i] != ' ' && s[i] != '>' && s[i] != '<' && s[i] != '\t')
	{
		i++;
		while (s[i] && (s[i] == '\'' || s[i] == '\"'))
		{
			i += ft_iterations(s + i + 1, s[i]);
			if (s[i] == '\'' || s[i] == '\"')
				i++;
		}
	}
	if (s[i] == '>' || s[i] == '<')
		count[0] += 1;
	if (s[i] != '\0' && s[i] != ' ' && s[i] != '>' && s[i] != '<'
		&& s[i] != '\t')
		i++;
	return (i);
}

int	ft_count_args(char *s, int i)
{
	int	count;

	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != ' '
			&& s[i] != '>' && s[i] != '<' && s[i] != '\t')
			i++;
		if (s[i] == ' ' || s[i] == '\t')
		{
			i += ft_skip_spaces(s + i);
			count += (s[i] != '\0');
		}
		else if ((s[i] == '<' || s[i] == '>') && s[i])
			i += ft_skip_redirs(s + i, &count);
		else if ((s[i] == '\'' || s[i] == '\"') && s[i])
		{
			i += ft_iterations(s + 1 + i, s[i]);
			i += (s[i] != '\0');
		}
	}
	return (count);
}
