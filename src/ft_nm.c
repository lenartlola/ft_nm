//
// Created by unixity on 10/28/22.
//

#include "nm.h"

void	ft_nm(t_data *data)
{
	t_prog_list	*tmp;

	tmp = data->p_lst;
	while (tmp)
	{
		if (data->p_lst->m_ptr[X86_ARCH] == 1)
			init_x86_data(data, tmp);
		else
			init_x64_data(data, tmp);
		tmp = tmp->next;
	}
}
