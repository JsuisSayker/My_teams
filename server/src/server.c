/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** server
*/

#include <signal.h>
#include <errno.h>
#include "server.h"

bool running = true;

void signal_handler(int signal)
{
    if (signal == SIGINT)
        running = false;
}

int server_response(int socket, char *message)
{
    if (socket == -1 || message == NULL)
        return ERROR;
    if (write(socket, message, strlen(message)) == ERROR) {
        printf("Error: write failed\n");
        return ERROR;
    }
    return 0;
}

static int server_loop(server_data_t *server_data)
{
    int result = 0;
    fd_set read_sockets;
    fd_set write_sockets;

    FD_ZERO(&server_data->current_sockets);
    FD_SET(server_data->server_socket, &server_data->current_sockets);
    while (running) {
        server_data->ready_sockets = server_data->current_sockets;
        FD_ZERO(&read_sockets);
        FD_ZERO(&write_sockets);
        result = select(FD_SETSIZE, &server_data->ready_sockets, &write_sockets
        , NULL, NULL);
        if (result == ERROR && errno != EINTR) {
            perror("Error: select failed\n");
            return ERROR;
        }
        if (running && loop_check_select_client(server_data) == ERROR)
            return ERROR;
    }
    return OK;
}

int launch_server(char *const *const av)
{
    server_data_t *server_data = malloc(sizeof(server_data_t));

    if (!av || !server_data)
        return KO;
    signal(SIGINT, signal_handler);
    srand(time(NULL));
    server_data->client_is_deco = 0;
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
