cmake_minimum_required(VERSION 3.22)
project(ft_nm C)

set(CMAKE_C_STANDARD 11)

include_directories(incs)
include_directories(libs/libft/incs)
include_directories(libs/libft/incs/libft)

link_directories(libs/libft)

SET(LIBS ft)

add_executable(
        ft_nm
        src/init_utils.c
        src/utils.c
        src/elf_head_infos_reader.c
        src/main.c
        src/x64_arch.c
        src/ft_nm.c
        src/x86_arch.c
        src/generic_utils.c
        src/list_utils.c
        src/x86_type_getter.c
        src/x64_type_getter.c
        )

target_link_libraries(ft_nm ${LIBS})