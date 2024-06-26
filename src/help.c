/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 18:13:17 by darodrig          #+#    #+#             */
/*   Updated: 2024/06/22 20:57:24 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void usage(const char **argv){
    const char *msg = ": [ -p -q -r -s] [..args]\n";

    write(1, argv[0], ft_strlen(argv[0]));
    write(1, msg, ft_strlen(msg));
}