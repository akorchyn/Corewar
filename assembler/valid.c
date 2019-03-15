/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 14:35:51 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/03/15 13:19:41 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	throw_error(char *error, size_t line)
{
	ft_putstr_fd(RED, 2);
	if (line)
	{
		ft_putstr_fd("Error on line ", 2);
		ft_putnbr_fd(line, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(error, 2);
	ft_putstr_fd(EOM, 2);
	exit(1);
}

void	check_labels(t_list *label_list, t_list *op_list)
{
	t_list *argument;

	while (op_list)
	{
		argument = ((t_instruction*)op_list->content)->argument;
		while (argument)
		{
			if (*((char*)argument->content) == LABEL_CHAR
			&& !ft_lstfind(label_list, argument->content + 1, label_find))
				throw_error("unknown label",
				((t_instruction*)op_list->content)->line_nb);
			argument = argument->next;
		}
		op_list = op_list->next;
	}
}

uint8_t	check_extension(char *file_name, char *extension)
{
	return (ft_strequ(file_name + ft_strlen(file_name)
			- ft_strlen(extension), extension));
}
