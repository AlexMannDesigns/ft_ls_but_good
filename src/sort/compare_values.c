#include "ft_ls.h"

// this should probably be moved to another file.
// we should make a sort directory, and put sorting related stuff in there.
// i.e. this file, the args sorting file, and functions for comparing values like this one
// NB the man for notes on lexicographical fall-back sorting in the case of
// time.
unsigned int    compare_values(t_options options, t_file_info *a, t_file_info *b)
{
    int cmp;
    int time_a;
    int time_b;

    if (options.sort == LEXICOGRAPHICAL)
        cmp = ft_strcmp(a->path, b->path);
    else if (options.sort == TIME)
    {
        time_a = (int) a->sys_file_info.st_mtimespec.tv_sec;
        time_b = (int) b->sys_file_info.st_mtimespec.tv_sec;
        cmp = time_b - time_a;
        if (cmp == 0)
            cmp = ft_strcmp(a->path, b->path);
    }
    if (check_misc_option_bit(options.misc, REVERSED))
        return (cmp < 0);
    return (cmp > 0);
}
