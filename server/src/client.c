/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** client
*/

#include "server.h"

static void client_disconnection(server_data_t *server_data, int client_socket)
{
    close(client_socket);
    FD_CLR(client_socket, &server_data->current_sockets);
    FD_CLR(client_socket, &server_data->ready_sockets);
}

static int read_and_update_client(server_data_t *server_data,
    client_server_t *actual_client, int client_socket, char *client_msg)
{
    client_msg = read_client(server_data, client_socket);
    if (client_msg == NULL)
        return ERROR;
    if (actual_client->user_input == NULL) {
        actual_client->user_input = realloc(actual_client->user_input,
            strlen(client_msg) + 1);
        actual_client->user_input[0] = '\0';
    } else
        actual_client->user_input = realloc(actual_client->user_input,
            strlen(client_msg) + 1);
    strcat(actual_client->user_input, client_msg);
    if (server_data->client_is_deco == 1) {
        client_disconnection(server_data, client_socket);
        return OK;
    }
    printf("client_msg: %s\n", client_msg);
    check_command(server_data, actual_client);
    free(client_msg);
}

static int update_client(server_data_t *server_data,
    client_server_t *actual_client, int client_socket, char *client_msg)
{
    if (client_socket == server_data->server_socket) {
        if (accept_client(server_data) == ERROR)
            return ERROR;
    } else
        return read_and_update_client(server_data, actual_client,
            client_socket, client_msg);
    return OK;
}

static int check_client(server_data_t *server_data, int i)
{
    client_server_t *actual_client = NULL;
    client_server_t *tmp = server_data->clients.lh_first;

    LIST_FOREACH(tmp, &server_data->clients, entries) {
        if (tmp->socket == i) {
            actual_client = tmp;
            break;
        }
    }
    return update_client(server_data, actual_client, i, NULL);
}

static int check_select_client(server_data_t *server_data, int i)
{
    if (FD_ISSET(i, &server_data->ready_sockets)) {
        if (check_client(server_data, i) == ERROR)
            return ERROR;
    }
    return OK;
}

int loop_check_select_client(server_data_t *server_data)
{
    if (!server_data)
        return ERROR;
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (check_select_client(server_data, i) == ERROR)
            return ERROR;
    }
    return OK;
}
