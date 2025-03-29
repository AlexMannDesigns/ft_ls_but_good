
#include "ft_ls.h"
#include "libft.h"
#include <assert.h>
#include <stdlib.h>

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
    // We should never get here
    ft_putstr_fd("Error: All options checked, no match found\n", STDERR_FILENO);
    assert(FALSE);
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

int set_options(t_options *options, char *arg)
{
    const t_option_handler  *handlers;
    int                     i;
    size_t                  j;
    char                    option;

    handlers = get_option_handlers();
    i = 1;
    while (arg[i])
    {
        option = arg[i];
        if (!is_valid_option(option))
            return (FALSE);
        j = 0;
        while (handlers[j])
        {
            if (handlers[j](options, option))
                break ;
            j++;
        }
        i++;
    }
    return (TRUE);
}
