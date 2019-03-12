# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/06 22:47:34 by dmlitvin          #+#    #+#              #
#    Updated: 2019/03/12 20:22:25 by dmlitvin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=asm

LIBFT=libft/libft.a

FLAGS=-Wall -Wextra -Werror -I libft/include

CC=clang $(FLAGS)

SRC=main.c assembly.c disassembly.c name_comment.c \
parse_instruction.c read_instructions.c valid.c

SRO=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRO) $(LIBFT)
	@$(CC) $(SRO) $(LIBFT) -o $(NAME) && printf "\x1b[32mBinary file compiled \
	succesfully!\nLaunch: ./asm \"source_file\"\n\x1b[0m"

$(SRO): $(LIBFT) $(SRC) asm.h
	@$(CC) -c $(SRC) && printf "\x1b[32mObject files compiled succesfully!\n\x1b[0m"

$(LIBFT):
	@make -C libft/

clean:
	@rm -f $(SRO) && printf "\x1b[31mObject files have been deleted!\n\x1b[0m"
	@make clean -C libft/

fclean: clean
	@rm -f $(NAME) && printf "\x1b[31mBinary file has been deleted!\n\x1b[0m"
	@make fclean -C libft/

re: fclean all

.PHONY: re clean fclean all
