/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 21:35:56 by tacarlen          #+#    #+#             */
/*   Updated: 2021/10/27 20:45:48 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ifkey(char c)
// {
// 	if (c == '_' || ft_isalnum(c))
// 		return (1);
// 	return (0);
// }

// char	*pre_copy(char **line, int *i, char sym)
// {
// 	char	*str1;
// 	char	*str2;
// 	int		j;

// 	j = *i;
// 	++(*i);
// 	while ((*line)[*i] != sym)
// 		++(*i);
// 	str1 = ft_substr(*line, 0, j);
// 	if (!str1)
// 		return (NULL);
// 	str2 = ft_substr(*line, j + 1, *i - j - 1);
// 	if (!str2)
// 	{
// 		free(str1);
// 		return (NULL);
// 	}
// 	free(str1);
// 	free(str2);
// 	return (ft_strjoin(str1, str2));
// }

// int	ft_ft(char **str, t_command_line *all)
// {
// 	int	i;

// 	i = -1;
// 	while (str[0][++i])
// 	{
// 		if (str[0][i] == '$')
// 		{
// 			if (ft_dollar(str, &i, all) == 0)
// 				return (-1);
// 		}
// 	}
// 	return (i);
// }

// void	free_ft(char **line, char *tmp, char *str1)
// {
// 	tmp = *line;
// 	*line = str1;
// 	free(tmp);
// }

// int	ft_quote(char **line, int *i, char sym, t_command_line *all)
// {
// 	char	*str1;
// 	char	*str2;
// 	char	*tmp;

// 	tmp = pre_copy(line, i, sym);
// 	if (!tmp)
// 		return (-1);
// 	str2 = ft_strdup(*line + *i + 1);
// 	if (!str2)
// 		return (-1);
// 	str1 = ft_strjoin(tmp, str2);
// 	free(tmp);
// 	free(str2);
// 	if (!str1)
// 		return (-1);
// 	if (sym == '\"')
// 	{
// 		if (ft_ft(&str1, all) == -1)
// 			return (-1);
// 	}
// 	i[0] = ft_strlen(*line) - *i;
// 	free_ft(line, tmp, str1);
// 	i[0] = ft_strlen(*line) - *i + (line[0][ft_strlen(*line) - *i] != '\0');
// 	return (1);
// }

int	ifkey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*pre_copy(char **line, int *i, char sym)
{
	char	*str1;
	char	*str2;
	char	*tmp;
	int		j;

	j = *i;
	++(*i);
	while ((*line)[*i] != sym)
		++(*i);
	str1 = ft_substr(*line, 0, j);
	if (!str1)
		return (NULL);
	str2 = ft_substr(*line, j + 1, *i - j - 1);
	if (!str2)
	{
		free(str1);
		return (NULL);
	}
	tmp = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (tmp);
}

int	ft_ft(char **str, t_command_line *all)
{
	int	i;

	i = -1;
	while (str[0][++i])
	{
		if (str[0][i] == '$')
		{
			if (ft_dollar(str, &i, all) == 0)
				return (-1);
		}
	}
	return (i);
}

int	ft_quote(char **line, int *i, char sym, t_command_line *all)
{
	char	*str1;
	char	*str2;
	char	*tmp;

	tmp = pre_copy(line, i, sym);
	if (!tmp)
		return (-1);
	str2 = ft_strdup(*line + *i + 1);
	if (!str2)
		return (-1);
	str1 = ft_strjoin(tmp, str2);
	free(tmp);
	free(str2);
	if (!str1)
		return (-1);
	if (sym == '\"')
	{
		if (ft_ft(&str1, all) == -1)
			return (-1);
	}
	i[0] = ft_strlen(*line) - *i;
	*line = str1;
	i[0] = ft_strlen(*line) - *i + (line[0][ft_strlen(*line) - *i] != '\0');
	return (1);
}

char	*ft_start_parser(char *line, t_command_line *all)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"')
		{
			if (ft_quote(&line, &i, '\"', all) == -1)
				return (NULL);
		}
		if (line[i] == '\'')
		{
			if (ft_quote(&line, &i, '\'', all) == -1)
				return (NULL);
		}
		if (line[i] == '$')
		{
			if (ft_dollar(&line, &i, all) == -1)
				return (NULL);
		}
		i += (line[i] != '\0');
	}
	return (line);
}
