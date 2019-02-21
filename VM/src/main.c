/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 23:43:59 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/21 15:07:07 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			bad_register_id(t_vars *vars, t_carriage *carriage)
{
	int8_t		i;

	i = -1;
	while (++i < g_op_tab[carriage->operation_id].variables)
	{
		if (vars->parsed_codage[i] == T_REG
			&& (vars->vars[i] < 1 || vars->vars[i] > REG_NUMBER))
			return (1);
	}
	return (0);
}

void		set_operation_code(t_carriage *carriage, t_corewar *corewar)
{
	int32_t		operation;

	if (!carriage)
		return ;
	set_operation_code(carriage->next, corewar);
	operation = bytes_to_dec(corewar->map + carriage->counter, 1);
	if (operation != carriage->operation_id + 1)
	{
		carriage->operation_id = operation - 1;
		carriage->pause = (operation > 0 && operation < OPERATIONS + 1)
							? g_op_tab[operation - 1].pause
							: 0;
	}
}

void		decrement_pause(t_carriage *carriage)
{
	if (!carriage)
		return ;
	decrement_pause(carriage->next);
	if (carriage->pause > 0)
		carriage->pause--;
}

int8_t		check_codage(t_carriage *carriage, t_vars *vars)
{
	int8_t		value;
	int8_t		shift;
	int8_t		counter;

	counter = g_op_tab[carriage->operation_id].variables;
	shift = 2 + (2 * (3 - g_op_tab[carriage->operation_id].variables));
	while (--counter > -1)
	{
		value = (vars->codage >> shift) & 0b11;
		if (value == REG_CODE)
			vars->parsed_codage[counter] = T_REG;
		else if (value == IND_CODE)
			vars->parsed_codage[counter] = T_IND;
		else if (value == DIR_CODE)
			vars->parsed_codage[counter] = T_DIR;
		else
			vars->parsed_codage[counter] = 0;
		shift += 2;
	}
	while (++counter < g_op_tab[carriage->operation_id].variables)
		if (!(g_op_tab[carriage->operation_id].vars[counter]
			& vars->parsed_codage[counter]))
			return (0);
	return ((int8_t)(vars->codage << counter * 2) == 0 ? 1 : 0);
}

int32_t			get_step_size(t_carriage *const carriage, t_vars *vars)
{
	int32_t		result;
	int8_t		i;
	int8_t		type;

	result = 0;
	i = -1;
	while (++i < g_op_tab[carriage->operation_id].variables)
	{
		type = (vars->codage) ? vars->parsed_codage[i]
							: g_op_tab[carriage->operation_id].vars[i];
		if (type == T_IND)
			(vars->bytes_codage[i] = IND_BYTES) && (result += IND_BYTES);
		else if (type == T_DIR)
		{
			vars->bytes_codage[i] = (g_op_tab[carriage->operation_id].is_ind)
					? IND_BYTES : DIR_BYTES;
			result += vars->bytes_codage[i];
		}
		else if (type == T_REG)
			(vars->bytes_codage[i] = REG_BYTES) && (result += REG_BYTES);
	}
	if (vars->codage)
		result += 1;
	return (result + 1);
}

void		get_variables(t_carriage *carriage, t_vars *vars,
		t_corewar *corewar)
{
	int8_t		i;
	int32_t		memory_shift;
	int32_t		read_bytes;

	i = -1;
	read_bytes = 0;
	while (++i < g_op_tab[carriage->operation_id].variables)
	{
		memory_shift = (carriage->counter + read_bytes +
				g_op_tab[carriage->operation_id].is_codage) % MEM_SIZE;
		vars->vars[i] = bytes_to_dec(corewar->map + memory_shift + 1,
				vars->bytes_codage[i]);
		read_bytes += vars->bytes_codage[i];
	}
}

void		ld(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int32_t		address;

	if (bad_register_id(vars, carriage))
		return ;
	if (vars->parsed_codage[0] == T_DIR)
	{
		carriage->reg[vars->vars[1] - 1] = vars->vars[0];
		carriage->carry = (vars->vars[0]) ? 0 : 1;
		printf("%lld\n", carriage->reg[vars->vars[1] - 1]);
		return ;
	}
	address = (carriage->counter + (int16_t)vars->vars[0] % IDX_MOD) % MEM_SIZE;
	carriage->reg[vars->vars[1] - 1] = bytes_to_dec(corewar->map + address,
			REG_SIZE);
	carriage->carry = carriage->reg[vars->vars[1] - 1] ? 0 : 1;
	printf("%lld\n", carriage->reg[vars->vars[1] - 1]);
}

void		st(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int32_t		address;

	if (bad_register_id(vars, carriage))
		return ;
	if (vars->parsed_codage[1] == REG_CODE)
	{
		carriage->reg[vars->vars[1] - 1] = carriage->reg[vars->vars[0] - 1];
		return ;
	}
	address = (carriage->counter + (int16_t)vars->vars[1] % IDX_MOD) % MEM_SIZE;
	(DEBUG) && ft_printf("\n\n\n\n\n\n\n%100.*m", 340, corewar->map);
	put_bytes(carriage->reg[vars->vars[0] - 1], corewar->map + address,
																	REG_SIZE);
	(DEBUG) && ft_printf("\n\n\n\n\n\n\n%100.*m", 340, corewar->map);
}

void		add(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	UNUSED_VARIABLE(corewar);
	if (bad_register_id(vars, carriage))
		return ;
	carriage->reg[vars->vars[2] - 1] = carriage->reg[vars->vars[0] - 1]
			+ carriage->reg[vars->vars[1] - 1];
	carriage->carry = (carriage->reg[vars->vars[2]] - 1) ? 0 : 1;
	printf("%lld\n", carriage->reg[vars->vars[2] - 1]);
}

void		sub(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	UNUSED_VARIABLE(corewar);
	if (bad_register_id(vars, carriage))
		return ;
	carriage->reg[vars->vars[2] - 1] = carriage->reg[vars->vars[0] - 1]
											- carriage->reg[vars->vars[1] - 1];
	carriage->carry = (carriage->reg[vars->vars[2]] - 1) ? 0 : 1;
}

void		and(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int8_t		i;
	int64_t		values[2];

	i = -1;
	if (bad_register_id(vars, carriage))
		return ;
	while (++i < 2)
	{
		if (vars->parsed_codage[i] == T_REG)
			values[i] = carriage->reg[vars->vars[i] - 1];
		else if (vars->parsed_codage[i] == T_DIR)
			values[i] = vars->vars[i];
		else if (vars->parsed_codage[i] == T_IND)
			values[i] = bytes_to_dec(corewar->map + (carriage->counter +
					(int16_t)vars->vars[i] % IDX_MOD) % MEM_SIZE, 4);
	}
	carriage->reg[vars->vars[2] - 1] = values[0] & values[1];
	carriage->carry = carriage->reg[vars->vars[2] - 1] == 0 ? 1 : 0;
}

void		or(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int8_t		i;
	int64_t		values[2];

	i = -1;
	if (bad_register_id(vars, carriage))
		return ;
	while (++i < 2)
	{
		if (vars->parsed_codage[i] == T_REG)
			values[i] = carriage->reg[vars->vars[i] - 1];
		else if (vars->parsed_codage[i] == T_DIR)
			values[i] = vars->vars[i];
		else if (vars->parsed_codage[i] == T_IND)
			values[i] = bytes_to_dec(corewar->map + (carriage->counter +
					(int16_t)vars->vars[i] % IDX_MOD) % MEM_SIZE, 4);
	}
	carriage->reg[vars->vars[2] - 1] = values[0] | values[1];
	carriage->carry = carriage->reg[vars->vars[2] - 1] == 0 ? 1 : 0;
}

void		xor(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int8_t		i;
	int64_t		values[2];

	i = -1;
	if (bad_register_id(vars, carriage))
		return ;
	while (++i < 2)
	{
		if (vars->parsed_codage[i] == T_REG)
			values[i] = carriage->reg[vars->vars[i] - 1];
		else if (vars->parsed_codage[i] == T_DIR)
			values[i] = vars->vars[i];
		else if (vars->parsed_codage[i] == T_IND)
			values[i] = bytes_to_dec(corewar->map + (carriage->counter +
					(int16_t)vars->vars[i] % IDX_MOD) % MEM_SIZE, 4);
	}
	carriage->reg[vars->vars[2] - 1] = values[0] ^ values[1];
	carriage->carry = carriage->reg[vars->vars[2] - 1] == 0 ? 1 : 0;
}

void		zjmp(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	UNUSED_VARIABLE(corewar);
	if (carriage->carry)
	{
		carriage->step_size = 0;
		carriage->counter = (carriage->counter + (vars->vars[0] % IDX_MOD))
							% MEM_SIZE;
	}
}

void		ldi(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int32_t		values[2];

	if (bad_register_id(vars, carriage))
		return ;
	if (vars->parsed_codage[0] == T_REG)
		values[0] = carriage->reg[vars->vars[0] - 1];
	else if (vars->parsed_codage[0] == T_IND)
		values[0] = bytes_to_dec(corewar->map + (carriage->counter +
				(int16_t)vars->vars[0] % IDX_MOD) % MEM_SIZE, REG_SIZE);
	else
		values[0] = vars->vars[0];
	if (vars->parsed_codage[1] == T_REG)
		values[1] = carriage->reg[vars->vars[1] - 1];
	else
		values[1] = vars->vars[1];
	carriage->reg[vars->vars[2] - 1] = bytes_to_dec(corewar->map +
			(carriage->counter + (values[0] + values[1]) % IDX_MOD) % MEM_SIZE,
																	REG_SIZE);
}

void		operation(t_corewar *corewar, t_dispatcher *dispatcher,
		t_carriage *carriage)
{
	t_vars		vars;

	if (!carriage)
		return ;
	operation(corewar, dispatcher, carriage->next);
	if (carriage->pause)
		return ;
	if (carriage->operation_id > 0 && carriage->operation_id < OPERATIONS + 1)
	{
		ft_bzero(&vars, sizeof(t_vars));
		if (g_op_tab[carriage->operation_id].is_codage)
			vars.codage = bytes_to_dec(corewar->map + carriage->counter + 1, 1);
		if (!vars.codage || check_codage(carriage, &vars))
		{
			carriage->step_size = get_step_size(carriage, &vars);
			get_variables(carriage, &vars, corewar);
			dispatcher[carriage->operation_id](carriage, corewar, &vars);
		}
		else
			carriage->step_size = get_step_size(carriage, &vars);
		carriage->counter = (carriage->counter + carriage->step_size)
																	% MEM_SIZE;
	}
	else
		carriage->counter = (carriage->counter + 1) % MEM_SIZE;
}

void		cycle_to_die(t_corewar *corewar, t_carriage *carriages)
{
	if (--corewar->to_check > 0)
		return ;
	while (carriages)
	{
		if (corewar->iteration - carriages->last_live > 0)
		{
			corewar->carriages = extract_list(&corewar->carriages, carriages);
			free(carriages);
			return;
		}
		carriages->last_live = 0;
		carriages = carriages->next;
	}
	if (corewar->count_live_for_cycle > NBR_LIVE ||
											corewar->count_checks == MAX_CHECKS)
	{
		corewar->count_checks = 0;
		corewar->cycles_to_die -= CYCLE_DELTA;
	}
	else
		corewar->count_checks++;
	corewar->to_check = corewar->cycles_to_die;
}

void		cycle(t_corewar *corewar, t_dispatcher *dispatcher)
{
	while (corewar->carriages)
	{
		corewar->iteration++;
		set_operation_code(corewar->carriages, corewar);
		decrement_pause(corewar->carriages);
		operation(corewar, dispatcher, corewar->carriages);
		cycle_to_die(corewar, corewar->carriages);
		printf("%d\n", corewar->iteration);
	}
}

int32_t		main(int ac, char **av)
{
	t_corewar		corewar;
	t_dispatcher	dispatcher[16];

	ft_bzero(&corewar, sizeof(corewar));
	parse_arguments(ac, av, &corewar);
	!(corewar.players_count) ? error(200, "No players.", NULL) : 0;
	initializing(&corewar);
	initializing_dispatcher(dispatcher);
	cycle(&corewar, dispatcher);
	return (0);
}
