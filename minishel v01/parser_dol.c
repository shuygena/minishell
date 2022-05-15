/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_dol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:40:10 by tacarlen          #+#    #+#             */
/*   Updated: 2021/10/27 18:16:08 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#	define SYNTAX "syntax error: open quote\n"

char	*ft_question(char **line, int *i, t_command_line *all)
{
	char	*str;
	char	*str1;
	int		status;

	if (i != 0)
		str1 = ft_substr(*line, 0, *i);
	if (all->error >= 0)
		status = (all->error / 256);
	else
		status = (256 - all->error / 256);
	str = ft_itoa(status);
	all->dol_que = ft_strjoin(str1, str);
	if (i != 0)
		free(str1);
	free(str);
	*(line) = ft_strjoin(all->dol_que, *line + 2);
	free(str);
	all->mystery = 1;
	return (NULL);
}

char	*ft_one_param(char *str, t_env_list	*key)
{
	if (str && key)
		return (ft_strjoin(str, key->value));
	else if (str)
		return (ft_strdup(str));
	else if (key)
		return (ft_strdup(key->value));
	return (ft_strdup(""));
}

char	*find_command(char **line, t_env_list *key, char *str3, int j)
{
	char		*str;
	char		*tmp;

	str = ft_substr(*line, 0, j);
	if (!str)
		return (NULL);
	tmp = ft_one_param(str, key);
	if (!tmp)
		return (NULL);
	free(str);
	str = tmp;
	if (str3)
	{
		tmp = ft_strjoin(str, str3);
		if (!tmp)
			return (NULL);
		free(str3);
	}
	free(str);
	return (tmp);
}

char	*check_and_create_line(char **line, int *i, t_command_line *all)
{
	int		j;
	char	*str;

	j = *i;
	if (line[0][*i + 1] == '?')
		return (ft_question(line, i, all));
	++(*i);
	while ((*line)[*i] && ifkey((*line)[*i]))
		++(*i);
	if (*i == j + 1)
		return (NULL);
	str = ft_substr(*line, j + 1, *i - j - 1);
	if (!str)
		return (NULL);
	return (str);
}

int	ft_dollar(char **line, int *i, t_command_line *all)
{
	int			j;
	t_env_list	*key;
	char		*str1;
	char		*str2;
	char		*tmp;

	j = *i;
	str2 = NULL;
	str1 = check_and_create_line(line, i, all);
	if (!str1)
		return (0 || all->mystery);
	if (*line + j + ft_strlen(str1) + 1)
	{
		str2 = ft_strdup(*line + j + ft_strlen(str1) + 1);
		if (!str2)
			return (-1);
	}
	key = ft_find_export(all, str1);
	free(str1);
	tmp = find_command(line, key, str2, j);
	if (!tmp)
		return (-1);
	*line = tmp;
	return (1);
}
