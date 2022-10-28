//
// Created by unixity on 10/2/22.
//

#include "nm.h"

static void	set_strct_to_zero(t_data *data)
{
	memset(data, 0, sizeof(&data));
	memset(&data->x64_elf, 0, sizeof(data->x64_elf));
	memset(&data->x86_elf, 0, sizeof(data->x86_elf));
}

int	init_data(char *file, t_data *data) {
	int fd;
	int	hdr_magic;

	if ((fd = open(file, O_RDONLY)) == -1)
		return -1;
	set_strct_to_zero(data);
	if (fstat(fd, &data->stat_buf) == -1) {
		return -1;
	}
	if ((data->mmap_ptr = mmap(NULL, data->stat_buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return -1;
	close(fd);
	hdr_magic = *(int *)(data->mmap_ptr);
	if (hdr_magic == ELF_LITTLE_MAGIC || hdr_magic == ELF_BIG_MAGIC)
		return 0;
	return -1;
}
