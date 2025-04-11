
#include "ft_ls.h"

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
