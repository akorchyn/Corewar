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

# define GET_INSTRUCTION(lst) ((t_instruction*)lst->content)

extern t_list	*g_instructions;

void			throw_error(int error_id, char *str);
void			parse_file(char *file_name);
void			set_inst_sizes(t_list *inst);
void			read_labels(t_list *inst);

typedef struct	s_lexem
{
	char		*command;
	t_list		*argument;
	char		*code;
	size_t		size;
}				t_lexem;

typedef struct	s_instruction
{
	char		*instruction;
	t_list		*label;
	t_lexem		lexem;
	size_t		global_size;
}				t_instruction;

#endif
