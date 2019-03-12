/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_for_printf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:46:48 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/11/28 16:46:51 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nblen(__int128 nb, int accurace, int divider)
{
	int out;

	out = 0;
	while (nb)
	{
		nb /= divider;
		out++;
	}
	return (accurace > out) ? accurace : out;
}

static char		*check_mask(t_printf *info, __int128 nb, int *accurace)
{
	char	*out;

	*accurace = info->accurace;
	(!nb && *accurace == -1) ? *accurace = ABS(*accurace) : 0;
	out = ft_strnew((info->accurace == -1 && info->zero == '0')
		? info->width + 21 : info->accurace + 21);
	if (info->type == DECIMAL)
	{
		(nb < 0) ? ft_strcat(out, "-") : 0;
		(!*out && info->flags->space) ? ft_strcat(out, " ") : 0;
		(nb >= 0 && info->flags->plus) ? ft_memset(out, '+', 1) : 0;
	}
	if (info->type == BIG_HEX || info->type == SMALL_HEX)
		if (info->flags->sharp && nb)
			ft_strcat(out, (info->type == BIG_HEX) ? "0X" : "0x");
	if (info->type == OCTAL && info->flags->sharp && nb)
		ft_memset(out, '0', 1);
	if (*accurace == -1 && info->zero == '0')
		*accurace = info->width - ft_strlen(out);
	return (out);
}

static char		*ft_get_this_str(__int128 nb, char *base, int a, t_printf *info)
{
	char				*out;
	int					nblen;
	unsigned long		divider;
	ULL					tmp;

	tmp = (ULL)nb;
	divider = ft_strlen(base);
	nblen = ft_nblen(nb, a, divider);
	out = ft_strnew(nblen);
	if (info->type == DECIMAL)
	{
		nb = ABS(nb);
		while (nb || a-- > 0)
		{
			out[--nblen] = base[nb % divider];
			nb /= divider;
		}
	}
	else
		while (tmp || a-- > 0)
		{
			out[--nblen] = base[tmp % divider];
			tmp /= divider;
		}
	return (out);
}

char			*ft_itoa_for_printf(char *base, __int128 nb, t_printf *info)
{
	char	*out;
	char	*mask;
	int		accurace;

	mask = check_mask(info, nb, &accurace);
	out = ft_get_this_str(nb, base, accurace, info);
	if (*mask)
	{
		mask = ft_strcat(mask, out);
		free(out);
		return (mask);
	}
	free(mask);
	return (out);
}
