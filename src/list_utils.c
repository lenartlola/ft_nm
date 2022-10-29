//
// Created by unixity on 10/28/22.
//

#include "nm.h"

void	print_lst(t_symbol_lst *list)
{
	t_symbol_lst *tmp;

	tmp = list;
	while (tmp)
	{
		if ( !ft_strncmp((char*)tmp->content, "", ft_strlen((char*)tmp->content)))
		{
			tmp = tmp->next;
			continue;
		}
		if (tmp->value)
			ft_printf(1, "%016x %c %s\n", tmp->value, tmp->type, tmp->content);
		else
			ft_printf(1, "%16c %c %s\n", ' ', tmp->type, tmp->content);
		tmp = tmp->next;
	}
}

void	free_lst(t_symbol_lst **lst)
{
	t_symbol_lst	*tmp;

	tmp = NULL;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp);
	}
}

t_symbol_lst	*add_symbol(void *content, uint64_t value, char t)
{
	t_symbol_lst	*r;

	r = (t_symbol_lst *)malloc(sizeof(t_symbol_lst));
	if (!r)
		return (NULL);
	r->content = content;
	r->type = t;
	r->value = value;
	r->next = (t_symbol_lst *)0;
	return (r);
}

t_symbol_lst	*last_node(t_symbol_lst *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}


void	add_symbol_back(t_symbol_lst **alst, t_symbol_lst *new)
{
	t_symbol_lst	*last;

	if (alst)
	{
		if (*alst)
		{
			last = last_node(*alst);
			last->next = new;
		}
		else
			*alst = new;
	}
}
