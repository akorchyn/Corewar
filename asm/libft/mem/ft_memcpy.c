/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:11:20 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/01/30 18:44:19 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *dst;
	unsigned char *sorc;

	dst = (unsigned char*)dest;
	sorc = (unsigned char*)src;
	while (n--)
		*dst++ = *sorc++;
	return (dest);
}
