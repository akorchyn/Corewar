/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 19:41:16 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/10/25 19:59:46 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	if (ft_strchr(s, c))
	{
		while (*s)
			s++;
		while (*s != c)
			s--;
		return ((char*)s);
	}
	return (NULL);
}
