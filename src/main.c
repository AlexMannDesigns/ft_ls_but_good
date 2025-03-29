
#include "ft_ls.h"
#include "libft.h"
#include <stdio.h>

static char *get_display(t_ls state)
{
    if (state.options.display == COLUMNS)
        return ("columns");
    if (state.options.display == LONG)
        return ("long");
    if (state.options.display == COMMA)
        return ("comma");
    if (state.options.display == ONE)
        return ("one");
    return ("error");
}

static char *get_sort(t_ls state)
{
    if (state.options.sort == LEXICOGRAPHICAL)
        return ("lexicographical");
    if (state.options.sort == TIME)
        return ("time");
    if (state.options.sort == SIZE)
        return ("size");
    return ("error");
}

void    print_options_state(t_ls state)
{
    printf(
        "display = %s\nsort = %s\nrecursive = %d\nreversed = %d\nall = %d\nargv_idx = %d\n",
        get_display(state),
        get_sort(state),
        check_misc_option_bit(state.options.misc, RECURSIVE),
        check_misc_option_bit(state.options.misc, REVERSED),
        check_misc_option_bit(state.options.misc, ALL),
        state.argv_index
    );

    return ;
}


int main(int argc, char **argv)
{
    t_ls    state;

    (void) argc;
    ft_bzero(&state, sizeof(t_ls));
    options_control(&state, argv);
    print_options_state(state);
    return (0);
}

