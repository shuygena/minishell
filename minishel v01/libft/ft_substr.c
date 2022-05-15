/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 15:53:12 by tacarlen          #+#    #+#             */
/*   Updated: 2021/04/22 15:53:35 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*mem;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (len <= 0)
		return (ft_strdup(""));
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	mem = malloc(sizeof(char) * len + 1);
	if (!mem)
		return (NULL);
	while (s[start + i] && i < len)
	{
		mem[i] = s[start + i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}
