#include "ft_ls.h"

void add_node_to_list(t_list **list, char *filename, struct stat sys_file_info)
{
    t_file_info file_info;
    t_list      *new_node;

    ft_bzero((void *) &file_info, sizeof(t_file_info));
    file_info.sys_file_info = sys_file_info;
    file_info.path = ft_strdup(filename);
    if (!file_info.path)
        print_malloc_error_and_exit();
    new_node = ft_lstnew((void *) &file_info, sizeof(t_file_info));
    if (!new_node)
        print_malloc_error_and_exit();
    if (!*list)
        *list = new_node;
    else
        ft_lstadd_back(list, new_node);
    return ;
}

static void    free_file_info(void *file_info_content, size_t n)
{
    t_file_info *file_info;

    (void) n;
    file_info = (void *) file_info_content;
    if (file_info->command_line)
        ft_strdel(&(file_info->command_line));
    if (file_info->path)
        ft_strdel(&(file_info->path));
    return ;
}

void    free_node_list(t_list **list)
{
    ft_lstdel(list, free_file_info);
    return ;
}

void    cleanup_lists_and_print_buf(t_ls *state)
{
    if (state->directories)
        free_node_list(&(state->directories));
    if (state->regular_files)
        free_node_list(&(state->regular_files));
    if (state->print.print_buf)
        free(state->print.print_buf);
    return ;
}
