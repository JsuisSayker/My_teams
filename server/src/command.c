/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** comman
*/

#include "server.h"

int check_command(server_data_t *server_data, client_server_t *client)
{
    if (client->user_input[strlen(client->user_input) - 1] ==
    '\n' && client->user_input[strlen(client->user_input) - 2]
    == '\a') {
        client->user_input[strlen(client->user_input) - 2] =
        '\0';
        printf("command\n");
        write(client->socket, "/login toto|69ET", 17);
        free(client->user_input);
        client->user_input = NULL;
    }
}
