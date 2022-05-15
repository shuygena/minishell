/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskeleto <mskeleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 21:38:12 by tacarlen          #+#    #+#             */
/*   Updated: 2021/10/27 11:03:51 by mskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#	define ERROR_PIPE "syntax error near unexpected token `|'"
#	define ERROR_POINT "syntax error near unexpected token `;'"
#	define SYN_ERR "syntax error\n"
#	define SYN_RED1 "syntax error near unexpected token `<'"
#	define SYN_RED2 "syntax error near unexpected token `newline'"
#	define SYN_RED3 "syntax error near unexpected token `>'"
#	define SYNTAX "syntax error: open quote"

int	ft_quote_check_for_close(char *line)
{
	char	c;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{	
			if (line[i + 1] == '\0')
				return (ft_error(NULL, NULL, SYNTAX));
			c = line[i];
			i++;
			while (line[i] && line[i] != c)
				i++;
			if (line[i] != c)
				return (ft_error(NULL, NULL, SYNTAX));
		}
		if (line[i])
			i++;
	}
	return (0);
}

int	ft_redir(char *line, int *i)
{
	(*i)++;
	if (line[(*i) - 1] == '>' && line[*i] == '<')
		return (ft_error (NULL, NULL, SYN_RED1));
	else if ((line[(*i - 1)] == '<' && line[*i] == '>'))
		return (ft_error (NULL, NULL, SYN_RED2));
	else if (line[(*i) - 1] == line[*i])
	{
		(*i)++;
		while (line[*i] == ' ')
			(*i)++;
		if (line[*i] == '\0')
			return (ft_error (NULL, NULL, SYN_RED2));
		else if (line[*i] == '>')
			return (ft_error (NULL, NULL, SYN_RED3));
		else if (line[*i] == '<')
			return (ft_error (NULL, NULL, SYN_RED1));
	}
	return (0);
}

int	ft_check_quote(char *line, char sym, int i)
{
	while (line[++i])
	{
		if (line[i] == sym)
			return (0);
	}
	return (-1);
}

int	ft_preparser2(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[ft_strlen(line) - 1] == '|')
			return (ft_error (NULL, NULL, ERROR_PIPE));
		if (line[i] == '>' || line[i] == '<')
			return (ft_redir(line, &i));
		else
			i++;
	}
	if (ft_quote_check_for_close(line) == 1)
		return (1);
	i = -1;
	while (line[++i])
		count += (line[i] != ' ' && line[i] != '\t');
	if (count == 0)
		return (1);
	return (0);
}

char	*ft_preparser(char *line)
{
	int	i;

	i = 0;
	while (ft_isalnum(line[i]) != 1 && line[i] != '\''
		&& line[i] != '\"' && line[i] != '>' && line[i] != '<'
		&& line[i])
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '|')
		{
			ft_error (NULL, NULL, ERROR_PIPE);
			return (NULL);
		}
		if (line[i] == ';')
		{
			ft_error (NULL, NULL, ERROR_POINT);
			return (NULL);
		}
		i++;
	}
	if (ft_preparser2(line) == 1)
		return (NULL);
	return (line);
}
