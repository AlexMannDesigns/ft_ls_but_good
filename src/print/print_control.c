#include "ft_ls.h"

// This should be a generic function for printing out files, either from
// the command line or from the contents of a directory 
// 
// Line breaks:
// each directory or the file args have a line break printed after them, except the last
// The best way to handle this may be to print a line break every time this function is called
// before the files (and title) are printed, except the first time it's called. e.g. put a var
// in the state struct.
//
// Titles (e.g. "libft:\n" being printed before the contents of libft):
// If there is one filename arg then no title is printed
// If there are multiple filename args (even if invalid) no title is printed
// This can probably also be handled with a var in the state struct.
void    print_control(t_options options, t_list *files)
{
    t_list      *iter;
    t_file_info *current_file_info;

    (void) options;
    iter = files;
    while (iter)
    {
        current_file_info = (t_file_info *) iter->content;
        ft_putendl(current_file_info->path);
        iter = iter->next;
    }
    return ;
}
