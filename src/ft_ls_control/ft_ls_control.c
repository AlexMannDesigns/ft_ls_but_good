
#include "ft_ls.h"
#include "libft.h"

/*
int    ft_ls_recursion_control(t_ls *state, t_dir_info dir)
{
    construct_file_list(state, dir);
    sort_control(state);
    print_control(state);
    recursion_control(state, dir);
    return (TRUE);
}
*/

/*
    - validate paths in argv, adding files to one array, dirs to another and invalid paths to another
    - sort the arrays based on sort option
    - print errors for invalid paths (NB no linebreaks after each, including the last)
    - print names of normal files based on display option
    - loop through dirs in ft_ls_control()
    
    NB:
    - only print name of dir before contents (e.g. libft: ) if more than one filename is passed as arg (valid or not)
        - total_num_filename_args or similar should be set...? We need some way of deciding whether to print it 
        - furthermore, the 'title' printed of each dir appears to just be the path that was passed
            - (e.g. '~' expands to absolute path to HOME, "ls ../../foo bar" foo would not be changed to an absolute path)
            - with the -R option, if no file is specified, it refers to current dir as '.' i.e. './libft:' etc)
    - array index variables should be size_t, let's keep it consistent
    
    // consider the following set-up for this function:
    // allocate_filename_lists();
    // validate_filename_args();
    // sort_filename_lists();
    // print_invalid_filenames();
    // print_files();
    // directory_control();
    //
    // and then move the below loop to directory_control()
*/
void ft_ls_control(t_ls *state, char **argv)
{
    filename_args_control(state, argv);
    print_invalid_args(&(state->invalid_args));
    // sort lists here
    
    t_list      *current_node;
    t_file_info *current_file_info;


    current_node = state->regular_files;
    while (current_node)
    {
        current_file_info = (t_file_info *) current_node->content;
        ft_putendl(current_file_info->path);
        current_node = current_node->next;
        //ft_ls_recursion_control(&state, dir_arr[i]);
    }

    current_node = state->directories;
    while (current_node)
    {
        current_file_info = (t_file_info *) current_node->content;
        ft_putendl(current_file_info->path);
        current_node = current_node->next;
        //ft_ls_recursion_control(&state, dir_arr[i]);
    }
    cleanup_lists(state);
    // printf("%p %p %p\n", state->directories, state->regular_files, state->invalid_args);
}

