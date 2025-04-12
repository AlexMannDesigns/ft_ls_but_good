#include "ft_ls.h"

// this should be moved to another file
void    print_node_list(t_list *list)
{
    t_file_info *current;

    ft_putstr("[ ");
    while (list)
    {
        current = list->content;
        ft_putstr(current->path);
        if (list->next)
            ft_putstr(", ");
        list = list->next;
    }
    ft_putendl("]");
    return ;
}

/*
 * Here, we need to find our min in the original list and drop it 
 * by making the next pointer from the node beforehand to bypass it.
 * We do not want to 'free' or 'delete' anything here. The process in
 * this sort is just to move pointers around until everything is
 * correctly ordered.
 */
static void remove_from_original(t_list **list, t_list *min, t_list *previous_to_min)
{
    if (!list || !*list || !min)
        return ;
    if (*list == min)
    {
        *list = (*list)->next;
        return ;
    }
    previous_to_min->next = min->next;
    return ;
}

/*
 * We can avoid a lot of unnecessary looping here by keeping track of the
 * tail of the list.
 */
static void append_to_sorted(t_list **sorted_head, t_list **sorted_tail, t_list *min)
{
    if (!(*sorted_head))
    {
        *sorted_head = min;
        *sorted_tail = min;
        return ;
    }
    (*sorted_tail)->next = min;
    *sorted_tail = min;
    return ;
}

// this should probably be moved to another file.
unsigned int    compare_values(t_options options, t_file_info *a, t_file_info *b)
{
    int cmp;

    (void) options;
    cmp = ft_strcmp(a->path, b->path);
    if (check_misc_option_bit(options.misc, REVERSED))
        return (cmp < 0);
    return (cmp > 0);
}

/*
 * previous_to_min tracks the location of the node before the node containing the
 * min value. This means we don't need to find it again when we remove it from
 * the original list.
 */
static t_list   *find_min(t_options options, t_list **list, t_list **previous_to_min)
{
    t_list  *iter;
    t_list  *min;
    t_list  *prev;

    iter = *list;
    min = NULL;
    prev = NULL;
    while (iter)
    {
        if (!min || compare_values(options, min->content, iter->content))
        {
            min = iter;
            *previous_to_min = prev;
        }
        prev = iter;
        iter = iter->next;
    }
    return (min);
}

/*
 * A simple select sort is used. The intention is to minimize code repetition
 * as much as possible, so we use the same list type and sorting process
 * across the program.
 */
void    sort_node_list(t_options options, t_list **list)
{
    t_list  *original;
    t_list  *sorted_head;
    t_list  *sorted_tail;
    t_list  *min;
    t_list  *previous_to_min;
    
    if (!list || !*list)
        return ;
    sorted_head = NULL;
    sorted_tail = NULL;
    min = NULL;
    original = *list;
    while (original)
    {
        previous_to_min = NULL;
        min = find_min(options, &original, &previous_to_min);
        remove_from_original(&original, min, previous_to_min);
        min->next = NULL;
        append_to_sorted(&sorted_head, &sorted_tail, min);
    }
    *list = sorted_head;
    return ;
}
