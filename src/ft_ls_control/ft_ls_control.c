
#include "ft_ls.h"

// t_list  *construct_file_list(t_file_info *dir_info)
// {
//     t_list  *file_list;
//
//     //opendir and readdir loop with lstat to populate the linked list
//
//     return (file_list);
// }
//
// void    ft_ls_recursion_control(t_options options, t_file_info *dir_info)
// {
//     t_list  *file_list;
//
//     file_list = construct_file_list(dir_info);
//     sort_node_list(options, &file_list);
//     // print_control(state);
//     // recursion_control(state, dir);
//     return ;
// }
//
// void    directory_control(t_ls *state)
// {
//     t_list      *iter;
//     
//     iter = state->directories;
//     while (iter)
//     {
//         ft_ls_recursion_control(state->options, iter->content);
//         iter = iter->next;
//     }
//     return ;
// }

// This should be a generic function for printing out files, either from
// the command line or from the contents of a directory 
// Maybe 'print_control' would be better.
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

/*
    - validate paths in argv, adding files to one array, dirs to another and invalid paths to another
    - sort the arrays based on sort option
    - print errors for invalid paths (NB no linebreaks after each, including the last)
    - print names of normal files based on display option
    - loop through dirs in ft_ls_control()
    
    NB:
    - only print name of dir before contents (e.g. libft: ) if more than one filename is passed as arg (valid or not)
        - total_num_filename_args or similar should be set...? We need some way of deciding whether to print it 
        - furthermore, the 'title' printed of each dir appears to just be the path that was passed
            - (e.g. '~' expands to absolute path to HOME, "ls ../../foo bar" foo would not be changed to an absolute path)
            - with the -R option, if no file is specified, it refers to current dir as '.' i.e. './libft:' etc)
    - array index variables should be size_t, let's keep it consistent
    
*/
void ft_ls_control(t_ls *state, char **argv)
{
    filename_args_control(state, argv);
    print_invalid_args(&(state->invalid_args));
    sort_node_list(state->options, &(state->regular_files));
    sort_node_list(state->options, &(state->directories));
    print_files(state->options, state->regular_files);
    //directory_control(state);
    cleanup_lists(state);
    return ;
    // printf("%p %p %p\n", state->directories, state->regular_files, state->invalid_args);
}

