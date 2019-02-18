/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:15:08 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:15:08 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*src;
	int			i;

	i = -1;
	src = s;
	while (++i < (int)n)
	{
		if (src[i] == (char)c)
			return (((char *)s) + i);
	}
	return (NULL);
}
