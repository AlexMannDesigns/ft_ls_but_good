#include "ft_ls.h"

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
    date_and_time(print_ptr, file_info->sys_file_info.st_mtime);
    file_name_and_link(print_ptr, file_info);
    return ;
}
