
#include "ft_ls.h"
#include "libft.h"

static int  arg_is_option_string(char *arg)
{
    return (!(arg[0] != '-' || ft_strequ(arg, "-")));
}

static int is_double_line(unsigned int *idx, char *arg)
{
    if (ft_strequ(arg, "--"))
    {
        (*idx)++;
        return (TRUE);
    }
    if (arg[0] == '-' && arg[1] == '-')
    {    
        print_unrecognized_option_error(arg);
        return (TRUE);
    }
    return (FALSE);
}

static void initialise_options(t_options *options)
{
    options->display = COLUMNS;
    options->sort = LEXICOGRAPHICAL;
    return ;
}

int options_control(t_ls *state, char **argv)
{
    char    *arg;
    unsigned int *idx;

    initialise_options(&(state->options));
    idx = &(state->argv_index);
    *idx = 1;
    while (argv[*idx])
    {
        arg = argv[*idx];
        if (!arg_is_option_string(arg) || is_double_line(idx, arg))
            break ;
        if (!set_options(&(state->options), arg))
            return (FALSE);
        (*idx)++;
    }
    return (TRUE);
}
