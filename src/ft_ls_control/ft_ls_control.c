
#include "ft_ls.h"
#include <stdio.h>

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

void    print_node_list(t_list *list)
{
    t_file_info *current;

    ft_putstr("[ ");
    while (list)
    {
        current = list->content;
        ft_putstr(current->path);
        ft_putstr(", ");
        list = list->next;
    }
    ft_putendl("]");
    return ;
}



unsigned int    check_swap_is_needed(t_options options, t_file_info *a, t_file_info *b)
{
    if (options.sort == LEXICOGRAPHICAL)
    {
        if (check_misc_option_bit(options.misc, REVERSED))
            return (ft_strcmp(a->path, b->path) < 0);
        else
            return (ft_strcmp(a->path, b->path) > 0);
    }
    return (FALSE);
}

void    swap_nodes(unsigned int *swapped, t_list *previous, t_list *current, t_list *next)
{
    t_list  *temp;

    *swapped = TRUE;
    temp = next->next;
    previous->next = next;
    next->next = current;
    current->next = temp;
    return ;
}

/*
 * A simple bubble sort is used. The intention is to minimize code repetition
 * as much as possible, so we use the same list type and sorting process
 * across the program.
 *
 * temp = b
 *
 *  d   c   b   a
 *
 */
void    sort_node_list(t_options options, t_list *list)
{
    t_list          *head;
    t_list          *current;
    t_list          *next;
    t_list          *previous;
    unsigned int    swapped;

    swapped = FALSE;
    head = list;
    previous = list;
    while (list->next)
    {
        current = list;
        next = list->next;
        print_node_list(head);
        printf("%p %p\n", current, next);
        if (check_swap_is_needed(options, current->content, next->content))
        {
            swap_nodes(&swapped, previous, current, next);
        }
        previous = current;
        list = list->next;
    }
    list = head;
    if (swapped)
        sort_node_list(options, list);
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
    
*/
void ft_ls_control(t_ls *state, char **argv)
{
    filename_args_control(state, argv);
    print_invalid_args(&(state->invalid_args));
    // sort lists here
    // if (state->regular_files)
    //     sort_node_list(state->options, state->regular_files);
    // if (state->directories)
    //     sort_node_list(state->options, state->directories);
    
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

