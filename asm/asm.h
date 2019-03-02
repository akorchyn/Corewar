/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:21:46 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft/include/libft.h"
# include <stdint.h>
# include <fcntl.h>

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define IND_BYTE_SIZE			2
# define REG_BYTE_SIZE			1
# define DIR_BYTE_SIZE			4

# define COMMENT_CHAR			'#'
# define ALT_COMMENT_CHAR		';'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define T_REG					1
# define T_DIR					2
# define T_IND					4

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3
# define EXEC_MAGIC_LENGTH		4

# define GET_INSTRUCTION(instruction) ((t_instruction*)instruction->content)

typedef struct					s_header
{
	unsigned int				magic;
	char						prog_name[PROG_NAME_LENGTH + 1];
	unsigned int				prog_size;
	char						comment[COMMENT_LENGTH + 1];
	uint8_t						*executable;
}								t_header;

typedef struct					s_op
{
	char						*op_name;
	uint8_t						arg_count;
	uint8_t						arg_code[3];
	uint8_t						op_index;
	uint16_t					pause_value;
	uint8_t						has_arg_type : 1;
	uint8_t						is_dir_2 : 1;
}								t_op;

typedef	struct					s_lexem
{
	t_list						*argument;
	uint8_t						op_index;
	uint8_t						size;
	uint8_t						*code;
}								t_lexem;

typedef struct					s_instruction
{
	char						*str;
	size_t						size_from_start;
	t_list						*label;
	size_t						line_nb;
	t_lexem						lexem;
}								t_instruction;

extern const t_op				g_op_tab[17];
extern t_header					g_header;

void							throw_error(int error_id,
		char *str, size_t line);
uint8_t							check_extension(char *file_name,
		char *extension, size_t extension_len);
char							*read_file(char *file_name);
void							assembly(t_list **instr_list,
		char *file_content, char *file_name);
t_list							*split_instr(char *file_content);
void							read_labels(t_list *instr);
void							disassembly(char *file_content);
void							read_command_argument(t_list *instruction);
void							calculate_sizes(t_list *instruction);
void							put_global_sizes(t_list *instruction);
void							parse_labels(t_list *instruction,
		t_list *instr_list);
void							parse_inst_code(t_list *lst);
void							put_bites(uint8_t *memory,
		uint32_t argument, uint8_t arg_len);
void							check_name_comment(t_list *list,
		t_list **instr_list);
void							write_champion(char *file_name);

#endif
