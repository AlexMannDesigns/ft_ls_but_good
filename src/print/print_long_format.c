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
    // overwrite the x's with the relevant above exceptions

    //TODO add_to_buf_len() with len param for when len value is known.
    add_to_buf_len(print, rwx_str, 10);
    add_to_buf_len(print, " ", 1);  // for testing DELETE
    return ;
}

/*
 * Here we analyse what's in the file_info (stat) struct to display various
 * metadata about the file.
 *  - file type + rwx permissions
 *  - number of links
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


    add_to_buf(print_ptr, file_info->path);
    add_to_buf(print_ptr, "\n");
    //print_one_format(state, current);
    return ;
}
