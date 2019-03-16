/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 23:43:59 by akorchyn          #+#    #+#             */
/*   Updated: 2019/03/16 14:39:54 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_header		*g_header[MAX_PLAYERS];
int32_t			g_car_count;
t_corewar		g_corewar;

int32_t			set_connection_to_visualization(char *address, int16_t *i)
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
	{
		error(17, "Can not connect to the server...", NULL);
		close(sock);
		exit(0);
	}
	return (sock);
}

static void		ending(t_corewar *g_corewar)
{
	int8_t		i;

	i = -1;
	free(g_corewar->map);
	if (g_corewar->sock)
		free(g_corewar->player_affected);
	while (++i < g_corewar->players)
		free(g_header[i]);
}

void			handler(int signal)
{
	(void)signal;
	if (g_corewar.sock)
		close(g_corewar.sock);
	exit(EXIT_SUCCESS);
}

int32_t			main(int ac, char **av)
{
	t_dispatcher	dispatcher[16];

	signal(SIGTERM, &handler);
	ft_bzero(&g_corewar, sizeof(g_corewar));
	parse_arguments(ac, av, &g_corewar, 0);
	(g_corewar.players > MAX_PLAYERS) ? error(767, "Too many players", NULL)
											: 0;
	!(g_corewar.players) ? print_usage(av) : 0;
	process_ids(g_corewar.carriages, g_corewar.players);
	g_id = g_corewar.players;
	g_car_count = g_corewar.players;
	initializing(&g_corewar);
	initializing_dispatcher(dispatcher);
	if (!g_corewar.is_dump)
		cycle(&g_corewar, dispatcher);
	else
		dump_cycle(&g_corewar, dispatcher);
	ending(&g_corewar);
	(g_corewar.verbose & 8) ? system("leaks -q corewar") : 0;
	if (g_corewar.sock)
		close(g_corewar.sock);
	return (0);
}
