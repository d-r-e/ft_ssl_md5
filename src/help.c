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
    dprintf(2,"%s: %s\n", argv[0], ": [ -p -q -r -s] [..args]\n");
}