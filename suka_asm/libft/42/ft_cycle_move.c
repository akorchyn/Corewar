/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cycle_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 20:33:24 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/01/10 20:35:08 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_cycle_move(void *content, size_t content_size,
		int size, int distance)
{
	distance %= size;
	ft_reverse(content + ((distance < 0) ? ABS(distance) : size - distance) *
		content_size, content_size, distance + ((distance < 0) ? size : 0));
	ft_reverse(content, content_size, (distance < 0)
			? ABS(distance) : size - distance);
	ft_reverse(content, content_size, size);
}
