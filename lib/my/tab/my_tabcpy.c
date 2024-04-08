/*
** EPITECH PROJECT, 2023
** Minishell2
** File description:
** my_tabcpy
*/

#include <unistd.h>
#include <stdlib.h>

#include "proto_lib.h"

int my_tabcpy(char **src, char ***dest)
{
    int lenTab = 0;

    if (src == NULL)
        return -1;
    lenTab = my_tablen(src);
    if (lenTab == -1)
        return -1;
    (*dest) = malloc(sizeof(char *)* (lenTab + 1));
    if ((*dest) == NULL)
        return -1;
    (*dest)[lenTab] = NULL;
    for (int y = 0; src[y] != NULL; y += 1){
        if (my_strcpy(src[y], &(*dest)[y]) == -1)
            return -1;
    }
    return 0;
}
