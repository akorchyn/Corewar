/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembly.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 14:44:28 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/03/12 14:44:37 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*read_file(char *file_name)
{
	ssize_t	read_ret;
	size_t	offset;
	char	*file;
	int		fd;

	if (!(file = malloc(BUFF_SIZE + 1)))
		throw_error("Memory allocation failed!", 2);
	if ((fd = open(file_name, O_RDONLY)) == -1 || read(fd, file, 0) == -1)
		throw_error("Error on file opening or reading!", 2);
	offset = 0;
	while ((read_ret = read(fd, file + (BUFF_SIZE * offset), BUFF_SIZE)))
	{
		file[read_ret + (BUFF_SIZE * offset++)] = 0;
		if (!(file = realloc(file, (BUFF_SIZE * (offset + 1)) + 1)))
			throw_error("Memory reallocation failed!", 2);
	}
	return (file);
}

void		assembly(char *file_name)
{
	void	*content_pointer;
	char	*file_content;
	t_list	*instr_list;

	content_pointer = read_file(file_name);
	file_content = read_name_comment(content_pointer, 2);
	instr_list = read_instructions(file_content);
}
