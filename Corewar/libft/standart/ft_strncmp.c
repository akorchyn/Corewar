/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:18:18 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:18:18 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*u1;
	unsigned char	*u2;
	int				i;

	u1 = (unsigned char *)s1;
	u2 = (unsigned char	*)s2;
	i = -1;
	while (++i < (int)n && u1[i] != '\0' && u2[i] != '\0' && u1[i] == u2[i])
		;
	if ((int)n == i)
		return (0);
	return (u1[i] - u2[i]);
}
