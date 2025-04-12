
#include "ft_ls.h"

unsigned int    get_file_type(mode_t st_mode)
{
    unsigned int    type;

    type = st_mode & S_IFMT;
    if (type == S_IFIFO)
        return FIFO;
    if (type == S_IFCHR)
        return CHAR;
    if (type == S_IFDIR)
        return DIRECTORY;
    if (type == S_IFBLK)
        return BLOCK;
    if (type == S_IFREG)
        return REGULAR;
    if (type == S_IFLNK)
        return LINK;
    if (type == S_IFSOCK)
        return SOCKET;
    if (type == S_IFWHT)
        return WHITEOUT;

    // unreachable code
    ft_putendl_fd("Error: could not find matching file-type, exiting...", STDERR_FILENO);
    exit(EXIT_FAILURE);
}

