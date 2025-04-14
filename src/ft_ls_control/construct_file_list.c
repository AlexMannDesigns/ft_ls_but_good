#include "ft_ls.h"
#include <dirent.h>

static char    *build_path(char *path, char *d_name)
{
    char        *path_with_slash;
    char        *full_path;
    size_t      path_len;

    path_len = ft_strlen(path);
    path_with_slash = ft_strnew(path_len + 1);
    if (!path_with_slash)
        print_malloc_error_and_exit();
    ft_strcpy(path_with_slash, path);
    path_with_slash[path_len] = '/';
    full_path = ft_strjoin(path_with_slash, d_name);
    free(path_with_slash);
    return (full_path);
}

static void    read_and_add_file(t_list **list, char *dir_path, char *filename)
{
    struct stat sys_file_info;
    char        *full_path;

    full_path = build_path(dir_path, filename);
    if (!full_path)
        print_malloc_error_and_exit();
    if (lstat(full_path, &sys_file_info) != 0)
        print_stat_error_and_exit(filename);
    add_node_to_list(list, filename, sys_file_info);
    free(full_path);
    return ;
}

/*
 * opendir and readdir loop. This cycles through the contents of a directory
 * and constructs a linked list with the content.
 */
t_list  *construct_file_list(t_file_info *dir_info)
{
    t_list          *file_list;
    DIR             *directory_stream;
    struct dirent   *directory_position;

    directory_stream = opendir(dir_info->path);
    if (directory_stream == NULL)
    {
        print_filename_error(dir_info->path);
        return (NULL);
    }
    file_list = NULL;
    directory_position = readdir(directory_stream);
    while (directory_position != NULL)
    {
        read_and_add_file(&file_list, dir_info->path, directory_position->d_name);
        directory_position = readdir(directory_stream);
    }
    closedir(directory_stream);
    return (file_list);
}
