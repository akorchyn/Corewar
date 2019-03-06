/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 00:37:17 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/03/01 00:37:23 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int8_t	is_label(char const *instruction, char const *label,
						const size_t line)
{
	if (instruction != label)
	{
		if (ft_is_whitespace(label - 1) || *(label - 1) == SEPARATOR_CHAR
			|| *(label - 1) == DIRECT_CHAR)
			return (0);
		while (instruction != label)
			if (!ft_strchr(LABEL_CHARS, *instruction++))
				throw_error(5, "Invalid label declaration on line ", line);
	}
	else
		throw_error(3, "Lexical error with label! Line ", line);
	return (1);
}

static int		op_find(void *content1, void *content2)
{
	char *str;

	(void)content2;
	str = ((t_instruction*)content1)->str;
	while (*str)
	{
		if (ft_is_whitespace(str)
			|| *str == DIRECT_CHAR || *str == SEPARATOR_CHAR)
			return (1);
		str++;
	}
	return (0);
}

static void		collect_label(t_list *label_list, char *str, char *label_char)
{
	size_t	label_size;
	t_list	*lst_op;
	char	tmp[(label_size = label_char++ - str) + 1];

	ft_memcpy(tmp, str, label_size);
	tmp[label_size] = 0;
	while (ft_is_whitespace(label_char))
		label_char++;
	ft_memmove(str, label_char, ft_strlen(label_char) + 1);
	if ((lst_op = ft_lstfind(label_list, NULL, op_find)))
		ft_lstadd(&GET_INSTRUCTION(lst_op)->label,
				ft_lstnew(tmp, label_size + 1));
	else
		ft_lstadd(&GET_INSTRUCTION(label_list)->label,
				ft_lstnew(tmp, label_size + 1));
}

void			read_labels(t_list *instr)
{
	char *label_char;

	while (instr)
	{
		if ((label_char = ft_strchr(GET_INSTRUCTION(instr)->str, LABEL_CHAR)))
		{
			if (is_label(GET_INSTRUCTION(instr)->str, label_char,
					GET_INSTRUCTION(instr)->line_nb))
				collect_label(instr,
					GET_INSTRUCTION(instr)->str, label_char);
		}
		instr = instr->next;
	}
}
