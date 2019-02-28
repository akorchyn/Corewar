/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 20:11:25 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/23 20:11:32 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_list	*g_instructions;

static int	find_label(void *content1, void *content2)
{
	t_list	*label;

	label = ((t_instruction*)content1)->label;
	while (label)
	{
		if (!ft_strcmp(label->content, content2))
			return (1);
		label = label->next;
	}
	return (0);
}

static void	change_str(void **label, char *tmp)
{
	size_t	len;
	char	*is_dir;

	is_dir = (*(char*)*label == DIRECT_CHAR) ? "%" : NULL;
	len = ft_strlen(tmp);
	free(*label);
	*label = (is_dir)
			? ft_strcat(ft_memalloc(len + 1), is_dir) : ft_memalloc(len);
	ft_strcat(*label, tmp);
	free(tmp);
}

static void	change_label(void **label, t_list *instruction)
{
	char	*tmp;
	t_list	*needed;

	tmp = (*(char*)*label == DIRECT_CHAR) ? *label + 2 : *label + 1;
	if ((needed = ft_lstfind(g_instructions, tmp, find_label)))
	{
		tmp = ft_itoa(GET_INSTRUCTION(needed)->size_from_start -
				GET_INSTRUCTION(instruction)->size_from_start);
		change_str(label, tmp);
	}
	else
		throw_error(10, "Unknown label. Line ",
				GET_INSTRUCTION(instruction)->line);
}

void		parse_labels(t_list *instruction)
{
	t_list	*argument;

	while (instruction)
	{
		argument = GET_INSTRUCTION(instruction)->lexem.argument;
		while (argument)
		{
			if (*(char*)argument->content == LABEL_CHAR
			|| *((char*)argument->content + 1) == LABEL_CHAR)
				change_label(&argument->content, instruction);
			argument = argument->next;
		}
		instruction = instruction->next;
	}
}
