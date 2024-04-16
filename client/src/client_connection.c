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

// static int check(int ret, char *msg)
// {
//     if (ret == -1) {
//         perror(msg);
//         return KO;
//     }
//     return OK;
// }

// static char *read_client_message(client_t *client)
// {
//     printf("salut mon mignon\n");
//     char buffer[BUFFER_SIZE];
//     int n_bytes_read = 0;
//     int msg_size = 0;

//     n_bytes_read = read(client->socket_fd, buffer + msg_size, sizeof(buffer) -
//         msg_size - 1);
//     while (n_bytes_read > 0) {
//         msg_size += n_bytes_read;
//         if (msg_size > BUFFER_SIZE - 1 || buffer[msg_size - 1] == '\n')
//             break;
//         n_bytes_read = read(client->socket_fd, buffer + msg_size, sizeof(buffer) -
//             msg_size - 1);
//     }
//     if (n_bytes_read == 0)
//         client_logout(client, "/logout");
//     if (check(n_bytes_read, "read") == KO)
//         return NULL;
//     buffer[msg_size] = '\0';
//     return strdup(buffer);
// }

static void receive_server_message(client_t *client, char *user_message, int socket_fd)
{
    char buffer[1024];
    int received_message_len = recv(socket_fd, buffer, 1023, 0);


    if (received_message_len < 0) {
        perror("Error: receive failed\n");
        return;
    }
    buffer[received_message_len] = '\0';
    // client_logout(client, "/logout");
    user_input_event(buffer, user_message, client);
}

char* read_input()
{
    char* input = NULL;
    char *temp = NULL;
    char temp_char;
    int input_length = 0;

    while ((temp_char = getchar()) != '\n' && temp_char != EOF) {
        temp = realloc(input, input_length + 2);
        if (temp == NULL) {
            free(input);
            printf("Failed to allocate memory.\n");
            return NULL;
        }
        input = temp;
        input[input_length] = temp_char;
        input_length++;
    }
    if (input != NULL)
        input[input_length] = '\0';
    return input;
}

static void client_loop(client_t *client)
{
    fd_set readfds;
    bool is_running = true;

    // dprintf(1, "client_socket client's side = [%d]\n", client->socket_fd);
    char *input = NULL;
    client->user_input = malloc(sizeof(user_input_t));
    while (is_running) {
        // fgets(client->user_input->command, sizeof(client->user_input->command), stdin);
        // input = read_input();
        // client->user_input->command = malloc(strlen(read_input()));
        client->user_input->command = read_input();
        // printf("client->user_input->command = [%s]\n", input);
        // printf("client->user_input->command = [%s]\n", client->user_input->command);

        if (client->user_input->command == NULL) {
            perror("Error: fgets failed\n");
        }
        else
            send_client_message(client);

        // FD_ZERO(&readfds);
        // FD_SET(STDIN_FILENO, &readfds);
        // FD_SET(client->socket_fd, &readfds);
        // if (select(client->socket_fd, &readfds, NULL, NULL, NULL) < 0) {
        //     perror("Error: select failed\n");
        //     return;
        // }
        // if (FD_ISSET(STDIN_FILENO, &readfds)) {
        //     printf("send message\n");
        //     send_client_message(client);
        //     return;
        // } else if (FD_ISSET(client->socket_fd, &readfds)) {
        //     printf("received message\n");
        //     receive_server_message(client, "/login", client->socket_fd);
        // }
    }
    write(1, "\n", 1);
    client_logout(client, "/logout");
}

int start_client_connection(const char *ip, int port)
{
    client_t client = {.is_logged=false, .uuid=NULL, .user_name=NULL,
    .socket_fd=socket(AF_INET, SOCK_STREAM, 0)};
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
