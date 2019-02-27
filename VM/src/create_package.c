/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_package.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:47:33 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/27 17:57:58 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/vm.h"

/*
** Allocates memory for buffer, that consists:
** First	carriages count								( int32_t each )
** Next		players count								( int8_t each )
** Next		map + player those affected on each cell	( int8_t each )
** Next		carriages position							( int16_t each )
** Next		players data:
**						name,							( int8_t )
**						id,								( int8_t )
**						last live,						( int32_t )
**						lives in current period			( int32_t )
** Next		CYCLE_TO_DIE								( int32_t )
** Next		CYCLE_DELTA									( int32_t )
** Next		NBR_LIVE									( int32_t )
** Next		MAX_CHECKS									( int32_t )
*/

unsigned char		*alloc_package(t_corewar *corewar, int32_t carr_count)
{
	int32_t		buffer_size;
	int8_t		i;

	buffer_size = sizeof(int32_t) +
		sizeof(int8_t) +
		sizeof(int8_t) * ((MEM_SIZE) * 2) +
		sizeof(int16_t) * carr_count +
		(sizeof(int8_t) * (corewar->players * (
									sizeof(int8_t) * PROG_NAME_LENGTH +
									sizeof(int8_t) +
									sizeof(int32_t) * 2))) +
		sizeof(int32_t) * 4;
	return ((unsigned char *)malloc(sizeof(unsigned char) * buffer_size));
}

unsigned char		*create_package(t_corewar *corewar)
{
	unsigned char	*package;
	const int32_t	carr_count = ft_list_counter((void **)(corewar->carriages));

	package = alloc_package(corewar, carr_count);
	return (package);
}
