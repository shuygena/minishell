/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:38:52 by tacarlen          #+#    #+#             */
/*   Updated: 2021/04/22 21:10:48 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_itoa_part2(int j, int i, unsigned int n2)
{
	char	*s;

	s = malloc(sizeof(char) * (i + 1 + j));
	if (s == NULL)
		return (NULL);
	s[i + j] = '\0';
	while (--i >= 0)
	{
		s[i + j] = (n2 % 10) + '0';
		n2 = n2 / 10;
	}
	if (j)
		s[i + j] = '-';
	return (s);
}

char	*ft_itoa(int n)
{
	int				i;
	unsigned int	n2;
	int				j;

	j = 0;
	i = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
	{
		n = -n;
		j++;
	}
	n2 = n;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (ft_itoa_part2(j, i, n2));
}
