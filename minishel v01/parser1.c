/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 23:05:00 by mskeleto          #+#    #+#             */
/*   Updated: 2021/10/27 20:44:53 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parser(char *line, t_command_line *all)
{
	char	**comands;
	int		i;

	i = -1;
	all->num_pipes = ft_pipes_count(line);
	comands = ft_split_line(line, all);
	all->pipes_fd = (int **)malloc(all->num_pipes * sizeof(int *));
	all->block = (t_command_block *)(malloc((all->num_pipes + 1)
				* sizeof(t_command_block)));
	while (comands[++i] != NULL)
	{
		ft_parse_block(comands[i], all, i);
		if (i < all->num_pipes)
		{
			all->pipes_fd[i] = (int *)malloc(2 * sizeof(int));
			pipe(all->pipes_fd[i]);
		}
	}
	i = 0;
	while (comands[i] != NULL)
		free(comands[i++]);
	free(comands);
	return (0);
}

int	ft_count_char(const char *str, char c)
{
	int	count;
	int	i;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c)
			count++;
	}
	return (count);
}

int	ft_count_redirs(char **tmp)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tmp[i] != NULL && tmp[i][0] != '\0')
	{
		if (tmp[i][0] == '<' || tmp[i][0] == '>')
			count++;
		i++;
	}
	return (count);
}

int	ft_parse_block(char *block, t_command_line *all, int index)
{
	char	**tmp;
	int		count_str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	tmp = ft_split_block(block, all);
	tmp = ft_hand_redirs(tmp);
	count_str = ft_count_str(tmp);
	all->block[index].last_left_redir = NULL;
	all->block[index].last_right_redir = NULL;
	all->block[index].redirects = (t_redirect *)malloc(
			(ft_count_redirs(tmp) + 1) * sizeof(t_redirect));
	all->block[index].narg = (char **)malloc(
			(count_str - ft_count_redirs(tmp) + 1) * sizeof(char *));
	while (tmp[++i])
		if (tmp[i][0] != '<' && tmp[i][0] != '>')
			all->block[index].narg[j++] = ft_strdup(tmp[i]);
	all->block[index].narg[j] = NULL;
	ft_parse_redirs(tmp, all, index);
	ft_pro_redirs(all, index);
	all->block[index].close_fd1 = 0;
	all->block[index].close_fd2 = 0;
	return (0);
}

void	ft_parse_redirs(char **tmp, t_command_line *all, int index)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (tmp[++i])
	{
		if (ft_strlen(tmp[i]) > 1)
		{
			if (tmp[i][0] == '<' || tmp[i][0] == '>')
			{
				all->block[index].redirects[++j].file = tmp[i];
				if (tmp[i][0] == '<' && tmp[i][1] == '<')
					all->block[index].redirects[j].type = 2;
				else if (tmp[i][0] == '<' && tmp[i][1] != '<')
					all->block[index].redirects[j].type = 1;
				else if (tmp[i][0] == '>' && tmp[i][1] == '>')
					all->block[index].redirects[j].type = 4;
				else if (tmp[i][0] == '>' && tmp[i][1] != '>')
					all->block[index].redirects[j].type = 3;
			}
		}
	}
	all->block[index].redirects[++j].type = 0;
}
