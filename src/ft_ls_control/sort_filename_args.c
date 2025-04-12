
#include "ft_ls.h"

static void swap_positions(char **a, char **b)
{
    char    *temp;

    temp = *a;
    *a = *b;
    *b = temp;
    return ;
}

/*
 * Any invalid arguments passed via the argv to ls will be printed before
 * any other output in standard lexicographical order, regardless of the
 * options. We use a recursive bubble sort algo here.
 */
void sort_filename_args(char **args)
{
    size_t  i;
    size_t  change;
    char    **current;
    char    **next;

    change = FALSE;
    i = 0;
    while (args[i + 1])
    {
        current = &(args[i]);
        next = &(args[i + 1]);
        if (ft_strcmp(*current, *next) > 0)
        {
            swap_positions(current, next);
            change = TRUE;
        }
        i++;
    }
    if (change)
        sort_filename_args(args);
    return ;
}
