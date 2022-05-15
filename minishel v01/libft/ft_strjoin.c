/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 16:59:25 by tacarlen          #+#    #+#             */
/*   Updated: 2021/04/22 16:59:29 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i1;
	int		i2;

	i1 = 0;
	i2 = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i1])
	{
		str[i1] = s1[i1];
		i1++;
	}
	while (s2[i2])
	{
		str[i1] = s2[i2];
		i1++;
		i2++;
	}
	str[i1] = '\0';
	return (str);
}
