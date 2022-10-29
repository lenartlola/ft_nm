//
// Created by unixity on 10/28/22.
//

#include "nm.h"

static Elf32_Shdr *find_shdr_table(Elf32_Shdr* shdr, uint16_t table_size, int e_shstrndx)
{
	for (uint16_t i = 0; i < table_size; i++) {
		if (shdr[i].sh_type == SHT_STRTAB && !(shdr[i].sh_flags & SHF_ALLOC) && e_shstrndx != i)
			return &shdr[i];
	}
	return NULL;
}

static void	add_shdr_to_lst(Elf32_Shdr* base_shdr, Elf32_Shdr* current_entry, Elf32_Shdr* string_shdr_table, t_data *data)
{
	(void)base_shdr;
	char *str;

	data->x86_elf.sym_lst = NULL;
	uint32_t n_symbol = current_entry->sh_size / current_entry->sh_entsize;
	data->x86_elf.elf32_sym = (Elf32_Sym*)(data->mmap_ptr + current_entry->sh_offset);
	while(n_symbol--)
	{
		str = &data->mmap_ptr[string_shdr_table->sh_offset + data->x86_elf.elf32_sym->st_name];
		add_symbol_back(&data->x86_elf.sym_lst,
						add_symbol(str, data->x86_elf.elf32_sym->st_value,
								   get_x86_symbol_type(data->x86_elf.elf32_sym, base_shdr)));
		data->x86_elf.elf32_sym += 1;
	}
}

void	init_x86_data(t_data *data)
{
	Elf32_Shdr*	string_shdr_table;
	uint32_t	shdr_size;

	data->x86_elf.elf32_header = (Elf32_Ehdr*)data->mmap_ptr;
	shdr_size = data->x86_elf.elf32_header->e_shnum;
	data->x86_elf.elf32_shdr = (Elf32_Shdr*)&data->mmap_ptr[data->x86_elf.elf32_header->e_shoff];
	string_shdr_table = find_shdr_table(data->x86_elf.elf32_shdr, shdr_size, data->x86_elf.elf32_header->e_shstrndx);
	for (uint32_t i = 0; i < shdr_size; i++) {
		if (data->x86_elf.elf32_shdr[i].sh_type == SHT_SYMTAB) {
			add_shdr_to_lst(data->x86_elf.elf32_shdr, &data->x86_elf.elf32_shdr[i], string_shdr_table, data);
		}
	}
	print_lst(data->x86_elf.sym_lst);
	free_lst(&(data->x86_elf.sym_lst));
}