/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** logout_command
*/

#include "client.h"

int logout_command(char *message, char **command, client_t *client)
{
    if (handle_server_code(command) == KO)
        return KO;
    client_logout(client, command, message);
    return OK;
}
