/*
** EPITECH PROJECT, 2023
** Minishell2
** File description:
** my_tablen
*/

#include <unistd.h>

int my_tablen(char **tab)
{
    int i = 0;

    if (tab == NULL)
        return -1;
    for (; tab[i] != NULL; i += 1);
    return i;
}
