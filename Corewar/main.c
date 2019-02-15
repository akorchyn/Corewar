/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 23:43:59 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/15 15:27:52 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/vm.h"

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

void	add_to_register(unsigned char *value, size_t index, unsigned char *reg)
{
	size_t	move;
	int		i;
	int		j;

	i = -1;
	j = 0;
	move = 0;
	while (--index > 0)
		move += REG_SIZE;
	i = REG_SIZE;
	while (i--)
		reg[move + i] = value[j++];
	printf("%d\n", from_bytes_to_dec(reg + move, 4));
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
	if (!(new->reg = ft_memalloc(REG_SIZE * REG_NUMBER)))
		error(13, "Memory allocation failed", NULL);
	add_to_register((unsigned char *)(&(int){-2}), 1, new->reg);
	parse_file(fd, new);
	*head = new;
	close(fd);
	return (1);
}

int8_t		id_exists(t_carriage *carriages, int8_t id, t_carriage *self)
{
	while (carriages)
	{
		if (id == carriages->id && self != carriages)
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
//			(id_exists(head, new_id)) && (new_id--);
			prev_carriages = prev_carriages->next;
		}
		!(carriages->id) && (carriages->id = new_id);
		carriages = carriages->next;
	}
	return (1);
}

void	parse_arguments(int ac, char **av, t_corewar *corewar)
{
	register int8_t		i;
	int8_t				number;

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

int32_t		main(int ac, char **av)
{
	t_corewar		corewar;

	ft_bzero(&corewar, sizeof(corewar));
	parse_arguments(ac, av, &corewar);
	while (corewar.carriages)
	{
		ft_printf("%d\n", corewar.carriages->id);
		corewar.carriages = corewar.carriages->next;
	}
	return (0);
}
