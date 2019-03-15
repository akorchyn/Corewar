/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_sorted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 13:30:16 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/10/30 23:26:41 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_sorted(t_list **alst, t_list *new,
	int (*cmp)(t_list *lst, t_list *new))
{
	t_list *tmp;

	if (!(*alst) || cmp(*alst, new) >= 0)
		ft_lstadd(alst, new);
	else
	{
		tmp = *alst;
		while (tmp->next && cmp(tmp->next, new) < 0)
			tmp = tmp->next;
		ft_lstadd(&tmp->next, new);
	}
}
