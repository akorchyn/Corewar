/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 23:43:59 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/19 14:08:35 by kpshenyc         ###   ########.fr       */
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
	if (operation != carriage->operation_id)
	{
		carriage->operation_id = operation;
		carriage->pause = (operation > 0 && operation < 17)
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

void		operation(t_corewar *corewar, t_dispatcher *dispatcher,
		t_carriage *carriage)
{
	if (!carriage)
		return ;
	operation(corewar, dispatcher, carriage->next);
	if (carriage->pause)
		return ;
	if (carriage->operation_id > 0 && carriage->operation_id < 17)
	{
		// if (dispatcher[carriage->operation_id](carriage, corewar));
	}
	else
		carriage->counter++;
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
	// t_corewar		corewar;
	// t_dispatcher	dispatcher[16];

	// ft_bzero(&corewar, sizeof(corewar));
	// parse_arguments(ac, av, &corewar);
	// !(corewar.players_count) ? error(200, "No players.", NULL) : 0;
	// initializing(&corewar);
	// initializing_op_tab();
	// initializing_dispatcher(dispatcher);
	// cycle(&corewar, dispatcher);
	av[ac] = 0;
	FOR(int i, 0, i != 20, ++i, { a + b });
	return (0);
}
