/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:42:42 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/01 18:44:15 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "visualization.hpp"
# include "window.hpp"
# include "text.hpp"

enum								Players
{
	NO_PLAYER, FIRST, SECOND, THIRD, FOURTH
};

enum waitStatus
{
	NOT_WAITING, WAITING
};

class Corewar
{
	struct Player
	{
		Text						idText;
		Text						nameText;

		Player(const Player &right) noexcept;
		Player(Player &&right) noexcept;
		Player();
		~Player();
	};

	/*
		There are field of 4096 bytes.
		Each cell is represented by Byte structure
	*/
	struct Byte
	{
		uint8_t						value;
		int8_t						affectedBy;
		bool						changed;
		Byte();

		static string valueToHex(uint8_t value);
		/*
			Graphics information
		*/
		bool						carriageOn;
		Text						byteText;
	};

	void							_parseInitPackage(uint8_t *initPackage, Window *window);
	void							_initField(Window *window);
	void							_processField(uint8_t *fieldPackage, uint16_t cells);
	void							_drawField(uint16_t from, uint16_t to);
	/*
		Info that gets from buffer, and applies by Corewar::refreshData method;
	*/
	vector<Byte>					_map;			// perfectly buffer of 4096 Byte's samples

	Text							_iteration;
	Text							_iterationTextValue;
	uint32_t						_iterationValue;

	Text							_processess;
	Text							_processessValue;

	vector<Player>					_players;		// max - 4

	Text							_cycleToDie;
	Text							_cycleToDieValue;

	Text							_cycleDelta;
	Text							_nbrLive;
	Text							_maxChecks;

	/*
		Info about graphic components, render, etc.
	*/
	TTF_Font						*_font;
	int32_t							_startX;
	int32_t							_startY;
	int32_t							_byteWidth;
	int32_t							_byteHeight;
	int32_t							_blankWidth;
	int32_t							_blankHeight;

	public:
	Corewar(Window *window, uint8_t *initPackage);
	~Corewar();

	void							draw(Window *window);
	friend void 					drawMap(uint8_t *map);
	void							drawWinner(Window *window);
	void							drawInitData(Window *window);

	void							refreshData(uint8_t *fieldPackage);

	int8_t							winner;

	static constexpr int16_t		mapSize = 4096;
	static constexpr int16_t		initPackageSize = 529;
	static constexpr int16_t		fieldPackageSize = 8200;
	static constexpr int16_t		maxNameLength = 128;
	static constexpr uint8_t		byteOrder[17] = "0123456789abcdef";
};
