/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 00:10:45 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/07 00:13:36 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list					*ft_lstfind(t_list *head, void *data,
							int (*content_cmp)(void*, void*))
{
	while (head)
	{
		if (content_cmp(head->content, data))
			return (head);
		head = head->next;
	}
	return (head);
}
