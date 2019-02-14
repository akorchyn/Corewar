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
			corewar->iteration = ft_atoi(av[i]);
		}
		else if (!ft_strcmp("-n", av[i]))
		{
			!ft_isnumeric(av[++i], '\0') && error(1, "Dump error", av[i]);
			create_carriage(av[i + 1], &corewar->carriages);
			corewar->carriages->player = ft_atoi(av[i++]);
		}
	}
}

int 	main(int ac, char **av)
{
	t_corewar		corewar;

	ft_bzero(&corewar, sizeof(corewar));
	parse_arguments(ac, av, &corewar);
	return 0;
}
