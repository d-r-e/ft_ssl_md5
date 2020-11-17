/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:20:24 by darodrig          #+#    #+#             */
/*   Updated: 2020/11/17 12:38:18 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct	s_md5
{
	__int128_t	val;
}				t_md5;

/*
** LIBFT
*/
void			ft_puts(const char *s);
void			ft_putstr(const char *s);
char			*ft_strdup(const char *s1);
size_t			ft_strlen(const char *s);
char			*ft_append(char *s, char c);
int				ft_strcmp(const char *s1, const char *s2);
/*
** MD5
*/
char			*ft_md5(const char *input);

/*
** Bit operations
*/
void			print_bin(__int128_t val);
size_t			strbitlen(const char *s);

#endif
