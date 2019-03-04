/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:38:06 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/28 17:49:22 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VM_H
# define COREWAR_VM_H

# include "op.h"
# include <errno.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include "../libft/includes/libft.h"
# include <signal.h>
extern int32_t			g_id;
extern int32_t			g_car_count;
extern char				*g_usage;
extern t_header			*g_header[MAX_PLAYERS];

typedef struct			s_carriage
{
	struct s_carriage	*next;
	struct s_carriage	*prev;
	uint32_t			reg[REG_NUMBER];
	t_header			*header;
	int32_t				counter;
	int32_t				last_live;
	int32_t				pause;
	int8_t				op_id;
	int8_t				id;
	uint8_t				carry : 1;
	int32_t				p_number;
	char				*code;
}						t_carriage;

typedef struct			s_corewar
{
	int8_t				*player_affected;
	unsigned char		*map;
	t_carriage			*carriages;
	int32_t				dump_drop;
	int32_t				iteration;
	int32_t				cycles_to_die;
	int32_t				count_live_for_cycle;
	int32_t				to_check;
	int8_t				verbose;
	int32_t				player_last_live;
	int8_t				count_checks;
	uint8_t				is_dump : 1;
	uint8_t				players;
	int					sock;
}						t_corewar;

typedef struct			s_variables
{
	int32_t				vars[MAX_ARGS_NUMBER];
	uint8_t				codage;
	int8_t				parsed_codage[MAX_ARGS_NUMBER];
	int8_t				bytes[MAX_ARGS_NUMBER];
	int16_t				skip;
}						t_vars;

typedef	void			(*t_dispatcher)(t_carriage *carriage,
									t_corewar *corewar, t_vars *vars);

/*
** PARSE SECTION
*/

void					parse_arguments(int ac, char **av, t_corewar *corewar,
									int16_t i);
int8_t					process_ids(t_carriage *carriages, int8_t players);

/*
** INITIALIZE SECTION
*/

void					initializing_dispatcher(t_dispatcher *dispatcher);
void					initializing(t_corewar *corewar);

/*
** LOOP SECTION
*/

void					cycle(t_corewar *corewar, t_dispatcher *disp);
void					dump_cycle(t_corewar *corewar, t_dispatcher *disp);

/*
** CODAGE SECTION (COLLECTING VARIABLES AND CHECKING THEM)
*/

int8_t					check_valid(t_carriage *pc, t_corewar *corewar,
									t_vars *vars);
void					get_variables(t_carriage *carriage, t_vars *vars,
									t_corewar *corewar);

/*
** DISPATCHER SECTION
*/

void					live(t_carriage *carriage, t_corewar *corewar,
									t_vars *vars);
void					st(t_carriage *carriage, t_corewar *corewar,
									t_vars *vars);
void					ld(t_carriage *carriage, t_corewar *corewar,
									t_vars *vars);
void					add(t_carriage *carriage, t_corewar *corewar,
									t_vars *vars);
void					sub(t_carriage *carriage, t_corewar *corewar,
									t_vars *vars);
void					and(t_carriage *carriage, t_corewar *corewar,
									t_vars *vars);
void					or(t_carriage *carriage, t_corewar *corewar,
									t_vars *vars);
void					xor(t_carriage *carriage, t_corewar *corewar,
									t_vars *vars);
void					zjmp(t_carriage *carriage, t_corewar *corewar,
									t_vars *vars);
void					ldi(t_carriage *carriage, t_corewar *corewar,
									t_vars *vars);
void					sti(t_carriage *carriage, t_corewar *corewar,
									t_vars *vars);
void					forks(t_carriage *carriage, t_corewar *corewar,
									t_vars *vars);
void					lld(t_carriage *carriage, t_corewar *corewar,
									t_vars *vars);
void					lldi(t_carriage *carriage, t_corewar *corewar,
									t_vars *vars);
void					lfork(t_carriage *carriage, t_corewar *corewar,
									t_vars *vars);
void					aff(t_carriage *carriage, t_corewar *corewar,
									t_vars *vars);
/*
** USEFUL FUNCTION SECTION
*/

void					send_init_package(t_corewar *corewar);
void					send_package(t_corewar *corewar);
int32_t					set_connection_to_visualization(char *ip, int16_t *i);
void					set_player(int8_t *map, int32_t counter,
									int32_t bytes, int8_t id);
int32_t					error(int code, char *msg, char *argument);
void					print_usage(char **av);
void					print_dump(uint8_t *map, int16_t bytes_in_line,
									int16_t size);
t_carriage				*extract_list(t_carriage **head, t_carriage *target);
void					sort_list(t_carriage **head);
int32_t					bytes_to_dec(unsigned char const *str, int16_t position,
									int32_t bytes);
int8_t					bad_register_id(t_vars *vars, t_carriage *carriage);
int32_t					shift(t_carriage *carriage, int32_t movement);
void					put_bytes(uint32_t value, unsigned char *placement,
									int16_t position, int8_t bytes);

#endif
