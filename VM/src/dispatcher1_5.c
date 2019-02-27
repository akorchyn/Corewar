/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command1_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:40:09 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/25 22:37:23 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int32_t			g_id;

void		live(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	if (corewar->verbose & 4)
		ft_printf("P% 5d | live %d\n", carriage->p_number, vars->vars[0]);
	corewar->count_live_for_cycle++;
	carriage->last_live = corewar->iteration;
	if (vars->vars[0] == -carriage->id)
	{
		if (corewar->verbose & 1)
			ft_printf("Player %d (%s) is said to be alive\n",
					carriage->id, carriage->header->prog_name);
		corewar->player_last_live = carriage->id;
	}
}

void		ld(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	if (bad_register_id(vars, carriage))
		return ;
	if (vars->parsed_codage[0] == T_DIR)
	{
		carriage->reg[vars->vars[1] - 1] = vars->vars[0];
		if (corewar->verbose & 4)
			ft_printf("P% 5d | ld %d r%hd\n", carriage->p_number,
					carriage->reg[vars->vars[1] - 1], vars->vars[1]);
	}
	else
	{
		carriage->reg[vars->vars[1] - 1] = bytes_to_dec(corewar->map,
				shift(carriage, vars->vars[0]), REG_SIZE);
		if (corewar->verbose & 4)
			ft_printf("P% 5d | ld %hd r%hd\n", carriage->p_number,
					carriage->reg[vars->vars[1] - 1], vars->vars[1]);
	}
	carriage->carry = (uint8_t)((carriage->reg[vars->vars[1] - 1]) ? 0 : 1);
}

void		st(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	if (bad_register_id(vars, carriage))
		return ;
	if (vars->parsed_codage[1] == REG_CODE)
	{
		carriage->reg[vars->vars[1] - 1] = carriage->reg[vars->vars[0] - 1];
		if (corewar->verbose & 4)
			ft_printf("P% 5d | st r%hd r%hd\n", carriage->p_number,
					vars->vars[0], vars->vars[1]);
		return ;
	}
	put_bytes(carriage->reg[vars->vars[0] - 1], corewar->map,
						shift(carriage, vars->vars[1]), REG_SIZE);
	if (corewar->verbose & 4)
		ft_printf("P% 5d | st r%hd %hd\n", carriage->p_number, vars->vars[0],
				vars->vars[1]);
}

void		add(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	if (bad_register_id(vars, carriage))
		return ;
	carriage->reg[vars->vars[2] - 1] = carriage->reg[vars->vars[0] - 1]
									+ carriage->reg[vars->vars[1] - 1];
	carriage->carry = (carriage->reg[vars->vars[2] - 1]) ? 0 : 1;
	if (corewar->verbose & 4)
		ft_printf("P% 5d | add r%d r%d r%d\n", carriage->p_number,
				vars->vars[0], vars->vars[1], vars->vars[2]);
}

void		sub(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	if (bad_register_id(vars, carriage))
		return ;
	carriage->reg[vars->vars[2] - 1] = carriage->reg[vars->vars[0] - 1]
									- carriage->reg[vars->vars[1] - 1];
	carriage->carry = (carriage->reg[vars->vars[2] - 1]) ? 0 : 1;
	if (corewar->verbose & 4)
		ft_printf("P% 5d | sub r%hd r%hd r%hd\n", carriage->p_number,
				vars->vars[0], vars->vars[1], vars->vars[2]);
}
