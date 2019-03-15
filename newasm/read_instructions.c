/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 17:31:09 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/03/12 17:31:14 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

size_t		g_line;
t_header	g_header;
t_list		*g_label_list;

char			*get_clear_string(char const *start, char const *end)
{
	char *alt_comment;
	char *reg_comment;

	while (ft_is_whitespace(start))
		start++;
	alt_comment = ft_strnchr(start, ALT_COMMENT_CHAR, end - start);
	reg_comment = ft_strnchr(start, COMMENT_CHAR, end - start);
	if (alt_comment || reg_comment)
	{
		alt_comment--;
		reg_comment--;
		end = MIN(alt_comment, reg_comment);
	}
	while (ft_is_whitespace(end))
		end--;
	return (ft_memcpy(ft_stralloc(end - start + 1), start, end - start + 1));
}

static void		collect_label(char *instruction, char *label_char)
{
	t_label	label;

	label.label_name = ft_memcpy(ft_stralloc(label_char - instruction),
			instruction, label_char - instruction);
	if (ft_lstfind(g_label_list, label.label_name, label_find))
		throw_error("double label declaration", g_line);
	label.label_value = g_header.prog_size;
	ft_lstadd(&g_label_list, ft_lstnew(&label, sizeof(t_label)));
	while (ft_is_whitespace(label_char + 1))
		label_char++;
	ft_cycle_move(instruction, 1, ft_strlen(instruction),
			-(label_char - instruction + 1));
	instruction[ft_strlen(instruction) - (label_char - instruction) - 1] = 0;
}

static uint8_t	valid_label(char const *instruction, char *label_char)
{
	if (label_char - instruction)
	{
		while (--label_char != instruction)
			if (!ft_strchr(LABEL_CHARS, *label_char))
				throw_error("invalid label declaration.", g_line);
	}
	else
		throw_error("invalid label declaration.", g_line);
	return (1);
}

static char		check_label(char *instruction)
{
	char	*label_char;

	label_char = instruction;
	while (*label_char && *label_char != LABEL_CHAR)
	{
		if (ft_is_whitespace(label_char) || *label_char == SEPARATOR_CHAR
			|| *label_char == DIRECT_CHAR)
			return (*label_char);
		label_char++;
	}
	valid_label(instruction, label_char);
	collect_label(instruction, label_char);
	return (*instruction);
}

t_list			*read_instructions(char *start)
{
	t_instruction	instr;
	t_list			*instr_list;
	char			*instruction;
	char			*end;

	instr_list = NULL;
	ft_bzero(&instr, sizeof(t_instruction));
	while (start)
	{
		end = ft_strchr(start, '\n');
		if (end)
		{
			instruction = (line_not_clear(start, end))
					? get_clear_string(start, end) : NULL;
			if (instruction && check_label(instruction))
				collect_instruction(&instr_list, &instr, instruction);
			ft_strdel(&instruction);
		}
		else if (line_not_clear(start, ft_strchr(start, 0)))
			throw_error("expected \\n", g_line);
		g_line++;
		start = (end) ? end + 1 : end;
	}
	return (instr_list);
}
