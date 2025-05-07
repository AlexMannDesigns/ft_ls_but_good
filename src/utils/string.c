#include "ft_ls.h"

t_string    create_string(char *str, size_t len)
{
    t_string    string;

    if (str == NULL)
        exit(EXIT_FAILURE); // handle this properly...
    if (len == 0)
        string.len = ft_strlen(str);
    else
        string.len = len;
    string.str = (char *) malloc((string.len + 1) * sizeof(char));
    if (!string.str)
        print_malloc_error_and_exit();
    ft_strcpy(string.str, str);
    return (string);
}
