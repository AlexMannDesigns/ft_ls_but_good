#include "ft_ls.h"

// note that dot files are still printed when passed as arg
// e.g. ls .gitignore -> prints .gitignore despite the lack of -a option
// maybe add 'printing_filename_args' bool to the state
int file_should_be_printed(t_options options, char *path)
{
    if (check_misc_option_bit(options.misc, ALL))
        return (TRUE);
    if (path[0] == '.')
        return (FALSE);
    return (TRUE);
}

// The differnt display options should be in a function dispatch table
void    print_display_dispatch(t_ls *state, t_list *current)
{
    t_file_info     *content;
    unsigned int    display;

    content = (t_file_info *) current->content;
    display = state->options.display;
    // print -1 display as a fall-back before other formats are implemented
    if (display == ONE || display == LONG || display == COLUMNS)
    {
        ft_putstr(content->path);
        ft_putchar('\n');
        return ;
    }
    // the comma display should print new lines if a file name wont fit in the
    // terminal window.
    if (display == COMMA)
    {
        ft_putstr(content->path);
        if (current->next)
            ft_putstr(", ");
        else
        {
            if (state->printing_file_args)
                ft_putchar(',');
            ft_putchar('\n');
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
        if (file_should_be_printed(state->options, current->path) || state->printing_file_args)
            print_display_dispatch(state, iter);
        iter = iter->next;

    }
    state->print_newline = TRUE;
    return ;
}
