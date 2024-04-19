/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** client_loop
*/

#include "client.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void free_client_struct(client_t *client, fd_set *readfds, fd_set *otherfds)
{
    client->user_input->command = strdup("/logout\a\n");
    send_client_message(client);
    receive_server_message(client);
    free(client->user_input->params);
    free(client->user_input->command);
    free(client->user_input);
    free(client->user_name);
    free(client->uuid);
    FD_CLR(client->socket_fd, readfds);
    FD_CLR(client->socket_fd, otherfds);
    FD_CLR(STDIN_FILENO, readfds);
    FD_CLR(STDIN_FILENO, otherfds);
}
