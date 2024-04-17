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

// Penser à changer le recv par un select

static int check(int ret, char *msg)
{
    if (ret == ERROR) {
        perror(msg);
        return KO;
    }
    return OK;
}

static char *read_client_message(client_t *client)
{
    char buffer[BUFFER_SIZE];
    int n_bytes_read = 0;
    int msg_size = 0;

    n_bytes_read = read(client->socket_fd, buffer + msg_size, sizeof(buffer) -
        msg_size - 1);
    while (n_bytes_read > 0) {
        msg_size += n_bytes_read;
        if (msg_size > BUFFER_SIZE - 1 || buffer[msg_size - 1] == '\0' ||
        buffer[msg_size - 1] == '\n')
            break;
        n_bytes_read = read(client->socket_fd, buffer + msg_size,
        sizeof(buffer) - msg_size - 1);
    }
    if (n_bytes_read == 0)
        client_logout(client, "/logout");
    if (check(n_bytes_read, "read") == KO)
        return NULL;
    buffer[msg_size] = '\0';
    return strdup(buffer);
}

static void receive_server_message(client_t *client)
{
    char *buffer = read_client_message(client);

    if (strlen(buffer) == 0)
        return;
    buffer[strlen(buffer)] = '\0';
    user_input_event(buffer, client);
}

static void put_end_of_input(char **input, int input_length)
{
    if ((*input) != NULL) {
        (*input)[input_length] = '\a';
        (*input)[input_length + 1] = '\n';
    }
}

static char *read_input(void)
{
    char *input = NULL;
    char *tmp = NULL;
    char tmp_char = 0;
    int input_length = 0;

    while (tmp_char != '\n' && tmp_char != EOF) {
        tmp_char = getchar();
        tmp = realloc(input, input_length + 1);
        if (tmp == NULL) {
            free(input);
            return NULL;
        }
        input = tmp;
        input[input_length] = tmp_char;
        input_length += 1;
    }
    put_end_of_input(&input, input_length);
    return input;
}

static void client_loop(client_t *client)
{
    fd_set readfds;
    fd_set otherfds;
    bool is_running = true;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    FD_SET(client->socket_fd, &readfds);
    client->user_input = malloc(sizeof(user_input_t));
    client->user_input->params = malloc(sizeof(param_t));
    while (is_running) {
        otherfds = readfds;
        if (select(client->socket_fd + 1, &otherfds, NULL, NULL, NULL) < 0) {
            perror("Error: select failed\n");
            return;
        }
        if (FD_ISSET(client->socket_fd, &otherfds)) {
            receive_server_message(client);
        } else if (FD_ISSET(STDIN_FILENO, &otherfds)) {
            client->user_input->command = read_input();
            if (client->user_input->command == NULL) {
                return;
            }
            send_client_message(client);
        }
        free(client->user_input->command);
        client->user_input->command = NULL;
    }
    write(1, "\n", 1);
    client_logout(client, "/logout");
}

// Replace INADDR_ANY by inet_addr(ip)
int start_client_connection(const char *ip, int port)
{
    client_t client = {.is_logged = false, .uuid = NULL, .user_name = NULL,
    .socket_fd = socket(AF_INET, SOCK_STREAM, 0), .server_response = NULL};
    struct hostent *client_info = gethostbyname(ip);
    struct sockaddr_in serv_addr;

    if (client_info == NULL) {
        perror("Error: no such ip\n");
        return KO;
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    if (connect(client.socket_fd, (struct sockaddr *)&serv_addr,
    sizeof(serv_addr)) < 0) {
        perror("Error: connection failed\n");
        return KO;
    }
    client_loop(&client);
    return OK;
}
