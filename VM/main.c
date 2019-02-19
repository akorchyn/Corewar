/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 23:43:59 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/19 09:34:23 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vm.h"

t_op				g_op_tab[17];

int32_t				error(int code, char *msg, char *argument)
{
	ft_putstr_fd(msg, 2);
	if (argument)
	{
		ft_putstr_fd(" on argument:\n", 2);
		ft_putstr_fd(argument, 2);
	}
	ft_putstr_fd("\n", 2);
	exit(code);
	return (1);
}

/*
** Function translate from some bytes to one united number;
**
** EXAMPLE: 1th byte - ff 2nd byte - ff
** 			Result of work 65535 (0xffff)
*/

uint32_t			from_bytes_to_dec(unsigned char const *str, int32_t bytes)
{
	uint32_t		res;
	int32_t			i;
	int32_t			number;

	res = 0;
	i = -1;
	while (++i < bytes)
	{
		number = str[i];
		res <<= 8;
		res |= number;
	}
	return (res);
}

void		parse_file(int32_t fd, t_carriage *new)
{
	unsigned char		buff[HEADER_SIZE + 1];
	int32_t				ret;

	ret = read(fd, buff, HEADER_SIZE);
	(ret != HEADER_SIZE) && error(7, "Bad file", NULL);
	new->header.magic = from_bytes_to_dec(buff, 4);
	if (new->header.magic != COREWAR_EXEC_MAGIC)
		error(8, "Bad magic number", NULL);
	ft_strncpy(new->header.prog_name, (char *)buff + MAGIC_LENGTH,
							PROG_NAME_LENGTH);
	new->header.prog_size = from_bytes_to_dec(buff + MAGIC_LENGTH
							+ PROG_NAME_LENGTH + NULL_SIZE, PROG_SIZE_LENGTH);
	if (new->header.prog_size > CHAMP_MAX_SIZE)
		error(9, "Exec code too big.", NULL);
	ft_strncpy(new->header.comment, (char *)buff + MAGIC_LENGTH +
			PROG_NAME_LENGTH + NULL_SIZE + PROG_SIZE_LENGTH, COMMENT_LENGTH);
	if (!(new->code = (char *)malloc(sizeof(char) * new->header.prog_size + 1)))
		error(10, "Memory allocation failed", NULL);
	ret = read(fd, new->code, new->header.prog_size + 1);
	if (ret != new->header.prog_size)
		error(11, "Exec code's size differs from the given one.", NULL);
	new->code[ret] = '\0';
}

int8_t			create_carriage(char *file, t_carriage **head)
{
	int32_t		fd;
	size_t		len;
	t_carriage	*new;

	!file && error(3, "Filename is missing", NULL);
	len = ft_strlen(file);
	ft_strcmp(file + len - 4, ".cor") && error(4, "Invalid file", file);
	(fd = open(file, O_RDONLY)) == -1 && error(5, strerror(errno), file);
	if (!(new = (t_carriage *)malloc(sizeof(t_carriage))))
		error(6, "Memory allocation failed", NULL);
	ft_bzero(new, sizeof(t_carriage));
	new->next = *head;
	parse_file(fd, new);
	*head = new;
	close(fd);
	return (1);
}

int8_t		id_exists(t_carriage *carriages, int8_t id)
{
	while (carriages)
	{
		if (id == carriages->id)
			return (1);
		carriages = carriages->next;
	}
	return (0);
}

int8_t		process_ids(t_carriage *carriages, int8_t players_count)
{
	t_carriage	*prev_carriages;
	t_carriage	*head;
	int8_t		new_id;

	new_id = players_count;
	head = carriages;
	while (carriages)
	{
		prev_carriages = head;
		if (carriages->id > players_count)
			error(15, "Uniq id is bigger than players count", NULL);
		while (prev_carriages)
		{
			(carriages->id == prev_carriages->id && prev_carriages != carriages
				&& carriages->id) && error(16, "Uniq id is repeating", NULL);
			(id_exists(head, new_id)) && (new_id--);
			prev_carriages = prev_carriages->next;
		}
		DEBUG && ft_printf("%d\n", new_id);
		!(carriages->id) && (carriages->id = new_id);
		carriages = carriages->next;
	}
	return (1);
}

void	parse_arguments(int ac, char **av, t_corewar *corewar)
{
	register int8_t		i;

	i = 0;
	while (++i < ac)
	{
		if (!ft_strcmp("-dump", av[i]))
		{
			!ft_isnumeric(av[++i], '\0') && error(1, "Dump error", av[i]);
			corewar->is_dump = 1;
			corewar->dump_drop = ft_atoi(av[i]);
		}
		else if (!ft_strcmp("-n", av[i]))
		{
			!ft_isnumeric(av[++i], '\0') && error(2, "Number error", av[i]);
			create_carriage(av[i + 1], &corewar->carriages) && (corewar->players_count)++;
			if (!(corewar->carriages->id = ft_atoi(av[i++])))
				error(14, "Uniq id can't be null", av[i - 1]);
		}
		else
			create_carriage(av[i], &corewar->carriages) && corewar->players_count++;
	}
	process_ids(corewar->carriages, corewar->players_count);
	DEBUG && ft_printf("Dump on: %d\n", corewar->is_dump);
}

void		introduction(t_carriage *tmp)
{
	if (!tmp)
	{
		ft_printf("Introducing contestants...\n");
		return;
	}
	introduction(tmp->next);
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\")\n",
			tmp->id, tmp->header.prog_size, tmp->header.prog_name,
			tmp->header.comment);
}

t_carriage		*extract_list(t_carriage **head, t_carriage *target)
{
	t_carriage		*prev;
	t_carriage		*tmp;

	tmp = *head;
	prev = NULL;
	if (*head == target)
	{
		*head = (*head)->next;
		return (*head);
	}
	while (tmp)
	{
		if (tmp == target)
		{
			if (prev)
				prev->next = tmp->next;
			return (*head);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (*head);
}

void		sort_list(t_carriage **head)
{
	t_carriage	*new_list;
	t_carriage	*tmp;
	int8_t		id;

	id = 1;
	tmp = *head;
	new_list = NULL;
	while (tmp)
	{
		if (id == tmp->id)
		{
			*head = extract_list(head, tmp);
			tmp->next = new_list;
			new_list = tmp;
			id++;
			tmp = *head;
		}
		else
			tmp = tmp->next;
	}
	*head = new_list;
}

void		initializing(t_corewar *corewar)
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
		ft_memcpy(corewar->map + tmp->counter, tmp->code, tmp->header.prog_size);
		free(tmp->code);
		(DEBUG) && ft_printf("%d id Counter : %d\n", tmp->id, tmp->counter);
		tmp = tmp->next;
	}
	introduction(corewar->carriages);
	(DEBUG) && ft_printf("%100.*m", MEM_SIZE, corewar->map);
}

void		live(t_carriage *carriage, t_corewar *corewar) // Наверное неправильная
{
	if (from_bytes_to_dec(corewar->map + carriage->counter + 1, DIR_SIZE)
				== -carriage->id)
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

void		st(t_carriage *carriage, t_corewar *corewar)
{
	uint64_t		value;
	uint64_t		position;
	uint64_t		codage;
	uint32_t		arg1;
	uint32_t		arg2;

}

void		initializing_dispatcher(t_dispatcher *dispatcher)
{
	dispatcher[0] = live;
	dispatcher[1] = ld;
	dispatcher[2] = NULL;
	dispatcher[3] = NULL;
	dispatcher[4] = NULL;
	dispatcher[5] = NULL;
	dispatcher[6] = NULL;
	dispatcher[7] = NULL;
	dispatcher[8] = NULL;
	dispatcher[9] = NULL;
	dispatcher[10] = NULL;
	dispatcher[11] = NULL;
	dispatcher[12] = NULL;
	dispatcher[13] = NULL;
	dispatcher[14] = NULL;
	dispatcher[15] = NULL;
}

void		initializing_op_tab()
{
	g_op_tab[0] = (t_op){"live", 1, {T_DIR}, 1, 10, "alive", 0, 0};
	g_op_tab[1] = (t_op){"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0};
	g_op_tab[2] = (t_op){"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0};
	g_op_tab[3] = (t_op){"add", 3, {T_REG, T_REG, T_REG}, 4, 10,
					  "addition", 1, 0};
	g_op_tab[4] = (t_op){"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction",
					  1, 0};
	g_op_tab[5] = (t_op){"and", 3,
					  {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
					  6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0};
	g_op_tab[6] = (t_op){"or", 3,
					  {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
					  7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0};
	g_op_tab[7] = (t_op){"xor", 3,
					  {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
					  8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0};
	g_op_tab[8] = (t_op){"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1};
	g_op_tab[9] = (t_op){"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG,
								 T_REG}, 10, 25, "load index", 1, 1};
	g_op_tab[10] = (t_op){"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG,
								  T_REG}, 10, 25, "load index", 1, 1};
	g_op_tab[11] = (t_op){"sti", 3, {T_REG, T_REG | T_DIR | T_IND,
								  T_DIR | T_REG}, 11, 25, "store index", 1, 1};
	g_op_tab[12] = (t_op){"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1};
	g_op_tab[13] = (t_op){"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10,
					   "long load", 1, 0};
	g_op_tab[14] = (t_op){"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG,
								   T_REG}, 14, 50, "long load index", 1, 1};
	g_op_tab[15] = (t_op){"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1};
	g_op_tab[16] = (t_op){"aff", 1, {T_REG}, 16, 2, "aff", 1, 0};
}

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
