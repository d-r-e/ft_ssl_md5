/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 11:55:34 by darodrig          #+#    #+#             */
/*   Updated: 2020/11/18 12:17:05 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

uint64_t	ft_strlen(const char *s)
{
	uint64_t i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src && n > 0)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char*)dst)[i] = ((unsigned char*)src)[i];
		i++;
	}
	return ((unsigned char*)dst);
}

void	*ft_calloc(size_t count, size_t size)
{
	char *ptr;

	ptr = malloc(size * count);
	if (!ptr)
		return (ptr);
	ft_bzero(ptr, count * sizeof(size));
	return ((void*)ptr);
}

void	ft_bzero(void *s, size_t n)
{
	char *ptr;

	if (n == 0)
		return ;
	ptr = s;
	while (n > 0 && *ptr != '\0')
	{
		*ptr = 0;
		ptr++;
		n--;
	}
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		ft_putnbr(147483648);
	}
	else if (nb < 0)
	{
		ft_putchar('-');
		ft_putnbr(nb * (-1));
	}
	else
	{
		if (nb >= 10)
			ft_putnbr(nb / 10);
		ft_putchar((nb % 10) + '0');
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}