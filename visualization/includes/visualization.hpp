/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 12:37:29 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/08 16:29:02 by akorchyn         ###   ########.fr       */
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
# include <vector>
# include <string.h>
# include <utility>

# include <thread>
# include <mutex>
# include <future>
# include <SDL.h>
# include <SDL_ttf.h>
# include <SDL_image.h>

using std::string;
using std::vector;
