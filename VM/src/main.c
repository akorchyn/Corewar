/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 23:43:59 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/22 18:31:51 by kpshenyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

/*
 * CHECK FOR CARRY GAGNANT DOESNT WORK
 */


#include "vm.h"

int			bad_register_id(t_vars *vars, t_carriage *carriage)
{
	int8_t		i;

	i = -1;
	while (++i < g_op_tab[carriage->operation_id].variables)
	{
		if (vars->parsed_codage[i] == T_REG
			&& (vars->vars[i] < 1 || vars->vars[i] > REG_NUMBER))
			return (1);
	}
	return (0);
}

void		set_operation_code(t_carriage *carriage, t_corewar *corewar)
{
	int32_t		operation;

	if (!carriage)
		return ;
	set_operation_code(carriage->next, corewar);
	if (carriage->pause)
		return ;
	operation = bytes_to_dec(corewar->map + carriage->counter, 1);
	carriage->operation_id = operation - 1;
	carriage->pause = (operation > 0 && operation < OPERATIONS + 1)
			? g_op_tab[operation - 1].pause
			: 0;
}

void		decrement_pause(t_carriage *carriage)
{
	if (!carriage)
		return ;
	decrement_pause(carriage->next);
	if (carriage->pause > 0)
		carriage->pause--;
}

int8_t		check_codage(t_carriage *carriage, t_vars *vars)
{
	int8_t		value;
	int8_t		shift;
	int8_t		counter;

	counter = g_op_tab[carriage->operation_id].variables;
	shift = 2 + (2 * (3 - g_op_tab[carriage->operation_id].variables));
	while (--counter > -1)
	{
		value = (vars->codage >> shift) & 0b11;
		if (value == REG_CODE)
			vars->parsed_codage[counter] = T_REG;
		else if (value == IND_CODE)
			vars->parsed_codage[counter] = T_IND;
		else if (value == DIR_CODE)
			vars->parsed_codage[counter] = T_DIR;
		else
			vars->parsed_codage[counter] = 0;
		shift += 2;
	}
	while (++counter < g_op_tab[carriage->operation_id].variables)
		if (!(g_op_tab[carriage->operation_id].vars[counter]
			& vars->parsed_codage[counter]))
			return (0);
	return ((int8_t)(vars->codage << counter * 2) == 0 ? 1 : 0);
}

int32_t			get_step_size(t_carriage *const carriage, t_vars *vars)
{
	int32_t		result;
	int8_t		i;
	int8_t		type;

	result = 0;
	i = -1;
	while (++i < g_op_tab[carriage->operation_id].variables)
	{
		type = (vars->codage) ? vars->parsed_codage[i]
							: g_op_tab[carriage->operation_id].vars[i];
		if (type == T_IND)
			(vars->bytes_codage[i] = IND_BYTES) && (result += IND_BYTES);
		else if (type == T_DIR)
		{
			vars->bytes_codage[i] = (g_op_tab[carriage->operation_id].is_ind)
					? IND_BYTES : DIR_BYTES;
			result += vars->bytes_codage[i];
		}
		else if (type == T_REG)
			(vars->bytes_codage[i] = REG_BYTES) && (result += REG_BYTES);
	}
	if (vars->codage)
		result += 1;
	return (result + 1);
}

void		get_variables(t_carriage *carriage, t_vars *vars,
		t_corewar *corewar)
{
	int8_t		i;
	int32_t		memory_shift;
	int32_t		read_bytes;

	i = -1;
	read_bytes = 0;
	while (++i < g_op_tab[carriage->operation_id].variables)
	{
		memory_shift = (carriage->counter + read_bytes +
				g_op_tab[carriage->operation_id].is_codage) % MEM_SIZE;
		vars->vars[i] = bytes_to_dec(corewar->map + memory_shift + 1,
				vars->bytes_codage[i]);
		read_bytes += vars->bytes_codage[i];
	}
}

void		live(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	ft_printf("live : %hd\n", vars->vars[0]);
	if (vars->vars[0] != -carriage->id)
		return ;
	corewar->player_last_live = carriage->id;
	corewar->count_live_for_cycle++;
	carriage->last_live = corewar->iteration;
}

void		ld(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int32_t		address;

	if (bad_register_id(vars, carriage))
		return ;
	if (vars->parsed_codage[0] == T_DIR)
	{
		carriage->reg[vars->vars[1] - 1] = vars->vars[0];
		carriage->carry = (vars->vars[0]) ? 0 : 1;
		ft_printf("ld : %d r%hd\n", carriage->reg[vars->vars[1] - 1], vars->vars[1]);
		return ;
	}
	address = (carriage->counter + (int16_t)vars->vars[0] % IDX_MOD) % MEM_SIZE;
	carriage->reg[vars->vars[1] - 1] = bytes_to_dec(corewar->map + address,
			REG_SIZE);
	carriage->carry = carriage->reg[vars->vars[1] - 1] ? 0 : 1;
	ft_printf("ld : %hd r%hd\n", carriage->reg[vars->vars[1] - 1], vars->vars[1]);
}

void		st(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int32_t		address;

	if (bad_register_id(vars, carriage))
		return ;
	if (vars->parsed_codage[1] == REG_CODE)
	{
		carriage->reg[vars->vars[1] - 1] = carriage->reg[vars->vars[0] - 1];
		ft_printf("st : r%hd r%hd\n", vars->vars[0], vars->vars[1]);
		return ;
	}
	address = (carriage->counter + (int16_t)vars->vars[1] % IDX_MOD) % MEM_SIZE;
	put_bytes(carriage->reg[vars->vars[0] - 1], corewar->map + address,
																	REG_SIZE);
	ft_printf("st : r%hd %hd\n", vars->vars[0], vars->vars[1]);
}

void		add(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	UNUSED_VARIABLE(corewar);
	if (bad_register_id(vars, carriage))
		return ;
	carriage->reg[vars->vars[2] - 1] = carriage->reg[vars->vars[0] - 1]
			+ carriage->reg[vars->vars[1] - 1];
	carriage->carry = (carriage->reg[vars->vars[2]] - 1) ? 0 : 1;
	ft_printf("add : r%d r%d r%d\n", vars->vars[0], vars->vars[1], vars->vars[2]);
}

void		sub(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	UNUSED_VARIABLE(corewar);
	if (bad_register_id(vars, carriage))
		return ;
	carriage->reg[vars->vars[2] - 1] = carriage->reg[vars->vars[0] - 1]
											- carriage->reg[vars->vars[1] - 1];
	carriage->carry = (carriage->reg[vars->vars[2]] - 1) ? 0 : 1;
	ft_printf("sub : r%hd r%hd r%hd\n", vars->vars[0], vars->vars[1], vars->vars[2]);
}

void		and(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int8_t		i;
	int64_t		values[2];

	i = -1;
	if (bad_register_id(vars, carriage))
		return ;
	while (++i < 2)
	{
		if (vars->parsed_codage[i] == T_REG)
			values[i] = carriage->reg[vars->vars[i] - 1];
		else if (vars->parsed_codage[i] == T_DIR)
			values[i] = vars->vars[i];
		else if (vars->parsed_codage[i] == T_IND)
			values[i] = bytes_to_dec(corewar->map + (carriage->counter +
					(int16_t)vars->vars[i] % IDX_MOD) % MEM_SIZE, 4);
	}
	carriage->reg[vars->vars[2] - 1] = values[0] & values[1];
	carriage->carry = carriage->reg[vars->vars[2] - 1] == 0 ? 1 : 0;
	ft_printf("and : %hd %hd r%hd\n", values[0], values[1], vars->vars[2]);
}

void		or(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int8_t		i;
	int64_t		values[2];

	i = -1;
	if (bad_register_id(vars, carriage))
		return ;
	while (++i < 2)
	{
		if (vars->parsed_codage[i] == T_REG)
			values[i] = carriage->reg[vars->vars[i] - 1];
		else if (vars->parsed_codage[i] == T_DIR)
			values[i] = vars->vars[i];
		else if (vars->parsed_codage[i] == T_IND)
			values[i] = bytes_to_dec(corewar->map + (carriage->counter +
					(int16_t)vars->vars[i] % IDX_MOD) % MEM_SIZE, 4);
	}
	carriage->reg[vars->vars[2] - 1] = values[0] | values[1];
	carriage->carry = carriage->reg[vars->vars[2] - 1] == 0 ? 1 : 0;
	ft_printf("or : %hd %hd r%hd\n", values[0], values[1], vars->vars[2]);
}

void		xor(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int8_t		i;
	int64_t		values[2];

	i = -1;
	if (bad_register_id(vars, carriage))
		return ;
	while (++i < 2)
	{
		if (vars->parsed_codage[i] == T_REG)
			values[i] = carriage->reg[vars->vars[i] - 1];
		else if (vars->parsed_codage[i] == T_DIR)
			values[i] = vars->vars[i];
		else if (vars->parsed_codage[i] == T_IND)
			values[i] = bytes_to_dec(corewar->map + (carriage->counter +
					(int16_t)vars->vars[i] % IDX_MOD) % MEM_SIZE, 4);
	}
	carriage->reg[vars->vars[2] - 1] = values[0] ^ values[1];
	carriage->carry = carriage->reg[vars->vars[2] - 1] == 0 ? 1 : 0;
	ft_printf("xor : %hd %hd r%hd\n", values[0], values[1], vars->vars[2]);
}

void		zjmp(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	UNUSED_VARIABLE(corewar);
	if (carriage->carry)
	{
		ft_printf("zjmp : %hd OK\n", vars->vars[0]);
		carriage->step_size = 0;
		carriage->counter = (carriage->counter
				+ ((int16_t )vars->vars[0]% IDX_MOD)) % MEM_SIZE;
	}
	else
		ft_printf("zjmp : %hd FAILED\n", vars->vars[0]);
}

void		ldi(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int32_t		values[2];

	if (bad_register_id(vars, carriage))
		return ;
	if (vars->parsed_codage[0] == T_REG)
		values[0] = carriage->reg[vars->vars[0] - 1];
	else if (vars->parsed_codage[0] == T_IND)
		values[0] = bytes_to_dec(corewar->map + (carriage->counter +
				(int16_t)vars->vars[0] % IDX_MOD) % MEM_SIZE, REG_SIZE);
	else
		values[0] = vars->vars[0];
	values[1] = (vars->parsed_codage[2] == T_REG) ?
						carriage->reg[vars->vars[1] - 1] : vars->vars[1];
	carriage->reg[vars->vars[2] - 1] = bytes_to_dec(corewar->map +
			(carriage->counter + (values[0] + values[1]) % IDX_MOD) % MEM_SIZE,
																	REG_SIZE);
	ft_printf("ldi : %hd %hd r%hd\n", values[0], values[1], vars->vars[2]);
}

void		sti(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int32_t		values[2];

	if (bad_register_id(vars, carriage))
		return ;
	if (vars->parsed_codage[1] == T_REG)
		values[0] = carriage->reg[vars->vars[1] - 1];
	else if (vars->parsed_codage[1] == T_IND)
		values[0] = bytes_to_dec(corewar->map + (carriage->counter +
					(int16_t)vars->vars[1] % IDX_MOD) % MEM_SIZE, REG_SIZE);
	else
		values[0] = vars->vars[1];
	values[1] = (vars->parsed_codage[2] == T_REG)
				? carriage->reg[vars->vars[2] - 1] : vars->vars[2];
	put_bytes(carriage->reg[vars->vars[0] - 1], corewar->map +
		(carriage->counter + (values[0] + values[1]) % IDX_MOD) % MEM_SIZE,
															REG_SIZE);
	ft_printf("sti : r%hd %hd %hd\n", vars->vars[0], values[0], values[1]);
}

void		forks(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	t_carriage		*new;

	if (!(new = (t_carriage *)ft_memalloc(sizeof(t_carriage))))
		error(55, "Allocation memory to new carriage failed.", NULL);
	ft_memcpy(new, carriage, sizeof(t_carriage));
	new->counter = (new->counter + (int16_t )vars->vars[0] % IDX_MOD)
										% MEM_SIZE;
	new->next = corewar->carriages;
	corewar->carriages = new;
	ft_printf("fork : %hd (%hd)\n", vars->vars[0], new->counter);
}

void		lld(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int32_t		address;

	if (bad_register_id(vars, carriage))
		return ;
	if (vars->parsed_codage[0] == T_DIR)
	{
		carriage->reg[vars->vars[1] - 1] = vars->vars[0];
		carriage->carry = (vars->vars[0]) ? 0 : 1;
		ft_printf("lld : %hd r%hd", vars->vars[0], vars->vars[1]);
		return ;
	}
	address = (carriage->counter + (int16_t)vars->vars[0]) % MEM_SIZE;
	carriage->reg[vars->vars[1] - 1] = bytes_to_dec(corewar->map + address,
			REG_SIZE);
	carriage->carry = carriage->reg[vars->vars[1] - 1] ? 0 : 1;
	ft_printf("lld : %hd r%hd", vars->vars[0], vars->vars[1]);
}

void		lldi(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	int32_t		values[2];

	if (bad_register_id(vars, carriage))
		return ;
	if (vars->parsed_codage[0] == T_REG)
		values[0] = carriage->reg[vars->vars[0] - 1];
	else if (vars->parsed_codage[0] == T_IND)
		values[0] = bytes_to_dec(corewar->map + (carriage->counter +
				(int16_t)vars->vars[0] % IDX_MOD) % MEM_SIZE, REG_SIZE);
	else
		values[0] = vars->vars[0];
	values[1] = (vars->parsed_codage[2] == T_REG) ?
						carriage->reg[vars->vars[1] - 1] : vars->vars[1];
	carriage->reg[vars->vars[2] - 1] = bytes_to_dec(corewar->map +
			(carriage->counter + values[0] + values[1]) % MEM_SIZE, REG_SIZE);
	ft_printf("lldi : %hd %hd r%hd", values[0], values[1], vars->vars[2]);
}

void		lfork(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	t_carriage		*new;

	if (!(new = (t_carriage *)ft_memalloc(sizeof(t_carriage))))
		error(55, "Allocation memory to new carriage failed.", NULL);
	ft_memcpy(new, carriage, sizeof(t_carriage));
	new->counter = (new->counter + vars->vars[0]) % MEM_SIZE;
	new->next = corewar->carriages;
	corewar->carriages = new;
	ft_printf("lfork : %hd (%hd)\n", vars->vars[0], new->counter);
}

void		aff(t_carriage *carriage, t_corewar *corewar, t_vars *vars)
{
	UNUSED_VARIABLE(corewar);
	if (bad_register_id(vars, carriage))
		return ;
	ft_printf("%c", (char)carriage->reg[vars->vars[0] - 1]);
}

void		draw_map(t_corewar *corewar)
{
	int i = 0;
	char hex[16] = "0123456789abcdef";
	while (i < 4096)
	{
		int j = -1;
		while (++j < 64)
		{
			write(1, &hex[*(corewar->map + i + j) / 16], 1);
			write(1, &hex[*(corewar->map + i + j) % 16], 1);
			write(1, " ", 1);
		}
		write(1, "\n", 1);
		i += 64;
	}
	usleep(10000);
	system("clear");
}

void		operation(t_corewar *corewar, t_dispatcher *dispatcher,
		t_carriage *carriage)
{
	t_vars		vars;

	if (!carriage)
		return ;
	if (!carriage->pause)
	{
		if (carriage->operation_id > -1 && carriage->operation_id < OPERATIONS)
		{
			ft_bzero(&vars, sizeof(t_vars));
			if (g_op_tab[carriage->operation_id].is_codage)
				vars.codage = bytes_to_dec(corewar->map + carriage->counter + 1,
										   1);
			if (!vars.codage || check_codage(carriage, &vars))
			{
				carriage->step_size = get_step_size(carriage, &vars);
				get_variables(carriage, &vars, corewar);
				dispatcher[carriage->operation_id](carriage, corewar, &vars);
			} else
				carriage->step_size = get_step_size(carriage, &vars);
			carriage->counter = (carriage->counter + carriage->step_size)
								% MEM_SIZE;
		} else
			carriage->counter = (carriage->counter + 1) % MEM_SIZE;
		carriage->operation_id = 0;
	}
	operation(corewar, dispatcher, carriage->next);
}

void		cycle_to_die(t_corewar *corewar, t_carriage *carriages)
{
	if (--corewar->to_check > 0)
		return ;
	while (carriages)
	{
		if (corewar->iteration - carriages->last_live >= corewar->cycles_to_die)
		{
			corewar->carriages = extract_list(&corewar->carriages, carriages);
			free(carriages);
		}
		carriages->last_live = 0;
		carriages = carriages->next;
	}
	if (corewar->count_live_for_cycle >= NBR_LIVE ||
											corewar->count_checks == MAX_CHECKS)
	{
		corewar->count_checks = 1;
		corewar->cycles_to_die -= CYCLE_DELTA;
	}
	else
		corewar->count_checks++;
	corewar->to_check = corewar->cycles_to_die;
	corewar->count_live_for_cycle = 0;
}

void		cycle(t_corewar *corewar, t_dispatcher *dispatcher, int sock)
{
	while (corewar->carriages)
	{
		send(sock, corewar->map, 4096, 0);
		corewar->iteration++;
		set_operation_code(corewar->carriages, corewar);
		decrement_pause(corewar->carriages);
		operation(corewar, dispatcher, corewar->carriages);
		cycle_to_die(corewar, corewar->carriages);
	}
	ft_printf("%d\n", corewar->iteration);
	ft_printf("ctd: %d\n", corewar->cycles_to_die);
}

int			set_connection_to_visualization()
{
	int sock;
	char *msg;

	msg = "Connection is set!\n";
	sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(4242);
	server_address.sin_addr.s_addr = INADDR_ANY;
	if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
	{
		ft_printf("Shit happened. You cannot connect to the server...");
		exit(EXIT_FAILURE);
	}
	send(sock, msg, sizeof(msg), 0);
	return (sock);
}

int32_t		main(int ac, char **av)
{
	t_corewar		corewar;
	t_dispatcher	dispatcher[16];
	int				sock;

	if (ac > 1 && !ft_strcmp(av[1], "-n"))
		sock = set_connection_to_visualization();
	else
		sock = 0;
	ft_bzero(&corewar, sizeof(corewar));
	parse_arguments(ac, av, &corewar);
	!(corewar.players_count) ? error(200, "No players.", NULL) : 0;
	initializing(&corewar);
	initializing_dispatcher(dispatcher);
	cycle(&corewar, dispatcher, sock);
	close(sock);
	return (0);
}
