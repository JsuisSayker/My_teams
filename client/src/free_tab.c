/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** free_tab
*/

#include <stddef.h>
#include <stdlib.h>

void free_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i += 1)
        free(tab[i]);
    free(tab);
}
