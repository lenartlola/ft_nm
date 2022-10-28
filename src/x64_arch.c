//
// Created by unixity on 10/27/22.
//

#include "nm.h"
#include <elf.h>

static Elf64_Shdr *find_shdr_table(Elf64_Shdr* shdr, uint16_t entries_index, int e_shstrndx)
{
	for (uint16_t i = 0; i < entries_index; i++) {
		if (shdr[i].sh_type == SHT_STRTAB && !(shdr[i].sh_flags & SHF_ALLOC) && e_shstrndx != i)
			return &shdr[i];
	}
	return NULL;
}

static void	add_shdr_to_lst(Elf64_Shdr* current_entry, Elf64_Shdr* string_shdr_table, t_data *data)
{
	char *str;

	data->x64_elf.sym_lst = NULL;
	int64_t n_symbol = current_entry->sh_size / current_entry->sh_entsize;
	Elf64_Sym* symbol_entry = (Elf64_Sym*)(data->mmap_ptr + current_entry->sh_offset);
	while(n_symbol--)
	{
		str = &data->mmap_ptr[string_shdr_table->sh_offset + symbol_entry->st_name];
		ft_lstadd_back(&data->x64_elf.sym_lst, ft_lstnew(str));
		symbol_entry += 1;
	}
}

void	init_x64_data(t_data *data)
{
	Elf64_Shdr	*string_shdr_table;

	// Get the ELF header structure
	data->x64_elf.elf64_header = (Elf64_Ehdr *)data->mmap_ptr;
	// Get the number of entries in the section header
	uint64_t entries_index = data->x64_elf.elf64_header->e_shnum;
	// Get the actual ELF section header
	data->x64_elf.elf64_shdr = (Elf64_Shdr *)&data->mmap_ptr[data->x64_elf.elf64_header->e_shoff];
	// Get the string table of the section header
	string_shdr_table = find_shdr_table(data->x64_elf.elf64_shdr, entries_index, data->x64_elf.elf64_header->e_shstrndx);
	for (uint16_t i = 0; i < entries_index; i++) {
		if (data->x64_elf.elf64_shdr[i].sh_type == SHT_SYMTAB) {
			add_shdr_to_lst(&data->x64_elf.elf64_shdr[i], string_shdr_table, data);
		}
	}
	print_lst(data->x64_elf.sym_lst);
	ft_freelst( &(data->x64_elf.sym_lst));
}
