/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:55:34 by darodrig          #+#    #+#             */
/*   Updated: 2020/11/16 12:21:28 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr(const char *s)
{
	write(1, s, ft_strlen(s));
}

void    ft_puts(const char *s)
{
    write(1, s, ft_strlen(s));
    write(1, "\n", 1);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;
	int		len;

	len = 0;
	while (s1[len])
		len++;
	if (!(s2 = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_append(char *s, char c)
{
	char	*tmp;
	size_t	i;

	tmp = malloc(ft_strlen(s) + 2);
	i = 0;
	while (i < ft_strlen(s))
	{
		tmp[i] = s[i];
		++i;
	}
	tmp[i] = c;
	tmp[i + 1] = 0;
	free(s);
	s = tmp;
	return s;

}