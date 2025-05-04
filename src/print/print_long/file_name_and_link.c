#include "ft_ls.h"

void    file_name_and_link(t_print *print, t_file_info *file_info)
{
    add_spaces_to_buf(print, 1);
    add_to_buf(print, file_info->path, file_info->path_len);
    if (get_file_type(file_info->sys_file_info.st_mode) == LINK)
    {
        add_to_buf(print, " -> ", 4);
        add_to_buf(print, file_info->link, file_info->link_len);
    }
    add_nl_to_buf(print);
    return ;
}
