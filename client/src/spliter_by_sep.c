/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** spliter_by_sep
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char **spliter_by_sep(char *str, char *separator)
{
    int i = 0;
    char **tab = NULL;
    char *tmp_str = strtok(str, separator);

    if (tmp_str == NULL)
        return NULL;
    tab = malloc(sizeof(char *) * (strlen(str) + 1));
    if (tab == NULL)
        return NULL;
    while (tmp_str != NULL) {
        tab[i] = strdup(tmp_str);
        tmp_str = strtok(NULL, separator);
        i += 1;
    }
    tab[i] = NULL;
    return tab;
}
