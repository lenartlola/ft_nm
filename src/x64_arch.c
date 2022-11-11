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

static void	add_shdr_to_lst(Elf64_Shdr* base_shdr, Elf64_Shdr* current_entry, Elf64_Shdr* string_shdr_table, t_data *data)
{
	char *str;

	data->x64_elf.sym_lst = NULL;
	uint64_t n_symbol = current_entry->sh_size / current_entry->sh_entsize;
	//Elf64_Sym* symbol_entry = (Elf64_Sym*)(data->mmap_ptr + current_entry->sh_offset);
	data->x64_elf.elf6_sym = (Elf64_Sym*)(data->mmap_ptr + current_entry->sh_offset);
	while(n_symbol--)
	{
		str = &data->mmap_ptr[string_shdr_table->sh_offset + data->x64_elf.elf6_sym->st_name];
		add_symbol_back(&data->x64_elf.sym_lst,
						add_symbol(str, data->x64_elf.elf6_sym->st_value,
								   get_x64_symbol_type(data->x64_elf.elf6_sym, base_shdr)));
		data->x64_elf.elf6_sym += 1;
	}
}

void	init_x64_data(t_data *data)
{
	Elf64_Shdr	*string_shdr_table;
	uint64_t	shdr_size;

	// Get the ELF header structure
	data->x64_elf.elf64_header = (Elf64_Ehdr *)data->mmap_ptr;
	// Get the number of entries in the section header
	shdr_size = data->x64_elf.elf64_header->e_shnum;
	// Get the actual ELF section header
	data->x64_elf.elf64_shdr = (Elf64_Shdr *)&data->mmap_ptr[data->x64_elf.elf64_header->e_shoff];
	// Get the string table of the section header
	string_shdr_table = find_shdr_table(data->x64_elf.elf64_shdr, shdr_size, data->x64_elf.elf64_header->e_shstrndx);
	for (uint64_t i = 0; i < shdr_size; i++) {
		if (data->x64_elf.elf64_shdr[i].sh_type == SHT_SYMTAB) {
			add_shdr_to_lst(data->x64_elf.elf64_shdr, &data->x64_elf.elf64_shdr[i], string_shdr_table, data);
		}
	}
	print_lst(data->x64_elf.sym_lst, data);
	free_lst( &(data->x64_elf.sym_lst));
}
