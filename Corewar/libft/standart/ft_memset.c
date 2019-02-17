/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:15:51 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:15:51 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	char	*ans;
	size_t	l;

	ans = str;
	l = 0;
	while (l < n)
		ans[l++] = (char)c;
	return (str);
}
