/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 12:37:35 by tacarlen          #+#    #+#             */
/*   Updated: 2021/04/22 20:18:39 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	n;

	i = -1;
	n = ft_strlen(s);
	while (n >= ++i)
		if (s[i] == c)
			return ((char *)s + i);
	return (NULL);
}
