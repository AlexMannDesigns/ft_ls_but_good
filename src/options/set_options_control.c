
#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

static int arg_is_word_option(char *arg)
{
    if (ft_strlen(arg) > 2 && arg[0] == '-' && arg[1] == '-')
        return (TRUE);
    return (FALSE);
}

static int  is_valid_option(char option)
{
    if (!ft_strchr(OPTIONS, option))
    {
        print_options_error(option);
        return (FALSE);
    }
    return (TRUE);
}

int set_options_control(t_ls *state, char *arg)
{
    char    option;
    int     i;

    if (arg_is_word_option(arg))
        return (handle_word_options(state, arg));
    i = 1;
    while (arg[i])
    {
        option = arg[i];
        if (!is_valid_option(option))
            return (FALSE);
        handle_single_char_option(&(state->options), option);
        i++;
    }
    return (TRUE);
}
