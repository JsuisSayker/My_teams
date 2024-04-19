/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** client_connection
*/

#include "client.h"
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

// Penser à changer le recv par un select
bool is_running = true;

static void signal_handler(int signal)
{
    if (signal == SIGINT)
        is_running = false;
}

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

static void receive_server_message(client_t *client)
{
    char *buffer = read_client_message(client);

    if (buffer == NULL)
        exit(0);
    buffer[strlen(buffer)] = '\0';
    user_input_event(buffer, client);
}

static void put_end_of_input(char **input, int input_length)
{
    if ((*input) != NULL && input_length != 1) {
        (*input)[input_length - 1] = '\a';
        (*input)[input_length] = '\n';
        (*input)[input_length + 1] = '\0';
    } else if (input_length == 1)
        (*input)[input_length - 1] = '\0';
}

static char *read_input(void)
{
    char *input = NULL;
    char *tmp = NULL;
    char tmp_char = 0;
    int input_length = 0;

    while (tmp_char != '\n' && tmp_char != EOF) {
        tmp_char = getchar();
        tmp = realloc(input, input_length + 3);
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

static void handle_input(client_t *client, fd_set otherfds)
{
    if (FD_ISSET(client->socket_fd, &otherfds)) {
            receive_server_message(client);
            return;
    }
    if (FD_ISSET(STDIN_FILENO, &otherfds)) {
        client->user_input->command = read_input();
        if (client->user_input->command == NULL) {
            return;
        }
        send_client_message(client);
    }
    free(client->user_input->command);
    client->user_input->command = NULL;
}

static void free_client_struct(client_t *client, fd_set *readfds,
    fd_set *otherfds)
{
    client->user_input->command = strdup("/logout\a\n");
    send_client_message(client);
    receive_server_message(client);
    free(client->user_input->params);
    free(client->user_input->command);
    free(client->user_input);
    free(client->user_name);
    free(client->uuid);
    FD_CLR(client->socket_fd, readfds);
    FD_CLR(client->socket_fd, otherfds);
    FD_CLR(STDIN_FILENO, readfds);
    FD_CLR(STDIN_FILENO, otherfds);
}

static void client_loop(client_t *client)
{
    fd_set readfds;
    fd_set otherfds;
    int result = 0;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    FD_SET(client->socket_fd, &readfds);
    signal(SIGINT, signal_handler);
    client->user_input = malloc(sizeof(user_input_t));
    client->user_input->params = malloc(sizeof(param_t));
    while (is_running) {
        otherfds = readfds;
        result = select(FD_SETSIZE, &otherfds, NULL, NULL, NULL);
        if (result < 0 && errno != EINTR) {
            perror("Error: select failed\n");
            return;
        }
        if (errno == EINTR) {
            free_client_struct(client, &readfds, &otherfds);
            return;
        }
        handle_input(client, otherfds);
    }
    write(1, "\n", 1);
}

// Replace INADDR_ANY by inet_addr(ip)
int start_client_connection(const char *ip, int port)
{
    client_t client = {.is_logged = false, .uuid = NULL, .user_name = NULL,
    .socket_fd = socket(AF_INET, SOCK_STREAM, 0)};
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
