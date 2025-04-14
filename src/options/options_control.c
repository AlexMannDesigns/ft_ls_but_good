#include "ft_ls.h"

static int  arg_is_options(char *arg)
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
    return (FALSE);
}

static void set_default_options(t_options *options)
{
    options->display = COLUMNS;
    options->sort = LEXICOGRAPHICAL;
    return ;
}

int options_control(t_ls *state, char **argv)
{
    char            *arg;
    unsigned int    *idx;

    set_default_options(&(state->options));
    idx = &(state->argv_index);
    *idx = 1;
    while (argv[*idx])
    {
        arg = argv[*idx];
        if (!arg_is_options(arg) || is_double_line(idx, arg))
            break ;
        if (!set_options_control(state, arg))
            return (FALSE);
        (*idx)++;
    }
    return (TRUE);
}
