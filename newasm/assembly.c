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

void		write_bites(uint8_t *mem, uint32_t value32, uint8_t bites)
{
	uint16_t	value16;

	if (bites == 4)
		while (bites--)
			*mem++ = (uint8_t)(value32 >> (bites * 8));
	else
	{
		value16 = (uint16_t)value32;
		while (bites--)
			*mem++ = (uint8_t)(value16 >> (bites * 8));
	}
}

uint8_t		find_op_index(char *command, size_t command_length)
{
	uint8_t		index;

	index = 0;
	while (index < 16)
	{
		if (ft_strnequ(command, g_op_tab[index].name, command_length))
			return (index);
		index++;
	}
	return (index);
}

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

static void	print_labels(t_list *label)
{
	if (label)
	{
		print_labels(label->next);
		ft_printf("label_name: %s\tlabel_value: %d\n",
				((t_label*)label->content)->label_name,
				((t_label*)label->content)->label_value);
	}
}

static int	create_file(char *file_name)
{
	int		fd;
	uint8_t	*mem4;
	char	*binary_name;

	binary_name = ft_strcat(ft_memcpy(ft_strnew(ft_strlen(file_name) + 2),
			file_name, ft_strlen(file_name + 1)), "cor");
	mem4 = malloc(4);
	if ((fd = open(binary_name, O_WRONLY | O_CREAT, 0b110110110)) == -1)
		throw_error("Error on file creating!", 0);
	write_bites(mem4, g_header.magic, 4);
	write(fd, mem4, 4);
	write(fd, g_header.prog_name, PROG_NAME_LENGTH);
	write(fd, COREWAR_NULL, COREWAR_NULL_LENGTH);
	write_bites(mem4, g_header.prog_size, 4);
	write(fd, mem4, 4);
	write(fd, g_header.comment, COMMENT_LENGTH);
	write(fd, COREWAR_NULL, COREWAR_NULL_LENGTH);
	free(mem4);
	return (fd);
}

void		assembly(char *file_name)
{
	int		fd;
	void	*content_pointer;
	char	*file_content;
	t_list	*instr_list;

	content_pointer = read_file(file_name);
	file_content = read_name_comment(content_pointer, 2);
	instr_list = read_instructions(file_content);
	free(content_pointer);
	fd = create_file(file_name);
	write_executable(fd, instr_list);
	print_labels(g_label_list);
}
