//
// Created by unixity on 10/28/22.
//

#include "libft.h"

void	ft_freelst(t_list **lst)
{
	t_list	*tmp;

	tmp = NULL;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}
