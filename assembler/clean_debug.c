/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 10:57:45 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/03/14 10:57:50 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		print_labels(t_list *label)
{
	return ;
	if (label)
	{
		print_labels(label->next);
		ft_printf("label_name: %s\tlabel_value: %d\n",
				((t_label*)label->content)->label_name,
				((t_label*)label->content)->label_value);
	}
}

void		print_operation(t_list *operation)
{
	return ;
	ft_printf("\nindex = %d\t", ((t_instruction*)operation->content)->op_index);
	ft_printf("op_name: %s\n", g_op_tab[((t_instruction*)operation->content)
			->op_index].name);
	ft_printf("size = %d\n", ((t_instruction*)operation->content)->op_size);
	ft_printf("\t\t\tglobal size = %d\n\n\n", g_header.prog_size);
}

static void	clean_argument(t_list *argument)
{
	if (argument)
	{
		clean_argument(argument->next);
		free(argument->content);
		free(argument);
	}
}

void		clean_labels(t_list *label)
{
	if (label)
	{
		clean_labels(label->next);
		free(((t_label*)label->content)->label_name);
		free(label->content);
		free(label);
	}
}

void		clean_instr(t_list *instr)
{
	if (instr)
	{
		clean_instr(instr->next);
		clean_argument(((t_instruction*)instr->content)->argument);
		free(instr->content);
		free(instr);
	}
}
