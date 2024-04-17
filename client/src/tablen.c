/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** tablen
*/

int tablen(char **tab)
{
    int i = 0;

    for (; tab[i]; i += 1);
    return i;
}
