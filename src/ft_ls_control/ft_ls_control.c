#include "ft_ls.h"

#include <dirent.h>

// This should be a generic function for printing out files, either from
// the command line or from the contents of a directory 
// Maybe 'print_control' would be better.
// 
// Line breaks:
// each directory or the file args have a line break printed after them, except the last
// The best way to handle this may be to print a line break every time this function is called
// before the files (and title) are printed, except the first time it's called. e.g. put a var
// in the state struct.
//
// Titles (e.g. "libft:\n" being printed before the contents of libft):
// If there is one filename arg then no title is printed
// If there are multiple filename args (even if invalid) no title is printed
// This can probably also be handled with a var in the state struct.
void    print_files(t_options options, t_list *files)
{
    t_list      *iter;
    t_file_info *current_file_info;

    (void) options;
    iter = files;
    while (iter)
    {
        current_file_info = (t_file_info *) iter->content;
        ft_putendl(current_file_info->path);
        iter = iter->next;
    }
    return ;
}

char    *build_path(char *path, char *d_name)
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

void    read_and_add_file(t_list **file_list, char *path, char *d_name)
{
    struct stat sys_file_info;
    char        *full_path;

    full_path = build_path(path, d_name);
    if (!full_path)
        print_malloc_error_and_exit();
    if (lstat(full_path, &sys_file_info) != 0)
        print_stat_error_and_exit(d_name); 
    add_node_to_list(file_list, d_name, sys_file_info);
    free(full_path);
    return ;
}

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

void    ft_ls_recursion_control(t_options options, t_file_info *dir_info)
{
    t_list  *file_list;

    file_list = construct_file_list(dir_info);
    sort_node_list(options, &file_list);
    print_files(options, file_list);

    // recursion_control(state, dir);
    free_node_list(&file_list);
    return ;
}

/*
    NB:
    - array index variables should be size_t, let's keep it consistent
*/
void ft_ls_control(t_ls *state, char **argv)
{
    t_list      *iter;
    
    filename_args_control(state, argv);
    sort_node_list(state->options, &(state->regular_files));
    sort_node_list(state->options, &(state->directories));
    print_files(state->options, state->regular_files);
    iter = state->directories;
    while (iter)
    {
        ft_ls_recursion_control(state->options, iter->content);
        iter = iter->next;
    }
    cleanup_lists(state);
    return ;
    // printf("%p %p %p\n", state->directories, state->regular_files, state->invalid_args);
}

