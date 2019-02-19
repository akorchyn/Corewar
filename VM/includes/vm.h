/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:38:06 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/19 09:09:10 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VM_H
#define COREWAR_VM_H

# include "op.h"
# include <errno.h>
# include "../libft/includes/libft.h"

# define SUCCESS 1
# define FAILURE 0
# define DEBUG 1


typedef struct			s_carriage
{
	struct s_carriage	*next;
	int64_t				reg[16];
	header_t			header;
	int32_t				counter;
	int32_t				step_size;
	int32_t 			last_live;
	int32_t 			pause;
	int8_t				id;
	uint8_t				carry : 1;
	char				*code;
}						t_carriage;

typedef struct			s_corewar
{
	unsigned char		*map;
	t_carriage			*carriages;
	int32_t				dump_drop;
	int32_t				iteration;
	int32_t 			cycles_to_die;
	int32_t				count_live_for_cycle;
	int32_t				to_check;
	int32_t				player_last_live;
	uint8_t				is_dump : 1;
	uint8_t				players_count;
}						t_corewar;

typedef					void (*t_dispatcher)(t_carriage *carriage,
		t_corewar *corewar);

#endif
