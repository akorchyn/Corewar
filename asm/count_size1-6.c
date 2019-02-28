/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_size1-5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 23:03:53 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/22 23:04:01 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	count_live(t_lexem *lexem, size_t line)
{
	(void)line;
	lexem->size = 1;
	lexem->size += DIR_SIZE;
}

void	count_ld(t_lexem *lexem, size_t line)
{
	lexem->size = 2;
	if (*(char*)lexem->argument->content == 'r'
		&& ft_isnumeric(lexem->argument->content + 1))
		lexem->size += 1;
	else
		throw_error(7, "Invalid argument where registry is required ", line);
	lexem->size += (*(char*)lexem->argument->next->content == DIRECT_CHAR)
			? DIR_SIZE : IND_SIZE;
}

void	count_st(t_lexem *lexem, size_t line)
{
	lexem->size = 2;
	lexem->size += (*(char*)lexem->argument->content == 'r')
			? REG_SIZE : IND_SIZE;
	if (*(char*)lexem->argument->next->content == 'r'
		&& ft_isnumeric(lexem->argument->content + 1))
		lexem->size += 1;
	else
		throw_error(7, "Invalid argument where registry is required ", line);
}

void	count_add(t_lexem *lexem, size_t line)
{
	t_list	*tmp;

	lexem->size = 2 + REG_SIZE * 3;
	tmp = lexem->argument;
	while (tmp)
	{
		if (*(char*)tmp->content != 'r')
			throw_error(7, "Invalid argument where registry is required ", line);
		tmp = tmp->next;
	}
}

void	count_sub(t_lexem *lexem, size_t line)
{
	(void)lexem;
	(void)line;
}
