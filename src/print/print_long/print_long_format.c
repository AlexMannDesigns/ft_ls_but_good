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
 * Here we analyse what's in the file_info (stat) struct to display various
 * metadata about the file.
 *  - file type + rwx permissions
 *  - number of links (st_nlink)
 *  - owner name
 *  - group name
 *  - number of bytes in the file
 *  - last modified date and time
 *  - file name
 *  - link info (if symlink)
*/
static void    print_long_format_control(t_print *print, t_file_info *file_info)
{
    file_type_and_permissions(print, file_info->sys_file_info.st_mode);
    number_of_links(print, (unsigned long) file_info->sys_file_info.st_nlink);
    user_and_group(print, file_info);
    file_size(print, (unsigned long) file_info->sys_file_info.st_size);
    date_and_time(print, file_info->sys_file_info.st_mtime);
    file_name_and_link(print, file_info);
    return ;
}

void    print_long_format(t_ls *state, t_list *files)
{
    t_file_info *file_info;
    t_print     *print_ptr;
    t_list      *iter;

    long_display_setup(state, files);
    print_ptr = (t_print *) &(state->print);
    iter = files;
    while (iter)
    {
        file_info = (t_file_info *) iter->content;
        if (file_should_be_printed(state, file_info->path))
            print_long_format_control(print_ptr, file_info);
        iter = iter->next;
    }
    return ;
}
