/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** send_client_message
*/

#include <stdio.h>
#include <unistd.h>

#include "client.h"
#include <unistd.h>

void send_client_message(client_t *client)
{
    // char **command = spliter_by_sep(client->user_input->command, " |");
    // printf("client->user_input->command = [%s]\n", client->user_input->command);
    // printf("command[0] = %s\n", command[0]);
    // printf("command[1] = %s\n", command[1]);

    if (client->is_logged == true &&
    strcmp(client->user_input->command, "/help") == 0)
        display_help();
    else {
        write(client->socket_fd, client->user_input->command,
        strlen(client->user_input->command));
        printf("client->user_input->command = [%s]\n", client->user_input->command);
    }
    // free_tab(command);
}
