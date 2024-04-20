/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** use_command
*/

#include "client.h"

int use_command(char *message, char **command, client_t *client)
{
    int len = 0;

    if (client->is_logged == false) {
        client_error_unauthorized();
        return KO;
    }
    if (message == NULL || command == NULL || client == NULL)
        return ERROR;
    len = my_tablen(command);
    if (len == ERROR)
        return ERROR;
    if (len > 4)
        return KO;
    return OK;
}
