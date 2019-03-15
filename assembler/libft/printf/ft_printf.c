/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 12:46:02 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/12/10 19:44:56 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_printf	*make_parameters(char **p, va_list *ap)
{
	t_printf	*out;

	out = (t_printf*)ft_memalloc(sizeof(t_printf));
	out->flags = (t_flags*)ft_memalloc(sizeof(t_flags));
	out->zero = ' ';
	out->type = NO_TYPE;
	out->accurace = -1;
	while (1)
	{
		(*p)++;
		(**p > '0' && **p <= '9') ? parse_nbr(out, p, ap) : 0;
		(**p == '.' || **p == '*') ? parse_nbr(out, p, ap) : 0;
		(**p == '#' || **p == ' ' || **p == '0' || **p == '-' || **p == '+')
			? parse_flag(out, p) : 0;
		(**p == 'l' || **p == 'h' || **p == 'L') ? parse_size(out, p) : 0;
		if (!**p || is_conversion_type(**p) || (**p >= 7 && **p <= 13)
			|| **p == 63 || **p == 92 || **p == 34 || **p == '\t')
			break ;
	}
	(is_conversion_type(**p)) ? parse_type(out, p) : 0;
	return (out);
}

static int		print_type(va_list *ap, t_printf *info)
{
	info->zero = (info->flags->minus) ? ' ' : info->zero;
	if (info->type != FLOAT && info->type != NO_TYPE)
	{
		if (info->type == STRING)
			return (print_string(info, va_arg(*ap, void*)));
		if (info->type == CHAR)
			return (print_char(info, va_arg(*ap, void*)));
		if (info->type == PERCENTAGE)
			return (print_char(info, NULL));
		if (info->type == POINTER)
			return (print_pointer(info, va_arg(*ap, void*)));
		return (print_numeric(info, va_arg(*ap, void*)));
	}
	if (info->type == FLOAT)
	{
		if (info->size || info->flags->big_longness)
			return (print_double(info, va_arg(*ap, long double)));
		return (print_float(info, va_arg(*ap, double)));
	}
	return (0);
}

int				ft_printf(const char *format, ...)
{
	va_list			ap;
	t_printf		*info;
	int				len;
	int				out;

	len = 0;
	out = 0;
	va_start(ap, format);
	while (*format)
	{
		while (format[len] && format[len] != '%')
			len++;
		out += write(1, format, len);
		format += len;
		if (*format == '%')
		{
			info = make_parameters((char**)&format, &ap);
			out += print_type(&ap, info);
			free(info->flags);
			free(info);
			len = 0;
		}
	}
	va_end(ap);
	return (out);
}
