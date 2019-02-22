/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 18:36:32 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/14 18:36:53 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_list	*g_instructions;

static int		line_not_clear(char const *start, char const *end)
{
	if (end - start > 1)
		while (start != end &&
		*start != ALT_COMMENT_CHAR && *start != COMMENT_CHAR)
			if (!ft_is_whitespace(start++))
				return (1);
	return (0);
}

static size_t	get_instruction_size(char const *start, char *end)
{
	size_t	size;
	char	*comment;
	char	*alt_comment;

	size = end - start;
	comment = ft_strnchr(start, COMMENT_CHAR, end - start);
	alt_comment = ft_strnchr(start, ALT_COMMENT_CHAR, end - start);
	comment = (!comment) ? alt_comment : comment;
	comment = (alt_comment) ? MIN(comment, alt_comment) : comment;
	size = (comment) ? comment - start : size;
	while (ft_is_whitespace(start - 1 + size))
		size--;
	return (size);
}

static void		add_instruction(char const *start, char *end,
		t_instruction *instruction, const size_t line)
{
	size_t			instruction_size;
	static t_list	*last = NULL;

	while (ft_is_whitespace(start))
		start++;
	instruction_size = get_instruction_size(start, end);
	instruction->instruction = ft_memcpy(malloc(instruction_size + 1),
			start, instruction_size);
	instruction->instruction[instruction_size] = 0;
	instruction->line = line;
	if (last)
	{
		last->next = ft_lstnew(instruction, sizeof(t_instruction));
		last = last->next;
	}
	else
		ft_lstadd(&g_instructions,
				(last = ft_lstnew(instruction, sizeof(t_instruction))));
}

static void		split_instructions(char *file)
{
	size_t			line;
	t_instruction	instruction;
	char			*end;
	char			*start;

	start = file;
	line = 0;
	ft_bzero(&instruction, sizeof(t_instruction));
	while (start)
	{
		++line;
		if ((end = ft_strchr(start, '\n')))
		{
			if (line_not_clear(start, end))
				add_instruction(start, end, &instruction, line);
		}
		else
			(line_not_clear(start, start + ft_strlen(start)))
				? throw_error(2, "Lexical error on line ", line) : 0;
		start = (end) ? end + 1 : end;
	}
	free(file);
}

void			parse_file(char *file_name)
{
	ssize_t	read_ret;
	size_t	offset;
	char	*file;
	int		fd;

	if (!(file = malloc(BUFF_SIZE + 1)))
		throw_error(2, "Memory allocation failed!\n", 0);
	if ((fd = open(file_name, O_RDONLY)) == -1 || read(fd, file, 0) == -1)
		throw_error(2, "Error on file opening or reading!\n", 0);
	offset = 0;
	while ((read_ret = read(fd, file + (BUFF_SIZE * offset), BUFF_SIZE)))
	{
		file[read_ret + (BUFF_SIZE * offset++)] = 0;
		if (!(file = realloc(file, (BUFF_SIZE * (offset + 1)) + 1)))
			throw_error(2, "Memory reallocation failed!\n", 0);
	}
	split_instructions(file);
}
