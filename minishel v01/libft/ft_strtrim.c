/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 17:27:22 by tacarlen          #+#    #+#             */
/*   Updated: 2021/04/22 17:27:25 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_search(char const str, char const *c)
{
	size_t	i;

	i = 0;
	while (c[i])
	{
		if (c[i] == str)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		end;
	char	*copy;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_search(s1[start], set))
		start++;
	while (end > start && ft_search(s1[end - 1], set))
		end--;
	copy = malloc(sizeof(char) * (end - start + 1));
	if (!copy)
		return (NULL);
	while (start < end)
		copy[i++] = s1[start++];
	copy[i] = '\0';
	return (copy);
}
