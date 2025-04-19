#include "ft_ls.h"

// the comma display should print new lines if a file name wont fit in the
// terminal window. If writing to a pipe or file it was about 80 char max
// line length.
void    print_comma_format(t_ls *state, t_list *current)
{
    t_file_info     *content;

    content = (t_file_info *) current->content;
    add_to_buf(state, content->path);
    if (current->next)
    {
        add_to_buf(state, ", ");
        return ;
    }
    if (state->printing_file_args)
        add_to_buf(state, ",");
    add_to_buf(state, "\n");
    return ;
}
