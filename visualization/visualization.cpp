/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:22:41 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/27 15:17:35 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.hpp"

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
	int				clientSocket = -1;
	int				sock;
	int32_t			drawCall;
	unsigned char	data[Corewar::MAP_SIZE];
	Window			window("Corewar", WIDTH, HEIGHT);
	Corewar			*corewar;
	bool			corewarInitialiazed = false;

	drawCall = 0;
	while (!window.isClosed())
	{
		if (window.preview == false)
		{
			if (corewarInitialiazed == false)
			{
				std::cout << "Initialiazing new corewar... ";
				corewar = new Corewar(&window);
				sock = init_socket();
				corewarInitialiazed = true;
				std::cout << "Done!" << std::endl;
				std::cout << "Accepting new corewar throught socket... ";
				clientSocket = accept(sock, NULL, NULL);
				std::cout << "Done!" << std::endl;
			}
			if (clientSocket != -1 && recv(clientSocket, data, 4096, 0) == 0)
			{
				std::cout << "VM closing connection... ";
				clientSocket = -1;
				window.preview = true;
				corewarInitialiazed = false;
				std::cout << "Done!" << std::endl;
				close(sock);
				sock = 0;
				delete corewar;
			}
			else
			{
				corewar->refreshData(data);
				corewar->draw(&window);
				std::cout << "Draw call: " << drawCall << std::endl;
				drawCall++;
			}
		}
		window.poolEvents();
		window.clear();
	}
	return (0);
}
