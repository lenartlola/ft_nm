//
// Created by unixity on 10/2/22.
//

#ifndef FT_NM_NM_H
#define FT_NM_NM_H

#include "libft.h"

#include <sys/mman.h>
#include <fcntl.h>

#define ELF_LITTLE_MAGIC 0x464c457f
#define ELF_BIG_MAGIC 0x7f454c47

typedef struct s_data
{
	int			prog_fd;
	struct stat	stat_buf;
	char		*header;
}	t_data;

/* Utils */
void	fatal(char *arg);

/* Init utils */
int		init_data(char *file, t_data *data);

#endif //FT_NM_NM_H
