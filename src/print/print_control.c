#include "ft_ls.h"

/*
 * The ordering of the functions in the dispatch table must be in sync with
 * the t_display enum
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

static void zero_field_widths(t_print *print)
{
    print->link_width = 0;
    print->user_width = 0;
    print->group_width = 0;
    print->size_width = 0;
}
/*
 * For the long format we need to analyse the length of various fields in each
 * file so that we can print the output with nicely aligned columns.
*/
void    get_field_widths(t_ls *state, t_list *files)
{
    t_list          *iter;
    t_file_info     *current;
    unsigned int    max_links;  // should be a 'max_lens' struct

    zero_field_widths(&(state->print));
    // bzero max lens struct
    max_links = 0;
    iter = files;
    while (iter)
    {
        current = (t_file_info *) iter->content;
        if (current->sys_file_info.st_nlink > max_links)
            max_links = current->sys_file_info.st_nlink;
        // do likewise for other values width is needed for
        iter = iter->next;
    }
    // set field widths in helper
    state->print.link_width = get_num_len(max_links) + 2;
    // consider setting predefined vals for column padding
    return ;
}

void    print_control(t_ls *state, t_list *files)
{
    const t_print_format    *print_format_handlers;
    t_list                  *iter;
    t_file_info             *current;
    void                    (*print_format_handler)(t_ls *, t_list *);

    if (!files)
        return ;
    print_format_handlers = get_print_format_handlers();
    print_format_handler = print_format_handlers[state->options.display];
    // if check for long display here. We don't need field widths otherwise
    // Also, we need to the 'total' for each dir with long display format
    get_field_widths(state, files);
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
