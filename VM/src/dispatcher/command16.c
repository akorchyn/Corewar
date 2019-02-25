/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command16.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:46:39 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/25 16:49:57 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int32_t			g_id;

void		aff(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	UNUSED_VARIABLE(corewar);
	if (bad_register_id(vars, carriage))
		return ;
	ft_printf("P%5d | %c", carriage->p_number, (char)carriage->reg[vars->vars[0] - 1]);
}
