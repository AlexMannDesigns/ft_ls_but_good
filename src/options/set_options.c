
#include "ft_ls.h"
#include "libft.h"

static int  is_valid_option(char option)
{
    if (!ft_strchr(OPTIONS, option))
    {
        print_options_error(option);
        return (FALSE);
    }
    return (TRUE);
}

static int  set_option_value(unsigned int *option, int value)
{
    *option = value;
    return (TRUE);
}

static int set_display(t_options *options, char option)
{
    if (option == 'l' || option == 'n')
        return (set_option_value(&(options->display), LONG));
    if (option == '1')
        return (set_option_value(&(options->display), ONE));
    if (option == 'm')
        return (set_option_value(&(options->display), COMMA));
    return (FALSE);
}

static int set_sort(t_options *options, char option)
{
    if (option == 't')
        return (set_option_value(&(options->sort), TIME));
    if (option == 'S')
        return (set_option_value(&(options->sort), SIZE));
    return (FALSE);
}

static int set_misc(t_options *options, char option)
{
    if (option == 'R')
        return (set_option_value(&(options->recursive), TRUE));
    if (option == 'r')
        return (set_option_value(&(options->reversed), TRUE));
    if (option == 'a')
        return (set_option_value(&(options->all), TRUE));
    return (FALSE);
}

int set_options(t_options *options, char *arg)
{
    int     i;
    char    option;

    i = 1;
    while (arg[i])
    {
        option = arg[i];
        if (!is_valid_option(option))
            return (FALSE);
        if (set_display(options, option))
             ;
        else if (set_sort(options, option))
             ;
        else if (set_misc(options, option))
             ;
        i++;
    }
    return (TRUE);
}
