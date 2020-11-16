/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:32:35 by darodrig          #+#    #+#             */
/*   Updated: 2020/11/16 12:37:36 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

/*
** This is the main MD% algorithm.
** input: string to convert
** output: 128 bit hash, null-terminated
*/

char	*ft_md5(const char *input)
{
	char hash[33];

	hash[32] = 0;
	return (hash);
}
