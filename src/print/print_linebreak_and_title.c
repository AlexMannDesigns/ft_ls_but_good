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
    t_print *print_ptr;

    print_ptr = &(state->print);
    if (print_ptr->print_newline)
        add_nl_to_buf(print_ptr);
    if (state->remaining_argv_len > 1
        || (print_ptr->print_newline
        && check_misc_option_bit(state->options.misc, RECURSIVE)))
    {
        add_to_buf(print_ptr, directory_name, 0);
        add_to_buf(print_ptr, ":", 1);
        add_nl_to_buf(print_ptr);
    }
    return ;
}
