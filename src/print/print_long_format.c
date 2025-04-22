#include "ft_ls.h"

void    number_of_links(t_print *print, unsigned int st_nlink)
{
    unsigned int    num_len;
    unsigned int    links;
    char            *links_str;

    links = st_nlink;
    num_len = get_num_len(links);
    add_spaces_to_buf(print, print->link_width - num_len);
    // let's create an add_int_to_buf() with 64bit unsigned int
    links_str = ft_itoa(st_nlink);
    if (!links_str)
        print_malloc_error_and_exit();
    add_to_buf_len(print, links_str, num_len);
    free(links_str);
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
    number_of_links(print_ptr, file_info->sys_file_info.st_nlink);
    add_to_buf_len(print_ptr, " ", 1);  // for testing DELETE ME


    add_to_buf(print_ptr, file_info->path);
    add_to_buf(print_ptr, "\n");
    //print_one_format(state, current);
    return ;
}
