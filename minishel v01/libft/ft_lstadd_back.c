/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:21:02 by tacarlen          #+#    #+#             */
/*   Updated: 2021/04/23 17:21:06 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*buf;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		buf = *lst;
		while (buf->next != NULL)
			buf = buf->next;
		buf->next = new;
	}
}
