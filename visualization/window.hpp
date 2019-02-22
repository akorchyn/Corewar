/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:33:28 by kpshenyc          #+#    #+#             */
/*   Updated: 2018/12/28 13:33:30 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

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

#endif
