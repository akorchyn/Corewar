/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_dispatcher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:49:28 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/23 16:58:34 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int8_t			bad_register_id(t_vars *vars, t_carriage *carriage)
{
	int8_t		i;

	i = -1;
	while (++i < g_op_tab[carriage->op_id].variables)
	{
		if (vars->parsed_codage[i] == T_REG
			&& (vars->vars[i] < 1 || vars->vars[i] > REG_NUMBER))
			return (1);
	}
	return (0);
}

int16_t			shift(t_carriage *carriage, int16_t movement)
{
	return ((carriage->counter + movement % IDX_MOD + MEM_SIZE) % MEM_SIZE);
}
