#include "ft_ls.h"

// so for this format, the linked list is an issue, as we will have to scan the
// list each time we print a file name to find the relevant node
// However, we will need to scan the list before printing anyway, to determine
// the column width (i.e. find the longest file name). While we do that, we
// should just copy the path pointer into a char array, which we can then just
// index into as we print.
void    print_columns_format(t_ls *state, t_list *files)
{
    t_list  *iter;

    // ft_putstr("list len = ");
    // ft_putnbr((int) state->print.list_len);
    // ft_putchar('\n');
    iter = files;
    while (iter)
    {
        print_one_format(state, iter);
        iter = iter->next;
    }
    state->print.print_newline = TRUE;
    return ;
}
