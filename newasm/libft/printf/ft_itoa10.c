/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:55:17 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/12/05 17:55:19 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nblen(__uint128_t nb)
{
	int out;

	out = 1;
	while ((nb /= 10))
		out++;
	return (out);
}

char		*ft_itoa10(__uint128_t nb)
{
	char	*out;
	int		nblen;

	nblen = ft_nblen(nb);
	out = ft_strnew(nblen);
	while (nblen--)
	{
		out[nblen] = (nb % 10) + 48;
		nb /= 10;
	}
	return (out);
}
