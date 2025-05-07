#include "ft_ls.h"

static int is_recursion_dir(t_ls *state, t_file_info *file_info)
{
    if (!file_should_be_printed(state, file_info->path.str))
        return (FALSE);
    if (get_file_type(file_info->sys_file_info.st_mode) == DIRECTORY
        && !ft_strequ(file_info->path.str, ".")
        && !ft_strequ(file_info->path.str, ".."))
        return (TRUE);
    return (FALSE);
}

static void    ft_ls_recursion(t_ls *state, t_file_info *dir_info)
{
    t_list      *file_list;
    t_list      *iter;
    t_file_info *current;

    print_linebreak_and_title(state, dir_info->path.str);
    file_list = construct_file_list(state, dir_info);
    sort_node_list(state->options, &file_list);
    print_control(state, file_list);
    if (check_misc_option_bit(state->options.misc, RECURSIVE))
    {
        iter = file_list;
        while (iter)
        {
            current = (t_file_info *) iter->content;
            if (is_recursion_dir(state, current))
                ft_ls_recursion(state, format_recursion_path(current, dir_info->path.str));
            iter = iter->next;
        }
    }
    free_node_list(&file_list);
    return ;
}

void    print_filename_args(t_ls *state)
{
    state->print.printing_file_args = TRUE;
    if (state->options.display == COLUMNS)
        state->print.list_len = get_list_len(state->regular_files);
    print_control(state, state->regular_files);
    state->print.printing_file_args = FALSE;
    return ;
}

void    print_directories(t_ls *state)
{
    t_list      *iter;

    iter = state->directories;
    while (iter)
    {
        ft_ls_recursion(state, iter->content);
        iter = iter->next;
    }
    return ;
}

void ft_ls_control(t_ls *state, char **argv)
{
    filename_args_control(state, argv);
    sort_node_list(state->options, &(state->regular_files));
    sort_node_list(state->options, &(state->directories));
    print_filename_args(state);
    print_directories(state);
    flush_buf(&(state->print));
    cleanup_lists_and_print_buf(state);
    return ;
}

