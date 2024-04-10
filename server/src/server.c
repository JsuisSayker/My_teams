/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** server
*/

#include "server.h"

int launch_server(char *const *const av)
{
    server_data_t *server_data = malloc(sizeof(server_data_t));

    if (!av || !server_data)
        return KO;
    server_data->server_socket = create_server_socket(av, server_data);
    if (server_data->server_socket == - 1) {
        free_server_data(server_data);
        return KO;
    }
    free_server_data(server_data);
    return OK;
}
