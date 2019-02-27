/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_package.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:47:33 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/27 19:31:44 by kpshenyc         ###   ########.fr       */
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

unsigned char		*alloc_package(t_corewar *corewar, int32_t *size)
{
	int8_t		i;

	*size = sizeof(int32_t) +
		sizeof(int8_t) +
		sizeof(int8_t) * ((MEM_SIZE) * 2) +
		sizeof(int16_t) * g_car_count +
		(sizeof(int8_t) * (corewar->players * (
									sizeof(int8_t) * PROG_NAME_LENGTH +
									sizeof(int8_t) +
									sizeof(int32_t) * 2))) +
		sizeof(int32_t) * 4;
	return ((unsigned char *)malloc(sizeof(unsigned char) * *size));
}

void				fill_package(t_corewar *corewar, unsigned char *package)
{
	int32_t			i;
	int32_t			step;
	t_carriage		*tmp;

	step = 0;
	ft_memcpy(package, &g_car_count, (step += sizeof(int32_t)));
	ft_memcpy(package + step++, &(corewar->players), 1);
	i = -1;
	while (++i < MEM_SIZE)
	{
		package[step++] = corewar->map[i];
		package[step++] = corewar->player_affected[i];
	}
	tmp = corewar->carriages;
	while (tmp)
	{
		ft_memcpy(package + step, tmp->counter, 2);
		step += 2;
		tmp = tmp->next;
	}
	
}

void				send_package(t_corewar *corewar)
{
	unsigned char	*package;
	int32_t			size;

	package = alloc_package(corewar, &size);
	fill_package(corewar, package);
	send(corewar->sock, package, size, 0);
	free(package);
}
