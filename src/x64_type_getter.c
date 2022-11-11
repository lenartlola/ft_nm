//
// Created by unixity on 10/29/22.
//

#include "nm.h"

static char	check_shdr_index(int64_t c)
{
	switch (c) {
		case SHN_UNDEF:
			return'U';
			break;
		case SHN_ABS:
			return 'a';
			break;
		case SHN_COMMON:
			return 'c';
			break;
	}
	return 0;
}

static char	get_x64_type(Elf64_Shdr* s)
{
	switch (s->sh_type) {
		case SHT_NOBITS:
			if (s->sh_flags & SHF_ALLOC && s->sh_flags & SHF_WRITE)
				return 'B';
			if (s->sh_flags & SHT_DYNSYM)
				return 'd';
			break;
		case SHT_PROGBITS:
			if (s->sh_flags & SHF_ALLOC) {
				if (s->sh_flags & SHF_EXECINSTR)
					return 'T';
				if (s->sh_flags & SHF_WRITE) {
					return 'd';
				}
				if (s->sh_flags == 18)
					return 'R';
				return 'r';
			}
			break;
		case SHT_DYNAMIC:
		case SHT_DYNSYM:
		case SHT_INIT_ARRAY:
		case SHT_FINI_ARRAY:
			return 'd';
			break;
//		case SHT_NOTE:
//			return 'r';
	}
	return '?';
}

char	get_x64_symbol_type(Elf64_Sym* symbol_entry, Elf64_Shdr* current_entry)
{
	char	type;

	if ((type = check_shdr_index(symbol_entry->st_shndx)) == 0) {
		type = get_x64_type(&current_entry[symbol_entry->st_shndx]);
	}
	return (type);
}
