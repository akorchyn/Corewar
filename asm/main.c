/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 18:18:09 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/14 18:18:10 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		throw_error(int error_id, char *str)
{
	ft_putendl_fd(str, 2);
	exit(error_id);
}

static void	write_output(char *file_name)
{
	if (g_instructions)
		ft_lstdel(g_instructions, del_instruction);
	g_instructions = NULL;
	parse_file(file_name);
}

int			main(int ac, char **av)
{
	size_t	arg_len;

	g_instructions = NULL;
	if (ac > 1)
	{
		while (ac--)
			if ((arg_len = ft_strlen(av[ac])) > 2 && av[ac][arg_len - 1] == '.'
			&& av[ac][arg_len - 2] == 's')
				write_output(av[ac]);
			else
			{
				ft_putstr_fd("Invalid extension for ", 2);
				ft_putendl_fd(av[ac], 2);
				ft_putstr_fd("!Example: source_file.s", 2);
			}
	}
	else
		throw_error(1, "usage: ./asm source_file.s");
	return (0);
}
