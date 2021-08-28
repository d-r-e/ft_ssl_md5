#include "../inc/ft_ssl.h"

void put_md5(const char *file, const char *hash)
{
    if (file)
    {
        ft_putstr("MD5(");
        ft_putstr(file);
        ft_putstr(")= ");
    }
    ft_puts(hash);
}

int ft_md5(const char *s, const char *file)
{
    char *padded = NULL;

    padded = ft_strdup(s);
    put_md5(file, padded);
    if (padded)
        free(padded);
    return(0);
}