/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:38:06 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/14 16:38:08 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VM_H
#define COREWAR_VM_H

# include "op.h"
# include "../libft/includes/libft.h"

typedef struct			s_carriage
{
	struct s_carriage	*next;
	int 				counter;
	int 				step_size;
	int 				last_live;
	int 				pause;
	char				player;
	unsigned char		carry : 1;
	void				*reg;

}						t_carriage;

typedef struct			s_corewar
{
	char				*map;
	t_carriage			*carriages;
}						t_corewar;

#endif
