/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualization.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 12:37:29 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/03/04 12:14:29 by kpshenyc         ###   ########.fr       */
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
# include "/Users/kpshenyc/.brew/include/SDL2/SDL.h"
# include "/Users/kpshenyc/.brew/include/SDL2/SDL_ttf.h"
# include "/Users/kpshenyc/.brew/include/SDL2/SDL_image.h"
using std::string;
using std::vector;