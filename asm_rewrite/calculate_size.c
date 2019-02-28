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

t_op	g_op_tab[17];

static int8_t	find_index(char *command)
{
	int8_t	index;

	index = 0;
	while (index < 16)
	{
		if (ft_strequ(g_op_tab[index].name, command))
			return (index);
		index++;
	}
	return (index);
}

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

static void		set_size(t_lexem *lexem, size_t line, int8_t index)
{
	t_list	*argument;
	int8_t	arg_cont;
	size_t	arg_size;

	argument = lexem->argument;
	lexem->size = (g_op_tab[index].has_arg_type) ? 2 : 1;
	arg_cont = 0;
	while (arg_cont < g_op_tab[index].variables)
	{
		if ((arg_size = arg_is_valid(g_op_tab[index].vars[arg_cont],
				argument->content, g_op_tab[index].is_dir_equal_ind)))
			lexem->size += arg_size;
		else
			throw_error(10, "Wrong argument on line ", line);
		argument = argument->next;
		arg_cont++;
	}
	lexem->code = malloc(lexem->size);
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
		op_index = find_index(GET_INSTRUCTION(instruction)->lexem.command);
		if (op_index != -1)
		{
			if (ft_list_size(GET_INSTRUCTION(instruction)->lexem.argument)
				== g_op_tab[op_index].variables)
				set_size(&GET_INSTRUCTION(instruction)->lexem,
					GET_INSTRUCTION(instruction)->line, op_index);
			else
				throw_error(8, "Wrong number of arguments on line ",
					GET_INSTRUCTION(instruction)->line);
		}
		else
			throw_error(9, "Unknown command on line ",
					GET_INSTRUCTION(instruction)->line);
		instruction = instruction->next;
	}
}
