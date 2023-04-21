//
// Created by unixity on 10/2/22.
//

#include "nm.h"

int map_data(t_data *data, char *prog)
{
	struct stat	stat_buf;
	int     fd;
	char    *mptr;

	fd = open(prog, O_RDONLY);
	if (fd == -1) {
		ft_printf(1, "ft_nm: '%s': No such file\n", prog);
		return 1;
	}
	if (fstat(fd, &stat_buf) == -1) {
		close(fd);
		return 1;
	}
	mptr = mmap(NULL, stat_buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (mptr == MAP_FAILED) {
		ft_printf(0, "Error: failed to map file %s.\n", prog);
		close(fd);
		return 1;
	}
	close(fd);
	uint32_t hdr_magic = *(uint32_t *)(mptr);
	if (hdr_magic != ELF_LITTLE_MAGIC && hdr_magic != ELF_BIG_MAGIC) {
		ft_printf(0, "Error: not an elf file %s\n", prog);
		munmap(mptr, stat_buf.st_size);
		return 1;
	}
    add_p_lst_back(&data->p_lst, add_prog(prog, mptr, stat_buf));
	return 0;
}
