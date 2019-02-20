/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:15:15 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:15:15 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *lhs, const void *rhs, size_t n)
{
	int	i;

	i = -1;
	while (++i < (int)n &&
			((unsigned char *)lhs)[i] == ((unsigned char *)rhs)[i])
		;
	if (i == (int)n)
		return (0);
	else
		return (((unsigned char *)lhs)[i] - ((unsigned char *)rhs)[i]);
}
