/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** receive_server_message
*/

#include "client.h"

void receive_server_message(client_t *client)
{
    char *buffer = read_server_message(client);

    if (buffer == NULL) {
        free(client->user_input->params);
        free(client->user_input);
        free(client->user_name);
        free(client->uuid);
        exit(0);
    }
    buffer[strlen(buffer)] = '\0';
    user_input_event(buffer, client);
}
