.PHONY: all re clean fclean

all:
	@make -C VM
	@make -C visualization
	@make -C assembler
	@cp VM/corewar .
	@cp assembler/asm .

clean:
	@make clean -C VM
	@make clean -C visualization
	@make clean -C assembler

fclean:
	@make fclean -C VM
	@make fclean -C visualization
	@make fclean -C assembler
	@rm -f corewar asm

re: fclean all

