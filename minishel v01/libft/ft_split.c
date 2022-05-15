/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 09:53:57 by tacarlen          #+#    #+#             */
/*   Updated: 2021/04/24 09:54:01 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numwords(char const *s, char c)
{
	unsigned int	i;
	unsigned int	n;

	i = 0;
	n = 1;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			n++;
		}
		if (s[i] == '\0')
			return (n);
		i++;
	}
	return (n);
}

static void	ft_free(char **s, int n)
{
	while (n >= 0)
	{
		free(s[n]);
		n--;
	}
	free(s);
	return ;
}

static char	**ft_ch(int len, char const *s, char c, char **buf)
{
	unsigned int	i;
	size_t			end;
	int				j;

	i = 0;
	j = -1;
	while (++j < len - 1)
	{
		while (s[i] && s[i] == c)
			i++;
		end = i;
		while (s[end] && s[end] != c)
			end++;
		buf[j] = ft_substr(s, i, end - i);
		if (!buf[j])
			ft_free(buf, j - 1);
		i = end;
	}
	buf[j] = NULL;
	return (buf);
}

char	**ft_split(char const *s, char c)
{
	char	**buf;
	int		len;

	if (!s)
		return (NULL);
	len = ft_numwords(s, c);
	buf = malloc(sizeof(char *) * (len));
	if (!buf)
		return (NULL);
	return (ft_ch(len, s, c, buf));
}
