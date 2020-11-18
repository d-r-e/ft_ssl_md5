/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:48:28 by darodrig          #+#    #+#             */
/*   Updated: 2020/11/18 12:17:43 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void	printbin(void *data, int len)
{
	int i;
	char *tmp;

	tmp = (char*)data;
	i = 0;
	while (i < len)
	{
		putcharbin((char)tmp[i]);
		if (i != len - 1)
			write(1, " ", 1);
		++i;
	}
}

void	putcharbin(unsigned char c)
{
	int i;
	unsigned char	bin[8];

	i = 7;
	while (i >= 0)
	{
		bin[i] = (c % 2) + '0';
		c = (c / 2);
		--i;
	}
	write(1, bin, 8);
}

void    print_bin(__int128_t val)
{
	char c;

	if (val <= 0)
	{
		write(1, "0", 1);
		return;
	}
	else if (val == 1)
	{
		write(1, "1", 1);
		return;
	}
	else if (val > 1)
	{
		c = val % 2 + '0';
		print_bin(val / 2);
		write(1, &c, 1);
	}
}

uint64_t	strbitlen(const char *s)
{
	return ((uint64_t)(ft_strlen(s) * 8));
}