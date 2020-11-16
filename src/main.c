/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 10:19:47 by darodrig          #+#    #+#             */
/*   Updated: 2020/11/16 12:32:11 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ssl.h"

char	*read_stdin(void)
{
	int		rd;
	char	buff[2];
	char	*str;

	str = ft_strdup("");
	buff[1] = 0;
	while ((rd = read(0, buff, 1)) > 0)
	{
		str = ft_append(str, *buff);
	}
	return (str);
}

int		main(int argc, char **argv)
{
	char *input;

	if (argc == 1)
	{
		input = read_stdin();
		ft_putstr(input);
		free(input);
	}
	if (argc == 2)
		ft_puts(argv[1]);
}
