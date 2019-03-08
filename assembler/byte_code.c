/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 17:28:04 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/03/08 16:12:25 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op const	g_op_tab[17];

void		put_bites(uint8_t *memory, uint32_t argument, uint8_t arg_len)
{
	uint16_t	arg_tmp;

	arg_tmp = (uint16_t)argument;
	if (arg_len == 4)
		while (arg_len--)
			*memory++ = (uint8_t)((argument >> (arg_len * 8)));
	else
		while (arg_len--)
			*memory++ = (uint8_t)((arg_tmp >> (arg_len * 8)));
}

static void	put_codage(uint8_t *codage_byte, t_list *argument)
{
	uint8_t	codage;
	uint8_t	shift;

	shift = 6;
	codage = 0;
	while (argument)
	{
		if (*(char*)argument->content == 'r')
			codage |= REG_CODE << shift;
		else if (*(char*)argument->content == DIRECT_CHAR)
			codage |= DIR_CODE << shift;
		else
			codage |= IND_CODE << shift;
		shift -= 2;
		argument = argument->next;
	}
	*codage_byte = codage;
}

static void	put_arguments(uint8_t *memory, t_list *argument, int8_t dir_ind)
{
	while (argument)
	{
		if (*(char*)argument->content == 'r')
			*memory++ = (uint8_t)ft_atoi(argument->content + 1);
		else if (*(char*)argument->content == DIRECT_CHAR && !dir_ind)
		{
			put_bites(memory, (uint32_t)ft_atoi(argument->content + 1), 4);
			memory += 4;
		}
		else
		{
			put_bites(memory, (uint32_t)ft_atoi(argument->content +
					(*(char*)argument->content == DIRECT_CHAR ? 1 : 0)), 2);
			memory += 2;
		}
		argument = argument->next;
	}
}

void		parse_inst_code(t_list *lst)
{
	int8_t	counter;
	int8_t	op_index;

	while (lst)
	{
		counter = 1;
		op_index = (GET_INSTRUCTION(lst)->lexem.code)
				? (*GET_INSTRUCTION(lst)->lexem.code - (int8_t)1) : 16;
		if (op_index != 16)
		{
			if (g_op_tab[op_index].has_arg_type)
				put_codage(&GET_INSTRUCTION(lst)->lexem.code[counter++],
						GET_INSTRUCTION(lst)->lexem.argument);
			put_arguments(&GET_INSTRUCTION(lst)->lexem.code[counter],
						GET_INSTRUCTION(lst)->lexem.argument,
						g_op_tab[op_index].is_dir_2);
		}
		lst = lst->next;
	}
}
