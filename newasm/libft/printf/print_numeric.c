/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numeric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 14:50:52 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/11/29 14:50:55 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int							print_pointer(t_printf *info, void *data)
{
	if (!data)
		return (print_string(info, "0x0"));
	info->size = 2;
	info->flags->sharp = 1;
	info->type = SMALL_HEX;
	return (print_numeric(info, data));
}

static unsigned long long	get_unsigned_integer(t_printf *info, void *data)
{
	unsigned long long integer;

	integer = (unsigned int)data;
	if (info->size)
	{
		if (info->size < 0)
			integer = (info->size < -1)
				? (unsigned long long)(unsigned char)data
					: (unsigned long long)(unsigned short int)data;
		else
			integer = (info->size > 1)
				? (unsigned long long)data
					: (unsigned long long)(unsigned long)data;
	}
	return (integer);
}

static long long			get_integer(t_printf *info, void *data)
{
	long long integer;

	integer = (int)data;
	if (info->size)
	{
		if (info->size < 0)
			integer = (info->size < -1)
				? (long long)(char)data : (long long)(short int)data;
		else
			integer = (info->size > 1)
				? (long long)data : (long long)(long)data;
	}
	return (integer);
}

int							print_numeric(t_printf *info, void *data)
{
	char				*buf;
	int					len;
	unsigned long long	u_integer;
	long long			integer;

	integer = get_integer(info, data);
	u_integer = get_unsigned_integer(info, data);
	if (info->type == DECIMAL)
		buf = ft_itoa_for_printf("0123456789", integer, info);
	else if (info->type == SMALL_HEX || info->type == BIG_HEX)
		buf = ft_itoa_for_printf((info->type == BIG_HEX) ? "0123456789ABCDEF"
			: "0123456789abcdef", u_integer, info);
	else if (info->type == OCTAL)
		buf = ft_itoa_for_printf("01234567", u_integer, info);
	else if (info->type == BINARY)
		buf = ft_itoa_for_printf("01", u_integer, info);
	else
		buf = ft_itoa_for_printf("0123456789", u_integer, info);
	info->accurace = -1;
	len = print_string(info, buf);
	free(buf);
	return (len);
}
