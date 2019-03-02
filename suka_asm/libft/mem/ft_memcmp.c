/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 11:23:56 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/10/25 17:00:32 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	u_s1;
	unsigned char	u_s2;

	while (n--)
	{
		u_s1 = *(unsigned char*)s1++;
		u_s2 = *(unsigned char*)s2++;
		if (u_s1 != u_s2)
			return (u_s1 - u_s2);
	}
	return (0);
}
