/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** send_client_message
*/

#include "client.h"

void send_client_message(client_t *client)
{
    if (strcmp(client->user_input->command, "") == 0)
        perror("Error: no message to send\n");

    if ((client->is_logged == false &&
    strcmp(client->user_input->command, "/login") != 0) && (client->is_logged
    == false && strcmp(client->user_input->command, "/help") != 0))
        client_error_unauthorized();
    else if (client->is_logged == true &&
    strcmp(client->user_input->command, "/login") == true) {
        client_error_already_exist();
        return;
    }
    if (client->is_logged ==true &&
    strcmp(client->user_input->command, "/help"))
        display_help();
    else
        write(client->socket_fd, &client->user_input, sizeof(client->user_input));
}
