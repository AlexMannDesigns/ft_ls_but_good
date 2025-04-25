#include "ft_ls.h"

void    number_of_links(t_print *print, unsigned long st_nlink)
{
    add_spaces_to_buf(print, (size_t) print->link_width - get_num_len(st_nlink));
    add_num_to_buf(print, st_nlink);
    return ;
}
