/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_instr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:50:27 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/28 17:50:32 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*check_comment(char *start, char *end)
{
	char	*reg_comment;
	char	*alt_comment;

	reg_comment = ft_strnchr(start, COMMENT_CHAR, end - start);
	alt_comment = ft_strnchr(start, ALT_COMMENT_CHAR, end - start);
	if (reg_comment || alt_comment)
	{
		reg_comment--;
		alt_comment--;
		return (MIN(reg_comment, alt_comment) + 1);
	}
	return (end);
}

static char	*get_clear_instr(char *start, char *end)
{
	char	*buff;
	size_t	size;

	end = check_comment(start, end);
	while (ft_is_whitespace(start))
		start++;
	while (ft_is_whitespace(end - 1))
		end--;
	size = end - start;
	buff = ft_memcpy(malloc(size + 1), start, size);
	buff[size] = 0;
	return (buff);
}

static void	collect_instruction(t_list **instr_list, size_t line,
			char *instr_content, t_instruction *instruction)
{
	instruction->str = instr_content;
	instruction->line_nb = line;
	ft_lstadd_end(instr_list, ft_lstnew(instruction, sizeof(t_instruction)));
}

static int	line_not_clear(char *start, char const *end)
{
	if (end - start)
		while (end - start)
			if (!ft_is_whitespace(start++))
				return (1);
	return (0);
}

t_list		*split_instr(char *file_content)
{
	t_list			*instr_list;
	t_instruction	instruction;
	char			*start;
	char			*end;
	size_t			line;

	instr_list = NULL;
	ft_bzero(&instruction, sizeof(t_instruction));
	start = file_content;
	line = 0;
	while (start)
	{
		line++;
		end = ft_strchr(start, '\n');
		if (end)
			(*start != COMMENT_CHAR && *start != ALT_COMMENT_CHAR
				&& line_not_clear(start, check_comment(start, end)))
			? collect_instruction(&instr_list, line,
					get_clear_instr(start, end), &instruction) : 0;
		else
			(ft_strlen(start) > 0) ? throw_error(EXIT_FAILURE,
					"Expected \'\\n\' on line ", line) : 0;
		start = (end) ? end + 1 : end;
	}
	return (instr_list);
}
