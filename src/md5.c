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

void init_md5_words(t_md5 *md5)
{
    md5->a = init_word_int(0x67452301);
    md5->b = init_word(0x89, 0xab, 0xcd, 0xef);
    md5->c = init_word(0xfe, 0xdc, 0xba, 0x98);
    md5->d = init_word(0x76, 0x54, 0x32, 0x10);
}

int ft_md5(const char *s)
{
    char *padded = NULL;
    t_md5 md5;

    init_md5_words(&md5);
    padded = ft_strdup(s);
    ft_putstr(padded);
    if (padded)
        free(padded);
    print_md5_hash(md5); 
    return(0);
}