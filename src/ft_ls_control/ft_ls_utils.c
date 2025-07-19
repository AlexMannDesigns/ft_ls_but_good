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
    ft_putendl_fd(ERROR_FILETYPE, STDERR_FILENO);
    exit(EXIT_FAILURE);
}

unsigned char   get_file_type_char(mode_t st_mode)
{
    unsigned int    type;

    type = get_file_type(st_mode);
    if (type == FIFO)
        return 'p';
    if (type == CHAR)
        return 'c';
    if (type == DIRECTORY)
        return 'd';
    if (type == BLOCK)
        return 'b';
    if (type == REGULAR)
        return '-';
    if (type == LINK)
        return 'l';
    if (type == SOCKET)
        return 's';
    if (type == WHITEOUT)
        return 'w';
    return '-';
}

t_file_info *format_recursion_path(t_file_info *dir_info, char *parent_path)
{
    char    *temp;
    char    *new_path;
    size_t  len;

    len = ft_strlen(parent_path);
    temp = ft_strnew(len + 1);
    if (!temp)
        print_malloc_error_and_exit();
    ft_strcpy(temp, parent_path);
    if (temp[len - 1] != '/')
        temp[len] = '/';
    else
        len -= 1;
    new_path = ft_strjoin(temp, dir_info->path.str);
    if (!new_path)
        print_malloc_error_and_exit();
    free(temp);
    free(dir_info->path.str);
    dir_info->path.str = new_path;
    dir_info->path.len = dir_info->path.len + len + 1;
    return (dir_info);
}
