/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:38:06 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/14 17:09:45 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VM_H
#define COREWAR_VM_H

# include "op.h"
# include "../libft/includes/libft.h"

# define ERROR(x, str) if (x) {write(2, str, ft_strlen(str)); exit(x);}

# define DEBUG 1

# pragma pack(1)

typedef struct			s_carriage
{
	struct s_carriage	*next;
	void				*reg;
	int32_t				counter;
	int32_t				step_size;
	int32_t 			last_live;
	int32_t 			pause;
	int16_t				size;
	int8_t				player;
	uint8_t				carry : 1;
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
