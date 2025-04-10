
#include "ft_ls.h"
#include "libft.h"

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
static void invalid_args_sort(char **invalid_args)
{
    size_t  i;
    size_t  change;
    char    **current;
    char    **next;

    change = FALSE;
    i = 0;
    while (invalid_args[i + 1])
    {
        current = &(invalid_args[i]);
        next = &(invalid_args[i + 1]);
        if (ft_strcmp(*current, *next) > 0)
        {
            swap_positions(current, next);
            change = TRUE;
        }
        i++;
    }
    if (change)
        invalid_args_sort(invalid_args);
    return ;
}

void    print_invalid_args(char ***invalid_args)
{
    size_t  i;

    if (!invalid_args || !(*invalid_args))
        return ;
    invalid_args_sort(*invalid_args);
    i = 0;
    while ((*invalid_args)[i])
    {
        ft_putstr_fd("ft_ls: ", STDERR_FILENO);
        ft_putstr_fd((*invalid_args)[i], STDERR_FILENO);
        ft_putendl_fd(": No such file or directory", STDERR_FILENO);
        i++;
    }
    ft_free_char_array(invalid_args);
    return ;
}

