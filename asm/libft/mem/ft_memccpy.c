/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:42:26 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/10/25 14:05:37 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*t_dest;
	unsigned char	*t_src;

	t_dest = (unsigned char*)dest;
	t_src = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		t_dest[i] = t_src[i];
		if (t_dest[i] == (unsigned char)c)
			return ((void*)&t_dest[i + 1]);
		i++;
	}
	return (NULL);
}
