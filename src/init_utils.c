//
// Created by unixity on 10/2/22.
//

#include "nm.h"
#include <sys/stat.h>


int	init_data(char *file, t_data *data) {
	if ((data->prog_fd = open(file, O_RDWR)) == -1)
		return -1;
	if (fstat(data->prog_fd, &data->stat_buf) == -1)
		return -1;
	data->header = mmap(NULL, data->stat_buf.st_size, PROT_READ, MAP_PRIVATE, data->prog_fd, 0);
	ft_printf(0, "%lx\n", *(int *)data->header);
	if (*(int *)(data->header) == ELF_LITTLE_MAGIC || *(int *)(data->header) == ELF_BIG_MAGIC)
		ft_printf(0, "ELF\n");
	return 0;
}