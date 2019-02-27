/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_package.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:47:33 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/27 17:14:17 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

unsigned char		*alloc_package(t_corewar *corewar)
{
	int32_t		buffer_size;

	buffer_size = 
		sizeof(int32_t) +
		sizeof(int8_t) +
		sizeof(int8_t) * (MEM_SIZE * 2) +
		sizeof(int16_t) * ft_list_counter((void **)(corewar->carriages)) +
		sizeof()
	return ((unsigned char *)malloc(sizeof(unsigned char) * buffer_size);
}

unsigned char		*create_package(t_corewar *corewar)
{
	unsigned char		*package;

	package = alloc_package(corewar);
	return (package);
}

