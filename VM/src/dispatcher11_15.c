/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher11_15.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:45:32 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/27 16:52:41 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		sti(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int32_t		values[2];

	if (bad_register_id(vars, carriage))
		return ;
	if (vars->parsed_codage[1] == T_REG)
		values[0] = carriage->reg[vars->vars[1] - 1];
	else if (vars->parsed_codage[1] == T_IND)
		values[0] = bytes_to_dec(corewar->map, shift(carriage, vars->vars[1]),
													REG_SIZE);
	else
		values[0] = vars->vars[1];
	values[1] = (vars->parsed_codage[2] == T_REG)
				? carriage->reg[vars->vars[2] - 1] : vars->vars[2];
	put_bytes(carriage->reg[vars->vars[0] - 1], corewar->map,
							shift(carriage, values[0] +
								values[1]), REG_SIZE);
	if (corewar->verbose & 4)
		ft_printf("P% 5d | sti r%d %d %d\n       | -> store to %d + %d = "
			"%d (with pc and mod %d)\n", carriage->p_number, vars->vars[0],
			values[0], values[1], values[0], values[1], values[0] + values[1],
				  carriage->counter + (values[0] + values[1]) % IDX_MOD);
}

void		forks(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	t_carriage		*nw;

	if (!(nw = (t_carriage *)ft_memalloc(sizeof(t_carriage))))
		error(55, "Allocation memory to new carriage failed.", NULL);
	ft_memcpy(nw, carriage, sizeof(t_carriage));
	nw->counter = shift(carriage, vars->vars[0]);
	nw->next = corewar->carriages;
	nw->op_id = 0;
	nw->p_number = ++g_id;
	corewar->carriages->prev = nw;
	nw->prev = NULL;
	corewar->carriages = nw;
	if (corewar->verbose & 4)
		ft_printf("P% 5d | fork %d (%d)\n", carriage->p_number, vars->vars[0],
				  (carriage->counter + vars->vars[0] % IDX_MOD) % MEM_SIZE);
}

void		lld(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int32_t		addr;

	if (bad_register_id(vars, carriage))
		return ;
	if (vars->parsed_codage[0] == T_DIR)
	{
		carriage->reg[vars->vars[1] - 1] = vars->vars[0];
		carriage->carry = (vars->vars[0]) ? 0 : 1;
		if (corewar->verbose & 4)
			ft_printf("P% 5d | lld %d r%d\n", carriage->p_number, vars->vars[0],
					vars->vars[1]);
		return ;
	}
	addr = (carriage->counter + (int16_t)vars->vars[0] + MEM_SIZE) % MEM_SIZE;
	carriage->reg[vars->vars[1] - 1] = bytes_to_dec(corewar->map, addr,
			REG_SIZE);
	carriage->carry = carriage->reg[vars->vars[1] - 1] ? 0 : 1;
	if (corewar->verbose & 4)
		ft_printf("P% 5d | lld %d r%d\n", carriage->p_number, vars->vars[0],
				vars->vars[1]);
}

void		lldi(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int32_t		values[2];

	if (bad_register_id(vars, carriage))
		return ;
	if (vars->parsed_codage[0] == T_REG)
		values[0] = carriage->reg[vars->vars[0] - 1];
	else if (vars->parsed_codage[0] == T_IND)
		values[0] = bytes_to_dec(corewar->map, shift(carriage, vars->vars[0]),
				REG_SIZE);
	else
		values[0] = vars->vars[0];
	values[1] = (vars->parsed_codage[1] == T_REG) ?
				carriage->reg[vars->vars[1] - 1] : vars->vars[1];
	carriage->reg[vars->vars[2] - 1] = bytes_to_dec(corewar->map,
		(carriage->counter + values[0] + values[1] + MEM_SIZE) % MEM_SIZE,
													REG_SIZE);
	carriage->carry = carriage->reg[vars->vars[2] - 1] ? 0 : 1;
	if (corewar->verbose & 4)
		ft_printf("P% 5d | lldi %d %d r%d\n", carriage->p_number, values[0],
				values[1], vars->vars[2]);
}

void		lfork(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	t_carriage		*nw;

	if (!(nw = (t_carriage *)ft_memalloc(sizeof(t_carriage))))
		error(55, "Allocation memory to new carriage failed.", NULL);
	ft_memcpy(nw, carriage, sizeof(t_carriage));
	nw->counter = (nw->counter + (int16_t)vars->vars[0] + MEM_SIZE) % MEM_SIZE;
	nw->next = corewar->carriages;
	nw->op_id = 0;
	nw->p_number = ++g_id;
	corewar->carriages->prev = nw;
	nw->prev = NULL;
	corewar->carriages = nw;
	if (corewar->verbose & 4)
		ft_printf("P% 5d | lfork %d (%d)\n", carriage->p_number,
				vars->vars[0], carriage->counter + vars->vars[0]);
}
