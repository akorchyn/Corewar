/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 12:35:54 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/01 15:32:42 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "text.hpp"

//-----------------------------------------------------------------------------

int16_t				Text::getLength()
{
	return _text.length() * _charWidth;
}

//-----------------------------------------------------------------------------

void		Text::draw()
{
	SDL_RenderCopy(_renderer, _textTexture, nullptr, &_textRect);
}

//-----------------------------------------------------------------------------

void		Text::dynamicDraw(int16_t x, int16_t y)
{
	_textRect.x = x;
	_textRect.y = y;

	draw();
}

//-----------------------------------------------------------------------------

void		Text::_initGraphicsInfo()
{
	_textSurface = TTF_RenderText_Solid(_font, _text.c_str(), *(_color));
	_textTexture = SDL_CreateTextureFromSurface(_renderer, _textSurface);

	_textRect.w = _charWidth * _text.length();
	_textRect.h = _charHeight;

	_textRect.x = _xPos;
	_textRect.y = _yPos;

	std::cout << "w: " << _textRect.w << " h: " << _textRect.h << " x: " << _textRect.x << " y: " << _textRect.y << std::endl;

	SDL_QueryTexture(_textTexture, nullptr, nullptr, &(_textRect.w), &(_textRect.h));
}

//-----------------------------------------------------------------------------

Text::Text()
{
	_textSurface = nullptr;
	_textTexture = nullptr;
}

//-----------------------------------------------------------------------------

Text::Text(string text, string fontName, int16_t fontSize,
		int16_t xPos, int16_t yPos, int16_t charWidth, int16_t charHeight,
		SDL_Color *color, SDL_Renderer *renderer) :
	_text(text), _font(TTF_OpenFont(fontName.c_str(), fontSize)), _fontSize(fontSize),
	_xPos(xPos), _yPos(yPos), _charWidth(charWidth), _charHeight(charHeight),
	_color(color), _commonFont(false), _renderer(renderer)
{
	if (!_font)
	{
		std::cerr << TTF_GetError() << std::endl;
		std::cerr << "Font isn't opened in object with text: " << text << std::endl;
		exit(EXIT_FAILURE);
	}
	_initGraphicsInfo();
}

//-----------------------------------------------------------------------------

Text::Text(string text, TTF_Font *font,
		int16_t xPos, int16_t yPos, int16_t charWidth, int16_t charHeight,
		SDL_Color *color, SDL_Renderer *renderer) :
	_text(text), _font(font),
	_xPos(xPos), _yPos(yPos), _charWidth(charWidth), _charHeight(charHeight),
	_color(color), _commonFont(true), _renderer(renderer)
{
	if (!_font)
	{
		std::cerr << TTF_GetError() << std::endl;
		std::cerr << "Bad font passed in object with text: " << text << std::endl;
		exit(EXIT_FAILURE);
	}
	_initGraphicsInfo();	
}

//-----------------------------------------------------------------------------

Text::Text(Text &&right)
{
	_renderer = right._renderer;
	right._renderer = nullptr;
	_textSurface = right._textSurface;
	right._textSurface = nullptr;
	_textTexture = right._textTexture;
	right._textTexture = nullptr;
	_textRect = right._textRect;
	_color = right._color;
	_text = right._text;
	_fontSize = right._fontSize;
	_font = right._font;
	_commonFont = right._font;
	_charHeight = right._charHeight;
	_charWidth = right._charWidth;
	_xPos = right._xPos;
	_yPos = right._yPos;
}

//-----------------------------------------------------------------------------

Text::~Text()
{
	if (_textSurface != nullptr)
		SDL_FreeSurface(_textSurface);
	if (_textTexture != nullptr)
		SDL_DestroyTexture(_textTexture);
	if (!_commonFont)
		TTF_CloseFont(_font);
}

//-----------------------------------------------------------------------------

Text&			Text::operator=(Text &&right)
{
	_renderer = right._renderer;
	right._renderer = nullptr;
	_textSurface = right._textSurface;
	right._textSurface = nullptr;
	_textTexture = right._textTexture;
	right._textTexture = nullptr;
	_textRect = right._textRect;
	_color = right._color;
	_text = right._text;
	_fontSize = right._fontSize;
	_font = right._font;
	_commonFont = right._font;
	_charHeight = right._charHeight;
	_charWidth = right._charWidth;
	_xPos = right._xPos;
	_yPos = right._yPos;
	return *this;
}

//-----------------------------------------------------------------------------