//
// Created by unixity on 10/1/22.
//

#include "nm.h"

int parse_args(char **args, t_data *data) {
	for (int i = 1; args[i]; ++i) {
		if (args[i][0] == '-') {
			for (int j = 1; args[i][j]; ++j) {
				if (args[i][j] == 'a')
					data->opts.a = true;
				else if (args[i][j] == 'g')
					data->opts.g = true;
				else if (args[i][j] == 'u')
					data->opts.u = true;
				else if (args[i][j] == 'r')
					data->opts.r = true;
				else if (args[i][j] == 'p')
					data->opts.p = true;
				else
					return -1;
			}
		} else {
			data->prog = args[i];
		}
	}
	return 0;
}

void usage() {
	// TODO
	exit(1);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	(void )argc;
	if (parse_args(argv, &data) < 0)
		usage();
	if (!data.prog)
		data.prog = "a.out";
	if (init_data( &data) == -1)
		fatal("ft_nm: could not initialise data");
	ft_nm(&data);
	if (munmap(data.mmap_ptr, data.stat_buf.st_size) == -1)
	{
		ft_printf(0, "PANIC: failed to unmap pages of memory! %lx, %ld", data.mmap_ptr, data.stat_buf.st_size);
		exit(127);
	}
	return 0;
}