#include "ft_ls.h"

void    file_size(t_print *print, unsigned long st_size)
{
    add_spaces_to_buf(print, (size_t) print->size_width - get_num_len(st_size));
    add_num_to_buf(print, st_size);
    return ;
}
