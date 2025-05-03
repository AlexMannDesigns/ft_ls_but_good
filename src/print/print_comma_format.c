#include "ft_ls.h"

// the comma display should print new lines if a file name wont fit in the
// terminal window. If writing to a pipe or file it was about 80 char max
// line length.
void    print_comma_format(t_ls *state, t_list *files)
{
    t_list          *iter;
    t_file_info     *content;
    t_print         *print_ptr;

    print_ptr = &(state->print);
    iter = files;
    while (iter)
    {
        content = (t_file_info *) iter->content;
        add_to_buf(print_ptr, content->path);
        if (iter->next)
        {
            add_to_buf(print_ptr, ", ");
            return ;
        }
        if (print_ptr->printing_file_args)
            add_to_buf(print_ptr, ",");
        iter = iter->next;
    }
    add_to_buf(print_ptr, "\n");
    return ;
}
