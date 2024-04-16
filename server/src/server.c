/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** server
*/

#include "server.h"

int response_server(int socket, char *message)
{
    if (socket == -1 || !message)
        return -1;
    write(1, message, strlen(message));
    return 0;
}

int server_loop(server_data_t *server_data)
{
    fd_set read_sockets;
    fd_set write_sockets;

    if (!server_data)
        return ERROR;
    LIST_INIT(&server_data->users);
    FD_ZERO(&server_data->current_sockets);
    FD_SET(server_data->server_socket, &server_data->current_sockets);
    while (1) {
        server_data->ready_sockets = server_data->current_sockets;

        FD_ZERO(&read_sockets);
        FD_ZERO(&write_sockets);

        if (select(FD_SETSIZE, &server_data->ready_sockets, &write_sockets,
        &read_sockets, NULL) < 0) {
            perror("Error: select failed\n");
            return ERROR;
        }
        if (loop_check_select_client(server_data) == ERROR)
            return ERROR;
    }
    return OK;
}


int launch_server(char *const *const av)
{
    server_data_t *server_data = malloc(sizeof(server_data_t));

    if (!av || !server_data)
        return KO;
    server_data->clients.lh_first = NULL;
    server_data->users.lh_first = NULL;
    server_data->server_socket = create_server_socket(av, server_data);
    if (server_data->server_socket == ERROR) {
        free_server_data(server_data);
        return KO;
    }
    if (server_loop(server_data) == ERROR) {
        free_server_data(server_data);
        return KO;
    }
    free_server_data(server_data);
    return OK;
}
