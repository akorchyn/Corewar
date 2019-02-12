/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:18:14 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:18:14 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	int		i;
	size_t	j;

	i = -1;
	j = ft_strlen(dest);
	while (++i < (int)n && src[i] != '\0')
		dest[j++] = src[i];
	dest[j] = '\0';
	return (dest);
}
