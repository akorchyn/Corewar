.PHONY: all clean fclean re
CC = clang

FLAGS = -Wall -Wextra -Werror -c -I includes

NAME = libft.a

SRC_STANDART = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c\
	  ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strchr.c\
	  ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c\
	  ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_isupper.c\
	  ft_islower.c ft_isspace.c ft_memalloc.c ft_memdel.c ft_strdel.c ft_strnew.c ft_striter.c\
	  ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c\
	  ft_strsplit.c ft_strtrim.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c\
	  ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strrev.c ft_strlcat.c ft_strclr.c\

SRC_PRINTF = itoa_base.c mask.c unsigned.c for_all.c printunicode.c binary_memory.c \
	float.c itoa_base.c decimal_int.c ft_printf.c csp.c unicode.c badtype_perc.c

SRC_LST = ft_lstmap.c ft_lstiter.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstnew.c ft_list_counter.c

SRC_MY_FUNCTION = ft_isxdigit.c ft_freesplit.c get_next_line.c ft_putred.c ft_len.c ft_isnumeric.c ft_pow.c

SRC = $(addprefix standart/, $(SRC_STANDART)) $(addprefix printf/, $(SRC_PRINTF)) $(addprefix lst/, $(SRC_LST)) \
	$(addprefix my_functions/, $(SRC_MY_FUNCTION))

SRO = $(SRC:.c=.o) 

all: $(SRC) $(NAME)

$(NAME): $(SRO)
	@echo "\x1b[34m ▄█        ▄█  ▀█████████▄     ▄████████     ███     \n███       ███    ███    ███   ███    ███ ▀█████████▄ \n███       ███▌   ███    ███   ███    █▀     ▀███▀▀██ \n███       ███▌  ▄███▄▄▄██▀   ▄███▄▄▄         ███   ▀ \n███       ███▌ ▀▀███▀▀▀██▄  ▀▀███▀▀▀         ███     \n███       ███    ███    ██▄   ███            ███     \n███▌    ▄ ███    ███    ███   ███            ███     \n█████▄▄██ █▀   ▄█████████▀    ███           ▄████▀   \n▀                                                    "
	@echo "\x1b[33mCompilation Library\x1b[0m"
	@ar rc $(NAME) $(SRO)
	@ranlib $(NAME) && echo "\x1b[32mSuccessful Library Compilation\x1b[0m"

%.o: %.c
	@$(CC) $(FLAGS) $< -o $@

clean:
	@/bin/rm -rf $(SRO)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all
