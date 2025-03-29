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

int  set_option_value(unsigned int *option, unsigned int value)
{
    *option = value;
    return (TRUE);
}

int set_misc_option_bit(unsigned int *misc, unsigned int bit)
{
    *misc |= (1U << bit);
    return (TRUE);
}

int check_misc_option_bit(unsigned int misc, unsigned int bit)
{
    if (misc & (1u << bit))
        return (TRUE);
    return (FALSE);
}
