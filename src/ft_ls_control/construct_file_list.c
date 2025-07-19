#include "ft_ls.h"
#include <dirent.h>

static t_list   *handle_permission_denied(t_ls *state, t_file_info *dir_info)
{
    if (check_misc_option_bit(state->options.misc, RECURSIVE))
        flush_buf(&(state->print));
    if (state->options.display == LONG)
    {
        print_total(&(state->print), 0UL);
        flush_buf(&(state->print));
    }
    print_filename_error(dir_info->path.str);
    return (NULL);
}

static char    *build_path(t_string path, char *d_name)
{
    char        *path_with_slash;
    char        *full_path;

    path_with_slash = ft_strnew(path.len + 1);
    if (!path_with_slash)
        print_malloc_error_and_exit();
    ft_strcpy(path_with_slash, path.str);
    path_with_slash[path.len] = '/';
    full_path = ft_strjoin(path_with_slash, d_name);
    free(path_with_slash);
    return (full_path);
}

static void    read_and_add_file(t_list **list, t_string dir_path, char *filename)
{
    struct stat sys_file_info;
    char        *full_path;

    full_path = build_path(dir_path, filename);
    if (!full_path)
        print_malloc_error_and_exit();
    if (lstat(full_path, &sys_file_info) != 0)
        print_stat_error_and_exit(filename);
    add_node_to_list(list, filename, sys_file_info, full_path);
    free(full_path);
    return ;
}

/*
 * opendir and readdir loop. This cycles through the contents of a directory
 * and constructs a linked list with the content.
 */
t_list  *construct_file_list(t_ls *state, t_file_info *dir_info)
{
    t_list          *file_list;
    DIR             *directory_stream;
    struct dirent   *directory_position;

    directory_stream = opendir(dir_info->path.str);
    if (directory_stream == NULL)
        return (handle_permission_denied(state, dir_info));
    file_list = NULL;
    state->print.list_len = 0;
    directory_position = readdir(directory_stream);
    while (directory_position != NULL)
    {
        if (file_should_be_printed(state, directory_position->d_name))
        {
            // TODO the length of the filename is also in directory_position -
            // we should refactor to make use of this to avoid extra looping.
            read_and_add_file(&file_list, dir_info->path, directory_position->d_name);
            (state->print.list_len)++;
        }
        directory_position = readdir(directory_stream);
    }
    closedir(directory_stream);
    return (file_list);
}
