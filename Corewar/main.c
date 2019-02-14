#include "vm.h"

int32_t		error(int code, char *msg, char *argument)
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

uint32_t			from_bytes_to_dec(uint8_t const *str, int32_t bytes)
{
	uint8_t		buff[bytes * 2];
	int32_t		i;
	int32_t		number;
	int32_t		counter;
	uint32_t 	res;

	counter = -1;
	i = 0;
	while (++counter < bytes)
	{
		number = str[counter] / 16;
		buff[i++] = (number < 10) ? number + '0' : 'a' + (number - 10);
		number = str[counter] % 16;
		buff[i++] = (number < 10) ? number + '0' : 'a' + (number - 10);
	}
	counter = 0;
	res = 0;
	bytes *= 2;
	while (bytes--)
	{
		number = (ft_isdigit(buff[bytes]))	? buff[bytes] - '0'
											: 10 + (buff[bytes] - 'a');
		res += number * ft_pow(16, counter++);
	}
	return (res);
}

void		parse_file(int32_t fd, t_carriage *new)
{
	uint8_t		buff[HEADER_SIZE + 1];
	int32_t		ret;

	ret = read(fd, buff, HEADER_SIZE);
	(ret != HEADER_SIZE) && error(7, "Bad file", NULL);
	new->header.magic = from_bytes_to_dec(buff, 4);
	if (new->header.magic != COREWAR_EXEC_MAGIC)
		error(8, "Bad magic number", NULL);

}

void			create_carriage(char *file, t_carriage **head)
{
	int32_t		fd;
	size_t 		len;
	t_carriage	*new;

	!file && error(3, "Filename is missing", NULL);
	len = ft_strlen(file);
	ft_strcmp(file + len - 4, ".cor") && error(4, "Invalid file", file);
	(fd = open(file, O_RDONLY)) == -1 && error(5, strerror(errno), file);
	if (!(new = (t_carriage *)malloc(sizeof(t_carriage))))
		error(6, "Memory allocation error", NULL);
	new->next = *head;
	parse_file(fd, new);
	*head = new;
	close(fd);
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
			create_carriage(av[i + 1], &corewar->carriages);
//			corewar->carriages->player = ft_atoi(av[i++]);
		}
		else
			create_carriage(av[i], &corewar->carriages);
	}
	DEBUG && ft_printf("Dump on: %d\n", corewar->is_dump);
}

int32_t 	main(int ac, char **av)
{
	t_corewar		corewar;

	ft_bzero(&corewar, sizeof(corewar));
	parse_arguments(ac, av, &corewar);
	return 0;
}
