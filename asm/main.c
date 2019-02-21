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

static void	print_labels(t_list *lst)
{
	while (lst)
	{
		ft_printf("\t%s\n", lst->content);
		lst = lst->next;
	}
}

static void	lst_print(t_list *list)
{
	while (list)
	{
		ft_printf("%s\n", ((t_instruction*)list->content)->instruction);
		print_labels(((t_instruction*)list->content)->label);
		list = list->next;
	}
}

static void	write_output(char *file_name)
{
	parse_file(file_name);
	lst_print(g_instructions);
	read_labels(g_instructions);
	lst_print(g_instructions);
	set_inst_sizes(g_instructions);
}

int			main(int ac, char **av)
{
	size_t	arg_len;

	g_instructions = NULL;
	if (ac-- == 2)
	{
		if ((arg_len = ft_strlen(av[ac])) > 1
		&& av[ac][arg_len - 1] == 's' && av[ac][arg_len - 2] == '.')
			write_output(av[ac]);
		else
		{
			ft_putstr_fd("Invalid extension for ", 2);
			ft_putstr_fd(av[ac], 2);
			ft_putendl_fd("! Example: source_file.s", 2);
		}
	}
	else
		throw_error(1, "usage: ./asm source_file.s");
	return (0);
}
