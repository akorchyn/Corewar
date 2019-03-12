/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 14:35:51 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/03/12 14:35:57 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	throw_error(char *error, size_t line)
{
	ft_putstr_fd(RED, 2);
	if (line)
	{
		ft_putstr_fd("Error on line ", 2);
		ft_putnbr_fd(line, 2);
		ft_putstr_fd(": "EOM, 2);
	}
	ft_putendl_fd(error, 2);
	ft_putstr_fd(EOM, 2);
	exit(1);
}

uint8_t	check_extension(char *file_name, char *extension)
{
	return (ft_strequ((file_name += ft_strlen(file_name)
			- ft_strlen(extension)), extension));
}
