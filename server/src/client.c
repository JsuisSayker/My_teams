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

static int check_client(server_data_t *server_data, int i)
{
    client_server_t *tmp = server_data->clients.lh_first;
    client_server_t *actual_client = NULL;

    LIST_FOREACH(tmp, &server_data->clients, entries) {
        if (tmp->socket == i) {
            actual_client = tmp;
            break;
        }
    }
    if (i == server_data->server_socket) {
        printf("new client\n");
        if (accept_client(server_data) == ERROR)
            return ERROR;
    } else {
        printf("client %d\n", i);
        actual_client->user_input = read_client(server_data, i);
        if (actual_client->user_input == NULL)
            return ERROR;
        if (server_data->client_is_deco == 1) {
            client_disconnection(server_data, i);
            return OK;
        }
        // printf("client message: %s\n", actual_client->user_input->command);
        // if (launch_command(server_data, client_msg, i) == ERROR) {
        //     free(client_msg);
        //     return ERROR;
        // }
    }
    return OK;
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
