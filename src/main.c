
#include "ft_ls.h"
#include "libft.h"


int main(int argc, char **argv)
{
    t_ls    state;

    (void) argc;
    ft_bzero(&state, sizeof(t_ls));
    options_control(&state, argv);
    print_options_state(state);
    return (0);
}

