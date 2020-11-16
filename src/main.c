/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:19:47 by darodrig          #+#    #+#             */
/*   Updated: 2020/11/16 12:10:33 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

void read_stdin(void)
{
	int rd;
	char buff[2];

	buff[1] = 0;
	while ((rd = read(0, buff, 1)) > 0)
	{
		write(1, buff, 1);
	}
}


int	main(int argc, char **argv)
{
	if (argc == 1)
		read_stdin();
	if (argc == 2)
		ft_puts(argv[1]);
}
