/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 16:52:24 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/04 19:27:00 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			is_not_null(void *memory, int size)
{
	while (size--)
		if (*(char *)(memory + size))
			return (1);
	return (0);
}

int					ft_len(void *array, int size)
{
	int		i;

	i = 0;
	while (is_not_null(array, size))
	{
		i++;
		array += size;
	}
	return (i);
}
