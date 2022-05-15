/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utlis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskeleto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 20:16:49 by mskeleto          #+#    #+#             */
/*   Updated: 2022/05/15 20:17:02 by mskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_copy(char *path)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc(ft_strlen(path) + 1);
	while (path[i])
	{
		str[i] = path[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_change_pwd(t_command_line *all)
{
	t_env_list	*tmp;
	char		*path;
	int			i;

	tmp = ft_find_env(all, "PWD=");
	if (tmp == NULL)
		return (0);
	path = (char *)malloc(1025);
	path = getcwd(path, 1024);
	if (tmp->value != NULL)
		free(tmp->value);
	tmp->value = (char *)malloc(ft_strlen(path));
	i = 0;
	while (path[i])
	{
		tmp->value[i] = path[i];
		i++;
	}
	tmp->value[i] = '\0';
	free(path);
	return (0);
}

int	ft_change_dir(t_command_line *all, char *path)
{
	int	res;
	int	fd;

	res = chdir(path);
	if (res == -1)
	{
		all->error = 1;
		fd = open(path, O_RDONLY);
		if (fd == -1)
			ft_error("cd: ", path, "No such file or directory");
		else
		{
			close(fd);
			ft_error("cd: ", path, "Not a directory");
		}
		return (1);
	}
	return (0);
}

int	ft_free_buf(int er, int *buf_pid)
{
	free(buf_pid);
	return (er);
}

void	ft_free_unlink(t_command_line *all)
{
	int		i;
	char	*name;
	char	*index;

	signal(SIGQUIT, SIG_IGN);
	i = 0;
	while (i <= all->num_pipes)
	{
		index = ft_itoa(i);
		name = ft_strjoin(".tmp_", index);
		ft_unlink(name);
		free(index);
		free(name);
		i++;
	}
}
