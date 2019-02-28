/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:29:17 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/21 16:29:33 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op			g_op_tab[17];
t_size_count	g_size_count_array[16];

static void		initialise_size_count_array(void)
{
	g_size_count_array[0] = count_live;
	g_size_count_array[1] = count_ld;
	g_size_count_array[2] = count_st;
	g_size_count_array[3] = count_add;
	g_size_count_array[4] = count_add;
}

static int8_t	find_op_index(t_lexem *lexem)
{
	int8_t	variable;

	variable = 0;
	while (variable < 17)
	{
		ft_printf("%s\n", lexem->command);
		if (ft_strequ(g_op_tab[variable].name, lexem->command))
			return (variable);
		variable++;
	}
	return (-1);
}

static void		read_arguments(t_instruction *instruction,
		char *argument, t_lexem *lexem)
{
	char *separator;

	while (*argument && ft_is_whitespace(argument))
		argument++;
	if (*argument)
		while (argument)
		{
			separator = ft_strchr(argument, SEPARATOR_CHAR);
			ft_lstadd(&lexem->argument, ft_lstnew(argument, ((separator)
				? separator - argument : ft_strlen(argument)) + 1));
			((char*)lexem->argument->content)[(separator)
				? separator - argument : ft_strlen(argument)] = 0;
			argument = (separator) ? separator + 1 : separator;
			while (argument && *argument && ft_is_whitespace(argument))
				argument++;
		}
	else
		throw_error(4, "Error with arguments! Line ", instruction->line);
}

static void		parse_lexem(t_instruction *instruction)
{
	char	*delimeter;

	delimeter = instruction->instruction;
	while (*delimeter && ft_is_whitespace(delimeter))
		delimeter++;
	if (*delimeter)
	{
		instruction->lexem.command = ft_memcpy(ft_strnew(delimeter -
				instruction->instruction), instruction->instruction,
					delimeter - instruction->instruction);
		instruction->lexem.command[delimeter - instruction->instruction] = 0;
		read_arguments(instruction, delimeter, &instruction->lexem);
	}
}

void			set_inst_sizes(t_list *inst)
{
	int8_t	op_index;

	initialise_size_count_array();
	while (inst)
	{
		parse_lexem(inst->content);
		op_index = find_op_index(&GET_INSTRUCTION(inst)->lexem);
		if (op_index != -1 &&
			ft_list_size(GET_INSTRUCTION(inst)->lexem.argument)
			!= g_op_tab[op_index].variables)
			throw_error(7, "Unexpected number of arguments, line ",
					GET_INSTRUCTION(inst)->line);
		if (op_index != -1)
			g_size_count_array[op_index](&GET_INSTRUCTION(inst)->lexem,
					GET_INSTRUCTION(inst)->line);
		else
			throw_error(6, "Unknown command on line ",
					GET_INSTRUCTION(inst)->line);
		inst = inst->next;
	}
}
