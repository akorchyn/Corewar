/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:22:41 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/01 12:47:44 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.hpp"

constexpr int16_t	WIDTH = 1920;
constexpr int16_t	HEIGHT = 1080;

int		init_socket()
{
	int		sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(4242);
	server_address.sin_addr.s_addr = INADDR_ANY;
	bind(sock, (struct sockaddr *)&server_address, sizeof(server_address));
	listen(sock, 2);
	return sock;
}

int		main(void)
{
	int32_t			clientSocket = -1;
	int32_t			sock;
	int32_t			drawCall;

	Window			window("Corewar", WIDTH, HEIGHT);
	Corewar			*corewar;

	uint8_t			initPackage[Corewar::initPackageSize];
	uint8_t			*drawPackage;
	bool			corewarInitialiazed = false;

	drawCall = 0;
	while (!window.isClosed())
	{
		if (window.preview == false)
		{
			if (corewarInitialiazed == false)
			{
				sock = init_socket();
				std::cout << "Accepting new corewar throught socket... ";
				clientSocket = accept(sock, NULL, NULL);
				std::cout << "Done!" << std::endl;

				std::cout << "Getting initialization package of size " <<  Corewar::initPackageSize << "... ";
				recv(clientSocket, initPackage, Corewar::initPackageSize, 0);
				std::cout << "Done!" << std::endl;

				std::cout << "Initialiazing new corewar... ";
				corewar = new Corewar(&window, initPackage);
				corewarInitialiazed = true;
				std::cout << "Done!" << std::endl;

			}
			corewar->drawInitData(&window);
			// if (clientSocket != -1 && recv(clientSocket, initPackage, 4096, 0) == 0)
			// {
			//	std::cout << "VM closing connection... ";
			//	clientSocket = -1;
			// 	window.preview = true;
			// 	corewarInitialiazed = false;
			// 	std::cout << "Done!" << std::endl;
			// 	close(sock);
			// 	sock = 0;
			// 	delete corewar;
			// }
			// else
			// {
			// 	corewar->refreshData(initPackage);
			// 	corewar->draw(&window);
			// 	std::cout << "Draw call: " << drawCall++ << std::endl;
			// }
		}
		window.poolEvents();
		window.clear();
	}
	return (0);
}
