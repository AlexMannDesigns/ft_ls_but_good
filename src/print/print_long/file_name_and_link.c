#include "ft_ls.h"

void    file_name_and_link(t_print *print, t_file_info *file_info)
{
    add_spaces_to_buf(print, 1);
    add_to_buf(print, file_info->path.str, file_info->path.len);
    if (get_file_type(file_info->sys_file_info.st_mode) == LINK)
    {
        add_to_buf(print, " -> ", 4);
        add_to_buf(print, file_info->link.str, file_info->link.len);
    }
    add_nl_to_buf(print);
    return ;
}
