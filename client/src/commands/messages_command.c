/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** messages_command
*/

#include "client.h"

int messages_command(char *message, char **command, client_t *client)
{
    client_event_private_message_received(command[1], command[2]);
    return OK;
}
