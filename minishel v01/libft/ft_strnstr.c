/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:28:03 by tacarlen          #+#    #+#             */
/*   Updated: 2021/04/22 20:58:15 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	a;

	i = 0;
	if (!needle[0])
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (haystack[i] && i < len)
	{
		a = 0;
		if (haystack[i] == needle[a])
		{
			while (needle[a] && haystack[i + a]
				&& haystack[i + a] == needle[a] && a + i < len)
				a++;
			if (!needle[a])
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
