/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 15:46:28 by tacarlen          #+#    #+#             */
/*   Updated: 2021/04/19 21:59:29 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	m;
	int	res;

	i = 0;
	m = 1;
	res = 0;
	while ((str[i] > 8 && str[i] < 14) || (str[i] == 32))
		i++;
	if (str[i] == 43)
		i++;
	else if (str[i] == 45)
	{
		m = -m;
		i++;
	}
	while (str[i])
	{
		if (str[i] > 47 && str[i] < 58)
			res = res * 10 + str[i] - 48;
		else
			break ;
		i++;
	}
	return (res * m);
}
