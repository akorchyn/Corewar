/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 23:43:59 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/28 18:03:41 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_header		*g_header[MAX_PLAYERS];
int32_t			g_car_count;

int32_t		set_connection_to_visualization(char *address, int16_t *i)
{
	int32_t					sock;
	struct sockaddr_in		server_address;
	struct hostent			*he;
	struct in_addr			**addr;

	he = (address) ? gethostbyname(address) : NULL;
	addr = (he) ? (struct in_addr**)he->h_addr_list : NULL;
	(addr) ? (*i)++ : 0;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(4242);
	server_address.sin_addr.s_addr = (addr) ? (*addr)->s_addr : INADDR_ANY;
	if (connect(sock, (struct sockaddr *)&server_address,
			sizeof(server_address)) == -1)
		error(17, "Can not connect to the server...", NULL);
	return (sock);
}

void		ending(t_corewar *corewar)
{
	int8_t		i;

	i = -1;
	free(corewar->map);
	if (corewar->sock)
		free(corewar->player_affected);
	while (++i < corewar->players)
		free(g_header[i]);
}

int32_t		main(int ac, char **av)
{
	t_corewar		corewar;
	t_dispatcher	dispatcher[16];

	ft_bzero(&corewar, sizeof(corewar));
	parse_arguments(ac, av, &corewar, 0);
	!(corewar.players) ? print_usage(av) : 0;
	process_ids(corewar.carriages, corewar.players);
	g_id = corewar.players;
	g_car_count = corewar.players;
	initializing(&corewar);
	initializing_dispatcher(dispatcher);
	if (!corewar.is_dump)
		cycle(&corewar, dispatcher);
	else
		dump_cycle(&corewar, dispatcher);
	ending(&corewar);
	(corewar.verbose & 8) ? system("leaks -q corewar") : 0;
	return (0);
}
