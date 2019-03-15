/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 23:15:55 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/11/15 23:15:58 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		is_conversion_type(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'o' || c == 'u' || c == 'x' || c == 'X' || c == 'f'
		|| c == 'b' || c == '%');
}

void	parse_flag(t_printf *info, char **c)
{
	(**c == '#') ? info->flags->sharp = 1 : 0;
	(**c == ' ') ? info->flags->space = 1 : 0;
	(**c == '+') ? info->flags->plus = 1 : 0;
	(**c == '0') ? info->zero = '0' : 0;
	(**c == '-') ? info->flags->minus = 1 : 0;
}

void	parse_size(t_printf *info, char **c)
{
	(**c == 'h') ? info->size-- : 0;
	(**c == 'l') ? info->size++ : 0;
	(**c == 'L') ? info->flags->big_longness = 1 : 0;
}

void	parse_nbr(t_printf *info, char **p, va_list *ap)
{
	if (**p == '*')
	{
		info->width = va_arg(*ap, int);
		if (info->width < 0)
		{
			info->flags->minus = 1;
			info->width = ABS(info->width);
		}
	}
	else if (**p == '.')
	{
		(*p)++;
		if (**p == '*')
			info->accurace = va_arg(*ap, int);
		else
			info->accurace = ft_atoi(*p);
	}
	else
		info->width = ft_atoi(*p);
	while (**p >= '0' && **p <= '9')
		(*p)++;
}

void	parse_type(t_printf *info, char **c)
{
	(**c == 'c') ? info->type = CHAR : 0;
	(**c == 's') ? info->type = STRING : 0;
	(**c == 'p') ? info->type = POINTER : 0;
	(**c == 'd' || **c == 'i') ? info->type = DECIMAL : 0;
	(**c == 'o') ? info->type = OCTAL : 0;
	(**c == 'u') ? info->type = UINT : 0;
	(**c == 'x') ? info->type = SMALL_HEX : 0;
	(**c == 'X') ? info->type = BIG_HEX : 0;
	(**c == 'f') ? info->type = FLOAT : 0;
	(**c == 'b') ? info->type = BINARY : 0;
	(**c == '%') ? info->type = PERCENTAGE : 0;
	(void)(*c)++;
}
