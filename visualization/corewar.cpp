/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:56:24 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/27 15:14:50 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.hpp"

SDL_Color	basicColors[5] = {
		SDL_Color{192, 192, 192},
		SDL_Color{255, 51, 51},
		SDL_Color{102, 255, 102},
		SDL_Color{51, 51, 255},
		SDL_Color{255, 255, 51}
};

Corewar::Byte::Byte() : value(0), owner(NO_PLAYER), hexText("00"), color(&(basicColors[NO_PLAYER])),
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
