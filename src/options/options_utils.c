#include "ft_ls.h"
#include "libft.h"

int  is_valid_option(char option)
{
    if (!ft_strchr(OPTIONS, option))
    {
        print_options_error(option);
        return (FALSE);
    }
    return (TRUE);
}

int  set_option_value(unsigned int *option, int value)
{
    *option = value;
    return (TRUE);
}

