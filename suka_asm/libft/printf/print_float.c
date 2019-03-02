/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 16:33:11 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/12/04 16:33:14 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	check_width(char **buf, t_printf *info)
{
	int		slen;
	int		i;
	char	*new;

	slen = (int)ft_strlen(*buf);
	if (info->width > slen && info->zero == '0')
	{
		i = 0;
		new = ft_strnew(info->width);
		(!ft_isdigit(**buf)) ? new[i++] = *(*buf)++ : 0;
		while (info->width-- - slen)
			new[i++] = '0';
		ft_strcat(new, *buf);
		free((ft_isdigit(*new)) ? *buf : *buf - 1);
		*buf = new;
	}
}

static void	ft_itoa_accurace(__int128 data, t_printf *info, char **buf)
{
	char	*out;
	int		accurace;

	accurace = (info->accurace == -1) ? 6 : info->accurace;
	out = ft_strnew(accurace);
	while (accurace--)
	{
		out[accurace] = data % 10 + 48;
		data /= 10;
	}
	info->accurace = -1;
	ft_strcat(ft_strcat(*buf, "."), out);
	free(out);
}

int			print_float(t_printf *info, float data)
{
	int			accurace;
	char		*buf;
	char		*str;
	int			len;

	buf = ft_strnew(80);
	(data < 0.0) ? *buf = '-' : 0;
	(!*buf && info->flags->plus) ? *buf = '+' : 0;
	(!*buf && info->flags->space) ? *buf = ' ' : 0;
	data = ABS(data);
	accurace = (info->accurace == -1) ? 6 : info->accurace;
	ft_strcat(buf, (str = ft_itoa10((__uint128_t)data)));
	data = data - ((__uint128_t)data);
	if (info->accurace)
	{
		while (accurace--)
			data *= (float)10.0;
		data += (float)0.5;
		ft_itoa_accurace((__uint128_t)data, info, &buf);
	}
	check_width(&buf, info);
	len = print_string(info, buf);
	free(str);
	free(buf);
	return (len);
}

int			print_double(t_printf *info, long double data)
{
	int			accurace;
	char		*buf;
	char		*str;
	int			len;

	buf = ft_strnew(80);
	(data < 0.0) ? *buf = '-' : 0;
	(!*buf && info->flags->plus) ? *buf = '+' : 0;
	(!*buf && info->flags->space) ? *buf = ' ' : 0;
	data = ABS(data);
	accurace = (info->accurace == -1) ? 6 : info->accurace;
	ft_strcat(buf, (str = ft_itoa10((__int128)data)));
	data -= (info->size) ? (double)(__int128)data : (long double)(__int128)data;
	if (info->accurace)
	{
		while (accurace--)
			data *= (info->size) ? (double)10.0 : (long double)10.0;
		data += (info->size) ? (double)0.5 : (long double)0.5;
		ft_itoa_accurace((__int128)data, info, &buf);
	}
	check_width(&buf, info);
	len = print_string(info, buf);
	free(str);
	free(buf);
	return (len);
}
