/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** users_command
*/

#include "client.h"

int users_command(char *message, char **command, client_t *client)
{
    if (client->is_logged == false) {
        client_error_unauthorized();
        return KO;
    } else {
        client_print_users(command[2], command[1], CONNECTED);
        return OK;
    }
    return OK;
}
