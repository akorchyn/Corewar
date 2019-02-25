/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:33:28 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/25 18:10:04 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <string>
# include "/Users/kpshenyc/.brew/include/SDL2/SDL.h"
# include "/Users/kpshenyc/.brew/include/SDL2/SDL_ttf.h"

class Window
{
	int				width = 2000;
	int				height = 2000;
	std::string		name = "Window";
	SDL_Window		*window = nullptr;
	int				closed = false;
	useconds_t		speed = 35000;
public:
	SDL_Renderer	*renderer = nullptr;
	Window(std::string name, int width, int height);
	useconds_t GetSpeed();
	bool isClosed();
	void poolEvents();
	void clear();
	~Window();
};
