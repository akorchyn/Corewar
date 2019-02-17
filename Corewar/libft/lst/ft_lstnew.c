/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:14:52 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:14:52 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;
	int		i;

	i = -1;
	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = malloc(content_size);
	if (!list->content)
		return (NULL);
	if (!content)
	{
		free(list->content);
		list->content = NULL;
		list->content_size = 0;
		list->next = NULL;
	}
	else
	{
		ft_memcpy(list->content, content, content_size);
		list->content_size = content_size;
		list->next = NULL;
	}
	return (list);
}
