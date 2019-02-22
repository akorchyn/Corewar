/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:22:41 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/22 17:22:43 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualization.hpp"

constexpr int16_t	WIDTH = 1920;
constexpr int16_t	HEIGHT = 1080;

void		draw_map(unsigned char *buff)
{
	int i = 0;
	unsigned char hex[] = "0123456789abcdef";
	while (i < 4096)
	{
		int j = -1;
		while (++j < 64)
		{
			write(1, &hex[*(buff + i + j) / 16], 1);
			write(1, &hex[*(buff + i + j) % 16], 1);
			write(1, " ", 1);
		}
		write(1, "\n", 1);
		i += 64;
	}
	system("clear");
}

int		init_socket()
{
	int		sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(4242);
	server_address.sin_addr.s_addr = INADDR_ANY;
	bind(sock, (struct sockaddr *)&server_address, sizeof(server_address));
	listen(sock, 1);
	return sock;
}

int		main(void)
{
	int				sock = init_socket();
	int				client_socket = -1;
	unsigned char	data[4096];
	Window window("Corewar", WIDTH, HEIGHT);

	while (!window.isClosed())
	{
		if (client_socket == -1)
			client_socket = accept(sock, NULL, NULL);
		if (client_socket != -1 && recv(client_socket, data, 4096, 0) == 0)
		{
			std::cout << "VM closed connection..." << std::endl;
			client_socket = -1;
		}
		else
			draw_map(data);
		window.poolEvents();
		window.clear();
	}
	close(sock);
	return (0);
}
