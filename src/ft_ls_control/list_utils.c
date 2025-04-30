#include "ft_ls.h"

static void add_link_info(t_file_info *file_info, char *full_path)
{
    char        link_path[PATH_MAX];

    file_info->link_len = readlink(full_path, link_path, PATH_MAX);
    if (file_info->link_len == -1)
        exit(EXIT_FAILURE);  // handle this error properly
    link_path[file_info->link_len] = '\0';
    file_info->link = ft_strdup(link_path);
    if (!file_info->link)
        print_malloc_error_and_exit();
    return ;
}

void add_node_to_list(t_list **list, char *filename, struct stat sys_file_info, char *full_path)
{
    t_file_info file_info;
    t_list      *new_node;

    ft_bzero((void *) &file_info, sizeof(t_file_info));
    file_info.sys_file_info = sys_file_info;
    file_info.path = ft_strdup(filename);
    if (!file_info.path)
        print_malloc_error_and_exit();
    if (get_file_type(sys_file_info.st_mode) == LINK)
        add_link_info(&file_info, full_path);
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
    if (file_info->path)
        ft_strdel(&(file_info->path));
    if (file_info->link)
        ft_strdel(&(file_info->link));
    return ;
}

static void    free_usr_grp_info(void *usr_grp_info_content, size_t n)
{
    t_known_usr_grp  *usr_grp_info;

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
    if (state->known_usr)
        ft_lstdel(&(state->known_usr), free_usr_grp_info);
    if (state->known_grp)
        ft_lstdel(&(state->known_grp), free_usr_grp_info);
    return ;
}
