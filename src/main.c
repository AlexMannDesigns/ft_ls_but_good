
#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

/*
int    ft_ls_control(t_ls *state, t_dir_info dir)
{
    construct_file_list(state, dir);
    sort_contorl(state);
    print_control(state);
    recursion_control(state, dir);
    return (TRUE);
}
*/

int main(int argc, char **argv)
{
    t_ls    state;

    (void) argc;
    ft_bzero(&state, sizeof(t_ls));
    if (!options_control(&state, argv))
        return (1);
    if (state.testing)
    {
        print_options_state(state);
        exit(EXIT_SUCCESS);
    }

    /*
    filenames_arr = filename_args_control(&state);
    int i = 0;
    while (filenames_arr[i])
    {
        ft_ls_control(&state, filenames_arr[i]);
        i++;
    }
    */
    return (0);
}

