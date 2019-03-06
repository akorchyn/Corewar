/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:51:43 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/03/02 17:19:19 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	const g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		6, 6, 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		7, 6, 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		8, 6, 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, 0, 1},
	{"aff", 1, {T_REG}, 16, 2, 1, 0},
	{0, 0, {0}, 0, 0, 0, 0}
};

int		main(int ac, char **av)
{
	t_list	*list;

	if (ac == 2)
	{
		if (check_extension(av[1], ".s", 2))
			assembly(&list, read_file(av[1]), av[1]);
		else
			throw_error(EXIT_FAILURE, "Invalid file extension."
				"\nExample: ./asm \"source_file.s\"\n", 0);
	}
	else if (ac == 3 && !ft_strcmp(av[1], "-d"))
	{
		if (check_extension(av[2], ".cor", 4))
			disassembly(read_file(av[2]));
		else
			throw_error(EXIT_FAILURE, "Invalid file extension."
				"\nExample: ./asm \"source_file.cor\"\n", 0);
	}
	else
		throw_error(EXIT_FAILURE, "usage: [-d] source_file(.s | .cor)\n", 0);
	return (0);
}
