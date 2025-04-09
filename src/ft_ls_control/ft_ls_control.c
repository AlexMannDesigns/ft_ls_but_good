
#include "ft_ls.h"
#include "libft.h"
#include <stdlib.h>

/*
int    ft_ls_recursion_control(t_ls *state, t_dir_info dir)
{
    construct_file_list(state, dir);
    sort_contorl(state);
    print_control(state);
    recursion_control(state, dir);
    return (TRUE);
}
*/

void    free_file_info(void *file_info_content, size_t file_info_size)
{
    t_file_info *file_info;

    file_info = (void *) file_info_content;
    if (file_info->command_line)
        ft_strdel(&(file_info->command_line));
    if (file_info->path)
        ft_strdel(&(file_info->path));
    ft_bzero((void *) file_info, file_info_size);
    return ;
}

void    print_stat_error_and_exit(void)
{
    ft_putendl_fd("Error: call to stat/lstat failed, exiting...", STDERR_FILENO); 
    exit(EXIT_FAILURE);
}

void    get_file_info(char *path, struct stat *stat)
{
    if (lstat(path, stat) != 0)
        print_stat_error_and_exit();
    return ;
}

/*
 * If there are no filenames passed in the command line args, we can just return 
 * the path to the current working directory
 */
void    no_filename_args(t_ls *state)
{
    char        *current_working_dir;
    t_file_info file_info; 

    current_working_dir = getcwd(NULL, FALSE);
    if (!current_working_dir)
        print_malloc_error_and_exit();

    // the below could probably be a separate function
    ft_bzero((void *) &file_info, sizeof(t_file_info));
    file_info.path = current_working_dir;
    get_file_info(current_working_dir, &file_info.file_info);
    //if (!(state->directories))
    state->directories = ft_lstnew((void *) &file_info, sizeof(t_file_info));
    if (!(state->directories))
        print_malloc_error_and_exit();
    //else ft_lstadd_back(state->directories...)...
    return ;
}

void    add_invalid_arg(t_ls *state, char **argv, char *filename)
{
    size_t next_idx;
    
    if (!(state->invalid_args))
    {
        state->invalid_args = (char **) ft_memalloc(sizeof(char *) * (ft_array_len(argv + state->argv_index) + 1));
        if (!(state->invalid_args))
            print_malloc_error_and_exit();
    }
    next_idx = ft_array_len(state->invalid_args);
    state->invalid_args[next_idx] = ft_strdup(filename);
    if (!((state->invalid_args)[next_idx]))
        print_malloc_error_and_exit();
    return ;
}

void    add_file_to_list(t_ls *state, char **argv)
{
    struct stat file_info;
    char        *filename;

    filename = argv[state->argv_index];
    if (lstat(filename, &file_info) != 0)
        add_invalid_arg(state, argv, filename);
    // check file type here
    return ;
}

void    filename_args_control(t_ls *state, char **argv)
{
    while (argv[state->argv_index])
    {
        add_file_to_list(state, argv);
        (state->argv_index)++;
    }
    return ;
}

void    print_invalid_args(char **invalid_args)
{
    size_t  i;

    if (!invalid_args)
        return ;
    i = 0;
    while (invalid_args[i])
    {
        ft_putstr_fd("ft_ls: ", STDERR_FILENO);
        ft_putstr_fd(invalid_args[i], STDERR_FILENO);
        ft_putendl_fd(": No such file or directory", STDERR_FILENO);
        i++;
    }
    return ;
}

/*
    - validate paths in argv, adding files to one array, dirs to another and invalid paths to another
    - sort the arrays based on sort option
    - print errors for invalid paths (NB no linebreaks after each, including the last)
    - print names of normal files based on display option
    - loop through dirs in ft_ls_control()
    
    NB:
    - only print name of dir before contents (e.g. libft: ) if more than one filename is passed as arg (valid or not)
        - total_num_filename_args or similar should be set...?
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
    // if argv[i] is null at this point, we use the current working dir as the 'default'
    if (!argv[state->argv_index])
        no_filename_args(state);
     
    filename_args_control(state, argv);
    
    print_invalid_args(state->invalid_args);

    t_list      *current_node;
    t_file_info *current_file_info;

    current_node = state->directories;
    while (current_node)
    {
        current_file_info = (t_file_info *) current_node->content;
        ft_putendl(current_file_info->path);
        current_node = current_node->next;
        //ft_ls_recursion_control(&state, dir_arr[i]);

    }
    // remember to free the arrays in the state struct
    // TODO create a cleanup function to free all memory allocations on exit
    if (state->directories)
        ft_lstdel(&(state->directories), free_file_info);
    if (state->regular_files)
        ft_lstdel(&(state->directories), free_file_info);
    if (state->invalid_args)
        ft_free_char_array(&(state->invalid_args));
}

