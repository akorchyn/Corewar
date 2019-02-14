/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:50:36 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/11/29 14:50:38 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		*ft_my_memset(void *b, int c, int len)
{
	char	*temp;
	int		i;

	i = -1;
	temp = (char*)b;
	while (++i < len)
		temp[i] = (unsigned char)c;
	return (b);
}

static char		*remake_buf(t_printf *info, char *buf, int slen)
{
	char	*out;
	int		needed;

	needed = (info->accurace != -1 && info->accurace < slen)
		? info->accurace : slen;
	needed = (info->width > needed) ? info->width : needed;
	(info->accurace != -1 && info->accurace < slen) ? slen = info->accurace : 0;
	out = ft_strnew(needed);
	(info->flags->minus) ? ft_strncat(out, buf, slen)
		: ft_my_memset(out, ' ', info->width - slen);
	(info->flags->minus) ? ft_my_memset(out + ft_strlen(out),
		' ', info->width - slen) : ft_strncat(out, buf, slen);
	return (out);
}

int				print_string(t_printf *info, void *data)
{
	int		len;
	char	*buf;

	buf = (data) ? (char*)data : "(null)";
	len = ft_strlen(buf);
	buf = remake_buf(info, buf, len);
	len = write(1, buf, ft_strlen(buf));
	free(buf);
	return (len);
}

int				print_char(t_printf *info, void *data)
{
	char	infoo;
	char	*symbol;
	int		len;

	infoo = (info->type == CHAR) ? (char)data : '%';
	info->width = ABS(info->width);
	symbol = ft_strnew(info->width + 1);
	(info->flags->minus) ? ft_my_memset(symbol, infoo, 1)
		: ft_my_memset(symbol, info->zero, info->width - 1);
	(info->flags->minus) ? ft_my_memset(symbol +
		ft_strlen(symbol), ' ', info->width - 1)
			: ft_my_memset(symbol + (ft_strlen(symbol)), infoo, 1);
	len = write(1, symbol, (info->width) ? info->width : 1);
	free(symbol);
	return (len);
}
