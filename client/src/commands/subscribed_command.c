/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** subscribed_command
*/

#include "client.h"

int subscribed_command(char *message, char **command, client_t *client)
{
    if (client->is_logged == false) {
        client_error_unauthorized();
        return KO;
    }
    return OK;
}
