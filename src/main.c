#include "ft_ls.h"

static void setup_state(t_ls *state)
{
    ft_bzero(state, sizeof(t_ls));
    state->print.print_buf = (char *) malloc(BUF_SIZE * sizeof(char));
    if (!(state->print.print_buf))
        print_malloc_error_and_exit();
    return ;
}

int main(int argc, char **argv)
{
    t_ls    state;

    (void) argc;
    setup_state(&state);
    if (!options_control(&state, argv))
        return (1);
    if (state.testing)
        print_options_state_and_exit(state);
    ft_ls_control(&state, argv);
    return (0);
}

