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
    client_t *tmp = server_data->clients.lh_first;
    client_t *actual_client = NULL;
    char *client_msg = NULL;

    for (; tmp != NULL; tmp = LIST_NEXT(tmp, entries)) {
        if (tmp->socket == i) {
            actual_client = tmp;
            break;
        }
    }
    if (i == server_data->server_socket) {
        if (accept_client(server_data) == ERROR)
            return ERROR;
    } else {
        client_msg = read_client(server_data, i);
        if (client_msg == NULL)
            return ERROR;
        if (server_data->client_is_deco == 1) {
            client_disconnection(server_data, i);
            return OK;
        }
        actual_client->command = my_str_to_word_array(client_msg, ' ');
        // if (launch_command(server_data, client_msg, i) == ERROR) {
        //     free(client_msg);
        //     return ERROR;
        // }
        free(client_msg);
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
