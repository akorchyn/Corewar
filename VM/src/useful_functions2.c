/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:49:28 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/25 23:05:24 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			print_usage(char **av)
{
	ft_printf("Usage: %s [-dump N -v N] <champion1.cor> <...>\n%s", av[0],
			g_usage);
	exit(0);
}

void			print_dump(uint8_t *map, int16_t bytes_in_line, int16_t size)
{
	int16_t		memory;
	int16_t		i;

	memory = 0;
	ft_printf("0x");
	while (memory < size)
	{
		ft_printf("%#.4x : ", memory);
		i = -1;
		while (++i < bytes_in_line)
			ft_printf("%.2x ", map[memory + i]);
		ft_printf("\n");
		memory += bytes_in_line;
	}
}

int8_t			bad_register_id(t_vars *vars, t_carriage *carriage)
{
	int8_t		i;

	i = -1;
	while (++i < g_op_tab[carriage->op_id].variables)
	{
		if (vars->parsed_codage[i] == T_REG
			&& (vars->vars[i] < 1 || vars->vars[i] > REG_NUMBER))
			return (1);
	}
	return (0);
}

int16_t			shift(t_carriage *carriage, int16_t movement)
{
	return ((carriage->counter + movement % IDX_MOD + MEM_SIZE) % MEM_SIZE);
}