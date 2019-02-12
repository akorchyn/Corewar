/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:17:55 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:17:55 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	ld;
	size_t	ls;
	size_t	n;

	ld = ft_strlen(dest);
	ls = ft_strlen((char *)src);
	if (size <= 0)
		return (ls);
	if (size < ld)
		return (ls + size);
	n = size - ld;
	ft_strncat(dest, src, n - 1);
	return (ld + ls);
}
