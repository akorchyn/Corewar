/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:43:15 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/23 16:43:21 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op const		g_op_tab[17];
t_header		g_header;

static size_t	arg_is_valid(int32_t var,
		char const *argument, int8_t is_dir_equal_ind)
{
	if (*argument == 'r' && (var & T_REG) == T_REG)
		return (REG_BYTE_SIZE);
	else if (*argument == DIRECT_CHAR && (var & T_DIR) == T_DIR)
		return ((is_dir_equal_ind) ? IND_BYTE_SIZE : DIR_BYTE_SIZE);
	else if (*argument != 'r' && *argument != DIRECT_CHAR
			&& (var & T_IND) == T_IND)
		return (IND_BYTE_SIZE);
	return (0);
}

static void		set_size(t_lexem *lexem, size_t line, uint8_t index)
{
	t_list	*argument;
	int8_t	arg_cont;
	size_t	arg_size;

	argument = lexem->argument;
	lexem->size = (g_op_tab[index].has_arg_type) ? 2 : 1;
	arg_cont = 0;
	while (arg_cont < g_op_tab[index].arg_count)
	{
		if ((arg_size = arg_is_valid(g_op_tab[index].arg_code[arg_cont],
				argument->content, g_op_tab[index].is_dir_2)))
			lexem->size += arg_size;
		else
			throw_error(10, "Wrong argument on line ", line);
		argument = argument->next;
		arg_cont++;
	}
	g_header.prog_size += (index != 16) ? lexem->size : 0;
	lexem->code = (index != 16) ? malloc(lexem->size) : NULL;
	(lexem->code) ? *lexem->code = ++index : 0;
	(index == 16) ? lexem->size = 0 : 0;
}

void			put_global_sizes(t_list *instruction)
{
	int32_t	tmp_size;

	tmp_size = 0;
	while (instruction)
	{
		GET_INSTRUCTION(instruction)->size_from_start = tmp_size;
		tmp_size += GET_INSTRUCTION(instruction)->lexem.size;
		instruction = instruction->next;
	}
}

void			calculate_sizes(t_list *instruction)
{
	int8_t	op_index;

	while (instruction)
	{
		op_index = GET_INSTRUCTION(instruction)->lexem.op_index;
		if (op_index < 17)
		{
			if (ft_list_size(GET_INSTRUCTION(instruction)->lexem.argument)
				== g_op_tab[op_index].arg_count)
				set_size(&GET_INSTRUCTION(instruction)->lexem,
					GET_INSTRUCTION(instruction)->line_nb,
					GET_INSTRUCTION(instruction)->lexem.op_index);
			else
				throw_error(8, "Wrong number of arguments on line ",
					GET_INSTRUCTION(instruction)->line_nb);
		}
		else
			throw_error(9, "Unknown command on line ",
					GET_INSTRUCTION(instruction)->line_nb);
		instruction = instruction->next;
	}
}
