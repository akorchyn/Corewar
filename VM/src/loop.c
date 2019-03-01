/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 22:59:19 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/28 18:07:16 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		operation(t_carriage *pc, t_corewar *corewar,
					t_dispatcher *funcs)
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
			pc->op_id = 0;
		}
		pc = pc->next;
	}
}

static void		kill_carriages(t_carriage *pc, t_corewar *corewar)
{
	t_carriage	*tmp;

	while (pc)
	{
		tmp = pc->next;
		if (corewar->iteration - pc->last_live >= corewar->cycles_to_die
			|| corewar->cycles_to_die <= 0)
		{
			(pc->prev) ? pc->prev->next = pc->next : 0;
			(pc->next) ? pc->next->prev = pc->prev : 0;
			(corewar->carriages == pc) ? corewar->carriages = pc->next : 0;
			g_car_count--;
			free(pc);
		}
		else
			pc->last_live = 0;
		pc = tmp;
	}
}

static void		cycle_to_die(t_corewar *corewar, t_carriage *pc)
{
	corewar->count_checks++;
	kill_carriages(pc, corewar);
	if (corewar->count_live_for_cycle >= NBR_LIVE ||
		corewar->count_checks >= MAX_CHECKS)
	{
		corewar->cycles_to_die -= CYCLE_DELTA;
		(corewar->verbose & 2) && ft_printf("Cycle to die is now %d\n",
											corewar->cycles_to_die);
		corewar->count_checks = 0;
	}
	corewar->to_check = corewar->cycles_to_die;
	corewar->count_live_for_cycle = 0;
}

void			cycle(t_corewar *corewar, t_dispatcher *dispatcher)
{
	if (corewar->sock)
		send_init_package(corewar);
	while (corewar->carriages)
	{
		corewar->iteration++;
		(corewar->verbose & 2) && ft_printf("It is now cycle %d\n",
											corewar->iteration);
		operation(corewar->carriages, corewar, dispatcher);
		if (--corewar->to_check < 1)
			cycle_to_die(corewar, corewar->carriages);
		if (corewar->verbose & 8 && !(corewar->iteration % 500))
			system("leaks -q corewar");
		// if (corewar->sock)
		// 	send_package(corewar);
	}
	ft_printf("Contestant %d, \"%s\", has won !\n", corewar->player_last_live,
			g_header[corewar->player_last_live - 1]->prog_name);
}

void			dump_cycle(t_corewar *corewar, t_dispatcher *dispatcher)
{
	if (corewar->sock)
		send_init_package(corewar);
	while (corewar->carriages && ++corewar->iteration <= corewar->dump_drop)
	{
		operation(corewar->carriages, corewar, dispatcher);
		(corewar->verbose & 2) && ft_printf("It is now cycle %d\n",
											corewar->iteration);
		if (--corewar->to_check < 1)
			cycle_to_die(corewar, corewar->carriages);
		if (corewar->verbose & 8 && !(corewar->iteration % 500))
			system("leaks -q corewar");
		// if (corewar->sock)
		// 	send_package(corewar);
	}
	print_dump(corewar->map, 64, MEM_SIZE);
}
