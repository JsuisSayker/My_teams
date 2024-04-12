/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** user_command
*/

#include "client.h"

int user_command(char *message, char **command, client_t *client)
{
    if (client->is_logged == false) {
        client_error_unauthorized();
        return KO;
    } else {
        client_print_user(command[1], command[2], CONNECTED);
        return OK;
    }
    return OK;
}
