/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 14:56:24 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/08 15:52:00 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.hpp"

SDL_Color	basicColors[5] = {
		SDL_Color{192, 192, 192},
		SDL_Color{237, 67, 55},
		SDL_Color{102, 255, 102},
		SDL_Color{0, 191, 255},
		SDL_Color{153,50,204}
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

Corewar::Byte::Byte() : value(0), affectedBy(NO_PLAYER), changed(false), carriageOn(false)
{
}

//-----------------------------------------------------------------------------

string Corewar::Byte::valueToHex(uint8_t value)
{
	string res;
	res += byteOrder[value / 16];
	res += byteOrder[value % 16];
	return res;
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
									paddingLeft, paddingTop += 35,
									10, 7 ,
									&basicColors[NO_PLAYER], window->renderer);
	
	_nbrLive = Text("NBR_LIVE: " + std::to_string(*(initPackage + (packageIter += 4))),
									_font,
									paddingLeft, paddingTop += 35,
									10, 7 ,
									&basicColors[NO_PLAYER], window->renderer);

	_maxChecks = Text("MAX_CHECKS: " + std::to_string(*(initPackage + (packageIter += 4))),
								_font,
								paddingLeft, paddingTop += 35,
								10, 7 ,
								&basicColors[NO_PLAYER], window->renderer);

	_cycleToDie = Text("CYCLE_TO_DIE: ",
								_font,
								paddingLeft, paddingTop += 35,
								10, 7,
								&basicColors[NO_PLAYER], window->renderer);

	_cycleToDieValue = Text("0",
								_font,
								paddingLeft + 110, paddingTop,
								10, 7,
								&basicColors[NO_PLAYER], window->renderer);

	_processess = Text("processess: ",
					   _font,
					   paddingLeft, paddingTop += 35,
					   10, 7,
					   &basicColors[NO_PLAYER], window->renderer);

	_processessValue = Text("0",
							_font,
							paddingLeft + 150, paddingTop,
							10, 7,
							&basicColors[NO_PLAYER], window->renderer);

	_iteration = Text("iteration: ",
								_font,
								paddingLeft, paddingTop += 70,
								10, 7,
								&basicColors[NO_PLAYER], window->renderer);

	_iterationTextValue = Text("0",
								_font,
								paddingLeft + 100, paddingTop,
								10, 7,
								&basicColors[NO_PLAYER], window->renderer);
}

//-----------------------------------------------------------------------------

void							Corewar::_initField(Window *window)
{
	int16_t		i = 0;
	int16_t		j = 0;
	for (auto& byte : _map)
	{
		byte.byteText = Text((string("00")).c_str(),
							_font,
							_startX + j * _byteWidth + j * _blankWidth, _startY + i * _byteHeight + i * _blankHeight,
							_byteWidth, _byteHeight,
							&basicColors[NO_PLAYER], window->renderer);
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
	_byteWidth(10), _byteHeight(2), _blankWidth(18), _blankHeight(18),
	_iterationValue(0), winner(0)
{
	_font = TTF_OpenFont("fonts/BebasNeue.ttf", 22);
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

void					Corewar::_processField(uint8_t *fieldPackage, uint16_t cells)
{
	for (uint16_t i = 0; i < cells; ++i)
	{
		if (*(fieldPackage + i * 2) != _map[i].value || *(fieldPackage + i * 2 + 1) != _map[i].affectedBy)
		{
			_map[i].value = *(fieldPackage + i * 2);
			_map[i].affectedBy = *(fieldPackage + i * 2 + 1);
			_map[i].byteText.changeText(Byte::valueToHex(*(fieldPackage + i * 2)),
							&basicColors[*(fieldPackage + i * 2 + 1)]);
		}
		_map[i].carriageOn = false;
	}
}

//-----------------------------------------------------------------------------

void		Corewar::refreshData(uint8_t *fieldPackage)
{
	uint8_t		*carPack = fieldPackage + Corewar::fieldPackageSize;

	if (_processessValue.getText() != std::to_string(*((uint32_t *)(fieldPackage))))
		_processessValue.changeText(std::to_string(*((uint32_t *)(fieldPackage))), &basicColors[NO_PLAYER]);
	fieldPackage += 4;
	_processField(fieldPackage, Corewar::mapSize);
	for (uint32_t j = 0; j < Corewar::mapSize; ++j)
		_map.at(j).carriageOn = (bool) carPack[j];
	if (_cycleToDieValue.getText() != std::to_string(*((int32_t *)(fieldPackage + Corewar::mapSize * 2))))
		_cycleToDieValue.changeText(std::to_string(*((int32_t *)(fieldPackage + Corewar::mapSize * 2))), &basicColors[NO_PLAYER]);
	_iterationValue++;
	_iterationTextValue.changeText(std::to_string(_iterationValue), &basicColors[NO_PLAYER]);
}

//-----------------------------------------------------------------------------

void							Corewar::_drawField(uint16_t from, uint16_t to)
{
	while (from < to)
	{
		_map[from].byteText.draw();
		++from;
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
		byte.byteText.drawBackground(byte.carriageOn);
		byte.byteText.draw();
	}
	_cycleToDie.draw();
	_cycleToDieValue.draw();
	_processess.draw();
	_processessValue.draw();
	_iteration.draw();
	_iterationTextValue.draw();
}

//-----------------------------------------------------------------------------

void Corewar::drawWinner(Window *window)
{
	static Text winnerText = Text(("Winner is " + _players[winner - 1].idText.getText() +
										" " +
										  _players[winner - 1].nameText.getText()).c_str(),
										  		_font, (64 * (_byteWidth + _blankWidth)) + 25, 750,
										  		200, 300, &basicColors[winner], window->renderer);
	winnerText.draw();
}

//-----------------------------------------------------------------------------
