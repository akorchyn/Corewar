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

extern char		*g_file;
extern t_list	*g_instructions;

void		throw_error(int error_id, char *str);
void		read_file(char *file_name);
void		split_instructions(void);

typedef struct	s_instruction
{
	char		*instruction;
	char		**inst_content;
	size_t		instruction_size;
}				t_insturction;

typedef struct	s_label
{

}				t_label;

#endif
