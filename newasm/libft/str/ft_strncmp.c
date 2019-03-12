/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:35:03 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/10/29 19:33:02 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n)
	{
		while (--n && *(unsigned char*)s1
			&& *(unsigned char*)s1 == *(unsigned char*)s2)
		{
			s1++;
			s2++;
		}
		return (*(unsigned char*)s1 - *(unsigned char*)s2);
	}
	return (n);
}
