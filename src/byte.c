#include "../inc/ft_ssl.h"

t_word init_word(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
    t_word w = {.bit = {.b0 = a, .b1 = b, .b2 =c, .b3 = d}};
    return (w);
}

t_word init_word_int(int n)
{
    t_word w = {.i = n};
    return (w);
}

void print_dword(uint8_t n)
{
    char base[16]  ="0123456789abcdef";
    ft_putchar_fd(base[n / 16], 1);
    ft_putchar_fd(base[n % 16], 1);
}

void print_word(t_word w)
{
    print_dword(w.bit.b3);
    // ft_putstr(" ");
    print_dword(w.bit.b2);
    // ft_putstr(" ");
    print_dword(w.bit.b1);
    // ft_putstr(" ");
    print_dword(w.bit.b0);
    // ft_putstr(" ");
}

void print_block(t_block b)
{
    for (int i = 0; i < 16; ++i)
    {
        print_word(b.words[i]);
        ft_putstr(" ");
    }
    ft_puts("");
}

void print_md5_hash(t_md5 md5)
{
    print_word(md5.a);
    print_word(md5.b);
    print_word(md5.c);
    print_word(md5.d);
    ft_puts("");
}