
#include "ft_ls.h"
#include "libft.h"

/*
int    ft_ls_recursion_control(t_ls *state, t_dir_info dir)
{
    construct_file_list(state, dir);
    sort_contorl(state);
    print_control(state);
    recursion_control(state, dir);
    return (TRUE);
}
*/

/*
int ft_ls_control(t_ls *state, char **argv)
{
    // filename_args_control will:
    // - validate paths in argv, printing any errors, adding files to one array and dirs to another
    // - sort the arrays based on sort option
    // - print names of normal files based on display option
    // - return the array of dirs
    dir_arr = filename_args_control(state, argv);
    int i = 0;
    while (dir_arr[i])
    {
        ft_ls_recursion_control(&state, dir_arr[i]);
        i++;
    }
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
        print_options_state_and_exit(state);
    /*
    ft_ls_control(&state, argv);
    */
    return (0);
}

