#include <vm.h>

int		error(int code, char *msg, char *argument)
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

void	create_carriage(char *file, t_carriage **head)
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
	*head = new;
	close(fd);
}

void	parse_arguments(int ac, char **av, t_corewar *corewar)
{
	int8_t		i;
	int8_t		number;

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

int 	main(int ac, char **av)
{
	t_corewar		corewar;

	ft_bzero(&corewar, sizeof(corewar));
	parse_arguments(ac, av, &corewar);
	return 0;
}
