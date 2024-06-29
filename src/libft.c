/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 18:13:17 by darodrig          #+#    #+#             */
/*   Updated: 2024/06/22 20:57:24 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ssl.h"

int ft_strcmp(const char *s1, const char *s2){

    if (s1 == NULL || s2 == NULL)
        return 0;
    while (s1 && s2 && *s1 && *s2 && *s1 == *s2){
        s1++;
        s2++;
    }
    if (*s1 == '\0' && *s2 == '\0')
        return 0;
    return *s1 - *s2;
}


size_t ft_strlen(const char *s){
    size_t len;

    len = 0;
    while (s[len]){
        len++;
    }
    return len;
}

void ft_memset(void *b, int c, size_t len){
    unsigned char *ptr;

    ptr = (unsigned char *)b;
    while (len--){
        *ptr = (unsigned char)c;
        ptr++;
    }
}

void ft_memcpy(void *dst, const void *src, size_t len){
    unsigned char *d;
    unsigned char *s;

    d = (unsigned char *)dst;
    s = (unsigned char *)src;
    while (len--){
        *d = *s;
        d++;
        s++;
    }
}

const char *ft_strchr(const char *str, char c) {
    while (*str) {
        if (*str == c)
            return str;
        str++;
    }
    return NULL;
}
