/*
** EPITECH PROJECT, 2024
** My_teams
** File description:
** login_command
*/

#include "client.h"

int login_command(char *message, char **command, client_t *client)
{
    client->user_name = strdup(command[1]);
    client->user_input->params->user_name = strdup(command[1]);
    client->is_logged = true;
    client->uuid = strdup(command[2]);
    client->user_input->params->user_uuid = strdup(command[1]);
    client_event_logged_in(client->uuid, client->user_name);
    return OK;
}
