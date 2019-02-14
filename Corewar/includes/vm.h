#ifndef COREWAR_VM_H
#define COREWAR_VM_H

# include "op.h"
# include "../libft/includes/libft.h"

typedef struct			s_carriage
{
	struct s_carriage	*next;
	int 				counter;
	int 				step_size;
	int 				last_live;
	int 				pause;
	char				player;
	unsigned char		carry : 1;
	void				*reg;

}						t_carriage;

typedef struct			s_corewar
{
	char				*map;
	t_carriage			*carriages;
}						t_corewar;

#endif
