/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:56:24 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/28 18:15:36 by kpshenyc         ###   ########.fr       */
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

//-----------------------------------------------------------------------------

Corewar::Byte::Byte() : value(0), owner(NO_PLAYER), hexText("00"), color(&(basicColors[NO_PLAYER])),
						position(SDL_Rect{.x = 0, .y = 0, .w = 0, .h = 0}), changed(1),
						byteSurface(nullptr), byteTexture(nullptr)
{
}

//-----------------------------------------------------------------------------

void Corewar::Byte::valueToHex(unsigned char value)
{
	hexText[0] = Corewar::byteOrder[value / 16];
	hexText[1] = Corewar::byteOrder[value % 16];
}

//-----------------------------------------------------------------------------

void	Corewar::_parseInitPackage(uint8_t *initPackage, Window *window)
{
	int16_t		packageIter = 0;
	uint8_t		nameBuff[Corewar::maxNameLength];
	string		tmp;

	int32_t		paddingLeft = (64 * (_byteWidth + _blankWidth)) + 50;
	int32_t		paddingTop = 50;

	_players = vector<Player>(initPackage[packageIter++]);
	for (int16_t i = 0; i < 4; ++i)
	{
		if (i < _players.size())
		{
			_players[i].id = initPackage[packageIter];
			memcpy(nameBuff, initPackage + packageIter + 1, Corewar::maxNameLength);
			_players[i].name = (char *)nameBuff;

			tmp = "Player " + std::to_string(_players[i].id) + ":";
			_players[i].idRect.h = _byteHeight;
			_players[i].idRect.w = tmp.length() * 10;
			_players[i].idRect.x = paddingLeft;
			_players[i].idRect.y = paddingTop;
			_players[i].idSurface = TTF_RenderText_Solid(_font, tmp.c_str(), basicColors[0]);
			_players[i].idTexture = SDL_CreateTextureFromSurface(window->renderer, _players[i].idSurface);
			SDL_QueryTexture(_players[i].idTexture, NULL, NULL, &(_players[i].idRect.w), &(_players[i].idRect.h));


			tmp = _players[i].name;
			_players[i].nameRect.h = _byteHeight;
			_players[i].nameRect.w = tmp.length() * 10;
			_players[i].nameRect.x = paddingLeft + 65;
			_players[i].nameRect.y = paddingTop;
			_players[i].nameSurface = TTF_RenderText_Solid(_font, tmp.c_str(), basicColors[i + 1]);
			_players[i].nameTexture = SDL_CreateTextureFromSurface(window->renderer, _players[i].nameSurface);
			SDL_QueryTexture(_players[i].nameTexture, NULL, NULL, &(_players[i].nameRect.w), &(_players[i].nameRect.h));
			paddingTop += 35;
		}
		packageIter += Corewar::maxNameLength + 1;
	}
	_cycleDelta = *(initPackage + packageIter);
	_nbrLive = *(initPackage + (packageIter += 4));
	_maxChecks = *(initPackage + (packageIter += 4));
}

//-----------------------------------------------------------------------------

void							Corewar::_initField(Window *window)
{
	int16_t		i = 0;
	int16_t		j = 0;
	for (auto& byte : _map)
	{
		byte.position.x = _startX + j * _byteWidth + j * _blankWidth;
		byte.position.y = _startY + i * _byteHeight + i * _blankHeight;
		byte.position.h = _byteHeight;
		byte.position.w = _byteWidth;
		byte.byteSurface = TTF_RenderText_Solid(_font, byte.hexText.c_str(), *(byte.color));
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

//-----------------------------------------------------------------------------

Corewar::Corewar(Window *window, uint8_t *initPackage) :
	_map(vector<Byte>(Corewar::mapSize, Byte{})), _startX(10), _startY(10),
	_byteWidth(7), _byteHeight(5), _blankWidth(14), _blankHeight(11)
{
	_font = TTF_OpenFont("../fonts/BebasNeue.ttf", 18);
	if (!_font)
	{
		std::cerr << TTF_GetError() << std::endl;
		std::cerr << "Font isn't opened.." << std::endl;
		exit(EXIT_FAILURE);
	}
	_initField(window);
	_parseInitPackage(initPackage, window);
}

//-----------------------------------------------------------------------------

Corewar::~Corewar()
{
	TTF_CloseFont(_font);
}

//-----------------------------------------------------------------------------

void Corewar::refreshData(uint8_t *package)
{
	for (int16_t i = 0; i < Corewar::mapSize; ++i)
	{
		if (*(package + i) != _map.at(i).value)
		{
			_map.at(i).value = *(package + i);
			_map.at(i).valueToHex(*(package + i));
			_map.at(i).changed = 1;
		}
		else
			_map.at(i).changed = 0;
	}
}

//-----------------------------------------------------------------------------

void			Corewar::drawInitData(Window *window)
{
	for (int8_t i = 0; i < _players.size(); ++i)
	{
		SDL_RenderCopy(window->renderer, _players[i].idTexture, NULL, &(_players[i].idRect));
		SDL_RenderCopy(window->renderer, _players[i].nameTexture, NULL, &(_players[i].nameRect));
	}
}

//-----------------------------------------------------------------------------

void Corewar::draw(Window *window)
{
	for (auto& byte : _map)
	{
		if (byte.changed == 1)
		{
			SDL_DestroyTexture(byte.byteTexture);
			SDL_FreeSurface(byte.byteSurface);
			byte.byteSurface = TTF_RenderText_Solid(_font, byte.hexText.c_str(), *(byte.color));
			byte.byteTexture = SDL_CreateTextureFromSurface(window->renderer, byte.byteSurface);
			SDL_QueryTexture(byte.byteTexture, NULL, NULL, &(byte.position.w), &(byte.position.h));
		}
		SDL_RenderCopy(window->renderer, byte.byteTexture, NULL, &(byte.position));
	}
}

//-----------------------------------------------------------------------------
