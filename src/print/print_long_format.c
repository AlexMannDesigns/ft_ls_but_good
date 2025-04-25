#include "ft_ls.h"

void    number_of_links(t_print *print, unsigned long st_nlink)
{
    add_spaces_to_buf(print, (size_t) print->link_width - get_num_len(st_nlink));
    add_num_to_buf(print, st_nlink);
    return ;
}

void    user_and_group(t_print *print, t_file_info *file_info)
{
    add_spaces_to_buf(print, print->user_width - file_info->user_id_str_len);
    add_to_buf_len(print, file_info->user_id_str, file_info->user_id_str_len);
    add_spaces_to_buf(print, print->group_width - file_info->group_id_str_len);
    add_to_buf_len(print, file_info->group_id_str, file_info->group_id_str_len);
    return ;
}

void    file_size(t_print *print, unsigned long st_size)
{
    add_spaces_to_buf(print, (size_t) print->size_width - get_num_len(st_size));
    add_num_to_buf(print, st_size);
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
void    print_long_format(t_ls *state, t_list *current)
{
    t_file_info *file_info;
    t_print     *print_ptr;

    file_info = (t_file_info *) current->content;
    print_ptr = (t_print *) &(state->print);
    file_type_and_permissions(print_ptr, file_info->sys_file_info.st_mode);
    number_of_links(print_ptr, (unsigned long) file_info->sys_file_info.st_nlink);
    user_and_group(print_ptr, file_info);
    file_size(print_ptr, (unsigned long) file_info->sys_file_info.st_size);

    add_to_buf_len(print_ptr, " ", 1);  // for testing DELETE ME


    add_to_buf(print_ptr, file_info->path);
    add_to_buf(print_ptr, "\n");
    //print_one_format(state, current);
    return ;
}
