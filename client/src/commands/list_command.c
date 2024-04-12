/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** list_command
*/

#include "client.h"

int list_command(char *message, char **command, client_t *client)
{
    for (int i = 1; command[i]; i += 3)
        client_print_teams(command[i], command[i + 1], command[i + 2]);
    return OK;
}
