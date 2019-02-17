/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:18:22 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:18:22 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	int	i;

	i = -1;
	while (src[++i] != '\0' && i < (int)n)
		dest[i] = src[i];
	while (i < (int)n)
		dest[i++] = '\0';
	return (dest);
}
