#include "ft_ls.h"

static void    ft_ls_recursion_control(t_ls *state, t_file_info *dir_info)
{
    t_list  *file_list;

    print_linebreak_and_title(state, dir_info->path);
    file_list = construct_file_list(dir_info);
    sort_node_list(state->options, &file_list);
    print_control(state, file_list);

    // recursion_control(state, dir);
    free_node_list(&file_list);
    return ;
}

void    print_filename_args(t_ls *state)
{
    state->printing_file_args = TRUE;
    print_control(state, state->regular_files);
    state->printing_file_args = FALSE;
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
    state->print_buf = (char *) ft_memalloc(BUF_SIZE * sizeof(char));
    if (!(state->print_buf))
        print_malloc_error_and_exit();
    print_filename_args(state);
    iter = state->directories;
    while (iter)
    {
        ft_ls_recursion_control(state, iter->content);
        iter = iter->next;
    }
    flush_buf(state);
    cleanup_lists_and_print_buf(state);
    return ;
}

