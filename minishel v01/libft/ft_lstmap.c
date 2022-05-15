/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:36:11 by tacarlen          #+#    #+#             */
/*   Updated: 2021/04/25 13:36:13 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mem;
	t_list	*new;

	mem = NULL;
	new = NULL;
	if (!lst || !f)
		return (new);
	while (lst)
	{
		mem = ft_lstnew(f(lst->content));
		if (mem)
		{
			ft_lstadd_back(&new, mem);
			lst = lst->next;
		}
		else
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
	}
	return (new);
}
