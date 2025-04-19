#include "ft_ls.h"

void    print_one_format(t_ls *state, t_list *current)
{
    t_file_info     *content;

    content = (t_file_info *) current->content;
    add_to_buf(state, content->path);
    add_to_buf(state, "\n");
    return ;
}
