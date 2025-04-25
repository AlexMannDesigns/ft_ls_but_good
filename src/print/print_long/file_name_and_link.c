#include "ft_ls.h"

void    file_name_and_link(t_print *print, t_file_info *file_info)
{
    add_to_buf_len(print, " ", 1);
    add_to_buf(print, file_info->path);
    add_to_buf(print, "\n");
    return ;
}
