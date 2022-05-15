/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 22:21:35 by mskeleto          #+#    #+#             */
/*   Updated: 2021/10/27 20:47:35 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_block(char *block, t_command_line *all)
{
	char		**tmp;
	int			i;
	int			count;
	t_vector	s;

	count = ft_start_count_args(block + ft_skip_spaces(block));
	tmp = (char **)malloc(count * sizeof(char *));
	while (block[0] == ' ' || block[0] == '\t')
		++block;
	i = -1;
	s.x2 = 0;
	while (++i < count - 1)
	{
		s.x1 = ft_skip_spaces(block + s.x2) + s.x2;
		s.x2 = ft_find_end_arg(block, 0, 0, i);
		tmp[i] = ft_substr(block, s.x1, s.x2 - s.x1);
		tmp[i] = ft_start_parser(tmp[i], all);
		if (tmp[i] == NULL)
			return (NULL);
	}
	tmp[i] = NULL;
	return (tmp);
}

int	ft_find_end_arg(char *s, int i, int count, int index)
{
	while (s[i])
	{
		while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != ' '
			&& s[i] != '>' && s[i] != '<' && s[i] != '\t')
			i++;
		if ((count == index && (s[i] == ' ' || s[i] == '\t')) || ((s[i] == '>'
					|| s[i] == '<') && i > 0 && s[i - 1] != ' '
				&& s[i - 1] != '\t' && count == index + 1))
			return (i);
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
	return (i);
}

int	ft_check_for_ft_hand(char *tmp)
{
	char	*str;

	str = tmp;
	if (ft_strlen(str) == 0)
		return (0);
	if ((str[0] == '>' || str[0] == '<') && ft_strlen(str) == 1)
		return (1);
	if (((str[0] == '>' && str[1] == '>') || (str[0] == '<'\
			&& str[1] == '<')) && ft_strlen(str) == 2)
		return (1);
	return (0);
}

char	**ft_hand_redirs(char **tmp)
{
	int		i;
	char	**new;
	int		j;

	i = 0;
	j = 0;
	if (ft_crutch(tmp) == 0)
		return (tmp);
	new = (char **)malloc((ft_count_str(tmp) + 1) * sizeof(char *));
	while (tmp[i] != NULL)
	{
		if (ft_check_for_ft_hand(tmp[i]) == 1)
		{
			new[j] = ft_strjoin(tmp[i], tmp[i + 1]);
			i++;
		}
		else
			new[j] = ft_strdup(tmp[i]);
		i++;
		j++;
	}
	new[j] = NULL;
	return (new);
}

void	ft_creat_redirects(t_command_line *all, int index)
{
	int			j;
	char		*name;
	t_redirect	*last2;

	j = -1;
	last2 = NULL;
	name = ft_itoa(index);
	while (all->block[index].redirects[++j].type != 0)
	{
		if (all->block[index].redirects[j].type == 2)
		{
			ft_redirect2(all->block[index].redirects[j].file + 2, name);
			last2 = (&(all->block[index].redirects[j]));
		}
	}
	if (last2 != NULL)
		last2->file = ft_strjoin("<<.tmp_", name);
	free(name);
}
