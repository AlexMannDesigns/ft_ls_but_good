#include "ft_ls.h"

static void long_display_setup(t_ls *state, t_list *files)
{
    get_usr_and_grp(state, files);
    get_field_widths_and_total(state, files);
    add_to_buf_len(&(state->print), "total ", 6);
    add_num_to_buf(&(state->print), state->print.total);
    add_to_buf_len(&(state->print), "\n", 1);
    return ;
}

/*
 * The ordering of the functions in the dispatch table must be in sync with
 * the t_display enum
*/
static const t_print_format *get_print_format_handlers(void)
{
    static const t_print_format dispatch_table[] = {
        print_long_format,
        print_comma_format,
        print_one_format,
    };
    return (dispatch_table);
}

void    print_control(t_ls *state, t_list *files)
{
    const t_print_format    *print_format_handlers;
    t_list                  *iter;
    t_file_info             *current;
    void                    (*print_format_handler)(t_ls *, t_list *);

    if (!files)
        return ;
    if (state->options.display == LONG)
        long_display_setup(state, files);
    else if (state->options.display == COLUMNS)
        return (print_columns_format(state, files));
    print_format_handlers = get_print_format_handlers();
    print_format_handler = print_format_handlers[state->options.display];
    iter = files;
    while (iter)
    {
        current = (t_file_info *) iter->content;
        if (file_should_be_printed(state, current->path))
            print_format_handler(state, iter);
        iter = iter->next;
    }
    state->print.print_newline = TRUE;
    return ;
}
