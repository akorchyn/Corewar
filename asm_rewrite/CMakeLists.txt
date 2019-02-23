cmake_minimum_required(VERSION 3.12)

project(asm C)

set(CMAKE_C_STANDARD 99)

add_executable(asm op.c read_label.c parse_label.c main.c asm.h file_reading.c command_argument.c calculate_size.c)

target_link_libraries(asm ${CMAKE_SOURCE_DIR}/libft/libft.a)
