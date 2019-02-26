/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 17:22:41 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/26 17:39:16 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualization.hpp"

constexpr int16_t	WIDTH = 1920;
constexpr int16_t	HEIGHT = 1080;

using std::vector;
using std::pair;

enum Players
{
	NO_PLAYER, FIRST, SECOND, THIRD, FOURTH
};

SDL_Color	basicColors[5] = {
		SDL_Color{192, 192, 192},
		SDL_Color{255, 51, 51},
		SDL_Color{102, 255, 102},
		SDL_Color{51, 51, 255},
		SDL_Color{255, 255, 51}
};

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

Corewar::Byte::Byte() : value(0), owner(NO_PLAYER), hexText("00"), color(&basicColors[NO_PLAYER]),
						position(SDL_Rect{.x = 0, .y = 0, .w = 0, .h = 0}), changed(1),
						byteSurface(nullptr), byteTexture(nullptr)
{

}

void Corewar::Byte::valueToHex(unsigned char value)
{
	hexText[0] = Corewar::byteOrder[value / 16];
	hexText[1] = Corewar::byteOrder[value % 16];
}

Corewar::Corewar(Window *window) :
	_map(vector<Byte>(Corewar::MAP_SIZE, Byte{})), startX(10), startY(10),
	byteWidth(7), byteHeight(5), blankWidth(14), blankHeight(11)
{
	font = TTF_OpenFont("fonts/BebasNeue.ttf", 18);
	if (!font)
	{
		std::cerr << TTF_GetError() << std::endl;
		std::cerr << "Font isn't opened.." << std::endl;
		exit(EXIT_FAILURE);
	}

	int16_t		i = 0;
	int16_t		j = 0;
	for (auto& byte : _map)
	{
		byte.position.x = startX + j * byteWidth + j * blankWidth;
		byte.position.y = startY + i * byteHeight + i * blankHeight;
		byte.position.h = byteHeight;
		byte.position.w = byteWidth;
		byte.byteSurface = TTF_RenderText_Solid(font, byte.hexText.c_str(), *(byte.color));
		byte.byteTexture = SDL_CreateTextureFromSurface(window->renderer, byte.byteSurface);
		SDL_QueryTexture(byte.byteTexture, NULL, NULL, &(byte.position.w), &(byte.position.h));
		++j;
		if (j == 64)
		{
			++i;
			j = 0;
		}
	}
}

Corewar::~Corewar()
{
	TTF_CloseFont(font);
}

void Corewar::refreshData(unsigned char *buffer)
{
	for (int16_t i = 0; i < Corewar::MAP_SIZE; ++i)
	{
		if (*(buffer + i) != _map.at(i).value)
		{
			_map.at(i).value = *(buffer + i);
			_map.at(i).valueToHex(*(buffer + i));
			_map.at(i).changed = 1;
		}
		else
			_map.at(i).changed = 0;
		// else if (_map.at(i).byteSurface != nullptr && _map.at(i).byteTexture != nullptr)
		// 	_map.at(i).changed = 0;
	}
}

void Corewar::draw(Window *window)
{
	for (auto& byte : _map)
	{
		if (byte.changed == 1)
		{
			SDL_DestroyTexture(byte.byteTexture);
			SDL_FreeSurface(byte.byteSurface);
			byte.byteSurface = TTF_RenderText_Solid(font, byte.hexText.c_str(), *(byte.color));
			byte.byteTexture = SDL_CreateTextureFromSurface(window->renderer, byte.byteSurface);
			SDL_QueryTexture(byte.byteTexture, NULL, NULL, &(byte.position.w), &(byte.position.h));
		}
		SDL_RenderCopy(window->renderer, byte.byteTexture, NULL, &(byte.position));
	}
}

int		main(void)
{
	int				clientSocket = -1;
	int				sock;
	int32_t			drawCall;
	unsigned char	data[Corewar::MAP_SIZE];
	Window window	("Corewar", WIDTH, HEIGHT);
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
