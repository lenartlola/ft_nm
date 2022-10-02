//
// Created by unixity on 10/1/22.
//

#include "nm.h"

const unsigned char	ELF_MAGIC[4] = {0x7f, 0x45, 0x4c, 0x46};

int	init_data(char *file, t_data *data) {
	if ((data->prog_fd = open(file, O_RDONLY)) == -1)
		return -1;
	if ((read(data->prog_fd, data->header, 4)) == -1)
		return -1;
	data->header[4] = '\0';
	return 0;
}

void	fatal(char *arg) {
	ft_printf(0, "%s\n", arg);
	exit(127);
}

void	print_header(t_data *data) {
	int i = 0;
	while(data->header[i])
	{
		ft_printf(0, "0x%x ", data->header[i]);
		i++;
	}
	ft_printf(0, "\n");
}

int	main(int argc, char *argv[])
{
	t_data	data;

	// TODO: check for a.out in the path
	if (argc != 2) {
		ft_printf(0, "ft_nm: 'a.out': No such file\n");
		return 1;
	}
	if (init_data(argv[1], &data) == -1)
		fatal("ft_nm: could not initialise data");
	if (memcmp(data.header, ELF_MAGIC, 4) != 0) {
		ft_printf(0, "ft_nm: %s: file format not recognized\n", argv[1]);
		return 1;
	}
	print_header(&data);
	return 0;
}