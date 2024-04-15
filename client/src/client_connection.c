/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** client_connection
*/

#include "client.h"
#include <stdio.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

static void receive_server_message(client_t *client, int socket_fd)
{
    char buffer[1024];
    int received_message_len = recv(socket_fd, buffer, 1023, 0);

    if (received_message_len < 0) {
        perror("Error: receive failed\n");
        return;
    }
    buffer[received_message_len] = '\0';
    client_logout(client, "/logout");
    user_input_event(buffer, client);
}

static void client_loop(client_t *client)
{
    fd_set readfds;
    bool is_running = true;

    // client->socket_fd = socket_fd;
    while (is_running) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(client->socket_fd, &readfds);
        if (select(client->socket_fd + 1, &readfds, NULL, NULL, NULL) < 0) {
            perror("Error: select failed\n");
            return;
        }
        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            send_client_message(client);
            return;
        } else if (FD_ISSET(client->socket_fd, &readfds)) {
            receive_server_message(client, client->socket_fd);
        }
    }
    write(1, "\n", 1);
    client_logout(client, "/logout");
}

int start_client_connection(const char *ip, int port)
{
    client_t client = {.is_logged=false, .uuid=NULL, .user_name=NULL,
    .socket_fd=socket(AF_INET, SOCK_STREAM, 0), .user_input=malloc(sizeof(user_input_t))};
    // int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct hostent *client_info = gethostbyname(ip);
    struct sockaddr_in serv_addr;

    if (client_info == NULL) {
        perror("Error: no such ip\n");
        return KO;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY; // inet_addr(ip)
    if (connect(client.socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <
    0) {
        perror("Error: connection failed\n");
        return KO;
    }
    client_loop(&client);
    return OK;
}
