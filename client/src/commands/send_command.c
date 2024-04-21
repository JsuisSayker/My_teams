/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** send_command
*/

#include "client.h"

int send_command(char *message, char **command, client_t *client)
{
    if (handle_server_code(command) == KO)
        return KO;
    client_event_private_message_received(command[2], command[3]);
    return OK;
}
