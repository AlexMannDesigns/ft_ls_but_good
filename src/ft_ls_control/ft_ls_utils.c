
#include "ft_ls.h"

unsigned int    get_file_type(mode_t st_mode)
{
    unsigned int    type;

    type = st_mode & S_IFMT;
    if (type == S_IFIFO)
        return FFO;
    if (type == S_IFCHR)
        return CHR;
    if (type == S_IFDIR)
        return DIR;
    if (type == S_IFBLK)
        return BLK;
    if (type == S_IFREG)
        return REG;
    if (type == S_IFLNK)
        return LNK;
    if (type == S_IFSOCK)
        return SOK;
    if (type == S_IFWHT)
        return WHT;

    // unreachable code
    ft_putendl_fd("Error: could not find matching file-type, exiting...", STDERR_FILENO);
    exit(EXIT_FAILURE);
}

