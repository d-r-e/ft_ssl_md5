#include "../inc/ft_ssl.h"

t_word init_word(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
    t_word w = {.bit = {.b0 = d, .b1 = c, .b2 =b, .b3 = a}};
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
    ft_putstr(" ");
    print_dword(w.bit.b2);
    ft_putstr(" ");
    print_dword(w.bit.b1);
    ft_putstr(" ");
    print_dword(w.bit.b0);
    ft_putstr(" ");
}