#include "ft_ls.h"


void    print_newline_and_title(t_ls *state, char *directory_name)
{
    if (state->print.print_newline)
        ft_putstr("\n");
    if (state->print.printing_directory && state->remaining_argv_len > 1)
    {
        ft_putstr(directory_name);
        ft_putendl(":");
    }
    return ;
}

void    ft_ls_recursion_control(t_ls *state, t_file_info *dir_info)
{
    t_list  *file_list;

    print_newline_and_title(state, dir_info->path);
    file_list = construct_file_list(dir_info);
    sort_node_list(state->options, &file_list);
    print_control(state, file_list);

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
    print_control(state, state->regular_files);
    state->print.printing_directory = TRUE;
    iter = state->directories;
    while (iter)
    {
        ft_ls_recursion_control(state, iter->content);
        iter = iter->next;
    }
    cleanup_lists(state);
    return ;
    // printf("%p %p %p\n", state->directories, state->regular_files, state->invalid_args);
}

