
#ifndef FT_LS_H
# define FT_LS_H

/*** Defined values & enums ***/
    
# define TRUE 1
# define FALSE 0

# define OPTIONS "RSalmnrt1"
# define USAGE "usage: ./ft_ls [-RSalmnrt] [file ...]"


/*** Enums ***/

typedef enum e_display
{
    COLUMNS,
    LONG,
    COMMA,
    ONE,
}   t_display;

typedef enum e_sort
{
    LEXICOGRAPHICAL,
    TIME,
    SIZE,
}   t_sort;


/*** Structs ***/

typedef struct s_options
{
    t_display       display;
    t_sort          sort;
    unsigned int    reversed;
    unsigned int    recursive;
    unsigned int    all;
}   t_options;

typedef struct s_ls
{
    t_options       options;
    unsigned int    argv_index;
}                   t_ls;

/*** Typedefs ***/

typedef int (*t_option_handler)(t_options *, char);


/*** Functions ***/

/* OPTIONS */

/* options_control.c */
int options_control(t_ls *state, char **argv);

/* set_options.c */
int set_options(t_options *options, char *arg);

/* options_utils.c */
int  is_valid_option(char option);
int  set_option_value(unsigned int *option, int value);


/* ERROR */

/* print_error.c */
void print_options_error(char options);
void print_unrecognized_option_error(char *arg);

# endif
