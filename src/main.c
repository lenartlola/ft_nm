//
// Created by unixity on 10/1/22.
//

#include "nm.h"

int	read_elf_hdr(t_data *data)
{
	ft_printf(0, "----ELF MAGIC----\n");
	ft_printf(0, "1. 0x%x\n", data->mmap_ptr[EI_MAG0]);
	ft_printf(0, "2. 0x%x\n", data->mmap_ptr[EI_MAG1]);
	ft_printf(0, "3. 0x%x\n", data->mmap_ptr[EI_MAG2]);
	ft_printf(0, "4. 0x%x\n", data->mmap_ptr[EI_MAG3]);

	return 0;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	// TODO: check for a.out in the path, and more args may be given
	if (argc != 2) {
		//TODO: write more sophisticated parser
		ft_printf(0, "ft_nm: 'a.out': No such file\n");
		return 1;
	}
	if (init_data(argv[1], &data) == -1)
		fatal("ft_nm: could not initialise data");
	read_elf_hdr(&data);
	return 0;
}