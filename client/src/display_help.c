/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** display_help
*/

#include <unistd.h>
#include "macro.h"

int display_help(void)
{
    if (write(1, "USAGE: ./myteams_cli ip port\n\n\
    ip is the server ip address on which the server socket listens\n\
    port is the port number on which the server socket listens\n", 161) == -1)
        return KO;
    return OK;
}
