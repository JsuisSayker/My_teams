/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <string.h>
#include "client.h"

int main(int ac, char const *const *av)
{
    if (!av)
        return KO;
    if (check_arguments(ac, av) == ERROR)
        return KO;
    if (strcmp(av[1], "-help") == 0)
        return display_help();
    return OK;
}
