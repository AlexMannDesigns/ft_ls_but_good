
#include "ft_ls.h"
#include "libft.h"

int main(int argc, char **argv)
{
    t_ls    state;

    (void) argc;
    ft_bzero(&state, sizeof(t_ls));
    if (!options_control(&state, argv))
        return (1);
    if (state.testing)
        print_options_state_and_exit(state);
    ft_ls_control(&state, argv);
    return (0);
}

