/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 12:35:47 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/01 16:42:51 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "visualization.hpp"

class Text
{
	SDL_Renderer	*_renderer;
	SDL_Surface		*_textSurface;
	SDL_Texture		*_textTexture;
	SDL_Rect		_textRect;
	SDL_Color		*_color;

	string			_text;
	int16_t			_fontSize;
	TTF_Font		*_font;
	bool			_commonFont;

	int16_t			_charHeight;
	int16_t			_charWidth;

	int16_t			_xPos;
	int16_t			_yPos;

	void			_initGraphicsInfo();

	public:
	Text();
	Text(string text, string fontName, int16_t fontSize,
		int16_t xPos, int16_t yPos, int16_t charWidth, int16_t charHeight,
		SDL_Color *color, SDL_Renderer *renderer);
	Text(string text, TTF_Font *font,
		int16_t xPos, int16_t yPos, int16_t charWidth, int16_t charHeight,
		SDL_Color *color, SDL_Renderer *renderer);
	~Text();
	Text(const Text &right) noexcept;
	Text(Text &&right) noexcept;
	void			draw();
	void			dynamicDraw(int16_t x, int16_t y);
	int16_t			getLength();

	Text&			operator=(const Text &right) noexcept;
	Text&			operator=(Text &&right) noexcept;
};