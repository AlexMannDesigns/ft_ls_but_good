#include "ft_ls.h"

static void zero_field_widths(t_print *print)
{
    print->link_width = 0;
    print->user_width = 0;
    print->group_width = 0;
    print->size_width = 0;
}

static void check_and_update_max(t_file_info *current, t_max *max)
{
    if (current->sys_file_info.st_nlink > max->max_links)
        max->max_links = current->sys_file_info.st_nlink;
    if (current->user_id_str_len > max->max_user)
        max->max_user = current->user_id_str_len;
    if (current->group_id_str_len > max->max_group)
        max->max_group = current->group_id_str_len;
    if ((unsigned long) current->sys_file_info.st_size > max->max_size)
        max->max_size = (unsigned long) current->sys_file_info.st_size;
    return ;
}

/*
 * For the long format we need to analyse the length of various fields in each
 * file so that we can print the output with nicely aligned columns.
*/
void    get_field_widths(t_ls *state, t_list *files)
{
    t_list          *iter;
    t_file_info     *current;
    t_max           max_lens;

    zero_field_widths(&(state->print));
    ft_bzero((void *) &max_lens, sizeof(t_max));
    iter = files;
    while (iter)
    {
        current = (t_file_info *) iter->content;
        if (file_should_be_printed(state, current->path))
            check_and_update_max(current, &max_lens);
        iter = iter->next;
    }
    state->print.link_width = (unsigned long) get_num_len(max_lens.max_links) + 2;
    state->print.user_width = max_lens.max_user + 1;
    state->print.group_width = max_lens.max_group + 2;
    state->print.size_width = (unsigned long) get_num_len(max_lens.max_size) + 2;
    return ;
}
