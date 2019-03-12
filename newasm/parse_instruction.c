/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 18:51:50 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/03/12 18:51:56 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

size_t			g_line;
t_header		g_header;

static void		print_operation(t_list *operation)
{
	ft_printf("\nindex = %d\t", ((t_instruction*)operation->content)->op_index);
	ft_printf("op_name: %s\n", g_op_tab[((t_instruction*)operation->content)
		->op_index].name);
	ft_printf("size = %d\n", ((t_instruction*)operation->content)->op_size);
	ft_printf("\t\t\tglobal size = %d\n\n\n", g_header.prog_size);
}

static void		check_arguments(t_instruction *instr,
		t_list *argument, uint8_t arg_count)
{
	uint8_t		arg_sz;

	if (arg_count != ft_list_size(argument))
		throw_error("invalid number of arguments", g_line);
	while (arg_count--)
	{

	}
}

static t_list	*collect_arguments(char *str, t_instruction *instr)
{
	t_list		*argument;
	char		*arg_end;

	argument = NULL;
	while (*str)
	{
		while (ft_is_whitespace(str))
			str++;
		arg_end = str;
		while (*arg_end && !ft_is_whitespace(arg_end)
				&& *arg_end != SEPARATOR_CHAR)
			arg_end++;
		ft_lstadd(&argument, ft_lstnew(NULL, 0));
		argument->content =
				ft_memcpy(ft_stralloc(arg_end - str), str, arg_end - str);
		str = (*arg_end == SEPARATOR_CHAR) ? arg_end + 1 : arg_end;
	}
	check_arguments(instr, argument, g_op_tab[instr->op_index].arg_count);
	return (argument);
}

static uint8_t	find_op_index(char *command, size_t command_length)
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

void			collect_instruction(t_list **instr_list,
		t_instruction *instr, char *instruction)
{
	t_list		*operation;
	char		*command_end;

	command_end = instruction;
	while (!ft_is_whitespace(command_end) && *command_end != DIRECT_CHAR)
		command_end++;
	instr->op_index = find_op_index(instruction, command_end - instruction - 1);
	if (instr->op_index == 16)
		throw_error("unknown command", g_line);
	instr->op_size = (g_op_tab[instr->op_index].has_arg_type) ? 2 : 1;
	instr->argument = collect_arguments(command_end, instr);
	operation = ft_lstnew(instr, sizeof(t_instruction));
	print_operation(operation);
	ft_lstadd_end(instr_list, operation);
	g_header.prog_size += instr->op_size;
}
