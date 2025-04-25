#include "ft_ls.h"

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

void    add_spaces_to_buf(t_print *print, size_t spaces)
{
    while (spaces)
    {
        add_to_buf_len(print, " ", 1);
        spaces--;
    }
    return ;
}

void    add_num_to_buf(t_print *print, unsigned long num)
{
    char    num_str[2];

	if (num > 9)
	{
		add_num_to_buf(print, num / 10);
		add_num_to_buf(print, num % 10);
	}
	else
	{
        num_str[0] = (char) num + 48;
        num_str[1] = '\0';
		add_to_buf_len(print, num_str, 1);
	}
    return ;
}
