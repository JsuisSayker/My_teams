/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** help_command
*/

#include "client.h"
#include <unistd.h>

int help_command(char *message, char **command, client_t *client)
{
    if (client->is_logged == false) {
        client_error_unauthorized();
        return KO;
    }
    for (int i = 2; command[i] != NULL; i += 1)
        write(1, command[i], strlen(command[i]));
    return OK;
}