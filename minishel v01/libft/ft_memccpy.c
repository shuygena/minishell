/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 17:27:19 by tacarlen          #+#    #+#             */
/*   Updated: 2021/04/20 18:56:17 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	int		i;
	char	buf;
	char	*dest;
	char	*source;

	i = 0;
	buf = (char)c;
	dest = (char *)dst;
	source = (char *)src;
	if (!dest && !source)
		return (NULL);
	while (i < (int)n)
	{
		dest[i] = source[i];
		if (source[i] == buf)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
