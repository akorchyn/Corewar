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

void	throw_error(int error_out, char *str)
{
	ft_putendl_fd(str, 2);
	exit(error_out);
}

int		main(int ac, char **av)
{
	if (ac != 2)
		throw_error(1, "usage: asm source_file");
	else if (av[1][ft_strlen(av[1]) - 1] == 's'
		&& av[1][ft_strlen(av[1]) - 2] == '.')
		read_file(av[1]);
	else
		throw_error(1, "Invalid file extention!\nEample: sorce_file.s");
	return (0);
}