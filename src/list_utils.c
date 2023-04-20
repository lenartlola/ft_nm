//
// Created by unixity on 10/28/22.
//

#include "nm.h"

void	print_undef_only(t_symbol_lst *lst)
{
	while (lst) {
		if (lst->type == 'U') {
			if (lst->value)
				ft_printf(1, "%016x %c %s\n", lst->value, lst->type, lst->content);
			else
				ft_printf(1, "%16c %c %s\n", ' ', lst->type, lst->content);
		}
		lst = lst->next;
	}
}

void	print_extern_only(t_symbol_lst *lst)
{
	while (lst) {
		if (!ft_strncmp((char*)lst->content, "", ft_strlen((char*)lst->content))) {
			lst = lst->next;
			continue;
		}
		if (lst->type == 'U' || lst->type == 'w' || lst->type == 'D'
			|| lst->type == 'B' || lst->type == 'T' || lst->type == 'W') {
			if (lst->value)
				ft_printf(1, "%016x %c %s\n", lst->value, lst->type, lst->content);
			else
				ft_printf(1, "%16c %c %s\n", ' ', lst->type, lst->content);
		}
		lst = lst->next;
	}
}

void	print_lst(t_symbol_lst *list, t_data *data)
{
	t_symbol_lst *tmp;

	tmp = list;
	while (tmp)
	{
		if (data->opts.u == true) {
			print_undef_only(tmp);
			break;
		}
		if (data->opts.g == true) {
			print_extern_only(tmp);
			break;
		}
		if (tmp->type == 'a' && data->opts.a == false)
		{
			tmp = tmp->next;
			continue;
		}
		if (!ft_strncmp((char*)tmp->content, "", ft_strlen((char*)tmp->content)) && (data->opts.a == false || tmp->type == 'U'))
		{
			tmp = tmp->next;
			continue;
		}
		if (data->mmap_ptr[X86_ARCH] == 1) {
			if (tmp->value)
				ft_printf(1, "%08x %c %s\n", tmp->value, tmp->type, tmp->content);
			else
				ft_printf(1, "%8c %c %s\n", ' ', tmp->type, tmp->content);
		} else {
			if (tmp->value)
				ft_printf(1, "%016x %c %s\n", tmp->value, tmp->type, tmp->content);
			else
				ft_printf(1, "%16c %c %s\n", ' ', tmp->type, tmp->content);
		}
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

t_prog_list	*last_prog(t_prog_list *lst)
{
    while (lst)
    {
        if (!lst->next)
            return (lst);
        lst = lst->next;
    }
    return (lst);
}


void	add_p_lst_back(t_prog_list **alst, t_prog_list *new)
{
    t_prog_list *last;

    if (alst)
    {
        if (*alst)
        {
            last = last_prog(*alst);
            last->next = new;
        }
        else
            *alst = new;
    }
}

static void	set_strct_to_zero(t_prog_list *prog)
{
//	memset(prog, 0, sizeof(&prog));
	memset(&prog->x64_elf, 0, sizeof(prog->x64_elf));
	memset(&prog->x86_elf, 0, sizeof(prog->x86_elf));
}

t_prog_list	*add_prog(void *content, char *ptr, struct stat sb)
{
    t_prog_list	*r;

    r = (t_prog_list *)malloc(sizeof(t_prog_list));
    if (!r)
        return (NULL);
    r->content = content;
    r->m_ptr = ptr;
	r->stat_buf = sb;
    r->next = (t_prog_list *)0;
	set_strct_to_zero(r);
    return (r);
}

/*
1. Take a pointer to the head of the linked list as an argument
2. Iterate through the list and compare each char * element to the next one
3. If the current char * is greater than the next one, swap the char * elements
4. Repeat step 3 until the linked list is sorted
*/

void sort_list(t_symbol_lst **head)
{
    t_symbol_lst *start = *head;
    t_symbol_lst *i, *j;
    char *tmp;

    for (i = start; i->next != NULL; i=i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->content, j->content) > 0)
            {
                tmp = i->content;
                i->content = j->content;
                j->content = tmp;
            }
        }
    }
}