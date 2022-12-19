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
#include <stdbool.h>

typedef struct s_symbol_lst	t_symbol_lst;

typedef struct s_arg_options {
	bool	a;
	bool	g;
	bool	u;
	bool	r;
	bool	p;
}	t_arg_options;

struct s_symbol_lst
{
	void			*content;
	char			type;
	uint64_t 		value;
	t_symbol_lst	*next;
};


typedef struct	s_x64_elf
{
	Elf64_Ehdr		*elf64_header; // Elf header structure for 64-bit
	Elf64_Shdr		*elf64_shdr; // Section header for 64-bit
	Elf64_Sym		*elf6_sym; // Symbol table section
	t_symbol_lst	*sym_lst; // A linked list to store information
}	t_x64_elf;

typedef struct	s_x86_elf
{
	Elf32_Ehdr		*elf32_header; // Elf header structure for 32-bit
	Elf32_Shdr		*elf32_shdr; // Section header for 32-bit
	Elf32_Sym		*elf32_sym; // Symbol table section
	t_symbol_lst	*sym_lst; // A linked list to store information
}	t_x86_elf;

typedef struct s_data
{
	struct stat	stat_buf;
	char			*mmap_ptr;
	char			*prog;
	t_x64_elf		x64_elf;
	t_x86_elf		x86_elf;
	t_arg_options	opts;
}	t_data;

/* ft_nm */
void			ft_nm(t_data *data);

/* Utils */
void			fatal(char *arg);

/* Init utils */
int				init_data(t_data *data);

/* Elf infos reader */
int	read_elf_hdr(t_data *data);

/* x64 arch */
void			init_x64_data(t_data *data);
char			get_x64_symbol_type(Elf64_Sym* symbol_entry, Elf64_Shdr* current_entry);


/* x86 arch */
void			init_x86_data(t_data *data);
char			get_x86_symbol_type(Elf32_Sym* symbol_entry, Elf32_Shdr* current_entry);


/* Generic utils */
void			print_lst(t_symbol_lst *list, t_data *data);
t_symbol_lst	*add_symbol(void *content, uint64_t value, char t);
void			free_lst(t_symbol_lst **lst);
void			add_symbol_back(t_symbol_lst **alst, t_symbol_lst *new);
void 			sort_list(t_symbol_lst **head);


#endif //FT_NM_NM_H
