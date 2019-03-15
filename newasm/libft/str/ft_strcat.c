/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 12:06:52 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/12/06 14:23:43 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strcat(char *s1, const char *s2)
{
	size_t i;
	size_t k;

	i = ft_strlen(s1);
	k = ft_strlen(s2);
	s1[i + k] = '\0';
	if (s1 < s2)
	{
		k = 0;
		while (s2[k])
		{
			s1[i + k] = s2[k];
			k++;
		}
	}
	else
		while (k--)
			s1[i + k] = s2[k];
	return (s1);
}
