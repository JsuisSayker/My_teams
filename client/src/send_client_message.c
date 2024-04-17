/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** send_client_message
*/

#include <stdio.h>
#include <unistd.h>

#include "client.h"
#include <unistd.h>

void send_client_message(client_t *client)
{
    if (client->is_logged == true &&
    strcmp(client->user_input->command, "/help") == 0)
        display_help();
    else
        write(client->socket_fd, client->user_input->command,
        strlen(client->user_input->command));
}
