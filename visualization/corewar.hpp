/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 16:42:42 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/28 18:11:20 by kpshenyc         ###   ########.fr       */
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
# include <string.h>

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

		SDL_Surface					*idSurface;
		SDL_Texture					*idTexture;
		SDL_Rect					idRect;

		SDL_Surface					*nameSurface;
		SDL_Texture					*nameTexture;
		SDL_Rect					nameRect;
	};

	/*
		There are field of 4096 bytes.
		Each cell is represented by Byte structure
	*/
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

	void							_parseInitPackage(uint8_t *initPackage, Window *window);
	void							_initField(Window *window);
	
	/*
		Info that gets from buffer, and applies by Corewar::refreshData method;
	*/
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
	void							drawInitData(Window *window);
	void							refreshData(uint8_t *package);

	static constexpr int16_t		mapSize = 4096;
	static constexpr int16_t		initPackageSize = 529;
	static constexpr int16_t		maxNameLength = 128;
	static constexpr unsigned char	byteOrder[17] = "0123456789abcdef";
};
