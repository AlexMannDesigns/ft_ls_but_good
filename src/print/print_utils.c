#include "ft_ls.h"

int file_should_be_printed(t_ls *state, char *path)
{
    unsigned int    print_all;

    print_all = check_misc_option_bit(state->options.misc, ALL);
    if (print_all || state->print.printing_file_args)
        return (TRUE);
    if (path[0] == '.')
        return (FALSE);
    return (TRUE);
}

void    flush_buf(t_print *print)
{
    write(STDOUT_FILENO, print->print_buf, print->buf_index);
    print->buf_index = 0;
    return ;
}

void    add_to_buf(t_print *print, char *str)
{
    size_t  len;

    len = ft_strlen(str);
    if (print->buf_index + len + 1 >= BUF_SIZE)
        flush_buf(print);
    ft_memcpy(print->print_buf + print->buf_index, str, len);
    print->buf_index += len;
    return ;
}

void    add_to_buf_len(t_print *print, char *str, size_t len)
{
    if (print->buf_index + len + 1 >= BUF_SIZE)
        flush_buf(print);
    ft_memcpy(print->print_buf + print->buf_index, str, len);
    print->buf_index += len;
    return ;
}
