/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 13:25:40 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/10/31 23:17:12 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t dst_end;
	size_t out;

	out = 0;
	i = 0;
	while (dst[i] && i < dstsize)
		i++;
	dst_end = i;
	if (!dstsize)
		return (ft_strlen(src));
	if (dst_end > dstsize)
		return (dst_end + ft_strlen(src));
	while (src[i - dst_end] && i < dstsize - 1)
	{
		dst[i] = src[i - dst_end];
		i++;
		out++;
	}
	if (dst_end < dstsize)
		dst[i] = '\0';
	return (dst_end + ft_strlen(src));
}
