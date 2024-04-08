/*
** EPITECH PROJECT, 2022
** my_strcat
** File description:
** rajoute le mot de 1 dans 2
*/

#include <unistd.h>
#include <stdlib.h>
#include "proto_lib.h"

static int alloc_tmp(char *dest, char const *src, char **tmp)
{
    int lenDest = 0;
    int lenSrc = 0;

    lenDest = my_strlen(dest);
    lenSrc = my_strlen(src);
    if (lenDest == -1 || lenSrc == -1)
        return -1;
    tmp = malloc(sizeof(char) * (lenDest + lenSrc) + 1);
    if (tmp == NULL)
        return -1;
    return 0;
}

char *my_strcat(char *dest, char const *src)
{
    int count = 0;
    char *tmp = NULL;

    if (dest == NULL || src == NULL)
        return NULL;
    if (alloc_tmp(dest, src, &tmp) == -1)
        return NULL;
    for (int i = 0; dest[i] != '\0'; i += 1){
        tmp[count] = dest[i];
        count += 1;
    }
    for (int i = 0; src[i] != '\0'; i += 1){
        tmp[count] = src[i];
        count += 1;
    }
    tmp[count] = '\0';
    return tmp;
}
