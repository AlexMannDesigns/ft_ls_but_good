#include "ft_ls.h"
#include "libft.h"

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

static void    free_usr_grp_info(void *usr_grp_info_content, size_t n)
{
    t_known_usr_grp  *usr_grp_info;

    ft_putendl("BONJOUR");
    (void) n;
    usr_grp_info = (void *) usr_grp_info_content;
    if (usr_grp_info->usr_grp_name_str)
        ft_strdel(&(usr_grp_info->usr_grp_name_str));
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
    // remember to delete the known usr grp lists
    if (state->known_usr)
        ft_lstdel(&(state->known_usr), free_usr_grp_info);
    if (state->known_grp)
        ft_lstdel(&(state->known_grp), free_usr_grp_info);

    return ;
}
