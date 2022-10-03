//
// Created by unixity on 10/2/22.
//

#include "nm.h"

int	init_data(char *file, t_data *data) {
	if ((data->prog_fd = open(file, O_RDONLY)) == -1)
		return -1;
	if (fstat(data->prog_fd, &data->stat_buf) == -1)
		return -1;
	data->mmap_ptr = mmap(NULL, data->stat_buf.st_size, PROT_READ, MAP_PRIVATE, data->prog_fd, 0);
	if (data->mmap_ptr == MAP_FAILED)
		return -1;
	data->header_magic = *(int *)(data->mmap_ptr);
	if (data->header_magic == ELF_LITTLE_MAGIC || data->header_magic == ELF_BIG_MAGIC)
	{
		ft_printf(0, "ELF\n");
		return 0;
	}
	return -1;
}