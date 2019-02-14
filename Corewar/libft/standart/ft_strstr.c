/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:19:04 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:19:04 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	int		j;

	j = 0;
	i = ft_strlen((char *)needle);
	if ((char)needle[j] == '\0')
		return ((char *)haystack);
	while (haystack[j] != '\0')
	{
		if (ft_strncmp(haystack + j, needle, i) == 0)
			return ((char *)haystack + j);
		j++;
	}
	return (NULL);
}
