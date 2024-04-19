/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** read_server_message
*/

#include "client.h"
#include <unistd.h>
#include <stdio.h>

static int check(int ret, char *msg)
{
    if (ret == ERROR) {
        perror(msg);
        return KO;
    }
    return OK;
}

char *read_server_message(client_t *client)
{
    char buffer[BUFFER_SIZE];
    int n_bytes_read = 0;
    int msg_size = 0;

    n_bytes_read = read(client->socket_fd, buffer + msg_size, sizeof(buffer) -
        msg_size - 1);
    if (n_bytes_read == 0)
        return NULL;
    while (n_bytes_read > 0) {
        msg_size += n_bytes_read;
        if (msg_size > BUFFER_SIZE - 1 || buffer[msg_size - 1] == '\0' ||
        buffer[msg_size - 1] == '\n' || buffer[msg_size] == '\n')
            break;
        n_bytes_read = read(client->socket_fd, buffer + msg_size,
        sizeof(buffer) - msg_size - 1);
    }
    if (check(n_bytes_read, "read") == KO)
        return NULL;
    buffer[msg_size] = '\0';
    return strdup(buffer);
}
