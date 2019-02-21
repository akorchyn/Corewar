/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 09:40:23 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/21 16:50:13 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"

t_op	g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

static void		introduction(t_carriage *tmp)
{
	if (!tmp)
	{
		ft_printf("Introducing contestants...\n");
		return ;
	}
	introduction(tmp->next);
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")\n",
			tmp->id, tmp->header.prog_size, tmp->header.prog_name,
			tmp->header.comment);
}

void			initializing(t_corewar *corewar)
{
	t_carriage		*tmp;
	int32_t			distance;

	if (ft_list_counter((void **)corewar->carriages) > MAX_PLAYERS)
		error(17, "Too many players.", NULL);
	if (!(corewar->map = (unsigned char *)ft_memalloc(sizeof(char) * MEM_SIZE)))
		error(18, "Allocation battle arena failed.", NULL);
	sort_list(&corewar->carriages);
	corewar->player_last_live = corewar->carriages->id;
	corewar->count_live_for_cycle = CYCLE_TO_DIE;
	corewar->cycles_to_die = CYCLE_TO_DIE;
	distance = MEM_SIZE / corewar->players_count;
	tmp = corewar->carriages;
	while (tmp)
	{
		tmp->reg[0] = -tmp->id;
		tmp->counter = distance * (tmp->id - 1);
		ft_memcpy(corewar->map + tmp->counter, tmp->code,
				tmp->header.prog_size);
		free(tmp->code);
		(DEBUG) && ft_printf("%d id Counter : %d\n", tmp->id, tmp->counter);
		tmp = tmp->next;
	}
	introduction(corewar->carriages);
	(DEBUG) && ft_printf("%100.*m", MEM_SIZE, corewar->map);
}

void			initializing_dispatcher(t_dispatcher *dispatcher)
{
	dispatcher[0] = live;
	dispatcher[1] = ld;
	dispatcher[2] = st;
	dispatcher[3] = add;
	dispatcher[4] = sub;
	dispatcher[5] = and;
	dispatcher[6] = or;
	dispatcher[7] = xor;
	dispatcher[8] = zjmp;
	dispatcher[9] = ldi;
	dispatcher[10] = sti;
	dispatcher[11] = fork;
	dispatcher[12] = lld;
	dispatcher[13] = lldi;
	dispatcher[14] = lfork;
	dispatcher[15] = aff;
}
