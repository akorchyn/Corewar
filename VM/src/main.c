/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 23:43:59 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/25 17:33:17 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		get_variables(t_carriage *carriage, t_vars *vars,
		t_corewar *corewar)
{
	int8_t		i;
	int32_t		memory_shift;
	int32_t		read_bytes;

	i = -1;
	read_bytes = 0;
	while (++i < g_op_tab[carriage->op_id].variables)
	{
		memory_shift = (carriage->counter + read_bytes +
				g_op_tab[carriage->op_id].is_codage) % MEM_SIZE;
		vars->vars[i] = bytes_to_dec(corewar->map, memory_shift + 1,
				vars->bytes[i]);
		read_bytes += vars->bytes[i];
	}
}


uint8_t		generate_cadage(int8_t op_num)
{
	uint8_t		value;
	int8_t		i;

	value = 0;
	i = -1;
	while (++i < MAX_ARGS_NUMBER)
	{
		value <<= 2;
		if (g_op_tab[op_num].vars[i] == T_REG)
			value |= T_REG;
		else if (g_op_tab[op_num].vars[i] == T_IND)
			value |= T_IND;
		else if (g_op_tab[op_num].vars[i] == T_DIR)
			value |= T_DIR;
	}
	return (value);
}

void		print_dump(uint8_t *map, int16_t bytes_in_line, int16_t size)
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

void		get_info_from_cadage(t_vars *vars, int8_t value, int8_t i,
				int8_t op_id)
{
	if (value == REG_CODE)
	{
		vars->parsed_codage[i] = T_REG;
		vars->bytes[i] = REG_BYTES;
	}
	else if (value == IND_CODE)
	{
		vars->parsed_codage[i] = T_IND;
		vars->bytes[i] = IND_BYTES;
	}
	else if (value == DIR_CODE)
	{
		vars->parsed_codage[i] = T_DIR;
		(vars->bytes[i] = (int8_t) ((g_op_tab[op_id].is_ind)
									? IND_BYTES : DIR_BYTES));
	}
	else
		vars->parsed_codage[i] = 0;
}

int8_t		check_valid(t_carriage *pc, t_corewar *corewar, t_vars *vars)
{
	int8_t	shift;
	int8_t	value;
	int8_t	i;
	int8_t	answer;

	vars->codage = (g_op_tab[pc->op_id].is_codage)
			? bytes_to_dec(corewar->map, pc->counter + 1, 1)
			: generate_cadage(pc->op_id);
	(g_op_tab[pc->op_id].is_codage) ? vars->skip++ : 0;
	shift = 6;
	i = 0;
	answer = 1;
	while (shift > 0)
	{
		value = (int8_t)((vars->codage >> shift) & 0b11);
		get_info_from_cadage(vars, value, i, pc->op_id);
		if (!(vars->parsed_codage[i] & g_op_tab[pc->op_id].vars[i]
			  || vars->parsed_codage[i] == g_op_tab[pc->op_id].vars[i]))
			answer = 0;
		vars->skip += vars->bytes[i++];
		shift -= 2;
	}
	return (answer);
}

void		operation(t_carriage *pc, t_corewar *corewar, t_dispatcher *funcs)
{
	t_vars		vars;

	while (pc)
	{
		if (!pc->pause)
		{
			pc->op_id = bytes_to_dec(corewar->map, pc->counter, 1) - 1;
			if (pc->op_id > -1 && pc->op_id < COMANDS)
				pc->pause = g_op_tab[pc->op_id].pause - 1;
			else
				pc->counter = (pc->counter + 1) % MEM_SIZE;
		}
		else if (!(--pc->pause))
		{
			ft_bzero(&vars, sizeof(vars));
			if (check_valid(pc, corewar, &vars))
			{
				get_variables(pc, &vars, corewar);
				funcs[pc->op_id](pc, corewar, &vars);
			}
			pc->counter = (pc->counter + vars.skip + 1) % MEM_SIZE;
		}
		pc = pc->next;
	}
}

void		cycle_to_die(t_corewar *corewar, t_carriage *pc)
{
	t_carriage	*tmp;

	corewar->count_checks++;
	while (pc)
	{
		tmp = pc->next;
		if (corewar->iteration - pc->last_live >= corewar->cycles_to_die
			|| corewar->cycles_to_die < 0)
		{
			(pc->prev) ? pc->prev->next = pc->next : 0;
			(pc->next) ? pc->next->prev = pc->prev : 0;
			(corewar->carriages == pc) ? corewar->carriages = pc->next : 0;
			free(pc);
		}
		else
			pc->last_live = 0;
		pc = tmp;
	}
	if (corewar->count_live_for_cycle >= NBR_LIVE ||
			corewar->count_checks >= MAX_CHECKS)
	{
		corewar->cycles_to_die -= CYCLE_DELTA;
		corewar->count_checks = 0;
	}
	corewar->to_check = corewar->cycles_to_die;
	corewar->count_live_for_cycle = 0;
}

void		cycle(t_corewar *corewar, t_dispatcher *dispatcher, t_header **head)
{
	while (corewar->carriages)
	{
		if (corewar->iteration == 4894)
			printf("ok");
		corewar->iteration++;
		operation(corewar->carriages, corewar, dispatcher);
		if (--corewar->to_check < 1)
			cycle_to_die(corewar, corewar->carriages);
	}
	ft_printf("%d\n", corewar->iteration);
	ft_printf("ctd: %d\n", corewar->cycles_to_die);
	ft_printf("Contestant %d, \"%s\", has won !\n", corewar->player_last_live,
				head[corewar->player_last_live - 1]->prog_name);
}

void		dump(t_corewar *corewar, t_dispatcher *dispatcher)
{
	while (corewar->carriages && ++corewar->iteration <= corewar->dump_drop)
	{
		operation(corewar->carriages, corewar, dispatcher);
		if (--corewar->to_check < 1)
			cycle_to_die(corewar, corewar->carriages);
	}
	print_dump(corewar->map, 64, MEM_SIZE);
}

int32_t		main(int ac, char **av)
{
	t_corewar		corewar;
	t_dispatcher	dispatcher[16];
	t_header		*header[4];

	ft_bzero(&corewar, sizeof(corewar));
	parse_arguments(ac, av, &corewar);
	!(corewar.players_count) ? error(200, "No players.", NULL) : 0;
	g_id = corewar.players_count;
	initializing(&corewar, header);
	initializing_dispatcher(dispatcher);
	if (!corewar.is_dump)
		cycle(&corewar, dispatcher, header);
	else
		dump(&corewar, dispatcher);
	return (0);
}
