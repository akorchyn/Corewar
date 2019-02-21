/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 21:14:12 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/19 21:14:24 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_end(t_list **head, t_list *new)
{
	static t_list	*last;

	if (*head)
	{
		last->next = new;
		last = last->next;
	}
	else
		ft_lstadd(head, (last = new));
}
