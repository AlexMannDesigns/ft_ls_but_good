#include "ft_ls.h"

int file_should_be_printed(t_ls *state, char *path)
{
    unsigned int    print_all;

    print_all = check_misc_option_bit(state->options.misc, ALL);
    if (print_all || state->printing_file_args)
        return (TRUE);
    if (path[0] == '.')
        return (FALSE);
    return (TRUE);
}

// The differnt display options should be in a function dispatch table
// consider creating a malloc'd buffer we copy into a flush, rather than
// repeatedly calling write() like this
void    print_display_dispatch(t_ls *state, t_list *current)
{
    t_file_info     *content;
    unsigned int    display;

    content = (t_file_info *) current->content;
    display = state->options.display;
    // print -1 display as a fall-back before other formats are implemented
    if (display == ONE || display == LONG || display == COLUMNS)
    {
        add_to_buf(state, content->path);
        add_to_buf(state, "\n");
        return ;
    }
    // the comma display should print new lines if a file name wont fit in the
    // terminal window. If writing to a pipe or file it was about 80 char max
    // line length.
    if (display == COMMA)
    {
        add_to_buf(state, content->path);
        if (current->next)
            add_to_buf(state, ", ");
        else
        {
            if (state->printing_file_args)
                add_to_buf(state, ",");
            add_to_buf(state, "\n");
        }
        return ;
    }
    return ;
}

void    print_control(t_ls *state, t_list *files)
{
    t_list      *iter;
    t_file_info *current;

    if (!files)
        return ;
    iter = files;
    while (iter)
    {
        current = (t_file_info *) iter->content;
        if (file_should_be_printed(state, current->path))
            print_display_dispatch(state, iter);
        iter = iter->next;

    }
    state->print_newline = TRUE;
    return ;
}
