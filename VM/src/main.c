/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 23:43:59 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/19 10:47:04 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		live(t_carriage *carriage, t_corewar *corewar) // Наверное неправильная
{
	if ((int32_t)from_bytes_to_dec(corewar->map + carriage->counter + 1,
				DIR_SIZE) == -carriage->id)
	{
		corewar->player_last_live = carriage->id;
		corewar->count_live_for_cycle++;
		carriage->last_live = corewar->iteration;
	}
}

void		ld(t_carriage *carriage, t_corewar *corewar)
{
	uint64_t		value;
	uint64_t		position;
	uint64_t		codage;
	uint32_t		arg1;
	uint32_t		arg2;

	codage = from_bytes_to_dec(corewar->map + carriage->counter + 1, 1);
	arg2 = from_bytes_to_dec(corewar->map + carriage->counter + 2 + REG_SIZE,
			REG_SIZE);
	if (codage >> 6 == IND_CODE)
	{
		arg1 = from_bytes_to_dec(corewar->map + carriage->counter + 2,
				IND_SIZE);
		position = (carriage->counter + (arg1 % IDX_MOD)) % MEM_SIZE;
		value = from_bytes_to_dec(corewar->map + position, REG_SIZE);
	}
	else
		value = from_bytes_to_dec(corewar->map + carriage->counter + 2,
								DIR_SIZE);
	if (arg2 > 0 && arg2 <= REG_NUMBER)
	{
		carriage->carry = (value == 0) ? 1 : 0;
		carriage->reg[arg2 - 1] = value;
	}
}

//void		st(t_carriage *carriage, t_corewar *corewar)
//{
//	uint64_t		value;
//	uint64_t		position;
//	uint64_t		codage;
//	uint32_t		arg1;
//	uint32_t		arg2;
//}

int32_t		main(int ac, char **av)
{
	t_corewar		corewar;
	t_dispatcher	dispatcher[16];

	ft_bzero(&corewar, sizeof(corewar));
	parse_arguments(ac, av, &corewar);
	initializing(&corewar);
	initializing_op_tab();
	initializing_dispatcher(dispatcher);
	return (0);
}
