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

# include "../libft/libft.h"

typedef union byte {
    int i;
    struct {
        char a : 1;
		char b : 1;
		char c : 1;
		char d : 1;
    } bit;
} t_byte;

typedef struct s_word { t_byte bytes[4]; } t_word;

typedef struct s_md5
{
	char	*str;
	t_word	a;
	t_word	b;
	t_word	c;
	t_word	d;
}	t_md5;

int ft_md5(const char *s);

#endif
