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
static void receive_server_message(client_t *client)
{
    char buffer[1024];
    int received_message_len = recv(client->socket_fd, buffer, 1023, 0);

    if (received_message_len < 0) {
        perror("Error: receive failed\n");
        return;
    }
    if (received_message_len == 0)
        return;
    buffer[received_message_len] = '\0';
    printf("buffer = %s\n", buffer);
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
    bool is_running = true;

    client->user_input = malloc(sizeof(user_input_t));
    client->user_input->params = malloc(sizeof(param_t));
    while (is_running) {
        client->user_input->command = read_input();
        if (client->user_input->command == NULL) {
            client->user_input->command = strdup("\0");
        }
        send_client_message(client);
        receive_server_message(client);
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
