/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 23:43:59 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/25 23:01:46 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int32_t		main(int ac, char **av)
{
	t_corewar		corewar;
	t_dispatcher	dispatcher[16];
	t_header		*header[4];

	ft_bzero(&corewar, sizeof(corewar));
	parse_arguments(ac, av, &corewar);
	process_ids(corewar.carriages, corewar.players);
	!(corewar.players) ? print_usage(av) : 0;
	g_id = corewar.players;
	initializing(&corewar, header);
	initializing_dispatcher(dispatcher);
	if (!corewar.is_dump)
		cycle(&corewar, dispatcher, header);
	else
		dump_cycle(&corewar, dispatcher);
	return (0);
}
