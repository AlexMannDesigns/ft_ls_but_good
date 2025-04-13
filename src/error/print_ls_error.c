
#include "ft_ls.h"
#include <stdio.h>

void print_options_error(char option)
{
    ft_putstr_fd("ft_ls: invalid option -- ", STDERR_FILENO);
    ft_putchar_fd(option, STDERR_FILENO);
    ft_putchar_fd('\n', STDERR_FILENO);
    ft_putendl_fd(USAGE, STDERR_FILENO);
    return ;
}

void print_unrecognized_option_error(char *arg)
{
    ft_putstr_fd("ft_ls: unrecognized option `", STDERR_FILENO);
    ft_putstr_fd(arg, STDERR_FILENO);
    ft_putendl_fd("'", STDERR_FILENO);
    ft_putendl_fd(USAGE, STDERR_FILENO);
    return ;
}

/*
 * Some edge case handling needed for empty strings ("") in the commandline args
 * For some reason perror will not print a colon in this scenario.
*/
void    print_filename_error(char *filename)
{
    ft_putstr_fd("ft_ls: ", STDERR_FILENO);
    if (ft_strequ(filename, ""))
        ft_putstr_fd(": ", STDERR_FILENO);
    perror(filename);
    return ;
}
