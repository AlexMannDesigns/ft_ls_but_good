#include "ft_ls.h"

/*
 * When printing the contents of directories, we need to manage when
 * the linebreaks and titles are printed. We only need the title if there
 * is more than one filename arg in the argv. We print linebreaks before
 * the title of the next dir is printed, except in the case of the first
 * directory (or indeed, any non-directory args). The print_newline var
 * in the state is set to false when the program starts then to true
 * at the end of print_control().
*/
void    print_linebreak_and_title(t_ls *state, char *directory_name)
{
    if (state->print_newline)
        add_to_buf(state, "\n");
    if (state->remaining_argv_len > 1)
    {
        add_to_buf(state, directory_name);
        add_to_buf(state, ":\n");
    }
    return ;
}
