#include "ft_ls.h"

/*
 * If there are no filenames passed in the command line args, we can just add
 * the path to the current working directory to the dir list
 */
static void    no_filename_args(t_ls *state)
{
    char        *current_working_dir;
    struct stat sys_file_info;

    current_working_dir = getcwd(NULL, FALSE);
    if (!current_working_dir)
        print_malloc_error_and_exit();
    if (lstat(current_working_dir, &sys_file_info) != 0)
        print_stat_error_and_exit(current_working_dir); 
    add_node_to_list(&(state->directories), current_working_dir, sys_file_info);
    free(current_working_dir);
    return ;
}

/*
 * We do not need any extra data from the filesystem when handling invalid 
 * filenames in the argv, so we can just build a **char array here.
 */
static void    add_invalid_arg(t_ls *state, char **argv, char *filename)
{
    size_t  next_idx;
    size_t  remaining_argv_len;
    
    if (!(state->invalid_args))
    {
        remaining_argv_len = ft_array_len(argv + state->argv_index);
        state->invalid_args = (char **) ft_memalloc(sizeof(char *) * (remaining_argv_len + 1));
        if (!(state->invalid_args))
            print_malloc_error_and_exit();
    }
    next_idx = ft_array_len(state->invalid_args);
    state->invalid_args[next_idx] = ft_strdup(filename);
    if (!((state->invalid_args)[next_idx]))
        print_malloc_error_and_exit();
    return ;
}

static void    add_to_file_lists(t_ls *state, char *filename, struct stat sys_file_info)
{
    if (get_file_type(sys_file_info.st_mode) == DIRECTORY)
    {
        add_node_to_list(&(state->directories), filename, sys_file_info);
        return ;
    }
    add_node_to_list(&(state->regular_files), filename, sys_file_info);
    return ;
} 

/*
 * This function builds the lists and arrays from the argv arguments.
 * Invalid arguments (i.e. string does not match a path to a valid file 
 * on the system) are added to a **char array. Non-directories are put 
 * into a linked-list with their path and lstat info to be sorted and printed 
 * next. Finally, directories are put into another list to have their contents
 * printed at the end of the process.
*/
void    filename_args_control(t_ls *state, char **argv)
{
    struct stat     sys_file_info;
    char            *filename;

    if (!argv[state->argv_index])
    {
        no_filename_args(state);
        return ;
    }
    while (argv[state->argv_index])
    {
        filename = argv[state->argv_index];
        // TODO check permissions of path
        // Different error message is printed in event of no permissions for file
        // Sorting appears to be the same
        // directory permissions errors are handled downstream
        if (lstat(filename, &sys_file_info) != 0)
            add_invalid_arg(state, argv, filename);
        else 
            add_to_file_lists(state, filename, sys_file_info);
        (state->argv_index)++;
    }
    return ;
}
