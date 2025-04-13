#include "ft_ls.h"

int file_should_be_printed(t_options options, char *path)
{
    if (check_misc_option_bit(options.misc, ALL))
        return (TRUE);
    if (path[0] == '.')
        return (FALSE);
    return (TRUE);
}

void    print_control(t_ls *state, t_list *files)
{
    t_list      *iter;
    t_file_info *current;

    if (!files)
        return ;
    iter = files;
    while (iter)
    {
        current = (t_file_info *) iter->content;
        if (file_should_be_printed(state->options, current->path))
            ft_putendl(current->path);
        iter = iter->next;
    }
    state->print_newline = TRUE;
    return ;
}
