/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembly.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:59:39 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/28 16:59:45 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_header		g_header;
t_op const		g_op_tab[17];

static uint32_t	get_content(char *file_content, uint8_t len)
{
	uint32_t	content;

	content = 0;
	while (len--)
	{
		content = content << 8;
		content = *file_content++;
	}
	return (content);
}

static void		print_argument_codage(uint8_t op_index, uint8_t codage,
		uint8_t **executable_pointer, uint32_t *prog_size)
{
	uint8_t	shift;
	char	type;
	uint8_t arg_len;
	uint8_t arg_count;

	shift = 6;
	arg_count = g_op_tab[op_index].arg_count;
	while (arg_count--)
	{
		if ((codage >> shift & REG_CODE) == REG_CODE)
			type = 'r';
		else if ((codage >> shift & DIR_CODE) == DIR_CODE)
			type = DIRECT_CHAR;
		else
			type = 0;
		arg_len = 2;
		if (type == 'r' || (type == '%' && !g_op_tab[op_index].is_dir_2))
			arg_len = type == 'r' ? 1 : 4;
		ft_printf("%c%d",
				type, get_content((char*)*executable_pointer, arg_len));
		*executable_pointer += arg_len;
		*prog_size -= arg_len;
		ft_printf("%s", (arg_count) ? ", " : "\n");
		shift -= 2;
	}
}

static void		print_argument(uint8_t index,
		uint8_t **ex_pointer, uint32_t *prog_size)
{
	char	type;
	uint8_t	i;
	uint8_t arg_len;
	uint8_t arg_count;

	i = 0;
	arg_count = g_op_tab[index].arg_count;
	while (arg_count--)
	{
		if (g_op_tab[index].arg_code[i] == T_DIR)
			type = DIRECT_CHAR;
		else if (g_op_tab[index].arg_code[i] == T_REG)
			type = 'r';
		else
			type = 0;
		arg_len = 2;
		if (type == 'r' || (type == DIRECT_CHAR && !g_op_tab[index].is_dir_2))
			arg_len = type == 'r' ? 1 : 4;
		ft_printf("%c%d", type, get_content((char*)*ex_pointer, arg_len));
		*ex_pointer += arg_len;
		*prog_size -= arg_len;
		ft_printf("%s", (arg_count) ? ", " : "\n");
		i++;
	}
}

static void		put_code(t_header *header)
{
	uint8_t	op_index;
	uint8_t codage;
	uint8_t	*executable_pointer;

	ft_printf(GREEN"\tDisassembly mode\n\n"EOM);
	ft_printf("Bot name: %s\n", header->prog_name);
	ft_printf("Bot comment: %s\n", header->comment);
	ft_printf("Executable code size: %d\n\nExecutable bot code:\n",
			header->prog_size);
	executable_pointer = header->executable;
	codage = header->prog_size;
	while (header->prog_size)
	{
		op_index = *executable_pointer++ - 1;
		header->prog_size -= (g_op_tab[op_index].has_arg_type) ? 2 : 1;
		ft_printf("%s ", g_op_tab[op_index].op_name);
		codage = (g_op_tab[op_index].has_arg_type) ? *executable_pointer++ : 0;
		if (g_op_tab[op_index].has_arg_type)
			print_argument_codage(op_index, codage,
					&executable_pointer, &header->prog_size);
		else
			print_argument(op_index, &executable_pointer,
					&header->prog_size);
	}
}

void			disassembly(char *file_content)
{
	void *content_pointer;

	content_pointer = file_content;
	ft_bzero(&g_header, sizeof(t_header));
	g_header.magic = get_content(file_content, EXEC_MAGIC_LENGTH);
	file_content += EXEC_MAGIC_LENGTH;
	ft_memcpy(g_header.prog_name, file_content, PROG_NAME_LENGTH);
	file_content += PROG_NAME_LENGTH + 4;
	g_header.prog_size = get_content(file_content, 4);
	file_content += 4;
	ft_memcpy(g_header.comment, file_content, COMMENT_LENGTH);
	file_content += COMMENT_LENGTH + 4;
	g_header.executable = ft_memcpy(malloc(g_header.prog_size), file_content,
			g_header.prog_size);
	free(content_pointer);
	put_code(&g_header);
}
