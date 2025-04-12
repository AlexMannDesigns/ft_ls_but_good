#include "ft_ls.h"

void    ft_ls_recursion_control(t_options options, t_file_info *dir_info)
{
    t_list  *file_list;

    file_list = construct_file_list(dir_info);
    sort_node_list(options, &file_list);
    print_control(options, file_list);

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
    print_control(state->options, state->regular_files);
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

