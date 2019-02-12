/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:15:47 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:15:47 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	int				i;

	d = dest;
	s = (void *)src;
	i = -1;
	if (d < s)
		while (++i < (int)n)
			d[i] = s[i];
	else if (d > s)
		while (n > 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
	return (dest);
}
