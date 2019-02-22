/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:57:28 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/21 16:57:36 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

static int8_t	is_label(char const *instruction, char const *label)
{
	while (instruction != label)
		if (!ft_strchr(LABEL_CHARS, *instruction++))
			return (0);
	return (1);
}

static int		is_instruction(void *content1, void *content2)
{
	return (ft_strchr(((t_instruction*)content1)->instruction,
			*(char*)content2) != NULL);
}

static void		add_label(t_list *inst, t_instruction *instr, char *label)
{
	t_list	*this_nst;

	this_nst = ft_lstfind(inst, " ", is_instruction);
	ft_lstadd((this_nst) ? &((t_instruction*)this_nst->content)->label
			: &instr->label, ft_lstnew(instr->instruction,
			label - instr->instruction + 1));
	if (this_nst)
		((char*)((t_instruction*)this_nst->content)->label->content)
		[label - instr->instruction] = 0;
	else
		((char*)instr->label->content)[label - instr->instruction] = 0;
	ft_cycle_move(instr->instruction, 1, (int)ft_strlen(instr->instruction),
		-1 * ((int)(label - instr->instruction + 1)));
	instr->instruction[ft_strlen(instr->instruction) -
		(label - instr->instruction) - 1] = 0;
}

void			read_labels(t_list *inst)
{
	char	*label;

	while (inst)
	{
		if ((label = ft_strchr(((t_instruction*)inst->content)->instruction,
		LABEL_CHAR)) && is_label(GET_INSTRUCTION(inst)->instruction, label))
			add_label(inst, inst->content, label);
		inst = inst->next;
	}
}
