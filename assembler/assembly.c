/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembly.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:14:26 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/02/28 15:14:34 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	get_executable(t_list *lst)
{
	uint32_t	counter;

	counter = 0;
	g_header.executable = malloc(g_header.prog_size);
	while (lst)
	{
		ft_memcpy(g_header.executable + counter,
		GET_INSTRUCTION(lst)->lexem.code, GET_INSTRUCTION(lst)->lexem.size);
		counter += GET_INSTRUCTION(lst)->lexem.size;
		lst = lst->next;
	}
}

void		assembly(t_list **instr_list, char *file_content, char *file_name)
{
	*instr_list = split_instr(file_content);
	free(file_content);
	check_name_comment(*instr_list, instr_list);
	read_labels(*instr_list);
	read_command_argument(*instr_list);
	calculate_sizes(*instr_list);
	put_global_sizes(*instr_list);
	parse_labels(*instr_list, *instr_list);
	parse_inst_code(*instr_list);
	get_executable(*instr_list);
	write_champion(file_name);
}
