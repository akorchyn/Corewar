/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:14:58 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:14:58 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*arr;
	int		i;

	i = -1;
	if (!size)
		return (NULL);
	arr = (char *)malloc(size);
	if (!arr)
		return (NULL);
	while (++i < (int)size)
		arr[i] = '\0';
	return (arr);
}
