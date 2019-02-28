/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 09:51:52 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/26 16:19:15 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			parse_file(int32_t fd, t_carriage *new)
{
	unsigned char		buff[HEADER_SIZE + 1];
	uint32_t			ret;

	ret = read(fd, buff, HEADER_SIZE);
	(ret != HEADER_SIZE) && error(7, "Bad file", NULL);
	new->header->magic = bytes_to_dec(buff, 0, 4);
	if (new->header->magic != COREWAR_EXEC_MAGIC)
		error(8, "Bad magic number", NULL);
	ft_strncpy(new->header->prog_name, (char *)buff + MAGIC_LENGTH,
			PROG_NAME_LENGTH);
	new->header->prog_size = bytes_to_dec(buff, MAGIC_LENGTH
							+ PROG_NAME_LENGTH + NULL_SIZE, PROG_SIZE_LENGTH);
	if (new->header->prog_size > CHAMP_MAX_SIZE)
		error(9, "Exec code too big.", NULL);
	ft_strncpy(new->header->comment, (char *)buff + MAGIC_LENGTH +
			PROG_NAME_LENGTH + NULL_SIZE + PROG_SIZE_LENGTH, COMMENT_LENGTH);
	if (!(new->code = (char *)malloc(new->header->prog_size + 1)))
		error(10, "Memory allocation failed", NULL);
	ret = read(fd, new->code, new->header->prog_size + 1);
	if (ret != new->header->prog_size)
		error(11, "Exec code's size differs from the given one.", NULL);
	new->code[ret] = '\0';
}

static int8_t		create_carriage(char *file, t_carriage **head)
{
	int32_t		fd;
	size_t		len;
	t_carriage	*nw;

	!file && error(3, "Filename is missing", NULL);
	len = ft_strlen(file);
	ft_strcmp(file + len - 4, ".cor") && error(4, "Invalid file", file);
	(fd = open(file, O_RDONLY)) == -1 && error(5, strerror(errno), file);
	if (!(nw = (t_carriage *)ft_memalloc(sizeof(t_carriage))))
		error(6, "Memory allocation failed", NULL);
	if (!(nw->header = (t_header *)malloc(sizeof(t_header))))
		error(18, "Memory allocation failed", NULL);
	nw->next = *head;
	if (*head)
		(*head)->prev = nw;
	nw->prev = NULL;
	parse_file(fd, nw);
	*head = nw;
	close(fd);
	return (1);
}

static int8_t		id_exists(t_carriage *carriages, int8_t id)
{
	while (carriages)
	{
		if (id == carriages->id)
			return (1);
		carriages = carriages->next;
	}
	return (0);
}

int8_t				process_ids(t_carriage *carriages, int8_t players)
{
	t_carriage	*prev_carriages;
	t_carriage	*head;
	int8_t		new_id;

	new_id = players;
	head = carriages;
	while (carriages)
	{
		prev_carriages = head;
		if (carriages->id > players)
			error(15, "Uniq id is bigger than players count", NULL);
		while (prev_carriages)
		{
			(carriages->id == prev_carriages->id && prev_carriages != carriages
				&& carriages->id) && error(16, "Uniq id is repeating", NULL);
			(id_exists(head, new_id)) && (new_id--);
			prev_carriages = prev_carriages->next;
		}
		!(carriages->id) && (carriages->id = new_id);
		carriages->p_number = carriages->id;
		carriages = carriages->next;
	}
	return (1);
}

void				parse_arguments(int ac, char **av, t_corewar *corewar,
			int16_t i)
{
	while (++i < ac)
		if (!ft_strcmp("-dump", av[i]) || !ft_strcmp("-d", av[i]))
		{
			!ft_isnumeric(av[++i], '\0') && error(1, "Dump error", av[i]);
			corewar->is_dump = 1;
			corewar->dump_drop = ft_atoi(av[i]);
		}
		else if (!ft_strcmp("-n", av[i]))
		{
			!ft_isnumeric(av[++i], '\0') && error(2, "Number error", av[i]);
			create_carriage(av[i + 1], &corewar->carriages)
					&& ++corewar->players;
			if (!(corewar->carriages->id = ft_atoi(av[i++])))
				error(14, "Uniq id can't be null", av[i - 1]);
		}
		else if (!ft_strcmp("-v", av[i]))
		{
			!ft_isnumeric(av[++i], '\0') && error(2, "Verbose error", av[i]);
			corewar->verbose = ft_atoi(av[i]);
		}
		else if (!ft_strcmp("-visual", av[i]))
			corewar->sock = set_connection_to_visualization(av[i + 1], &i);
		else
			create_carriage(av[i], &corewar->carriages) && ++(corewar->players);
}
