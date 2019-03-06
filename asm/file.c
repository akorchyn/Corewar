/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:29:52 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/26 17:29:59 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*read_file(char *file_name)
{
	ssize_t	carriage;
	size_t	offset;
	char	*buff;
	int		fd;

	offset = 0;
	ft_reverse(file_name, 1, ft_strlen(file_name));
	if (!(buff = malloc(BUFF_SIZE + 1)))
		throw_error(EXIT_FAILURE, "Memory allocation failed!\n", 0);
	if ((fd = open(file_name, O_RDONLY)) == -1 || read(fd, buff, 0) == -1)
		throw_error(EXIT_FAILURE, "Error opening or reading file!\n", 0);
	while ((carriage = read(fd, buff + (offset * BUFF_SIZE), BUFF_SIZE)))
	{
		buff[carriage + (offset++ * BUFF_SIZE)] = 0;
		if (!(buff = realloc(buff, ((offset + 1) * BUFF_SIZE + 1))))
			throw_error(EXIT_FAILURE, "Memory allocation failed!\n", 0);
	}
	return (buff);
}
