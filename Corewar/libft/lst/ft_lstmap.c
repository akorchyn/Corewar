/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:14:47 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:14:47 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*run;
	t_list	*new;
	t_list	*new_run;

	if (!lst)
		return (NULL);
	new = (t_list *)malloc(sizeof(t_list));
	run = lst;
	new = f(run);
	run = run->next;
	new_run = new;
	while (run)
	{
		new_run->next = (t_list *)malloc(sizeof(t_list));
		new_run->next = f(run);
		new_run = new_run->next;
		run = run->next;
	}
	return (new);
}
