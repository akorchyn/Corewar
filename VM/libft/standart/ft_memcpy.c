/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:15:20 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:15:20 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	char		*ans;
	int			i;

	i = -1;
	ans = (char *)dest;
	while (++i < (int)count)
		ans[i] = ((unsigned char *)src)[i];
	return (ans);
}
