//
// Created by unixity on 10/1/22.
//

#include "nm.h"

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
	//read_elf_hdr(&data);
	init_x64_data(&data);
	if (munmap(data.mmap_ptr, data.stat_buf.st_size) == -1)
	{
		ft_printf(0, "PANIC: failed to unmap pages of memory! %lx, %ld", data.mmap_ptr, data.stat_buf.st_size);
		exit(127);
	}
	return 0;
}