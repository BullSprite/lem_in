cmake_minimum_required(VERSION 3.14.5)
project(lem_in C)

set(CMAKE_C_STANDARD 99)

file(GLOB libft_SRC
        "libft/*.c")

file(GLOB SRCS
        "srcs/*.c")

add_executable(lem_in ${SRCS} includes/lem_in.h
        ${libft_SRC})