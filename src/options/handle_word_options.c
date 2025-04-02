#include "ft_ls.h"
#include "libft.h"

int handle_word_options(t_ls *state, char *arg)
{
    if (ft_strequ(arg, TEST))
    {
        state->testing = TRUE;
        return (TRUE);
    }
    print_unrecognized_option_error(arg);
    return (FALSE);
}
