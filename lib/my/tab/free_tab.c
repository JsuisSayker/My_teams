/*
** EPITECH PROJECT, 2023
** SBMLParser
** File description:
** free_tab
*/

#include <unistd.h>
#include <stdlib.h>

void free_tab(char **tab)
{
    if (!tab)
        return;
    for (int i = 0; tab[i] != NULL; i ++){
        free(tab[i]);
    }
    free(tab);
    return;
}
