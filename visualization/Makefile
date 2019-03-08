.PHONY: all re fclean clean create_dir

NAME = visualization

CC = g++

FLAGS = -std=c++1z -Ofast

LIB = -L$(HOME)/.brew/lib/ -lSDL2-2.0.0 -lSDL2_image-2.0.0 -lSDL2_ttf-2.0.0

INCLUDES = -I includes -I $(HOME)/.brew/include/SDL2/

FILE = window visualization text corewar

OBJ_LIST = $(addprefix obj/, $(addsuffix .o, $(FILE)))

all: create_dir $(NAME)

$(NAME): $(OBJ_LIST)
		@echo "\x1b[33mVisualazing linking\x1b[0m"
		@$(CC) -std=c++1z -Ofast $(OBJ_LIST) $(LIB) -o $(NAME)
		@echo "\x1b[32mSuccessful\x1b[0m"

create_dir:
		@mkdir -p obj

obj/%.o: src/%.cpp
		@printf "\x1b[33mCompiling %s. \x1b[0m" $<
		@$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<
		@echo "\x1b[32mDone.\x1b[0m"

clean:
	@/bin/rm -rf $(OBJ_LIST)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all
