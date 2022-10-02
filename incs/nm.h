//
// Created by unixity on 10/2/22.
//

#ifndef FT_NM_NM_H
#define FT_NM_NM_H

#include "libft.h"

#include <sys/mman.h>
#include <fcntl.h>

typedef struct s_data
{
	int	prog_fd;
	char header[4];
}	t_data;

#endif //FT_NM_NM_H
