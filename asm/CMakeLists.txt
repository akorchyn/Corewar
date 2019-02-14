cmake_minimum_required(VERSION 3.12)

project(asm C)

set(CMAKE_C_STANDARD 99)

add_executable(asm main.c asm.h file_reading.c )

link_libraries(libft/libft.a)
