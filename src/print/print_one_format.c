#include "ft_ls.h"

void    print_one_format(t_ls *state, t_list *files)
{
    t_list          *iter;
    t_file_info     *content;

    iter = files;
    while (iter)
    {
        content = (t_file_info *) iter->content;
        add_to_buf(&(state->print), content->path.str, content->path.len);
        add_nl_to_buf(&(state->print));
        iter = iter->next;
    }
    return ;
}
