/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** accept
*/

#include "server.h"

int accept_client(server_data_t *data)
{
    client_t *new_client = malloc(sizeof(client_t));
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
    LIST_INSERT_HEAD(&data->clients, new_client, entries);
    write(new_client->socket, "client connected correctly\n", 28);
    return OK;
}

static char *read_client_msg(int client_socket, server_data_t *data)
{
    int msg_size = 0;
    int nb_bytes = 0;
    char buffer[BUFSIZ];

    nb_bytes = read(client_socket, buffer + msg_size, sizeof(buffer) -
        msg_size - 1);
    while (nb_bytes > 0) {
        msg_size += nb_bytes;
        if (msg_size > BUFSIZ - 1 || buffer[msg_size - 1] == '\n')
            break;
        nb_bytes = read(client_socket, buffer + msg_size, sizeof(buffer) -
            msg_size - 1);
    }
    if (nb_bytes == -1)
        return NULL;
    // if (nb_bytes == 0)
        // data->client_is_deco = 1;
    buffer[msg_size] = '\0';
    return strdup(buffer);
}

char *read_client(server_data_t *data, int client_socket)
{
    char *client_msg = read_client_msg(client_socket, data);

    if (data == NULL) {
        write(2, "Error: data is NULL\n", 20);
        return NULL;
    }
    if (client_msg == NULL) {
        write(2, "Error: read_client_msg failed\n", 30);
        return NULL;
    }
    return client_msg;
}
