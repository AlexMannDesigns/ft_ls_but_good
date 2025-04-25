#include "ft_ls.h"
#include <time.h>

void    date_and_time(t_print *print, time_t modified)
{
    time_t  now;
    char    *time_str;
    char    time_sub_str[13];
    char    year[5];

    time(&now);
    time_str = ctime(&modified);
    if (now - modified < SIX_MONTHS_IN_SECONDS && now >= modified)
    {
        ft_memcpy((void *) time_sub_str, (void *) time_str + 4, 12);
        add_spaces_to_buf(print, 1);
        add_to_buf_len(print, time_sub_str, 12);
        return ;
    }
    ft_memcpy((void *) time_sub_str, (void *) time_str + 4, 7);
    ft_memcpy((void *) year, (void *) time_str + 20, 4);
    add_spaces_to_buf(print, 1);
    add_to_buf_len(print, time_sub_str, 12);
    add_spaces_to_buf(print, 1);
    add_to_buf_len(print, year, 4);
    return ;
}
