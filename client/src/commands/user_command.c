/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** user_command
*/

#include "client.h"

int user_command(char *message, char **command, client_t *client)
{
    if (handle_server_code(command) == KO)
        return KO;
    if (strcmp(command[4], "1") == OK)
        client_print_user(command[3], command[2], CONNECTED);
    else
        client_print_user(command[3], command[2], DISCONNECTED);
    return OK;
}
