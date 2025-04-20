#include "ft_ls.h"

static int  arg_is_options(char *arg)
{
    return (!(arg[0] != '-' || ft_strequ(arg, "-")));
}

static int is_double_line(size_t *index, char *arg)
{
    if (ft_strequ(arg, "--"))
    {
        (*index)++;
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
    char    *arg;
    size_t  *index;

    set_default_options(&(state->options));
    index = &(state->argv_index);
    *index = 1;
    while (argv[*index])
    {
        arg = argv[*index];
        if (!arg_is_options(arg) || is_double_line(index, arg))
            break ;
        if (!set_options_control(state, arg))
            return (FALSE);
        (*index)++;
    }
    return (TRUE);
}
