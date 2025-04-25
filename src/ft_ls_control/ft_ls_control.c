#include "ft_ls.h"
#include "libft.h"

static int is_recursion_dir(t_file_info *file_info)
{
    if (get_file_type(file_info->sys_file_info.st_mode) == DIRECTORY
        && !ft_strequ(file_info->path, ".")
        && !ft_strequ(file_info->path, ".."))
        return (TRUE);
    return (FALSE);
}

t_file_info *format_recursion_path(t_file_info *dir_info, char *parent_path)
{
    char    *temp;
    char    *new_path;
    size_t  len;

    len = ft_strlen(parent_path);
    temp = ft_strnew(len + 1);
    ft_strcpy(temp, parent_path);
    temp[len] = '/';
    new_path = ft_strjoin(temp, dir_info->path);
    free(temp);
    free(dir_info->path);
    dir_info->path = new_path;
    return (dir_info);
}

static void    ft_ls_recursion(t_ls *state, t_file_info *dir_info)
{
    t_list      *file_list;
    t_list      *iter;
    t_file_info *current;

    print_linebreak_and_title(state, dir_info->path);
    file_list = construct_file_list(state, dir_info);
    sort_node_list(state->options, &file_list);
    print_control(state, file_list);
    if (check_misc_option_bit(state->options.misc, RECURSIVE))
    {
        iter = file_list;
        while (iter)
        {
            current = (t_file_info *) iter->content;
            if (file_should_be_printed(state, current->path) && is_recursion_dir(current))
                ft_ls_recursion(state, format_recursion_path(current, dir_info->path));
            iter = iter->next;
        }
    }
    free_node_list(&file_list);
    return ;
}

void    print_filename_args(t_ls *state)
{
    state->print.printing_file_args = TRUE;
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

