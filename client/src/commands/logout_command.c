/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** logout_command
*/

#include "client.h"

int logout_command(char *message, char **command, client_t *client)
{
    client_logout(client, command[0]);
    return OK;
}
