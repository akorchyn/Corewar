/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:04:09 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/26 17:04:24 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	throw_error(int error_id, char *str, const size_t line)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(str, 2);
	if (line)
	{
		ft_putnbr_fd(line, 2);
		ft_putendl_fd("!", 2);
	}
	ft_putstr_fd(EOM, 2);
	exit(error_id);
}

uint8_t	check_extension(char *file_name, char *extension, size_t extension_len)
{
	size_t	name_len;
	char	extension_buff[extension_len];

	ft_memcpy(extension_buff, extension, extension_len + 1);
	name_len = ft_strlen(file_name);
	ft_reverse(file_name, 1, name_len);
	ft_reverse(extension_buff, 1, extension_len);
	return (!ft_strncmp(file_name, extension_buff, extension_len));
}
