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

static int handle_input(client_t *client, fd_set otherfds)
{
    if (FD_ISSET(client->socket_fd, &otherfds)) {
            receive_server_message(client);
            return ERROR;
    }
    if (FD_ISSET(STDIN_FILENO, &otherfds)) {
        client->user_input->command = read_input();
        if (client->user_input->command == NULL) {
            return ERROR;
        }
        send_client_message(client);
    }
    free(client->user_input->command);
    client->user_input->command = NULL;
}

static void end_client_loop(client_t *client)
{
    free(client->user_input->params);
    free(client->user_input);
    write(1, "\n", 1);
}

static int handle_select_and_sigint(client_t *client, fd_set *readfds,
    fd_set *otherfds, int result)
{
    if (result < 0 && errno != EINTR) {
        perror("Error: select failed\n");
        return ERROR;
    }
    if (errno == EINTR) {
        free_client_struct(client, readfds, otherfds);
        return ERROR;
    }
}

static void client_loop(client_t *client)
{
    fd_set readfds;
    fd_set otherfds;
    int result = 0;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    FD_SET(client->socket_fd, &readfds);
    client->user_input = malloc(sizeof(user_input_t));
    client->user_input->params = malloc(sizeof(param_t));
    while (is_running) {
        otherfds = readfds;
        result = select(FD_SETSIZE, &otherfds, NULL, NULL, NULL);
        if (handle_select_and_sigint(client,
            &readfds, &otherfds, result) == ERROR)
            return;
        handle_input(client, otherfds);
    }
    end_client_loop(client);
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
    signal(SIGINT, signal_handler);
    client_loop(&client);
    return OK;
}
