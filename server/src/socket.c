/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** socket
*/

#include "server.h"

static int initialize_socket_and_check_parm(char *const *const av,
    server_data_t *data)
{
    if (av == NULL) {
        write(2, "Error: av is NULL\n", 18);
        return -1;
    }
    data->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (data->server_socket == -1) {
        write(2, "Error: socket failed\n", 21);
        return -1;
    }
    data->server_address.sin_family = AF_INET;
    data->server_address.sin_port = htons(atoi(av[1]));
    data->server_address.sin_addr.s_addr = INADDR_ANY;
    return 0;
}

int create_server_socket(char *const *const av, server_data_t *data)
{
    int op = 1;

    if (initialize_socket_and_check_parm(av, data) == -1)
        return -1;
    setsockopt(data->server_socket, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op));
    if (bind(data->server_socket, (struct sockaddr *)&data->server_address,
    sizeof(data->server_address)) == -1) {
        write(2, "Error: bind failed\n", 19);
        return -1;
    }
    if (listen(data->server_socket, 50) == -1) {
        write(2, "Error: listen failed\n", 21);
        return -1;
    }
    return data->server_socket;
}
