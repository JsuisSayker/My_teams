/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** subscribe_command
*/

#include "client.h"

int subscribe_command(char *message, char **command, client_t *client)
{
    if (handle_server_code(command) == KO)
        return KO;
    client_print_subscribed(command[2], command[3]);
    return OK;
}
