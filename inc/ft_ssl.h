/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:20:24 by darodrig          #+#    #+#             */
/*   Updated: 2020/11/19 08:44:58 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
typedef struct	s_md5
{
	char		*msg;
	uint64_t	len0;
	uint8_t		*padded;
	uint64_t	len1;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
}				t_md5;

/*
** LIBFT
*/
void			ft_puts(const char *s);
void			ft_putstr(const char *s);
char			*ft_strdup(const char *s1);
uint64_t		ft_strlen(const char *s);
char			*ft_append(char *s, char c);
int				ft_strcmp(const char *s1, const char *s2);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			ft_bzero(void *s, size_t n);
void			ft_putnbr(int nb);
void			ft_putchar(char c);
/*
** MD5
*/

void			step12(t_md5	*md5);
char			*ft_md5(const char *input);
void			test_md5(const char *msg);

/*
** Bit operations
*/
void			printbin(void *data, int len);
void			print_bin(__int128_t val);
void			putcharbin(unsigned char c);
uint64_t		strbitlen(const char *s);



#endif
