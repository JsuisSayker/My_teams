/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** free
*/

#include "server.h"

void free_server_data(server_data_t *server_data)
{
    if (!server_data)
        return;
    if (server_data->server_socket != -1)
        close(server_data->server_socket);
    free(server_data);
}
