/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 14:09:19 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/23 14:09:28 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op const		g_op_tab[17];

static uint8_t	find_index(char *command)
{
	uint8_t	index;

	index = 0;
	while (index < 16)
	{
		if (ft_strequ(g_op_tab[index].op_name, command))
			return (index);
		index++;
	}
	return ((uint8_t)-1);
}

static void		read_command(t_instruction *instr, char *instruction)
{
	char	*command;
	char	*command_end;

	command_end = instruction;
	while (!ft_is_whitespace(command_end) && *command_end != DIRECT_CHAR
		&& *command_end != SEPARATOR_CHAR && !ft_isdigit(*command_end))
		command_end++;
	if (*command_end)
	{
		command = ft_stralloc(command_end - instruction);
		ft_memcpy(command, instruction, command_end - instruction);
		if ((instr->lexem.op_index = find_index(command)) > 16)
			throw_error(EXIT_FAILURE, "Unknown command. Line ", instr->line_nb);
		free(command);
	}
}

static void		save_argument(char const *start,
		char const *end, t_lexem *lexem)
{
	t_list	*argument;
	size_t	size;

	size = end - start;
	while (ft_is_whitespace(start + size - 1))
		size--;
	argument = ft_lstnew(NULL, 0);
	argument->content = ft_memcpy(ft_stralloc(size), start, size);
	ft_lstadd_end(&lexem->argument, argument);
}

static void		read_argument(t_lexem *lexem, char *instruction)
{
	char	*argument_start;
	char	*argument_end;

	while (*instruction && !ft_is_whitespace(instruction))
		instruction++;
	argument_start = instruction;
	while (argument_start && *argument_start)
	{
		while (ft_is_whitespace(argument_start))
			argument_start++;
		if (!(argument_end = ft_strchr(argument_start, SEPARATOR_CHAR)))
			argument_end = ft_strchr(argument_start, 0);
		save_argument(argument_start, argument_end, lexem);
		if ((argument_start = ft_strchr(argument_end, SEPARATOR_CHAR)))
			argument_start++;
	}
}

void			read_command_argument(t_list *instruction)
{
	while (instruction)
	{
		read_command(instruction->content,
				GET_INSTRUCTION(instruction)->str);
		read_argument(&GET_INSTRUCTION(instruction)->lexem,
				GET_INSTRUCTION(instruction)->str);
		instruction = instruction->next;
	}
}
