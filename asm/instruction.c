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

size_t	get_instruction_size(char const *instruction)
{
	size_t	size;

	size = 0;
	(void)instruction;
//	size = find_command(instruction);
	return (size);
}

void	set_inst_sizes(t_list *inst)
{
	while (inst)
	{
		((t_instruction*)inst->content)->lexem.size =
		get_instruction_size(((t_instruction*)inst->content)->instruction);
		inst = inst->next;
	}
}
