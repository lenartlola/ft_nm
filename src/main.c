//
// Created by unixity on 10/1/22.
//

#include "nm.h"

void    free_list(t_list *lst)
{
    t_list *tmp = NULL;
    while (lst)
    {
        tmp = lst;
        free(tmp);
        lst = lst->next;
    }
}

int parse_args(char **args, t_data *data)
{
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
            map_data(data, args[i]);
        }
	}
	if (!data->p_lst)
		map_data(data, "a.out");
	return 0;
}

void usage()
{
	ft_printf(1, "Usage: ./ft_nm [OPIONS] <program>\n");
	ft_printf(1, "Options:\n%6c -a\n%6c -g\n", ' ', ' ');
	exit(1);
}

int	main(int argc, char *argv[])
{
	t_data	data;
//    data.prog = NULL;

	(void )argc;
	if (parse_args(argv, &data) < 0)
		usage();
	ft_nm(&data);
//	if (init_data(&data) == -1)
//		fatal("ft_nm: could not initialise data");
//	ft_nm(&data);
//	if (munmap(data.mmap_ptr, data.stat_buf.st_size) == -1)
//	{
//		ft_printf(0, "PANIC: failed to unmap pages of memory! %lx, %ld", data.mmap_ptr, data.stat_buf.st_size);
//		exit(127);
//	}
	return 0;
}