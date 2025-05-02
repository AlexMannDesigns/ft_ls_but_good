#include "ft_ls.h"
#include <sys/ioctl.h>

typedef struct s_string_with_length
{
    char    *str;
    size_t  len;
}           t_string_with_length;

t_string_with_length    *allocate_file_names_arr(size_t len)
{
    t_string_with_length *file_names;

    file_names = (t_string_with_length *) malloc(sizeof(t_string_with_length) * len);
    if (!file_names)
        print_malloc_error_and_exit();
    return (file_names);
}

size_t  get_term_width(void)
{
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return ((size_t) w.ws_col);
}

void    print_filename_column(t_print *print, t_string_with_length filename, size_t width)
{
    add_to_buf_len(print, filename.str, filename.len);
    add_spaces_to_buf(print, width - filename.len);
    return ;
}

void    calculate_cols_and_rows(t_print *print, size_t max_len)
{
    // calculate num cols
    print->col_width = max_len + 1;
    print->num_cols = (size_t) (get_term_width() / print->col_width);
    if (print->num_cols == 0)
        print->num_cols = 1;

    // calc rows
    // this is the same as ciel(list_len / num_cols)
    print->rows = (size_t) ((print->list_len + print->num_cols - 1) / print->num_cols);
    return ;
}

void    print_columns(t_print *print, t_string_with_length *file_names)
{
    size_t row;
    size_t col;
    size_t index;

    row = 0;
    while (row < print->rows)
    {
        col = 0;
        while (col < print->num_cols)
        {
            index = row + col * print->rows;
            if (index < print->list_len)
                print_filename_column(print, file_names[index], print->col_width);
            col++;
        }
        add_to_buf_len(print, "\n", 1);
        row++;
    }
    return ;
}

size_t  get_max_len_and_populate_file_names(t_list *files, t_string_with_length *file_names)
{
    t_list      *iter;
    t_file_info *current;
    size_t      i;
    size_t      max_len;

    max_len = 0;
    i = 0;
    iter = files;
    while (iter)
    {
        current = (t_file_info *) iter->content;
        current->path_len = ft_strlen(current->path);
        if (current->path_len > max_len)
            max_len = current->path_len;
        file_names[i].str = current->path;
        file_names[i].len = current->path_len;
        i++;
        iter = iter->next;
    }
    return (max_len);
}

// so for this format, the linked list is an issue, as we will have to scan the
// list each time we print a file name to find the relevant node
// However, we will need to scan the list before printing anyway, to determine
// the column width (i.e. find the longest file name). While we do that, we
// should just copy the path pointer into a char array, which we can then just
// index into as we print.
// We can use the list_len var to malloc an array of pointers to the filenames
// from the linked list.
void    print_columns_format(t_ls *state, t_list *files)
{
    t_string_with_length    *file_names;
    size_t                  max_len;

    file_names = allocate_file_names_arr(state->print.list_len);
    max_len = get_max_len_and_populate_file_names(files, file_names);
    calculate_cols_and_rows(&(state->print), max_len);
    print_columns(&(state->print), file_names);
    free(file_names);
    state->print.print_newline = TRUE;
    return ;
}
