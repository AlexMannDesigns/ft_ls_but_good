#include "ft_ls.h"

static const unsigned int *get_rwx_macros_table()
{
    static const unsigned int  rwx_macros[] = {
        S_IRUSR,
        S_IWUSR,
        S_IXUSR,
        S_IRGRP,
        S_IWGRP,
        S_IXGRP,
        S_IROTH,
        S_IWOTH,
        S_IXOTH,
        0
    };

    return (rwx_macros);
}

/*
 * Each character represents the following. In all cases '-' means no permission:
 * 0 = file type
 * 1-3 = RWX permissions for owner
 * 4-6 = RWX permissions for group
 * 7-9 = RWX permissions for other
 *
 * NB: characters 3, 6, and 9 represent the first of the following:
 *  - S = not executable and set-user-id-mode is set, either in owner or group.
 *  - s = is executable and set-user-id-mode is set, either in owner or group.
 *  - x = file is executable or directory is searchable
 *  - - = Not readable, writable or executable nor set-user-id-mode nor sticky
 *  - T = sticky bit is set, but not ececute or search permission
 *  - t = sticky bit is set and is searchable or executable
 */
void    file_type_and_permissions(t_print *print, mode_t mode)
{
    const unsigned int  *rwx_macros_table;
    char                rwx_str[11];
    char                c;
    size_t              i;

    rwx_str[10] = '\0';
    rwx_str[0] = get_file_type_char(mode);
    rwx_macros_table = get_rwx_macros_table();
    i = 0;
    while (rwx_macros_table[i])
    {
        c = '-';
        if (mode & rwx_macros_table[i])
            c = RWX_CHARS[i];
        rwx_str[i + 1] = c;
        i++;
    }
    // rwx_str[3] = handle_set_user_id_mode();
    // rwx_str[6] = handle_set_group_id_mode();
    // rwx_str[9] = handle_sticky_bit();
    add_to_buf_len(print, rwx_str, 10);
    return ;
}

void    number_of_links(t_print *print, unsigned int st_nlink)
{
    unsigned int    num_len;
    unsigned int    links;
    char            *links_str;

    links = st_nlink;
    num_len = 0;
    while (links)
    {
        links = links / 10;
        num_len++;
    } // create get_num_len() function as we do this in a couple places
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
