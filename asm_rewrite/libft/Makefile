# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/25 13:26:24 by dmlitvin          #+#    #+#              #
#    Updated: 2019/02/23 17:36:23 by dmlitvin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

CC=clang

FLAGS=-c -Wall -Wextra -Werror -I include

COMPRESS=ar rc

REMOVE=rm -rf

SRC_42=ft_atoi.c ft_bzero.c ft_cycle_move.c ft_is_whitespace.c ft_isalnum.c \
ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isnumeric.c ft_isprint.c ft_putchar.c \
ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c \
ft_putstr_fd.c ft_reverse.c ft_tolower.c ft_toupper.c get_next_line.c \

SRC_MEM=ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memdel.c ft_memmove.c ft_memset.c \

SRC_STR=ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c \
ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c \
ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c ft_strsplit.c \
ft_strstr.c ft_strsub.c ft_strtrim.c ft_strnchr.c ft_stralloc.c \

SRC_PRINTF=ft_itoa.c ft_itoa10.c ft_itoa_for_printf.c ft_printf.c parsers.c \
print_cs.c print_float.c print_numeric.c \

SRC_LST=ft_list_size.c ft_lstadd.c ft_lstadd_sorted.c ft_lstdel.c \
ft_lstdelone.c ft_lstfind.c ft_lstiter.c ft_lstmap.c ft_lstnew.c \
ft_lstadd_end.c \

SRC=$(addprefix 42/, $(SRC_42)) $(addprefix mem/, $(SRC_MEM)) \
$(addprefix str/, $(SRC_STR)) $(addprefix lst/, $(SRC_LST)) \
$(addprefix printf/, $(SRC_PRINTF))

SRO=$(SRC:.c=.o)

$(NAME): $(SRO) include/libft.h
	@$(COMPRESS) $(NAME) $(SRO)

%.o: %.c
	@$(CC) $(FLAGS) $< -o $@

all: $(NAME) $(SRC)

clean:
	@$(REMOVE) $(SRO)

fclean: clean
	@$(REMOVE) $(SRO) $(NAME)

re: fclean all

.PHONY: all clean fclean re
