/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 13:40:04 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/11/01 20:32:12 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *begin;
	t_list *tmp;

	if (lst && f)
	{
		begin = f(lst);
		tmp = begin;
		while (lst->next)
		{
			tmp->next = f(lst->next);
			tmp = tmp->next;
			lst = lst->next;
		}
		return (begin);
	}
	return (lst);
}
