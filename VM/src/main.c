/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 23:43:59 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/19 22:51:18 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		set_operation_code(t_carriage *carriage, t_corewar *corewar)
{
	int32_t		operation;

	if (!carriage)
		return ;
	set_operation_code(carriage->next, corewar);
	operation = from_bytes_to_dec(corewar->map + carriage->counter, 1);
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
			vars->parsed_codage[counter] =  T_IND;
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
			result += IND_BYTES;
		else if (type == T_DIR)
			result += (g_op_tab[carriage->operation_id].is_ind) ? IND_BYTES
																: DIR_BYTES;
		else if (type == T_REG)
			result += REG_BYTES;
	}
	if (vars->codage)
		result += 1;
	return (result);
}

void		operation(t_corewar *corewar, t_dispatcher *dispatcher,
		t_carriage *carriage)
{
	t_vars		vars;
	int8_t		is_codage;

	if (!carriage)
		return ;
	operation(corewar, dispatcher, carriage->next);
	if (carriage->pause)
		return ;
	if (carriage->operation_id > 0 && carriage->operation_id < OPERATIONS + 1)
	{
		ft_bzero(&vars, sizeof(t_vars));
		is_codage = g_op_tab[carriage->operation_id].is_codage;
		if (is_codage)
			vars.codage = from_bytes_to_dec(corewar->map + carriage->counter + 1
					, 1);
		int k;
		if (!is_codage || (k = check_codage(carriage, &vars)))
		{
			carriage->step_size = get_step_size(carriage, &vars) + 1;
		}
		else
		{
			printf("neok\n");
			carriage->step_size = get_step_size(carriage, &vars) + 1;
		}
		carriage->counter = (carriage->counter + carriage->step_size) % MEM_SIZE;
	}
	else
		carriage->counter = (carriage->counter + 1) % MEM_SIZE;
	printf("%d\n", carriage->counter);
}

void		cycle(t_corewar *corewar, t_dispatcher *dispatcher)
{

	while (corewar->carriages)
	{
		corewar->iteration++;
		corewar->to_check--;
		set_operation_code(corewar->carriages, corewar);
		decrement_pause(corewar->carriages);
		operation(corewar, dispatcher, corewar->carriages);

	}
}

int32_t		main(int ac, char **av)
{
	t_corewar		corewar;
	t_dispatcher	dispatcher[16];

	ft_bzero(&corewar, sizeof(corewar));
	parse_arguments(ac, av, &corewar);
	initializing(&corewar);
	initializing_op_tab();
	initializing_dispatcher(dispatcher);
	cycle(&corewar, dispatcher);
	return (0);
}
