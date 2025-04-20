#include "ft_ls.h"

// the comma display should print new lines if a file name wont fit in the
// terminal window. If writing to a pipe or file it was about 80 char max
// line length.
void    print_comma_format(t_ls *state, t_list *current)
{
    t_file_info     *content;
    t_print         *print_ptr;

    print_ptr = &(state->print);
    content = (t_file_info *) current->content;
    add_to_buf(print_ptr, content->path);
    if (current->next)
    {
        add_to_buf(print_ptr, ", ");
        return ;
    }
    if (print_ptr->printing_file_args)
        add_to_buf(print_ptr, ",");
    add_to_buf(print_ptr, "\n");
    return ;
}
