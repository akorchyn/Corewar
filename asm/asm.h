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

# include <fcntl.h>
# include "libft.h"
# include "op.h"

# define GET_INSTRUCTION(lst) ((t_instruction*)lst->content)

typedef struct		s_lexem
{
	char			*command;
	t_list			*argument;
	char			*code;
	size_t			size;
}					t_lexem;

typedef struct		s_instruction
{
	char			*instruction;
	size_t			line;
	t_list			*label;
	t_lexem			lexem;
	size_t			global_size;
}					t_instruction;

//typedef void 		(*t_size_count)(t_lexem *lexem, size_t line);

extern t_list		*g_instructions;
//extern t_size_count	g_size_count_array[16];

void				throw_error(int error_id, char *str, size_t line);
void				parse_file(char *file_name);
void				set_inst_sizes(t_list *inst);
void				read_labels(t_list *inst);
void				count_live(t_lexem *lexem, size_t line);
void				count_ld(t_lexem *lexem, size_t line);
void				count_st(t_lexem *lexem, size_t line);
void				count_add(t_lexem *lexem, size_t line);

#endif
