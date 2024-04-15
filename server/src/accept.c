/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** accept
*/

#include "server.h"

int accept_client(server_data_t *data)
{
    client_server_t *new_client = malloc(sizeof(client_t));
    int client_socket = 0;

    if (data == NULL) {
        write(2, "Error: data is NULL\n", 20);
        return KO;
    }
    client_socket = accept(data->server_socket, NULL, NULL);
    if (client_socket < 0) {
        write(2, "Error: accept failed\n", 21);
        return KO;
    }
    FD_SET(client_socket, &data->current_sockets);
    new_client->socket = client_socket;
    new_client->is_logged = 0;
    new_client->user = NULL;
    new_client->user_input = NULL;
    LIST_INSERT_HEAD(&data->clients, new_client, entries);
    write(new_client->socket, "client connected correctly\n", 28);
    return OK;
}

static user_input_t *read_client_msg(int client_socket, server_data_t *server_data)
{
    int nb_bytes = 0;
    user_input_t *client_msg = malloc(sizeof(user_input_t));

    if (client_msg == NULL) {
        write(2, "Error: malloc failed\n", 21);
        return NULL;
    }
    nb_bytes = read(client_socket, client_msg, sizeof(user_input_t));
    if (nb_bytes == -1) {
        free(client_msg);
        return NULL;
    }
    if (nb_bytes == 0) {
        free(client_msg);
        server_data->client_is_deco = 1;
    }
    return client_msg;
}

user_input_t *read_client(server_data_t *server_data, int client_socket)
{
    user_input_t *client_msg = NULL;

    if (server_data == NULL) {
        write(2, "Error: data is NULL\n", 20);
        return NULL;
    }
    client_msg = read_client_msg(client_socket, server_data);
    if (client_msg == NULL) {
        write(2, "Error: read_client_msg failed\n", 30);
        return NULL;
    }
    return client_msg;
}
