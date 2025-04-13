#include "ft_ls.h"
#include <stdlib.h>
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

/*
 * This is function prints the options state and is for testing purposes only
 */
void    print_options_state_and_exit(t_ls state)
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
    exit(EXIT_SUCCESS);
}
