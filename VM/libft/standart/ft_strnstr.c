/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:18:41 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:18:41 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t i;
	size_t len;

	len = ft_strlen((char *)needle);
	i = 0;
	if (haystack[i])
		;
	if (needle[i] == '\0' && !haystack)
		return ((char *)haystack);
	while (i + len <= n && ((char *)haystack)[i])
	{
		if (ft_strncmp(haystack + i, needle, len) == 0)
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
