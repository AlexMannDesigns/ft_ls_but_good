#include "ft_ls.h"

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
    unsigned int    max_user;
    unsigned int    max_group;

    zero_field_widths(&(state->print));
    // bzero max lens struct
    max_links = 0;
    max_user = 0;
    max_group = 0;
    iter = files;
    while (iter)
    {
        // we need to check file will be printed here
        // let's invert this if check once we've built the helper
        if (!file_should_be_printed(state, current->path))
            ;
        else
        {
            current = (t_file_info *) iter->content;
            if (current->sys_file_info.st_nlink > max_links)
                max_links = current->sys_file_info.st_nlink;
            if (current->user_id_str_len > max_user)
                max_user = current->user_id_str_len;
            if (current->group_id_str_len > max_group)
                max_group = current->group_id_str_len;

            // do likewise for other values width is needed for
        }
        iter = iter->next;
    }
    // set field widths in helper
    state->print.link_width = (unsigned int) get_num_len(max_links) + 2;
    state->print.user_width = max_user + 1;
    state->print.group_width = max_group + 2;
    // consider setting predefined vals for column padding
    return ;
}
