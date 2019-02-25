/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command16.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:46:39 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/25 21:55:06 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int32_t			g_id;

void		aff(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	if (bad_register_id(vars, carriage))
		return ;
	ft_printf("%c", (char)carriage->reg[vars->vars[0] - 1]);
	if (corewar->verbose & 4)
		ft_printf("P% 5d | aff r%hd", carriage->p_number,
									carriage->reg[vars->vars[0] - 1]);
}
