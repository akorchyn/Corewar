/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:32:57 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/22 17:05:57 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualization.hpp"
#include <iostream>

# define WIDTH 5120
# define HEIGHT 2880

void choose_sizes(int *square_size, int *stride, int rows, int columns)
{
	if (rows >= 99 && columns >= 99)
	{
		*square_size = HEIGHT/rows - 7;
		*stride = 3;
	}
	else
	{
		*square_size = HEIGHT/rows - 36;
		*stride = 7;
	}
}

int		main(void)
{
	Window window("Filler", WIDTH, HEIGHT);

	char buff[INPUT_BUFF_SIZE];
	memset(buff, 1, INPUT_BUFF_SIZE);

	std::string first_player;
	std::string second_player;

	while (std::cin.getline(buff, INPUT_BUFF_SIZE) && strstr(buff, "exec") == NULL);

	char *last = strrchr(buff, '/') + 1;

	for (int i = 0; last[i] && last[i] != ']'; ++i)
		first_player += last[i];

	while (std::cin.getline(buff, INPUT_BUFF_SIZE) && strstr(buff, "exec") == NULL);

	last = strrchr(buff, '/') + 1;

	for (int i = 0; last[i] && last[i] != ']'; ++i)
		second_player += last[i];


	while (std::cin.getline(buff, INPUT_BUFF_SIZE) && strstr(buff, "Plateau") == NULL);

	int rows, columns;
	rows = atoi(strchr(buff, ' ') + 1);
	columns = atoi(strchr(strchr(buff, ' ') + 1, ' ') + 1);

	int square_size;
	int stride;

	choose_sizes(&square_size, &stride, rows, columns);

	Grid grid{&window, _2DPoint{WIDTH/2 - ((columns/2) * (square_size + stride)), HEIGHT/2 - ((rows/2) * (square_size + stride))},
								rows, columns, square_size, square_size, stride};
	grid.SetGrid();

	TTF_Font *font = TTF_OpenFont("visualizationSDL/fonts/joystix monospace.ttf", 100);
	SDL_Surface *textSurface = TTF_RenderText_Solid(font, first_player.c_str(), SDL_Color{ 165, 44, 60, 255 });
	SDL_Texture *text = SDL_CreateTextureFromSurface(window.renderer, textSurface);
	SDL_Rect textRect;
	textRect.x = textRect.y = 0;
	SDL_QueryTexture(text, NULL, NULL, &textRect.w, &textRect.h);


	SDL_Surface *textSurface1 = TTF_RenderText_Solid(font, second_player.c_str(), SDL_Color{ 60, 60, 165, 255 });
	SDL_Texture *text1 = SDL_CreateTextureFromSurface(window.renderer, textSurface1);
	SDL_Rect textRect1;
	textRect1.x = 3600;
	textRect1.y = 0;
	SDL_QueryTexture(text1, NULL, NULL, &textRect1.w, &textRect1.h);

	std::string first_player_score = "";
	std::string second_player_score = "";

	SDL_Surface *textSurface2 = nullptr;
	SDL_Texture *text2 = nullptr;
	SDL_Rect textRect2;
	textRect2.x = 0;
	textRect2.y = 2775;


	SDL_Surface *textSurface3 = nullptr;
	SDL_Texture *text3 = nullptr;
	SDL_Rect textRect3;
	textRect3.x = 4800;
	textRect3.y = 2775;


	while (!window.isClosed())
	{
		if (first_player_score != "" && second_player_score != "" && textSurface2 == nullptr)
		{
			textSurface2 = TTF_RenderText_Solid(font, first_player_score.c_str(), SDL_Color{ 165, 44, 60, 255 });
			text2 = SDL_CreateTextureFromSurface(window.renderer, textSurface2);
			SDL_QueryTexture(text2, NULL, NULL, &textRect2.w, &textRect2.h);

			textSurface3 = TTF_RenderText_Solid(font, second_player_score.c_str(), SDL_Color{ 60, 60, 165, 255 });
			text3 = SDL_CreateTextureFromSurface(window.renderer, textSurface3);
			SDL_QueryTexture(text3, NULL, NULL, &textRect3.w, &textRect3.h);
		}
		else if (textSurface2 != nullptr)
		{
			SDL_RenderCopy(window.renderer, text2, nullptr, &textRect2);
			SDL_RenderCopy(window.renderer, text3, nullptr, &textRect3);
		}
		while (std::cin.getline(buff, INPUT_BUFF_SIZE) && *buff)
			if (buff[4] == '0')
				break ;
			else if (strstr(buff, "== O fin:") != NULL)
				first_player_score = strrchr(buff, ' ') + 1;
			else if (strstr(buff, "== X fin:") != NULL)
				second_player_score = strrchr(buff, ' ') + 1;
		if (*buff)
		{
			grid.ReadInputSetColors();
			grid.draw();
		}
		else
			grid.draw();
		SDL_RenderCopy(window.renderer, text, nullptr, &textRect);
		SDL_RenderCopy(window.renderer, text1, nullptr, &textRect1);
		window.poolEvents();
		window.clear();
		usleep(window.GetSpeed());
	}
	SDL_DestroyTexture(text);
	SDL_DestroyTexture(text1);
	SDL_DestroyTexture(text2);
	SDL_DestroyTexture(text3);
	return (0);
}
