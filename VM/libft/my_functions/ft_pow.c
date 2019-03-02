/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 19:19:27 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/14 19:22:25 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int32_t		ft_pow(int32_t number, int32_t power)
{
	if (power == 0)
		return (1);
	if (power == 1)
		return (number);
	return (number * ft_pow(number, power - 1));
}
