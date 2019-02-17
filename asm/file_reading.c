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

char	*g_file;
t_list	*g_instructions;

static void	lst_print(t_list *list)
{
	while (list)
	{
		ft_printf("%s\n", ((t_insturction*)list->content)->instruction);
		list = list->next;
	}
}

static int	line_not_clear(char const *start, char const *end)
{
	if (end - start > 1)
		while (start != end)
			if (!ft_is_whitespace(start++))
				return (1);
	return (0);
}

static void	add_instruction(char *start, char *end, t_insturction *instruction)
{
	static t_list	*last = NULL;

	instruction->instruction = ft_memcpy(malloc(end - start),
			(*start == '\n') ? start + 1 : start, end - start - 1);
	instruction->instruction[end - start - 1] = 0;
	if (last)
	{
		last->next = ft_lstnew(instruction, sizeof(t_insturction));
		last = last->next;
	}
	else
		ft_lstadd(&g_instructions,
				(last = ft_lstnew(instruction, sizeof(t_insturction))));
}

void		split_instructions(void)
{
	t_insturction	insturction;
	char			*end;
	char			*start;

	start = g_file;
	ft_bzero(&insturction, sizeof(t_insturction));
	while (start)
	{
		if ((end = ft_strchr(start + 1, '\n')))
			if (line_not_clear(start, end))
				add_instruction(start, end, &insturction);
		start = end;
	}
//	ft_lstiter(g_instructions, lst_print);
lst_print(g_instructions);
}

void		read_file(char *file_name)
{
	ssize_t	read_ret;
	size_t	offset;
	int		fd;

	if (!(g_file = malloc(BUFF_SIZE + 1)))
		throw_error(2, "Memory allocation failed!");
	if ((fd = open(file_name, O_RDONLY)) == -1 || read(fd, g_file, 0) == -1)
		throw_error(2, "Error on file opening or reading!");
	offset = 0;
	while ((read_ret = read(fd, g_file + (BUFF_SIZE * offset), BUFF_SIZE)))
	{
		g_file[read_ret + (BUFF_SIZE * offset++)] = 0;
		if (!(g_file = realloc(g_file, (BUFF_SIZE * (offset + 1)) + 1)))
			throw_error(2, "Memory reallocation failed!");
	}
//	ft_printf("%s", g_file);
	g_instructions = NULL;
}
