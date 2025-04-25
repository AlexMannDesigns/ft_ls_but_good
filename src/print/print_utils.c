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

size_t  get_num_len(unsigned long num)
{
    size_t  len;

    len = 0;
    while (num)
    {
        num = num / 10;
        len++;
    }
    return (len);
}
