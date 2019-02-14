/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:38:06 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/14 16:50:25 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VM_H
#define COREWAR_VM_H

# include "op.h"
# include "../libft/includes/libft.h"

typedef struct			s_carriage
{
	struct s_carriage	*next;
	int32_t				counter;
	int32_t				step_size;
	int32_t 			last_live;
	int32_t 			pause;
	int8_t				player;
	uint8_t				carry : 1;
	void				*reg;

}						t_carriage;

typedef struct			s_corewar
{
	char				*map;
	t_carriage			*carriages;
	uint8_t				is_dump : 1;
	int32_t				dump_drop;
	int32_t				iteration;
}						t_corewar;

#endif
