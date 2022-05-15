/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 19:12:29 by tacarlen          #+#    #+#             */
/*   Updated: 2021/04/22 20:19:52 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	n;

	n = 0;
	if (!dst && !src)
		return (0);
	if (dstsize > 0)
	{
		while (src[n] && n < dstsize - 1)
		{
			dst[n] = src[n];
			n++;
		}
		dst[n] = '\0';
	}
	return (ft_strlen(src));
}
