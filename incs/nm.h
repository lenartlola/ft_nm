//
// Created by unixity on 10/2/22.
//

#ifndef FT_NM_NM_H
#define FT_NM_NM_H

#include "libft.h"
#include "const_defines.h"

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <elf.h>


typedef struct	s_x64_elf
{
	Elf64_Ehdr	*elf64_header; // Elf header structure for 64-bit
	Elf64_Shdr	*elf64_shdr; // Section header for 64-bit
	Elf64_Sym	*elf64_sym;
} t_x64_elf;

typedef struct	s_x86_elf
{
	Elf32_Ehdr	*elf32_header; // Elf header structure for 32-bit
	Elf32_Shdr	*elf32_shdr; // Section header for 32-bit
}	t_x86_elf;

typedef struct s_data
{
	struct stat	stat_buf;
	char		*mmap_ptr;
	t_x64_elf	x64_elf;
	t_x86_elf	x86_elf;
}	t_data;

/* Utils */
void	fatal(char *arg);

/* Init utils */
int		init_data(char *file, t_data *data);

/* Elf infos reader */
int	read_elf_hdr(t_data *data);

/* x64 arch */
void	init_x64_data(t_data *data);

#endif //FT_NM_NM_H
