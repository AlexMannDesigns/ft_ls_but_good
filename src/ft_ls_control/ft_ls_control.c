
#include "ft_ls.h"
#include <stdio.h>
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

void    free_file_info(void *file_info_content, size_t n)
{
    t_file_info *file_info;

    (void) n;
    file_info = (void *) file_info_content;
    if (file_info->command_line)
        ft_strdel(&(file_info->command_line));
    if (file_info->path)
        ft_strdel(&(file_info->path));
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


void add_node_to_list(t_list **list, char *filename, struct stat sys_file_info) 
{
    t_file_info file_info;
    t_list      *new_node;

    ft_bzero((void *) &file_info, sizeof(t_file_info));
    file_info.sys_file_info = sys_file_info;
    file_info.path = ft_strdup(filename);
    if (!file_info.path)
        print_malloc_error_and_exit();
    new_node = ft_lstnew((void *) &file_info, sizeof(t_file_info));
    if (!new_node)
        print_malloc_error_and_exit();
    if (!*list)
        *list = new_node;
    else
        ft_lstadd_back(list, new_node);
    return ;
}

/*
 * If there are no filenames passed in the command line args, we can just return 
 * the path to the current working directory
 */
void    no_filename_args(t_ls *state)
{
    char        *current_working_dir;
    struct stat sys_file_info;

    current_working_dir = getcwd(NULL, FALSE);
    if (!current_working_dir)
        print_malloc_error_and_exit();
    if (lstat(current_working_dir, &sys_file_info) != 0)
        print_stat_error_and_exit(); 
    add_node_to_list(&(state->directories), current_working_dir, sys_file_info);
    free(current_working_dir);
    return ;
}

void    add_invalid_arg(t_ls *state, char **argv, char *filename)
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
    print_stat_error_and_exit();
    exit(EXIT_FAILURE);
}

void    add_file_to_list(t_ls *state, char **argv)
{
    struct stat sys_file_info;
    char        *filename;
    t_list      **list;

    filename = argv[state->argv_index];
    if (lstat(filename, &sys_file_info) != 0)
        return (add_invalid_arg(state, argv, filename));
    if (get_file_type(sys_file_info.st_mode) == DIR)
        list = &(state->directories);
    else
        list = &(state->regular_files);
    add_node_to_list(list, filename, sys_file_info);
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
    // if argv[i] is null at this point, we use the current working dir as the 'default'
    if (!argv[state->argv_index])
        no_filename_args(state);
     
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
    // remember to free the arrays in the state struct
    // TODO create a cleanup function to free all memory allocations on exit
    if (state->directories)
        ft_lstdel(&(state->directories), free_file_info);
    if (state->regular_files)
        ft_lstdel(&(state->regular_files), free_file_info);
    // invalid_args freed in print_invalid_args()
    if (state->invalid_args)
        ft_free_char_array(&(state->invalid_args));
    // printf("%p %p %p\n", state->directories, state->regular_files, state->invalid_args);
}

