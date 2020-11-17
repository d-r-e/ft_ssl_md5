/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bits.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:48:28 by darodrig          #+#    #+#             */
/*   Updated: 2020/11/17 12:37:52 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

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

size_t	strbitlen(const char *s)
{
	return (ft_strlen(s) * 8);
}