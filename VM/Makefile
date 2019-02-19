.PHONY: all re fcleam clean

NAME = corewar

CC = clang

FLAGS = -Wall -Wextra -Werror -c

LIBFT = -Llibft -lft

INCLUDES = -I includes

FILE = initializing main parse useful_function

OBJ_LIST = $(addprefix obj/, $(addsuffix .o, $(FILE)))

$all: $(NAME)

$(NAME): $(OBJ_LIST)
	@$(CC) $(OBJ_LIST) $(LIBFT) -o $(NAME)

obj/%.o: src/%.c
	@$(CC) $(FLAGS) $(INCLUDES) -o $@ $<

clean:
	@/bin/rm -rf $(OBJ_LIST)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all
