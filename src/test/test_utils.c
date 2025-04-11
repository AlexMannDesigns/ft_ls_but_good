#include "ft_ls.h"

unsigned int    check_testing(int argc, char **argv)
{
    if (argc < 2)
        return (FALSE);
    if (ft_strequ(argv[1], TEST))
        return (TRUE);
    return (FALSE);
}
