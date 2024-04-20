/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** unsubscribe_command
*/

#include "client.h"

int unsubscribe_command(char *message, char **command, client_t *client)
{
    if (client->is_logged == false) {
        client_error_unauthorized();
        return KO;
    }
    client_print_unsubscribed(command[2], command[3]);
    return OK;
}
