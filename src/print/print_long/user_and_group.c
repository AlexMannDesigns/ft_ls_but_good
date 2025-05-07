#include "ft_ls.h"

void    user_and_group(t_print *print, t_file_info *file_info)
{
    add_spaces_to_buf(print, print->user_width - file_info->user_id_str.len);
    add_to_buf(print, file_info->user_id_str.str, file_info->user_id_str.len);
    add_spaces_to_buf(print, print->group_width - file_info->group_id_str.len);
    add_to_buf(print, file_info->group_id_str.str, file_info->group_id_str.len);
    return ;
}
