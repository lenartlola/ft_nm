//
// Created by unixity on 10/2/22.
//

#ifndef FT_NM_NM_H
#define FT_NM_NM_H

#include "libft.h"
#include "const_defines.h"

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>


typedef struct s_data
{
	int			prog_fd;
	struct stat	stat_buf;
	const char	*mmap_ptr;
	int			header_magic;
}	t_data;

/* Utils */
void	fatal(char *arg);

/* Init utils */
int		init_data(char *file, t_data *data);

#endif //FT_NM_NM_H
