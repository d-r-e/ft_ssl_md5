/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:55:34 by darodrig          #+#    #+#             */
/*   Updated: 2020/11/18 09:11:38 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void	ft_putstr(const char *s)
{
	write(1, s, ft_strlen(s));
}

void	ft_puts(const char *s)
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

	tmp = malloc((ft_strlen(s) + 2) * sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		tmp[i] = s[i];
		++i;
	}
	tmp[i] = c;
	tmp[i + 1] = '\0';
	ft_puts(tmp);
	free(s);
	ft_puts("END");
	s = tmp;
	return (s);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
