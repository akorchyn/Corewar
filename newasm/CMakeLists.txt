cmake_minimum_required(VERSION 3.13)

project(asm C)

set(SOURCE_C main.c assembly.c name_comment.c disassembly.c clean_debug.c
        valid.c read_instructions.c parse_instruction.c executable.c)

set(SOURCE_H asm.h)

add_executable(asm ${SOURCE_C} ${SOURCE_H})

target_link_libraries(asm /Users/dmlitvin/corewarYE/newasm/libft/libft.a)
