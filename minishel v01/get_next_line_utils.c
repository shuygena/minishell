/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mskeleto <mskeleto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 16:02:20 by mskeleto          #+#    #+#             */
/*   Updated: 2021/04/28 15:04:17 by mskeleto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t number, size_t size)
{
	size_t	i;
	size_t	tmp;
	char	*arr;

	i = 0;
	tmp = number * size;
	arr = (char *) malloc(tmp);
	if (arr == NULL)
		return (NULL);
	while (i < (tmp))
	{
		arr[i] = '\0';
		i++;
	}
	return (arr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_dup(const char *str)
{
	char	*pstr;
	char	*duble_str;
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	pstr = (char *) str;
	while (pstr[j] != '\n' && pstr[j] != '\0')
		j++;
	if (pstr[j] == '\n')
		j++;
	duble_str = (char *)malloc(ft_strlen((pstr + j)) + 1);
	if (!duble_str)
		return (NULL);
	while (pstr[j])
		duble_str[i++] = pstr[j++];
	duble_str[i] = '\0';
	return (duble_str);
}

int	ft_nsymbol(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (0);
		str++;
	}
	return (1);
}

char	*ft_strjon(char *s1, char *s2)
{
	char			*str;
	unsigned int	index;
	unsigned int	j;

	if (s1 == NULL)
		return (NULL);
	index = 0;
	j = 0;
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), 1);
	if (!str)
		return (NULL);
	while (s1[index])
	{
		str[index] = s1[index];
		index++;
	}
	free(s1);
	while (s2[j] && s2[j] != '\n')
		str[index++] = s2[j++];
	return (str);
}
