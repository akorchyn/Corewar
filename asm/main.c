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

void	throw_error(int error_id, char *str)
{
	ft_putendl_fd(str, 2);
	exit(error_id);
}

int		main(int ac, char **av)
{
	g_instructions = NULL;
	if (ac != 2)
		throw_error(1, "usage: ./asm source_file");
	else if (av[1][ft_strlen(av[1]) - 1] == 's'
			&& av[1][ft_strlen(av[1]) - 2] == '.')
		parse_file(av[1], NULL);
	else
		throw_error(1, "Invalid file extension!\nExample: source_file.s");
	return (0);
}
