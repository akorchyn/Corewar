/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:42:42 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/27 19:31:48 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <iostream>
# include "window.hpp"
# include <vector>

enum								Players
{
	NO_PLAYER, FIRST, SECOND, THIRD, FOURTH
};

using	std::vector;
using	std::string;

class Corewar
{

	struct Player
	{
		int8_t						id;
		string						name;
		int32_t						lastLive;
		int32_t						livesCurrentPeriod;
	};
	struct Byte
	{
		unsigned char				value;
		int8_t						owner;
		int8_t						changed;
		void						valueToHex(unsigned char value);
		Byte();

		/*
			Graphics information
		*/
		string						hexText;
		SDL_Color					*color;
		SDL_Rect					position;
		SDL_Surface					*byteSurface;
		SDL_Texture					*byteTexture;
	};

	/*
		Info that gets from buffer, and applies by Corewar::refreshData method;
	*/
	unsigned char					_initPackage[]
	vector<Byte>					_map;			// perfectly buffer of 4096 Byte's samples
	int32_t							_iteration;
	int16_t							_processess;
	vector<Player>					_players;		// max - 4
	int32_t							_cycleToDie;
	int32_t							_cycleDelta;
	int32_t							_nbrLive;
	int32_t							_maxChecks;

	/*
		Info about graphic components, render, etc.
	*/
	TTF_Font						*font;
	int32_t							startX;
	int32_t							startY;
	int32_t							byteWidth;
	int32_t							byteHeight;
	int32_t							blankWidth;
	int32_t							blankHeight;

	public:
	static constexpr int16_t		MAP_SIZE = 4096;
	static constexpr unsigned char	byteOrder[17] = "0123456789abcdef";

	Corewar(Window *window);
	~Corewar();

	void							draw(Window *window);
	void							refreshData(unsigned char *buffer);
};
