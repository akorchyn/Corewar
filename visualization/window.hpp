/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:33:28 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/01 12:38:59 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "visualization.hpp"

class Window
{
	int				width = 2000;
	int				height = 2000;
	std::string		name = "Window";
	SDL_Window		*window = nullptr;
	int				closed = false;
public:
	bool			preview;
	SDL_Renderer	*renderer = nullptr;
	Window(std::string name, int width, int height);
	bool isClosed();
	void poolEvents();
	void clear();
	~Window();
};
