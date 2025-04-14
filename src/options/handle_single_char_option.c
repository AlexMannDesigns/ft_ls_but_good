#include "ft_ls.h"

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
        return (set_misc_option_bit(&(options->misc), RECURSIVE));
    if (option == 'r')
        return (set_misc_option_bit(&(options->misc), REVERSED));
    if (option == 'a')
        return (set_misc_option_bit(&(options->misc), ALL));
    
    // Unreachable code
    print_valid_option_not_handled_error(option);
    exit(EXIT_FAILURE);
}

static const t_option_handler *get_option_handlers(void)
{
    static const t_option_handler dispatch_table[] = {
        set_display,
        set_sort,
        set_misc,
        NULL
    };
    return (dispatch_table);
}

void    handle_single_char_option(t_options *options, char option)
{
    const t_option_handler  *handlers;
    int                     i;
    
    handlers = get_option_handlers();
    i = 0;
    while (handlers[i])
    {
        if (handlers[i](options, option))
            break ;
        i++;
    }
    return ;
}
