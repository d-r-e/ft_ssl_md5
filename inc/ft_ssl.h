/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:20:24 by darodrig          #+#    #+#             */
/*   Updated: 2020/11/16 12:43:37 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

/*
** LIBFT
*/
void	ft_puts(const char *s);
void	ft_putstr(const char *s);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_append(char *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
/*
** MD5
*/
char	*ft_md5(const char *input);

#endif
