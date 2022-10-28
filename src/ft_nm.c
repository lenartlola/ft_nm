//
// Created by unixity on 10/28/22.
//

#include "nm.h"

void	ft_nm(t_data *data)
{
	if (data->mmap_ptr[ENDIAN] == 1)
		init_x86_data(data);
	else
		init_x64_data(data);
}
