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
t_op			g_op_tab[17];

static void		print_operation(t_list *operation)
{
	ft_printf("\nindex = %d\t", ((t_instruction*)operation->content)->op_index);
	ft_printf("op_name: %s\n", g_op_tab[((t_instruction*)operation->content)
		->op_index].name);
	ft_printf("size = %d\n", ((t_instruction*)operation->content)->op_size);
	ft_printf("\t\t\tglobal size = %d\n\n\n", g_header.prog_size);
}

static uint8_t	arg_valid(char *str,
		uint8_t argument_code, uint8_t is_dir_ind)
{
	if (*str == REGISTRY_CHAR && (argument_code & T_REG) == T_REG
	&& ft_isnumeric(str++ + 1) && ft_atoi(str) && ft_atoi(str) <= REG_NUMBER)
		return (1);
	else if (*str == DIRECT_CHAR && (argument_code & T_DIR) == T_DIR
	&& ((*(str + 1) == LABEL_CHAR && *(str + 2)) ||
	(*(str + 1) == '-' && ft_isnumeric(str + 2)) || ft_isnumeric(str + 1)))
		return (is_dir_ind ? 2 : 4);
	else if ((argument_code & T_IND) == T_IND &&
	((*str == LABEL_CHAR && *(str + 1)) ||
	((*str == '-' && ft_isnumeric(str + 1)) || ft_isnumeric(str))))
		return (2);
	throw_error("invalid argument", g_line);
	return (0);
}

static void		check_arguments(t_instruction *instr,
		t_list *argument, uint8_t arg_count)
{
	if (arg_count != ft_list_size(argument))
		throw_error("invalid number of arguments", g_line);
	while (arg_count--)
	{
		instr->op_size += arg_valid(argument->content,
				g_op_tab[instr->op_index].argument[arg_count],
				g_op_tab[instr->op_index].ind_dir);
		argument = argument->next;
	}
}

static t_list	*collect_arguments(char *str, t_instruction *instr)
{
	t_list		*arg;
	char		*end;

	arg = NULL;
	while (*str)
	{
		while (ft_is_whitespace(str))
			str++;
		end = str;
		while (*end && !ft_is_whitespace(end) && *end != SEPARATOR_CHAR)
			end++;
		if (end - str)
		{
			ft_lstadd(&arg, ft_lstnew(NULL, 0));
			arg->content = ft_memcpy(ft_stralloc(end - str), str, end - str);
		}
		else
			throw_error("expected expression", g_line);
		while (*end && *end != SEPARATOR_CHAR && ft_is_whitespace(end))
			end++;
		(*end != SEPARATOR_CHAR && !ft_is_whitespace(end))
			? throw_error("expected expression", g_line) : 0;
		str = (*end == SEPARATOR_CHAR && *(end + 1)) ? end + 1 : end;
	}
	check_arguments(instr, arg, g_op_tab[instr->op_index].arg_count);
	return (arg);
}

void			collect_instruction(t_list **instr_list,
		t_instruction *instr, char *instruction)
{
	t_list		*operation;
	char		*command_end;

	command_end = instruction;
	while (!ft_is_whitespace(command_end) && *command_end != DIRECT_CHAR)
		command_end++;
	instr->op_index = find_op_index(instruction, command_end - instruction);
	if (instr->op_index == 16)
		throw_error("unknown command", g_line);
	instr->op_size = (g_op_tab[instr->op_index].has_arg_type) ? 2 : 1;
	instr->argument = collect_arguments(command_end, instr);
	instr->line_nb = g_line;
	instr->size_here = g_header.prog_size;
	operation = ft_lstnew(instr, sizeof(t_instruction));
	print_operation(operation);
	ft_lstadd_end(instr_list, operation);
	g_header.prog_size += instr->op_size;
}
