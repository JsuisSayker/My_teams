/*
** EPITECH PROJECT, 2023
** Lib
** File description:
** tab_genetor
*/

#include <unistd.h>
#include <stdlib.h>

int tab_generator(char ***tab, int y, int x)
{
    if (tab == NULL)
        return -1;
    (*tab) = malloc(sizeof(char *) * y + 1);
    if ((*tab) == NULL)
        return -1;
    (*tab)[y] = NULL;
    for (int i = 0; (*tab)[i] != NULL; i += 1){
        (*tab)[i] = malloc(sizeof(char) * x + 1);
        if ((*tab)[i] == NULL)
            return -1;
        (*tab)[i][x] = '\0';
    }
    return 0;
}
