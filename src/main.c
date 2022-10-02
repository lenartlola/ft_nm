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
	return 0;
}