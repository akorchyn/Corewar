/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 13:36:00 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/03/12 13:37:07 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft/include/libft.h"
# include <fcntl.h>
# include <stdint.h>

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define COMMENT_CHAR			'#'
# define ALT_COMMENT_CHAR		';'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define REGISTRY_CHAR			'r'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"
# define COREWAR_NULL			"\0\0\0\0"

# define REG_NUMBER				16

# define T_REG					1
# define T_DIR					2
# define T_IND					4

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_NULL_LENGTH	(4)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct					s_header
{
	unsigned int				magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	unsigned int				prog_size;
	char						comment[COMMENT_LENGTH + 1];
}								t_header;

typedef struct					s_op
{
	char						*name;
	uint8_t						arg_count;
	uint8_t						argument[3];
	uint8_t						index;
	uint16_t					pause_value;
	char						*comment;
	uint8_t						has_arg_type : 1;
	uint8_t						ind_dir : 1;
}								t_op;

typedef struct					s_label
{
	char						*label_name;
	size_t						label_value;
}								t_label;

typedef struct					s_instruction
{
	uint8_t						op_index;
	uint8_t						op_size;
	uint32_t					size_here;
	t_list						*argument;
	size_t						line_nb;
}								t_instruction;

extern t_op						g_op_tab[17];
extern t_header					g_header;
extern size_t					g_line;
extern t_list					*g_label_list;
extern char						g_c;
extern char						g_n;

void							throw_error(char *error, size_t line);
uint8_t							check_extension(char *file_name,
		char *extension);
void							assembly(char *file_name);
void							disassembly(char *file_name);
int								line_not_clear(char const *start,
		char const *end);
char							*get_clear_string(char const *start,
		char const *end);
char							*read_name_comment(char *file_content,
		uint8_t counter);
t_list							*read_instructions(char *start);
void							collect_instruction(t_list **instr_list,
		t_instruction *instr, char *instruction);
uint8_t							find_op_index(char *command,
		size_t command_length);
void							write_bites(uint8_t *mem,
		uint32_t value32, uint8_t bites);
void							write_executable(int fd, t_list *instr_list);
void							print_labels(t_list *label);
void							clean_labels(t_list *label);
void							clean_instr(t_list *instr);
void							print_operation(t_list *operation);
void							check_labels(t_list *label_list,
		t_list *op_list);
int								label_find(void *lst_content, void *content);

#endif
