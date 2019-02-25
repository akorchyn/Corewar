/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 16:38:06 by kpshenyc          #+#    #+#             */
/*   Updated: 2019/02/25 16:30:59 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_VM_H
# define COREWAR_VM_H

# include "op.h"
# include <errno.h>
# include "../libft/includes/libft.h"

# define SUCCESS 1
# define FAILURE 0
# define DEBUG 0

# define UNUSED_VARIABLE(x) x = NULL

extern int32_t			g_id;

typedef struct			s_carriage
{
	struct s_carriage	*next;
	struct s_carriage	*prev;
	uint32_t			reg[16];
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
	unsigned char		*map;
	t_carriage			*carriages;
	int32_t				dump_drop;
	int32_t				iteration;
	int32_t				cycles_to_die;
	int32_t				count_live_for_cycle;
	int32_t				to_check;
	int32_t				player_last_live;
	int8_t				count_checks;
	uint8_t				is_dump : 1;
	uint8_t				players_count;
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

void					parse_arguments(int ac, char **av, t_corewar *corewar);

/*
** INITIALIZE SECTION
*/

void					initializing_dispatcher(t_dispatcher *dispatcher);
void					initializing(t_corewar *corewar, t_header **header);


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

int32_t					error(int code, char *msg, char *argument);
t_carriage				*extract_list(t_carriage **head, t_carriage *target);
void					sort_list(t_carriage **head, t_corewar *corewar);
int32_t					bytes_to_dec(unsigned char const *str, int16_t position,
										int32_t bytes);
int8_t					bad_register_id(t_vars *vars, t_carriage *carriage);
int16_t					shift(t_carriage *carriage, int16_t movement);
void					put_bytes(uint32_t value, unsigned char *placement,
								  int16_t position, int8_t bytes);

#endif
