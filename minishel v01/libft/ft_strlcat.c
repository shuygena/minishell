/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 13:54:59 by tacarlen          #+#    #+#             */
/*   Updated: 2021/04/20 13:18:28 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = ft_strlen(dst);
	if (!dst && !src)
		return (0);
	if (count >= dstsize)
		return (ft_strlen(src) + dstsize);
	else
	{
		while (src[i] && (i + count) < dstsize - 1)
		{
			dst[i + count] = src[i];
			i++;
		}
	}
	dst[i + count] = '\0';
	return (count + ft_strlen(src));
}
