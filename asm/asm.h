/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 18:19:37 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/14 18:26:00 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include <fcntl.h>

extern t_list	*g_instructions;

void			throw_error(int error_id, char *str);
void			parse_file(char *file_name);

typedef struct	s_instruction
{
	char		*instruction;
	t_list		*label;
	char		*instruction_code;
	size_t		instruction_size;
	size_t		global_size;
}				t_instruction;

#endif
