/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 15:23:25 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/03/12 15:23:31 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

size_t		g_line;
char		g_n;
char		g_c;

int			line_not_clear(char const *start, char const *end)
{
	if (end - start > 1)
		while (start != end && *start != ALT_COMMENT_CHAR
			&& *start != COMMENT_CHAR)
			if (!ft_is_whitespace(start++))
				return (1);
	return (0);
}

static void	collect_name(char const *q1, char const *q2,
		const size_t content_size)
{
	if (g_n)
		throw_error("Double name declaration", 0);
	else if (content_size > PROG_NAME_LENGTH)
		throw_error("Too big bot name", 0);
	else
		ft_memcpy(g_header.prog_name, q1 + 1, q2 - q1 - 1);
	g_n = 1;
	while (q1 != q2)
		if (*q1++ == '\n')
			g_line++;
}

static void	collect_comment(char const *q1, char const *q2,
		const size_t content_size)
{
	if (content_size > COMMENT_LENGTH)
		throw_error("Too big bot comment", 0);
	else if (g_c)
		throw_error("Double bot comment declaration", 0);
	else
		ft_memcpy(g_header.comment, q1 + 1, q2 - q1 - 1);
	g_c = 1;
	while (q1 != q2)
		if (*q1++ == '\n')
			g_line++;
}

static char	*collect_directive(char *start)
{
	char	*quote1;
	char	*quote2;

	while (ft_is_whitespace(start) && *start)
		start++;
	quote1 = ft_strchr(start, '\"');
	quote2 = (quote1) ? ft_strchr(quote1 + 1, '\"') : NULL;
	if (!quote2)
		throw_error("bad name or comment", g_line);
	if (!ft_strncmp(start, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING))
			&& ft_is_whitespace(start + ft_strlen(NAME_CMD_STRING)))
		collect_name(quote1, quote2, quote2 - quote1 - 1);
	else if (!ft_strncmp(start, COMMENT_CMD_STRING,
			ft_strlen(COMMENT_CMD_STRING))
			&& ft_is_whitespace(start + ft_strlen(COMMENT_CMD_STRING)))
		collect_comment(quote1, quote2, quote2 - quote1 - 1);
	else
		throw_error("First two instructions must "
				"include bot name and comment!", 0);
	return (quote2 + 1);
}

char		*read_name_comment(char *start, uint8_t counter)
{
	char	*end;

	end = NULL;
	while (counter && start)
	{
		g_line++;
		end = ft_strchr(start, '\n');
		if (line_not_clear(start, end))
		{
			end = collect_directive(start);
			counter--;
		}
		start = (end) ? end + 1 : end;
	}
	return (end);
}
