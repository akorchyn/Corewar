/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 15:43:25 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/03/13 15:43:31 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op		g_op_tab[17];
t_header	g_header;
t_list		*g_label_list;

static char		get_arg_type(uint8_t op_index, t_instruction *instr)
{
	uint8_t	arg_count;
	uint8_t	shift;
	t_list	*argument;
	char	result;

	arg_count = g_op_tab[op_index].arg_count;
	shift = 6;
	argument = instr->argument;
	result = 0;
	while (arg_count--)
	{
		if (*(char*)argument->content == DIRECT_CHAR)
			result |= DIR_CODE << shift;
		else if (*(char*)argument->content == REGISTRY_CHAR)
			result |= REG_CODE << shift;
		else
			result |= IND_CODE << shift;
		argument = argument->next;
		shift -= 2;
	}
	return (result);
}

int				label_find(void *lst_content, void *content)
{
	return (!ft_strcmp(content, ((t_label*)lst_content)->label_name));
}

static uint32_t	get_arg_value(char *argument, t_instruction *instr)
{
	t_list	*label;

	if (*argument == LABEL_CHAR
		|| (*argument == DIRECT_CHAR && *(argument + 1) == LABEL_CHAR))
	{
		if (!(label = ft_lstfind(g_label_list, (*argument == DIRECT_CHAR)
				? argument + 2 : argument + 1, label_find)))
			throw_error("unknown label", instr->line_nb);
		return (((t_label*)label->content)->label_value - instr->size_here);
	}
	return (*argument == DIRECT_CHAR || *argument == REGISTRY_CHAR
		? (uint32_t)ft_atoi(argument + 1) : (uint32_t)ft_atoi(argument));
}

static void		put_arguments(int fd, uint8_t dir_ind, t_list *argument,
		t_instruction *instr)
{
	uint32_t	arg_value;
	uint8_t		arg_size;
	uint8_t		*mem;

	mem = malloc(4);
	while (argument)
	{
		if (*(char*)argument->content == DIRECT_CHAR)
			arg_size = dir_ind ? 2 : 4;
		else if (*(char*)argument->content == REGISTRY_CHAR)
			arg_size = 1;
		else
			arg_size = 2;
		arg_value = get_arg_value(argument->content, instr);
		write_bites(mem, arg_value, arg_size);
		write(fd, mem, arg_size);
		argument = argument->next;
	}
	free(mem);
}

void			write_executable(int fd, t_list *instr_list)
{
	uint8_t	op_index;

	while (instr_list)
	{
		op_index = ((t_instruction*)instr_list->content)->op_index;
		ft_putchar_fd(op_index + 1, fd);
		ft_lstrev(&((t_instruction*)instr_list->content)->argument);
		if (g_op_tab[op_index].has_arg_type)
			ft_putchar_fd(get_arg_type(op_index, instr_list->content), fd);
		put_arguments(fd, g_op_tab[op_index].ind_dir,
				((t_instruction*)instr_list->content)->argument,
				instr_list->content);
		instr_list = instr_list->next;
	}
}
