/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 22:15:52 by tacarlen          #+#    #+#             */
/*   Updated: 2021/04/24 22:15:54 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;

	if (!lst || !del)
		return ;
	if (!*lst)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		list = (*lst)->next;
		free(*lst);
		*lst = list;
	}
}
