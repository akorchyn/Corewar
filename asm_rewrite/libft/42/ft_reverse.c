/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 20:34:34 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/01/10 20:34:42 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_reverse(void *content, size_t content_size, size_t size)
{
	void	*tmp;
	size_t	i;

	i = 0;
	tmp = malloc(sizeof(content_size));
	while (i < size / 2)
	{
		ft_memcpy(tmp, content + i * content_size, content_size);
		ft_memcpy(content + i * content_size, content + (size - i - 1)
				* content_size, content_size);
		ft_memcpy(content + (size - i - 1) * content_size, tmp, content_size);
		i++;
	}
	free(tmp);
}
