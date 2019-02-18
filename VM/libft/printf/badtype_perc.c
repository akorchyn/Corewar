/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   badtype_perc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:12:25 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:12:25 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		bad_type(t_mask *mask, void *s)
{
	if (!s)
		ft_space_null(mask->width - 1, mask);
	return ((mask->width > 0) ? mask->width - 1 : 0);
}

int		percent(t_mask *mask, void *data)
{
	if (!data)
		return (ft_putch(mask, (void *)'%'));
	return (0);
}
