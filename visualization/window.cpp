/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 13:33:23 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/04 12:23:53 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.hpp"

Window::Window(std::string name, int width, int height)
{
	this->width = width;
	this->height = height;
	this->name = name;
	this->preview = true;
	this->isStoped = true;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL_INIT_VIDEO::ERROR" << std::endl;
		closed = true;
		return ;
	}

	if (TTF_Init() != 0)
	{
		std::cerr << "TTF_INIT::ERROR" << std::endl;
		closed = true;
		return ;
	}

	this->window = SDL_CreateWindow(this->name.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			this->width,
			this->height,
			SDL_WINDOW_BORDERLESS);

	if (this->window == nullptr)
	{
		std::cerr << "CREATE_WINDOW::ERROR" << std::endl;
		closed = true;
		return ;
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);

	if (this->renderer == nullptr)
	{
		std::cerr << "CREATE_RENDERER::ERROR" << std::endl;
	}
}

Window::~Window()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

bool Window::isClosed()
{
	return (closed) ? true : false;
}

void Window::poolEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event))
	{
			if (event.type == SDL_QUIT)
				this->closed = true;
			else if (event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE: this->closed = true; break;
					case SDLK_RETURN: 
					{
						if (this->preview == true)
							this->preview = false;
						break ;
					}
					case SDLK_SPACE:
					{
						this->isStoped = this->isStoped ? false : true;
					}
					default:
						break;
				}
			}
		}
	}

void Window::clear()
{
	SDL_RenderPresent(this->renderer);
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
	SDL_RenderClear(this->renderer);
}

