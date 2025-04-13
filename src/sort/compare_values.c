#include "ft_ls.h"

// this should probably be moved to another file.
// we should make a sort directory, and put sorting related stuff in there.
// i.e. this file, the args sorting file, and functions for comparing values like this one
unsigned int    compare_values(t_options options, t_file_info *a, t_file_info *b)
{
    int cmp;

    (void) options;
    cmp = ft_strcmp(a->path, b->path);
    if (check_misc_option_bit(options.misc, REVERSED))
        return (cmp < 0);
    return (cmp > 0);
}
