/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:56:24 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/01 16:43:19 by kpshenyc         ###   ########.fr       */
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

Corewar::Player::Player(Player &&right) noexcept
{
	idText = std::move(right.idText);
	nameText = std::move(right.nameText);
}

//-----------------------------------------------------------------------------

Corewar::Player::Player(const Player &right) noexcept
{
	std::cout << "wtf1" << std::endl;
	idText = right.idText;
	nameText = right.nameText;
}

//-----------------------------------------------------------------------------

Corewar::Player::Player()
{
}

//-----------------------------------------------------------------------------

Corewar::Player::~Player()
{
}

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
	int16_t		paddingLeft = (64 * (_byteWidth + _blankWidth)) + 50;
	int16_t		paddingTop = 50;
	int8_t		playersAmount = initPackage[packageIter++];
	Player		tmpPlayer;


	for (int16_t i = 0; i < 4; ++i)
	{
		if (i < playersAmount)
		{
			memcpy(nameBuff, initPackage + packageIter + 1, Corewar::maxNameLength);

			tmpPlayer.idText = Text("Player " + std::to_string(initPackage[packageIter]) + ":",
					_font,
					paddingLeft, paddingTop,
					10, 7,
					&basicColors[NO_PLAYER],
					window->renderer);

			tmpPlayer.nameText = Text((char *)nameBuff,
					_font,
					paddingLeft + tmpPlayer.idText.getLength(), paddingTop,
					10, 7,
					&basicColors[i + 1],
					window->renderer);
			_players.push_back(std::move(tmpPlayer));
			paddingTop += 35;
		}
		packageIter += Corewar::maxNameLength + 1;
	}

	_cycleDelta = Text("CYCLE_DELTA: " + std::to_string(*(initPackage + packageIter)),
									_font,
									paddingLeft, paddingTop,
									10, 7 ,
									&basicColors[NO_PLAYER], window->renderer);
	
	paddingTop += 35;
	_nbrLive = Text("NBR_LIVE: " + std::to_string(*(initPackage + (packageIter += 4))),
									_font,
									paddingLeft, paddingTop,
									10, 7 ,
									&basicColors[NO_PLAYER], window->renderer);

	paddingTop += 35;
	_maxChecks = Text("MAX_CHECKS: " + std::to_string(*(initPackage + (packageIter += 4))),
								_font,
								paddingLeft, paddingTop,
								10, 7 ,
								&basicColors[NO_PLAYER], window->renderer);
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
	_byteWidth(7), _byteHeight(10), _blankWidth(14), _blankHeight(11)
{
	_font = TTF_OpenFont("../fonts/BebasNeue.ttf", 22);
	if (!_font)
	{
		std::cerr << TTF_GetError() << std::endl;
		std::cerr << "Font isn't opened in corewar object" << std::endl;
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
		_players[i].idText.draw();
		_players[i].nameText.draw();
	}
	_cycleDelta.draw();
	_nbrLive.draw();
	_maxChecks.draw();
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
