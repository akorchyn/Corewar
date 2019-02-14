/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:38:06 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/14 23:39:06 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VM_H
#define COREWAR_VM_H

# include "op.h"
# include <errno.h>
# include "../libft/includes/libft.h"

# define DEBUG 1

# pragma pack(1)

typedef struct			s_carriage
{
	struct s_carriage	*next;
	void				*reg;
	header_t			header;
	int32_t				counter;
	int32_t				step_size;
	int32_t 			last_live;
	int32_t 			pause;
	int8_t				player;
	uint8_t				carry : 1;
	char				*code;
}						t_carriage;

typedef struct			s_corewar
{
	char				*map;
	t_carriage			*carriages;
	int32_t				dump_drop;
	int32_t				iteration;
	uint8_t				is_dump : 1;
}						t_corewar;

#endif
