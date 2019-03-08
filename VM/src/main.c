/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 23:43:59 by akorchyn          #+#    #+#             */
/*   Updated: 2019/03/04 14:30:30 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_header		*g_header[MAX_PLAYERS];
int32_t			g_car_count;
t_corewar		corewar;

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
			}
//	int info = 0;
//	int len = sizeof(info);
//	if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &info, &len) == -1)
//	{
//		ft_printf("cannot get info about socket\n");
//		ft_printf("errno: %d", errno);
//		exit(1);
//	}
//	ft_printf("%d\n", info);
//	info *= 30;
//	setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &info, sizeof(len));
//	if (getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &info, &len) == -1)
//	{
//		ft_printf("cannot get info about socket\n");
//		ft_printf("errno: %d", errno);
//		exit(1);
//	}
//	ft_printf("%d\n", info);
	return (sock);
}

static void		ending(t_corewar *corewar)
{
	int8_t		i;

	i = -1;
	free(corewar->map);
	if (corewar->sock)
		free(corewar->player_affected);
	while (++i < corewar->players)
		free(g_header[i]);
}


void			handler(int signal)
{
	(void)signal;
	if (corewar.sock)
		close(corewar.sock);
	exit(EXIT_SUCCESS);
}

int32_t			main(int ac, char **av)
{
	t_dispatcher	dispatcher[16];

	signal(SIGTERM, &handler);
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
	if (corewar.sock)
		close(corewar.sock);
	return (0);
}
