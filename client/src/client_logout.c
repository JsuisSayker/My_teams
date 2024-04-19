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

void client_logout(client_t *client, char **command, char *message)
{
    printf("Je suis dans client_logout\n");
    if (client->is_logged == true) {
        client_event_logged_out(client->uuid, client->user_name);
        client->is_logged = false;
        close(client->socket_fd);
        free(client->user_input->params);
        free(client->user_input->command);
        free(client->user_input);
        free(client->user_name);
        free(client->uuid);
        free_tab(command);
        free(message);
        exit(0);
    }
}
