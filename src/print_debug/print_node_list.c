#include "ft_ls.h"

/*
* just for debugging node lists. Not a part of the program
*/
void    print_node_list(t_list *list)
{
    t_file_info *current;

    ft_putstr("[ ");
    while (list)
    {
        current = list->content;
        ft_putstr(current->path.str);
        if (list->next)
            ft_putstr(", ");
        list = list->next;
    }
    ft_putendl("]");
    return ;
}

