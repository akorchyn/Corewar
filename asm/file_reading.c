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

char	*g_file;

void	read_file(char *file_name)
{
	ssize_t	read_ret;
	size_t	offset;
	int		fd;

	if (!(g_file = malloc(BUFF_SIZE + 1)))
		throw_error(2, "Memory allocation failed!");
	if ((fd = open(file_name, O_RDONLY)) == -1 || read(fd, g_file, 0) == -1)
		throw_error(2, "Error on file opening or reading!");
	offset = 0;
	while ((read_ret = read(fd, g_file + (BUFF_SIZE * offset++), BUFF_SIZE)))
	{
		g_file[read_ret + (BUFF_SIZE * offset)] = 0;
		if (!(g_file = realloc(g_file, (BUFF_SIZE * (offset + 1)) + 1)))
			throw_error(2, "Memory reallocation failed!");
	}
}
