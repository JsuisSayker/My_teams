/*
** EPITECH PROJECT, 2022
** my_strcpy
** File description:
** sauvegarder un mot dans une autre variable
*/

#include <unistd.h>
#include <stdlib.h>

#include "proto_lib.h"

int my_strcpy(char const *src, char **dest)
{
    int lenStr = 0;

    if (src == NULL)
        return -1;
    lenStr = my_strlen(src);
    if (lenStr == -1)
        return -1;
    (*dest) = malloc(sizeof(char) * (lenStr + 1));
    if ((*dest) == NULL)
        return -1;
    for (int i = 0; src[i] != '\0'; i += 1)
        (*dest)[i] = src[i];
    (*dest)[lenStr] = '\0';
    return 0;
}
