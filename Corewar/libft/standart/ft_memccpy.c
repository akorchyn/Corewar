/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:15:04 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:15:04 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*ans;
	size_t		i;

	i = 0;
	ans = dest;
	while (i < n)
	{
		*(ans + i) = *(((unsigned char *)src) + i);
		if (ans[i] == (char)c)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
