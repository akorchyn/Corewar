/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 20:36:13 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/10/28 15:18:27 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t needle_len;

	needle_len = ft_strlen(needle);
	if (!*(unsigned char*)needle)
		return ((char*)haystack);
	while (*(unsigned char*)haystack && len)
	{
		if (*(unsigned char*)haystack == *(unsigned char*)needle &&
		needle_len <= len && !ft_memcmp(haystack, needle, needle_len))
			return ((char*)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
