/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 22:52:51 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/25 23:07:06 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			get_variables(t_carriage *carriage, t_vars *vars,
						t_corewar *corewar)
{
	int8_t		i;
	int32_t		memory_shift;
	int32_t		read_bytes;

	i = -1;
	read_bytes = 0;
	while (++i < g_op_tab[carriage->op_id].variables)
	{
		memory_shift = (carriage->counter + read_bytes +
						g_op_tab[carriage->op_id].is_codage) % MEM_SIZE;
		vars->vars[i] = bytes_to_dec(corewar->map, memory_shift + 1,
									vars->bytes[i]);
		read_bytes += vars->bytes[i];
	}
}

static uint8_t	generate_cadage(int8_t op_num)
{
	uint8_t		value;
	int8_t		i;

	value = 0;
	i = -1;
	while (++i < MAX_ARGS_NUMBER)
	{
		value <<= 2;
		if (g_op_tab[op_num].vars[i] == T_REG)
			value |= T_REG;
		else if (g_op_tab[op_num].vars[i] == T_IND)
			value |= T_IND;
		else if (g_op_tab[op_num].vars[i] == T_DIR)
			value |= T_DIR;
	}
	return (value);
}

static void		get_info_from_cadage(t_vars *vars, int8_t value, int8_t i,
								int8_t op_id)
{
	if (value == REG_CODE)
	{
		vars->parsed_codage[i] = T_REG;
		vars->bytes[i] = REG_BYTES;
	}
	else if (value == IND_CODE)
	{
		vars->parsed_codage[i] = T_IND;
		vars->bytes[i] = IND_BYTES;
	}
	else if (value == DIR_CODE)
	{
		vars->parsed_codage[i] = T_DIR;
		(vars->bytes[i] = (int8_t)((g_op_tab[op_id].is_ind)
								? IND_BYTES : DIR_BYTES));
	}
	else
		vars->parsed_codage[i] = 0;
}

int8_t			check_valid(t_carriage *pc, t_corewar *corewar, t_vars *vars)
{
	int8_t	shift;
	int8_t	value;
	int8_t	i;
	int8_t	answer;

	vars->codage = (g_op_tab[pc->op_id].is_codage)
				? bytes_to_dec(corewar->map, pc->counter + 1, 1)
				: generate_cadage(pc->op_id);
	(g_op_tab[pc->op_id].is_codage) ? vars->skip++ : 0;
	shift = 6;
	i = 0;
	answer = 1;
	while (shift > 0)
	{
		value = (int8_t)((vars->codage >> shift) & 0b11);
		get_info_from_cadage(vars, value, i, pc->op_id);
		if (!(vars->parsed_codage[i] & g_op_tab[pc->op_id].vars[i]
			|| vars->parsed_codage[i] == g_op_tab[pc->op_id].vars[i])
			&& g_op_tab[pc->op_id].vars[i])
			answer = 0;
		if (g_op_tab[pc->op_id].vars[i])
			vars->skip += vars->bytes[i];
		i++;
		shift -= 2;
	}
	return (answer);
}
