#include "ft_ls.h"
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>

static t_known_usr_grp add_node_to_known_usr_list(t_list **known_usr_list, t_file_info file_info)
{
    t_known_usr_grp usr_info;
    t_list          *new_node;
	struct passwd	*pwd;

    ft_bzero((void *) &usr_info, sizeof(t_known_usr_grp));
	pwd = getpwuid(file_info.sys_file_info.st_uid);
    if (!pwd)
        exit(EXIT_FAILURE);  // create error handler
    usr_info.usr_grp_name_str = ft_strdup(pwd->pw_name);
    if (!(usr_info.usr_grp_name_str))
        print_malloc_error_and_exit();
    usr_info.usr_grp_name_len = ft_strlen(usr_info.usr_grp_name_str);
    usr_info.usr_grp_id = file_info.sys_file_info.st_uid;
    new_node = ft_lstnew((void *) &usr_info, sizeof(t_known_usr_grp));
    if (!new_node)
        print_malloc_error_and_exit();
    if (!*known_usr_list)
        *known_usr_list = new_node;
    else
        ft_lstadd_back(known_usr_list, new_node);
    return (usr_info);
}

static t_known_usr_grp add_node_to_known_grp_list(t_list **known_grp_list, t_file_info file_info)
{
    t_known_usr_grp grp_info;
    t_list          *new_node;
	struct group    *grp;

    ft_bzero((void *) &grp_info, sizeof(t_known_usr_grp));
	grp = getgrgid(file_info.sys_file_info.st_gid);
    if (!grp)
        exit(EXIT_FAILURE);  // create error handler
    grp_info.usr_grp_name_str = ft_strdup(grp->gr_name);
    if (!(grp_info.usr_grp_name_str))
        print_malloc_error_and_exit();
    grp_info.usr_grp_name_len = ft_strlen(grp_info.usr_grp_name_str);
    grp_info.usr_grp_id = file_info.sys_file_info.st_gid;
    new_node = ft_lstnew((void *) &grp_info, sizeof(t_known_usr_grp));
    if (!new_node)
        print_malloc_error_and_exit();
    if (!*known_grp_list)
        *known_grp_list = new_node;
    else
        ft_lstadd_back(known_grp_list, new_node);
    return (grp_info);
}

static void    check_known_usr(t_list **known_usr_list, t_file_info *current)
{
    t_list          *iter;
    t_known_usr_grp *current_usr;
    t_known_usr_grp new_usr_info;

    iter = *known_usr_list;
    while (iter)
    {
        current_usr = (t_known_usr_grp *) iter->content;
        if (current_usr->usr_grp_id == current->sys_file_info.st_uid)
        {
            current->user_id_str = current_usr->usr_grp_name_str;
            current->user_id_str_len = current_usr->usr_grp_name_len;
            return ;
        }
        iter = iter->next;
    }
    new_usr_info = add_node_to_known_usr_list(known_usr_list, *current);
    current->user_id_str = new_usr_info.usr_grp_name_str;
    current->user_id_str_len = new_usr_info.usr_grp_name_len;
    return ;
}

static void    check_known_grp(t_list **known_grp_list, t_file_info *current)
{
    t_list          *iter;
    t_known_usr_grp *current_usr;
    t_known_usr_grp new_usr_info;

    iter = *known_grp_list;
    while (iter)
    {
        current_usr = (t_known_usr_grp *) iter->content;
        if (current_usr->usr_grp_id == current->sys_file_info.st_gid)
        {
            current->group_id_str = current_usr->usr_grp_name_str;
            current->group_id_str_len = current_usr->usr_grp_name_len;
            return ;
        }
        iter = iter->next;
    }
    new_usr_info = add_node_to_known_grp_list(known_grp_list, *current);
    current->group_id_str = new_usr_info.usr_grp_name_str;
    current->group_id_str_len = new_usr_info.usr_grp_name_len;
    return ;
}

void    get_usr_and_grp(t_ls *state, t_list *files)
{
    t_list          *iter;
    t_file_info     *current;

    iter = files;
    while (iter)
    {
        current = (t_file_info *) iter->content;
        check_known_usr(&(state->known_usr), current);
        check_known_grp(&(state->known_grp), current);
        iter = iter->next;
    }
    return ;
}
