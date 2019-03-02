/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 13:08:51 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/10/30 23:06:56 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *out;

	out = (t_list*)malloc(sizeof(t_list));
	if (out)
	{
		out->content_size = (content) ? content_size : 0;
		out->content = (out->content_size)
			? ft_memcpy(malloc(content_size), content, content_size) : NULL;
		out->next = NULL;
	}
	return (out);
}
