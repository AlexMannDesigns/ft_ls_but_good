
#include "ft_ls.h"
#include "libft.h"

void print_valid_option_not_handled_error(char option)
{
    ft_putstr_fd("Error: All options checked, no match found for '", STDERR_FILENO);
    ft_putchar_fd(option, STDERR_FILENO);
    ft_putstr_fd("'\n", STDERR_FILENO);
    return ;
}

void    print_malloc_error_and_exit(void)
{
    ft_putendl_fd("Error: malloc failed, exiting...", STDERR_FILENO);
    exit(EXIT_FAILURE);
}
