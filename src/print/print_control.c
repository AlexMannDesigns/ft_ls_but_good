#include "ft_ls.h"
#include "libft.h"
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>

/*
 * The ordering of the functions in the dispatch table must be in sync with
 * the t_display enum
*/
static const t_print_format *get_print_format_handlers(void)
{
    static const t_print_format dispatch_table[] = {
        print_columns_format,
        print_long_format,
        print_comma_format,
        print_one_format,
    };
    return (dispatch_table);
}

static void zero_field_widths(t_print *print)
{
    print->link_width = 0;
    print->user_width = 0;
    print->group_width = 0;
    print->size_width = 0;
}

t_known_usr_grp add_node_to_known_usr_list(t_list **list, t_file_info file_info)
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
    if (!*list)
        *list = new_node;
    else
        ft_lstadd_back(list, new_node);
    return (usr_info);
}

void    check_known_usr(t_ls *state, t_file_info *current)
{
    t_list          *iter;
    t_known_usr_grp *current_usr;
    t_known_usr_grp new_usr_info;

    iter = state->known_usr;
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
    new_usr_info = add_node_to_known_usr_list(&(state->known_usr), *current);
    current->user_id_str = new_usr_info.usr_grp_name_str;
    current->user_id_str_len = new_usr_info.usr_grp_name_len;
    return ;
}

// create new list in state of know user id's with their corresponding names and
// name lengths.
void    get_usr_and_grp(t_ls *state, t_list *files)
{
    t_list          *iter;
    t_file_info     *current;

    iter = files;
    while (iter)
    {
        current = (t_file_info *) iter->content;
        check_known_usr(state, current);
        iter = iter->next;
    }
    return ;
}

/*
 * For the long format we need to analyse the length of various fields in each
 * file so that we can print the output with nicely aligned columns.
*/
void    get_field_widths(t_ls *state, t_list *files)
{
    t_list          *iter;
    t_file_info     *current;
    unsigned int    max_links;  // should be a 'max_lens' struct
    unsigned int    max_user;
    // unsigned int    max_group;

    zero_field_widths(&(state->print));
    // bzero max lens struct
    max_links = 0;
    max_user = 0;
    // max_group = 0;
    iter = files;
    while (iter)
    {
        // we need to check file will be printed here
        current = (t_file_info *) iter->content;
        if (current->sys_file_info.st_nlink > max_links)
            max_links = current->sys_file_info.st_nlink;
        if (current->user_id_str_len > max_user)
            max_user = current->user_id_str_len;
        // get_group_name(current);
        // if (current->group_len > max_group)
        //     max_group = current->group_len;

        // do likewise for other values width is needed for
        iter = iter->next;
    }
    // set field widths in helper
    state->print.link_width = get_num_len(max_links) + 2;
    state->print.user_width = max_user + 1;
    // consider setting predefined vals for column padding
    return ;
}

// Remember to print the 'total' here as well.
static void long_display_setup(t_ls *state, t_list *files)
{
    get_usr_and_grp(state, files);
    get_field_widths(state, files);
    return ;
}

void    print_control(t_ls *state, t_list *files)
{
    const t_print_format    *print_format_handlers;
    t_list                  *iter;
    t_file_info             *current;
    void                    (*print_format_handler)(t_ls *, t_list *);

    if (!files)
        return ;
    if (state->options.display == LONG)
        long_display_setup(state, files);
    print_format_handlers = get_print_format_handlers();
    print_format_handler = print_format_handlers[state->options.display];
    iter = files;
    while (iter)
    {
        current = (t_file_info *) iter->content;
        if (file_should_be_printed(state, current->path))
            print_format_handler(state, iter);
        iter = iter->next;
    }
    state->print.print_newline = TRUE;
    return ;
}
