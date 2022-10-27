//
// Created by unixity on 10/27/22.
//

#include "nm.h"

static Elf64_Shdr *find_shdr_table(Elf64_Shdr* shdr, int16_t entries_index, int e_shstrndx)
{
	for (int i = 0; i < entries_index; i++) {
		if (shdr[i].sh_type == SHT_STRTAB && !(shdr[i].sh_flags & SHF_ALLOC) && e_shstrndx != i)
			return &shdr[i];
	}
	return NULL;
}

static void	add_shdr_to_lst(Elf64_Shdr* cur_tab, Elf64_Shdr* shdr_table, t_data *data)
{
	char *str;

	int64_t n_symbol = cur_tab->sh_size / cur_tab->sh_entsize;
	Elf64_Sym* sentry = (Elf64_Sym*)(data->mmap_ptr + cur_tab->sh_offset);
	int i = 0;

	while(n_symbol--)
	{
		i++;
		str = &data->mmap_ptr[shdr_table->sh_offset + sentry->st_name];
		ft_printf(1, "%d. %s\n", i, str);
		sentry += 1;
	}
}

void	init_x64_data(t_data *data)
{
	Elf64_Shdr	*shdr_table;

	data->x64_elf.elf64_header = (Elf64_Ehdr *)data->mmap_ptr;
	int16_t	entries_index = data->x64_elf.elf64_header->e_shnum;
	data->x64_elf.elf64_shdr = (Elf64_Shdr *)&data->mmap_ptr[data->x64_elf.elf64_header->e_shoff];
	shdr_table = find_shdr_table(data->x64_elf.elf64_shdr, entries_index, data->x64_elf.elf64_header->e_shstrndx);
	for (int i = 0; i < entries_index; i++) {
		if (data->x64_elf.elf64_shdr[i].sh_type == SHT_SYMTAB) {
			add_shdr_to_lst(&data->x64_elf.elf64_shdr[i], shdr_table, data);
		}
	}
}
