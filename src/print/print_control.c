#include "ft_ls.h"

/*
 * The ordering of the functions must be in sync with the display enum
*/
static const t_print_format *get_print_format_handlers(void)
{
    static const t_print_format dispatch_table[] = {
        print_columns_format,
        print_long_format,
        print_comma_format,
        print_one_format,
    };
    return (dispatch_table);
}

void    print_display_dispatch(t_ls *state, t_list *current)
{
    const t_print_format    *format_handlers;

    format_handlers = get_print_format_handlers();
    format_handlers[state->options.display](state, current);
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
