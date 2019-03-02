/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 21:48:34 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/10/27 23:40:54 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	if (!*(unsigned char*)needle)
		return ((char*)haystack);
	while (*(unsigned char*)haystack)
	{
		if (*(unsigned char*)haystack == *(unsigned char*)needle &&
				!ft_memcmp(haystack, needle, ft_strlen(needle)))
			return ((char*)haystack);
		haystack++;
	}
	return (NULL);
}
