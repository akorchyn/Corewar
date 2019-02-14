/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 18:36:32 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/14 18:36:53 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <stdio.h>

void		read_file(char *file_name)
{
	ssize_t	read_return;
	size_t	offset;
	int		fd;

	if (!(g_file = malloc(BUFF_SIZE)))
		throw_error(11, "Allocation failed!");
	if ((fd = open(file_name, O_RDONLY)) != -1)
	{
		offset = 0;
		while ((read_return = read(fd, g_file + (BUFF_SIZE * offset), BUFF_SIZE)))
		{
			if (read_return == -1)
				throw_error(1, "Error on reading file.");
			g_file[offset++ * BUFF_SIZE + read_return] = 0;
			if (!(g_file = realloc(g_file, BUFF_SIZE)))
				throw_error(11, "Allocation failed!");
			write(1, g_file, ft_strlen(g_file));
		}
	}
	else
		throw_error(1, "Error on file opening!");
}
