#include "ft_ls.h"

/*
 * If there are no filenames passed in the command line args, we can just add
 * the path to the current working directory to the dir list
 */
static void    no_filename_args(t_ls *state)
{
    struct stat sys_file_info;

    if (lstat("./", &sys_file_info) != 0)
    {
        print_filename_error("./"); 
        return ;
    }
    add_node_to_list(&(state->directories), "./", sys_file_info);
    return ;
}

static char **copy_and_sort_remaining_argv(t_ls *state, char **argv)
{
    char    **filename_args;
    size_t  i;
    
    state->remaining_argv_len = ft_array_len(argv + state->argv_index);
    filename_args = (char **) ft_memalloc(sizeof(char *) * (state->remaining_argv_len + 1));
    if (!filename_args)
        print_malloc_error_and_exit();
    i = 0;
    while (argv[state->argv_index + i])
    {
        filename_args[i] = ft_strdup(argv[state->argv_index + i]);
        if (!(filename_args[i]))
            print_malloc_error_and_exit();
        i++;
    }
    sort_filename_args(filename_args);
    return (filename_args);
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
 * This function cycles through the remaining argv which are interpreted
 * as filenames. We copy the argv to an array and sort it into lexicographical
 * order. We then cycle through it and build two linked lists, one for
 * directories and one for other files. Error messages for invalid args
 * are printed during this process.
*/
void    filename_args_control(t_ls *state, char **argv)
{
    struct stat     sys_file_info;
    char            **sorted_filename_args;
    char            *filename;
    size_t          i;

    if (!argv[state->argv_index])
    {
        no_filename_args(state);
        return ;
    }
    sorted_filename_args = copy_and_sort_remaining_argv(state, argv);
    i = 0;
    while (sorted_filename_args[i])
    {
        filename = sorted_filename_args[i];
        if (lstat(filename, &sys_file_info) != 0)
            print_filename_error(filename);
        else 
            add_to_file_lists(state, filename, sys_file_info);
        i++;
    }
    ft_free_char_array(&sorted_filename_args);
    return ;
}
