/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@42madrid.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:20:24 by darodrig          #+#    #+#             */
/*   Updated: 2021/08/28 20:10:18 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include "../libft/libft.h"

typedef union s_word {
    uint32_t i;
    struct {
        uint8_t b0 : 8;
		uint8_t b1 : 8;
		uint8_t b2 : 8;
		uint8_t b3 : 8;
    } bit;
} t_word;

typedef union s_block
{
	char	str[64];
	t_word	words[16];
} t_block;

typedef int (*command)(const char *s);

typedef struct s_ssl
{
	int p;
	int r;
	int s;
	int q;
	int md5;
	char	*str;
	char	*msg;
	char *input;
	char *file;
}	t_ssl;

typedef struct s_md5
{
	t_word a;
	t_word b;
	t_word c;
	t_word d;
	char *msg;
	t_block *blocks;
	uint64_t	len;
}	t_md5;

t_ssl g_ssl;

int		ft_append(char **buff, char c);
int		ft_md5(t_ssl ssl);
t_word	init_word(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
t_word	init_word_int(int n);
void	print_word(t_word w);
void	print_block(t_block b);
void	print_md5_hash(t_md5 md5);
#endif
