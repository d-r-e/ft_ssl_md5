#include "../inc/ft_ssl.h"

int ft_md5(const char *s)
{
    char *padded = NULL;

    padded = ft_strdup(s);
    if (padded)
        free(padded);
    return(0);
}