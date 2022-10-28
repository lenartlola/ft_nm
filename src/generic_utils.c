//
// Created by unixity on 10/28/22.
//

#include "nm.h"

void	print_lst(t_list *list)
{
	t_list *tmp;

	tmp = list;
	ft_printf(1, "-----------------------------------------------------------------------------\n");
	while (tmp)
	{
		ft_printf(1, "> %s\n", tmp->content);
		tmp = tmp->next;
	}
	ft_printf(1, "-----------------------------------------------------------------------------\n");
}