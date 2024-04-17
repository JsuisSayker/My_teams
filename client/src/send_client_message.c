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
    // char *tmp = strdup(client->user_input->command);
    // char **command = spliter_by_sep(tmp, " |");
    // printf("client->user_input->command = [%s]\n", client->user_input->command);
    // printf("command[0] = %s\n", command[0]);
    // printf("command[1] = %s\n", command[1]);

    // if (client->is_logged == true &&
    // strcmp(command[0], "/help") == 0)
    //     display_help();
    // else {
    write(client->socket_fd, client->user_input->command,
    strlen(client->user_input->command));
    // }
    // free_tab(command);
    // free(tmp);
}
