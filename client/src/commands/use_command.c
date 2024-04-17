/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** use_command
*/

#include "client.h"

int use_command(char *message, char **command, client_t *client)
{
    if (tablen(command) > 4)
        perror("Too many arguments");
    return OK;
}
