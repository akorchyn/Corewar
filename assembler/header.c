/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 17:39:21 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/25 17:39:32 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_header	g_header;

void		write_champion(char *file_name)
{
	int		fd;
	size_t	len;
	char	*binary_name;
	char	*num4b;

	len = ft_strlen(file_name) - 1;
	binary_name = ft_memcpy(malloc(len + 4), file_name, len);
	ft_memcpy(binary_name + len, "cor", 4);
	if ((fd = open(binary_name, O_WRONLY | O_CREAT, 0600)) == -1)
		throw_error(14, "Couldn't create file.\n", 0);
	ft_printf(GREEN"Writing champion code into %s\n"EOM, binary_name);
	free(binary_name);
	g_header.magic = COREWAR_EXEC_MAGIC;
	put_bites((uint8_t*)(num4b = malloc(4)), g_header.magic, 4);
	write(fd, num4b, 4);
	write(fd, g_header.prog_name, PROG_NAME_LENGTH);
	write(fd, "\0\0\0\0", 4);
	put_bites((uint8_t*)num4b, g_header.prog_size, 4);
	write(fd, num4b, 4);
	write(fd, g_header.comment, COMMENT_LENGTH);
	write(fd, "\0\0\0\0", 4);
	write(fd, g_header.executable, g_header.prog_size);
	free(num4b);
}

static void	clean_name_comment(t_list *lst, int i)
{
	if (i)
		clean_name_comment(lst->next, i - 1);
	free(GET_INSTRUCTION(lst)->str);
	free(lst->content);
	free(lst);
}

static void	collect_directive(char *str)
{
	char *quote_start;
	char *quote_end;

	quote_end = ft_strrchr(str, '\"');
	quote_start = ft_strchr(str, '\"');
	if (*str == 'c')
	{
		if (quote_end && quote_start &&
		quote_end - quote_start - 1 < COMMENT_LENGTH)
			ft_memcpy(g_header.comment, quote_start + 1,
					quote_end - quote_start - 1);
		else
			throw_error(12, "Invalid comment or it is too long", 0);
	}
	else
	{
		if (quote_end && quote_start &&
			quote_end - quote_start - 1 < PROG_NAME_LENGTH)
			ft_memcpy(g_header.prog_name, quote_start + 1,
					quote_end - quote_start - 1);
		else
			throw_error(12, "Invalid comment or it is too long", 0);
	}
}

void		check_name_comment(t_list *list, t_list **instr_list)
{
	uint8_t	counter;

	counter = 2;
	if (ft_list_size(*instr_list) < 3)
		throw_error(EXIT_FAILURE, "Bad champion(not enough code)\n", 0);
	while (counter-- && list)
	{
		if ((!ft_strncmp(GET_INSTRUCTION(list)->str, NAME_CMD_STRING,
			ft_strlen(NAME_CMD_STRING)) && ft_is_whitespace(
		GET_INSTRUCTION(list)->str + ft_strlen(NAME_CMD_STRING)))
		|| (!ft_strncmp(GET_INSTRUCTION(list)->str, COMMENT_CMD_STRING,
			ft_strlen(COMMENT_CMD_STRING)) && ft_is_whitespace(
		GET_INSTRUCTION(list)->str + ft_strlen(COMMENT_CMD_STRING))))
			collect_directive(GET_INSTRUCTION(list)->str + 1);
		else
			throw_error(12, "First two instructions must include champion's"
			" name and comment!\n", 0);
		list = list->next;
	}
	list = *instr_list;
	*(instr_list) = (*instr_list)->next->next;
	clean_name_comment(list, 1);
}
