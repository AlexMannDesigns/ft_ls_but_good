#include "ft_ls.h"

void    print_control(t_ls *state, t_list *files)
{
    unsigned int    display;

    if (!files)
        return ;
    display = state->options.display;
    if (display == LONG)
        print_long_format(state, files);
    else if (display == COLUMNS && isatty(STDOUT_FILENO))
        print_columns_format(state, files);
    else if (display == COLUMNS || display == ONE)
        print_one_format(state, files);
    else if (display == COMMA)
        print_comma_format(state, files);
    else
        exit(EXIT_FAILURE);  // create handler for this
    state->print.print_newline = TRUE;
    return ;
}
