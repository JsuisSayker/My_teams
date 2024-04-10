/*
** EPITECH PROJECT, 2023
** main
** File description:
** main
*/

#include <unistd.h>
#include <string.h>
#include "server.h"

int main(int ac, char *const *const av)
{
    if (!av)
        return KO;
    if (ac != 2) {
        write(1, "bad usage of ./myteams_server\n", 31);
        display_help();
        return KO;
    }
    if (strcmp(av[1], "-help") == 0)
        return display_help();
    return OK;
}
