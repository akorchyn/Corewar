/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:55:57 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/23 13:56:33 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft/include/libft.h"
# include <fcntl.h>
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
	int32_t			size_from_start;
}					t_instruction;

extern t_list		*g_instructions;

void				throw_error(int error_id, char *str, size_t line);
void				parse_file(char *file_name);
void				read_labels(t_list *inst);
void				read_command_argument(t_list *instruction);
void				calculate_sizes(t_list *instruction);
void				put_global_sizes(t_list *instruction);
void				parse_labels(t_list *instruction);

#endif
