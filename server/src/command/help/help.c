/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** help
*/

#include "server.h"

int help(server_data_t *server, client_server_t *client)
{
    char *message = NULL;
    char tmp[BUFFER_SIZE + 1];
    int fd = open("help.txt", O_RDONLY);
    ssize_t bytes_read;

    if (fd == -1)
        return ERROR;
    bytes_read = read(fd, tmp, BUFFER_SIZE);
    while (bytes_read > 0){
        tmp[bytes_read] = '\0';
        append_to_string(&message, tmp);
        bytes_read = read(fd, tmp, BUFFER_SIZE);
    }
    close(fd);
    append_to_string(&message, "\a\n");
    server_response(client->socket, message);
    free(message);
    return OK;
}
