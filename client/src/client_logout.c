/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** client_logout
*/

#include "client.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void client_logout(client_t *client, char *command)
{
    if ((strcmp(command, "/logout") == 0) && (client->is_logged == true)) {
        client_event_logged_out(client->uuid, client->user_name);
        close(client->socket_fd);
        free(client);
        exit(0);
    }
}